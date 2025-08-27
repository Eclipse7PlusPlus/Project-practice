#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "nikitasfuncs.h"

int main() {
    try {
        std::ifstream file1_in("file1.txt");
        std::ifstream file2_in("file2.txt");
        std::ofstream marks("Marks-file.bin", std::ios::binary);
        FillBinFile("file1.txt", "1file.bin");
        FillBinFile("file2.txt", "2file.bin");
        std::ifstream ff("1file.bin", std::ios::binary);
        std::ifstream sf("2file.bin", std::ios::binary);
        Student * stud_arr{};
        int stud_count{CountStudents(ff)};
        FormArrOfStuds(stud_arr, stud_count, ff, sf);

        OpenCheck(file1_in, "file1.txt");
        OpenCheck(file2_in, "file2.txt");
        OutputOpenCheck(marks, "Marks-file.bin");

        EmptyCheck(file1_in, "file1.txt");
        EmptyCheck(file2_in, "file2.txt");

        std::cout << "Все файлы успешно открыты и не пустые!" << std::endl;
        WriteAllStudents(marks,stud_arr,stud_count);

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
    }

    return 0;
}


