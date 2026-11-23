#pragma once // Захист від повторного підключення файлу

#include <vector>     // Підключення динамічного масиву std::vector
#include <iostream>   // Підключення потоків введення/виведення
#include "Seedling.h" // Підключення класу Seedling

// Розсадник — колекція саджанців з методами save/load.
class Nursery { // Оголошення класу Nursery (контейнер для саджанців)
public: // Відкриті методи класу
    Nursery() = default; // Конструктор за замовчуванням

    void add(Seedling s) { items_.push_back(std::move(s)); } // Додає саженец у вектор, використовуючи семантику переміщення

    std::size_t size() const { return items_.size(); } // Повертає поточну кількість саджанців у розсаднику
    Seedling&       at(std::size_t i)       { return items_.at(i); } // Доступ до саджанця за індексом з перевіркою меж (для зміни)
    const Seedling& at(std::size_t i) const { return items_.at(i); } // Константний доступ до саджанця за індексом (тільки для читання)

    const std::vector<Seedling>& items() const { return items_; } // Повертає константне посилання на весь внутрішній вектор

    void save(std::ostream& os) const; // Оголошення методу збереження каталогу в потік
    void load(std::istream& is);       // Оголошення методу завантаження каталогу з потоку

private: // Приватна секція
    std::vector<Seedling> items_; // Внутрішнє сховище саджанців
};