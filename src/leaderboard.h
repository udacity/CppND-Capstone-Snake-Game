#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class Record {
public:
    Record(int s, std::string n);
    Record(std::istream& is);
    ~Record();
    Record(const Record& other);
    Record& operator = (const Record& other);
    Record(Record&& other) noexcept;
    Record& operator = (Record&& other) noexcept;

    int getScore() const;
    std::string getName() const;
    bool operator<(const Record& other) const;
    void write(std::ostream& os) const;

private:
    int score;
    std::string name;
};

class Leaderboard {
public:
    Leaderboard();
    void addRecord(Record& record);
    void addRecord(Record&& record);
    void getRecords();
    void saveRecords();
    void printRecords(int n);
    void sortRecords();

private:
    std::vector<Record> records;
};

#endif // LEADERBOARD_H
