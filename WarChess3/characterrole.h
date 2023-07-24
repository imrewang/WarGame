#pragma once

#include "character.h"

class Sultan : public Character
{
public:
    Sultan(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};

class Teutonic : public Character
{
public:
    Teutonic(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};

class Hussars : public Character
{
public:
    Hussars(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};


class Dragoon : public Character
{
public:
    Dragoon(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};


class Mamluk : public Character
{
public:
    Mamluk(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};
