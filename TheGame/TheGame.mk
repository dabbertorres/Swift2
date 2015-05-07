##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TheGame
ConfigurationName      :=Debug
WorkspacePath          := "/home/alec/Code/Swift2"
ProjectPath            := "/home/alec/Code/Swift2/TheGame"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alec Iverson
Date                   :=03/22/15
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
ObjectsFileList        :="TheGame.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            := $(IncludeSwitch)/usr/local/include  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)swift2 $(LibrarySwitch)sfml-graphics $(LibrarySwitch)sfml-audio $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-system $(LibrarySwitch)lua $(LibrarySwitch)dl $(LibrarySwitch)GL $(LibrarySwitch)tinyxml2 
ArLibs                 :=  "swift2" "sfml-graphics" "sfml-audio" "sfml-window" "sfml-system" "lua" "dl" "GL" "tinyxml2" 
LibPath                :=$(LibraryPathSwitch)/usr/local/lib  $(LibraryPathSwitch). $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -g -O0 -ansi -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_TheGame.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GamePlay.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GameMenu.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GameSettings.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GameScript.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GameAssets.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GameWorld.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_Galaxy.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_SolarSystem.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/World_Body.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/src_TheGame.cpp$(ObjectSuffix): src/TheGame.cpp $(IntermediateDirectory)/src_TheGame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/TheGame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_TheGame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TheGame.cpp$(DependSuffix): src/TheGame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TheGame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TheGame.cpp$(DependSuffix) -MM "src/TheGame.cpp"

$(IntermediateDirectory)/src_TheGame.cpp$(PreprocessSuffix): src/TheGame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TheGame.cpp$(PreprocessSuffix) "src/TheGame.cpp"

$(IntermediateDirectory)/src_GamePlay.cpp$(ObjectSuffix): src/GamePlay.cpp $(IntermediateDirectory)/src_GamePlay.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/GamePlay.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GamePlay.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GamePlay.cpp$(DependSuffix): src/GamePlay.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GamePlay.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GamePlay.cpp$(DependSuffix) -MM "src/GamePlay.cpp"

$(IntermediateDirectory)/src_GamePlay.cpp$(PreprocessSuffix): src/GamePlay.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GamePlay.cpp$(PreprocessSuffix) "src/GamePlay.cpp"

$(IntermediateDirectory)/src_GameMenu.cpp$(ObjectSuffix): src/GameMenu.cpp $(IntermediateDirectory)/src_GameMenu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/GameMenu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GameMenu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GameMenu.cpp$(DependSuffix): src/GameMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GameMenu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GameMenu.cpp$(DependSuffix) -MM "src/GameMenu.cpp"

$(IntermediateDirectory)/src_GameMenu.cpp$(PreprocessSuffix): src/GameMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GameMenu.cpp$(PreprocessSuffix) "src/GameMenu.cpp"

$(IntermediateDirectory)/src_GameSettings.cpp$(ObjectSuffix): src/GameSettings.cpp $(IntermediateDirectory)/src_GameSettings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/GameSettings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GameSettings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GameSettings.cpp$(DependSuffix): src/GameSettings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GameSettings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GameSettings.cpp$(DependSuffix) -MM "src/GameSettings.cpp"

$(IntermediateDirectory)/src_GameSettings.cpp$(PreprocessSuffix): src/GameSettings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GameSettings.cpp$(PreprocessSuffix) "src/GameSettings.cpp"

$(IntermediateDirectory)/src_GameScript.cpp$(ObjectSuffix): src/GameScript.cpp $(IntermediateDirectory)/src_GameScript.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/GameScript.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GameScript.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GameScript.cpp$(DependSuffix): src/GameScript.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GameScript.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GameScript.cpp$(DependSuffix) -MM "src/GameScript.cpp"

$(IntermediateDirectory)/src_GameScript.cpp$(PreprocessSuffix): src/GameScript.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GameScript.cpp$(PreprocessSuffix) "src/GameScript.cpp"

$(IntermediateDirectory)/src_GameAssets.cpp$(ObjectSuffix): src/GameAssets.cpp $(IntermediateDirectory)/src_GameAssets.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/GameAssets.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GameAssets.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GameAssets.cpp$(DependSuffix): src/GameAssets.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GameAssets.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GameAssets.cpp$(DependSuffix) -MM "src/GameAssets.cpp"

$(IntermediateDirectory)/src_GameAssets.cpp$(PreprocessSuffix): src/GameAssets.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GameAssets.cpp$(PreprocessSuffix) "src/GameAssets.cpp"

$(IntermediateDirectory)/src_GameWorld.cpp$(ObjectSuffix): src/GameWorld.cpp $(IntermediateDirectory)/src_GameWorld.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/GameWorld.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GameWorld.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GameWorld.cpp$(DependSuffix): src/GameWorld.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GameWorld.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GameWorld.cpp$(DependSuffix) -MM "src/GameWorld.cpp"

$(IntermediateDirectory)/src_GameWorld.cpp$(PreprocessSuffix): src/GameWorld.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GameWorld.cpp$(PreprocessSuffix) "src/GameWorld.cpp"

$(IntermediateDirectory)/World_Galaxy.cpp$(ObjectSuffix): src/World/Galaxy.cpp $(IntermediateDirectory)/World_Galaxy.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/World/Galaxy.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_Galaxy.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_Galaxy.cpp$(DependSuffix): src/World/Galaxy.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_Galaxy.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_Galaxy.cpp$(DependSuffix) -MM "src/World/Galaxy.cpp"

$(IntermediateDirectory)/World_Galaxy.cpp$(PreprocessSuffix): src/World/Galaxy.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_Galaxy.cpp$(PreprocessSuffix) "src/World/Galaxy.cpp"

$(IntermediateDirectory)/World_SolarSystem.cpp$(ObjectSuffix): src/World/SolarSystem.cpp $(IntermediateDirectory)/World_SolarSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/World/SolarSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_SolarSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_SolarSystem.cpp$(DependSuffix): src/World/SolarSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_SolarSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_SolarSystem.cpp$(DependSuffix) -MM "src/World/SolarSystem.cpp"

$(IntermediateDirectory)/World_SolarSystem.cpp$(PreprocessSuffix): src/World/SolarSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_SolarSystem.cpp$(PreprocessSuffix) "src/World/SolarSystem.cpp"

$(IntermediateDirectory)/World_Body.cpp$(ObjectSuffix): src/World/Body.cpp $(IntermediateDirectory)/World_Body.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alec/Code/Swift2/TheGame/src/World/Body.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_Body.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_Body.cpp$(DependSuffix): src/World/Body.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_Body.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_Body.cpp$(DependSuffix) -MM "src/World/Body.cpp"

$(IntermediateDirectory)/World_Body.cpp$(PreprocessSuffix): src/World/Body.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_Body.cpp$(PreprocessSuffix) "src/World/Body.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


