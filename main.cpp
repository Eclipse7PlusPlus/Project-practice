#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

struct Student {
    std::string name;
    std::string surname;
    std::string patronymic;
    int32_t group;
    int32_t zachet_number;
    int32_t ma_mark;
    int32_t geo_mark;
    int32_t prog_mark;
};

void OpenCheck(std::ifstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
}

void OutputOpenCheck(std::ofstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать файл: " + filename);
    }
}

void EmptyCheck(std::ifstream& file, const std::string& filename) {
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        throw std::runtime_error("Файл пустой: " + filename);
    }
    file.seekg(0, std::ios::beg);
}

int main() {
    try {
        std::ifstream file1_in("file1.txt");
        std::ifstream file2_in("file2.txt");
        std::ofstream marks("Marks-file.bin", std::ios::binary);

        OpenCheck(file1_in, "file1.txt");
        OpenCheck(file2_in, "file2.txt");
        OutputOpenCheck(marks, "Marks-file.bin");

        EmptyCheck(file1_in, "file1.txt");
        EmptyCheck(file2_in, "file2.txt");

        std::cout << "Все файлы успешно открыты и не пустые!" << std::endl;

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
    }

    system("pause");
    return 0;
}