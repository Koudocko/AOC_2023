#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <algorithm>
#include <limits>

struct Range
{
    unsigned long long start;
    unsigned long long end;

    Range(unsigned long long _start, unsigned long long _end) : start(_start), end(_end) { };
};

struct MapData
{
    unsigned long long basicMappingValue;
    Range range;

    MapData(unsigned long long _basicMappingValue, Range _range) : basicMappingValue(_basicMappingValue), range(_range) { };

    unsigned long long findNextKey(const unsigned long long previousKey) const
    {
        return basicMappingValue + (previousKey - range.start);
    }
};

std::vector<Range> parseSeeds(const std::string line) noexcept
{
    std::string seedsPrefix, seeds;
    std::stringstream ss;
    std::vector<unsigned long long> seedNumbers;
    std::vector<Range> ranges;
    ss << line;
    std::getline(ss, seedsPrefix, ':');
    ss >> std::ws;
    std::getline(ss, seeds);
    ss.clear();
    ss << seeds;
    for (std::string num; std::getline(ss, num, ' ');)
    {
        seedNumbers.push_back(std::stol(num));
    }
    for (auto it = seedNumbers.begin(); it != seedNumbers.end(); it += 2)
    {
        auto start = *it;
        auto end = start + *(it + 1);
        ranges.push_back(Range(start, end));
    }
    return ranges;
}

MapData parseMapEntry(std::string line) noexcept
{
    std::stringstream ss;
    unsigned long long nextKey, rangeStart, rangeLength;
    ss << line;
    ss >> nextKey >> rangeStart >> rangeLength;
    return MapData(nextKey, Range(rangeStart, rangeStart + rangeLength));
}

std::vector<Range> findSubRanges(const Range &mainRange, const std::vector<MapData> &sortedMappings) noexcept
{
    std::vector<Range> result;


    unsigned long long mappingLowestX = sortedMappings[0].range.start;
    unsigned long long currentX = mainRange.start;
    int currentMappingIndex = 0;
    while (currentX < mainRange.end && currentMappingIndex < sortedMappings.size())
    {
        MapData currentMappingData = sortedMappings[currentMappingIndex];
        Range currentMappingRange = currentMappingData.range;
        if (currentX > currentMappingRange.end)
        {
            currentMappingIndex++;
            continue;
        }
        //сейчас мы находимся в пустоте
        unsigned long long holeStart = currentX;
        unsigned long long holeEnd = std::min(sortedMappings[currentMappingIndex].range.start, mainRange.end);
        //выделяем дырку в отдельный рендж; прямой маппинг
        if (holeStart < holeEnd)
        {
            result.push_back(Range(holeStart, holeEnd));
        }
        if (holeEnd == mainRange.end)
        {
            currentX = mainRange.end;
            break;
        }

        //если не дошли до конца, прописываем кусок от начала диапазона с маппингом до его конца или конца seed range
        currentX = std::max(currentMappingRange.start, mainRange.start);
        unsigned long long end = std::min(currentMappingRange.end, mainRange.end);

        unsigned long long offset = currentMappingRange.start - currentMappingData.basicMappingValue;
        unsigned long long mappedBeginning = currentX - offset;
        unsigned long long mappedEnd = end - offset;

        if (currentX < end)
        {
            result.push_back(Range(mappedBeginning, mappedEnd));
        }
        currentX = end;
        currentMappingIndex++;
        //если дальше есть дырка, она рассмотрится как дырка перед диапазоном в следующей итерации или при выходе
    }

    //TODO если в конце дырка от маппинг-ренджа + 1 до mainRange.end
    if (currentX < mainRange.end)
    {
        result.push_back(Range(currentX, mainRange.end));
    }
    return result;
}

unsigned long long findLowestLocation(const Range &seedRange, const std::vector<std::vector<MapData>> &maps, const int currentMapIndex) noexcept
{
    if (maps.size() == currentMapIndex)
    {
        return seedRange.start;
    }
    auto subRanges = findSubRanges(seedRange, maps[currentMapIndex]);
    unsigned long long minLocation = std::numeric_limits<unsigned long long>::max();
    for (auto &range : subRanges)
    {
        unsigned long long location = findLowestLocation(range, maps, currentMapIndex + 1);
        if (location < minLocation)
        {
            minLocation = location;
        }
    }
    return minLocation;
}

int main()
{
    std::ifstream x;
    x.open("day5_input");
    std::string line;
    std::getline(x, line);
    std::vector<Range> seeds = parseSeeds(line);
    std::vector<std::vector<MapData>> maps;

    while (std::getline(x, line))
    {
        if (line.length() == 0)
        {
            maps.push_back(std::vector<MapData> {});
        }
        else
        {
            bool mentionsMap = line.find("map:") != std::string::npos;
            if (!mentionsMap)
            {
                auto mapData = parseMapEntry(line);
                maps.back().push_back(mapData);
            }
        }
    }
    for (auto &it : maps)
    {
        std::sort(
            it.begin(),
            it.end(),
            [](const MapData &a, const MapData &b) { return a.range.start < b.range.start; }
        );
    }
    std::vector<unsigned long long> locations {};
    for (const auto &seed : seeds)
    {
        locations.push_back(findLowestLocation(seed, maps, 0));
    }
    unsigned long long lowestLocation = *(std::min_element(locations.begin(), locations.end()));
    std::cout << "Lowest location is " << lowestLocation << std::endl;
    return 0;
}
