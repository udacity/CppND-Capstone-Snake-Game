class BadFood {

public:

	BadFood() : is_active(false), x(1), y(1) {}

	void Place(int new_x, int new_y) {
		std::lock_guard<std::mutex> lock(data_mutex);
		x = new_x;
		y = new_y;
		is_active = true;
	}

	void Remove() {
		std::lock_guard<std::mutex> lock(data_mutex);
		x = 1;
		y = 1;
		is_active = false;
	}

	bool IsActive() {
		std::lock_guard<std::mutex> lock(data_mutex);
		return is_active;
	}

	void Cancel() {
		std::unique_lock<std::mutex> lock(cancel_mutex);
		cancel = true;
		cond.notify_one();
	}

	bool IsEaten(int head_x, int head_y) {
		std::lock_guard<std::mutex> lock(data_mutex);
		return head_x == x && head_y == y;
	}

	std::pair<int, int> GetPosition() {
		std::lock_guard<std::mutex> lock(data_mutex);
		return {x, y};
	}

	// Need to figure out how to do this safely... Remove method is also calling the mutex.
	void BadFoodTimer() {
		const int duration = 10;
		auto start_time = std::chrono::high_resolution_clock::now();
		std::unique_lock<std::mutex> lock(cancel_mutex);
		while (!cancel && IsActive()) {
			auto current_time = std::chrono::high_resolution_clock::now();
			auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
			if (elapsed_seconds >= duration) {
				Remove();
				break;
			}
			cond.wait_for(lock, std::chrono::milliseconds(500));
		}
	}

private:
	std::mutex data_mutex;
	std::mutex cancel_mutex;
	std::condition_variable cond;
	bool is_active;
	bool cancel = false;
	int x, y;
	
};