// Example program
#include <iostream>
#include <string>

struct A { int x; };
struct B { int x; B() = default;};

int main()
{
    int cnt_a1{}, cnt_a2{}, cnt_a3{}, cnt_a4{}, cnt_a5{};
    int cnt_b1{}, cnt_b2{}, cnt_b3{}, cnt_b4{}, cnt_b5{};

    for (size_t i = 0; i < 10000; ++i)
    {
        // struct A
        A a1;
        // A a2(); // -Wvexing-parse
        A a3{};
        auto a4 = A();
        auto a5 = A{};
        
        cnt_a1 += (a1.x != 0) ? 1 : 0;
        // cnt_a2 += (a2.x != 0) ? 1 : 0;
        cnt_a3 += (a3.x != 0) ? 1 : 0;
        cnt_a4 += (a4.x != 0) ? 1 : 0;
        cnt_a5 += (a5.x != 0) ? 1 : 0;
        

        // struct B
        B b1;
        // B b2(); // -Wvexing-parse
        B b3{};
        auto b4 = B();
        auto b5 = B{};
        
        cnt_b1 += (b1.x != 0) ? 1 : 0;
        // cnt_b2 += (b2.x != 0) ? 1 : 0;
        cnt_b3 += (b3.x != 0) ? 1 : 0;
        cnt_b4 += (b4.x != 0) ? 1 : 0;
        cnt_b5 += (b5.x != 0) ? 1 : 0;

    }    
    
    printf("[counts] a1:%d a2:-- a3:%d a4:%d a5:%d\n", cnt_a1, cnt_a3, cnt_a4, cnt_a5);
    printf("[counts] b1:%d b2:-- b3:%d b4:%d b5:%d\n", cnt_b1, cnt_b3, cnt_b4, cnt_b5);    
    return 0;
}

