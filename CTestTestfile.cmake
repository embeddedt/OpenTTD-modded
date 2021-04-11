# CMake generated Testfile for 
# Source directory: /__w/OpenTTD-modded/OpenTTD-modded
# Build directory: /__w/OpenTTD-modded/OpenTTD-modded/em_build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(regression_regression "/usr/bin/cmake" "-DOPENTTD_EXECUTABLE=/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.html" "-DEDITBIN_EXECUTABLE=" "-DREGRESSION_TEST=regression" "-P" "/__w/OpenTTD-modded/OpenTTD-modded/cmake/scripts/Regression.cmake")
set_tests_properties(regression_regression PROPERTIES  WORKING_DIRECTORY "/__w/OpenTTD-modded/OpenTTD-modded/em_build")
add_test(regression_stationlist "/usr/bin/cmake" "-DOPENTTD_EXECUTABLE=/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.html" "-DEDITBIN_EXECUTABLE=" "-DREGRESSION_TEST=stationlist" "-P" "/__w/OpenTTD-modded/OpenTTD-modded/cmake/scripts/Regression.cmake")
set_tests_properties(regression_stationlist PROPERTIES  WORKING_DIRECTORY "/__w/OpenTTD-modded/OpenTTD-modded/em_build")
subdirs("bin")
subdirs("src")
subdirs("media")
