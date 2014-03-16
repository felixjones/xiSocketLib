# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"../include" 
Debug64_Include_Path=-I"../include" 
Release_Include_Path=-I"../include" 
Release64_Include_Path=-I"../include" 

# Library paths...
Debug_Library_Path=
Debug64_Library_Path=
Release_Library_Path=
Release64_Library_Path=

# Additional libraries...
Debug_Libraries=
Debug64_Libraries=
Release_Libraries=
Release64_Libraries=

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _LIB 
Debug64_Preprocessor_Definitions=-D _DEBUG -D _LIB -D GCC_BUILD 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _LIB 
Release64_Preprocessor_Definitions=-D NDEBUG -D _LIB -D GCC_BUILD 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Debug64_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=
Release64_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -std=c++0x
Debug64_Compiler_Flags=-O0 -std=c++0x -m64
Release_Compiler_Flags=-O2 -std=c++0x
Release64_Compiler_Flags=-O2 -std=c++0x -m64

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Debug64 Release Release64 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/source/Endian.o gccDebug/source/NetString.o gccDebug/source/ProtoBase.o gccDebug/source/SmartPointer.o gccDebug/source/Socket.o gccDebug/source/TCP.o gccDebug/source/UDP.o 
	ar rcs gccDebug/libxiSock32_d.a gccDebug/source/Endian.o gccDebug/source/NetString.o gccDebug/source/ProtoBase.o gccDebug/source/SmartPointer.o gccDebug/source/Socket.o gccDebug/source/TCP.o gccDebug/source/UDP.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file ../source/Endian.cpp for the Debug configuration...
-include gccDebug/source/Endian.d
gccDebug/source/Endian.o: ../source/Endian.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/Endian.cpp $(Debug_Include_Path) -o gccDebug/source/Endian.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/Endian.cpp $(Debug_Include_Path) > gccDebug/source/Endian.d

# Compiles file ../source/NetString.cpp for the Debug configuration...
-include gccDebug/source/NetString.d
gccDebug/source/NetString.o: ../source/NetString.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/NetString.cpp $(Debug_Include_Path) -o gccDebug/source/NetString.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/NetString.cpp $(Debug_Include_Path) > gccDebug/source/NetString.d

# Compiles file ../source/ProtoBase.cpp for the Debug configuration...
-include gccDebug/source/ProtoBase.d
gccDebug/source/ProtoBase.o: ../source/ProtoBase.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/ProtoBase.cpp $(Debug_Include_Path) -o gccDebug/source/ProtoBase.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/ProtoBase.cpp $(Debug_Include_Path) > gccDebug/source/ProtoBase.d

# Compiles file ../source/SmartPointer.cpp for the Debug configuration...
-include gccDebug/source/SmartPointer.d
gccDebug/source/SmartPointer.o: ../source/SmartPointer.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/SmartPointer.cpp $(Debug_Include_Path) -o gccDebug/source/SmartPointer.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/SmartPointer.cpp $(Debug_Include_Path) > gccDebug/source/SmartPointer.d

# Compiles file ../source/Socket.cpp for the Debug configuration...
-include gccDebug/source/Socket.d
gccDebug/source/Socket.o: ../source/Socket.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/Socket.cpp $(Debug_Include_Path) -o gccDebug/source/Socket.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/Socket.cpp $(Debug_Include_Path) > gccDebug/source/Socket.d

# Compiles file ../source/TCP.cpp for the Debug configuration...
-include gccDebug/source/TCP.d
gccDebug/source/TCP.o: ../source/TCP.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/TCP.cpp $(Debug_Include_Path) -o gccDebug/source/TCP.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/TCP.cpp $(Debug_Include_Path) > gccDebug/source/TCP.d

# Compiles file ../source/UDP.cpp for the Debug configuration...
-include gccDebug/source/UDP.d
gccDebug/source/UDP.o: ../source/UDP.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../source/UDP.cpp $(Debug_Include_Path) -o gccDebug/source/UDP.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../source/UDP.cpp $(Debug_Include_Path) > gccDebug/source/UDP.d

# Builds the Debug configuration...
.PHONY: Debug64
Debug: create_folders x64/gccDebug/source/Endian.o x64/gccDebug/source/NetString.o x64/gccDebug/source/ProtoBase.o x64/gccDebug/source/SmartPointer.o x64/gccDebug/source/Socket.o x64/gccDebug/source/TCP.o x64/gccDebug/source/UDP.o 
	ar rcs x64/gccDebug/libxiSock64_d.a x64/gccDebug/source/Endian.o x64/gccDebug/source/NetString.o x64/gccDebug/source/ProtoBase.o x64/gccDebug/source/SmartPointer.o x64/gccDebug/source/Socket.o x64/gccDebug/source/TCP.o x64/gccDebug/source/UDP.o  $(Debug64_Implicitly_Linked_Objects)

