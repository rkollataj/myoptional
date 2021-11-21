#include <catch2/catch_test_macros.hpp>
#include <myoptional.h>

struct DefClass {
    DefClass() = default;

    int mVal{ 123 };
};

struct NonDefClass {
    NonDefClass() = delete;

    NonDefClass(int val)
        : mVal(val)
    {
    }

    int mVal{ 234 };
};

// REQ: must be possible to check if error is present (provide nice impl for if usage)
// REQ: creating from Status must indicate error
// REQ: must have error getter
TEST_CASE("creation from status", "[basic]")
{
    auto checkStatus = [](auto& op, const Status s) {
        // operator bool()
        REQUIRE(!op);
        REQUIRE((op.status() == s));
        REQUIRE((op.operator->() == nullptr));

        // implicit cast
        Status s2 = op;
        REQUIRE(s == s2);

        // explicit cast
        Status s3 = static_cast<Status>(op);
        REQUIRE(s == s3);
    };

    myoptional<DefClass> op1 = Status::ERROR;
    checkStatus(op1, Status::ERROR);
    op1 = Status::INVALID_ARG;
    checkStatus(op1, Status::INVALID_ARG);
    op1 = Status::OK;
    checkStatus(op1, Status::INVALID_ARG);

    myoptional<DefClass> op2 = Status::OK;
    checkStatus(op2, Status::INVALID_ARG);

    auto statusFunc = []() -> myoptional<DefClass> { return Status::INVALID_ARG; };
    myoptional<DefClass> op3 = statusFunc();
    checkStatus(op3, Status::INVALID_ARG);
}

// REQ: creating from value must indicate success
// REQ: must have value getter
// REQ: value type can be default constructible
TEST_CASE("creating from value (default constructible)", "[basic]")
{
    auto checkStatus = [](auto& op, int val) {
        // operator bool()
        REQUIRE(op);
        REQUIRE((op.status() == Status::OK));
        REQUIRE((op.operator->() != nullptr));

        REQUIRE((op->mVal == val));
        REQUIRE(((*op).mVal == val));

        using ClassType = typename std::remove_reference_t<decltype(op)>::type;

        // implicit cast
        ClassType obj = op;
        REQUIRE((obj.mVal == val));

        // explicit cast
        auto obj2 = static_cast<ClassType>(op);
        REQUIRE((obj2.mVal == val));

        // Check if const is maintained in access operators
        REQUIRE(std::is_same<ClassType, std::remove_pointer_t<decltype(op.operator->())>>::value);
        REQUIRE(std::is_same<ClassType, std::remove_reference_t<decltype(*op)>>::value);
    };

    // will not compile (default constructor deleted)
    // myoptional<DefClass> op;

    myoptional<DefClass> op1 = DefClass();
    checkStatus(op1, 123);

    DefClass df1;
    df1.mVal = 666;
    myoptional<DefClass> op2(df1);
    checkStatus(op2, 666);

    myoptional<const DefClass> op3 = DefClass();
    checkStatus(op3, 123);

    DefClass df2;
    df2.mVal = 666;
    myoptional<const DefClass> op4(df2);
    checkStatus(op4, 666);
}

// REQ: value type does not need to be default constructible (most important feature)
TEST_CASE("creating from value (non-default constructible)", "[all-inclusive]")
{
    auto checkStatus = [](auto& op, int val) {
        // operator bool()
        REQUIRE(op);
        REQUIRE((op.status() == Status::OK));
        REQUIRE((op.operator->() != nullptr));

        REQUIRE((op->mVal == val));
        REQUIRE(((*op).mVal == val));

        using ClassType = typename std::remove_reference_t<decltype(op)>::type;

        // implicit cast
        ClassType obj = op;
        REQUIRE((obj.mVal == val));

        // explicit cast
        auto obj2 = static_cast<ClassType>(op);
        REQUIRE((obj2.mVal == val));

        // Check if const is maintained in access operators
        REQUIRE(std::is_same<ClassType, std::remove_pointer_t<decltype(op.operator->())>>::value);
        REQUIRE(std::is_same<ClassType, std::remove_reference_t<decltype(*op)>>::value);
    };

    myoptional<NonDefClass> op1 = NonDefClass(88);
    checkStatus(op1, 88);

    NonDefClass df1(666);
    myoptional<NonDefClass> op2(df1);
    checkStatus(op2, 666);

    myoptional<const NonDefClass> op3 = NonDefClass(88);
    checkStatus(op3, 88);

    NonDefClass df2(666);
    myoptional<const NonDefClass> op4(df2);
    checkStatus(op4, 666);
}

// REQ: constructors shall be compile-time disabled when they do not match
TEST_CASE("enable_if", "[all-inclusive]")
{
    // enable_if used for constructors
}

// REQ: require from enum Status to have member OK with value 0
TEST_CASE("enum type", "[all-inclusive]")
{
    using StatusType = typename std::underlying_type_t<Status>;

    REQUIRE(std::is_same<StatusType, int>::value);

    int okVal = static_cast<StatusType>(Status::OK);

    REQUIRE(okVal == 0);
}

