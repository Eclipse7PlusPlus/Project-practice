#include"nikitasfuncs.h"


size_t returnIdxOfEdgeElem(Student * arr, int length, bool (*func_of_comp)(Student, Student))
{
    Student temp{arr[0]};
    size_t idx{};
    for (int i = 0; i < length; ++i)
    {
        if (func_of_comp(arr[i], temp))
        {
            idx = i;
            temp = arr[i];
        }
    }
    return idx;
}

void selectionSort(Student *arr, int length, bool (*func_of_comp)(Student, Student))
{
    for (int i = 0; i < length; ++i)
    {
        std::swap(arr[i], arr[i + returnIdxOfEdgeElem(arr + i, length - i, func_of_comp)]);
    }
}


bool numCompare(Student first, Student second)
{
    return first.group < second.group;
}

bool nameCompare(Student first, Student second)
{
    return first.surname + first.name + first.patronymic < second.surname + second.name + second.patronymic;
}

void sort(Student* stud_arr, int stud_count)
{
    selectionSort(stud_arr, stud_count, numCompare);
    for (int i{}; i < stud_count; ++i)
    {
        for(int j = i; j < stud_count; ++j)
        {
            if (j == stud_count-1 || stud_arr[i].group != stud_arr[j+1].group)
            {
                selectionSort(&(stud_arr[i]), j - i + 1, nameCompare);
                i = j;
                break;
            }
        }
    }
   
}


bool checkStupid(Student stud)
{
    return stud.ma_mark < 4 || stud.geo_mark < 4 || stud.prog_mark < 4;
}

bool averageCompare(Student first, Student second)
{
    return first.average > second.average;
}

void PutStudentInList(std::fstream& file, Student stud)
{
    blabla(stud.group, file);
            file.put(';');
            blabla(stud.zachet_number, file);
            file.put(';');
            file.write(stud.surname.c_str(), sizeof(stud.surname.c_str()));
            file.put('\n');
}
void taskDE(std::fstream& file, Student * stud_arr, int stud_count)
{
    for(int i{}; i < stud_count; ++i)
    {
        if(checkStupid(stud_arr[i]))
        {
            PutStudentInList(file, stud_arr[i]);
        }
    }
}


void taskG(std::fstream& file, Student * stud_arr, int stud_count, int group_number)
{
    int counter{};
    while(stud_arr[counter].group != group_number && counter < stud_count)
    {
        ++counter;
    }
    while(stud_arr[counter].group == group_number && counter < stud_count)
    {
        writeOneStudentToBinary(file, stud_arr[counter]);
        file.put('\n');
    }
}


void taskH(std::fstream& file, Student * stud_arr, int stud_count, int group_number)
{
    int left{};
    while(stud_arr[left].group != group_number && left < stud_count)
    {
        ++left;
    }
    int right = left;
    while(stud_arr[right].group == group_number && right < stud_count)
    {
        ++right;
    }
    selectionSort(&stud_arr[left], right - left + 1, averageCompare);
    for(int i = left; i < right; ++i)
    {
        writeOneStudentToBinary(file, stud_arr[i]);
        file.put('\n');
    }
    selectionSort(&stud_arr[left], right - left + 1, nameCompare);
}


bool checkClever(Student stud)
{
    return stud.geo_mark >= 8 && stud.ma_mark >= 8 && stud.prog_mark >= 8;
}


void taskI(std::fstream& file, Student* stud_arr, int stud_count)
{
    for (int i{}; i < stud_count; ++i)
    {
        if(checkClever(stud_arr[i]))
        {
            PutStudentInList(file, stud_arr[i]);
        }
    }
}


