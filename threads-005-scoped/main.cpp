#include <thread>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

void sleep_ns( int n ){
    std::this_thread::sleep_for( std::chrono::nanoseconds( n ));
}

std::recursive_mutex cout_mutex;

void write( char c ){
    std::scoped_lock use_cout_exclusively( cout_mutex );
    std::cout << c;
}

void write( const char *s ){
    std::scoped_lock use_cout_exclusively( cout_mutex );
    while( *s != '\0' ){
        write( *s++ );
    }
}

void writer( const char *s, const int n ){
    for( int i = 0; i < n; ++i ){ 
        write( s );
        sleep_ns( 1000 );
    }
}

int main(){
    std::thread thread_1( writer, "Hello\n", 10 );
    std::thread thread_2( writer, "World\n", 10 );
    thread_1.join();
    thread_2.join();
}