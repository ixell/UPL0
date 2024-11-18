cmake_minimum_required (VERSION 3.13)

project (UPL VERSION 0.2)

add_subdirectory (src)

find_package(GTest REQUIRED)
if (GTEST_FOUND)
	enable_testing ()
	add_subdirectory (tests)

	target_include_directories (
		tests
		PRIVATE
			lexer
			token
	)

	target_link_libraries (
		tests
		PRIVATE
			${GTEST_BOTH_LIBRARIES}
			lexer
	)
	
	add_test (
		NAME check
		COMMAND tests
	)
else (GTEST_FOUND)
	message (STATUS "GTest not found. Tests will not run.")
endif (GTEST_FOUND)
