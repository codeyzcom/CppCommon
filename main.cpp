#include <iostream>
#include <chrono>
#include <random>

#include "lib/multithreading/simple_worker_thread/worker.h"
#include "lib/algorithms/trees/btree/tree.h"
#include "lib/design_patterns/creational/singleton.h"

void run_worker_thread_example();
void run_btree_example();
void pattern_singleton_example();

int main() {
    std::cout << "Hello, World!" << std::endl;
    pattern_singleton_example();
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
            std::cout << "Last blocking call!\n";
        });
    }
}

void run_btree_example() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(1, 64);

    std::cout << "Start BTree!" << std::endl;

    auto tree = new btree();

    for (int n = 0; n < 50; ++n) {
        int num = distribution(gen);
        tree->insert(num);
        std::cout << "Insert number: " << num << std::endl;
    }

    std::cout << tree->search(2)->key_value << std::endl;

    std::cout << "Stop BTree!" << std::endl;
}

void pattern_singleton_example() {
    std::cout << Singleton::get_instance().foo() << std::endl;

}