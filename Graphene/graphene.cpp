#include "graphene.hpp"
#include "constants.hpp"

// Конструктор графена на основе вектора, состоящего из атомов
Graphene::Graphene(vector<Atom> const atoms)
  : m_atoms(atoms)
{
  CreateMat();
}

// Конструктор копирования
Graphene::Graphene(Graphene const & graphene)
  : m_mat(graphene.getMat()), m_atoms(graphene.getAtoms())
{}

// Конструктор графена, смещающий i атом графена на dx вдоль направления x (n=0), y (n=1), z (n=2)
Graphene::Graphene(Graphene graphene, int const k, int const n, double const dx)
  : m_mat(graphene.getMat()), m_atoms(graphene.getAtoms())
{
  switch (n)
  {
  case 0:
    m_atoms[k].plusX(dx);
    break;
  case 1:
    m_atoms[k].plusY(dx);
    break;
  case 2:
    m_atoms[k].plusZ(dx);
    break;
  default:
    cout << "n error" << endl;
    break;
  }
}

// Геттеры
vector<Atom> const & Graphene::getAtoms() const { return m_atoms; }
vector<vector<int>> const & Graphene::getMat() const { return m_mat; }
int const Graphene::getN() const { return m_atoms.size(); }

// Сеттеры
void Graphene::setAtom(int const index, double const x, double const y, double const z)
{
  m_atoms[index] = Atom(x, y, z, m_atoms[index].getType());
}

// Основные мотоды

// Создание матрицы связей
void Graphene::CreateMat()
{
  vector<vector<int>> mat(getN(), vector<int>(3, 0));

  for (int i = 0; i < getN(); i++)
  {
    int count = 0;
    for (int j = 0; j < getN(); j++)
    {
      if (abs(R(i, j) - d) < f)
      {
        mat[i][count] = j + 1;
        count++;
      }
    }
  }

  m_mat = mat;
}

// Возвращает расстояние между i и j атомами
double Graphene::R(int const i, int const j) const
{
  return (sqrt(Square(m_atoms[i].getX() - m_atoms[j].getX())
    + Square(m_atoms[i].getY() - m_atoms[j].getY())
    + Square(m_atoms[i].getZ() - m_atoms[j].getZ())));
}

// Возращает угол ijk, j - центральный атом
double Graphene::ANG(int const i, int const j, int const k) const
{
  return (180.0 / PI * acos((R(i, j) * R(i, j) + R(j, k) * R(j, k) - R(i, k) * R(i, k)) / (2 * R(i, j) * R(j, k))));
}

// Минимальная координату по x в графене
double Graphene::minX() const
{
  double minX = MAXR;
  for (int i = 0; i < getN(); i++)
  {
    minX = (m_atoms[i].getX() < minX) ? m_atoms[i].getX() : minX;
  }
  return minX;
}

// Максимальная координата по x в графене
double Graphene::maxX() const
{
  double maxX = -MAXR;
  for (int i = 0; i < getN(); i++)
  {
    maxX = (m_atoms[i].getX() > maxX) ? m_atoms[i].getX() : maxX;
  }
  return maxX;
}

// Список номеров атомов, у которых максимальна и минимальна координата x
// Т.е. те атомы, которые мы будем растягивать
vector<double> Graphene::Out() const
{
  vector<double> result(getN());

  for (int i = 0; i < getN(); i++)
  {
    if (EqualsWithEps(m_atoms[i].getX(), maxX()))
      result[i] = 1;
    else if (EqualsWithEps(m_atoms[i].getX(), minX()))
      result[i] = -1;
  }

  return result;
}

// Энергия, зависящая от растояний между соседними атомами
double Graphene::Energy1() const
{
  double U = 0;

  for (int i = 0; i < getN(); i++)
    for (int j = i; j < getN(); j++)
      if (abs(R(i, j) - d) < eps)
        U = U + a * Square(abs(R(i, j) - d));

  return U;
}

// Энергия, зависящая от углов
double Graphene::Energy2() const
{
  double U = 0;
  for (int i = 0; i < getN(); i++)
  {
    U = U + b * Square(abs((ANG(m_mat[i][0] - 1, i, m_mat[i][1] - 1)) - 120));

    if (m_mat[i][2] != 0)
    {
      U = U + b * Square(abs((ANG(m_mat[i][0] - 1, i, m_mat[i][2] - 1)) - 120));
      U = U + b * Square(abs((ANG(m_mat[i][1] - 1, i, m_mat[i][2] - 1)) - 120));
    }
  }
  return U;
}

// Полная энергия
double Graphene::Energy() const
{
  return Energy1() + Energy2();
}

// Вычиление производной от энергии k - номер атома, который смещается на dx вдоль оси x (n=0), y (n=1), z (n=2)
double Graphene::EnergyDerivative(int const k, int const n, double const dx) const
{
  // Старая энергия
  double E1 = Energy();

  // Задаем новую энергию со смещением k-го атома на dx
  Graphene graphene_temp(*this, k, n, dx);
  double E2 = graphene_temp.Energy();

  return (E2 - E1) / dx;
}

// Оператор вывода в поток
ostream & operator << (ostream & os, Graphene const & graphene)
{
  os << "Graphene {" << graphene.getN() << "}" << endl;
  for each (Atom atom in graphene.getAtoms())
  {
    os << atom << endl;
  }
  return os;
}
