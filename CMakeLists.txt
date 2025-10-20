cmake_minimum_required(VERSION 3.22)

option(MV_UNITY_BUILD "Combine target source files into batches for faster compilation" OFF)

# -----------------------------------------------------------------------------
# ChartLegendView Plugin
# -----------------------------------------------------------------------------
project(SimianViewerPlugin)

# -----------------------------------------------------------------------------
# CMake Options
# -----------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32 /EHsc /MP /permissive- /Zc:__cplusplus")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif(MSVC)

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------
find_package(Qt6 COMPONENTS Widgets WebEngineWidgets REQUIRED)

find_package(ManiVault COMPONENTS Core PointData ClusterData CONFIG QUIET)

# -----------------------------------------------------------------------------
# Source files
# -----------------------------------------------------------------------------
# Define the plugin sources
set(SOURCES
    src/SimianViewerPlugin.h
    src/SimianViewerPlugin.cpp
    src/SimianViewerWidget.h
    src/SimianViewerWidget.cpp
    src/SimianViewerPlugin.json
)

set (RESOURCES
    res/simian_viewer_resources.qrc
)
set (Web
    res/simian_viewer/simian_viewer.html
	res/simian_viewer/simian_viewer.js
	res/simian_viewer/simian_viewer.css
)


set(Data
#    src/Data/chimp_gorilla.txt
#	src/Data/chimp_marmoset.txt
#    src/Data/chimp_rhesus.txt
#	src/Data/gorilla_marmoset.txt
#    src/Data/gorilla_rhesus.txt
#	src/Data/human_chimp.txt
#	src/Data/human_gorilla.txt
#    src/Data/human_marmoset.txt
#	src/Data/human_rhesus.txt
#    src/Data/rhesus_marmoset.txt
    src/Data/globalMetadata.h
	src/Data/globalMetadata.cpp
)

set(Common
#    src/Common/ChannelAction.cpp
#    src/Common/ChannelAction.h
#    src/Common/ChannelStylingAction.cpp
#    src/Common/ChannelStylingAction.h
    src/Common/SimianOptionsAction.cpp
    src/Common/SimianOptionsAction.h
# 	src/Common/OtherFilterSelectionAction.cpp
 #    src/Common/OtherFilterSelectionAction.h
# 	src/Common/ClusterSelectionAction.cpp
 #    src/Common/ClusterSelectionAction.h
# 	src/Common/SpeciesSelectionAction.cpp
#     src/Common/SpeciesSelectionAction.h
)


source_group( PluginFiles FILES ${SOURCES})
source_group( ResourceFiles FILES ${RESOURCES})
source_group( ResourceFiles\\generated FILES ${CMAKE_CURRENT_BINARY_DIR}/qrc_simian_viewer_resources.cpp)
source_group( DataFiles FILES ${Data})
source_group( WebFiles FILES ${Web})
source_group( ActionFiles FILES ${Common})

qt_add_resources(RESOURCE_FILES ${RESOURCES})
# -----------------------------------------------------------------------------
# CMake Target
# -----------------------------------------------------------------------------
# Create dynamic library for the plugin
add_library(${PROJECT_NAME} SHARED 
    ${SOURCES} 
    ${RESOURCE_FILES}  # This was missing
    ${Data} 
    ${Web} 
    ${Common}
)
# -----------------------------------------------------------------------------
# Target include directories
# -----------------------------------------------------------------------------
# Include ManiVault headers, including system data plugins
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src  # For SimianViewerPlugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Common  # For Common headers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Data  # For Data headers
    "${ManiVault_INCLUDE_DIR}"
)
# -----------------------------------------------------------------------------
# Target properties
# -----------------------------------------------------------------------------
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    FOLDER ViewPlugins
)


# Enable unity build
if(MV_UNITY_BUILD)
    set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)
endif()

# -----------------------------------------------------------------------------
# Target library linking
# -----------------------------------------------------------------------------
# Link to Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::WebEngineWidgets)

# Link to ManiVault and data plugins
target_link_libraries(${PROJECT_NAME} PRIVATE ManiVault::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE ManiVault::PointData)
target_link_libraries(${PROJECT_NAME} PRIVATE ManiVault::ClusterData)

# -----------------------------------------------------------------------------
# Target installation
# -----------------------------------------------------------------------------
# Install the shared plugin library to the "Plugins" folder in the ManiVault install directory
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION Plugins COMPONENT PLUGINS # Windows .dll
    LIBRARY DESTINATION Plugins COMPONENT PLUGINS # Linux/Mac .so
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
        --install ${CMAKE_CURRENT_BINARY_DIR}
        --config $<CONFIGURATION>
        --prefix ${ManiVault_INSTALL_DIR}/$<CONFIGURATION>
)

# -----------------------------------------------------------------------------
# Miscellaneous
# -----------------------------------------------------------------------------
# Automatically set the debug environment (command + working directory) for MSVC
if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<IF:$<CONFIG:DEBUG>,${ManiVault_INSTALL_DIR}/debug,${ManiVault_INSTALL_DIR}/release>)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_COMMAND $<IF:$<CONFIG:DEBUG>,${ManiVault_INSTALL_DIR}/debug/ManiVault\ Studio.exe,${ManiVault_INSTALL_DIR}/release/ManiVault\ Studio.exe>)
endif()
