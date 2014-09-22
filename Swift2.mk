##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Swift2
ConfigurationName      :=Debug
WorkspacePath          := "/home/alec/Code/Swift2"
ProjectPath            := "/home/alec/Code/Swift2"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alec Iverson
Date                   :=09/21/14
CodeLitePath           :="/home/alec/.codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Swift2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-graphics $(LibrarySwitch)sfml-audio $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-system $(LibrarySwitch)lua $(LibrarySwitch)GL 
ArLibs                 :=  "sfml-graphics" "sfml-audio" "sfml-window" "sfml-system" "lua" "GL" 
LibPath                :=$(LibraryPathSwitch)/usr/local/lib  $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -g --std=c++11 -Wall -Wextra -O0  $(Preprocessors)
CFLAGS   :=  -g -Wall -O0 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix) $(IntermediateDirectory)/test_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/LD30_Maze.cpp$(ObjectSuffix) $(IntermediateDirectory)/Console_Console.cpp$(ObjectSuffix) $(IntermediateDirectory)/GUI_Window.cpp$(ObjectSuffix) $(IntermediateDirectory)/Logger_Logger.cpp$(ObjectSuffix) $(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/ResourceManager_Mod.cpp$(ObjectSuffix) $(IntermediateDirectory)/ResourceManager_ModManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Settings_Settings.cpp$(ObjectSuffix) $(IntermediateDirectory)/StateSystem_State.cpp$(ObjectSuffix) $(IntermediateDirectory)/Scripting_Script.cpp$(ObjectSuffix) $(IntermediateDirectory)/Animation_FrameAnimation.cpp$(ObjectSuffix) $(IntermediateDirectory)/Mapping_TileMap.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_World.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_Camera.cpp$(ObjectSuffix) $(IntermediateDirectory)/MessageSystem_Observable.cpp$(ObjectSuffix) $(IntermediateDirectory)/MessageSystem_Observer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Widgets_Label.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Widgets_Button.cpp$(ObjectSuffix) $(IntermediateDirectory)/Widgets_Spacer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Widgets_Toggle.cpp$(ObjectSuffix) $(IntermediateDirectory)/Widgets_TextBox.cpp$(ObjectSuffix) $(IntermediateDirectory)/Widgets_Slider.cpp$(ObjectSuffix) $(IntermediateDirectory)/Containers_Column.cpp$(ObjectSuffix) $(IntermediateDirectory)/Containers_Row.cpp$(ObjectSuffix) $(IntermediateDirectory)/Components_Drawable.cpp$(ObjectSuffix) $(IntermediateDirectory)/Components_Physical.cpp$(ObjectSuffix) $(IntermediateDirectory)/Components_Movable.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/Systems_MovableSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/States_MainMenu.cpp$(ObjectSuffix) $(IntermediateDirectory)/States_Play.cpp$(ObjectSuffix) $(IntermediateDirectory)/States_SettingsMenu.cpp$(ObjectSuffix) $(IntermediateDirectory)/Worlds_TestWorld.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix): src/Game.cpp $(IntermediateDirectory)/src_Game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Game.cpp$(DependSuffix): src/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Game.cpp$(DependSuffix) -MM "src/Game.cpp"

$(IntermediateDirectory)/src_Game.cpp$(PreprocessSuffix): src/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Game.cpp$(PreprocessSuffix) "src/Game.cpp"

$(IntermediateDirectory)/test_main.cpp$(ObjectSuffix): test/main.cpp $(IntermediateDirectory)/test_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/test/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_main.cpp$(DependSuffix): test/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/test_main.cpp$(DependSuffix) -MM "test/main.cpp"

$(IntermediateDirectory)/test_main.cpp$(PreprocessSuffix): test/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_main.cpp$(PreprocessSuffix) "test/main.cpp"

