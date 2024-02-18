#include "bad_food.h"
#include <chrono>

BadFood::BadFood() : is_active(false) {}

void BadFood::Place(int new_x, int new_y) {
    std::lock_guard<std::mutex> lock(data_mutex);
    position.x = new_x;
    position.y = new_y;
    is_active = true;
}

void BadFood::Remove() {
    std::lock_guard<std::mutex> lock(data_mutex);
    position.x = 1;
    position.y = 1;
    is_active = false;
}


bool BadFood::IsActive() const {
    std::lock_guard<std::mutex> lock(data_mutex);
    return is_active;
}

void BadFood::Cancel() {
    std::unique_lock<std::mutex> lock(cancel_mutex);
    cancel = true;
    cond.notify_one();
}

bool BadFood::IsEaten(int head_x, int head_y) const {
    std::lock_guard<std::mutex> lock(data_mutex);
    return head_x == position.x && head_y == position.y;
}

SDL_Point BadFood::GetPosition() const {
    std::lock_guard<std::mutex> lock(data_mutex);
    return position;
}

void BadFood::BadFoodTimer() {
    const int duration = 10;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::unique_lock<std::mutex> lock(cancel_mutex);
    cancel = false;
    while (!cancel && IsActive()) {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        if (elapsed_seconds >= duration) {
            Remove();
            break;
        }
        cond.wait_for(lock, std::chrono::milliseconds(500));
    }
    cancel = false;
}
