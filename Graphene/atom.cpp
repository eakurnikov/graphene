#include "atom.hpp"

// Конструктор
Atom::Atom(double const x, double const y, double const z, char const type)
  : m_x(x), m_y(y), m_z(z), m_type(type)
{}

// Конструктор копирования
Atom::Atom(Atom const & atom)
  : m_x(atom.getX()), m_y(atom.getY()), m_z(atom.getZ()), m_type(atom.getType())
{}

// Сеттеры
void Atom::setX(double const x) { m_x = x; };
void Atom::setY(double const y) { m_y = y; };
void Atom::setZ(double const z) { m_z = z; };
void Atom::setType(char const type) { m_type = type; };

// Геттеры
double const & Atom::getX() const { return m_x; };
double const & Atom::getY() const { return m_y; };
double const & Atom::getZ() const { return m_z; };
char const & Atom::getType() const { return m_type; };

// Дополнительные методы
void Atom::plusX(double const x) { m_x += x; };
void Atom::plusY(double const y) { m_y += y; };
void Atom::plusZ(double const z) { m_z += z; };

// Оператор присваивания
Atom & Atom::operator = (Atom const & atom)
{
  if (this == &atom) return *this;

  m_x = atom.getX();
  m_y = atom.getY();
  m_z = atom.getZ();
  m_type = atom.getType();

  return *this;
}

// Оператор вывода в поток
ostream & operator << (ostream & os, Atom const & atom)
{
  os << "Atom {" << atom.getX() << ", " << atom.getY() << ", " << atom.getZ() << ", " << atom.getType() << "}";
  return os;
}
