#include "graphene.hpp"
#include "constants.hpp"

// ����������� ������� �� ������ �������, ���������� �� ������
Graphene::Graphene(vector<Atom> const atoms)
  : m_atoms(atoms)
{
  CreateMat();
}

// ����������� �����������
Graphene::Graphene(Graphene const & graphene)
  : m_mat(graphene.getMat()), m_atoms(graphene.getAtoms())
{}

// ����������� �������, ��������� i ���� ������� �� dx ����� ����������� x (n=0), y (n=1), z (n=2)
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

// �������
vector<Atom> const & Graphene::getAtoms() const { return m_atoms; }
vector<vector<int>> const & Graphene::getMat() const { return m_mat; }
int const Graphene::getN() const { return m_atoms.size(); }

// �������
void Graphene::setAtom(int const index, double const x, double const y, double const z)
{
  m_atoms[index] = Atom(x, y, z, m_atoms[index].getType());
}

// �������� ������

// �������� ������� ������
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

// ���������� ���������� ����� i � j �������
double Graphene::R(int const i, int const j) const
{
  return (sqrt(Square(m_atoms[i].getX() - m_atoms[j].getX())
    + Square(m_atoms[i].getY() - m_atoms[j].getY())
    + Square(m_atoms[i].getZ() - m_atoms[j].getZ())));
}

// ��������� ���� ijk, j - ����������� ����
double Graphene::ANG(int const i, int const j, int const k) const
{
  return (180.0 / PI * acos((R(i, j) * R(i, j) + R(j, k) * R(j, k) - R(i, k) * R(i, k)) / (2 * R(i, j) * R(j, k))));
}

// ����������� ���������� �� x � �������
double Graphene::minX() const
{
  double minX = MAXR;
  for (int i = 0; i < getN(); i++)
  {
    minX = (m_atoms[i].getX() < minX) ? m_atoms[i].getX() : minX;
  }
  return minX;
}

// ������������ ���������� �� x � �������
double Graphene::maxX() const
{
  double maxX = -MAXR;
  for (int i = 0; i < getN(); i++)
  {
    maxX = (m_atoms[i].getX() > maxX) ? m_atoms[i].getX() : maxX;
  }
  return maxX;
}

// ������ ������� ������, � ������� ����������� � ���������� ���������� x
// �.�. �� �����, ������� �� ����� �����������
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

// �������, ��������� �� ��������� ����� ��������� �������
double Graphene::Energy1() const
{
  double U = 0;

  for (int i = 0; i < getN(); i++)
    for (int j = i; j < getN(); j++)
      if (abs(R(i, j) - d) < eps)
        U = U + a * Square(abs(R(i, j) - d));

  return U;
}

// �������, ��������� �� �����
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

// ������ �������
double Graphene::Energy() const
{
  return Energy1() + Energy2();
}

// ��������� ����������� �� ������� k - ����� �����, ������� ��������� �� dx ����� ��� x (n=0), y (n=1), z (n=2)
double Graphene::EnergyDerivative(int const k, int const n, double const dx) const
{
  // ������ �������
  double E1 = Energy();

  // ������ ����� ������� �� ��������� k-�� ����� �� dx
  Graphene graphene_temp(*this, k, n, dx);
  double E2 = graphene_temp.Energy();

  return (E2 - E1) / dx;
}

// �������� ������ � �����
ostream & operator << (ostream & os, Graphene const & graphene)
{
  os << "Graphene {" << graphene.getN() << "}" << endl;
  for each (Atom atom in graphene.getAtoms())
  {
    os << atom << endl;
  }
  return os;
}