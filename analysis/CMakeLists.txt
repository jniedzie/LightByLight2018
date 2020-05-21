cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project (LightByLight)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS Minuit Eve Geom)
include(${ROOT_USE_FILE})

SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
SET(CMAKE_INSTALL_RPATH "/cvmfs/sft.cern.ch/lcg/releases/vdt/0.4.3-992df/x86_64-centos7-gcc8-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/tbb/2019_U7-ba3eb/x86_64-centos7-gcc8-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/Davix/0.7.3-d94fa/x86_64-centos7-gcc8-opt/lib64/:/cvmfs/sft.cern.ch/lcg/releases/png/1.6.37-9c2fe/x86_64-centos7-gcc8-opt/lib/:/cvmfs/sft.cern.ch/lcg/releases/GSL/2.5-32fc5/x86_64-centos7-gcc8-opt/lib/")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(getEfficienciesLbL getEfficienciesLbL.cpp)
add_executable(getEfficienciesQED getEfficienciesQED.cpp)
add_executable(preparePhotonIDplots preparePhotonIDplots.cpp)
add_executable(prepareElectronIDplots prepareElectronIDplots.cpp)
add_executable(prepareBasicPlots prepareBasicPlots.cpp)
add_executable(applySelections applySelections.cpp)
add_executable(runDumpEvent runDumpEvent.cpp)
add_executable(runEventList runEventList.cpp)
add_executable(addPixelTrackInfo addPixelTrackInfo.cpp)
add_executable(prepareTauTauPlots prepareTauTauPlots.cpp)

set_property(TARGET getEfficienciesLbL PROPERTY CXX_STANDARD 17)
set_property(TARGET getEfficienciesQED PROPERTY CXX_STANDARD 17)
set_property(TARGET preparePhotonIDplots PROPERTY CXX_STANDARD 17)
set_property(TARGET prepareElectronIDplots PROPERTY CXX_STANDARD 17)
set_property(TARGET prepareBasicPlots PROPERTY CXX_STANDARD 17)
set_property(TARGET applySelections PROPERTY CXX_STANDARD 17)
set_property(TARGET runDumpEvent PROPERTY CXX_STANDARD 17)
set_property(TARGET runEventList PROPERTY CXX_STANDARD 17)
set_property(TARGET addPixelTrackInfo PROPERTY CXX_STANDARD 17)
set_property(TARGET prepareTauTauPlots  PROPERTY CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(Analysis  src/Event.cpp
                      src/EventProcessor.cpp
                      src/PhysObject.cpp
                      src/PhysObjectProcessor.cpp
                      src/ConfigManager.cpp
                      src/DumpEvent.cpp
)

set_property(TARGET Analysis PROPERTY CXX_STANDARD 17)

target_link_libraries(getEfficienciesLbL Analysis ${ROOT_LIBRARIES})
target_link_libraries(getEfficienciesQED Analysis ${ROOT_LIBRARIES})
target_link_libraries(preparePhotonIDplots Analysis ${ROOT_LIBRARIES})
target_link_libraries(prepareElectronIDplots Analysis ${ROOT_LIBRARIES})
target_link_libraries(prepareBasicPlots Analysis ${ROOT_LIBRARIES})
target_link_libraries(applySelections Analysis ${ROOT_LIBRARIES})
target_link_libraries(runDumpEvent Analysis ${ROOT_LIBRARIES})
target_link_libraries(runEventList Analysis ${ROOT_LIBRARIES})
target_link_libraries(addPixelTrackInfo Analysis ${ROOT_LIBRARIES})
target_link_libraries(prepareTauTauPlots Analysis ${ROOT_LIBRARIES})

