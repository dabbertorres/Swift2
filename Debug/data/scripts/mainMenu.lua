--MainMenu setup
function Start()
	winW, winH = getWindowSize()
	
	buttonWidth = 100
	buttonHeight = 50
	
	setFont("./data/fonts/segoeui.ttf")
	
	title = addLabel(winW / 2 - 75, winH / 8, "Swift2")
	title:setTextSize(50)
	
	start = addButton(winW / 2 - buttonWidth / 2, winH / 2 - buttonHeight, buttonWidth, buttonHeight, "./data/textures/button.png", startFunc)
	start:setText("Start")
	
	settings = addButton(winW / 2 - buttonWidth / 2, winH / 2 + 10, buttonWidth, buttonHeight, "./data/textures/button.png", settingsFunc)
	settings:setText("Settings")
	
	exit = addButton(winW / 2 - buttonWidth / 2, winH / 2 + 20 + buttonHeight, buttonWidth, buttonHeight, "./data/textures/button.png", exitFunc)
	exit:setText("Exit")
	
	Done = true
end

function startFunc()
	setStateReturn(states.Play)
end

function settingsFunc()
	setStateReturn(states.Settings)
end

function exitFunc()
	setStateReturn(states.Exit)
end