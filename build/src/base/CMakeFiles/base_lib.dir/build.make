# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/envy/tank

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/envy/tank/build

# Include any dependencies generated for this target.
include src/base/CMakeFiles/base_lib.dir/depend.make

# Include the progress variables for this target.
include src/base/CMakeFiles/base_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/base/CMakeFiles/base_lib.dir/flags.make

src/base/CMakeFiles/base_lib.dir/Connection.cc.o: src/base/CMakeFiles/base_lib.dir/flags.make
src/base/CMakeFiles/base_lib.dir/Connection.cc.o: ../src/base/Connection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/envy/tank/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/base/CMakeFiles/base_lib.dir/Connection.cc.o"
	cd /home/envy/tank/build/src/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base_lib.dir/Connection.cc.o -c /home/envy/tank/src/base/Connection.cc

src/base/CMakeFiles/base_lib.dir/Connection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base_lib.dir/Connection.cc.i"
	cd /home/envy/tank/build/src/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/envy/tank/src/base/Connection.cc > CMakeFiles/base_lib.dir/Connection.cc.i

src/base/CMakeFiles/base_lib.dir/Connection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base_lib.dir/Connection.cc.s"
	cd /home/envy/tank/build/src/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/envy/tank/src/base/Connection.cc -o CMakeFiles/base_lib.dir/Connection.cc.s

src/base/CMakeFiles/base_lib.dir/Connection.cc.o.requires:

.PHONY : src/base/CMakeFiles/base_lib.dir/Connection.cc.o.requires

src/base/CMakeFiles/base_lib.dir/Connection.cc.o.provides: src/base/CMakeFiles/base_lib.dir/Connection.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/base_lib.dir/build.make src/base/CMakeFiles/base_lib.dir/Connection.cc.o.provides.build
.PHONY : src/base/CMakeFiles/base_lib.dir/Connection.cc.o.provides

src/base/CMakeFiles/base_lib.dir/Connection.cc.o.provides.build: src/base/CMakeFiles/base_lib.dir/Connection.cc.o


src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o: src/base/CMakeFiles/base_lib.dir/flags.make
src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o: ../src/base/NetworkManager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/envy/tank/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o"
	cd /home/envy/tank/build/src/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base_lib.dir/NetworkManager.cc.o -c /home/envy/tank/src/base/NetworkManager.cc

src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base_lib.dir/NetworkManager.cc.i"
	cd /home/envy/tank/build/src/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/envy/tank/src/base/NetworkManager.cc > CMakeFiles/base_lib.dir/NetworkManager.cc.i

src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base_lib.dir/NetworkManager.cc.s"
	cd /home/envy/tank/build/src/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/envy/tank/src/base/NetworkManager.cc -o CMakeFiles/base_lib.dir/NetworkManager.cc.s

src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.requires:

.PHONY : src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.requires

src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.provides: src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/base_lib.dir/build.make src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.provides.build
.PHONY : src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.provides

src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.provides.build: src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o


src/base/CMakeFiles/base_lib.dir/Timer.cc.o: src/base/CMakeFiles/base_lib.dir/flags.make
src/base/CMakeFiles/base_lib.dir/Timer.cc.o: ../src/base/Timer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/envy/tank/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/base/CMakeFiles/base_lib.dir/Timer.cc.o"
	cd /home/envy/tank/build/src/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base_lib.dir/Timer.cc.o -c /home/envy/tank/src/base/Timer.cc

src/base/CMakeFiles/base_lib.dir/Timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base_lib.dir/Timer.cc.i"
	cd /home/envy/tank/build/src/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/envy/tank/src/base/Timer.cc > CMakeFiles/base_lib.dir/Timer.cc.i

src/base/CMakeFiles/base_lib.dir/Timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base_lib.dir/Timer.cc.s"
	cd /home/envy/tank/build/src/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/envy/tank/src/base/Timer.cc -o CMakeFiles/base_lib.dir/Timer.cc.s

src/base/CMakeFiles/base_lib.dir/Timer.cc.o.requires:

.PHONY : src/base/CMakeFiles/base_lib.dir/Timer.cc.o.requires

src/base/CMakeFiles/base_lib.dir/Timer.cc.o.provides: src/base/CMakeFiles/base_lib.dir/Timer.cc.o.requires
	$(MAKE) -f src/base/CMakeFiles/base_lib.dir/build.make src/base/CMakeFiles/base_lib.dir/Timer.cc.o.provides.build
.PHONY : src/base/CMakeFiles/base_lib.dir/Timer.cc.o.provides

src/base/CMakeFiles/base_lib.dir/Timer.cc.o.provides.build: src/base/CMakeFiles/base_lib.dir/Timer.cc.o


# Object files for target base_lib
base_lib_OBJECTS = \
"CMakeFiles/base_lib.dir/Connection.cc.o" \
"CMakeFiles/base_lib.dir/NetworkManager.cc.o" \
"CMakeFiles/base_lib.dir/Timer.cc.o"

# External object files for target base_lib
base_lib_EXTERNAL_OBJECTS =

src/base/libbase_lib.a: src/base/CMakeFiles/base_lib.dir/Connection.cc.o
src/base/libbase_lib.a: src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o
src/base/libbase_lib.a: src/base/CMakeFiles/base_lib.dir/Timer.cc.o
src/base/libbase_lib.a: src/base/CMakeFiles/base_lib.dir/build.make
src/base/libbase_lib.a: src/base/CMakeFiles/base_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/envy/tank/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libbase_lib.a"
	cd /home/envy/tank/build/src/base && $(CMAKE_COMMAND) -P CMakeFiles/base_lib.dir/cmake_clean_target.cmake
	cd /home/envy/tank/build/src/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/base/CMakeFiles/base_lib.dir/build: src/base/libbase_lib.a

.PHONY : src/base/CMakeFiles/base_lib.dir/build

src/base/CMakeFiles/base_lib.dir/requires: src/base/CMakeFiles/base_lib.dir/Connection.cc.o.requires
src/base/CMakeFiles/base_lib.dir/requires: src/base/CMakeFiles/base_lib.dir/NetworkManager.cc.o.requires
src/base/CMakeFiles/base_lib.dir/requires: src/base/CMakeFiles/base_lib.dir/Timer.cc.o.requires

.PHONY : src/base/CMakeFiles/base_lib.dir/requires

src/base/CMakeFiles/base_lib.dir/clean:
	cd /home/envy/tank/build/src/base && $(CMAKE_COMMAND) -P CMakeFiles/base_lib.dir/cmake_clean.cmake
.PHONY : src/base/CMakeFiles/base_lib.dir/clean

src/base/CMakeFiles/base_lib.dir/depend:
	cd /home/envy/tank/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/envy/tank /home/envy/tank/src/base /home/envy/tank/build /home/envy/tank/build/src/base /home/envy/tank/build/src/base/CMakeFiles/base_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/base/CMakeFiles/base_lib.dir/depend

