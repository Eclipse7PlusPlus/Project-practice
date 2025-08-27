#include "nikitasfuncs.h"
void OpenCheck(std::fstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
}

void OutputOpenCheck(std::fstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать файл: " + filename);
    }
}

void EmptyCheck(std::fstream& file, const std::string& filename) {
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        throw std::runtime_error("Файл пустой: " + filename);
    }
    file.seekg(0, std::ios::beg);
}

void CreateBinaryFile(const std::string& Textfilename, const std::string& Binaryfilename){
  std::ifstream file1_in(Textfilename);
  std::ofstream file11_in(Binaryfilename,std::ios::binary);

  std::string line;

    while (std::getline(file1_in, line)) {
      file11_in.write(line.c_str(), line.size());
      file11_in.put('\n');
    }
    file1_in.close();
    file11_in.close();
}

Student parseMarksLine(const std::string& line){

  Student student;
  std::istringstream iss(line);
  std::string token;
  std::getline(iss, token, ';'); // пропуск номера группы
    std::getline(iss, token, ';');
    student.zachet_number = std::stoi(token);
    
    std::getline(iss, token, ';'); // "МА"
    std::getline(iss, token, ';');
    student.ma_mark = std::stoi(token);
    
    std::getline(iss, token, ';'); // "ГЕО"
    std::getline(iss, token, ';');
    student.geo_mark = std::stoi(token);
    
    std::getline(iss, token, ';'); // "ПРОГ"
    std::getline(iss, token, ';');
    student.prog_mark = std::stoi(token);
    
    return student;
}
Student parseStudentLine(const std::string& line) {
    Student student;
    std::istringstream iss(line);
    std::string token;
    
    std::getline(iss, token, ';');
    student.zachet_number = std::stoi(token);
    
    std::getline(iss, student.surname, ';');
    std::getline(iss, student.name, ';');
    std::getline(iss, student.patronymic, ';');
    
    student.ma_mark = 0;
    student.geo_mark = 0;
    student.prog_mark = 0;
    
    return student;
}

void blabla(int a, std::fstream& out)
{
    int b{};
    int digit_count{};
    while(a!= 0)
    {
        b = 10*b + a%10;
        a /= 10;
        ++digit_count;
    }
    while(digit_count != 0)
    {
        out.put('0' + b%10);
        b/=10;
        --digit_count;
    }
}


void writeOneStudentToBinary(std::fstream& file, Student student) { 
    blabla(student.zachet_number,file);
    file.put(';');
    file.write(student.surname.c_str(), student.surname.size());
     file.put(';');
    
    file.write(student.name.c_str(), student.name.size());
    file.put(';');
    file.write(student.patronymic.c_str(), student.patronymic.size());

    file.put(';');
    blabla(student.ma_mark,file);
    file.put(';');
    blabla(student.geo_mark,file);
    file.put(';');
    blabla(student.prog_mark,file);
}

void WriteAllStudentsAverage(std::fstream& file, Student* stud_arr,int stud_count){
    for(int32_t i{};i<stud_count;++i){
        writeOneStudentToBinary(file,stud_arr[i]);
        file.put(';');
        OutputDecimalWithTwoDigits(stud_arr[i].average, file);
        file.put('\n');
    }
}


void WriteAllStudents(std::fstream& file, Student* stud_arr, int stud_count) {
    for (int32_t i{}; i < stud_count; ++i) {
        writeOneStudentToBinary(file, stud_arr[i]);
        file.put('\n');
    }
}


void OutputDecimalWithTwoDigits(double a, std::fstream& out)
{
    if (a == 10)
    {
        out.write("10", sizeof("10"));
    }
    else
    {
        out.put('0' + (int)a);
        out.put('.');
        for (int i{}; i < 2; ++i)
        {
            a -= (int)a;
            a *= 10;
            out.put('0' + (int)a);
        }
    }
    
}


double CalculateAverageScore(Student st) {
    return (st.ma_mark + st.geo_mark + st.prog_mark) / 3.0;
}

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
            file.write((stud.surname).c_str(), stud.surname.size());
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


void taskGG(std::fstream& file, Student * stud_arr, int stud_count, int group_number)
{
    int counter{};
    while(stud_arr[counter].group != group_number && counter < stud_count)
    {
        ++counter;
    }
    while(stud_arr[counter].group == group_number && counter < stud_count)
    {
        PutStudentInList(file, stud_arr[counter]);
        ++counter;
    }
}


void taskHH(std::fstream& file, Student *& stud_arr, int stud_count, int group_number)
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
    --right;
    selectionSort(&stud_arr[left], right - left + 1, averageCompare);
    for(int i = left; i < right; ++i)
    {
        PutStudentInList(file, stud_arr[i]);
        file.put('\n');
    }
    selectionSort(&stud_arr[left], right - left + 1, nameCompare);
}


bool checkClever(Student stud)
{
    return stud.geo_mark >= 8 && stud.ma_mark >= 8 && stud.prog_mark >= 8;
}


void taskII(std::fstream& file, Student* stud_arr, int stud_count)
{
    for (int i{}; i < stud_count; ++i)
    {
        if(checkClever(stud_arr[i]))
        {
            PutStudentInList(file, stud_arr[i]);
        }
    }
}


