#pragma once

#include "constants.hpp"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// ��������� �������
double Square(double const x);

// ���������� 2 ����� � ������ �����������
bool EqualsWithEps(double const a, double const b);

// ��������� ������������ 2-� ��������
double Scalar(vector<double> const & X, vector<double> const & Y);

// ��������� ������ ���������
void Ones(vector<double> & X);

// ��� ���������� k
double OLS(vector<double> const & X, vector<double> const & Y);

// ����, ������������ ��������� ���������� �����
bool Flag(vector<vector<double>> const & array);

// ����� ��� ������ ���������� ������� int
template <typename T> void Print(string const & s, vector<vector<T>> const & vv)
{
  cout << s << endl;
  for (int i = 0; i < vv.size(); i++)
  {
    for (int k = 0; k < vv[i].size(); k++)
      cout << vv[i][k] << '\t';
    cout << endl;
  }
}

// ����� ��� ������ ����������� �������
template <typename T> void Print(string const & s, vector<T> const & v)
{
  cout << s << endl;
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << '\t';
  cout << endl;
}


