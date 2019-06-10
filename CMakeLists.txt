cmake_minimum_required(VERSION 3.2)
project(stm-32f103c8-oled)

include(CMakeListsPrivate.txt)
include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/framework-stm32cube/f1/Drivers/STM32F1xx_HAL_Driver/Src")
include_directories("$ENV{HOME}/.platformio/packages/framework-stm32cube/f1/Drivers/STM32F1xx_HAL_Driver/Src")

include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/gGFX/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/mGFX/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/MonoLCD/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/PE_SSD1306/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/PE_Ticker/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/SSD1306/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/Timeout/src")

include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/EEPROM_Emulation/inc")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/EEPROM_Emulation/src")

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_BUILD_VERBOSE ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --verbose
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_MONITOR ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion device monitor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_TEST ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_REBUILD_PROJECT_INDEX ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion init --ide clion
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
