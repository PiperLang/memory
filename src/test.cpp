#include <memory/memory.hpp>

#include <cassert>

class Foo {
    public:
        Foo() {
            this->a = 1;
        }

        int a;
};

class Bar {
    public:
        Bar() {
            this->b = 2;
        }

        int b;
        Foo foo;
};

int main(int argc, char *argv[]) {
    auto memory = new piper::Memory<Foo>(1024 * 1024);

    Foo *foo = memory->get_new();
    assert(foo->a == 1);

    delete memory;
}