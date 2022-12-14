cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "HCache")
set (BUILD_DIR ./build)

project(${PACKAGE_NAME})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SQLiteCpp/include
	)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(HCACHE_SRC
			${CMAKE_CURRENT_SOURCE_DIR}/src/CacheValue.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/DiskStorage.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/KVSingleton.cpp
			)

	set(HCACHE_INC
			${CMAKE_CURRENT_SOURCE_DIR}/include/CacheValue.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/include/DiskStorage.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/include/KVSingleton.hpp
			)
else()
	set(HCACHE_SRC
			${CMAKE_CURRENT_SOURCE_DIR}/src/CacheValue.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/DiskStorage.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/KVSingleton.cpp
			)

	set(HCACHE_INC
			${CMAKE_CURRENT_SOURCE_DIR}/include/CacheValue.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/include/DiskStorage.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/include/KVSingleton.hpp)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
	add_library(
		${PACKAGE_NAME}
		STATIC
		${HCACHE_SRC}
		${HCACHE_INC}
		)
else()
	add_library(
		${PACKAGE_NAME}
		SHARED
        ${HCACHE_SRC}
        ${HCACHE_INC}
		)
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SQLiteCpp)

set_target_properties(
	${PACKAGE_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	POSITON_INDEPENDENT ON
	)
if (CMAKE_SYSTEM_NAME MATCHES "Android")
	find_library(log-lib log)
	target_link_libraries(
			${PACKAGE_NAME}
			${log-lib}
			SQLiteCpp
	)
else()
	target_link_libraries(
			${PACKAGE_NAME}
			SQLiteCpp
	)
endif()
