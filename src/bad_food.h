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
	bool IsActive();
	void Cancel();
	bool IsEaten(int head_x, int head_y);
	SDL_Point GetPosition();
	void BadFoodTimer();

private:
	std::mutex data_mutex;
	std::mutex cancel_mutex;
	bool is_active;
	bool cancel = false;
	SDL_Point position;

};

#endif // !BAD_FOOD_H
