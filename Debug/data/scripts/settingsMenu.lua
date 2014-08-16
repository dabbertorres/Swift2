--Settings Menu setup
function Start()
	Done = false
	winW, winH = getWindowSize()
	
	buttonWidth = 100
	buttonHeight = 50
	labelSize = 35
	
	setFont("./data/fonts/segoeui.ttf")
	
	mainMenuReturnStr = "Main Menu"
	mainMenu = addButton(winW - buttonWidth - 10, winH - buttonHeight - 10, buttonWidth, buttonHeight, "./data/textures/button.png", mainMenuReturn)
	mainMenu:setText("Main Menu")
	
	testTextBox = addTextBox(10, 200, 100, 20, 0, 0, 0, 128, 128, 128)
	
	vsyncLabel = addLabel(10, 10, "Vsync:")
	vsyncLabel:setTextSize(labelSize)
	
	local found, value = getSettingBool("vsync")
	vsyncToggle = addToggle(250, 10, buttonHeight, buttonHeight, "./data/textures/toggleOff.png", "./data/textures/toggleOn.png", value)
	
	fullscreenLabel = addLabel(10, 75, "Fullscreen:")
	fullscreenLabel:setTextSize(labelSize)
	
	local found, value = getSettingBool("fullscreen")
	fullscreenToggle = addToggle(250, 75, buttonHeight, buttonHeight, "./data/textures/toggleOff.png", "./data/textures/toggleOn.png", value)
	
	
end

function Update()
	changeSetting("vsync", vsyncToggle:getState())
	
	changeSetting("fullscreen", fullscreenToggle:getState())
end

function mainMenuReturn()
	setStateReturn(states.MainMenu)
end

function changeSetting(setting, new)
	local found, value = getSettingBool(setting)
	
	if found then
		if value ~= new then
			setSettingBool(setting, new)
		end
	end
end

function testFunc()
	
end