#ifndef FUNCTIONS_NIKITA
#define FUNCTIONS_NIKITA
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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
void OpenCheck(std::ifstream& file, const std::string& filename);
void OutputOpenCheck(std::ofstream& file, const std::string& filename);
void EmptyCheck(std::ifstream& file, const std::string& filename);
void CreateBinaryFile(const std::string& Textfilename, const std::string& Binaryfilename);
Student parseMarksLine(const std::string& line);
Student parseStudentLine(const std::string& line);
void writeOneStudentToBinary(std::ofstream& file,Student student);
void FillBinFile(std::string FileName, std::string BinFileName);
void OutputBinFile(std::string BinFileName);
Student* FormArrOfStuds(Student *& stud_arr, int stud_count, std::ifstream& firstFile, std::ifstream& secondFile);
int CountStudents(std::ifstream& in);
void FillOneStudentFromSecondFile(std::ifstream & in, Student& stud);
void FillOneStudentFromFirstFile(std::ifstream & in, Student& stud);
std::string GetOneWordFromFile(std::ifstream& in);
void blabla(int a, std::ofstream& out);
void WriteAllStudents(std::ofstream& file, Student* stud_arr,int stud_count);

#endif