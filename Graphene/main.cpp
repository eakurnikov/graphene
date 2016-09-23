#include "graphene.hpp"
#include "fileio.hpp"
#include "functions.hpp"
#include "constants.hpp"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
  setlocale(LC_ALL, "ru");
  
  // Создание графена на основе файла 
  Graphene graphene(FileToVector("graphene.txt"));

  int const N = graphene.getN();

  // Проверка правильности заполнения графена.
  cout << graphene << endl;

  // Проверка правильности заполнения матрицы связей.
  Print("Матрица связей", graphene.getMat());

  // Максимальная и минимальная координаты x в графене
  double x_max = graphene.maxX();
  double x_min = graphene.minX();

  // Список внешних атомов (за них мы растягиваем графен)
  vector<double> out_atoms = graphene.Out();

  //------------------------------------------------------
  // Основной цикл
  //------------------------------------------------------
  
  // Набор сил
  vector<double> F(NF);
  F[0] = startF;
  for (int i = 1; i < F.size(); i++)
    F[i] = F[i - 1] + dF;

  // Набор энергий, соответсвующих силам
  vector<double> E(NF);

  // Набор квадратов сил для нахождени k
  vector<double> sqF(NF);
  for (int i = 0; i < F.size(); i++)
    sqF[i] = F[i] * F[i];

  // Печать
  cout << "E1 = " << graphene.Energy1() << endl;
  cout << "E2 = " << graphene.Energy2() << endl;
  cout << "E = " << graphene.Energy() << endl;

  for (int k = 0; k < NF; k++)
  {
    // Начальные силы, действующие на атомы (N атомов, 3 компоненты)       
    vector<vector<double>> force0(N, vector<double>(3,0));
    for (int i = 0; i < N; i++)
      force0[i][0] += out_atoms[i] * F[k];

    // Начальные структура графена
    Graphene graphene1(graphene);

    // Структура графена на следующем шаге
    Graphene graphene2(graphene);

    // Начальные силы, действующие на атомы (Копирование force0 в force1)
    vector<vector<double>> force1(force0);

    // Силы, действующие на атомы, на следующем шаге
    vector<vector<double>> force2(N, vector<double>(3, 0));

    // Переменная для прекращения бесконечного цикла
    int J = 0;

    cout << "Процесс запущен" << endl;

    do
    {
      // Считаем новые координаты атомов
      for (int i = 0; i < N; i++)
      {
        graphene2.setAtom(i, graphene1.getAtoms()[i].getX() + force1[i][0] * step,
                             graphene1.getAtoms()[i].getY() + force1[i][1] * step,
                             graphene1.getAtoms()[i].getZ() + force1[i][2] * step);
      }

      // Считаем новые силы
      for (int i = 0; i < N; i++)
      {
        force2[i][0] = -graphene2.EnergyDerivative(i, 0, dx) + force0[i][0];
        force2[i][1] = -graphene2.EnergyDerivative(i, 1, dx) + force0[i][1];
        force2[i][2] = -graphene2.EnergyDerivative(i, 2, dx) + force0[i][2];
      }
      J++;

      // Переходим с k на k+1 
      graphene1 = graphene2;
      force1 = force2;

    } while ((Flag(force2)) && J < J_MAX);

    E[k] = graphene2.Energy();

    // Печатаем
    cout << "F = " << F[k] << ", E = " << E[k] << endl;
  }

  // Печать результатов
  cout << endl << "Результаты:" << endl << endl;

  Print("E", E);
  Print("f^2", sqF);

  cout << endl << "k = " << OLS(sqF, E) << endl;

  system("pause");
  return 0;
}
