#pragma once

#include "Role.h"

class Sultan : public Role
{
public:
    Sultan(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);
};

class Teutonic : public Role
{
public:
    Teutonic(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);
};

class Hussars : public Role
{
public:
    Hussars(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);
};


class Dragoon : public Role
{
public:
    Dragoon(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);
};


class Mamluk : public Role
{
public:
    Mamluk(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);
};
