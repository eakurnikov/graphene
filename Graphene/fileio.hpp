#pragma once

#include "atom.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Чтение координат из файла
vector<Atom> FileToVector(string const & filename)
{
  vector<Atom> atoms;
  ifstream fin(filename);
  double x, y, z;
  char type;
  int i = 0;
  while (fin >> x && fin >> y && fin >> z && fin >> type)
    atoms.push_back(Atom(x, y, z, type));
  fin.close();
  return atoms;
}
