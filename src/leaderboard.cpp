#include <string>
#include <vector>
#include <algorithm>

class Record {

	public:
		Record(int s, std:string n) : score(s), name(n) {};

		Record(std::istream& is) {
			is >> name >> score;
		}

		~Record() {};

		Record(const Record& other) : score(other.getScore()), name(other.getName()) {};

		Record& operator = (const Record& other) {
			if (this != &other) {
				score = other.score;
				name = other.name;
			}
			return *this
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


		int getScore() const { return score };
		std::string getName() const { return name };

		bool operator<(const Record& other) const {
			return score > other.getScore();
		}

		void write(std::ostream& os) const {
			os << name << " " << score << "\n";
		}

	private:
		int score;
		std:string name;

	
};

class Leaderbord {

public:
	Leaderbord() {
		getRecords();
	};
	
	void addRecord(Record& record) {
		records.push_back(record);
	}

	void addRecord(Record&& record) {
		records.push_back(std::move(record));
	}

	void getRecords() {
		std::ifstream("leaderboard.txt");
		while (file) {
			records.push_back(Record(file));
		}
	};

	void saveRecords() {
		std::ofstream("leaderboard.txt");
		for( const auto& record : records) {
			record.write(file);
		}
	}
		
	);

	void printRecords(int n) {
		sortRecords();
		for (int i =0; i<n ; i++) {
			switch i{
			case 0:
				std::cout << "1st: "; break;
			case 1:
				std::cout << "2nd: "; break;
			case 2:
				std::cout << "3rd: "; break;
			default:
				std::cout << i + 1 << "th: "; break;
			}

			record
		}
	}

	void sortRecords() {
		std::sort(records.begin(), records.end())
	}

private:
	std::vector<Record> records;

};