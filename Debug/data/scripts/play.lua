--Play setup
function Start()
	e = newEntity()
	
	e:add("Drawable")
	e:add("Movable")
	e:add("Physical")
	
	if e:has("Drawable") then
		print("e has Drawable")
	end
	
	if e:has("Movable") then
		print("e has Movable")
	end
	
	if e:has("Physical") then
		print("e has Physical")
	end
	
	Done = false
end

function Update()

end