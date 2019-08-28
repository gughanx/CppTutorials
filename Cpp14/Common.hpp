#pragma once

#include <iostream>
#include <array>
#include <string>
#include <utility>

namespace cpp14
{
/// Lambda function to print any container.
/// Prints in the format: #varName: <element1, element2, element3, ...>
/// @param varName The name of the variable to be printed
/// @container The container object
auto PrintContainer = [](const std::string& varName,
                         const auto&        container,
                         std::ostream&      out = std::cout) {
  using std::endl;

  if (!varName.empty())
    out << varName << ": <";
  else
    out << "{";

  bool firstLoop = true;
  for (const auto& element : container)
  {
    if (firstLoop)
    {
      firstLoop = false;
    }
    else
    {
      out << ", ";
    }
    out << element;
  }

  if (!varName.empty())
    out << ">" << endl;
  else
    out << "}";
};

/// Overload operator >> to print a std::pair
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& value)
{
  out << value.first << ":" << value.second;
  return out;
}

/// Overload operator >> to print a std::array
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<T, N>& value)
{
  PrintContainer("", value, out);
  return out;
}

} // namespace cpp14
