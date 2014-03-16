# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"../../include" 
Debug_Include_Path=-I"../../include" 
Release_Include_Path=-I"../../include" 
Release_Include_Path=-I"../../include" 

# Library paths...
Debug_Library_Path=
Debug_Library_Path=
Release_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=
Debug_Libraries=
Release_Libraries=
Release_Libraries=

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _CONSOLE 
Debug_Preprocessor_Definitions=-D WIN64 -D _DEBUG -D _CONSOLE -D GCC_BUILD 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _CONSOLE 
Release_Preprocessor_Definitions=-D WIN64 -D NDEBUG -D _CONSOLE -D GCC_BUILD 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -g 
Debug_Compiler_Flags=-O0 -g 
Release_Compiler_Flags=-O2 
Release_Compiler_Flags=-O2 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Debug Release Release 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/main.o 
	g++ gccDebug/main.o  $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o ../../vs2010/gccDebug/example.02.client.exe

# Compiles file main.cpp for the Debug configuration...
-include gccDebug/main.d
gccDebug/main.o: main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c main.cpp $(Debug_Include_Path) -o gccDebug/main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM main.cpp $(Debug_Include_Path) > gccDebug/main.d

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders x64/gccDebug/main.o 
	g++ x64/gccDebug/main.o  $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o ../../vs2010/x64/gccDebug/example.02.client.exe

# Compiles file main.cpp for the Debug configuration...
-include x64/gccDebug/main.d
x64/gccDebug/main.o: main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c main.cpp $(Debug_Include_Path) -o x64/gccDebug/main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM main.cpp $(Debug_Include_Path) > x64/gccDebug/main.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/main.o 
	g++ gccRelease/main.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o ../../vs2010/gccRelease/example.02.client.exe

# Compiles file main.cpp for the Release configuration...
-include gccRelease/main.d
gccRelease/main.o: main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c main.cpp $(Release_Include_Path) -o gccRelease/main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM main.cpp $(Release_Include_Path) > gccRelease/main.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders x64/gccRelease/main.o 
	g++ x64/gccRelease/main.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o ../../vs2010/x64/gccRelease/example.02.client.exe

# Compiles file main.cpp for the Release configuration...
-include x64/gccRelease/main.d
x64/gccRelease/main.o: main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c main.cpp $(Release_Include_Path) -o x64/gccRelease/main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM main.cpp $(Release_Include_Path) > x64/gccRelease/main.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/source
	mkdir -p ../../vs2010/gccDebug
	mkdir -p x64/gccDebug/source
	mkdir -p ../../vs2010/x64/gccDebug
	mkdir -p gccRelease/source
	mkdir -p ../../vs2010/gccRelease
	mkdir -p x64/gccRelease/source
	mkdir -p ../../vs2010/x64/gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f ../../vs2010/gccDebug/*.a
	rm -f ../../vs2010/gccDebug/*.so
	rm -f ../../vs2010/gccDebug/*.dll
	rm -f ../../vs2010/gccDebug/*.exe
	rm -f x64/gccDebug/*.o
	rm -f x64/gccDebug/*.d
	rm -f ../../vs2010/x64/gccDebug/*.a
	rm -f ../../vs2010/x64/gccDebug/*.so
	rm -f ../../vs2010/x64/gccDebug/*.dll
	rm -f ../../vs2010/x64/gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f ../../vs2010/gccRelease/*.a
	rm -f ../../vs2010/gccRelease/*.so
	rm -f ../../vs2010/gccRelease/*.dll
	rm -f ../../vs2010/gccRelease/*.exe
	rm -f x64/gccRelease/*.o
	rm -f x64/gccRelease/*.d
	rm -f ../../vs2010/x64/gccRelease/*.a
	rm -f ../../vs2010/x64/gccRelease/*.so
	rm -f ../../vs2010/x64/gccRelease/*.dll
	rm -f ../../vs2010/x64/gccRelease/*.exe

