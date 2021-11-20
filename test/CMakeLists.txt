set(SRC
    myoptional_test.cpp
)

add_executable(myoptional_test ${SRC})
target_link_libraries(myoptional_test myoptional)
add_test(NAME myoptional_test COMMAND myoptional_test)
