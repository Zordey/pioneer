
define_model('lff', {
	info = {
			materials={'medsteel'},
			bounding_radius = 2,
			},
			
	static = function(lod)
		set_material('medsteel', .4,.4,.4,1,.65,.68,.72,30)
		use_material('medsteel')
		texture('fighter.png')
		load_obj('fighter_leftfrontflap.obj')
	end
})

define_model('rff', {
	info = {
			materials={'medsteel'},
			bounding_radius = 2,
			},
			
	static = function(lod)
		set_material('medsteel', .4,.4,.4,1,.65,.68,.72,30)
		use_material('medsteel')
		texture('fighter.png')
		load_obj('fighter_rightfrontflap.obj')
	end
})

define_model('lrf', {
	info = {
			materials={'medsteel'},
			bounding_radius = 2,
			},
			
	static = function(lod)
		set_material('medsteel', .4,.4,.4,1,.65,.68,.72,30)
		use_material('medsteel')
		texture('fighter.png')
		load_obj('fighter_leftrearflap.obj')
	end
})

define_model('rrf', {
	info = {
			materials={'medsteel'},
			bounding_radius = 2,
			},
			
	static = function(lod)
		set_material('medsteel', .4,.4,.4,1,.65,.68,.72,30)
		use_material('medsteel')
		texture('fighter.png')
		load_obj('fighter_rightrearflap.obj')
	end
})

define_model('tfrgear', {
	info = {
			materials={'medsteel'},
			bounding_radius = 2,
			},
			
	static = function(lod)
		set_material('medsteel', .4,.4,.4,1,.65,.68,.72,30)
		use_material('medsteel')
		
	end,
	
	dynamic = function(lod)
		local rot = get_arg(0)
		--texture('fighter.png')
		call_model('rff', v(.5*rot,0,0),v(1,0,0),v(0,1,0),1)
		call_model('lff', v(-.5*rot,0,0), v(1,0,0), v(0,1,0), 1)
		call_model('headlight',v(0,-.6-rot,-1.25-rot), v(1,0,0), v(0,1-rot,-rot), 1.5)
		call_model('nosewheel', v(0,-.5,-2.2), v(1,0,0), v(0,-rot,1-rot), .3)
		call_model('rrf', v(rot*2.5,rot*1,-rot*.35),v(1-rot,-rot,0),v(rot,1-rot,0),1)
		call_model('lrf', v(-rot*2.5,rot*1,-rot*.35),v(1-rot,rot,0),v(-rot,1-rot,0),1)
		call_model('mainwheel', v(2,-.7,3.8), v(1,0,0), v(0,-rot,1-rot), .3)
		call_model('mainwheel', v(-2,-.7,3.8), v(1,0,0), v(0,-rot,1-rot), .3)
	end
})




