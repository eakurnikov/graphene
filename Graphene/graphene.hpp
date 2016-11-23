#pragma once

#include "atom.hpp"
#include "functions.hpp"
#include <iostream>
#include <sstream>
#include <vector>

class Graphene
{
private:
  // Графен - набор атомов
  vector<Atom> m_atoms;

  // Матрица связей, нужна для нахождения энергии
  vector<vector<int>> m_mat;

public:
  // Конструктор графена на основе вектора, состоящего из атомов
  Graphene(vector<Atom> const atoms);

  // Конструктор копирования
  Graphene(Graphene const & graphene);

  // Конструктор графена, смещающий i атом графена на dx вдоль направления x (n=0), y (n=1), z (n=2)
  Graphene(Graphene graphene, int const k, int const n, double const dx);

  // Геттеры
  vector<Atom> const & getAtoms() const;
  vector<vector<int>> const & getMat() const;
  int const getN() const;

  // Сеттеры
  void setAtom(int const index, double const x, double const y, double const z);

  // Основные мотоды

  // Создание матрицы связей
  void CreateMat();

  // Расстояние между i и j атомами
  double R(int const i, int const j) const;

  // Возращает угол ijk, j - центральный атом
  double ANG(int const i, int const j, int const k) const;

  // Минимальная координата по x в графене
  double minX() const;

  // Максимальная координата по x в графене
  double maxX() const;

  // Список номеров атомов, у которых максимальна и минимальна координата x
  // Т.е. те атомы, которые мы будем растягивать
  vector<double> Out() const;

  // Энергия, зависящая от растояний между соседними атомами
  double Energy1() const;

  // Энергия, зависящая от углов
  double Energy2() const;

  // Полная энергия
  double Energy() const;

  // Вычиление производной от энергии k - номер атома, который смещается на dx вдоль оси x (n=0), y (n=1), z (n=2)
  double EnergyDerivative(int const k, int const n, double const dx) const;
};

// Оператор вывода в поток
ostream & operator << (ostream & os, Graphene const & graphene);
