cmake_minimum_required(VERSION 3.14)
project(nodeeditor)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt/5.15.0)

add_executable(nodeeditor main.cpp Converters.cpp MathOperationDataModel.cpp ModuloModel.cpp NumberDisplayDataModel.cpp NumberSourceDataModel.cpp)


find_package(Qt5Widgets REQUIRED)
if (Qt5Widgets_FOUND)
    message("-- Qt Widgets is Found")
    target_link_libraries(nodeeditor Qt5::Widgets)
endif ()

find_package(Qt5Core REQUIRED)
if (Qt5Core_FOUND)
    message("-- Qt Core is Found")
    target_link_libraries(nodeeditor Qt5::Core)
endif ()

find_package(Qt5Gui REQUIRED)
if (Qt5Core_FOUND)
    message("-- Qt Gui is Found")
    target_link_libraries(nodeeditor Qt5::Gui)
endif ()

find_package(Qt5Multimedia REQUIRED)
if (Qt5Multimedia_FOUND)
    message("-- Qt Multimedia is Found")
    target_link_libraries(nodeeditor Qt5::Multimedia)
endif ()

find_package(Qt5MultimediaWidgets REQUIRED)
if (Qt5MultimediaWidgets_FOUND)
    message("-- Qt MultimediaWidgets is Found")
    target_link_libraries(nodeeditor Qt5::MultimediaWidgets)
endif ()

# import nodeeditor library
include_directories(/Users/coskunyerli/Local/nodeeditor/include)
target_compile_definitions(nodeeditor
        PUBLIC
        NODE_EDITOR_SHARED)
# Burada libnodes.dylib dizini değişebilir
target_link_libraries(nodeeditor /Users/coskunyerli/Local/nodeeditor/build/lib/libnodes.dylib)


