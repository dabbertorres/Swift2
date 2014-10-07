function Start()
	Done = false
	
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
		setPosition(ship:getPhysical(), 400, 20)
		setSize(ship:getPhysical(), getSpriteSize(ship:getDrawable()))
		setName(ship:getName(), "Lua Entity")
	end
	
	Save = {}
end

function Update()
	local ship = getEntity(1)
	
	shipPosX, shipPosY = getPosition(ship:getPhysical())
	
	if isAround(getEntity(0):getPhysical(), shipPosX, shipPosY, 20) then
		print("Congratulations!")
		Done = true
	end
	
	Save = {shipPosX, shipPosY}
end