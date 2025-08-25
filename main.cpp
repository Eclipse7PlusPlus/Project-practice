#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

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

int main() {
    try {
        std::ifstream file1_in("file1.txt");
        std::ifstream file2_in("file2.txt");
        std::ofstream marks("Marks-file.bin", std::ios::binary);

        OpenCheck(file1_in, "file1.txt");
        OpenCheck(file2_in, "file2.txt");
        OutputOpenCheck(marks, "Marks-file.bin");

        EmptyCheck(file1_in, "file1.txt");
        EmptyCheck(file2_in, "file2.txt");

        std::cout << "Все файлы успешно открыты и не пустые!" << std::endl;

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
    }

    system("pause");
    return 0;
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


void writeStudentToBinary(std::ofstream& file, const Student& student) {
    size_t len;
    
    file.write(reinterpret_cast<const char*>(&student.zachet_number), sizeof(student.zachet_number));
    
    len = student.surname.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(student.surname.c_str(), len);
    
    len = student.name.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(student.name.c_str(), len);
    
    len = student.patronymic.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(student.patronymic.c_str(), len);
    
    file.write(reinterpret_cast<const char*>(&student.ma_mark), sizeof(student.ma_mark));
    file.write(reinterpret_cast<const char*>(&student.geo_mark), sizeof(student.geo_mark));
    file.write(reinterpret_cast<const char*>(&student.prog_mark), sizeof(student.prog_mark));
}

void mergeStudentsWithMarks(const std::string& studentsFile, const std::string& marksFile, const std::string& outputFile) {
    std::ifstream marksIn(marksFile);
    OpenCheck(marksIn, marksFile);
    
    Student marksData[100]; 
    
    std::string line;
    while (std::getline(marksIn, line) && marksCount < 100) {
        marksData[marksCount++] = parseMarksLine(line);
    }
    marksIn.close();
    
    std::ifstream studentsIn(studentsFile);
    OpenCheck(studentsIn, studentsFile);
    
    std::ofstream binaryOut(outputFile, std::ios::binary);
    OutputOpenCheck(binaryOut, outputFile);
    
    while (std::getline(studentsIn, line)) {
        Student student = parseStudentLine(line);
        
        for (int i = 0; i < marksCount; i++) {
            if (marksData[i].zachet_number == student.zachet_number) {
                student.ma_mark = marksData[i].ma_mark;
                student.geo_mark = marksData[i].geo_mark;
                student.prog_mark = marksData[i].prog_mark;
                break;
            }
        }
        
        writeStudentToBinary(binaryOut, student);
    }
    
    studentsIn.close();
    binaryOut.close();}