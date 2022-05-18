#include <thread>
#include <iostream>
#include <chrono>
#include <thread>

void sleep_ns( int n ){
    std::this_thread::sleep_for( std::chrono::nanoseconds( n ));
}

void write( char c ){
    std::cout << c;
    sleep_ns( 1000 );
}

void write( const char *s ){
    while( *s != '\0' ){
        write( *s++ );
    }
}

void writer( const char *s, const int n ){
    for( int i = 0; i < n; ++i ){ 
        write( s );
    }
}

int main(){
    std::thread thread_1( writer, "Hello\n", 10 );
    std::thread thread_2( writer, "World\n", 10 );
    thread_1.join();
    thread_2.join();
}