<<<<<<< HEAD
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = import("Engine")

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
local normalColor = { r=0.5, g=0.5, b=0.5, a=1.0 }
local hoverColor  = { r=0.8, g=0.8, b=0.8, a=1.0 }
local activeColor = { r=1.0, g=1.0, b=1.0, a=1.0 }

local ui = Engine.ui

local _FindTabNum = function (self, id)
	for i = 1,#self.tabs do
		if self.tabs[i].id == id then
			return i
		end
	end
	return nil
end

<<<<<<< HEAD
UI.TabGroup = {

New = function ()

=======
local TabGroup = {}

function TabGroup.New ()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local self = {
		tabs   = {},
	}

	self.header    = ui:HBox(10)
	self.title     = ui:Label(""):SetFont("HEADING_XLARGE")
	self.titleArea = ui:Expand("HORIZONTAL"):SetInnerWidget(ui:Align("RIGHT"):SetInnerWidget(self.title))
	self.body      = ui:Expand()
<<<<<<< HEAD
=======
	self.footer    = ui:Margin(0)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	self.widget =
		ui:VBox():PackEnd({
			ui:Margin(5):SetInnerWidget(
				ui:HBox():PackEnd(self.header)
			),
			ui:Margin(5):SetInnerWidget(
				ui:Background():SetInnerWidget(
<<<<<<< HEAD
					self.body
=======
					ui:VBox():PackEnd({
						self.body,
						self.footer
					})
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
				)
			)
		})

	setmetatable(self, {
<<<<<<< HEAD
		__index = UI.TabGroup,
=======
		__index = TabGroup,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		class = "UI.TabGroup",
	})

	return self
<<<<<<< HEAD
end,

AddTab = function (self, args)
=======
end

function TabGroup.AddTab (self, args)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local id       = args.id
	local title    = args.title
	local icon     = args.icon
	local template = args.template

	local tab = {
		group    = self,
		id       = id,
		icon     = icon,
		title    = title,
		template = template,
	}

	self:RemoveTab(id)

	local num = #self.tabs+1
	self.tabs[num] = tab

	tab.iconWidget = ui:Icon(tab.icon):SetColor(normalColor)
	tab.iconWidget.onMouseOver:Connect(function () if self.current ~= num then tab.iconWidget:SetColor(hoverColor) end end)
	tab.iconWidget.onMouseOut:Connect(function () if self.current ~= num then tab.iconWidget:SetColor(normalColor) end end)
	tab.iconWidget.onClick:Connect(function () self:SwitchTo(tab.id) end)

	self.header:Remove(self.titleArea)
	self.header:PackEnd({ tab.iconWidget, self.titleArea })

	tab.Refresh = function ()
		if self.current ~= num then return end
		self:Refresh()
	end

<<<<<<< HEAD
	if not self.current then
		self:SwitchToNum(num)
	end
end,

RemoveTab = function (self, id)
=======
	tab.SetTitle = function (t, text)
		self.title:SetText(text)
	end

	if not self.current then
		self:SwitchToNum(num)
	end

	return tab
end

function TabGroup.RemoveTab (self, id)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local num = _FindTabNum(self, id)
	if not num then return end

	local tab = self.tabs[num]

	self.header:Remove(tab.iconImage)

	table.remove(self.tabs, num)

	if self.current == num then
		self:SwitchFirst()
	end
<<<<<<< HEAD
end,

SwitchToNum = function (self, num)
=======
end

function TabGroup.SwitchToNum (self, num)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local tab = self.tabs[num]

	if self.current then
		self.tabs[self.current].iconWidget:SetColor(normalColor)
	end

	tab.iconWidget:SetColor(activeColor)

	self.current = num

	self.title:SetText(tab.title)

<<<<<<< HEAD
	self.body:SetInnerWidget(tab.template(tab))
end,

SwitchTo = function (self, id)
=======
	self.body:SetInnerWidget(tab.template(tab, self))
end

function TabGroup.SwitchTo (self, id)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local num = _FindTabNum(self, id)
	if not num then return end

	self:SwitchToNum(num)
<<<<<<< HEAD
end,

SwitchFirst = function (self)
	self:SwitchToNum(1)
end,

SwitchNext = function (self)
=======
end

function TabGroup.SwitchFirst (self)
	self:SwitchToNum(1)
end

function TabGroup.SwitchNext (self)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if not self.current then
		self:SwitchFirst()
	else
		local nextNum = self.current + 1
		if nextNum > #self.tabs then nextNum = 1 end
		self:SwitchToNum(nextNum)
	end
<<<<<<< HEAD
end,

SwitchPrev = function (self)
=======
end

function TabGroup.SwitchPrev (self)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if not self.current then
		self:SwitchFirst()
	else
		local nextNum = self.current - 1
		if nextNum < 1 then nextNum = #self.tabs end
		self:SwitchToNum(nextNum)
	end
<<<<<<< HEAD
end,

Refresh = function (self)
=======
end

function TabGroup.Refresh (self)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if not self.current then
		self:SwitchFirst()
	else
		self:SwitchToNum(self.current)
	end
end

<<<<<<< HEAD
}
=======
function TabGroup.SetFooter (self, footer)
	self.footer:SetInnerWidget(footer)
end

return TabGroup
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
