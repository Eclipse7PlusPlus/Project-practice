#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include "nikitasfuncs.h"

int main() {
    try {
        std::fstream file1_in("FILES/file1.txt", std::ios::in);
        std::fstream file2_in("FILES/file2.txt", std::ios::in);
        std::fstream marks("FILES/Marks-file.bin", std::ios::binary | std::ios::out);
        std::fstream taskC("FILES/AverageScoreOfStudent.bin", std::ios::binary | std::ios::out);
        FillBinFile("FILES/file1.txt", "FILES/1file.bin");
        FillBinFile("FILES/file2.txt", "FILES/2file.bin");
        std::ifstream ff("FILES/1file.bin", std::ios::binary);
        std::ifstream sf("FILES/2file.bin", std::ios::binary);
        std::fstream taskD("FILES/TaskD.txt",std::ios::out);
        std::fstream taskG("FILES/TaskG.txt",std::ios::out);
        std::fstream taskH("FILES/TaskH.txt",std::ios::out);
        std::fstream taskI("FILES/TaskI.txt",std::ios::out);
        Student * stud_arr{};
        int stud_count{CountStudents(ff)};
        FormArrOfStuds(stud_arr, stud_count, ff, sf);

        OpenCheck(file1_in, "FILES/file1.txt");
        OpenCheck(file2_in, "FILES/file2.txt");

        OutputOpenCheck(marks, "FILES/Marks-file.bin");

        EmptyCheck(file1_in, "FILES/file1.txt");
        EmptyCheck(file2_in, "FILES/file2.txt");

        std::cout << "Все файлы успешно открыты и не пустые!" << std::endl;
        sort(stud_arr, stud_count);
        WriteAllStudents(marks, stud_arr, stud_count);
        WriteAllStudentsAverage(taskC, stud_arr,stud_count);
        taskDE(taskD,stud_arr,stud_count);
        int group;
        std::cout<<"Input group number: "<<std::endl;
        std::cin>>group;

        taskGG(taskG,stud_arr,stud_count,group);
        taskHH(taskH,stud_arr,stud_count,group);
        taskII(taskI,stud_arr,stud_count);

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
    }



    return 0;
}