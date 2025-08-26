#ifndef FUNCS
#define FUNCS

#include <fstream>
#include <iostream>
#include <string>

void FillBinFile(std::string FileName, std::string BinFileName);
void OutputBinFile(std::string BinFileName);
Student * FormArrOfStuds(Student *& stud_arr, int stud_count, std::ifstream& firstFile, std::ifstream& secondFile);
int CountStudents(std::ifstream& in);
void FillOneStudentFromSecondFile(std::ifstream & in, Student& stud);
void FillOneStudentFromFirstFile(std::ifstream & in, Student& stud);
std::string GetOneWordFromFile(std::ifstream& in);

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


#endif