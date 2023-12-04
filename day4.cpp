#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main(){
  std::unordered_map<int, int> card_count;

  std::ifstream file;
  file.open("day4_input");

  int total_1{}, total_2{};
  int line_count{};

  std::string buf;
  while (std::getline(file, buf)){
    int line_total = ++card_count.insert({ line_count, 0 }).first->second;
    int points{}, part = buf.find('|');

    std::unordered_set<int> winning_nums;
    std::stringstream winning_stream(buf.substr(buf.find(':') + 1, part - 1));
    std::stringstream nums(buf.substr(part + 1));

    int num{};
    while (winning_stream >> num)
      winning_nums.insert(num);

    int next_card = ++line_count;
    while (nums >> num)
      if (winning_nums.find(num) != winning_nums.end()){
        points = points > 0 ? points * 2 : 1;
        card_count.insert({ next_card++, 0 }).first->second += line_total;
      }

    total_1 += points;
    total_2 += line_total;
  }

  std::cout << total_1 << std::endl
    << total_2 << std::endl;
}
