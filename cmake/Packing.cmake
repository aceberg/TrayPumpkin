install(TARGETS ${PROJECT_NAME} DESTINATION bin)

install(FILES packaging/tray-pumpkin.desktop
        DESTINATION share/applications)

install(FILES packaging/icons/tray-pumpkin.png
        DESTINATION share/icons/hicolor/48x48/apps)

set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_PACKAGE_NAME "tray-pumpkin")
set(CPACK_PACKAGE_VERSION "0.1.3")
set(CPACK_PACKAGE_CONTACT "Andrew Erlikh <aceberg_a@proton.me>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrew Erlikh")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libqt5widgets5, libqt5gui5, libqt5core5a, libkf5notifications5, libyaml-cpp0.7 | libyaml-cpp0.8"
)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "configurable tray icon and menu")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/aceberg/TrayPumpkin")

# Naming of archives
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}"
)

include(CPack)