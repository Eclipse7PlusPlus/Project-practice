#include <iostream>
#include <fstream>
#include <string>
struct Student{
  std::string name;
  std::string surname;
  std::string patronymic;
  int32_t group;
  int32_t zachet_number;
  int32_t ma_mark;
  int32_t geo_mark;
  int32_t prog_mark;

};
int main(){
  std::ifstream file1_in("file1.txt");
  std::ifstream file2_in("file2.txt");
  std::ofstream marks("Marks-file.bin",std::ios::binary);
  
  system("pause");
  return 0;
}
