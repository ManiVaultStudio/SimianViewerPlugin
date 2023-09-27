cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0058 NEW) # suppress Ninja warning on Linux about /res files
set(PROJECT "SimianViewerPlugin")

PROJECT(${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32 /EHsc /MP /permissive- /Zc:__cplusplus")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif(MSVC)

file(TO_CMAKE_PATH $ENV{HDPS_INSTALL_DIR} INSTALL_DIR)

find_package(Qt6 COMPONENTS Widgets WebEngineWidgets REQUIRED)

qt6_add_resources(RESOURCE_FILES res/simian_viewer_resources.qrc)

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

add_library(${PROJECT} SHARED ${SOURCES} ${RESOURCES} ${RESOURCE_FILES} ${Data} ${Web} ${Common})

target_include_directories(${PROJECT} PRIVATE "${INSTALL_DIR}/$<CONFIGURATION>/include/")
target_include_directories(${PROJECT} PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_compile_features(${PROJECT} PRIVATE cxx_std_17)

set(HDPS_LINK_PATH "${INSTALL_DIR}/$<CONFIGURATION>/lib")
set(PLUGIN_LINK_PATH "${INSTALL_DIR}/$<CONFIGURATION>/$<IF:$<CXX_COMPILER_ID:MSVC>,lib,Plugins>")
set(HDPS_LINK_SUFFIX $<IF:$<CXX_COMPILER_ID:MSVC>,${CMAKE_LINK_LIBRARY_SUFFIX},${CMAKE_SHARED_LIBRARY_SUFFIX}>)

set(HDPS_LINK_LIBRARY "${HDPS_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}HDPS_Public${HDPS_LINK_SUFFIX}")
set(POINTDATA_LINK_LIBRARY "${PLUGIN_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}PointData${HDPS_LINK_SUFFIX}") 
set(CLUSTERDATA_LINK_LIBRARY "${PLUGIN_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}ClusterData${HDPS_LINK_SUFFIX}") 

target_link_libraries(${PROJECT} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT} PRIVATE Qt6::WebEngineWidgets)
target_link_libraries(${PROJECT} PRIVATE "${HDPS_LINK_LIBRARY}")
target_link_libraries(${PROJECT} PRIVATE "${POINTDATA_LINK_LIBRARY}")
target_link_libraries(${PROJECT} PRIVATE "${CLUSTERDATA_LINK_LIBRARY}")

install(TARGETS ${PROJECT}
    RUNTIME DESTINATION Plugins COMPONENT PLUGINS # Windows .dll
    LIBRARY DESTINATION Plugins COMPONENT PLUGINS # Linux/Mac .so
)

add_custom_command(TARGET ${PROJECT} POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
        --install ${CMAKE_CURRENT_BINARY_DIR}
        --config $<CONFIGURATION>
        --prefix ${INSTALL_DIR}/$<CONFIGURATION>
)

# Automatically set the debug environment (command + working directory) for MSVC
if(MSVC)
	set_property(TARGET ${PROJECT} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<IF:$<CONFIG:DEBUG>,${INSTALL_DIR}/debug,${INSTALL_DIR}/release>)
    set_property(TARGET ${PROJECT} PROPERTY VS_DEBUGGER_COMMAND $<IF:$<CONFIG:DEBUG>,${INSTALL_DIR}/debug/HDPS.exe,${INSTALL_DIR}/release/HDPS.exe>)
endif()
