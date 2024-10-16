cmake_minimum_required(VERSION 3.14)

project(Main)

enable_testing()
add_subdirectory(unit_tests/)
add_subdirectory(${CMAKE_SOURCE_DIR}/unit_tests/test_utils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_LOGGING "Enable logging" OFF)
option(DEBUG "Debug version" OFF)
option(ENABLE_BIG_TESTS "Enables big data tests" OFF)

set(RELEASE_COMPILE_OPTIONS
	-O2
	-fstack-protector
	-fPIE
	-fstrict-overflow
	-Wformat-security
	-Wformat=2
	-Wall
	-Wextra
	-Wnon-virtual-dtor
	-Woverloaded-virtual
	-Wcast-align
	-Wpointer-arith
	-Wunreachable-code
	-Wno-pre-c++17-compat
)

set(DEBUG_COMPILE_OPTIONS
	-D_DEBUG
	-ggdb3
	-O0
	-Wall
	-Wextra
	-Weffc++
	-Wc++14-compat
	-Wmissing-declarations
	-Wcast-align
	-Wcast-qual
	-Wchar-subscripts
	-Wconversion
	-Wctor-dtor-privacy
	-Wempty-body
	-Wfloat-equal
	-Wformat-security
	-Winline
	-Wnon-virtual-dtor
	-Woverloaded-virtual
	-Wpacked
	-Wpointer-arith
	-Winit-self
	-Wredundant-decls
	-Wshadow
	-Wsign-conversion
	-Wsign-promo
	-Wstrict-overflow=2
	-Wsuggest-override
	-Wswitch-default
	-Wswitch-enum
	-Wundef
	-Wunreachable-code
	-Wunused
	-Wvariadic-macros
	-Wno-missing-field-initializers
	-Wno-narrowing
	-Wno-old-style-cast
	-Wno-varargs
	-Wstack-protector
	-fcheck-new
	-fsized-deallocation
	-fstack-protector
	-fstrict-overflow
	-fno-omit-frame-pointer
	-Wlarger-than=8192
	-fPIE
	-Werror=vla
	-Wno-pre-c++17-compat
	-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
)

# ----- intersects library -----

add_library(intersects STATIC
	src/intersects.cpp
	src/vec.cpp
	src/utils.cpp
	src/distances.cpp
	src/plane.cpp
	src/triangle.cpp
	src/multi_inter.cpp
	src/bounding_box.cpp
	src/segment.cpp)

target_include_directories(intersects PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/utils/include)

if(ENABLE_LOGGING)
	target_compile_definitions(intersects PRIVATE ENABLE_LOGGING)
endif()

if(DEBUG)
	target_compile_options(intersects PRIVATE ${DEBUG_COMPILE_OPTIONS})
	target_compile_definitions(intersects PRIVATE DEBUG)

	target_link_options(intersects PRIVATE
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
	)
else()
	target_compile_options(intersects PRIVATE ${RELEASE_COMPILE_OPTIONS})
endif()

# ----- executable -----

add_executable(intersect.x ./main.cpp)
target_include_directories(intersect.x PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/utils/include)

if(ENABLE_LOGGING)
	target_compile_definitions(intersect.x PRIVATE ENABLE_LOGGING)
endif()

if(DEBUG)
	target_compile_definitions(intersect.x PRIVATE DEBUG)
	target_compile_options(intersect.x PRIVATE ${DEBUG_COMPILE_OPTIONS})

	target_link_options(intersect.x PRIVATE
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
	)
else()
	target_compile_options(intersect.x PRIVATE ${RELEASE_COMPILE_OPTIONS})
endif()

target_link_libraries(intersect.x PRIVATE intersects)

