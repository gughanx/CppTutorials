#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::numeric_limits;
using std::sqrt;
using std::vector;

auto max(const vector<double>& dnumbers)
{
  auto maxVal = -numeric_limits<double>::max();
  for (auto it = dnumbers.begin(); it != dnumbers.end(); ++it)
  {
    if (maxVal < *it)
    {
      maxVal = *it;
    }
  }
  return maxVal;
}

auto MaxContainer = [](const auto& container) ->
    typename std::remove_reference<decltype(*container.begin())>::type
{
  auto maxVal = -numeric_limits<typename std::remove_reference<decltype(
      *container.begin())>::type>::max();
  for (auto it = container.begin(); it != container.end(); ++it)
  {
    if (maxVal < *it)
    {
      maxVal = *it;
    }
  }
  return maxVal;
};

int main(int argc, char* argv[])
{
  auto i = 10;
  cout << "The value of i is " << i << endl;

  auto f = 10.1f;
  cout << "The value of f is " << f << endl;

  auto d = sqrt(2.0);
  cout << "The value of d is " << d << endl;

  vector<decltype(d)> dnumbers;
  for (size_t i = 0; i < 100; ++i)
  {
    dnumbers.push_back(sqrt(i));
  }

  for (auto& dnumber : dnumbers)
  {
    dnumber += 100.981;
    cout << dnumber << "\t";
  }
  cout << endl
       << "=====> MaxContainer(" << MaxContainer(dnumbers) << ") max("
       << max(dnumbers) << ")" << endl;

  return EXIT_SUCCESS;
}
