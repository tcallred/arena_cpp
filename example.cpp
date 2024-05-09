#include "arena.hpp"
#include <iostream>
#include <memory>

struct Foo
{
    int xx = 32;
    int yy = 5;
};

void makeTest()
{
    Arena scratch{};
    int *x = scratch.make<int>();
    *x = 42;
    std::cout << *x << '\n';
    Foo *foo = scratch.make<Foo>();
    std::cout << foo->xx << '\n';
    Foo *bar = scratch.make<Foo>(21, 69);
    std::cout << bar->xx << '\n';
    auto baz = scratch.make<Foo>(Foo{
        .xx = 4,
        .yy = 5});
    std::cout << baz->xx << '\n';
}

void vectorTest()
{
    Arena scratch{};
    auto myvec = scratch.make_vector<int>(42, 69);
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    for (auto i : myvec)
    {
        std::cout << i << '\n';
    }
}

void stringTest()
{
    Arena scratch{};
    auto mystr = scratch.make_string("hello");
    std::cout << mystr << '\n';
}

int main(void)
{
    makeTest();
    vectorTest();
    stringTest();
    return 0;
}