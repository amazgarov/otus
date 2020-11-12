cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_subdirectory(${PROJECT_SOURCE_DIR}/gtest)
enable_testing()

include_directories(
    ${GTEST_INCLUDE_DIRS}
)

add_executable(ip_filter main.cpp)
add_library(ip_filter_lib ip_filter.cpp)

add_executable(tests tests.cpp)
add_dependencies(tests googletest)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

target_link_libraries(
    tests
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(tests
    PRIVATE "${CMAKE_BINARY_DIR}"
    ${GTEST_SOURCE_DIR}/include
    ${GTEST_SOURCE_DIR}
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(tests PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_custom_command(TARGET ip_filter POST_BUILD		# Adds a post-build event to ip_filter
	COMMAND ${CMAKE_COMMAND} -E copy_if_different	# which executes "cmake - E copy_if_different..."
		"${PROJECT_SOURCE_DIR}/ip_filter.tsv"		# <--this is in-file
		$<TARGET_FILE_DIR:ip_filter>)				# <--this is out-file path

set_target_properties(tests PROPERTIES
    PREFIX ""
    SUFFIX "")

add_test(NAME tests COMMAND tests)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS tests)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
