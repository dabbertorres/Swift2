function Start()
	Done = false
	winW, winH = getWindowSize()
	
	buttonWidth = 100
	buttonHeight = 50
	
	setFont("./data/fonts/DroidSansMono.ttf")
	
	resume = addButton(winW / 2 - buttonWidth / 2, winH / 2 - buttonHeight / 2 - 30, buttonWidth, buttonHeight, "./data/textures/button.png", playReturn)
	resume:setText("Resume")
	
	mainMenu = addButton(winW / 2 - buttonWidth / 2, winH / 2 - buttonHeight / 2 + 30, buttonWidth, buttonHeight, "./data/textures/button.png", mainMenuReturn)
	mainMenu:setText("Main Menu")
end

function Update()
	
end

function playReturn()
	doKeypress("PauseMenu")
end

function mainMenuReturn()
	setStateReturn(states.MainMenu)
end