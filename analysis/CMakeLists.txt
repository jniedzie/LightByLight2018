cmake_minimum_required (VERSION 2.6)
project (LightByLight)

find_package(ROOT REQUIRED COMPONENTS Minuit Eve Geom)
include(${ROOT_USE_FILE})

set_property(TARGET ROOT::Core PROPERTY
INTERFACE_INCLUDE_DIRECTORIES "${ROOT_INCLUDE_DIRS}")

add_library(ROOT::Flags_CXX IMPORTED INTERFACE)

# Fix for ROOT_CXX_FLAGS not actually being a CMake list
separate_arguments(ROOT_CXX_FLAGS)
set_property(TARGET ROOT::Flags_CXX APPEND PROPERTY
INTERFACE_COMPILE_OPTIONS ${ROOT_CXX_FLAGS})

# Add definitions
separate_arguments(ROOT_DEFINITIONS)
foreach(_flag ${ROOT_EXE_LINKER_FLAG_LIST})
# Remove -D or /D if present
string(REGEX REPLACE [=[^[-//]D]=] "" _flag ${_flag})
set_property(TARGET ROOT::Flags APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${_flag})
endforeach()

# This also fixes a bug in the linker flags
string(REPLACE "-L " "-L" ROOT_EXE_LINKER_FLAGS "${ROOT_EXE_LINKER_FLAGS}")
separate_arguments(ROOT_EXE_LINKER_FLAGS)
set_property(TARGET ROOT::Flags_CXX APPEND PROPERTY
INTERFACE_LINK_LIBRARIES ${ROOT_EXE_LINKER_FLAGS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_executable(getEfficienciesLbL getEfficienciesLbL.cpp)
add_executable(getEfficienciesQED getEfficienciesQED.cpp)
add_executable(preparePhtonIDplots preparePhtonIDplots.cpp)
add_executable(prepareBasicPlots prepareAcoplanarityPlots.cpp)

set_property(TARGET getEfficienciesLbL PROPERTY CXX_STANDARD 17)
set_property(TARGET getEfficienciesQED PROPERTY CXX_STANDARD 17)
set_property(TARGET preparePhtonIDplots PROPERTY CXX_STANDARD 17)
set_property(TARGET prepareBasicPlots PROPERTY CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(Analysis  src/Event.cpp
                      src/EventProcessor.cpp
                      src/PhysObject.cpp
                      src/PhysObjectProcessor.cpp
                      src/ConfigManager.cpp
)

set_property(TARGET Analysis PROPERTY CXX_STANDARD 17)

target_link_libraries(getEfficienciesLbL Analysis ${ROOT_LIBRARIES})
target_link_libraries(getEfficienciesQED Analysis ${ROOT_LIBRARIES})
target_link_libraries(preparePhtonIDplots Analysis ${ROOT_LIBRARIES})
target_link_libraries(prepareBasicPlots Analysis ${ROOT_LIBRARIES})
