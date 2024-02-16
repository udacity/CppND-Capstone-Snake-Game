#include "leaderboard.h"

Record::Record(int s, std::string n) : score(s), name(n) {}

Record::Record(std::istream& is) {
    if (!(is >> name >> score)) {
        throw std::runtime_error("Error reading from file");
    }
}

Record::~Record() {}

Record::Record(const Record& other) : score(other.getScore()), name(other.getName()) {}

Record& Record::operator = (const Record& other) {
    if (this != &other) {
        score = other.score;
        name = other.name;
    }
    return *this;
}

Record::Record(Record&& other) noexcept : score(other.score), name(other.name) {
    other.score = 0;
    other.name = "";
}

Record& Record::operator = (Record&& other) noexcept {
    if (this != &other) {
        score = other.score;
        name = other.name;
        other.score = 0;
        other.name = "";
    }
    return *this;
}

int Record::getScore() const { return score; }

std::string Record::getName() const { return name; }

bool Record::operator<(const Record& other) const {
    return score > other.getScore();
}

void Record::write(std::ostream& os) const {
    os << name << " " << score << "\n";
}

Leaderboard::Leaderboard() {
    getRecords();
}

void Leaderboard::addRecord(Record& record) {
    records.push_back(record);
}

void Leaderboard::addRecord(Record&& record) {
    records.push_back(std::move(record));
}

void Leaderboard::getRecords() {
    std::ifstream file("leaderboard.txt");
    if (file.is_open()) {
        while (file >> std::ws && !file.eof()) {
            try {
                records.push_back(Record(file));
            }
            catch (std::runtime_error& e) {
                std::cerr << "Error reading from file: " << e.what() << "\n";
                break;
            }
        }
    }
}

void Leaderboard::saveRecords() {
    std::ofstream file("leaderboard.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open leaderboard.txt for writing.");
    }
    for (const auto& record : records) {
        record.write(file);
    }
}

void Leaderboard::printRecords(int n) {
    sortRecords();
    int i = 0;
    std::cout << "\n";
    std::cout << "Leaderboard\n";
    std::cout << "===========\n";
    for (const auto& record : records) {
        if (i < n) {
            switch (i) {
            case 0:
                std::cout << "1st: "; break;
            case 1:
                std::cout << "2nd: "; break;
            case 2:
                std::cout << "3rd: "; break;
            default:
                std::cout << i + 1 << "th: "; break;
            }
            std::cout << records[i].getName() << " - " << records[i].getScore() << "\n";
        }
        else {
            break;
        }
        i++;
    }
}

void Leaderboard::sortRecords() {
    std::sort(records.begin(), records.end());
}