# Compiles file ../source/Endian.cpp for the Debug configuration...
-include x64/gccDebug/source/Endian.d
x64/gccDebug/source/Endian.o: ../source/Endian.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/Endian.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/Endian.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/Endian.cpp $(Debug64_Include_Path) > x64/gccDebug/source/Endian.d

# Compiles file ../source/NetString.cpp for the Debug configuration...
-include x64/gccDebug/source/NetString.d
x64/gccDebug/source/NetString.o: ../source/NetString.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/NetString.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/NetString.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/NetString.cpp $(Debug64_Include_Path) > x64/gccDebug/source/NetString.d

# Compiles file ../source/ProtoBase.cpp for the Debug configuration...
-include x64/gccDebug/source/ProtoBase.d
x64/gccDebug/source/ProtoBase.o: ../source/ProtoBase.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/ProtoBase.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/ProtoBase.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/ProtoBase.cpp $(Debug64_Include_Path) > x64/gccDebug/source/ProtoBase.d

# Compiles file ../source/SmartPointer.cpp for the Debug configuration...
-include x64/gccDebug/source/SmartPointer.d
x64/gccDebug/source/SmartPointer.o: ../source/SmartPointer.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/SmartPointer.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/SmartPointer.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/SmartPointer.cpp $(Debug64_Include_Path) > x64/gccDebug/source/SmartPointer.d

# Compiles file ../source/Socket.cpp for the Debug configuration...
-include x64/gccDebug/source/Socket.d
x64/gccDebug/source/Socket.o: ../source/Socket.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/Socket.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/Socket.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/Socket.cpp $(Debug64_Include_Path) > x64/gccDebug/source/Socket.d

# Compiles file ../source/TCP.cpp for the Debug configuration...
-include x64/gccDebug/source/TCP.d
x64/gccDebug/source/TCP.o: ../source/TCP.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/TCP.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/TCP.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/TCP.cpp $(Debug64_Include_Path) > x64/gccDebug/source/TCP.d

# Compiles file ../source/UDP.cpp for the Debug configuration...
-include x64/gccDebug/source/UDP.d
x64/gccDebug/source/UDP.o: ../source/UDP.cpp
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -c ../source/UDP.cpp $(Debug64_Include_Path) -o x64/gccDebug/source/UDP.o
	$(CPP_COMPILER) $(Debug64_Preprocessor_Definitions) $(Debug64_Compiler_Flags) -MM ../source/UDP.cpp $(Debug64_Include_Path) > x64/gccDebug/source/UDP.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/source/Endian.o gccRelease/source/NetString.o gccRelease/source/ProtoBase.o gccRelease/source/SmartPointer.o gccRelease/source/Socket.o gccRelease/source/TCP.o gccRelease/source/UDP.o 
	ar rcs gccRelease/libxiSock32.a gccRelease/source/Endian.o gccRelease/source/NetString.o gccRelease/source/ProtoBase.o gccRelease/source/SmartPointer.o gccRelease/source/Socket.o gccRelease/source/TCP.o gccRelease/source/UDP.o  $(Release_Implicitly_Linked_Objects)

# Compiles file ../source/Endian.cpp for the Release configuration...
-include gccRelease/source/Endian.d
gccRelease/source/Endian.o: ../source/Endian.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/Endian.cpp $(Release_Include_Path) -o gccRelease/source/Endian.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/Endian.cpp $(Release_Include_Path) > gccRelease/source/Endian.d

# Compiles file ../source/NetString.cpp for the Release configuration...
-include gccRelease/source/NetString.d
gccRelease/source/NetString.o: ../source/NetString.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/NetString.cpp $(Release_Include_Path) -o gccRelease/source/NetString.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/NetString.cpp $(Release_Include_Path) > gccRelease/source/NetString.d

# Compiles file ../source/ProtoBase.cpp for the Release configuration...
-include gccRelease/source/ProtoBase.d
gccRelease/source/ProtoBase.o: ../source/ProtoBase.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/ProtoBase.cpp $(Release_Include_Path) -o gccRelease/source/ProtoBase.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/ProtoBase.cpp $(Release_Include_Path) > gccRelease/source/ProtoBase.d

# Compiles file ../source/SmartPointer.cpp for the Release configuration...
-include gccRelease/source/SmartPointer.d
gccRelease/source/SmartPointer.o: ../source/SmartPointer.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/SmartPointer.cpp $(Release_Include_Path) -o gccRelease/source/SmartPointer.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/SmartPointer.cpp $(Release_Include_Path) > gccRelease/source/SmartPointer.d

