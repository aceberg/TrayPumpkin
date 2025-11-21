install(TARGETS ${PROJECT_NAME} DESTINATION bin)

set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_PACKAGE_NAME "tray-pumpkin")
set(CPACK_PACKAGE_VERSION "0.1.2")
set(CPACK_PACKAGE_CONTACT "Andrew Erlikh <aceberg_a@proton.me>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrew Erlikh")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qtbase5-dev, libkf5notifications-dev, libyaml-cpp-dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "configurable tray icon and menu")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/aceberg/TrayPumpkin")

# Naming of archives
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}"
)

include(CPack)