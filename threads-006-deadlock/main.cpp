#include <thread>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

void sleep_ns( int n ){
    std::this_thread::sleep_for( std::chrono::nanoseconds( n ));
}

std::recursive_mutex cout_mutex;

int counter = 0;
std::recursive_mutex counter_mutex;

void hello_writer(){
    for( int i = 0; i < 10; ++i ){ 
        std::scoped_lock use_cout_exclusively( cout_mutex );
        sleep_ns( 1000 );
        std::scoped_lock use_counter_exclusively( counter_mutex );
        std::cout << ++counter << "hello\n";
    }    
}

void world_writer(){
    for( int i = 0; i < 10; ++i ){ 
        std::scoped_lock use_counter_exclusively( counter_mutex );
        sleep_ns( 1000 );
        std::scoped_lock use_cout_exclusively( cout_mutex );
        std::cout << ++counter << "world\n";
    }    
}

int main(){
    std::thread thread_1( hello_writer );
    std::thread thread_2( world_writer );
    thread_1.join();
    thread_2.join();
}