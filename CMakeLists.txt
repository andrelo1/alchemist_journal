cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

project(AlchemistJournal VERSION 1.3.0.0)

find_package(CommonLibSSE REQUIRED)
find_package(Detours REQUIRED)
find_package(nlohmann_json REQUIRED)

configure_file(cmake/version.h.in version.h)
configure_file(cmake/version.rc.in version.rc)

add_library("${PROJECT_NAME}" SHARED)

target_sources("${PROJECT_NAME}"
	PRIVATE
	src/main.cpp
	src/pch.h
	"${PROJECT_BINARY_DIR}/version.h"
	"${PROJECT_BINARY_DIR}/version.rc"
	src/init.h
	src/init.cpp
	src/Journal.h
	src/Journal.cpp
	src/JournalData.h
	src/JournalData.cpp
	src/Offsets.h
	src/BookMenu.h
	src/BookMenu.cpp
	src/Settings.h
	src/Settings.cpp
	src/SettingsPapyrus.h
	src/SettingsPapyrus.cpp
)

target_precompile_headers("${PROJECT_NAME}"
	PRIVATE
	src/pch.h
)

target_compile_features("${PROJECT_NAME}"
	PRIVATE
	cxx_std_23
)

target_include_directories("${PROJECT_NAME}"
	PRIVATE
	"${PROJECT_BINARY_DIR}"
)

target_link_libraries("${PROJECT_NAME}"
	PRIVATE
	CommonLibSSE::CommonLibSSE
	Detours::Detours
	nlohmann_json::nlohmann_json
)

install(TARGETS "${PROJECT_NAME}" RUNTIME DESTINATION "${SKYRIM_ROOT}/data/skse/plugins")