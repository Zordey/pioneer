-- Copyright © 2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

-- This module allows the player to hire crew members through BB adverts
-- on stations, and handles periodic events such as their wages.

-- Get the translator function
local t = Translate:GetTranslator()
local wage_period = 604800 -- a week of seconds

-- The contract for a crew member is a table containing their weekly wage,
-- the date that they should next be paid and the amount outstanding if
-- the player has been unable to pay them.
--
-- contract = {
--   wage = 0,
--   payday = 0,
--   outstanding = 0,
-- }

---------------------- Part 1 ----------------------
-- Life aboard ship

local boostCrewSkills = function (crewMember)
	-- Each week, there's a small chance that a crew member gets better
	-- at each skill, due to the experience of working on the ship.

	-- If they fail their intelligence roll, they learn nothing.
	if not crewMember:TestRoll('intelligence') then return end

	-- The attributes to be tested and possibly enhanced. These will be sorted
	-- by their current value, but appear first in arbitrary order.
	local attribute = {
		{'engineering',crewMember.engineering},
		{'piloting',crewMember.piloting},
		{'navigation',crewMember.piloting},
		{'sensors',crewMember.sensors},
	}
	table.sort(attribute,function (a,b) return a[2] > b[2] end)
	-- The sorted attributes mean that the highest scoring attribute gets the
	-- first opportunity for improvement. The next loop actually makes it harder
	-- for the highest scoring attributes to improve, so if they fail, the next
	-- one is given an opportunity. At most one attribute will be improved, and
	-- the distribution means that, for example, a pilot will improve in piloting
	-- first, but once that starts to get very good, the other skills will start
	-- to see an improvement.

	for i = 1,#attribute do
		-- A carefully weighted test here. Scores will creep up to the low 50s.
		if not crewMember:TestRoll(attribute[i][1],math.floor(attribute[i][2] * 0.2 - 10)) then
			-- They learned from their failure,
			crewMember[attribute[i][1]] = crewMember[attribute[i][1]]+1
			-- but only on this skill.
			break
		end
	end
end

local scheduleWages = function (crewMember)
	-- Must have a contract to be treated like crew
	if not crewMember.contract then return end

	local payWages
	payWages = function ()
		local contract = crewMember.contract
		-- Check if crew member has been dismissed
		if not contract then return end

		if Game.player:GetMoney() > contract.wage then
			Game.player:AddMoney(0 - contract.wage)
		else
			contract.outstanding = contract.outstanding + contract.wage
		end
		
		-- Attempt to pay off any arrears
		local arrears = math.min(Game.player:GetMoney(),contract.outstanding)
		Game.player:AddMoney(0 - arrears)
		contract.outstanding = contract.outstanding - arrears

		-- The crew gain experience each week, and might get better
		boostCrewSkills(crewMember)

		-- Schedule the next pay day, if there is one.
		if contract.payday then
			contract.payday = contract.payday + wage_period
			Timer:CallAt(contract.payday,payWages)
		end
	end

	Timer:CallAt(crewMember.contract.payday,payWages)
end

-- This gets run just after crew are restored from a saved game
Event.Register('crewAvailable',function()
	-- scheduleWages() for everybody
	for crewMember in Game.player:EachCrewMember() do
		scheduleWages(crewMember)
	end
end)

-- This gets run whenever a crew member joins a ship
Event.Register('onJoinCrew',function(ship, crewMember)
	if ship:IsPlayer() then
		scheduleWages(crewMember)
	end
end)

-- This gets run whenever a crew member leaves a ship
Event.Register('onLeaveCrew',function(ship, crewMember)
	if ship:IsPlayer() and crewMember.contract then
		crewMember.contract.payday = nil
	end
end)

---------------------- Part 2 ----------------------
-- The bulletin board

local nonPersistentCharactersForCrew = {}

local wageFromScore = function(score)
	-- Default score is four 15s (=60). Anybody with that or less
	-- gets minimum wage offered.
	score = math.max(0,score-60)
	return math.floor(score * score / 100) + 10
end

