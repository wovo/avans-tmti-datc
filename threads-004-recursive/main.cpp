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
    cout_mutex.lock();
    std::cout << c;
    cout_mutex.unlock();
}

void write( const char *s ){
    cout_mutex.lock();
    while( *s != '\0' ){
        write( *s++ );
    }
    cout_mutex.unlock();
    sleep_ns( 1000 );
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