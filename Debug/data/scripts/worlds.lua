local tileSize = {x = 0, y = 0}
local Done = false

function Update()
	local currentWorld = getCurrentWorld()
	
	tileSize.x, tileSize.y = getTileSize()
	
	local player = getPlayer()
	local phys = getPhysical(player)
	
	local x, y = getPosition(phys)
	
	--list of if statements checking for the player entering a tile that should change the active world
	if currentWorld == "testWorld" and math.floor(x / tileSize.x) == 19 and y / tileSize.y < 0.5 then
		setCurrentWorld("testWorld2", "./data/maps/maze2.tmx")
		player = getPlayer()
		phys = getPhysical(player)
		setPosition(phys, 19.5 * tileSize.x, 1.5 * tileSize.y)
	elseif currentWorld == "testWorld2" and math.floor(x / tileSize.x) == 19 and y / tileSize.y < 0.5 then
		setCurrentWorld("testWorld", "./data/maps/maze.tmx")
		player = getPlayer()
		phys = getPhysical(player)
		setPosition(phys, 19.5 * tileSize.x, 1.5 * tileSize.y)
	end
end
