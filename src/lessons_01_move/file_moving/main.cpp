/*
RAII над файлом (перемещаемый, без копий)
Цель: 
    потренироваться в «забирании» ресурса.
Задание: 
    Добавь функцию File make_temp(); (создаёт временный файл) и покажи, 
    что возврат по значению использует перемещение/NRVO.
*/

#include <cstdio>
#include <stdexcept>
#include <utility>

struct File {
    std::FILE* f{};
    explicit File(const char* path) {
        f = std::fopen(path, "w");
        if (!f) throw std::runtime_error("open fail");
    }
    ~File(){ if (f) std::fclose(f); }

    File(const File&) = delete;
    File& operator=(const File&) = delete;

    File(File&& other) noexcept : f(other.f) { other.f=nullptr; }
    File& operator=(File&& other) noexcept {
        if (this != &other) { if (f) std::fclose(f); f = other.f; other.f=nullptr; }
        return *this;
    }
};

int main() {
    File a("out.txt");
    File b = std::move(a);   // b владеет, a пуст
}
