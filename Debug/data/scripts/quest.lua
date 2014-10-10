ship = nil
Done = false
startDone = false

function Start()	
	Save = {"bDone"}
end

function Update()
	if not startDone then
		ship = getEntity(1)
		
		if ship == nil then
			ship = newEntity()
			ship:add("Drawable")
			ship:add("Movable")
			ship:add("Physical")
			ship:add("Name")
			
			setTexture(ship:getDrawable(), "./data/textures/ship.png")
			setMoveVelocity(ship:getMovable(), 100)
			setPosition(ship:getPhysical(), 400, 20)
			setSize(ship:getPhysical(), getSpriteSize(ship:getDrawable()))
			setName(ship:getName(), "Lua Entity")
		end
		
		startDone = true
	end
	
	if not Done and isAround(getEntity(0):getPhysical(), 400, 20, 20) then
		print("Congratulations!")
		Done = true
	end
end