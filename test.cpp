#include "evgenhead.h"








int main()
{
    FillBinFile("file1.txt","1file.bin");
    FillBinFile("file2.txt", "2file.bin");
    std::ifstream ff("1file.bin", std::ios::binary);
    std::ifstream sf("2file.bin", std::ios::binary);
    Student* stud_arr{};
    int stud_count{CountStudents(ff)};
    FormArrOfStuds(stud_arr, stud_count, ff, sf);
    return 0;
}