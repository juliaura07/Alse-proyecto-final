cmake_minimum_required(VERSION 3.5)

project(IoTConfigManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar Qt (Qt6 o Qt5) con Widgets y Sql
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Indicar dónde buscar archivos .ui
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Incluir el directorio de headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Definir los archivos del proyecto con sus rutas correctas
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    ui/mainwindow.ui
    
    src/databasemanager.cpp
    include/databasemanager.h
    
    src/user.cpp
    include/user.h
    
    src/device.cpp
    include/device.h
    
    src/devicemanager.cpp
    include/devicemanager.h
    
    src/loginmanager.cpp
    include/loginmanager.h
    
    src/loginwindow.cpp
    include/loginwindow.h
    ui/loginwindow.ui
    
    src/adddevicedialog.cpp
    include/adddevicedialog.h
    ui/adddevicedialog.ui
    
    src/registerwindow.cpp
    include/registerwindow.h
    ui/registerwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(IoTConfigManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(IoTConfigManager SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(IoTConfigManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Linkear con los módulos Qt
target_link_libraries(IoTConfigManager
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

# Propiedades específicas para macOS/iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.IoTConfigManager)
endif()

set_target_properties(IoTConfigManager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS IoTConfigManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(IoTConfigManager)
endif()