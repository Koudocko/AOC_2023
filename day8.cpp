#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

struct Path{
  std::string curr, left, right;
  int total{}, step{};
};

int main(){
  std::unordered_map<std::string, std::pair<std::string, std::string>> instructions;
  std::vector<Path> paths;

  std::ifstream file;
  file.open("day8_input");

  int total{}, lock{};

  std::string steps;
  std::getline(file, steps);

  std::string buf;
  while (std::getline(file, buf)){
    if (!buf.empty()){
      std::string curr = buf.substr(0, 3),
        left = buf.substr(7, 3),
        right = buf.substr(12, 3);

      instructions.insert_or_assign(curr, std::make_pair(left, right));

      if (curr.back() == 'A')
        paths.push_back(Path{ curr, left, right, 0, 0 });

      bool broke{};
      for (auto& path : paths){
        path.left = instructions[path.curr].first,
          path.right = instructions[path.curr].second;

        while (!path.left.empty() &&
              !path.right.empty()){
          if (path.curr.back() != 'Z'){
            std::cout << "1: " << path.curr << std::endl;
            path.curr = steps[path.step] == 'L' ? path.left : path.right,
              path.left = instructions[path.curr].first,
              path.right = instructions[path.curr].second;

            path.step = ++path.total % steps.length();
          }
          else{
            if((total = std::max(total, path.total)) != path.total){
            std::cout << "2: " << path.curr << std::endl;
              path.curr = steps[path.step] == 'L' ? path.left : path.right,
                path.left = instructions[path.curr].first,
                path.right = instructions[path.curr].second;

              path.step = ++path.total % steps.length();
            }
            else{
              std::cout << "NEW WALL: " << path.curr << std::endl;
              break;
            }
          }
        }
      }
    }
  }

  std::cout << total << std::endl;
}
