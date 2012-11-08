local ui = Engine.ui

uilib = { -- Suggestions for a better namespace gladly accepted

	FaceWidget = function (character)
		if not (character and (type(character)=='table') and (getmetatable(character).class == 'Character'))
		then
			error ('FaceWidget: Character object expected.')
		end
		local faceFlags = {
			character.female and "FEMALE" or "MALE",
			character.armor and "ARMOUR",
		}
		return UI.Game.Face.New(ui, faceFlags, character.seed)
		-- face + name gradient
		:SetInnerWidget(
			ui:Align("BOTTOM_LEFT"):SetInnerWidget(
				ui:Expand("HORIZONTAL"):SetInnerWidget(
					ui:Gradient({r=0.1,g=0.1,b=0.1,a=0.8}, {r=0.0,g=0.0,b=0.1,a=0.0}, "HORIZONTAL"):SetInnerWidget(
						ui:Margin(20):SetInnerWidget(ui:VBox():PackEnd({
							ui:Label(character.name):SetFont("HEADING_NORMAL"),
							ui:Label(character.title or ''):SetFont("HEADING_SMALL"),
						}))
					)
				)
			)
		)
	end,

	UpdateFaceText = function (widget,character)
		if not (widget and (type(widget) == 'userdata'))
		then
			error('UpdateFaceText: Widget expected.')
		end
		if not (character and (type(character)=='table') and (getmetatable(character).class == 'Character'))
		then
			error ('UpdateFaceText: Character object expected.')
		end
		widget:SetInnerWidget(
			ui:Align("BOTTOM_LEFT"):SetInnerWidget(
				ui:Expand("HORIZONTAL"):SetInnerWidget(
					ui:Gradient({r=0.1,g=0.1,b=0.1,a=0.8}, {r=0.0,g=0.0,b=0.1,a=0.0}, "HORIZONTAL"):SetInnerWidget(
						ui:Margin(20):SetInnerWidget(ui:VBox():PackEnd({
							ui:Label(character.name):SetFont("HEADING_NORMAL"),
							ui:Label(character.title):SetFont("HEADING_SMALL"),
						}))
					)
				)
			)
		)
	end,

}
