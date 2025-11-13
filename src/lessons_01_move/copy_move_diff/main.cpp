#include <vector>
#include <string>
#include <iostream>
#include <utility>

struct Record {
    std::string s;
    static inline int copies=0, moves=0;
    Record(std::string s): s(std::move(s)) {}
    Record(const Record& r): s(r.s) { ++copies; }
    Record(Record&& r) noexcept: s(std::move(r.s)) { ++moves; }
};

int main() {
    Record::copies = Record::moves = 0;
    std::vector<Record> v;
    v.reserve(3);

    Record r("alpha");
    v.push_back(r);                  // копия

    v.push_back(std::move(r));       // перемещение

    v.emplace_back("bravo");         // конструирование на месте

    std::cout << Record::copies << " " << Record::moves << "\n";
}
