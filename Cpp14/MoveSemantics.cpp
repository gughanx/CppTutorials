#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "Common.hpp"

using std::array;
using std::vector;

using std::cout;
using std::endl;

using cpp14::PrintContainer;

/// A Surface class with copy and move constructors
class Surface
{
public:
#define USEDEFAULT1
#ifdef USEDEFAULT
  Surface()                 = default;
  Surface(const Surface& s) = default;
  Surface(Surface&& s)      = default;
#else
  Surface() {}
  Surface(const Surface& s)
  {
    cout << "***Copy constructor called!***" << endl;
  }
  Surface(Surface&& s)
      : vertices_(std::move(s.vertices_)), indices_(std::move(s.indices_))
  {
    cout << "***Move constructor called!***" << endl;
  }
#endif

  Surface(const vector<array<double, 3> >&       vertices,
          const vector<array<unsigned int, 3> >& indices)
      : vertices_(vertices), indices_(indices)
  {
  }

  void Print()
  {
    PrintContainer("Vertices", vertices_);
    PrintContainer("Indices", indices_);
  }

private:
  vector<array<double, 3> >       vertices_;
  vector<array<unsigned int, 3> > indices_;
};

template <size_t TX,
          size_t TY,
          size_t TZ,
          std::enable_if_t<(TX > 0)> = 0,
          std::enable_if_t<(TY > 0)> = 0,
          std::enable_if_t<(TZ > 0)> = 0>
class Workpiece
{
public:
  Workpiece()
  {
    voxels_ = std::make_unique<unsigned short[]>(TX * TY * TZ);
  }
  Workpiece(const Workpiece& s)
  {
      voxels_ = std::make_unique<unsigned short[]>(TX * TY * TZ);
  }
  Workpiece(Workpiece&& s)      = default;

private:
  std::unique_ptr<unsigned short[]> voxels_;
};

/// Function that generates a square surface
Surface GenerateSquareSurface(double size = 1.0)
{
  Surface s({ { 0.0, 0.0, 0.0 },
              { size, 0.0, 0.0 },
              { size, size, 0.0 },
              { 0.0, size, 0.0 } },
            { { 0, 1, 2 }, { 0, 2, 3 } });
  return std::move(s);
}

auto main() -> int
{
  cout << "Creating s..." << endl;
  Surface s({ { 0.0, 0.0, 0.0 },
              { 1.0, 0.0, 0.0 },
              { 1.0, 1.0, 0.0 },
              { 0.0, 1.0, 0.0 } },
            { { 0, 1, 2 }, { 0, 2, 3 } });

  cout << "Original surface:" << endl;
  s.Print();
  cout << endl;

  cout << "Creating s1..." << endl;
  Surface s1(s);
  cout << "Copied surface:" << endl;
  s1.Print();
  cout << "Original surface after being copied:" << endl;
  s.Print();
  cout << endl;

  cout << "Creating s2..." << endl;
  Surface s2(std::move(s));
  cout << "Move-constructed surface:" << endl;
  s2.Print();
  cout << "Original surface after being moved:" << endl;
  s.Print();
  cout << endl;

  Surface s3(GenerateSquareSurface(2.1));
  cout << "Move-constructed surface (from a function):" << endl;
  s3.Print();
  cout << endl;

  Surface s4(std::move(GenerateSquareSurface(5.1)));
  cout << "Move-constructed surface (from a function):" << endl;
  s4.Print();
  cout << endl;

  Surface s5 = GenerateSquareSurface(6.1);
  cout << "Move-assigned surface (from a function):" << endl;
  s5.Print();
  cout << endl;
}
