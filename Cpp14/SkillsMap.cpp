#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

#include "Common.hpp"

using std::list;
using std::string;
using std::unordered_map;
using std::vector;

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

using cpp14::PrintContainer;

/// Read lines from the given file as a list of strings.
auto ReadListFromFile(const string& filename)
{
  list<string> items;

  ifstream fin(filename);
  if (fin.is_open())
    while (!fin.eof())
    {
      string item;
      getline(fin, item);
      if (!item.empty())
        items.push_back(item);
    }

  return move(items);
}

auto clamp = [](auto min, auto max, auto value) -> decltype(value) {
  if (value < static_cast<decltype(value)>(min))
    value = min;
  else if (value > static_cast<decltype(value)>(max))
    value = max;
  return value;
};

int main(int argc, char* argv[])
{
  auto skills  = ReadListFromFile("skills");
  auto persons = ReadListFromFile("persons");
  PrintContainer("Skills", skills);
  PrintContainer("Persons", persons);

  unordered_map<string, unordered_map<string, unsigned int> > skillDistribution;

  for (auto const& person : persons)
    for (auto const& skill : skills)
    {
      int level;
      cout << "Skill level of " << person << " on " << skill
           << " is (scale of 1-5): ";
      cin >> level;
      skillDistribution[person][skill] = clamp(1, 5.0, level);
    }

  unordered_map<string, unsigned int> teamSkillLevel;
  std::for_each(std::begin(skillDistribution),
                std::end(skillDistribution),
                [&teamSkillLevel](const auto& personSkillLevel) {
                  for (auto& skill : personSkillLevel.second)
                    teamSkillLevel[skill.first] += skill.second;
                });

  PrintContainer("Team Skill Level", teamSkillLevel);
}
