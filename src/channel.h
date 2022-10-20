#ifndef CHANNEL_H
#define CHANNEL_H

#include <condition_variable>
#include <vector>
#include "settings.h"

namespace SnakeGame
{

template<typename T>
class Channel {
public:
    T waitForStart()  {
        std::unique_lock<std::mutex> lock(mtx_);
        cond_.wait(lock, [this]{ return !messages_.empty();});
        T msg = messages_.front();
        return msg;
    } ;
    void start(T & msg)  {
        std::lock_guard<std::mutex> lock(mtx_);
        messages_.push_back(msg);
        cond_.notify_all();        
    };
    void reset() {
        std::lock_guard<std::mutex> lock(mtx_);
        messages_.clear();
    };

private:
    std::mutex mtx_;
    std::condition_variable cond_; 
    std::vector<T> messages_;
};
}

#endif