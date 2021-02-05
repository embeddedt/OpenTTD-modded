# Make the current version available to CPack
set(CPACK_PACKAGE_VERSION "20210205-stock_jgr-g1bac34fb7d")

# Name the output file with the correct version
string(REPLACE "#CPACK_PACKAGE_VERSION#" "20210205-stock_jgr-g1bac34fb7d" CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}")

if (CPACK_BUNDLE_PLIST_SOURCE)
    # Rewrite the Info.plist.in to contain the correct version
    file(READ ${CPACK_BUNDLE_PLIST_SOURCE} INFO_PLIST_CONTENT)
    string(REPLACE "#CPACK_PACKAGE_VERSION#" "20210205-stock_jgr-g1bac34fb7d" INFO_PLIST_CONTENT "${INFO_PLIST_CONTENT}")
    file(WRITE ${CPACK_BUNDLE_PLIST} "${INFO_PLIST_CONTENT}")
endif (CPACK_BUNDLE_PLIST_SOURCE)
