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
    double average;
};
void OpenCheck(std::fstream& file, const std::string& filename);
void OutputOpenCheck(std::fstream& file, const std::string& filename);
void EmptyCheck(std::fstream& file, const std::string& filename);
void CreateBinaryFile(const std::string& Textfilename, const std::string& Binaryfilename);
Student parseMarksLine(const std::string& line);
Student parseStudentLine(const std::string& line);
void writeOneStudentToBinary(std::fstream& file,Student student);
void FillBinFile(std::string FileName, std::string BinFileName);
void OutputBinFile(std::string BinFileName);
Student* FormArrOfStuds(Student *& stud_arr, int stud_count, std::ifstream& firstFile, std::ifstream& secondFile);
int CountStudents(std::ifstream& in);
void FillOneStudentFromSecondFile(std::ifstream & in, Student& stud);
void FillOneStudentFromFirstFile(std::ifstream & in, Student& stud);
std::string GetOneWordFromFile(std::ifstream& in);
void blabla(int a, std::fstream& out);
void WriteAllStudents(std::fstream& file, Student* stud_arr,int stud_count);
void WriteAllStudentsAverage(std::fstream& file, Student* stud_arr, int stud_count);
void OutputDecimalWithTwoDigits(double a, std::fstream& out);
double CalculateAverageScore(Student st);
bool CheckingStudentMarks(Student st);
void GenerateListOfLowScoreStudents(Student* stud_arr, int stud_count, std::fstream& file);
int32_t Compare(const void* x1, const void* x2);
int32_t CountLowScoreStudents(Student * stud_arr, int32_t stud_count);
Student* CreateArrWithtLowScoreStudents(Student* stud_arr, int32_t stud_count, int32_t& low_count);
void SortByGroupNumber(Student* arr, int32_t count);
int32_t CompareInGroupBySurname(const void* x1, const void* x2);
void SortStudentsByGroupThenSurname(Student* arr, int32_t count);
bool numCompare(Student first, Student second);
bool nameCompare(Student first, Student second);
void sort(Student* stud_arr, int stud_count);
void selectionSort(Student *arr, int length, bool (*func_of_comp)(Student, Student));
size_t returnIdxOfEdgeElem(Student * arr, int length, bool (*func_of_comp)(Student, Student));


#endif