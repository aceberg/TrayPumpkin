install(TARGETS ${PROJECT_NAME} DESTINATION bin)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "tray-pumpkin")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_CONTACT "Andrew Erlikh <aceberg_a@proton.me>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrew Erlikh")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qtbase5-dev, libkf5notifications-dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Tray Pumpkin App")

include(CPack)