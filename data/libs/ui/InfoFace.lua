<<<<<<< HEAD
local ui = Engine.ui
local t = Translate:GetTranslator()
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = import("Engine")

local Face = import("UI.Game.Face")

local ui = Engine.ui
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

local testCharacter = function (character)
	if not (character and (type(character)=='table') and (getmetatable(character).class == 'Character'))
	then
		error ('Character object expected')
	end
end

local setFaceInfo = function (face, character)
	face:SetInnerWidget(
		ui:Align("BOTTOM_LEFT"):SetInnerWidget(
			ui:Expand("HORIZONTAL"):SetInnerWidget(
				ui:Gradient({r=0.1,g=0.1,b=0.1,a=0.8}, {r=0.0,g=0.0,b=0.1,a=0.0}, "HORIZONTAL"):SetInnerWidget(
					ui:Margin(20):SetInnerWidget(ui:VBox():PackEnd({
						ui:Label(character.name):SetFont("HEADING_NORMAL"),
<<<<<<< HEAD
						ui:Label((t(character.title) or '')):SetFont("HEADING_SMALL"),
=======
						ui:Label(character.title or ''):SetFont("HEADING_SMALL"),
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
					}))
				)
			)
		)
	)
end

<<<<<<< HEAD
UI.InfoFace = {

New = function (character)
=======
local InfoFace = {}

function InfoFace.New (character)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	testCharacter(character)

	local faceFlags = {
		character.female and "FEMALE" or "MALE",
<<<<<<< HEAD
		character.armor and "ARMOUR",
	}

	local self = {
		widget = UI.Game.Face.New(ui, faceFlags, character.seed)
=======
	}
	if character.armour then table.insert(faceFlags, "ARMOUR") end

	local self = {
		widget = Face.New(ui, faceFlags, character.seed)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}

	setFaceInfo(self.widget, character)

	setmetatable(self, {
<<<<<<< HEAD
		__index = UI.InfoFace,
=======
		__index = InfoFace,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		class = "UI.InfoFace",
	})

	return self
<<<<<<< HEAD
end,

UpdateInfo = function (self, character)
	testCharacter(character)
	setFaceInfo(self.widget, character)
end,

}
=======
end

function InfoFace.UpdateInfo (self, character)
	testCharacter(character)
	setFaceInfo(self.widget, character)
end

return InfoFace
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
