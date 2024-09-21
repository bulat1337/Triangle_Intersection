cmake_minimum_required(VERSION 3.13)

project(Main)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_LOGGING "Enable logging" ON)
option(DEBUG "Debug version" ON)
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
	-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
)

# ----- executable -----

add_executable(intersect.x ./main.cpp)
target_include_directories(intersect.x PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src)

if(ENABLE_LOGGING)
	target_compile_definitions(intersect.x PRIVATE ENABLE_LOGGING)
endif()

if(DEBUG)
	target_compile_options(intersect.x PRIVATE ${DEBUG_COMPILE_OPTIONS})

	target_link_options(intersect.x PRIVATE
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
	)
else()
	target_compile_options(intersect.x PRIVATE ${RELEASE_COMPILE_OPTIONS})
endif()


# ----- tests -----
set(TESTS ./tests)

file(GLOB testfiles "${TESTS}/*.dat")
file(GLOB_RECURSE subfolder_testfiles "${TESTS}/**/*.dat")
list(APPEND testfiles ${subfolder_testfiles})

foreach(file ${testfiles})
	add_test(
		NAME ${file}
		COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${file} ./intersect.x"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
	set_tests_properties(${file} PROPERTIES DEPENDS intersect.x)
endforeach()

if(ENABLE_BIG_TESTS)
	set(BD_TESTS ./big_data_tests)

	file(GLOB big_data_tests "${BD_TESTS}/*.dat")
	file(GLOB_RECURSE bd_subfolder_testfiles "${BD_TESTS}/**/*.dat")
	list(APPEND big_data_tests ${bd_subfolder_testfiles})

	foreach(file ${big_data_tests})
		add_test(
			NAME bd_${file}
			COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${file} ./intersect.x"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
		set_tests_properties(bd_${file} PROPERTIES DEPENDS intersect.x)
	endforeach()
endif()
