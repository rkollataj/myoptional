#include <myoptional.h>

#include <cstdlib>

class DefaultClass {
public:
    int abc;
};

myoptional<DefaultClass> func1() { return DefaultClass(); }

myoptional<DefaultClass> func2() { return Status::ERROR; }

int main(int argc, char** argv) {
    myoptional<const DefaultClass> op1 = DefaultClass();
    myoptional<DefaultClass> op2 = Status::ERROR;

    myoptional<DefaultClass> op3 = func1();
    myoptional<DefaultClass> op4 = func2();

    return EXIT_SUCCESS;
}