define_model('fi', {     
   	info = {
			scale = 1.1,
			lod_pixels={.1,40,80,0},
			bounding_radius = 18,
			materials={'steel', 'darksteel', 'medsteel', 'glow', 'rand1', 'rand2', 'glass', 'inside','text1', 'text2'},
			tags = { 'ship' },
                 ship_defs = {
                	{
                	'Talon Military Interceptor',
                    { 3*10^6,-9*10^6,4*10^6,-1*10^6,-2*10^6,2*10^6 },
                    8*10^6,
                    {
                    { v(0,-2,-46), v(0,0,-1) },
                    { v(0,0,0), v(0,0,1) },
                    },
                    { 10, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    10, 4, 880, --8800000, high price for size because this is a very fast military ship, the thrust is distributed between the thrust pods, for hover there are 3 pods so powerful thrust for down thrust there is 1 pod so weaker thrust. Side thrust has 2 pods each so medium thrust.  Its comparable to an eagle but sacrifice carry weight for thrust.
                    8
                    }
                  }
        	},

   	static = function(lod)

   	if lod > 1 then
		set_material('steel', .7,.7,.7,1,.95,.98,1,60)
		set_material('glass', .8,.8,.8,.9,1,1,1,100)
		set_material('medsteel', .4,.4,.4,1,.65,.68,.72,60)
		set_material('darksteel', .1,.1,.12,1,.65,.68,.72,60)
		set_material('inside', .7,.7,.7,1,.95,.98,1,0)
		set_material('text1', .1,.5,.4,1,.2,.6,.5,5)
		set_material('text2', .5,.1,.1,1,.6,.2,.2,5)

		if lod > 3 then
			texture('fighter.png')
			use_material('rand1')
			load_obj('fighter_top.obj')
			--use_material('medsteel')
			--load_obj('fighter_bot.obj')
			
			use_material('inside')
			texture('fighter_inside.png')
			load_obj('fighter_inside.obj')
			texture(nil)
			call_model('pilot2', v(0,-.05,-3.95), v(1,0,0), v(0,.75,.25), .22)	
				
			use_material('rand1')
			texture('fighter2.png')
			load_obj('fighter_sides.obj')
			use_material('glow')
			load_obj('fighter_glow.obj')
				
			use_material('darksteel')
			texture(nil)
			load_obj('fighter_rest.obj')
			load_obj('fighter_thrusters.obj')
			load_obj('fighter_retros.obj')
			
			texture('fighter.png')
			use_material('glass')	
			load_obj('fighter_cockpit.obj')
		elseif lod > 2 then
			texture('fightersml.png')
			use_material('rand1')
			load_obj('fighter_top.obj')
			use_material('medsteel')
			load_obj('fighter_bot.obj')
			
			use_material('inside')
			texture('fighter_inside.png')
			load_obj('fighter_inside.obj')	
				
			use_material('rand1')
			texture('fighter2sml.png')
			load_obj('fighter_sides.obj')
			use_material('glow')
			load_obj('fighter_glow.obj')
				
			use_material('darksteel')
			texture(nil)
			load_obj('fighter_restLQ.obj')
			
			texture('fightersml.png')
			use_material('glass')	
			load_obj('fighter_cockpit.obj')
		else
			texture('fightervsml.png')
			use_material('rand1')
			load_obj('fighter_topLQ.obj')
			use_material('medsteel')
			load_obj('fighter_botLQ.obj')
			
				
			use_material('rand1')
			texture('fighter2vsml.png')
			load_obj('fighter_sidesLQ.obj')
			use_material('glow')
			load_obj('fighter_glowLQ.obj')
				
			use_material('darksteel')
			texture(nil)
			load_obj('fighter_restLQ.obj')
			
			texture('fightervsml.png')
			use_material('inside')	
			load_obj('fighter_cockpitLQ.obj')
		end
		
		

	else
		load_obj('fighter_collision.obj')
	end

		
		use_material('steel')
		local vMainThruster1 = v(1.5,-0.7,6.5)
		local vMainThruster2 = v(-1.5,-0.7,6.5)
		local vRetroThruster1 = v(0.688,-0.88,-5.574)
		local vRetroThruster2 = v(-0.688,-0.88,-5.574)
		local vHoverThruster1 = v(0,-1.091,-3)
		local vHoverThruster2 = v(0.89,-1.84,4.38)
		local vHoverThruster3 = v(-0.89,-1.84,4.38)
		local vTopThruster1 = v(-0,0.516,0.877)
		local vLeftThruster1 = v(-2.693,-0.716,5.654)
		local vLeftThruster2 = v(-1.463,-0.36,-3.55)
		local vRightThruster1 = v(2.693,-0.716,5.654)
		local vRightThruster2 = v(1.463,-0.36,-3.55)
		
		thruster(vMainThruster1, v(0,0,1), 8, true)
		thruster(vMainThruster2, v(0,0,1), 8, true)
		thruster(vRetroThruster1, v(0,0,-1), 2, true)
		thruster(vRetroThruster2, v(0,0,-1), 2, true)
		thruster(vHoverThruster1, v(0,-1,0), 3)
		thruster(vHoverThruster2, v(0,-1,0), 3)
		thruster(vHoverThruster3, v(0,-1,0), 3)
		thruster(vTopThruster1, v(0,1,0), 3)
		thruster(vLeftThruster1, v(-0.9,0.1,0), 2)
		thruster(vLeftThruster2, v(-0.9,0,-0.1), 2)
		thruster(vRightThruster1, v(0.9,0.1,0), 2)
		thruster(vRightThruster2, v(0.9,0,-0.1), 2)
		
		


	end,
 
 
	dynamic = function(lod)
	
		if lod > 3 then
	
				
			if get_arg(0) > 0 then	
				local rot = get_arg(0)	
				texture('models/ships/talon/fighter.png')
				use_material('medsteel')
				load_obj('models/ships/talon/fighter_bot2.obj')
				load_obj('models/ships/talon/fighter_frontgearbox.obj')
				load_obj('models/ships/talon/fighter_backgearbox.obj')
				call_model('tfrgear', v(0,0,0), v(1,0,0), v(0,1,0), 1)
				texture(nil)
				call_model('posl_green', v(6.128,-1.928,4.85), v(0,0,1), v(1,0,0),1)
				call_model('posl_red', v(-6.128,-1.928,4.85), v(0,0,1), v(-1,0,0),1)
				call_model('posl_green', v(3.169,2.009,5.147), v(1,0,0), v(0,1,0),.3)
				call_model('posl_red', v(-3.169,2.009,5.147), v(1,0,0), v(0,1,0),.3)
			else
				texture('models/ships/talon/fighter.png')
				use_material('medsteel')
				load_obj('models/ships/talon/fighter_bot.obj')
				texture(nil)
			end
			
			if get_arg(8) > 0 then
				call_model('scanner', v(-0,0.516,4), v(1,0,0), v(0,1,0), 0.33)
				call_model('antenna_1', v(0.5,-0.36,-6.524), v(1,0,0), v(0,1,0), 0.3)
			end
			
			if get_arg(7) > 0 then
				call_model('ecm_1', v(-1.1,-0.32,-5), v(0,1,0), v(-1,0,0), 0.25)
			end
			
			if get_arg(10) > 0 then
			use_material('darksteel')
			texture(nil)
			load_obj('models/ships/talon/fighter_LGun.obj')
			load_obj('models/ships/talon/fighter_RGun.obj')
			end
			
			if get_arg(11) > 0 then
			use_material('darksteel')
			texture(nil)
			load_obj('models/ships/talon/fighter_LGun.obj')
			load_obj('models/ships/talon/fighter_RGun.obj')
			end
			
			if get_arg(12) > 0 then
			call_model('missile_1', v(3,-1.3,4.1), v(1,0,0), v(0,.95,.05), 1)
			end
			
			if get_arg(13) > 0 then
			call_model('missile_1', v(-3,-1.3,4.1), v(1,0,0), v(0,.95,.05), 1)
			end
			
			if get_arg(14) > 0 then
			call_model('missile_1', v(3.5,-1.35,4.35), v(1,0,0), v(0,.95,.05), 1)
			end
			
			if get_arg(15) > 0 then
			call_model('missile_1', v(-3.5,-1.35,4.35), v(1,0,0), v(0,.95,.05), 1)
			end
			
			if get_arg(16) > 0 then
			call_model('missile_1', v(4,-1.48,4.6), v(1,0,0), v(0,.95,.05), 1)
			end
			
			if get_arg(17) > 0 then
			call_model('missile_1', v(-4,-1.48,4.6), v(1,0,0), v(0,.95,.05), 1)
			end
			
			if get_arg(6) > 0 then
			set_material('glow', lerp_materials(os.clock()*0.25,	{0, 0, 0, 1, 0, 0, 0, 0, 1.7, 2.2, 2.5 },
															{0, 0, 0, 1, 0, 0, 0, 0, .1, .2, 0.5 }))
			else

			set_material('glow', .03,.03,.03,1,.65,.68,.72,10)
			
			end
			
			local reg = get_arg_string(0)
			use_material('text1')
			--zbias(1, v(-5,0.516,0.877), v(0,0.25,1))
			--text(reg, v(-1,0.63,1.877), v(0,1,0), v(0,0,1), .5, {center=true})
			text(get_arg_string(3), v(-.8,0.64,1.877), v(0,1,0), v(0,0,1), .5, {center=true})
			--zbias(0)
			use_material('rand2')
			--zbias(1, v(5, -1.527, -18.867), v(0,.2,-1))
			text(get_arg_string(2), v(-.8,0.69,3.877), v(0,1,0), v(0,0,1), .5, {center=true})
			text('Talon:', v(.8,0.645,2.8), v(0,1,0), v(0,0,-1), .5, {center=true})
			use_material('text2')
			text(reg, v(.8,0.615,1.0), v(0,1,0), v(0,0,-1), .5, {center=true})
			--zbias(0)
			
		end
		
        set_material('rand1', get_arg_material(0))
        set_material('rand2', get_arg_material(1))
	    
															
	end
															
})

