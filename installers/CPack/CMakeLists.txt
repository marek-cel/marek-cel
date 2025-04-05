cmake_minimum_required(VERSION 3.10)
project(HelloCPack VERSION 1.0.0)

# Create the executable
add_executable(hello main.cpp)

# Install rules
install(TARGETS hello DESTINATION bin)

# Required for some platforms
include(InstallRequiredSystemLibraries)

# CPack configuration
set(CPACK_PACKAGE_NAME "HelloCPack")
set(CPACK_PACKAGE_VENDOR "MyCompany")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple Hello World program using CPack")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH 0)

# Choose one or more generators
set(CPACK_GENERATOR "WIX") # you can change this to DEB, RPM, NSIS, etc.

include(CPack)