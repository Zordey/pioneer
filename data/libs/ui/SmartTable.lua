<<<<<<< HEAD
local ui = Engine.ui

_DefaultSort = function (self, cmp)
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = import("Engine")
local utils = import("utils")

local ui = Engine.ui

local _DefaultSort = function (self, cmp)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if not cmp then
		cmp = function (a,b) return a.data[col] <= b.data[col] end
	end
	col = self.sortCol
<<<<<<< HEAD
	self.table = stable_sort(self.table, cmp)
end

_DefaultCellWidget = function (data)
	return ui:Label(data) end

UI.SmartTable = {

New = function (rowspec)
=======
	self.table = utils.stable_sort(self.table, cmp)
end

local _DefaultCellWidget = function (data)
	return ui:Label(data) end

local SmartTable = {}

function SmartTable.New (rowspec)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local self = {}
	
	self.rowspec = rowspec
	self.headers = ui:Grid(rowspec,1)
	self.body = ui:VBox(10) 
	
	self.table = {} -- data and widgets
	self.sortCol = nil
	self.defaultSortFunction = _DefaultSort
	self.sortFunction = _DefaultSort
	self.defaultCellWidget = _DefaultCellWidget

	self.widget =
		ui:VBox(10):PackEnd({
			self.headers,
<<<<<<< HEAD
			ui:Scroller():SetInnerWidget(self.body)
		})

	setmetatable(self, {
		__index = UI.SmartTable,
=======
			ui:Expand():SetInnerWidget(ui:Scroller(self.body))
		})

	setmetatable(self, {
		__index = SmartTable,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		class = "UI.SmartTable",
	})

	return self
<<<<<<< HEAD
end,

SetHeaders = function (self, headers)
=======
end

function SmartTable.SetHeaders (self, headers)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	for i,header in ipairs(headers) do
		local label = ui:Label(header)
		label.onClick:Connect(function () self:Sort(i) end)
		self.headers:SetCell(i-1, 0, label)
	end
<<<<<<< HEAD
end,

AddRow = function (self, cells)
=======
end

function SmartTable.AddRow (self, cells)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local row = {data = {}, widgets = {}}
	for _,cell in ipairs(cells) do
		if not cell.widget then  -- if widget isn't specified use default one
			cell.widget = self.defaultCellWidget(cell.data)
		end
		table.insert(row.data, cell.data)
		table.insert(row.widgets, cell.widget)
	end
	table.insert(self.table, row)
	self:Sort(self.sortCol)
<<<<<<< HEAD
end,

Sort = function (self, col)
=======
end

function SmartTable.Sort (self, col)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if col then
		self.sortCol = col
		self:sortFunction()
	end
	self:UpdateBody()
<<<<<<< HEAD
end,

UpdateBody = function (self)
=======
end

function SmartTable.UpdateBody (self)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	self.body:Clear()
	for _,row in ipairs(self.table) do
		local rowGrid = ui:Grid(self.rowspec, 1)
		rowGrid:SetRow(0, row.widgets)
		self.body:PackEnd(rowGrid)
	end
<<<<<<< HEAD
end,

Clear = function (self)
	self.table = {}
	self.body:Clear()
end,

SetSortFunction = function (self, f)
	self.sortFunction = f
end,
}
=======
end

function SmartTable.Clear (self)
	self.table = {}
	self.body:Clear()
end

function SmartTable.SetSortFunction (self, f)
	self.sortFunction = f
end

return SmartTable
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
