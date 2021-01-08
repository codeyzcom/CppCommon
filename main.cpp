#include <iostream>
#include <chrono>

#include "lib/multithreading/simple_worker_thread/worker.h"

void run_worker_thread_example();

int main() {
    std::cout << "Hello, World!" << std::endl;
    run_worker_thread_example();
    return 0;
}


void run_worker_thread_example() {
    std::cout << "Hi! Welcome to demo of worker thread" << std::endl;
    {
        Worker w1;
        Worker w2;

        w1.do_sync([] {
            std::cout << "First - blocking call " << std::endl;
        });

        for (int i = 1; i < 100; i++) {
            auto &t = i % 2 == 0 ? w1 : w2;
            if (i == 10) {
                w1.do_sync([] {
                    std::cout << "Second - blocking call" << std::endl;
                });
            }
            t.do_async([i] {
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(200));
                std::cout << (i % 2 == 0 ? "w1: " : "w2: ") << "iteration number: " << i << std::endl;
            });
        }

        w1.wait();
        w2.wait();

        w1.do_sync([] {
            std::cout << "Last blocking call!";
        });
    }
}