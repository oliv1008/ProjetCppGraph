##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ProjetCppGraph
ConfigurationName      :=Debug
WorkspacePath          :=/home/tom/Documents/DI3/S6/C++/ProjetCppGraph
ProjectPath            :=/home/tom/Documents/DI3/S6/C++/ProjetCppGraph
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=tom
Date                   :=07/05/19
CodeLitePath           :=/home/tom/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
ObjectsFileList        :="ProjetCppGraph.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_CSommet.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CParser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CGraphe.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CException.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CArc.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CParserGraphe.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_CSommet.cpp$(ObjectSuffix): src/CSommet.cpp $(IntermediateDirectory)/src_CSommet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/CSommet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CSommet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CSommet.cpp$(DependSuffix): src/CSommet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CSommet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CSommet.cpp$(DependSuffix) -MM src/CSommet.cpp

$(IntermediateDirectory)/src_CSommet.cpp$(PreprocessSuffix): src/CSommet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CSommet.cpp$(PreprocessSuffix) src/CSommet.cpp

$(IntermediateDirectory)/src_CParser.cpp$(ObjectSuffix): src/CParser.cpp $(IntermediateDirectory)/src_CParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/CParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CParser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CParser.cpp$(DependSuffix): src/CParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CParser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CParser.cpp$(DependSuffix) -MM src/CParser.cpp

$(IntermediateDirectory)/src_CParser.cpp$(PreprocessSuffix): src/CParser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CParser.cpp$(PreprocessSuffix) src/CParser.cpp

$(IntermediateDirectory)/src_CGraphe.cpp$(ObjectSuffix): src/CGraphe.cpp $(IntermediateDirectory)/src_CGraphe.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/CGraphe.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CGraphe.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CGraphe.cpp$(DependSuffix): src/CGraphe.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CGraphe.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CGraphe.cpp$(DependSuffix) -MM src/CGraphe.cpp

$(IntermediateDirectory)/src_CGraphe.cpp$(PreprocessSuffix): src/CGraphe.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CGraphe.cpp$(PreprocessSuffix) src/CGraphe.cpp

$(IntermediateDirectory)/src_CException.cpp$(ObjectSuffix): src/CException.cpp $(IntermediateDirectory)/src_CException.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/CException.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CException.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CException.cpp$(DependSuffix): src/CException.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CException.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CException.cpp$(DependSuffix) -MM src/CException.cpp

$(IntermediateDirectory)/src_CException.cpp$(PreprocessSuffix): src/CException.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CException.cpp$(PreprocessSuffix) src/CException.cpp

$(IntermediateDirectory)/src_CArc.cpp$(ObjectSuffix): src/CArc.cpp $(IntermediateDirectory)/src_CArc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/CArc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CArc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CArc.cpp$(DependSuffix): src/CArc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CArc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CArc.cpp$(DependSuffix) -MM src/CArc.cpp

$(IntermediateDirectory)/src_CArc.cpp$(PreprocessSuffix): src/CArc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CArc.cpp$(PreprocessSuffix) src/CArc.cpp

$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM src/main.cpp

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) src/main.cpp

$(IntermediateDirectory)/src_CParserGraphe.cpp$(ObjectSuffix): src/CParserGraphe.cpp $(IntermediateDirectory)/src_CParserGraphe.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tom/Documents/DI3/S6/C++/ProjetCppGraph/src/CParserGraphe.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CParserGraphe.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CParserGraphe.cpp$(DependSuffix): src/CParserGraphe.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CParserGraphe.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CParserGraphe.cpp$(DependSuffix) -MM src/CParserGraphe.cpp

$(IntermediateDirectory)/src_CParserGraphe.cpp$(PreprocessSuffix): src/CParserGraphe.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CParserGraphe.cpp$(PreprocessSuffix) src/CParserGraphe.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


