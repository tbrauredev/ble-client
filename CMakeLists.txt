#===============================================================================
# Project
#===============================================================================
cmake_minimum_required(VERSION 3.17.4)
project(ble-client)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(common-options)
include(git-utils)

git_describe()
set(PROJECT_VERSION ${GIT_DESCRIBE_VERSION})
set(PROJECT_VERSION_MAJOR ${GIT_DESCRIBE_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${GIT_DESCRIBE_VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${GIT_DESCRIBE_VERSION_PATCH})

#===============================================================================
# Options
#===============================================================================

#===============================================================================
# External Packages
#===============================================================================
find_package(Qt6
    CONFIG
    REQUIRED
    COMPONENTS
        QuickControls2
        Qml
        Gui
        Bluetooth
        Core
    QUIET
)

#===============================================================================
# Subdirectories
#===============================================================================
add_subdirectory(src)