local onCreateBB = function (station)
	-- Create non-persistent Characters as available crew
	nonPersistentCharactersForCrew[station] = {}
	-- Number is based on population, nicked from Assassinations.lua and tweaked
	for i = 1, Engine.rand:Integer(0, math.ceil(Game.system.population) * 2 + 1) do
		local hopefulCrew = Character.New()
		-- Roll new stats, with a 1/3 chance that they're utterly inexperienced
		hopefulCrew:RollNew(Engine.rand:Integer(0, 2) > 0)
		-- Make them a title if they're good at anything
		local maxScore = math.max(hopefulCrew.engineering,
									hopefulCrew.piloting,
									hopefulCrew.navigation,
									hopefulCrew.sensors)
		if maxScore > 45 then
			if hopefulCrew.engineering == maxScore then hopefulCrew.title = t("Ship's Engineer") end
			if hopefulCrew.piloting == maxScore then hopefulCrew.title = t("Pilot") end
			if hopefulCrew.navigation == maxScore then hopefulCrew.title = t("Navigator") end
			if hopefulCrew.sensors == maxScore then hopefulCrew.title = t("Sensors and defence") end
		end
		table.insert(nonPersistentCharactersForCrew[station],hopefulCrew)
	end

	local crewInThisStation -- Table of available folk available for hire here

	local candidate -- Run-time "static" variable for onChat
	local offer

	-- Define onChat locally, so that it can see station arg
	local onChat = function (form,ref,option)

		if option == -1 then
			-- Hang up
			candidate = nil
			form:Close()
			return
		end

		if option == 0 then
			-- Not currently candidate; option values indicate crewInThisStation index
			candidate = nil
			-- Re-initialise crew list, and build it fresh
			crewInThisStation = {}

			-- Look for any persistent characters that are available in this station
			-- and have some sort of crew experience (however minor)
			-- and were last seen less than a month ago
			for c in Character.Find(function (c)
										return true
											and c.lastSavedSystemPath == station.path
											and c.available
											and (
												c.engineering > 16
												or c.piloting > 16
												or c.navigation > 16
												or c.sensors > 16
											)
											and Game.time - c.lastSavedTime < 2419200 -- (28 days)
									end) do
				table.insert(crewInThisStation,c)
				c.experienceScore = c.engineering
												+c.piloting
												+c.navigation
												+c.sensors
				-- Either base wage on experience, or as a slight increase on their previous wage
				c.estimatedWage = c.contract and c.contract.wage + 5 or c.estimatedWage or wageFromScore(c.experienceScore)
			end
			-- Now add any non-persistent characters (which are persistent only in the sense
			-- that this BB ad is storing them)
			for k,c in ipairs(nonPersistentCharactersForCrew[station]) do
				table.insert(crewInThisStation,c)
				c.experienceScore = c.engineering
												+c.piloting
												+c.navigation
												+c.sensors
				-- Base wage on experience
				c.estimatedWage = c.estimatedWage or wageFromScore(c.experienceScore)
			end

			form:SetTitle(t("Crew for hire"))
			form:Clear()
			form:SetMessage(t("Potential crew members are registered as seeking employment at {station}:"):interp({station=station.label}))
			for k,c in ipairs(crewInThisStation) do
				form:AddOption(t('Examine {potentialCrewMember} ({wage}/wk)'):interp({potentialCrewMember = c.name,wage = c.contract and c.contract.wage or c.estimatedWage}),k)
				if k > 12 then break end -- XXX They just won't all fit on screen. New UI can scroll.
			end
			form:AddOption(t('HANG_UP'), -1)
		end

		local showCandidateDetails = function (response)
			local experience =
				candidate.experienceScore > 160 and t('Veteran, time served crew member') or
				candidate.experienceScore > 140 and t('Time served crew member') or
				candidate.experienceScore > 100 and t('Minimal time served aboard ship') or
				candidate.experienceScore >  60 and t('Some experience in controlled environments') or
				candidate.experienceScore >  10 and t('Simulator training only') or
				t('No experience')
			form:SetFace(candidate)
			form:Clear()
			candidate:PrintStats()
			print("Attitude: ",candidate.playerRelationship)
			print("Aspiration: ",candidate.estimatedWage)
			form:SetMessage(t('crewDetailSheetBB'):interp({
				name = candidate.name,
				experience = experience,
				wage = Format.Money(offer),
				response = response,
			}))
			form:AddOption(t('Make offer of position on ship for stated amount'),1)
			form:AddOption(t('Suggest new weekly wage of {newAmount}'):interp({newAmount=Format.Money(offer*2)}),2)
			form:AddOption(t('Suggest new weekly wage of {newAmount}'):interp({newAmount=Format.Money(offer+5)}),3)
			form:AddOption(t('Suggest new weekly wage of {newAmount}'):interp({newAmount=Format.Money(offer-5)}),4)
			form:AddOption(t('Suggest new weekly wage of {newAmount}'):interp({newAmount=Format.Money(math.floor(offer/2))}),5)
			form:AddOption(t('GO_BACK'), 0)
			form:AddOption(t('HANG_UP'), -1)
		end
		
		if option > 0 then
			
			if not candidate then
				-- Absence of candidate indicates that option is to select a candidate,
				-- and that is all.
				candidate = crewInThisStation[option]
				offer = candidate.estimatedWage
				showCandidateDetails('')
				return
			end

			if option == 1 then
				-- Offer of employment
				form:Clear()
				if candidate:TestRoll('playerRelationship',15) then
					-- Boosting roll by 15, because they want to work
					if Game.player:Enroll(candidate) then
						candidate.contract = {
							wage = offer,
							payday = Game.time + wage_period,
							outstanding = 0
						}
						form:SetMessage(t("Thanks, I'll get settled on board immediately."))
						form:AddOption(t('GO_BACK'), 0)
						form:AddOption(t('HANG_UP'), -1)
					else
						form:SetMessage(t("Sorry, there seems to be a problem. Do you already have a full crew?"))
						form:AddOption(t('GO_BACK'), 0)
						form:AddOption(t('HANG_UP'), -1)
					end
				else
					form:SetMessage(t("I'm sorry, your offer isn't attractive to me."))
					form:AddOption(t('GO_BACK'), 0)
					form:AddOption(t('HANG_UP'), -1)
				end
				offer = nil
				candidate = nil
			end

			if option == 2 then
				-- Player suggested doubling the offer
				candidate.playerRelationship = candidate.playerRelationship + 5
				offer = offer * 2
				candidate.estimatedWage = offer -- They'll now re-evaluate themself
				showCandidateDetails(t("That's extremely generous of you!"))
			end

			if option == 3 then
				-- Player suggested an extra $5
				candidate.playerRelationship = candidate.playerRelationship + 1
				offer = offer + 5
				candidate.estimatedWage = offer -- They'll now re-evaluate themself
				showCandidateDetails(t("That certainly makes this offer look better!"))
			end

			if option == 4 then
				-- Player suggested $5 less
				candidate.playerRelationship = candidate.playerRelationship - 1
				if candidate:TestRoll('playerRelationship') then
					offer = offer - 5
					showCandidateDetails(t("OK, I suppose that's all right."))
				else
					showCandidateDetails(t("I'm sorry, I'm not prepared to go any lower."))
				end				
			end

			if option == 5 then
				-- Player suggested halving the offer
				candidate.playerRelationship = candidate.playerRelationship - 5
				if candidate:TestRoll('playerRelationship') then
					offer = math.floor(offer / 2)
					showCandidateDetails(t("OK, I suppose that's all right."))
				else
					showCandidateDetails(t("I'm sorry, I'm not prepared to go any lower."))
				end				
			end

		end

	end

	-- Only one crew hiring thingy per station
	station:AddAdvert(t('Crew for hire'), onChat)
end

Event.Register("onCreateBB", onCreateBB)

-- Wipe temporary crew out when hyperspacing
Event.Register("onEnterSystem", function(ship)
	if ship:IsPlayer() then nonPersistentCharactersForCrew = {} end
end)

-- Load temporary crew from saved data
local loaded_data
Event.Register("onGameStart", function()
	if loaded_data then
		nonPersistentCharactersForCrew = loaded_data.nonPersistentCharactersForCrew
	end
end)

local serialize = function ()
        return { nonPersistentCharactersForCrew = nonPersistentCharactersForCrew }
end

local unserialize = function (data)
        loaded_data = data
end

