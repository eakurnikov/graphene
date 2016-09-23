#pragma once

#include <iostream>

using namespace std;

class Atom
{

private:
  // ���� - ��� 3 ���������� + ���
  double m_x, m_y, m_z;
  char m_type;

public:
  // �����������
  Atom(double const x, double const y, double const z, char const type);

  // ����������� �����������
  Atom(Atom const & atom);

  // �������
  void setX(double const x);
  void setY(double const y);
  void setZ(double const z);
  void setType(char const type);

  // �������
  double const & getX() const;
  double const & getY() const;
  double const & getZ() const;
  char const & getType() const;

  // �������� ������������
  Atom & operator = (Atom const & atom);

  // �������������� ������
  void plusX(double const x);
  void plusY(double const y);
  void plusZ(double const z);
};

// �������� ������ � �����
ostream & operator << (ostream & os, Atom const & atom);

