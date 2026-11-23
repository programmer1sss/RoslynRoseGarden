#pragma once // Захист від повторного підключення файлу

#include <string>   // Підключення std::string для текстових полів
#include <tuple>    // Підключення std::tuple для лексикографічного порівняння
#include <iostream> // Підключення потоків введення/виведення
#include "Money.h"  // Підключення класу Money для зберігання ціни

// Саджанець — основний клас предметної області.
class Seedling { // Оголошення класу Seedling
public: // Відкритий інтерфейс класу
    Seedling() = default; // Конструктор за замовчуванням

    Seedling(std::string varietyCode, // Конструктор з параметрами: код сорту,
             std::string name,        // назва саджанця,
             int ageYears,            // вік у роках,
             int heightCm,            // висота в сантиметрах,
             Money price);            // ціна саджанця

    // ── Гетери ──
    const std::string& getVarietyCode() const { return varietyCode_; } // Повертає код сорту за константним посиланням
    const std::string& getName() const        { return name_; }        // Повертає назву сорту за константним посиланням
    int getAgeYears() const                   { return ageYears_; }    // Повертає вік саджанця
    int getHeightCm() const                   { return heightCm_; }    // Повертає висоту саджанця
    const Money& getPrice() const             { return price_; }       // Повертає ціну саджанця

    // ── Сетери (за потреби) ──
    void setPrice(Money p) { price_ = p; } // Встановлює нову ціну для саджанця

private: // Закриті поля класу
    std::string varietyCode_ = "(no-code)"; // Унікальний код сорту (значення за замовчуванням)
    std::string name_ = "(unnamed)";        // Назва рослини/сорту
    int ageYears_ = 0;                      // Вік у роках
    int heightCm_ = 0;                      // Висота у сантиметрах
    Money price_{0, 0};                     // Ціна (за замовчуванням 0 грн 00 коп)
};

// ── Порівняння ──
// Рівність — за унікальним кодом сорту.
inline bool operator==(const Seedling& a, const Seedling& b) { // Оператор перевірки рівності двох саджанців
    return a.getVarietyCode() == b.getVarietyCode();           // Саджанці вважаються однаковими, якщо збігаються коди сортів
}
inline bool operator!=(const Seedling& a, const Seedling& b) { return !(a == b); } // Оператор нерівності

// Порядок — лексикографічно за трьома полями: назва, вік, висота.
inline bool operator<(const Seedling& a, const Seedling& b) { // Оператор "менше" для сортування
    return std::make_tuple(a.getName(), a.getAgeYears(), a.getHeightCm()) // Створюємо кортеж полів першого саджанця
         < std::make_tuple(b.getName(), b.getAgeYears(), b.getHeightCm()); // Порівнюємо з кортежем другого саджанця
}
inline bool operator>(const Seedling& a, const Seedling& b)  { return b < a; }    // Оператор "більше"
inline bool operator<=(const Seedling& a, const Seedling& b) { return !(b < a); } // Оператор "менше або дорівнює"
inline bool operator>=(const Seedling& a, const Seedling& b) { return !(a < b); } // Оператор "більше або дорівнює"

// ── Введення / виведення ──
std::ostream& operator<<(std::ostream& os, const Seedling& s); // Оголошення оператора виведення саджанця в потік
std::istream& operator>>(std::istream& is, Seedling& s);       // Оголошення оператора зчитування саджанця з потоку