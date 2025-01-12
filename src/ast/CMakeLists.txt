add_subdirectory(expressions)
add_subdirectory(statements)

target_link_libraries (
    statements
    PRIVATE
        expressions
)

add_library (
    ast
    INTERFACE
)

target_link_libraries (
    ast
    INTERFACE
        statements
        expressions
)
