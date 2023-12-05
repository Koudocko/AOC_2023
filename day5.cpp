#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>

int main(){
  std::vector<std::tuple<bool, long, long>> sources;
  std::ifstream file;
  file.open("day5_input");

  std::string buf;
  std::getline(file, buf);
  
  std::stringstream seeds(buf.substr(buf.find(':') + 1));
  long seed_start{}, seed_length{};

  /* while (seeds >> seed_start >> seed_length) */
  /*   sources.emplace_back(true, seed_start, seed_length); */

  while (seeds >> seed_start)
    sources.emplace_back(true, seed_start, 1);

  while (std::getline(file, buf)){
    if (buf.find(':') == std::string::npos && !buf.empty()){
      long destination_start{}, source_start{}, range_length{};
      std::stringstream conversion(buf);
      conversion >> destination_start >> source_start >> range_length;

      for (auto& source : sources){
        long curr_start = std::get<1>(source),
             curr_end = std::get<1>(source) + std::get<2>(source),
             source_end = source_start + range_length;

        if (curr_start < source_start &&
            curr_end > source_start){
          if (curr_end < source_end){
            std::get<2>(source) = source_start - curr_start;
            sources.emplace_back(
              false,
              source_start + (destination_start - source_start),
              (curr_end - source_start) + (destination_start - source_start)
            );
          }
          else{
            std::get<2>(source) = source_start - curr_start;
            sources.emplace_back(
              false,
              source_start + (destination_start - source_start),
              range_length + (destination_start - source_start)
            );
            sources.emplace_back(true, source_end, curr_end - source_end);
          }
        }
        else if (curr_start > source_start &&
            curr_start < source_end){
          if (curr_end > source_end){
            source = {
              false,
              curr_start + (destination_start - source_start),
              (source_end - curr_start) + (destination_start - source_start)
            };
            sources.emplace_back(true, source_end, curr_end - source_end);
          }
          else{
            source = {
              false,
              curr_start + (destination_start - source_start),
              (curr_end - curr_start) + (destination_start - source_start)
            };
          }
        }
      }
    }
    else
      if (!buf.empty())
        for (auto& source : sources)
          std::get<0>(source) = true;
  }

  long min = sources.empty() ? 0 : std::get<1>(sources[0]);
  for (const auto& source : sources)
    min = std::min(min, std::get<1>(source));

  std::cout << min << std::endl;
}
