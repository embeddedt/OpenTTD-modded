# Make the current version available to CPack
set(CPACK_PACKAGE_VERSION "20230414-stock_jgr-g9e33bad646")

# Name the output file with the correct version
string(REPLACE "#CPACK_PACKAGE_VERSION#" "20230414-stock_jgr-g9e33bad646" CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}")

string(REGEX REPLACE "^jgrpp-" "" CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}")

if (CPACK_BUNDLE_PLIST_SOURCE)
    # Rewrite the Info.plist.in to contain the correct version
    file(READ ${CPACK_BUNDLE_PLIST_SOURCE} INFO_PLIST_CONTENT)
    string(REPLACE "#CPACK_PACKAGE_VERSION#" "20230414-stock_jgr-g9e33bad646" INFO_PLIST_CONTENT "${INFO_PLIST_CONTENT}")
    file(WRITE ${CPACK_BUNDLE_PLIST} "${INFO_PLIST_CONTENT}")
endif (CPACK_BUNDLE_PLIST_SOURCE)
