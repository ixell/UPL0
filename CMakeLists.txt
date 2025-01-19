cmake_minimum_required (VERSION 3.13)

project (UPL VERSION 0.2)

add_compile_definitions (
	$<$<CONFIG:Debug>:DEBUG> $<$<NOT:$<CONFIG:Debug>>:NDEBUG> 
)

add_subdirectory (src)

add_subdirectory (tests)
