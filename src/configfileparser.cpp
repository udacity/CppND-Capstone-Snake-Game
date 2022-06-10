#include <sstream>
#include <fstream>
#include "configfileparser.h"
#include "settings.h"

namespace SnakeGame {

template<typename T>
T ReadAndParse(const std::string & file, const std::string & searchkey) {

  std::ifstream filestream(file);
  if (filestream.is_open()) {
    std::string line;
    while (std::getline(filestream, line)) {
      std::string key;
      T value;
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (searchkey == key) {
          return value;
        }
      }
    }
  }
  return static_cast<T>(0); 
}

std::size_t GetGridHeight(std::string const & filename) {
    const auto result = ReadAndParse<std::size_t>(filename,kGridHeightName);

    return ((0U != result) ? result : SnakeGame::kGridHeight );
}

std::size_t GetScreenWidth(std::string const & filename) {
    const auto result = ReadAndParse<std::size_t>(filename,kScreenWidthName);

    return ((0U != result) ? result : SnakeGame::kScreenWidth );

}

std::size_t GetScreenHeight(std::string const & filename) {
    const auto result = ReadAndParse<std::size_t>(filename,kScreenHeightName);

    return ((0U != result) ? result : SnakeGame::kScreenHeight );
}

std::size_t GetGridWidth(std::string const & filename) {
    const auto result = ReadAndParse<std::size_t>(filename,kGridWidthName);

    return ((0U != result) ? result : SnakeGame::kGridWidth );
}

std::size_t GetNoOfSnakes(std::string const & filename) {
    const auto result = ReadAndParse<std::size_t>(filename,kNoSnakes);

    return ((0U != result) ? result : 1U );
}

}
