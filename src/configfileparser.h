#ifndef CONFIGFILEPARSER_HPP_INCLUDE
#define CONFIGFILEPARSER_HPP_INCLUDE

#include <string>

namespace SnakeGame
{

const std::string kDefaultFileName{"./snake.cfg"};
const std::string kScreenWidthName{"ScreenWidth"};
const std::string kScreenHeightName{"ScreenHeight"};
const std::string kGridWidthName{"GridWidth"};
const std::string kGridHeightName{"GridHeight"};
const std::string kNoSnakes{"NumOfSnakes"};
const std::string kFramesPerSecondName("FramesPerSecond");
const std::string kDemoMode("DemoMode");

std::size_t GetGridHeight(std::string const & filename = kDefaultFileName);
std::size_t GetScreenWidth(std::string const & filename = kDefaultFileName);
std::size_t GetScreenHeight(std::string const & filename = kDefaultFileName);
std::size_t GetGridWidth(std::string const & filename = kDefaultFileName);
std::size_t GetNoOfSnakes(std::string const & filename = kDefaultFileName);
std::size_t GetFps(std::string const & filename = kDefaultFileName);
std::size_t GetMsPerFrame(std::string const & filename = kDefaultFileName);
bool GetDemoMode(std::string const & filename = kDemoMode);

}

#endif