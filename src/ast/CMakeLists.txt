add_subdirectory(expressions)
add_subdirectory(statements)

target_link_libraries (
    statements
    PRIVATE
        expressions
)
