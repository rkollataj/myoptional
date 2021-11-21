#include <myoptional.h>

#include <cstdlib>

class DefaultClass {
public:
    DefaultClass() = delete;

    DefaultClass(int val)
        : _abc(val)
    {
    }

    int _abc{ 123 };
};

myoptional<DefaultClass> func1()
{
    return DefaultClass(11);
}

myoptional<DefaultClass> func2()
{
    return Status::ERROR;
}

int main(int, char**)
{
    myoptional<const DefaultClass> op1 = DefaultClass(22);
    myoptional<DefaultClass> op2 = Status::ERROR;

    myoptional<DefaultClass> op3 = func1();
    myoptional<DefaultClass> op4 = func2();

    op2 = DefaultClass(11);

    DefaultClass a = op3;
    DefaultClass b = static_cast<DefaultClass>(op3);

    Status s = op3;

    if (op3 == Status::OK) {
    }

    return EXIT_SUCCESS;
}

