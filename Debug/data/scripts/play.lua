--Play setup
function Start()
	winSizeX, winSizeY = getWindowSize()
	
	Done = false
	
	local e = newEntity()
	
	if e == nil then
		log("[WARNING]: e is nil")
	else
		e:add("Drawable")
		e:add("Movable")
		e:add("Physical")
		e:add("Name")
		
		setTexture(e:getDrawable(), "./data/textures/ship.png")
		setMoveVelocity(e:getMovable(), 100)
		setPosition(e:getPhysical(), 400, 20)
		setSize(e:getPhysical(), getSpriteSize(e:getDrawable()))
		setName(e:getName(), "Lua Entity")
	end
end

function Update()
	for i = 0, getTotalEntities() - 1 do
		local e = getEntity(i)
		local p = e:getPhysical()
		local x, y = getPosition(p)
		local w, h = getSize(p)
		
		if x < 0 then
			setPosition(p, 0, y)
		end
		if x + w > winSizeX then
			setPosition(p, winSizeX - w, y)
		end
		
		if y < 0 then
			setPosition(p, x, 0)
		end
		if y + h > winSizeY then
			setPosition(p, x, winSizeY - h)
		end
	end
end