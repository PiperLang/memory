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
    piper::Memory *memory = new piper::Memory(1024 * 1024);

    Foo *foo = piper::allocate<Foo>(memory);
    assert(foo->a == 1);

    Bar *bar = piper::allocate<Bar>(memory);
    assert(bar->b == 2);
    assert(bar->foo.a == 1);

    assert((void *)foo != (void *)bar);

    delete memory;
}