$(IntermediateDirectory)/LD30_Maze.cpp$(ObjectSuffix): LD30/Maze.cpp $(IntermediateDirectory)/LD30_Maze.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/LD30/Maze.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LD30_Maze.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LD30_Maze.cpp$(DependSuffix): LD30/Maze.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LD30_Maze.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LD30_Maze.cpp$(DependSuffix) -MM "LD30/Maze.cpp"

$(IntermediateDirectory)/LD30_Maze.cpp$(PreprocessSuffix): LD30/Maze.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LD30_Maze.cpp$(PreprocessSuffix) "LD30/Maze.cpp"

$(IntermediateDirectory)/Console_Console.cpp$(ObjectSuffix): src/Console/Console.cpp $(IntermediateDirectory)/Console_Console.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Console/Console.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Console_Console.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Console_Console.cpp$(DependSuffix): src/Console/Console.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Console_Console.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Console_Console.cpp$(DependSuffix) -MM "src/Console/Console.cpp"

$(IntermediateDirectory)/Console_Console.cpp$(PreprocessSuffix): src/Console/Console.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Console_Console.cpp$(PreprocessSuffix) "src/Console/Console.cpp"

$(IntermediateDirectory)/GUI_Window.cpp$(ObjectSuffix): src/GUI/Window.cpp $(IntermediateDirectory)/GUI_Window.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GUI_Window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GUI_Window.cpp$(DependSuffix): src/GUI/Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GUI_Window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GUI_Window.cpp$(DependSuffix) -MM "src/GUI/Window.cpp"

$(IntermediateDirectory)/GUI_Window.cpp$(PreprocessSuffix): src/GUI/Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GUI_Window.cpp$(PreprocessSuffix) "src/GUI/Window.cpp"

$(IntermediateDirectory)/Logger_Logger.cpp$(ObjectSuffix): src/Logger/Logger.cpp $(IntermediateDirectory)/Logger_Logger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Logger/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Logger_Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Logger_Logger.cpp$(DependSuffix): src/Logger/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Logger_Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Logger_Logger.cpp$(DependSuffix) -MM "src/Logger/Logger.cpp"

$(IntermediateDirectory)/Logger_Logger.cpp$(PreprocessSuffix): src/Logger/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Logger_Logger.cpp$(PreprocessSuffix) "src/Logger/Logger.cpp"

