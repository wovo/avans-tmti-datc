#include <iostream>
#include <chrono>
#include <thread>
#include <future>

#define TRACE { std::cout << __FILE__ << ":" << __LINE__ << "\n"; }

void sleep_ns( int n ){
    std::this_thread::sleep_for( std::chrono::nanoseconds( n ));
}

std::recursive_mutex cout_mutex;

template< typename F >
void run_locked( std::recursive_mutex & m, F f ){           
   std::scoped_lock lock( m );
   f();
}

void f( int n ){
    for( int i = 0; i < 10; ++ i ){
        run_locked( cout_mutex, [&]{
            std::cout << "async " << n << " " << i << "\n";
        });
        sleep_ns( 1'000'000 );
    }
}

int main(){
    auto f1 = std::async( std::launch::async, f, 1 );
    TRACE;
    auto f2 = std::async( std::launch::async, f, 2 );
    TRACE;
    auto f3 = std::async( std::launch::async, f, 3 );
    TRACE;
}
