#ifndef BAD_FOOD_H
#define BAD_FOOD_H

#include <mutex>
#include <condition_variable>
#include "SDL.h"

class BadFood {
	
public:
	BadFood();

	void Place(int new_x, int new_y);
	void Remove();
	bool IsActive() const;
	void Cancel();
	bool IsEaten(int head_x, int head_y) const;
	SDL_Point GetPosition() const;
	void BadFoodTimer();

private:
	mutable std::mutex data_mutex;
	std::mutex cancel_mutex;
	std::condition_variable cond;
	bool is_active;
	bool cancel = false;
	SDL_Point position;

};

#endif // !BAD_FOOD_H
