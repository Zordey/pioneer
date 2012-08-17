--
-- Class: EventQueue
--
-- A class to manage a queue of events.
--
-- The majority of the work done by a Pioneer Lua module is in response to
-- events. The typical structure of a module will be to define a number of
-- event handler functions and then register them with the appropriate event
-- queues.
--
-- When particular events occur within the game, such as a ship docking or the
-- player coming under attack, the appropriate <EventQueue> object is
-- triggered. This causes all functions registered with the event queue to be
-- called, in no particular order.
--
-- An event usually has one or more parameters attached to it that describe
-- the details of the event. For example, the <onShipDocked> event has two
-- parameters, the <Ship> that docked, and the <SpaceStation> it docked with.
--
-- Many of these events are triggered as a result of something happening to a
-- <Ship>. The same events are used when something happens to a <Player>
-- (which is also a <Ship>). Call the <Ship.IsPlayer> method on the <Ship> if
-- your module needs to know the difference.
--
-- The <EventQueue> objects are available under the global EventQueue
-- namespace.
--
EventQueue = {
	Create = function (name)
		local events = {}
		local callbacks = {}

		EventQueue["on"..name] = {

			--
			-- Method: Connect
			--
			-- Connect a function to an event queue. When the queue emits an event, the
			-- function will be called.
			--
			-- > onEvent:Connect(function)
			--
			-- Parameters:
			--
			--   function - function to call when the queue emits an event. The function
			--			  will recieve a copy of the parameters attached to the event
			--
			--
			-- Example:
			--
			-- > EventQueue.onEnterSystem:Connect(function (ship)
			-- >	 print("welcome to "..Game.system.name..", "..ship.label)
			-- > end)
			--
			-- Availability:
			--
			--   alpha 10
			--
			-- Status:
			--
			--   stable
			--
			Connect = function (cb)
				callbacks[cb] = cb
			end,

			--
			-- Method: Disconnect
			--
			-- Disconnects a function from an event queue. The function will no long
			-- receive events emitted by the queue.
			--
			-- If the function is not connected to the queue this method does nothing.
			--
			-- > onEvent:Disconnect(function)
			--
			-- Parameters:
			--
			--   function - a function that was previously connected to this queue with
			--              <Connect>
			--
			-- Availability:
			--
			--   alpha 10
			--
			-- Status:
			--
			--   stable
			--
			Disconnect = function (cb)
				callbacks[cb] = nil
			end,

			--
			-- Method: DebugTimer
			--
			-- Enables the function timer for this event queue. When enabled the console
			-- will display the amount of time that each function attached to this queue
			-- takes to run.
			--
			-- > onEvent:DebugTimer(enabled)
			--
			-- Parameters:
			--
			--   enabled - a true value to enable the timer, or a false value to disable
			--             it.
			--
			-- Availability:
			--
			--   alpha 19
			--
			-- Status:
			--
			--   debug
			--
			DebugTimer = function (enabled)
				-- XXX implement this
			end,

			-- XXX document this
			Queue = function (...)
				table.insert(events, {...})
			end,

			-- XXX document this
			Signal = function (...)
				local e = {...}
				for cb,_ in pairs(callbacks) do
					cb(table.unpack(e))
				end
			end,

			-- XXX document this
			Emit = function ()
				while #events > 0 do
					local e = table.remove(events, 1)
					for cb,_ in pairs(callbacks) do
						cb(table.unpack(e))
					end
				end
			end,

			-- XXX document this
			ClearEvents = function ()
				events = {}
			end,
		}
	end
}

--
-- Event: onGameStart
--
-- Triggered when the game is first initialised.
--
-- > local onGameStart = function () ... end
-- > EventQueue.onGameStart:Connect(onGameStart)
--
-- onGameStart is triggered just after the physics <Body> objects (including
-- the <Player>) are placed.
--
-- This is a good place to add equipment to the Player ship or spawn objects
-- in the space. You should also initialise your module data for the game
-- here.
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("GameStart");

--
-- Event: onGameEnd
--
-- Triggered when game is finished.
--
-- > local onGameEnd = function () ... end
-- > EventQueue.onGameEnd:Connect(onGameEnd)
--
-- Triggered just before the physics <Body> objects (include the <Player>) are
-- destroyed and Pioneer returns to the main menu.
--
-- You should clean up any game data here. Remember that your module will be
-- re-used if the player begins another game. You probably don't want any data
-- from a previous game to leak into a new one.
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("GameEnd");

--
-- Event: onEnterSystem
--
-- Triggered when a ship enters a system after hyperspace.
--
-- > local onEnterSystem = function (ship) ... end
-- > EventQueue.onEnterSystem:Connect(onEnterSystem)
--
-- This is the place to spawn pirates and other attack ships to give the
-- illusion that the ship was followed through hyperspace.
--
-- Note that this event is *not* triggered at game start.
--
-- Parameters:
--
--   ship - the <Ship> that entered the system
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("EnterSystem");

