<<<<<<< HEAD
local ui = Engine.ui

UI.SmallLabeledButton = {

New = function (text)
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = import("Engine")

local ui = Engine.ui

local SmallLabeledButton = {}

function SmallLabeledButton.New (text)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local self = {
		button = ui:SmallButton(),
		label  = ui:Label(text),
	}
	self.widget = ui:HBox(10):PackEnd({ self.button, self.label })

	setmetatable(self, {
<<<<<<< HEAD
		__index = UI.SmallLabeledButton,
=======
		__index = SmallLabeledButton,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		class = "UI.SmallLabeledButton",
	})

	return self
<<<<<<< HEAD
end,

}
=======
end

return SmallLabeledButton
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
