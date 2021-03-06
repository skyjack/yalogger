//
//  main.cpp
//  logger
//
//  Created by Dmitry Danilov on 08.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#include "logger.h"
#include "file_options.h"
#include "logger_exception.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <chrono>
#include <vector>

const ya::string_t filename = TEXT("file.log");
ya::file_options opt(filename, std::ios::ate | std::ios::app, false);

ya::logger logger(opt, ya::Debug);

struct test_writer {
    void operator() () {
        for (int i = 0; i < 10; ++i) {
            std::chrono::milliseconds wait(1);
            std::this_thread::sleep_for(wait);
            std::stringstream str;
            str << "message from thread: " << std::this_thread::get_id() << " #" << i;
            logger.log(ya::Debug, str.str().c_str());
        }
    }
};

void single_thread_test() {
    test_writer tw;
    auto start = std::chrono::high_resolution_clock::now();
    tw();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    std::cout << "logger ticks: " << elapsed.count() << '\n';
}

void multi_thread_test() {
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; ++i) {
        test_writer tw;
        threads.push_back(std::thread(tw));
    }
    for(auto& thread : threads){
        thread.join();
    }
}

int main(int argc, const char * argv[]) {
    try {
        //single_thread_test();
        multi_thread_test();
    }
    catch(ya::logger_exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch(...) {
        std::cout << "unknown execption\n";
    }
    
    return 0;
}

