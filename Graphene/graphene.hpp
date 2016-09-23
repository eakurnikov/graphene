#pragma once

#include "atom.hpp"
#include "functions.hpp"
#include <iostream>
#include <sstream>
#include <vector>

class Graphene
{
private:
  // ������ - ����� ������
  vector<Atom> m_atoms;

  // ������� ������, ����� ��� ���������� �������
  vector<vector<int>> m_mat;

public:
  // ����������� ������� �� ������ �������, ���������� �� ������
  Graphene(vector<Atom> const atoms);

  // ����������� �����������
  Graphene(Graphene const & graphene);

  // ����������� �������, ��������� i ���� ������� �� dx ����� ����������� x (n=0), y (n=1), z (n=2)
  Graphene(Graphene graphene, int const k, int const n, double const dx);

  // �������
  vector<Atom> const & getAtoms() const;
  vector<vector<int>> const & getMat() const;
  int const getN() const;

  // �������
  void setAtom(int const index, double const x, double const y, double const z);

  // �������� ������

  // �������� ������� ������
  void CreateMat();

  // ���������� ����� i � j �������
  double R(int const i, int const j) const;

  // ��������� ���� ijk, j - ����������� ����
  double ANG(int const i, int const j, int const k) const;

  // ����������� ���������� �� x � �������
  double minX() const;

  // ������������ ���������� �� x � �������
  double maxX() const;

  // ������ ������� ������, � ������� ����������� � ���������� ���������� x
  // �.�. �� �����, ������� �� ����� �����������
  vector<double> Out() const;

  // �������, ��������� �� ��������� ����� ��������� �������
  double Energy1() const;

  // �������, ��������� �� �����
  double Energy2() const;

  // ������ �������
  double Energy() const;

  // ��������� ����������� �� ������� k - ����� �����, ������� ��������� �� dx ����� ��� x (n=0), y (n=1), z (n=2)
  double EnergyDerivative(int const k, int const n, double const dx) const;
};

// �������� ������ � �����
ostream & operator << (ostream & os, Graphene const & graphene);