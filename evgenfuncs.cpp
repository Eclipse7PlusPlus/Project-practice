
#include "nikitasfuncs.h"

void FillBinFile(std::string FileName, std::string BinFileName)
{
    std::ifstream in(FileName);
    std::ofstream out(BinFileName,std::ios::binary);
    char buffer{};
    while (in.get(buffer))
    {
        out.put(buffer);
    }
    in.close();
    out.close();
}

void OutputBinFile(std::string FileName)
{
    char buffer{};
    std::ifstream in(FileName, std::ios::binary);
    while(in.get(buffer))
    {
        std::cout << buffer;
    }
    in.close();
}


std::string GetOneWordFromFile(std::ifstream& in)
{
    std::string result{};
    char buffer{};
    while(in.get(buffer) && buffer != '\n' && buffer != ';')
    {
        result += buffer;
    }
    return result;
}


void FillOneStudentFromFirstFile(std::ifstream & in, Student& stud)
{
    stud.zachet_number = stoi(GetOneWordFromFile(in));
    stud.surname = GetOneWordFromFile(in);
    stud.name = GetOneWordFromFile(in);
    stud.patronymic = GetOneWordFromFile(in);
}


void FillOneStudentFromSecondFile(std::ifstream & in, Student& stud)
{
    stud.group = stoi(GetOneWordFromFile(in));
    stud.zachet_number = stoi(GetOneWordFromFile(in));
    GetOneWordFromFile(in);
    stud.ma_mark = stoi(GetOneWordFromFile(in));
    GetOneWordFromFile(in);
    stud.geo_mark = stoi(GetOneWordFromFile(in));
    GetOneWordFromFile(in);
    stud.prog_mark = stoi(GetOneWordFromFile(in));
}



int CountStudents(std::ifstream& in)
{
    int res{};
    char buffer{};
    while(in.get(buffer))
    {
        if (buffer == '\n')
        {
            ++res;
        }
    }
    in.clear();
    in.seekg(std::ios::beg);
    return res;
}

Student * FormArrOfStuds(Student *& stud_arr, int stud_count, std::ifstream& firstFile, std::ifstream& secondFile)
{
    stud_arr = new Student[stud_count];
    for(int i = 0; i < stud_count; ++i)
    {
        FillOneStudentFromFirstFile(firstFile, stud_arr[i]);
    }



    Student buffer{};
    for (int j = 0; j < stud_count; ++j)
    {
        FillOneStudentFromSecondFile(secondFile, buffer);
        for(int i = 0; i < stud_count; ++i)
        {
            if(stud_arr[i].zachet_number == buffer.zachet_number)
            {
                stud_arr[i].group = buffer.group;
                stud_arr[i].ma_mark = buffer.ma_mark;
                stud_arr[i].geo_mark = buffer.geo_mark;
                stud_arr[i].prog_mark = buffer.prog_mark;
                stud_arr[i].average = ((double)(buffer.geo_mark + buffer.ma_mark + buffer.prog_mark)) / 3.0;
                break;
            }
        }

    }
    return stud_arr;
}