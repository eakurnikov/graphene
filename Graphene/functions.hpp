#pragma once

#include "constants.hpp"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Вычисляет квадрат
double Square(double const x);

// Сравнивает 2 числа с учетом погрешности
bool EqualsWithEps(double const a, double const b);

// Скалярное произведение 2-х векторов
double Scalar(vector<double> const & X, vector<double> const & Y);

// Заполняет вектор единицами
void Ones(vector<double> & X);

// МНК возвращает k
double OLS(vector<double> const & X, vector<double> const & Y);

// Флаг, определяющий остановку выполнения цикла
bool Flag(vector<vector<double>> const & array);

// Метод для печати двумерного вектора int
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

// Метод для печати одномерного вектора
template <typename T> void Print(string const & s, vector<T> const & v)
{
  cout << s << endl;
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << '\t';
  cout << endl;
}


