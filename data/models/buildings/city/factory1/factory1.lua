--[[
--updated 05/08/2010
define_model('rotor', {
	info = {	
			lod_pixels = {20, 40, 100, 0},
			scale=1,
			bounding_radius = 3,
			materials = {'alu'},
			},
	static = function(lod)
    	set_material('alu', .5,.52,.55,1,.45,.5,.55,50)
    	use_material('alu')
		circle(4*lod, v(0,0,0), v(0,1,0), v(0,0,1),.3)
		xref_tri(v(0,0,0), v(1.3,0,.25), v(1.3,0,-.25)) 
		tri(v(0,0,0), v(-.25,0,1.3), v(.25,0,1.3))
		tri(v(0,0,0), v(.25,0,-1.3), v(-.25,0,-1.3))
		xref_tri(v(0,0,0), v(-1.1,0,.7), v(-.7,0,1.1))
		xref_tri(v(0,0,0), v(1.1,0,-.7), v(.7,0,-1.1))
	end
})

define_model('factory1', {
	info = {
			lod_pixels = {20, 40, 100, 0},
			scale=1.25, 
			bounding_radius = 50,
			materials = {'clay', 'concrete', 'blood', 'snow', 'coal', 'alu', 'nausea', 'sea', 
						'dandelion', 'kentucky1', 'kentucky2', 'kentucky3', 'kentucky4', 'roof'},
			tags = {'city_building', 'city_power'}
			},
	static = function(lod)
    	set_material('blood', .3,0,0,1,.1,.1,.1,10)
		set_material('snow', .7,.7,.7,1,.1,.1,.1,10)
		set_material('coal', .05,.05,.04,1,.1,.1,.1,10)
	  	set_material('sea', 0,.06,.3,1,.3,.3,.3,5)
		set_material('dandelion', .6, .55,0, 1, .3, .3, .3, 5)

		local  v0 = v(20,1,-20)
		local  v1 = v(-20,1,-20)
		local  v2 = v(20,29,-20)
		local  v3 = v(-20,29,-20)
		local  v4 = v(18,31,-18)
		local  v5 = v(-18,31,-18)
		local  v6 = v(18,31,-2)
		local  v7 = v(-18,31,-2)
		local  v8 = v(20,29,0)
		local  v9 = v(-20,29,0)
		local v10 = v(20,21,0)
		local v11 = v(-20,21,0)
		local v12 = v(20,21,20)
		local v13 = v(-20,21,20)
		local v14 = v(20,1,20)
		local v15 = v(-20,1,20)
		
		--walls
		if lod > 2 then
	  		texture('corrosion3.png', v(.5,.97,0), v(.025,0,0), v(0,-.036,0))
		end
		use_material('clay')
		quad(v0,v1,v3,v2)
		quad(v14,v12,v13,v15)
		quad(v8,v9,v11,v10)
		if lod > 2 then
		  	texture('corrosion3.png', v(0,.97,0), v(0,0,-.7), v(0,-.036,0))
		end
		xref_flat(1, v(1,0,0), {v0},{v2},{v8},{v10},{v12},{v14})

		--roof sides
	 	if lod > 2 then
			texture('concrete.png', v(0,0,0), v(.05,0,0), v(0,0,.5))
		end
	    use_material('roof')
		quad(v2,v3,v5,v4)                                
		quad(v6,v7,v9,v8)
		xref_quad(v2,v4,v6,v8)

		--roof top
		quad(v4,v5,v7,v6)
		quad(v10,v11,v13,v12)

		--chimney
		if lod > 2 then
			texture('concrete_b.png', v(0,0,0), v(.5,0,.5), v(0,.2,0))
		end
		use_material('concrete')
		xref_tapered_cylinder(4*lod, v(12,31,-10), v(12,47,-10), v(0,0,1), 2.0, 1.36)
		tapered_cylinder(4*lod, v(0,31,-10), v(0,47,-10), v(0,0,1), 2.0, 1.36)
	    xref_tube(4*lod, v(12,50,-10), v(12,51,-10), v(0,0,1), .94, 1.24)
		tube(4*lod, v(0,50,-10), v(0,51,-10), v(0,0,1), .94, 1.24)

        --entry
		extrusion(v(-17.6,0,0), v(-13.6,0,0), v(0,1,0), 1, v(-22,1,0), v(-20,1,0), v(-20,3.5,0), v(-22,3.5,0))
		extrusion(v(-26,1,0), v(-20,1,0), v(0,1,0), 1, v(-20,0,0), v(0,0,0), v(10,0,0), v(-20,4,0))

		--chimney
		texture(nil)
		use_material('blood')
		xref_tapered_cylinder(4*lod, v(12,47,-10), v(12,48,-10), v(0,0,1), 1.36, 1.32)
		tapered_cylinder(4*lod, v(0,47,-10), v(0,48,-10), v(0,0,1), 1.36, 1.32)
		xref_tapered_cylinder(4*lod, v(12,49,-10), v(12,50,-10), v(0,0,1), 1.28, 1.24)
		tapered_cylinder(4*lod, v(0,49,-10), v(0,50,-10), v(0,0,1), 1.28, 1.24)

		use_material('snow')
		xref_tapered_cylinder(4*lod, v(12,48,-10), v(12,49,-10), v(0,0,1), 1.32, 1.28)
		tapered_cylinder(4*lod, v(0,48,-10), v(0,49,-10), v(0,0,1), 1.32, 1.28)

    	use_material('coal')
		xref_circle(4*lod, v(12,50.01,-10), v(0,1,0), v(0,0,1), 1.19)
		circle(4*lod, v(0,50.01,-10), v(0,1,0), v(0,0,1), 1.19)
		xref_circle(4*lod, v(11,22.01,12), v(0,1,0), v(0,0,1), 1.5)
		quad(v(30,1,-23), v(-26,1,-23), v(-26,1,30), v(30,1,30))
		--entry
		quad(v(-25.5,1,20.01), v(-20.5,1,20.01), v(-20.5,4,20.01), v(-25.5,4,20.01))

		--vent
		use_material('alu')
    	if lod > 2 then
			texture('alu_tiled.png', v(0,0,0), v(.1,0,0), v(0,0,1))
		end
		extrusion(v(0,0,0), v(0,0,10), v(0,1,0), 1, v(-12,21,0), v(-10,21,0), v(-10,22,0), v(-12,22,0))
		extrusion(v(0,0,0), v(0,0,10), v(0,1,0), 1, v(10,21,0), v(12,21,0), v(12,22,0), v(10,22,0))
		extrusion(v(0,0,10), v(0,0,14), v(0,1,0), 1, v(-13,21,0), v(-9,21,0), v(-9,22,0), v(-13,22,0))
		extrusion(v(0,0,10), v(0,0,14), v(0,1,0), 1, v(9,21,0), v(13,21,0), v(13,22,0), v(9,22,0))
		
		--tubes
		if lod > 2 then
			texture('alu_tiled.png', v(0,0,0), v(-.15,0,0), v(0,-.1,0))
		end
		xref_ring(4*lod, v(12,1,-21), v(12,21,-21), v(0,0,1), 1)
		xref_ring(4*lod, v(12,21,-21), v(12,23,-19), v(0,0,1), 1)
		ring(4*lod, v(0,1,-21), v(0,21,-21), v(0,0,1), 1)
		ring(4*lod, v(0,21,-21), v(0,23,-19), v(0,0,1), 1)
    	if lod > 2 then
			texture('alu_xtiled.png', v(.3,0,0), v(.1,0,0), v(0,0,.5))
		end
		ring(4*lod, v(25,14,14), v(23,16,14), v(0,1,0), 1)
		ring(4*lod, v(20,16,14), v(23,16,14), v(0,0,1), 1)
		ring(4*lod, v(25,14,4), v(23,16,4), v(0,1,0), 1)
		ring(4*lod, v(20,16,4), v(23,16,4), v(0,0,1), 1)

		--tanks
        use_material('nausea')
		if lod > 2 then
			texture('corrosion3.png', v(0,.93,0), v(-.15,0,1), v(0,-.071,0))
		end
		ring(6*lod, v(24,1,14), v(24,15,14), v(0,0,1), 4)
		ring(6*lod, v(24,1,4), v(24,15,4), v(0,0,1), 4)
		if lod > 2 then
 	       texture('corrosion3.png', v(0,.2,0), v(.1,0,0), v(0,0,1))
		end
		circle(6*lod, v(24,15,14), v(0,1,0), v(0,0,1), 4)
		circle(6*lod, v(24,15,4), v(0,1,0), v(0,0,1), 4)
		texture(nil)
	
		--sign
		use_material('sea')
		zbias(1,v(0,18.8,20.01),v(0,0,1))
		quad(v(-11,17,20.01), v(11,17,20.01), v(11,20.6,20.01), v(-11,20.6,20.01))
		zbias(1,v(0,15.5,20.01),v(0,0,1))
		text('division', v(0,15.5,20.01), v(0,0,1), v(1,0,0), 1.5, {center=true})
        use_material('dandelion')
		zbias(2,v(0,19,20.02), v(0,0,1))
		text('ACME Bolts & Nuts', v(0,19,20.02), v(0,0,1), v(1,0,0), 2, {center=true})
		zbias(0)
		--windows
 		if lod > 2 then
			texture('corrosion3.png', v(0,.97,0), v(-.1,0,1), v(0,-.036,0))
		end
    	use_material('kentucky1')
		quad(v(-17,1,22.01), v(-14,1,22.01), v(-14,3,22.01), v(-17,3,22.01))
		xref_quad(v(-7.5,1.7,20.01), v(-4.5,1.7,20.01), v(-4.5,3,20.01), v(-7.5,3,20.01))
		quad(v(16.5,1.7,20.01), v(19.5,1.7,20.01), v(19.5,3,20.01), v(16.5,3,20.01))
		xref_quad(v(-7.5,4,20.01), v(-4.5,4,20.01), v(-4.5,5.3,20.01), v(-7.5,5.3,20.01))
		xref_quad(v(-3.5,4,20.01), v(-.5,4,20.01), v(-.5,5.3,20.01), v(-3.5,5.3,20.01))
		xref_quad(v(-19.5,8.6,20.01), v(-16.5,8.6,20.01), v(-16.5,9.9,20.01), v(-19.5,9.9,20.01))
		xref_quad(v(-20.01,6.3,-13), v(-20.01,6.3,-10), v(-20.01,7.6,-10), v(-20.01,7.6,-13))
		xref_quad(v(-20.01,8.6,-9), v(-20.01,8.6,-6), v(-20.01,9.9,-6), v(-20.01,9.9,-9))
		xref_quad(v(-20.01,13.2,-9), v(-20.01,13.2,-6), v(-20.01,14.5,-6), v(-20.01,14.5,-9))
		xref_quad(v(-20.01,13.2,-13), v(-20.01,13.2,-10), v(-20.01,14.5,-10), v(-20.01,14.5,-13))
		xref_quad(v(-20.01,15.5,-13), v(-20.01,15.5,-10), v(-20.01,16.8,-10), v(-20.01,16.8,-13))
		quad(v(-20.01,6.3,11), v(-20.01,6.3,14), v(-20.01,7.6,14), v(-20.01,7.6,11))
		quad(v(-20.01,6.3,3), v(-20.01,6.3,6), v(-20.01,7.6,6), v(-20.01,7.6,3))
		xref_quad(v(-7.5,24.7,0.01), v(-4.5,24.7,0.01), v(-4.5,26,0.01), v(-7.5,26,0.01))
		xref_quad(v(-20.01,24.7,-9), v(-20.01,24.7,-6), v(-20.01,26,-6), v(-20.01,26,-9))
		quad(v(-20.01,6.3,-1), v(-20.01,6.3,2), v(-20.01,7.6,2), v(-20.01,7.6,-1))
	
		use_material('kentucky2')
		xref_quad(v(-11.5,1.7,20.01), v(-8.5,1.7,20.01), v(-8.5,3,20.01), v(-11.5,3,20.01))
		xref_quad(v(-3.5,1.7,20.01), v(-.5,1.7,20.01), v(-.5,3,20.01), v(-3.5,3,20.01))
		quad(v(12.5,1.7,20.01), v(15.5,1.7,20.01), v(15.5,3,20.01), v(12.5,3,20.01))
		xref_quad(v(-19.5,6.3,20.01), v(-16.5,6.3,20.01), v(-16.5,7.6,20.01), v(-19.5,7.6,20.01))
		xref_quad(v(-11.5,8.6,20.01), v(-8.5,8.6,20.01), v(-8.5,9.9,20.01), v(-11.5,9.9,20.01))
		xref_quad(v(-20.01,1.7,-13), v(-20.01,1.7,-10), v(-20.01,3,-10), v(-20.01,3,-13))
		xref_quad(v(-20.01,10.9,-13), v(-20.01,10.9,-10), v(-20.01,12.2,-10), v(-20.01,12.2,-13))
		xref_quad(v(-20.01,17.8,-9), v(-20.01,17.8,-6), v(-20.01,19.1,-6), v(-20.01,19.1,-9))
		xref_quad(v(-20.01,24.7,-13), v(-20.01,24.7,-10), v(-20.01,26,-10), v(-20.01,26,-13))
		quad(v(-20.01,8.6,3), v(-20.01,8.6,6), v(-20.01,9.9,6), v(-20.01,9.9,3))
		quad(v(-20.01,8.6,11), v(-20.01,8.6,14), v(-20.01,9.9,14), v(-20.01,9.9,11))
		quad(v(-0.6,21,.01), v(0.6,21,.01), v(0.6,23,.01), v(-0.6,23,.01))
		xref_quad(v(-11.5,24.7,0.01), v(-8.5,24.7,0.01), v(-8.5,26,0.01), v(-11.5,26,0.01))
		xref_quad(v(-20.01,6.3,-9), v(-20.01,6.3,-6), v(-20.01,7.6,-6), v(-20.01,7.6,-9))
		xref_quad(v(-7.5,8.6,20.01), v(-4.5,8.6,20.01), v(-4.5,9.9,20.01), v(-7.5,9.9,20.01))
	
		use_material('kentucky3')
		xref_quad(v(-19.5,4,20.01), v(-16.5,4,20.01), v(-16.5,5.3,20.01), v(-19.5,5.3,20.01))
		xref_quad(v(-11.5,4,20.01), v(-8.5,4,20.01), v(-8.5,5.3,20.01), v(-11.5,5.3,20.01))
		xref_quad(v(-3.5,8.6,20.01), v(-.5,8.6,20.01), v(-.5,9.9,20.01), v(-3.5,9.9,20.01))
		xref_quad(v(-20.01,8.6,-13), v(-20.01,8.6,-10), v(-20.01,9.9,-10), v(-20.01,9.9,-13))
		xref_quad(v(-20.01,10.9,-9), v(-20.01,10.9,-6), v(-20.01,12.2,-6), v(-20.01,12.2,-9))
		xref_quad(v(-20.01,20.1,-9), v(-20.01,20.1,-6), v(-20.01,21.4,-6), v(-20.01,21.4,-9))
		xref_quad(v(-20.01,22.4,-13), v(-20.01,22.4,-10), v(-20.01,23.7,-10), v(-20.01,23.7,-13))
		quad(v(-20.01,6.3,-5), v(-20.01,6.3,-2), v(-20.01,7.6,-2), v(-20.01,7.6,-5))
		quad(v(-20.01,6.3,7), v(-20.01,6.3,10), v(-20.01,7.6,10), v(-20.01,7.6,7))
		quad(v(-20.01,8.6,15), v(-20.01,8.6,18), v(-20.01,9.9,18), v(-20.01,9.9,15))
		xref_quad(v(-15.5,24.7,0.01), v(-12.5,24.7,0.01), v(-12.5,26,0.01), v(-15.5,26,0.01))
	    xref_quad(v(-20.01,20.1,-13), v(-20.01,20.1,-10), v(-20.01,21.4,-10), v(-20.01,21.4,-13))
	    xref_quad(v(-20.01,1.7,-9), v(-20.01,1.7,-6), v(-20.01,3,-6), v(-20.01,3,-9))
	    xref_quad(v(-7.5,6.3,20.01), v(-4.5,6.3,20.01), v(-4.5,7.6,20.01), v(-7.5,7.6,20.01))
	    quad(v(-20.01,8.6,-5), v(-20.01,8.6,-2), v(-20.01,9.9,-2), v(-20.01,9.9,-5))
	
	    use_material('kentucky4')
	    xref_quad(v(-7.5,1.7,20.01), v(-4.5,1.7,20.01), v(-4.5,3,20.01), v(-7.5,3,20.01))
	    xref_quad(v(-15.5,6.3,20.01), v(-12.5,6.3,20.01), v(-12.5,7.6,20.01), v(-15.5,7.6,20.01))
		xref_quad(v(-11.5,6.3,20.01), v(-8.5,6.3,20.01), v(-8.5,7.6,20.01), v(-11.5,7.6,20.01))
	    xref_quad(v(-3.5,6.3,20.01), v(-.5,6.3,20.01), v(-.5,7.6,20.01), v(-3.5,7.6,20.01))
	    xref_quad(v(-15.5,8.6,20.01), v(-12.5,8.6,20.01), v(-12.5,9.9,20.01), v(-15.5,9.9,20.01))
	    xref_quad(v(-20.01,4,-9), v(-20.01,4,-6), v(-20.01,5.3,-6), v(-20.01,5.3,-9))
		xref_quad(v(-20.01,4,-13), v(-20.01,4,-10), v(-20.01,5.3,-10), v(-20.01,5.3,-13))
	    xref_quad(v(-20.01,15.5,-9), v(-20.01,15.5,-6), v(-20.01,16.8,-6), v(-20.01,16.8,-9))
	    xref_quad(v(-20.01,17.8,-13), v(-20.01,17.8,-10), v(-20.01,19.1,-10), v(-20.01,19.1,-13))
	    xref_quad(v(-20.01,22.4,-9), v(-20.01,22.4,-6), v(-20.01,23.7,-6), v(-20.01,23.7,-9))
	    xref_quad(v(-15.5,4,20.01), v(-12.5,4,20.01), v(-12.5,5.3,20.01), v(-15.5,5.3,20.01))
	    quad(v(-20.01,8.6,-1), v(-20.01,8.6,2), v(-20.01,9.9,2), v(-20.01,9.9,-1))
	    quad(v(-20.01,8.6,7), v(-20.01,8.6,10), v(-20.01,9.9,10), v(-20.01,9.9,7))
	    quad(v(-20.01,6.3,15), v(-20.01,6.3,18), v(-20.01,7.6,18), v(-20.01,7.6,15))
	    xref_quad(v(-3.5,24.7,0.01), v(-.5,24.7,0.01), v(-.5,26,0.01), v(-3.5,26,0.01))
	end,

dynamic = function(lod)
    if lod > 2 then
        set_material('clay', .75,.7,.4,1,.3,.3,.3,5)
        set_material('concrete',.6,.6,.5,1,.3,.3,.3,5)
        set_material('roof', .15,.155,.1,1,.3,.3,.3,5)
        set_material('alu', .62,.67,.7,1,.65,.7,.8,30)
        set_material('nausea', .45, .6, .35, 1, .3, .3, .3, 5)
        set_material('kentucky1', .2, .25, .3, 1, .95, 1, 1.2, 100,.4,.45,.5)
        set_material('kentucky2', .2, .25, .3, 1, .95, 1, 1.2, 100,.4,.45,.5)
        set_material('kentucky3', .2, .25, .3, 1, .95, 1, 1.2, 100,.4,.45,.5)
        set_material('kentucky4', .2, .25, .3, 1, .95, 1, 1.2, 100,.4,.45,.5) 
	else
        set_material('clay', .56,.48,.18,1,.3,.3,.3,5)
        set_material('concrete',.5,.5,.4,1,.3,.3,.3,5)
        set_material('roof', .02,.023,0,1,.3,.3,.3,5)
        set_material('alu', .5,.52,.55,1,.45,.5,.55,50)
        set_material('nausea', .28, .35, .15, 1, .3, .3, .3, 5)
        set_material('kentucky1', .07, .09, .1, 1, .7, .72, .75, 100,.3,.35,.4)
        set_material('kentucky2', .07, .09, .1, 1, .7, .72, .75, 100,.3,.35,.4)
        set_material('kentucky3', .07, .09, .1, 1, .7, .72, .75, 100,.3,.35,.4)
        set_material('kentucky4', .07, .09, .1, 1, .7, .72, .75, 100,.3,.35,.4) 
    end

    if lod > 2 then
		factor = 1.5*math.pi*get_time('seconds')
		call_model('rotor', v(11,22.02,12), v(math.cos(factor),0,math.sin(factor)), v(0,1,0),1)
		call_model('rotor', v(-11,22.02,12), v(math.cos(factor),0,math.sin(factor)), v(0,1,0),1)
	end
	local lightphase = math.fmod((get_time('seconds')*0.5), 1)
		if lightphase < .5 then
			billboard('smoke.png', 2, v(1,0,0), { v(13.5,50.5,-10), v(10.5,50.5,-10), v(-13.5,50.5,-10), v(-10.5,50.5,-10), v(1.5,50.5,-10), v(-1.5,50.5,-10) })
		else
			billboard('smoke.png', 2, v(1,0,0), { v(12,50.5,-11.5), v(12,50.5,-8.5), v(-12,50.5,-11.5), v(-12,50.5,-8.5), v(0,50.5,-11.5), v(0,50.5,-8.5) })
        end

	local switch = math.fmod((get_time('hours')*0.2),1)
	if switch < .26 then
		if lod > 2 then
	    	set_material('kentucky1', .2, .25, .3, 1, .95, 1, 1.2, 100)
       	else
       	    set_material('kentucky1', .07, .09, .1, 1, .7, .72, .75, 100) 
       	end
   	else
		if switch < .51 then
	    	if lod > 2 then
	    		set_material('kentucky2', .2, .25, .3, 1, .95, 1, 1.2, 100) 
       		else
       	    	 set_material('kentucky2', .07, .09, .1, 1, .7, .72, .75, 100) 
       		end
	    else
			if switch < .76 then
		        if lod > 2 then
	    			set_material('kentucky3', .2, .25, .3, 1, .95, 1, 1.2, 100) 
       			else
       	    		set_material('kentucky3', .07, .09, .1, 1, .7, .72, .75, 100) 
       			end
		    else
			    if switch > .75 then
			        if lod > 2 then
	    				set_material('kentucky4', .2, .25, .3, 1, .95, 1, 1.2, 100) 
       				else
       	    			set_material('kentucky4', .07, .09, .1, 1, .7, .72, .75, 100) 	
       				end
			    end
			end
		end
	end

end
})
--]]
