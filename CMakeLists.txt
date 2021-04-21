cmake_minimum_required(VERSION 3.1.0)

project(DataMiningToolbox VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#zahtevamo da Qt bude instaliran na sistemu
find_package(Qt5 COMPONENTS Core REQUIRED Gui REQUIRED Widgets REQUIRED)

#zahtevamo da Armadillo bude instaliran na sistemu
find_package(Armadillo REQUIRED)

#-------------------------------- PREUZETO SA ZVANICNOG MLPACK REPOZITORIJUMA ------------------------------------
#-------------------- (https://github.com/mlpack/models/blob/master/CMake/FindMLPACK.cmake) ----------------------
#------------------------ PROVERAVA DA LI JE MLPACK BIBLIOTEKA PRISUTNA NA RACUNARU ------------------------------

# This module sets the following variables::
#
#   MLPACK_FOUND - set to true if the library is found
#   MLPACK_INCLUDE_DIRS - list of required include directories
#   MLPACK_LIBRARIES - list of libraries to be linked
#   MLPACK_VERSION_MAJOR - major version number
#   MLPACK_VERSION_MINOR - minor version number
#   MLPACK_VERSION_PATCH - patch version number
#   MLPACK_VERSION_STRING - version number as a string (ex: "1.0.4")

include(FindPackageHandleStandardArgs)

# UNIX paths are standard, no need to specify them.
find_library(MLPACK_LIBRARY
    NAMES mlpack
    PATHS "$ENV{ProgramFiles}/mlpack/lib"  "$ENV{ProgramFiles}/mlpack/lib64" "$ENV{ProgramFiles}/mlpack"
)
find_path(MLPACK_INCLUDE_DIR
    NAMES mlpack/core.hpp mlpack/prereqs.hpp
    PATHS "$ENV{ProgramFiles}/mlpack"
)

find_package_handle_standard_args(MLPACK
    REQUIRED_VARS MLPACK_LIBRARY MLPACK_INCLUDE_DIR
)

if(MLPACK_FOUND)
    set(MLPACK_INCLUDE_DIRS ${MLPACK_INCLUDE_DIR})
    set(MLPACK_LIBRARIES ${MLPACK_LIBRARY})
endif()

# Hide internal variables
mark_as_advanced(
    MLPACK_INCLUDE_DIR
    MLPACK_LIBRARY
)
#----------------------------------------------------------------------------------------------------

#ako mlpack biblioteka nije pronadjena na sistemu javljamo gresku
if(NOT MLPACK_FOUND)
    message( FATAL_ERROR "Mlpack not found!" )
endif()
 
include_directories(${MLPACK_INCLUDE_DIRS})

set(SOURCES
  ClassificationNode.cpp
  ClusteringNode.cpp
  DBSCANNode.cpp
  ConnectionLine.cpp
  DataTable.cpp
  DecisionTreeNode.cpp
  DecisionTreeParametersDialog.cpp
  FilterNode.cpp
  FilterParametersDialog.cpp
  KMeansNode.cpp
  KMeansParametersDialog.cpp
  LinearRegressionNode.cpp
  LinearRegressionParametersDialog.cpp
  LinearSVMNode.cpp
  Node.cpp
  NormalizationNode.cpp
  PartitionParametersDialog.cpp
  PerceptronNode.cpp
  PartitionNode.cpp
  PerceptronParametersDialog.cpp
  SamplingNode.cpp
  SamplingParametersDialog.cpp
  SceneNode.cpp
  SourceParametersDialog.cpp
  StatisticsNode.cpp
  Stream.cpp
  TableDialog.cpp
  main.cpp
  SourceNode.cpp
  csvreader.cpp
  MainWindow.cpp
)

set(FORMS
  DecisionTreeParametersDialog.ui
  FilterParametersDialog.ui
  KMeansParametersDialog.ui
  LinearRegressionParametersDialog.ui
  MainWindow.ui
  PartitionParametersDialog.ui
  PerceptronParametersDialog.ui
  SamplingParametersDialog.ui
  SourceParametersDialog.ui
  TableDialog.ui
)

set(RESOURCES Resources.qrc)

add_executable(DataMiningToolbox
    ${SOURCES}
    ${FORMS}
    ${RESOURCES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#opcije za generisanje gcov izvestaja
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs")

#specifikujemo gde se nalaze .hpp fajlovi
target_include_directories(DataMiningToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#linkujemo sa Qt bibliotekom
target_link_libraries(DataMiningToolbox Qt5::Core Qt5::Widgets Qt5::Gui)

#linkujemo sa Armadillo bilbiotekom
target_link_libraries(DataMiningToolbox armadillo lapack blas)

#linkujemo sa mlpack bibliotekom
target_link_libraries(DataMiningToolbox ${MLPACK_LIBRARIES})
