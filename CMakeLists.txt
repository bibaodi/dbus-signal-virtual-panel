cmake_minimum_required(VERSION 3.5)

project(qt-quick-cpp4qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(${bin}_public_headers)
set(X11_LIB_SEARCH_PATH
    /usr/pkg/xorg/lib
    /usr/X11R6/lib
    /usr/X11R7/lib
    /usr/openwin/lib
    /usr/lib
  )
#CONFIG += qmltypes
#QML_IMPORT_NAME = io.qt.examples.backend
#QML_IMPORT_MAJOR_VERSION = 1

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
find_package(Qt5Gui)
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

find_package(Qt5 COMPONENTS Core Quick REQUIRED Widgets)
#for glog
find_package (glog 0.4.0 REQUIRED)
#for x11
find_package(X11)

if(ANDROID)
    add_library(qt-quick-cpp4qml SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(qt-quick-cpp4qml
      main.cpp
      qml.qrc
      backend.cpp
      #event_filter.cpp
    )
endif()

target_compile_definitions(qt-quick-cpp4qml
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qt-quick-cpp4qml
  PRIVATE Qt5::Core Qt5::Quick glog::glog ${X11_LIBRARIES})
