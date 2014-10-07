--Play setup
function Start()
	winSizeX, winSizeY = getWindowSize()
	worldSizeX, worldSizeY = getWorldSize()
	
	Done = false
end

function Update()
	--bound entities to the world size
	for i = 0, getTotalEntities() - 1 do
		local e = getEntity(i)
		
		local p = e:getPhysical()
		local x, y = getPosition(p)
		local w, h = getSize(p)
		
		local m = e:getMovable()
		local vx, vy = getVelocity()
		
		if x < 0 then
			setPosition(p, 0, y)
		elseif x + w > worldSizeX then
			setPosition(p, worldSizeX - w, y)
		end
		
		if y < 0 then
			setPosition(p, x, 0)
		elseif y + h > worldSizeY then
			setPosition(p, x, worldSizeY - h)
		end
	end
end
