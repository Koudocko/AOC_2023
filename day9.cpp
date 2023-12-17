#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

int main(){
  std::ifstream file;
  file.open("day9_input");

  int total{};

  std::string buf;
  /* while (std::getline(file, buf)){ */
    /* int value{}; */

    /* std::stringstream history(buf); */
    /* std::stack<int> cache; */

    /* while (history >> value) */
    /*  cache.push(value); */

    /* std::vector<std::queue<int>> build; */
    /* build.push_back(std::queue<int>()); */
    /* build[0].push(cache.top()); */
    /* build[0].push((cache.pop(), cache.top())); */

    /* while (true){ */
    /*   for (int i = build.size() - 1; i >= 0; --i){ */
    /*     if (build[i].size() > 1){ */
    /*       std::cout << "A" << std::endl; */
    /*       int diff = build[i].front() - (build[i].pop(), build[i].front()); */

    /*       if (i == build.size() - 1){ */
    /*         build.push_back(std::queue<int>()); */
    /*         build.back().push(diff); */
    /*       } */
    /*       else */
    /*         build[i + 1].push(diff); */

    /*       break; */
    /*     } */
    /*     else if (i == 0){ */
    /*       std::cout << "B" << std::endl; */
    /*       build[i].push(cache.top()); */
    /*       cache.pop(); */
    /*     } */
    /*   } */
    /* } */
  /* } */

  while (std::getline(file, buf)){

  }

  std::cout << total << std::endl;
}
