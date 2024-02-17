class BadFood {

public:

	BadFood() : is_active(false), x(1), y(1) {}

	void Place(int new_w, int new_y) {
		std::lock_guard<std::mutex> lock(mutex);
		x = new_x;
		y = new_y;
		is_active = true;
	}

	void Remove() {
		std::lock_guard<std::mutex> lock(mutex);
		x = 1;
		y = 1;
		is_active = false;
	}

	bool IsActive() {
		std::lock_guard<std::mutex> lock(mutex);
		return is_active;
	}

	bool IsEaten(int head_x, int head_y) {
		std::lock_guard<std::mutex> lock(mutex);
		return head_x == x && head_y == y;
	}

	std::pair<int, int> GetPosition() {
		std::lock_guard<std::mutex> lock(mutex);
		return {x, y};
	}

	// Need to figure out how to do this safely... Remove method is also calling the mutex.
	void BadFoodTimer() {
		const int duration = 10;
		auto start_time = std::chrono::high_resolution_clock::now();
		while (true) {
			if !(IsActive()) {
				break;
			}
			auto current_time = std::chrono::high_resolution_clock::now();
			auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
			if (elapsed_seconds >= duration) {
				Remove();
				break;
		}
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
		}
	}

private:
	std::mutex mutex;
	bool is_active;
	int x, y;
	
};