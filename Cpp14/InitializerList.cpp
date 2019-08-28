#include <array>
#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "Common.hpp"

using std::array;
using std::list;
using std::map;
using std::string;
using std::vector;
using std::pair;

using std::cout;
using std::endl;
using std::ostream;

using cpp14::PrintContainer;

/*
ostream& operator<<(ostream& out, const pair<int, array<string, 3> >& value)
{
  out << value.first << ":{\"" << value.second[0] << "\"," << value.second[1]
      << "\"," << value.second[2] << "\"}";

  return out;
}
*/
int main(int argc, char* argv[])
{
  vector<int>                 ivector      = { 1, 2, 3, 4 };
  array<float, 3>             farray       = { 1.2f, 2.3f, 4.5f };
  list<double>                dlist        = { 2.1, 3.2, 4.3, 5.4 };
  map<int, array<string, 3> > groupMembers = {
    { 1, { "Apple", "Ball", "Cat" } }, { 2, { "Dog", "Elephant", "Fox" } }
  };

  PrintContainer("ivector", ivector);
  PrintContainer("farray", farray);
  PrintContainer("dlist", dlist);
  PrintContainer("groupMembers", groupMembers);
}
