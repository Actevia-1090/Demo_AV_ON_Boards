# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Audio_Video/waveOverUDP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Audio_Video/waveOverUDP/build

# Include any dependencies generated for this target.
include CMakeFiles/waveSendUDP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/waveSendUDP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/waveSendUDP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/waveSendUDP.dir/flags.make

CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o: CMakeFiles/waveSendUDP.dir/flags.make
CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o: /root/Audio_Video/waveOverUDP/unix/waveSendUDP.cpp
CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o: CMakeFiles/waveSendUDP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Audio_Video/waveOverUDP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o -MF CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o.d -o CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o -c /root/Audio_Video/waveOverUDP/unix/waveSendUDP.cpp

CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Audio_Video/waveOverUDP/unix/waveSendUDP.cpp > CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.i

CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Audio_Video/waveOverUDP/unix/waveSendUDP.cpp -o CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.s

CMakeFiles/waveSendUDP.dir/Logger.cpp.o: CMakeFiles/waveSendUDP.dir/flags.make
CMakeFiles/waveSendUDP.dir/Logger.cpp.o: /root/Audio_Video/waveOverUDP/Logger.cpp
CMakeFiles/waveSendUDP.dir/Logger.cpp.o: CMakeFiles/waveSendUDP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Audio_Video/waveOverUDP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/waveSendUDP.dir/Logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/waveSendUDP.dir/Logger.cpp.o -MF CMakeFiles/waveSendUDP.dir/Logger.cpp.o.d -o CMakeFiles/waveSendUDP.dir/Logger.cpp.o -c /root/Audio_Video/waveOverUDP/Logger.cpp

CMakeFiles/waveSendUDP.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/waveSendUDP.dir/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Audio_Video/waveOverUDP/Logger.cpp > CMakeFiles/waveSendUDP.dir/Logger.cpp.i

CMakeFiles/waveSendUDP.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/waveSendUDP.dir/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Audio_Video/waveOverUDP/Logger.cpp -o CMakeFiles/waveSendUDP.dir/Logger.cpp.s

# Object files for target waveSendUDP
waveSendUDP_OBJECTS = \
"CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o" \
"CMakeFiles/waveSendUDP.dir/Logger.cpp.o"

# External object files for target waveSendUDP
waveSendUDP_EXTERNAL_OBJECTS =

/root/Audio_Video/waveOverUDP/build-bin/waveSendUDP: CMakeFiles/waveSendUDP.dir/unix/waveSendUDP.cpp.o
/root/Audio_Video/waveOverUDP/build-bin/waveSendUDP: CMakeFiles/waveSendUDP.dir/Logger.cpp.o
/root/Audio_Video/waveOverUDP/build-bin/waveSendUDP: CMakeFiles/waveSendUDP.dir/build.make
/root/Audio_Video/waveOverUDP/build-bin/waveSendUDP: CMakeFiles/waveSendUDP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/Audio_Video/waveOverUDP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /root/Audio_Video/waveOverUDP/build-bin/waveSendUDP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/waveSendUDP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/waveSendUDP.dir/build: /root/Audio_Video/waveOverUDP/build-bin/waveSendUDP
.PHONY : CMakeFiles/waveSendUDP.dir/build

CMakeFiles/waveSendUDP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/waveSendUDP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/waveSendUDP.dir/clean

CMakeFiles/waveSendUDP.dir/depend:
	cd /root/Audio_Video/waveOverUDP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Audio_Video/waveOverUDP /root/Audio_Video/waveOverUDP /root/Audio_Video/waveOverUDP/build /root/Audio_Video/waveOverUDP/build /root/Audio_Video/waveOverUDP/build/CMakeFiles/waveSendUDP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/waveSendUDP.dir/depend
