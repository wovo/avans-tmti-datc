#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <iomanip> 

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

int fib_n( int n ){
    std::vector< std::future< int > > v;
    for( int i = 0; i < n; ++i ){
        v.push_back( 
            std::async( std::launch::async, fib, 46 )
        );
    }
    return 0;    
}

int main(){
    for( int i = 1; i < 10; ++i ){
        auto d = run_time([&]{ return fib_n( i ); });
        std::cout 
            << "fib(n) * " << std::setw( 2 ) << i 
            << " takes " << std::setw( 7 ) << d << " us"
            << " = " << std::setw( 6 ) << d / i << " per async\n";
    }
}