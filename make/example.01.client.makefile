# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"../include" 
Debug64_Include_Path=-I"../include" 
Release_Include_Path=-I"../include" 
Release64_Include_Path=-I"../include" 

# Library paths...
Debug_Library_Path=-L"gccDebug/"
Debug64_Library_Path=-L"x64/gccDebug/"
Release_Library_Path=-L"gccRelease/"
Release64_Library_Path=-L"x64/gccRelease/"

# Additional libraries...
Debug_Libraries=-lxiSock32_d.a
Debug64_Libraries=-lxiSock64_d.a
Release_Libraries=-lxiSock32.a
Release64_Libraries=-lxiSock64.a

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _CONSOLE 
Debug64_Preprocessor_Definitions=-D _DEBUG -D _CONSOLE -D GCC_BUILD 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _CONSOLE 
Release64_Preprocessor_Definitions=-D NDEBUG -D _CONSOLE -D GCC_BUILD 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Debug64_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=
Release64_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -g -std=c++0x
Debug64_Compiler_Flags=-O0 -g -std=c++0x -m64
Release_Compiler_Flags=-O2 -std=c++0x
Release64_Compiler_Flags=-O2 -std=c++0x -m64

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Debug64 Release Release64 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/example.01.client/main.o 
	g++ gccDebug/example.01.client/main.o  $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o gccDebug/example.01.client.bin

# Compiles file ../examples/example.01.client/main.cpp for the Debug configuration...
-include gccDebug/example.01.client/main.d
gccDebug/example.01.client/main.o: ../examples/example.01.client/main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../examples/example.01.client/main.cpp $(Debug_Include_Path) -o gccDebug/example.01.client/main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../examples/example.01.client/main.cpp $(Debug_Include_Path) > gccDebug/example.01.client/main.d

# Builds the Debug configuration...
.PHONY: Debug64
Debug64: create_folders x64/gccDebug/example.01.client/main.o 
	g++ x64/gccDebug/example.01.client/main.o  $(Debug64_Library_Path) $(Debug64_Libraries) -Wl,-rpath,./ -o x64/gccDebug/example.01.client.bin

# Compiles file ../examples/example.01.client/main.cpp for the Debug configuration...
-include x64/gccDebug/main.d
x64/gccDebug/example.01.client/main.o: ../examples/example.01.client/main.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../examples/example.01.client/main.cpp $(Debug64_Include_Path) -o x64/gccDebug/example.01.client/main.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../examples/example.01.client/main.cpp $(Debug64_Include_Path) > x64/gccDebug/main.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/example.01.client/main.o 
	g++ gccRelease/example.01.client/main.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o gccRelease/example.01.client.bin

# Compiles file ../examples/example.01.client/main.cpp for the Release configuration...
-include gccRelease/main.d
gccRelease/example.01.client/main.o: ../examples/example.01.client/main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../examples/example.01.client/main.cpp $(Release_Include_Path) -o gccRelease/example.01.client/main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../examples/example.01.client/main.cpp $(Release_Include_Path) > gccRelease/main.d

# Builds the Release configuration...
.PHONY: Release64
Release64: create_folders x64/gccRelease/example.01.client/main.o 
	g++ x64/gccRelease/example.01.client/main.o  $(Release64_Library_Path) $(Release64_Libraries) -Wl,-rpath,./ -o x64/gccRelease/example.01.client.bin

# Compiles file ../examples/example.01.client/main.cpp for the Release configuration...
-include x64/gccRelease/main.d
x64/gccRelease/example.01.client/main.o: ../examples/example.01.client/main.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../examples/example.01.client/main.cpp $(Release64_Include_Path) -o x64/gccRelease/example.01.client/main.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../examples/example.01.client/main.cpp $(Release64_Include_Path) > x64/gccRelease/main.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/example.01.client
	mkdir -p gccDebug
	mkdir -p x64/gccDebug/example.01.client
	mkdir -p x64/gccDebug
	mkdir -p gccRelease/example.01.client
	mkdir -p gccRelease
	mkdir -p x64/gccRelease/example.01.client
	mkdir -p x64/gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f gccDebug/*.a
	rm -f gccDebug/*.so
	rm -f gccDebug/*.dll
	rm -f gccDebug/*.bin
	rm -f x64/gccDebug/*.o
	rm -f x64/gccDebug/*.d
	rm -f x64/gccDebug/*.a
	rm -f x64/gccDebug/*.so
	rm -f x64/gccDebug/*.dll
	rm -f x64/gccDebug/*.bin
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f gccRelease/*.a
	rm -f gccRelease/*.so
	rm -f gccRelease/*.dll
	rm -f gccRelease/*.bin
	rm -f x64/gccRelease/*.o
	rm -f x64/gccRelease/*.d
	rm -f x64/gccRelease/*.a
	rm -f x64/gccRelease/*.so
	rm -f x64/gccRelease/*.dll
	rm -f x64/gccRelease/*.bin

