#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <chrono>

int fib( int n ){
    return ( n < 2 ) ? 1 : fib( n - 1 ) + fib( n - 2 );
}

template< typename F >
int run_time( F f ){           
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    volatile auto dummy = f();
    (void)dummy;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto d = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    return d;
}

void fib1(){
    auto f1 = std::async( std::launch::async, fib, 40 );
    std::cout << "fib1 " << run_time([&]{
        volatile auto s = f1.get();
        return s;
    }) << "\n";
}

void fib2(){
    auto f1 = std::async( std::launch::async, fib, 40 );
    auto f2 = std::async( std::launch::async, fib, 40 );
    std::cout << "fib2 " << run_time([&]{
        volatile auto s = f1.get() + f2.get();
        return s;
    }) << "\n";
}

void fib3(){
    auto f1 = std::async( std::launch::async, fib, 40 );
    auto f2 = std::async( std::launch::async, fib, 40 );
    auto f3 = std::async( std::launch::async, fib, 40 );
    std::cout << "fib4 " << run_time([&]{
        volatile auto s = f1.get() + f2.get() + f3.get();
        return s;
    }) << "\n";
}

void fib4(){
    auto f1 = std::async( std::launch::async, fib, 40 );
    auto f2 = std::async( std::launch::async, fib, 40 );
    auto f3 = std::async( std::launch::async, fib, 40 );
    auto f4 = std::async( std::launch::async, fib, 40 );
    std::cout << "fib4 " << run_time([&]{
        volatile auto s = f1.get() + f2.get() + f3.get() + f4.get();
        return s;
    }) << "\n";
}

void fib5(){
    auto f1 = std::async( std::launch::async, fib, 40 );
    auto f2 = std::async( std::launch::async, fib, 40 );
    auto f3 = std::async( std::launch::async, fib, 40 );
    auto f4 = std::async( std::launch::async, fib, 40 );
    auto f5 = std::async( std::launch::async, fib, 40 );
    std::cout << "fib5 " << run_time([&]{
        volatile auto s = f1.get() + f2.get() + f3.get() + f4.get() + f5.get();
        return s;
    }) << "\n";
}

int main(){
    fib1();
    fib2();
    fib3();
    fib4();
    fib5();
}
