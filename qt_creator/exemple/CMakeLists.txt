cmake_minimum_required(VERSION 2.8.9)
project(Koch)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

set(SRCS
	main.cpp
	widget.cpp
	controles.cpp
	processeur.cpp
)

set(HDRS
	widget.h
	controles.h
	processeur.h
)

qt5_wrap_ui(UIS_HDRS controles.ui)

add_executable(koch
		${SRCS}
		${HDRS}
		${UIS_HDRS}
)

qt5_use_modules(koch Widgets)
