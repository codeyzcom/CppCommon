//
// Created by user on 1/8/21.
//

#ifndef CPPREPO_WORKER_H
#define CPPREPO_WORKER_H

#include <functional>
#include <thread>
#include <list>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <iostream>


class Worker {
public:
    Worker();

    ~Worker();

    void do_async(const std::function<void()> &t);

    void do_sync(const std::function<void()> &t);

    void wait();

    void stop();

private:
    void start_thread();

    std::condition_variable item_queue_;
    std::mutex mutex_;
    std::unique_ptr<std::thread> thread_;
    std::list<std::function<void()>> tasks_;
    volatile bool is_running_;

};


#endif //CPPREPO_WORKER_H
