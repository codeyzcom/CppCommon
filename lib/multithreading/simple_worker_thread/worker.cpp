//
// Created by user on 1/8/21.
//

#include "worker.h"

Worker::Worker() : is_running_(false) {
    thread_.reset(new std::thread([this] {
        is_running_ = true;
        this->start_thread();
    }));
}

Worker::~Worker() {
    stop();
}

void Worker::start_thread() {
    std::unique_lock<std::mutex> l(mutex_);
    do {
        while (is_running_ && tasks_.empty()) {
            item_queue_.wait(l);
        }
        while (!tasks_.empty()) {
            auto size = tasks_.size();
            std::cout << "Number of pending task are: " << size << "\n";
            const std::function<void()> t = tasks_.front();
            tasks_.pop_front();
            l.unlock();
            t();
            l.lock();
        }
        item_queue_.notify_all();
    } while (is_running_);
    item_queue_.notify_all();
}

void Worker::do_async(const std::function<void()> &t) {
    std::lock_guard<std::mutex> _(mutex_);
    tasks_.push_back(t);
    item_queue_.notify_one();
}

void Worker::do_sync(const std::function<void()> &t) {
    std::condition_variable event;
    bool finished = false;

    std::unique_lock<std::mutex> l(mutex_);
    auto lambda = [this, &t, &finished, &event] {
        t();
        std::lock_guard<std::mutex> l(mutex_);

        finished = true;
        event.notify_one();
    };

    tasks_.push_back(lambda);
    item_queue_.notify_one();

    while (!finished) {
        event.wait(l);
    }
}

void Worker::wait() {
    std::unique_lock<std::mutex> l(mutex_);
    while (!tasks_.empty()) {
        item_queue_.wait(l);
    }
}

void Worker::stop() {
    {
        std::lock_guard<std::mutex> l(mutex_);
        is_running_ = false;
        item_queue_.notify_one();
    }
    thread_->join();
}