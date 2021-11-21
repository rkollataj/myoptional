set(SRC
    myoptional_test.cpp
)

add_executable(myoptional_test ${SRC})
target_link_libraries(myoptional_test PRIVATE myoptional Catch2::Catch2WithMain)
add_test(NAME myoptional_test COMMAND myoptional_test)
