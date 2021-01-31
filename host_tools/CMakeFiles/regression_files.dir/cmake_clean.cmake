file(REMOVE_RECURSE
  "CMakeFiles/regression_files"
  "ai/regression/info.nut"
  "ai/regression/main.nut"
  "ai/regression/require.nut"
  "ai/regression/result.txt"
  "ai/regression/test.sav"
  "ai/stationlist/info.nut"
  "ai/stationlist/main.nut"
  "ai/stationlist/result.txt"
  "ai/stationlist/test.sav"
  "regression/regression.cfg"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/regression_files.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
