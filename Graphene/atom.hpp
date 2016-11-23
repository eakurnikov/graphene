#pragma once

#include <iostream>

using namespace std;

class Atom
{

private:
  // Атом - это 3 координаты + тип
  double m_x, m_y, m_z;
  char m_type;

public:
  // Конструктор
  Atom(double const x, double const y, double const z, char const type);

  // Конструктор копирования
  Atom(Atom const & atom);

  // Сеттеры
  void setX(double const x);
  void setY(double const y);
  void setZ(double const z);
  void setType(char const type);

  // Геттеры
  double const & getX() const;
  double const & getY() const;
  double const & getZ() const;
  char const & getType() const;

  // Оператор присваивания
  Atom & operator = (Atom const & atom);

  // Дополнительные методы
  void plusX(double const x);
  void plusY(double const y);
  void plusZ(double const z);
};

// Оператор вывода в поток
ostream & operator << (ostream & os, Atom const & atom);


