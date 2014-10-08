ShipPosX = 400
ShipPosY = 20
Done = false

function Start()
	ship = newEntity()
	
	if ship == nil then
		log("[WARNING]: ship is nil\n")
	else
		ship:add("Drawable")
		ship:add("Movable")
		ship:add("Physical")
		ship:add("Name")
		
		setTexture(ship:getDrawable(), "./data/textures/ship.png")
		setMoveVelocity(ship:getMovable(), 100)
		setPosition(ship:getPhysical(), ShipPosX, ShipPosY)
		setSize(ship:getPhysical(), getSpriteSize(ship:getDrawable()))
		setName(ship:getName(), "Lua Entity")
	end
	
	Save = {"nshipPosX", "nshipPosY", "bDone"}
end

function Update()
	shipPosX, shipPosY = getPosition(ship:getPhysical())
	
	local around = isAround(getEntity(0):getPhysical(), shipPosX, shipPosY, 20)
	
	if not Done and around then
		print("Congratulations!")
		Done = true
	end
end