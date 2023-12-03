#include <fstream>
#include <iostream>

void set_number(const std::string& buf, int& part_num, int& part_size){
  while (part_size >= 0 && isdigit(buf[part_size]))
    --part_size;
  ++part_size;

  const int begin = part_size;

  while (isdigit(buf[part_size])){
    part_num *= 10;
    part_num += buf[part_size] - 48;
    ++part_size;
  }

  part_size -= begin;
}

int main(){
  std::ifstream file;
  file.open("day3_input");

  int total_1{}, total_2{};

  std::string buf[3];
  std::getline(file, buf[1]);
  while (!buf[1].empty()){
    std::getline(file, buf[2]);

    for (int i = 0; i < buf[1].length(); ++i){
      if (buf[1][i] != '.'){
        if (isdigit(buf[1][i])){
          /* int part_num{}, part_size = i; */

          /* set_number(buf[1], part_num, part_size); */

          /* for (int j = 0; j < 3; ++j){ */
          /*   bool broke{}; */

          /*   for (int k = i - 1; k <= i + part_size; ++k){ */
          /*     if (k >= 0 && k < buf[j].length()){ */
          /*       if (!isdigit(buf[j][k]) && buf[j][k] != '.'){ */
          /*         total_1 += part_num; */

          /*         broke = true; */
          /*         break; */
          /*       } */
          /*     } */
          /*   } */
          /*   if (broke) break; */
          /* } */

          /* i += part_size > 1 ? part_size - 1 : 0; */
        }
        else{
          int first_num[]{ -1, 0, 0, 0 }, second_num[]{ -1, 0, 0, 0 };
          bool broke{};

          for (int j = 0; j < 3; ++j){
            bool same{};

            for (int k = i - 1; k <= i + 1; ++k){
              if (k >= 0 && k < buf[j].length()){
                if (!same && isdigit(buf[j][k])){
                  same = true;
                  int part_num{}, part_size = k;

                  set_number(buf[j], part_num, part_size);

                  if (first_num[0] == -1){
                    first_num[0] = part_num; first_num[1] = j;
                    first_num[2] = k; first_num[3] = part_size;
                  }
                  else{
                    if (second_num[0] == -1){
                      second_num[0] = part_num; second_num[1] = j;
                      second_num[2] = k; second_num[3] = part_size;
                    }
                    else{
                      broke = true;
                      break;
                    }
                  }
                  continue;
                }
                else if (!isdigit(buf[j][k]))
                  same = false;
              }
            }
            if (broke) break;
          }

          if (second_num[0] != -1 && !broke){
            total_2 += first_num[0] * second_num[0];

            for (int j = first_num[2]; j < first_num[2] + first_num[3]; ++j)
              buf[first_num[1]][j] = '.';
            for (int j = second_num[2]; j < second_num[2] + second_num[3]; ++j)
              buf[second_num[1]][j] = '.';
          }
        }
      }
    }

    buf[0] = buf[1]; buf[1] = buf[2];
  }

  std::cout << total_1 << std::endl
    << total_2 << std::endl;
}
