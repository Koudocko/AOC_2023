#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>

using Seed = std::tuple<bool, long long, long long>;

int main(){
  std::vector<Seed> sources;
  std::ifstream file;
  file.open("day5_input");

  std::string buf;
  std::getline(file, buf);
  
  std::stringstream seeds(buf.substr(buf.find(':') + 1));
  long long seed_start{}, seed_length{};

  while (seeds >> seed_start >> seed_length)
    sources.emplace_back(true, seed_start, seed_length);

  /* while (seeds >> seed_start) */
  /*   sources.emplace_back(true, seed_start, 1); */

  while (std::getline(file, buf)){
    if (buf.find(':') == std::string::npos && !buf.empty()){
      long long destination_start{}, source_start{}, range_length{};
      std::vector<Seed> splits;

      std::stringstream conversion(buf);
      conversion >> destination_start >> source_start >> range_length;
      std::cout << "---NEWLINE--- " << destination_start << " " << source_start << " " << range_length << std::endl;

      for (auto& source : sources){
        long long curr_start = std::get<1>(source),
             curr_end = std::get<1>(source) + std::get<2>(source),
             source_end = source_start + range_length;

        if (curr_start < source_start &&
            curr_end > source_start){
          if (curr_end < source_end){
            std::cout << "1: " << curr_start << ", " << curr_end - curr_start << " =>" << std::endl;
            std::get<2>(source) = source_start - curr_start;
            std::cout << "\t" << std::get<1>(source) << ", " << std::get<2>(source) << std::endl;
            splits.emplace_back(
              false,
              source_start + (destination_start - source_start),
              (curr_end - source_start)
            );
            std::cout << "\t" << std::get<1>(splits.back()) << ", " << std::get<2>(splits.back()) << std::endl;
          }
          else{
            std::cout << "2: " << curr_start << ", " << curr_end - curr_start << " =>" << std::endl;
            std::get<2>(source) = source_start - curr_start;
            std::cout << "\t" << std::get<1>(source) << ", " << std::get<2>(source) << std::endl;
            splits.emplace_back(
              false,
              source_start + (destination_start - source_start),
              range_length
            );
            std::cout << "\t" << std::get<1>(splits.back()) << ", " << std::get<2>(splits.back()) << std::endl;
            splits.emplace_back(true, source_end, curr_end - source_end);
            std::cout << "\t" << std::get<1>(splits.back()) << ", " << std::get<2>(splits.back()) << std::endl;
          }
        }
        else if (curr_start >= source_start &&
            curr_start < source_end){
          if (curr_end > source_end){
            std::cout << "3: " << curr_start << ", " << curr_end - curr_start << " =>" << std::endl;
            source = {
              false,
              curr_start + (destination_start - source_start),
              (source_end - curr_start)
            };
            std::cout << "\t" << std::get<1>(source) << ", " << std::get<2>(source) << std::endl;
            splits.emplace_back(true, source_end, curr_end - source_end);
            std::cout << "\t" << std::get<1>(splits.back()) << ", " << std::get<2>(splits.back()) << std::endl;
          }
          else{
            std::cout << "4: " << curr_start << ", " << curr_end - curr_start << " =>" << std::endl;
            source = {
              false,
              curr_start + (destination_start - source_start),
              (curr_end - curr_start)
            };
            std::cout << "\t" << std::get<1>(source) << ", " << std::get<2>(source) << std::endl;
          }
        }
      }

      sources.insert(sources.end(), splits.begin(), splits.end());
    }
    else{
      if (!buf.empty()){
        std::cout << "===CONVERSION===" << std::endl;

        for (auto& source : sources){
          std::cout << "(" << std::get<1>(source) << ", " << std::get<2>(source) << ")" << " : ";
          std::get<0>(source) = true;
        }
        endl(std::cout);
      }
    }
  }

  /* long long min_pos = std::get<1>(*std::min_element( */
  /*   sources.begin(), sources.end(), */ 
  /*   [](const Seed& a, const Seed& b){ */
  /*     return std::get<1>(a) < std::get<1>(b); */
  /* })); */
  long long min = sources.empty() ? 0 : std::get<1>(sources[0]);
  int counter{};
  for (const auto& source : sources){
    std::cout << counter++ << ": " << std::get<1>(source) << ", " << std::get<2>(source) << std::endl;
    min = std::min(min, std::get<1>(source));
  }

  std::cout << min << std::endl;
  /* std::cout << min_pos << std::endl; */
}