$(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(ObjectSuffix): src/ResourceManager/AssetManager.cpp $(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/ResourceManager/AssetManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(DependSuffix): src/ResourceManager/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(DependSuffix) -MM "src/ResourceManager/AssetManager.cpp"

$(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(PreprocessSuffix): src/ResourceManager/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResourceManager_AssetManager.cpp$(PreprocessSuffix) "src/ResourceManager/AssetManager.cpp"

$(IntermediateDirectory)/ResourceManager_Mod.cpp$(ObjectSuffix): src/ResourceManager/Mod.cpp $(IntermediateDirectory)/ResourceManager_Mod.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/ResourceManager/Mod.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResourceManager_Mod.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResourceManager_Mod.cpp$(DependSuffix): src/ResourceManager/Mod.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResourceManager_Mod.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ResourceManager_Mod.cpp$(DependSuffix) -MM "src/ResourceManager/Mod.cpp"

$(IntermediateDirectory)/ResourceManager_Mod.cpp$(PreprocessSuffix): src/ResourceManager/Mod.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResourceManager_Mod.cpp$(PreprocessSuffix) "src/ResourceManager/Mod.cpp"

$(IntermediateDirectory)/ResourceManager_ModManager.cpp$(ObjectSuffix): src/ResourceManager/ModManager.cpp $(IntermediateDirectory)/ResourceManager_ModManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/ResourceManager/ModManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResourceManager_ModManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResourceManager_ModManager.cpp$(DependSuffix): src/ResourceManager/ModManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResourceManager_ModManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ResourceManager_ModManager.cpp$(DependSuffix) -MM "src/ResourceManager/ModManager.cpp"

$(IntermediateDirectory)/ResourceManager_ModManager.cpp$(PreprocessSuffix): src/ResourceManager/ModManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResourceManager_ModManager.cpp$(PreprocessSuffix) "src/ResourceManager/ModManager.cpp"

$(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(ObjectSuffix): src/ResourceManager/Dictionary.cpp $(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/ResourceManager/Dictionary.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(DependSuffix): src/ResourceManager/Dictionary.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(DependSuffix) -MM "src/ResourceManager/Dictionary.cpp"

$(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(PreprocessSuffix): src/ResourceManager/Dictionary.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResourceManager_Dictionary.cpp$(PreprocessSuffix) "src/ResourceManager/Dictionary.cpp"

$(IntermediateDirectory)/Settings_Settings.cpp$(ObjectSuffix): src/Settings/Settings.cpp $(IntermediateDirectory)/Settings_Settings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Settings/Settings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Settings_Settings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Settings_Settings.cpp$(DependSuffix): src/Settings/Settings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Settings_Settings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Settings_Settings.cpp$(DependSuffix) -MM "src/Settings/Settings.cpp"

$(IntermediateDirectory)/Settings_Settings.cpp$(PreprocessSuffix): src/Settings/Settings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Settings_Settings.cpp$(PreprocessSuffix) "src/Settings/Settings.cpp"

$(IntermediateDirectory)/StateSystem_State.cpp$(ObjectSuffix): src/StateSystem/State.cpp $(IntermediateDirectory)/StateSystem_State.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/StateSystem/State.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StateSystem_State.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StateSystem_State.cpp$(DependSuffix): src/StateSystem/State.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StateSystem_State.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StateSystem_State.cpp$(DependSuffix) -MM "src/StateSystem/State.cpp"

$(IntermediateDirectory)/StateSystem_State.cpp$(PreprocessSuffix): src/StateSystem/State.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StateSystem_State.cpp$(PreprocessSuffix) "src/StateSystem/State.cpp"

$(IntermediateDirectory)/Scripting_Script.cpp$(ObjectSuffix): src/Scripting/Script.cpp $(IntermediateDirectory)/Scripting_Script.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Scripting/Script.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scripting_Script.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scripting_Script.cpp$(DependSuffix): src/Scripting/Script.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Scripting_Script.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Scripting_Script.cpp$(DependSuffix) -MM "src/Scripting/Script.cpp"

$(IntermediateDirectory)/Scripting_Script.cpp$(PreprocessSuffix): src/Scripting/Script.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scripting_Script.cpp$(PreprocessSuffix) "src/Scripting/Script.cpp"

$(IntermediateDirectory)/Animation_FrameAnimation.cpp$(ObjectSuffix): src/Animation/FrameAnimation.cpp $(IntermediateDirectory)/Animation_FrameAnimation.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Animation/FrameAnimation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Animation_FrameAnimation.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Animation_FrameAnimation.cpp$(DependSuffix): src/Animation/FrameAnimation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Animation_FrameAnimation.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Animation_FrameAnimation.cpp$(DependSuffix) -MM "src/Animation/FrameAnimation.cpp"

$(IntermediateDirectory)/Animation_FrameAnimation.cpp$(PreprocessSuffix): src/Animation/FrameAnimation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Animation_FrameAnimation.cpp$(PreprocessSuffix) "src/Animation/FrameAnimation.cpp"

$(IntermediateDirectory)/Mapping_TileMap.cpp$(ObjectSuffix): src/Mapping/TileMap.cpp $(IntermediateDirectory)/Mapping_TileMap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/Mapping/TileMap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Mapping_TileMap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Mapping_TileMap.cpp$(DependSuffix): src/Mapping/TileMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Mapping_TileMap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Mapping_TileMap.cpp$(DependSuffix) -MM "src/Mapping/TileMap.cpp"

$(IntermediateDirectory)/Mapping_TileMap.cpp$(PreprocessSuffix): src/Mapping/TileMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Mapping_TileMap.cpp$(PreprocessSuffix) "src/Mapping/TileMap.cpp"

$(IntermediateDirectory)/World_World.cpp$(ObjectSuffix): src/World/World.cpp $(IntermediateDirectory)/World_World.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/World/World.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_World.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_World.cpp$(DependSuffix): src/World/World.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_World.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_World.cpp$(DependSuffix) -MM "src/World/World.cpp"

$(IntermediateDirectory)/World_World.cpp$(PreprocessSuffix): src/World/World.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_World.cpp$(PreprocessSuffix) "src/World/World.cpp"

$(IntermediateDirectory)/World_Camera.cpp$(ObjectSuffix): src/World/Camera.cpp $(IntermediateDirectory)/World_Camera.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/World/Camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_Camera.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_Camera.cpp$(DependSuffix): src/World/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_Camera.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_Camera.cpp$(DependSuffix) -MM "src/World/Camera.cpp"

$(IntermediateDirectory)/World_Camera.cpp$(PreprocessSuffix): src/World/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_Camera.cpp$(PreprocessSuffix) "src/World/Camera.cpp"

$(IntermediateDirectory)/MessageSystem_Observable.cpp$(ObjectSuffix): src/MessageSystem/Observable.cpp $(IntermediateDirectory)/MessageSystem_Observable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/MessageSystem/Observable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MessageSystem_Observable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MessageSystem_Observable.cpp$(DependSuffix): src/MessageSystem/Observable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MessageSystem_Observable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MessageSystem_Observable.cpp$(DependSuffix) -MM "src/MessageSystem/Observable.cpp"

$(IntermediateDirectory)/MessageSystem_Observable.cpp$(PreprocessSuffix): src/MessageSystem/Observable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MessageSystem_Observable.cpp$(PreprocessSuffix) "src/MessageSystem/Observable.cpp"

$(IntermediateDirectory)/MessageSystem_Observer.cpp$(ObjectSuffix): src/MessageSystem/Observer.cpp $(IntermediateDirectory)/MessageSystem_Observer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/MessageSystem/Observer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MessageSystem_Observer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MessageSystem_Observer.cpp$(DependSuffix): src/MessageSystem/Observer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MessageSystem_Observer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MessageSystem_Observer.cpp$(DependSuffix) -MM "src/MessageSystem/Observer.cpp"

$(IntermediateDirectory)/MessageSystem_Observer.cpp$(PreprocessSuffix): src/MessageSystem/Observer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MessageSystem_Observer.cpp$(PreprocessSuffix) "src/MessageSystem/Observer.cpp"

$(IntermediateDirectory)/Widgets_Label.cpp$(ObjectSuffix): src/GUI/Widgets/Label.cpp $(IntermediateDirectory)/Widgets_Label.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Widgets/Label.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Widgets_Label.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Widgets_Label.cpp$(DependSuffix): src/GUI/Widgets/Label.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Widgets_Label.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Widgets_Label.cpp$(DependSuffix) -MM "src/GUI/Widgets/Label.cpp"

$(IntermediateDirectory)/Widgets_Label.cpp$(PreprocessSuffix): src/GUI/Widgets/Label.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Widgets_Label.cpp$(PreprocessSuffix) "src/GUI/Widgets/Label.cpp"

$(IntermediateDirectory)/Widgets_Button.cpp$(ObjectSuffix): src/GUI/Widgets/Button.cpp $(IntermediateDirectory)/Widgets_Button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Widgets/Button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Widgets_Button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Widgets_Button.cpp$(DependSuffix): src/GUI/Widgets/Button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Widgets_Button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Widgets_Button.cpp$(DependSuffix) -MM "src/GUI/Widgets/Button.cpp"

$(IntermediateDirectory)/Widgets_Button.cpp$(PreprocessSuffix): src/GUI/Widgets/Button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Widgets_Button.cpp$(PreprocessSuffix) "src/GUI/Widgets/Button.cpp"

$(IntermediateDirectory)/Widgets_Spacer.cpp$(ObjectSuffix): src/GUI/Widgets/Spacer.cpp $(IntermediateDirectory)/Widgets_Spacer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Widgets/Spacer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Widgets_Spacer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Widgets_Spacer.cpp$(DependSuffix): src/GUI/Widgets/Spacer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Widgets_Spacer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Widgets_Spacer.cpp$(DependSuffix) -MM "src/GUI/Widgets/Spacer.cpp"

$(IntermediateDirectory)/Widgets_Spacer.cpp$(PreprocessSuffix): src/GUI/Widgets/Spacer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Widgets_Spacer.cpp$(PreprocessSuffix) "src/GUI/Widgets/Spacer.cpp"

$(IntermediateDirectory)/Widgets_Toggle.cpp$(ObjectSuffix): src/GUI/Widgets/Toggle.cpp $(IntermediateDirectory)/Widgets_Toggle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Widgets/Toggle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Widgets_Toggle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Widgets_Toggle.cpp$(DependSuffix): src/GUI/Widgets/Toggle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Widgets_Toggle.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Widgets_Toggle.cpp$(DependSuffix) -MM "src/GUI/Widgets/Toggle.cpp"

$(IntermediateDirectory)/Widgets_Toggle.cpp$(PreprocessSuffix): src/GUI/Widgets/Toggle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Widgets_Toggle.cpp$(PreprocessSuffix) "src/GUI/Widgets/Toggle.cpp"

$(IntermediateDirectory)/Widgets_TextBox.cpp$(ObjectSuffix): src/GUI/Widgets/TextBox.cpp $(IntermediateDirectory)/Widgets_TextBox.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Widgets/TextBox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Widgets_TextBox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Widgets_TextBox.cpp$(DependSuffix): src/GUI/Widgets/TextBox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Widgets_TextBox.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Widgets_TextBox.cpp$(DependSuffix) -MM "src/GUI/Widgets/TextBox.cpp"

$(IntermediateDirectory)/Widgets_TextBox.cpp$(PreprocessSuffix): src/GUI/Widgets/TextBox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Widgets_TextBox.cpp$(PreprocessSuffix) "src/GUI/Widgets/TextBox.cpp"

$(IntermediateDirectory)/Widgets_Slider.cpp$(ObjectSuffix): src/GUI/Widgets/Slider.cpp $(IntermediateDirectory)/Widgets_Slider.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Widgets/Slider.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Widgets_Slider.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Widgets_Slider.cpp$(DependSuffix): src/GUI/Widgets/Slider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Widgets_Slider.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Widgets_Slider.cpp$(DependSuffix) -MM "src/GUI/Widgets/Slider.cpp"

$(IntermediateDirectory)/Widgets_Slider.cpp$(PreprocessSuffix): src/GUI/Widgets/Slider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Widgets_Slider.cpp$(PreprocessSuffix) "src/GUI/Widgets/Slider.cpp"

$(IntermediateDirectory)/Containers_Column.cpp$(ObjectSuffix): src/GUI/Containers/Column.cpp $(IntermediateDirectory)/Containers_Column.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Containers/Column.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Containers_Column.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Containers_Column.cpp$(DependSuffix): src/GUI/Containers/Column.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Containers_Column.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Containers_Column.cpp$(DependSuffix) -MM "src/GUI/Containers/Column.cpp"

$(IntermediateDirectory)/Containers_Column.cpp$(PreprocessSuffix): src/GUI/Containers/Column.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Containers_Column.cpp$(PreprocessSuffix) "src/GUI/Containers/Column.cpp"

$(IntermediateDirectory)/Containers_Row.cpp$(ObjectSuffix): src/GUI/Containers/Row.cpp $(IntermediateDirectory)/Containers_Row.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/GUI/Containers/Row.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Containers_Row.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Containers_Row.cpp$(DependSuffix): src/GUI/Containers/Row.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Containers_Row.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Containers_Row.cpp$(DependSuffix) -MM "src/GUI/Containers/Row.cpp"

$(IntermediateDirectory)/Containers_Row.cpp$(PreprocessSuffix): src/GUI/Containers/Row.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Containers_Row.cpp$(PreprocessSuffix) "src/GUI/Containers/Row.cpp"

$(IntermediateDirectory)/Components_Drawable.cpp$(ObjectSuffix): src/EntitySystem/Components/Drawable.cpp $(IntermediateDirectory)/Components_Drawable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/EntitySystem/Components/Drawable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Components_Drawable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Components_Drawable.cpp$(DependSuffix): src/EntitySystem/Components/Drawable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Components_Drawable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Components_Drawable.cpp$(DependSuffix) -MM "src/EntitySystem/Components/Drawable.cpp"

$(IntermediateDirectory)/Components_Drawable.cpp$(PreprocessSuffix): src/EntitySystem/Components/Drawable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Components_Drawable.cpp$(PreprocessSuffix) "src/EntitySystem/Components/Drawable.cpp"

$(IntermediateDirectory)/Components_Physical.cpp$(ObjectSuffix): src/EntitySystem/Components/Physical.cpp $(IntermediateDirectory)/Components_Physical.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/EntitySystem/Components/Physical.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Components_Physical.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Components_Physical.cpp$(DependSuffix): src/EntitySystem/Components/Physical.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Components_Physical.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Components_Physical.cpp$(DependSuffix) -MM "src/EntitySystem/Components/Physical.cpp"

$(IntermediateDirectory)/Components_Physical.cpp$(PreprocessSuffix): src/EntitySystem/Components/Physical.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Components_Physical.cpp$(PreprocessSuffix) "src/EntitySystem/Components/Physical.cpp"

$(IntermediateDirectory)/Components_Movable.cpp$(ObjectSuffix): src/EntitySystem/Components/Movable.cpp $(IntermediateDirectory)/Components_Movable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/EntitySystem/Components/Movable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Components_Movable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Components_Movable.cpp$(DependSuffix): src/EntitySystem/Components/Movable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Components_Movable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Components_Movable.cpp$(DependSuffix) -MM "src/EntitySystem/Components/Movable.cpp"

$(IntermediateDirectory)/Components_Movable.cpp$(PreprocessSuffix): src/EntitySystem/Components/Movable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Components_Movable.cpp$(PreprocessSuffix) "src/EntitySystem/Components/Movable.cpp"

$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(ObjectSuffix): src/EntitySystem/Systems/DrawableSystem.cpp $(IntermediateDirectory)/Systems_DrawableSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/EntitySystem/Systems/DrawableSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(DependSuffix): src/EntitySystem/Systems/DrawableSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(DependSuffix) -MM "src/EntitySystem/Systems/DrawableSystem.cpp"

$(IntermediateDirectory)/Systems_DrawableSystem.cpp$(PreprocessSuffix): src/EntitySystem/Systems/DrawableSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Systems_DrawableSystem.cpp$(PreprocessSuffix) "src/EntitySystem/Systems/DrawableSystem.cpp"

$(IntermediateDirectory)/Systems_MovableSystem.cpp$(ObjectSuffix): src/EntitySystem/Systems/MovableSystem.cpp $(IntermediateDirectory)/Systems_MovableSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/EntitySystem/Systems/MovableSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Systems_MovableSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Systems_MovableSystem.cpp$(DependSuffix): src/EntitySystem/Systems/MovableSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Systems_MovableSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Systems_MovableSystem.cpp$(DependSuffix) -MM "src/EntitySystem/Systems/MovableSystem.cpp"

$(IntermediateDirectory)/Systems_MovableSystem.cpp$(PreprocessSuffix): src/EntitySystem/Systems/MovableSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Systems_MovableSystem.cpp$(PreprocessSuffix) "src/EntitySystem/Systems/MovableSystem.cpp"

$(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(ObjectSuffix): src/EntitySystem/Systems/PhysicalSystem.cpp $(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/EntitySystem/Systems/PhysicalSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(DependSuffix): src/EntitySystem/Systems/PhysicalSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(DependSuffix) -MM "src/EntitySystem/Systems/PhysicalSystem.cpp"

$(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(PreprocessSuffix): src/EntitySystem/Systems/PhysicalSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Systems_PhysicalSystem.cpp$(PreprocessSuffix) "src/EntitySystem/Systems/PhysicalSystem.cpp"

$(IntermediateDirectory)/States_MainMenu.cpp$(ObjectSuffix): src/StateSystem/States/MainMenu.cpp $(IntermediateDirectory)/States_MainMenu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/StateSystem/States/MainMenu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/States_MainMenu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/States_MainMenu.cpp$(DependSuffix): src/StateSystem/States/MainMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/States_MainMenu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/States_MainMenu.cpp$(DependSuffix) -MM "src/StateSystem/States/MainMenu.cpp"

$(IntermediateDirectory)/States_MainMenu.cpp$(PreprocessSuffix): src/StateSystem/States/MainMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/States_MainMenu.cpp$(PreprocessSuffix) "src/StateSystem/States/MainMenu.cpp"

$(IntermediateDirectory)/States_Play.cpp$(ObjectSuffix): src/StateSystem/States/Play.cpp $(IntermediateDirectory)/States_Play.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/StateSystem/States/Play.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/States_Play.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/States_Play.cpp$(DependSuffix): src/StateSystem/States/Play.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/States_Play.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/States_Play.cpp$(DependSuffix) -MM "src/StateSystem/States/Play.cpp"

$(IntermediateDirectory)/States_Play.cpp$(PreprocessSuffix): src/StateSystem/States/Play.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/States_Play.cpp$(PreprocessSuffix) "src/StateSystem/States/Play.cpp"

$(IntermediateDirectory)/States_SettingsMenu.cpp$(ObjectSuffix): src/StateSystem/States/SettingsMenu.cpp $(IntermediateDirectory)/States_SettingsMenu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/StateSystem/States/SettingsMenu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/States_SettingsMenu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/States_SettingsMenu.cpp$(DependSuffix): src/StateSystem/States/SettingsMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/States_SettingsMenu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/States_SettingsMenu.cpp$(DependSuffix) -MM "src/StateSystem/States/SettingsMenu.cpp"

$(IntermediateDirectory)/States_SettingsMenu.cpp$(PreprocessSuffix): src/StateSystem/States/SettingsMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/States_SettingsMenu.cpp$(PreprocessSuffix) "src/StateSystem/States/SettingsMenu.cpp"

$(IntermediateDirectory)/Worlds_TestWorld.cpp$(ObjectSuffix): src/World/Worlds/TestWorld.cpp $(IntermediateDirectory)/Worlds_TestWorld.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/src/World/Worlds/TestWorld.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Worlds_TestWorld.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Worlds_TestWorld.cpp$(DependSuffix): src/World/Worlds/TestWorld.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Worlds_TestWorld.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Worlds_TestWorld.cpp$(DependSuffix) -MM "src/World/Worlds/TestWorld.cpp"

$(IntermediateDirectory)/Worlds_TestWorld.cpp$(PreprocessSuffix): src/World/Worlds/TestWorld.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Worlds_TestWorld.cpp$(PreprocessSuffix) "src/World/Worlds/TestWorld.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Debug/*$(ObjectSuffix)
	$(RM) ./Debug/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/Swift2"


