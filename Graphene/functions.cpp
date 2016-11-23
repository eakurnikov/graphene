#include "functions.hpp"

using namespace std;

// Вычисляет квадрат
double Square(double const x)
{
  return x*x;
}

// Сравнивает 2 числа с учетом погрешности
bool EqualsWithEps(double const a, double const b)
{
  return (abs(a - b) < kEps) ? true : false;
}

// Скалярное произведение 2-х векторов
double Scalar(vector<double> const & X, vector<double> const & Y)
{
  double result = 0;
  if (X.size() != Y.size())
  {
    cout << "Different lengths of vectors: returned -1" << endl;
    return -1;
  }

  for (int i = 0; i < X.size(); i++)
    result += X[i] * Y[i];
  return result;
}

// Заполняет массив единицами
void Ones(vector<double> & X)
{
  for (int i = 0; i < X.size(); i++)
    X[i] = 1;
}

// МНК возвращает k
double OLS(vector<double> const & X, vector<double> const & Y)
{
  if (X.size() != Y.size())
  {
    cout << "Different lengths of vectors: returned -1" << endl;
    return -1;
  }

  vector<double> phi0(X.size());
  Ones(phi0);

  double A11 = Scalar(phi0, phi0);
  double A12 = Scalar(phi0, X);
  double A22 = Scalar(X, X);
  double F1 = Scalar(Y, phi0);
  double F2 = Scalar(Y, X);

  double k = (F1 * A12 - F2 * A11) / (A12 * A12 - A22 * A11);
  double b = (F1 - A12 * k) / A11;

  return k;
}

// Флаг, определяющий остановку выполнения цикла
bool Flag(vector<vector<double>> const & array)
{
  bool res = true;
  for (int i = 0; i < array.size(); i++)
    res = res && EqualsWithEps(abs(array[i][0]) - kEps2, 0.0)
              && EqualsWithEps(abs(array[i][1]) - kEps2, 0.0)
              && EqualsWithEps(abs(array[i][2]) - kEps2, 0.0);
  return !res;
}


