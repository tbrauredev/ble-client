#===============================================================================
# Local Variables
#===============================================================================
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(GEN_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(HDRS
    "${SRC_DIR}/bluetooth_controller.h"
    "${SRC_DIR}/characteristics_model.h"
    "${SRC_DIR}/descriptors_model.h"
    "${SRC_DIR}/devices_model.h"
    "${SRC_DIR}/globals.h"
    "${SRC_DIR}/log_entry.h"
    "${SRC_DIR}/log_entry_p.h"
    "${SRC_DIR}/logger.h"
    "${SRC_DIR}/logger_model.h"
    "${SRC_DIR}/services_model.h"
    "${SRC_DIR}/settings.h"
)

set(SRCS
    "${SRC_DIR}/bluetooth_controller.cpp"
    "${SRC_DIR}/characteristics_model.cpp"
    "${SRC_DIR}/descriptors_model.cpp"
    "${SRC_DIR}/devices_model.cpp"
    "${SRC_DIR}/globals.cpp"
    "${SRC_DIR}/log_entry.cpp"
    "${SRC_DIR}/logger.cpp"
    "${SRC_DIR}/logger_model.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/services_model.cpp"
    "${SRC_DIR}/settings.cpp"
)

set(GEN_SRCS
    "${GEN_SRC_DIR}/version.h"
)

set(QRC_FILES
    "${SRC_DIR}/res.qrc"
)

#===============================================================================
# Preprocessing
#===============================================================================
configure_file(
    "${SRC_DIR}/version.h.in"
    "${GEN_SRC_DIR}/version.h"
    @ONLY
)

qt6_wrap_cpp(MOC_SRCS
        ${HDRS}
    TARGET
        ble-client
    OPTIONS
        --no-notes
)

qt6_add_resources(QRC_SRCS
    ${QRC_FILES}
)

#===============================================================================
# Targets
#===============================================================================
add_executable(ble-client WIN32
    ${HDRS}
    ${SRCS}
    ${GEN_SRCS}
    ${MOC_SRCS}
    ${QRC_SRCS}
)

target_link_libraries(ble-client
    PRIVATE
        Qt6::QuickControls2
        Qt6::Qml
        Qt6::Gui
        Qt6::Bluetooth
        Qt6::Core
)

target_include_directories(ble-client
    PRIVATE
        ${SRC_DIR}
        ${GEN_SRC_DIR}
)

#===============================================================================
# Install
#===============================================================================
install(TARGETS
        ble-client
    RUNTIME
        DESTINATION
            "bin"
)