--
-- Event: onLeaveSystem
--
-- Triggered immediately before ship leaves a system and enters hyperspace.
--
-- > local onLeaveSystem = function (ship) ... end
-- > EventQueue.onLeaveSystem:Connect(onLeaveSystem)
--
-- If the ship was the player then all physics <Body> objects are invalid after
-- this method returns.
--
-- Parameters:
--
--   ship - the <Ship> that left the system
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("LeaveSystem");

--
-- Event: onFrameChanged
--
-- Triggered as a dynamic <Body> moves between frames of reference.
--
-- > local onFrameChanged = function (body) ... end
-- > EventQueue.onFrameChanged:Connect(onFrameChanged)
--
-- Details of the new frame itself can be obtained from the body's
-- <Body.frameBody> and <Body.frameRotating> attributes.
--
-- Parameters:
--
--   body - the dynamic <Body> that changed frames
--
-- Availability:
--
--   alpha 12
--
-- Status:
--
--   experimental
--
EventQueue.Create("FrameChanged");

--
-- Event: onShipDestroyed
--
-- Triggered when a ship is destroyed.
--
-- > local onShipDestroyed = function (ship, attacker) ... end
-- > EventQueue.onShipDestroyed:Connect(onShipDestroyed)
--
-- Parameters:
--
--   ship - the ship that was destroyed
--
--   attacker - the <Body> that was responsible for reducing the ship's hull
--   strength to 0. Usually a ship that fired lasers or missiles, but may be
--   another <Body> (eg <Planet> or <SpaceStation>) if the ship was destroyed
--   by a collision.
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("ShipDestroyed");

--
-- Event: onShipHit
--
-- Triggered when a ship is hit by laser fire or a missile.
--
-- > local onShipHit = function (ship, attacker) ... end
-- > EventQueue.onShipHit:Connect(onShipHit)
--
-- Parameters:
--
--   ship - the <Ship> that was hit
--
--   attacker - the <Ship> that fired the laser or missile
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("ShipHit");

--
-- Event: onShipCollided
--
-- Triggered when a ship collides with an object.
--
-- > local onShipCollided = function (ship, other) ... end
-- > EventQueue.onShipCollided:Connect(onShipCollided)
--
-- If the ship collides with a city building on a planet it will register as
-- as collision with the planet itself.
--
-- If the ship "collides" with a missile, <onShipHit> will be triggered
-- instead of <onShipCollided>.
--
-- If the ship hit another <Ship>, this event will be triggered twice, once
-- for each ship.
--
-- Parameters:
--
--   ship - the <Ship> that was hit
--
--   other - the <Body> that the ship collided with
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("ShipCollided");

--
-- Event: onShipDocked
--
-- Triggered when a ship docks with a space station.
--
-- > local onShipDocked = function (ship, station) ... end
-- > EventQueue.onShipDocked:Connect(onShipDocked)
--
-- Parameters:
--
--   ship - the <Ship> that docked
--
--   station - the <SpaceStation> the ship docked with
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("ShipDocked");

--
-- Event: onShipUndocked
--
-- Triggered when a ship undocks with a space station.
--
-- > local onShipUndocked = function (ship, station) ... end
-- > EventQueue.onShipUndocked:Connect(onShipUndocked)
--
-- Parameters:
--
--   ship - the <Ship> that docked
--
--   station - the <SpaceStation> the ship undocked with
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("ShipUndocked");

--
-- Event: onShipLanded
--
-- Triggered when a ship performs a surface landing
-- (not on a spaceport).
--
-- > local onShipLanded = function (ship, body) ... end
-- > EventQueue.onShipLanded:Connect(onShipLanded)
--
-- Parameters:
--
--   ship - the <Ship> that landed
--
--   body - the <Body> the ship landed on
--
-- Availability:
--
--   alpha 13
--
-- Status:
--
--   experimental
--
EventQueue.Create("ShipLanded");

--
-- Event: onShipTakeOff
--
-- Triggered when a ship takes off from a surface
-- (not from a spaceport).
--
-- > local onBlastOff = function (ship, body) ... end
-- > EventQueue.onShipTakeOff:Connect(onBlastOff)
--
-- Parameters:
--
--   ship - the <Ship> that took off
--
--   body - the <Body> the ship took off from
--
-- Availability:
--
--   alpha 13
--
-- Status:
--
--   experimental
--
EventQueue.Create("ShipTakeOff");

--
-- Event: onShipAlertChanged
--
-- Triggered when a ship's alert status changes.
--
-- > local onShipAlertChanged = function (ship, alert) ... end
-- > EventQueue.onShipAlertChanged:Connect(onShipAlertChanged)
--
-- Parameters:
--
--   ship - the <Ship> that changed status
--
--   alert - the new <Constants.ShipAlertStatus>
--
--  Availability:
--
--    alpha 10
--
--  Status:
--
--    stable
--
EventQueue.Create("ShipAlertChanged");

