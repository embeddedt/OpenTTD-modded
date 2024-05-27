# CMake generated Testfile for 
# Source directory: /__w/OpenTTD-modded/OpenTTD-modded/regression/regression
# Build directory: /__w/OpenTTD-modded/OpenTTD-modded/em_build/regression/regression
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(regression_regression "/usr/bin/cmake" "-DOPENTTD_EXECUTABLE=/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.html" "-DEDITBIN_EXECUTABLE=" "-DREGRESSION_TEST=regression" "-P" "/__w/OpenTTD-modded/OpenTTD-modded/cmake/scripts/Regression.cmake")
set_tests_properties(regression_regression PROPERTIES  WORKING_DIRECTORY "/__w/OpenTTD-modded/OpenTTD-modded/em_build" _BACKTRACE_TRIPLES "/__w/OpenTTD-modded/OpenTTD-modded/cmake/CreateRegression.cmake;48;add_test;/__w/OpenTTD-modded/OpenTTD-modded/regression/regression/CMakeLists.txt;2;create_regression;/__w/OpenTTD-modded/OpenTTD-modded/regression/regression/CMakeLists.txt;0;")
