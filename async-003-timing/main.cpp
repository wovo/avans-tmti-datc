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

int main(){
    for( int i = 0; i < 100; ++i ){
        std::cout << i << " " << run_time( [=]{ return fib( i ); } ) << "\n";
    }    
}
