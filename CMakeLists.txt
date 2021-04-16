cmake_minimum_required(VERSION 3.14)

project(virtualCtrlPanel LANGUAGES CXX)

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

#find_package(Qt5Gui)
find_package(QT NAMES Qt5 COMPONENTS Core DBus REQUIRED)
find_package(Qt5 COMPONENTS Core Quick Gui Qml DBus REQUIRED)
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
#for glog
find_package (glog 0.4.0 REQUIRED)
#for gtest
#find_package(GTest CONFIG REQUIRED)
#for x11
#find_package(X11)
#for global key_shortcuts
#find_package(qxtglobalshortcut REQUIRED)

set(exe virtual_panel.exe)
aux_source_directory(. CPP_FILES)
file (GLOB H_Files "./*.h")
message("My H_Files: " ${H_Files})

add_executable(${exe}
      qml.qrc
      ${CPP_FILES}
      ${H_Files})

target_compile_definitions(${exe}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${exe}
  PRIVATE Qt5::Core Qt5::Quick glog::glog Qt5::DBus)
#below command can only appear once!!!
#target_link_libraries(${exe} qxtglobalshortcut)
#target_link_libraries(${exe} Qt5::Widgets)
