/*
--- Day 3: Gear Ratios ---

You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water source, but this is as far as he can bring you. You go inside.

It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.

"Aaah!"

You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.

The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one. If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.

The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

Your puzzle answer was 527369.
--- Part Two ---

The engineer finds the missing part and installs it in the engine! As the engine springs to life, you jump in the closest gondola, finally ready to ascend to the water source.

You don't seem to be going very fast, though. Maybe something is still wrong? Fortunately, the gondola has a phone labeled "help", so you pick it up and the engineer answers.

Before you can explain the situation, she suggests that you look out the window. There stands the engineer, holding a phone in one hand and waving with the other. You're going so slowly that you haven't even left the station. You exit the gondola.

The missing part wasn't the only issue - one of the gears in the engine is wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, there are two gears. The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?

Your puzzle answer was 73074886.
*/

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
          int part_num{}, part_size = i;

          set_number(buf[1], part_num, part_size);

          for (int j = 0; j < 3; ++j){
            bool broke{};

            for (int k = i - 1; k <= i + part_size; ++k){
              if (k >= 0 && k < buf[j].length()){
                if (!isdigit(buf[j][k]) && buf[j][k] != '.'){
                  total_1 += part_num;

                  broke = true;
                  break;
                }
              }
            }
            if (broke) break;
          }

          i += part_size > 1 ? part_size - 1 : 0;
        }
        else{
          int first_num = -1, second_num = -1;
          bool broke{};

          for (int j = 0; j < 3; ++j){
            bool same{};

            for (int k = i - 1; k <= i + 1; ++k){
              if (k >= 0 && k < buf[j].length()){
                if (!same && isdigit(buf[j][k])){
                  same = true;
                  int part_num{}, part_size = k;

                  set_number(buf[j], part_num, part_size);

                  if (first_num == -1)
                    first_num = part_num;
                  else{
                    if (second_num == -1)
                      second_num = part_num;
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

          if (second_num != -1 && !broke)
            total_2 += first_num * second_num;
        }
      }
    }

    buf[0] = buf[1]; buf[1] = buf[2];
  }

  std::cout << total_1 << std::endl
    << total_2 << std::endl;
}
