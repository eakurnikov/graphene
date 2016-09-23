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
  
  // �������� ������� �� ������ ����� 
  Graphene graphene(FileToVector("graphene.txt"));

  int const N = graphene.getN();

  // �������� ������������ ���������� �������.
  cout << graphene << endl;

  // �������� ������������ ���������� ������� ������.
  Print("������� ������", graphene.getMat());

  // ������������ � ����������� ���������� x � �������
  double x_max = graphene.maxX();
  double x_min = graphene.minX();

  // ������ ������� ������ (�� ��� �� ����������� ������)
  vector<double> out_atoms = graphene.Out();

  //------------------------------------------------------
  // �������� ����
  //------------------------------------------------------
  
  // ����� ���
  vector<double> F(NF);
  F[0] = startF;
  for (int i = 1; i < F.size(); i++)
    F[i] = F[i - 1] + dF;

  // ����� �������, �������������� �����
  vector<double> E(NF);

  // ����� ��������� ��� ��� ��������� k
  vector<double> sqF(NF);
  for (int i = 0; i < F.size(); i++)
    sqF[i] = F[i] * F[i];

  // ������
  cout << "E1 = " << graphene.Energy1() << endl;
  cout << "E2 = " << graphene.Energy2() << endl;
  cout << "E = " << graphene.Energy() << endl;

  for (int k = 0; k < NF; k++)
  {
    // ��������� ����, ����������� �� ����� (N ������, 3 ����������)       
    vector<vector<double>> force0(N, vector<double>(3,0));
    for (int i = 0; i < N; i++)
      force0[i][0] += out_atoms[i] * F[k];

    // ��������� ��������� �������
    Graphene graphene1(graphene);

    // ��������� ������� �� ��������� ����
    Graphene graphene2(graphene);

    // ��������� ����, ����������� �� ����� (����������� force0 � force1)
    vector<vector<double>> force1(force0);

    // ����, ����������� �� �����, �� ��������� ����
    vector<vector<double>> force2(N, vector<double>(3, 0));

    // ���������� ��� ����������� ������������ �����
    int J = 0;

    cout << "������� �������" << endl;

    do
    {
      // ������� ����� ���������� ������
      for (int i = 0; i < N; i++)
      {
        graphene2.setAtom(i, graphene1.getAtoms()[i].getX() + force1[i][0] * step,
                             graphene1.getAtoms()[i].getY() + force1[i][1] * step,
                             graphene1.getAtoms()[i].getZ() + force1[i][2] * step);
      }

      // ������� ����� ����
      for (int i = 0; i < N; i++)
      {
        force2[i][0] = -graphene2.EnergyDerivative(i, 0, dx) + force0[i][0];
        force2[i][1] = -graphene2.EnergyDerivative(i, 1, dx) + force0[i][1];
        force2[i][2] = -graphene2.EnergyDerivative(i, 2, dx) + force0[i][2];
      }
      J++;

      // ��������� � k �� k+1 
      graphene1 = graphene2;
      force1 = force2;

    } while ((Flag(force2)) && J < J_MAX);

    E[k] = graphene2.Energy();

    // ��������
    cout << "F = " << F[k] << ", E = " << E[k] << endl;
  }

  // ������ �����������
  cout << endl << "����������:" << endl << endl;

  Print("E", E);
  Print("f^2", sqF);

  cout << endl << "k = " << OLS(sqF, E) << endl;

  system("pause");
  return 0;
}
