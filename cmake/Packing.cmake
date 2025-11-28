install(TARGETS ${PROJECT_NAME} DESTINATION bin COMPONENT main)

install(FILES packaging/tray-pumpkin.desktop
        DESTINATION share/applications COMPONENT main)

install(FILES packaging/icons/tray-pumpkin.png
        DESTINATION share/icons/hicolor/48x48/apps COMPONENT main)

install(FILES packaging/default-config.yaml
        DESTINATION share/tray-pumpkin COMPONENT main)

install(FILES packaging/icons/tray-pumpkin.png
        DESTINATION share/tray-pumpkin/icons COMPONENT main)

install(FILES packaging/icons/tray-pumpkin-green.png
        DESTINATION share/tray-pumpkin/icons COMPONENT main)

install(FILES packaging/install.sh
        DESTINATION . 
        PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE
        COMPONENT installer_script)

set(CPACK_ARCHIVE_COMPONENT_INSTALL OFF)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE ON)
set(CPACK_COMPONENTS_ALL main)

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