# Compiles file ../source/Socket.cpp for the Release configuration...
-include gccRelease/source/Socket.d
gccRelease/source/Socket.o: ../source/Socket.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/Socket.cpp $(Release_Include_Path) -o gccRelease/source/Socket.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/Socket.cpp $(Release_Include_Path) > gccRelease/source/Socket.d

# Compiles file ../source/TCP.cpp for the Release configuration...
-include gccRelease/source/TCP.d
gccRelease/source/TCP.o: ../source/TCP.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/TCP.cpp $(Release_Include_Path) -o gccRelease/source/TCP.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/TCP.cpp $(Release_Include_Path) > gccRelease/source/TCP.d

# Compiles file ../source/UDP.cpp for the Release configuration...
-include gccRelease/source/UDP.d
gccRelease/source/UDP.o: ../source/UDP.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../source/UDP.cpp $(Release_Include_Path) -o gccRelease/source/UDP.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../source/UDP.cpp $(Release_Include_Path) > gccRelease/source/UDP.d

# Builds the Release configuration...
.PHONY: Release64
Release: create_folders x64/gccRelease/source/Endian.o x64/gccRelease/source/NetString.o x64/gccRelease/source/ProtoBase.o x64/gccRelease/source/SmartPointer.o x64/gccRelease/source/Socket.o x64/gccRelease/source/TCP.o x64/gccRelease/source/UDP.o 
	ar rcs x64/gccRelease/libxiSock64.a x64/gccRelease/source/Endian.o x64/gccRelease/source/NetString.o x64/gccRelease/source/ProtoBase.o x64/gccRelease/source/SmartPointer.o x64/gccRelease/source/Socket.o x64/gccRelease/source/TCP.o x64/gccRelease/source/UDP.o  $(Release64_Implicitly_Linked_Objects)

# Compiles file ../source/Endian.cpp for the Release configuration...
-include x64/gccRelease/source/Endian.d
x64/gccRelease/source/Endian.o: ../source/Endian.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/Endian.cpp $(Release64_Include_Path) -o x64/gccRelease/source/Endian.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/Endian.cpp $(Release64_Include_Path) > x64/gccRelease/source/Endian.d

# Compiles file ../source/NetString.cpp for the Release configuration...
-include x64/gccRelease/source/NetString.d
x64/gccRelease/source/NetString.o: ../source/NetString.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/NetString.cpp $(Release64_Include_Path) -o x64/gccRelease/source/NetString.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/NetString.cpp $(Release64_Include_Path) > x64/gccRelease/source/NetString.d

# Compiles file ../source/ProtoBase.cpp for the Release configuration...
-include x64/gccRelease/source/ProtoBase.d
x64/gccRelease/source/ProtoBase.o: ../source/ProtoBase.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/ProtoBase.cpp $(Release64_Include_Path) -o x64/gccRelease/source/ProtoBase.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/ProtoBase.cpp $(Release64_Include_Path) > x64/gccRelease/source/ProtoBase.d

# Compiles file ../source/SmartPointer.cpp for the Release configuration...
-include x64/gccRelease/source/SmartPointer.d
x64/gccRelease/source/SmartPointer.o: ../source/SmartPointer.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/SmartPointer.cpp $(Release64_Include_Path) -o x64/gccRelease/source/SmartPointer.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/SmartPointer.cpp $(Release64_Include_Path) > x64/gccRelease/source/SmartPointer.d

# Compiles file ../source/Socket.cpp for the Release configuration...
-include x64/gccRelease/source/Socket.d
x64/gccRelease/source/Socket.o: ../source/Socket.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/Socket.cpp $(Release64_Include_Path) -o x64/gccRelease/source/Socket.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/Socket.cpp $(Release64_Include_Path) > x64/gccRelease/source/Socket.d

# Compiles file ../source/TCP.cpp for the Release configuration...
-include x64/gccRelease/source/TCP.d
x64/gccRelease/source/TCP.o: ../source/TCP.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/TCP.cpp $(Release64_Include_Path) -o x64/gccRelease/source/TCP.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/TCP.cpp $(Release64_Include_Path) > x64/gccRelease/source/TCP.d

# Compiles file ../source/UDP.cpp for the Release configuration...
-include x64/gccRelease/source/UDP.d
x64/gccRelease/source/UDP.o: ../source/UDP.cpp
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -c ../source/UDP.cpp $(Release64_Include_Path) -o x64/gccRelease/source/UDP.o
	$(CPP_COMPILER) $(Release64_Preprocessor_Definitions) $(Release64_Compiler_Flags) -MM ../source/UDP.cpp $(Release64_Include_Path) > x64/gccRelease/source/UDP.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/source
	mkdir -p x64/gccDebug/source
	mkdir -p gccRelease/source
	mkdir -p x64/gccRelease/source

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