--
-- Event: onJettison
--
-- Triggered when a ship jettisons a cargo item.
--
-- > local onJettison = function (ship, cargo) ... end
-- > EventQueue.onJettison:Connect(onJettison)
--
-- Parameters:
--
--   ship - the <Ship> that jettisoned the cargo item
--
--   cargo - the <CargoBody> now drifting in space
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   experimental
--
EventQueue.Create("Jettison");

--
-- Event: onCargoUnload
--
-- Triggered when the player unloads a cargo item while docked or landed.
--
-- > local onUnload = function (body, cargoType) ... end
-- > EventQueue.onCargoUnload:Connect(onUnload)
--
-- Parameters:
--
--   body - the <Body> the <Player> was docked with (a <SpaceStation>) or landed on (a <Planet>)
--
--   cargoType - <EquipType> of the unloaded cargo
--
-- Availability:
--
--   alpha 18
--
-- Status:
--
--   experimental
--
EventQueue.Create("CargoUnload");

--
-- Event: onAICompleted
--
-- Triggered when a ship AI completes
--
-- > local onAICompleted = function (ship, error) ... end
-- > EventQueue.onAICompleted:Connect(onAICompleted)
--
-- Parameters:
--
--   ship - the <Ship>
--
--   error - the <Constants.ShipAIError>
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("AICompleted");

--
-- Event: onCreateBB
--
-- Triggered when a space station bulletin board is created.
--
-- > local onCreateBB = function (station) ... end
-- > EventQueue.onCreateBB:Connect(onCreateBB)
--
-- The usual function of a <onCreateBB> event handler is to call
-- <SpaceStation.AddAdvert> to populate the bulletin board with ads.
--
-- This event is triggered the first time a <Ship> docks with the station or
-- is placed directly into the station (eg by <Space.SpawnShipDocked> or at
-- game start)
--
-- Parameters:
--
--   station - the <SpaceStation> the bulletin board is being created for
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("CreateBB");

--
-- Event: onUpdateBB
--
-- Triggered every 1-2 hours of game time to update the bulletin board.
--
-- > local onUpdateBB = function (station) ... end
-- > EventQueue.onUpdateBB:Connect(onUpdateBB)
--
-- The usual function of a <onUpdateBB> event handler is to call
-- <SpaceStation.AddAdvert> and <SpaceStation.RemoveAdvert> to update the
-- bulletin board.
--
-- This event is triggered at a random game time 1-2 hours after it was
-- previously called. This period is subject to change; script authors should
-- not rely on it.
--
-- <onUpdateBB> will never be triggered for a station that has not previously
-- had <onCreateBB> triggered for it.
--
-- Parameters:
--
--   station - the <SpaceStation> the bulletin board is being updated for
--
-- Availability:
--
--   alpha 10
--
-- Status:
--
--   stable
--
EventQueue.Create("UpdateBB");

--
-- Event: onShipFlavourChanged
--
-- Triggered when a ship's type, registration or graphical flavour changes.
--
-- > local onShipFlavourChanged = function (ship) ... end
-- > EventQueue.onShipFlavourChanged:Connect(onShipFlavourChanged)
--
-- Parameters:
--
--   ship - the <Ship> whose type or graphical flavour just changed
--
-- Availability:
--
--   alpha 15
--
-- Status:
--
--   experimental
--
EventQueue.Create("ShipFlavourChanged");

--
-- Event: onShipEquipmentChanged
--
-- Triggered when a ship's equipment set changes.
--
-- > local onShipEquipmentChanged = function (ship, equipType) ... end
-- > EventQueue.onShipEquipmentChanged:Connect(onShipEquipmentChanged)
--
-- Parameters:
--
--   ship - the <Ship> whose equipment just changed
--
--   equipType - the string ID of the <EquipType> that was added or removed,
--   or 'NONE' if the change involved multiple types of equipment
--
-- Availability:
--
--   alpha 15
--
-- Status:
--
--   experimental
--
EventQueue.Create("ShipEquipmentChanged");

--
-- Event: onShipFuelChanged
--
-- Triggered when a ship's fuel status changes.
--
-- > local onShipFuelChanged = function (ship, fuelStatus) ... end
-- > EventQueue.onShipFuelChanged:Connect(onShipFuelChanged)
--
-- Parameters:
--
--   ship - the <Ship> whose fuel status just changed
--
--   fuelStatus - the new <Constants.ShipFuelStatus>
--
-- Availability:
--
--   alpha 20
--
-- Status:
--
--   experimental
--
EventQueue.Create("ShipFuelChanged");

-- XXX document this
EventQueue.Create("SongFinished");
