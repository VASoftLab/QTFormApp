#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <vector>

// Структура данных 3D точек после кластеризации
struct Data3DItem
{
    std::vector<int> vu;       // 2D координаты точки на изображении
    std::vector<double> xyz;   // 3D координаты точки в пространсве
    std::vector<int> rgb;      // Цвет точки
    int cluster;               // Номер кастера
};

struct Data3DVector
{
    std::vector<std::vector<int>> vu;       // 2D координаты точки на изображении
    std::vector<std::vector<double>> xyz;   // 3D координаты точки в пространсве
    std::vector<std::vector<int>> rgb;      // Цвет точки
    std::vector<int> cluster;               // Номер кастера
};
#endif // DATASTRUCTURE_H
