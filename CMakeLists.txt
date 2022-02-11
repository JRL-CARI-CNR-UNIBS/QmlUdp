cmake_minimum_required(VERSION 3.5)

project(socket_qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-std=c++11 -funroll-loops -Wall -Ofast)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)


SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.40.0 REQUIRED system thread regex)
find_package( OpenCV REQUIRED )


#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick  LinguistTools Multimedia REQUIRED)


include_directories(
   ${Boost_INCLUDE_DIRS}
)

SET(APP_FILES
  qml.qrc
  main.cpp
  QmlUdpReceiver.cpp
  QmlUdpSender.cpp
  UdpVideoStream.cpp
  PracticalSocket.cpp
  )

if(ANDROID)
    add_library(socket_qml SHARED
      ${APP_FILES}
    )
else()
    add_executable(socket_qml
      ${APP_FILES}
    )
endif()

target_compile_definitions(socket_qml
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(socket_qml
  PRIVATE Qt5::Core Qt5::Quick Qt5::Multimedia ${Boost_LIBRARIES} ${OpenCV_LIBS} )
