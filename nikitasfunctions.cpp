#include "nikitasfuncs.h"
void OpenCheck(std::ifstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
}

void OutputOpenCheck(std::ofstream& file, const std::string& filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать файл: " + filename);
    }
}

void EmptyCheck(std::ifstream& file, const std::string& filename) {
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

void blabla(int a, std::ofstream& out)
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


void writeOneStudentToBinary(std::ofstream& file, Student student) { 
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

void WriteAllStudentsAverage(std::ofstream& file, Student* stud_arr,int stud_count){
    for(int32_t i{};i<stud_count;++i){
        writeOneStudentToBinary(file,stud_arr[i]);
        file.put(';');
        OutputDecimalWithTwoDigits(stud_arr[i].average, file);
        file.put('\n');
    }
}


void WriteAllStudents(std::ofstream& file, Student* stud_arr, int stud_count) {
    for (int32_t i{}; i < stud_count; ++i) {
        writeOneStudentToBinary(file, stud_arr[i]);
        file.put('\n');
    }
}


void OutputDecimalWithTwoDigits(double a, std::ofstream& out)
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


bool CheckingStudentMarks(Student st) {
    return ((st.ma_mark < 4) || (st.geo_mark < 4) || (st.prog_mark < 4));
}

void GenerateListOfLowScoreStudents(Student* stud_arr, int stud_count, std::fstream& file) {
    for (int i{}; i < stud_count; ++i)
    {
        if (CheckingStudentMarks(stud_arr[i]))
        {
            blabla(st.group, file);
            file.put(';');
            blabla(st.zachet_number, file);
            file.put(';');
            file.write(st.surname.c_str(), st.surname.size());
            file.put('\n');
        }
    }
    
}


int32_t CountLowScoreStudents(Student* stud_arr, int32_t stud_count) {
    int32_t count{};
        for (int32_t i{}; i < stud_count; ++i) {
            if (CheckingStudentMarks(stud_arr[i])) {
                ++count;
            }
        }
        return count;
 }


Student* CreateArrWithtLowScoreStudents(Student * stud_arr, int32_t stud_count, int32_t& low_count) {
    low_count = CountLowScoreStudents(stud_arr, stud_count);
    if (low_count == 0) {
        return nullptr;
    }

            Student* low_score_arr = new Student[low_count];
            int index = 0;
            for (int i = 0; i < stud_count; ++i) {
                if (CheckingStudentMarks(stud_arr[i])) {
                    low_score_arr[index++] = stud_arr[i];
                }
            }
            return low_score_arr;
        }


void SortByGroupNumber(Student* arr,int32_t count){
    qsort(arr, count, sizeof(Student), Compare);
}


int32_t Compare(const void* x1, const void* x2){
    return ((Student*)x1->group - (Student*)x2->group);           
}


int32_t CompareInGroupBySurname(const void* x1, const void* x2) {
    if ((Student*)x1->group != (Student*)x2->group) {
        return (Student*)x1->group - (Student*)x2->group;
    }
    return ((Student*)x1->surname.Compare((Student*)x2->surname);
}


void SortStudentsByGroupThenSurname(Student* arr, int32_t count) {
    qsort(arr, count, sizeof(Student), CompareInGroupBySurname);
}