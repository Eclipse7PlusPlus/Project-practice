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


void OutputAverageScore(double a, std::ofstream& out){
    out.write("AVG:", sizeof("AVG"));
    out.put('0' + (int)a);
    out.put('.');
    for (int i{}; i < 2; ++i){
        a -= (int)a;
        a *= 10;
        out.put('0' + (int)a);
    }
}


double CalculateAverageScore(Student st) {
    return (st.ma_mark + st.geo_mark + st.prog_mark) / 3.0;
}


void CheckAverageScoreOfStudent(std::string fileWithStudents, std::string fileWithMarks, std::string studentWithLowScore) {
    std::ifstream marks(fileWithMarks);

    OpenCheck(marks, fileWithMarks);
    EmptyCheck(marks, fileWithMarks);

    int32_t size{ CountStudents(fileWithStudents) };
    Student marksData[size];
    int32_t marksCount{};
    std::string line;

    while (std::getline(marks, line) && marksCount < size) {
        marksData[++marksCount] = parseMarksLine(line);
    }
    marks.close();

    std::ifstream studentsIn(fileWithStudents);
    OpenCheck(studentsIn, fileWithStudents);
    EmptyCheck(studentsIn, fileWithStudents);

    std::ofstream out(studentWithLowScore);
    OutputOpenCheck(out, studentWithLowScore);

    while (std::getline(studentsIn, line)) {
        Student st = parseStudentLine(line);

        for (int32_t i{}; i < marksCount; ++i) {
            if (marksData[i].zachet_number == st.zachet_number) {
                st.ma_mark = marksData[i].ma_mark;
                st.geo_mark = marksData[i].geo_mark;
                st.prog_mark = marksData[i].prog_mark;
                break;
            }
        }

        double average = CalculateAverageScore(st);

        if (average < 4.0) {
            out << st.surname << " "
                << st.group << " "
                << st.zachet_number << "\n";
        }
    }

    studentsIn.close();
    out.close();

}


bool CompareDataOfStudentByAlphabet(std::string firstStudent, std::string secondStudent) {
    const char* first = firstStudent.c_str;
    const char* second = secondStudent.c_str;

    if (strcmp(first, second) > 0) {
        return 1;
    }
    return 0;
}


void SortDataOfStudent(std::string students, int32_t size) {
    while (size) {
        for (int32_t i{}; i < size - 1; ++i) {
            if (CompareDataOfStudentByAlphabet(students[i].surname, students[i + 1].surname)) {
                std::swap(students[i], students[i + 1]);
            }
        }
    }
}