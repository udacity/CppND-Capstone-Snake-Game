#include "leaderboard.h"

class Record {

public:
	Record(int s, std::string n) : score(s), name(n) {};

	Record(std::istream& is) {
		if (!(is >> name >> score)) {
			throw std::runtime_error("Error reading from file");
		}
	}

	~Record() {};

	Record(const Record& other) : score(other.getScore()), name(other.getName()) {};

	Record& operator = (const Record& other) {
		if (this != &other) {
			score = other.score;
			name = other.name;
		}
		return *this;
	}

	Record(Record&& other) : score(other.score), name(other.name) {
		other.score = 0;
		other.name = "";
	}

	Record& operator = (Record&& other) {
		if (this != &other) {
			score = other.score;
			name = other.name;
			other.score = 0;
			other.name = "";
		}
		return *this;
	}


	int getScore() const { return score; }
	std::string getName() const { return name; }

	bool operator<(const Record& other) const {
		return score > other.getScore();
	}

	void write(std::ostream& os) const {
		os << name << " " << score << "\n";
	}

private:
	int score;
	std::string name;
};

class Leaderboard {

public:
	Leaderboard() {
		getRecords();
	};

	void addRecord(Record& record) {
		records.push_back(record);
	}

	void addRecord(Record&& record) {
		records.push_back(std::move(record));
	}

	void getRecords() {
		std::ifstream file("leaderboard.txt");
		if (file.is_open()) {
			while (file) {
				try
					records.push_back(Record(file));
			}
			catch (std::runtime_error& e) {
				std::cerr << "Error reading from file: " << e.what() << "\n";
				break;
			}
		}
	};

	void saveRecords() {
		std::ofstream file("leaderboard.txt");
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open leaderboard.txt for writing.")
		}
		for (const auto& record : records) {
			record.write(file);
		}
	}

	void printRecords(int n) {
		sortRecords();
		for (int i = 0; i < n; i++) {
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

			std::cout << records[i].getName() << " " << records[i].getScore() << "\n";
		}
	}

	void sortRecords() {
		std::sort(records.begin(), records.end());
	}

private:
	std::vector<Record> records;
};