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
CMAKE_SOURCE_DIR = /home/luca/Unipd/Computer_vision/cpp/lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2"

# Include any dependencies generated for this target.
include CMakeFiles/lab2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab2.dir/flags.make

CMakeFiles/lab2.dir/lab2.cpp.o: CMakeFiles/lab2.dir/flags.make
CMakeFiles/lab2.dir/lab2.cpp.o: /home/luca/Unipd/Computer_vision/cpp/lab2/lab2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab2.dir/lab2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab2.dir/lab2.cpp.o -c /home/luca/Unipd/Computer_vision/cpp/lab2/lab2.cpp

CMakeFiles/lab2.dir/lab2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab2.dir/lab2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Unipd/Computer_vision/cpp/lab2/lab2.cpp > CMakeFiles/lab2.dir/lab2.cpp.i

CMakeFiles/lab2.dir/lab2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab2.dir/lab2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Unipd/Computer_vision/cpp/lab2/lab2.cpp -o CMakeFiles/lab2.dir/lab2.cpp.s

CMakeFiles/lab2.dir/lab2.cpp.o.requires:

.PHONY : CMakeFiles/lab2.dir/lab2.cpp.o.requires

CMakeFiles/lab2.dir/lab2.cpp.o.provides: CMakeFiles/lab2.dir/lab2.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab2.dir/build.make CMakeFiles/lab2.dir/lab2.cpp.o.provides.build
.PHONY : CMakeFiles/lab2.dir/lab2.cpp.o.provides

CMakeFiles/lab2.dir/lab2.cpp.o.provides.build: CMakeFiles/lab2.dir/lab2.cpp.o


# Object files for target lab2
lab2_OBJECTS = \
"CMakeFiles/lab2.dir/lab2.cpp.o"

# External object files for target lab2
lab2_EXTERNAL_OBJECTS =

lab2: CMakeFiles/lab2.dir/lab2.cpp.o
lab2: CMakeFiles/lab2.dir/build.make
lab2: /usr/local/lib/libopencv_gapi.so.4.0.1
lab2: /usr/local/lib/libopencv_stitching.so.4.0.1
lab2: /usr/local/lib/libopencv_aruco.so.4.0.1
lab2: /usr/local/lib/libopencv_bgsegm.so.4.0.1
lab2: /usr/local/lib/libopencv_bioinspired.so.4.0.1
lab2: /usr/local/lib/libopencv_ccalib.so.4.0.1
lab2: /usr/local/lib/libopencv_cvv.so.4.0.1
lab2: /usr/local/lib/libopencv_dnn_objdetect.so.4.0.1
lab2: /usr/local/lib/libopencv_dpm.so.4.0.1
lab2: /usr/local/lib/libopencv_face.so.4.0.1
lab2: /usr/local/lib/libopencv_freetype.so.4.0.1
lab2: /usr/local/lib/libopencv_fuzzy.so.4.0.1
lab2: /usr/local/lib/libopencv_hdf.so.4.0.1
lab2: /usr/local/lib/libopencv_hfs.so.4.0.1
lab2: /usr/local/lib/libopencv_img_hash.so.4.0.1
lab2: /usr/local/lib/libopencv_line_descriptor.so.4.0.1
lab2: /usr/local/lib/libopencv_reg.so.4.0.1
lab2: /usr/local/lib/libopencv_rgbd.so.4.0.1
lab2: /usr/local/lib/libopencv_saliency.so.4.0.1
lab2: /usr/local/lib/libopencv_sfm.so.4.0.1
lab2: /usr/local/lib/libopencv_stereo.so.4.0.1
lab2: /usr/local/lib/libopencv_structured_light.so.4.0.1
lab2: /usr/local/lib/libopencv_superres.so.4.0.1
lab2: /usr/local/lib/libopencv_surface_matching.so.4.0.1
lab2: /usr/local/lib/libopencv_tracking.so.4.0.1
lab2: /usr/local/lib/libopencv_videostab.so.4.0.1
lab2: /usr/local/lib/libopencv_viz.so.4.0.1
lab2: /usr/local/lib/libopencv_xfeatures2d.so.4.0.1
lab2: /usr/local/lib/libopencv_xobjdetect.so.4.0.1
lab2: /usr/local/lib/libopencv_xphoto.so.4.0.1
lab2: /usr/lib/x86_64-linux-gnu/libboost_system.so
lab2: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
lab2: /usr/local/lib/libopencv_shape.so.4.0.1
lab2: /usr/local/lib/libopencv_phase_unwrapping.so.4.0.1
lab2: /usr/local/lib/libopencv_optflow.so.4.0.1
lab2: /usr/local/lib/libopencv_ximgproc.so.4.0.1
lab2: /usr/local/lib/libopencv_datasets.so.4.0.1
lab2: /usr/local/lib/libopencv_plot.so.4.0.1
lab2: /usr/local/lib/libopencv_text.so.4.0.1
lab2: /usr/local/lib/libopencv_dnn.so.4.0.1
lab2: /usr/local/lib/libopencv_ml.so.4.0.1
lab2: /usr/local/lib/libopencv_video.so.4.0.1
lab2: /usr/local/lib/libopencv_objdetect.so.4.0.1
lab2: /usr/local/lib/libopencv_calib3d.so.4.0.1
lab2: /usr/local/lib/libopencv_features2d.so.4.0.1
lab2: /usr/local/lib/libopencv_flann.so.4.0.1
lab2: /usr/local/lib/libopencv_highgui.so.4.0.1
lab2: /usr/local/lib/libopencv_videoio.so.4.0.1
lab2: /usr/local/lib/libopencv_imgcodecs.so.4.0.1
lab2: /usr/local/lib/libopencv_photo.so.4.0.1
lab2: /usr/local/lib/libopencv_imgproc.so.4.0.1
lab2: /usr/local/lib/libopencv_core.so.4.0.1
lab2: CMakeFiles/lab2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab2.dir/build: lab2

.PHONY : CMakeFiles/lab2.dir/build

CMakeFiles/lab2.dir/requires: CMakeFiles/lab2.dir/lab2.cpp.o.requires

.PHONY : CMakeFiles/lab2.dir/requires

CMakeFiles/lab2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab2.dir/clean

CMakeFiles/lab2.dir/depend:
	cd "/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luca/Unipd/Computer_vision/cpp/lab2 /home/luca/Unipd/Computer_vision/cpp/lab2 "/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2" "/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2" "/home/luca/Unipd/Ingegneria informatica LM-32/Computer_vision/cpp/lab2/CMakeFiles/lab2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lab2.dir/depend

