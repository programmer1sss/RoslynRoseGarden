#pragma once // Директива препроцесора для захисту від повторного включення заголовного файлу

#include <cstddef>  // Підключення стандартних типів даних (наприклад, std::size_t)
#include <iostream> // Підключення бібліотеки для роботи з потоками введення/виведення

class Money { // Оголошення класу Money для точного зберігання та обробки грошових сум
public: // Відкрита секція класу (доступна ззовні)
    Money() = default; // Конструктор за замовчуванням (ініціалізує суму нулем)
    Money(long long hryvnias, int kopecks); // Параметризований конструктор (приймає гривні та копійки)

    long long hryvnias() const;   // Метод-гетер: повертає кількість цілих гривень
    int kopecks() const;          // Метод-гетер: повертає залишок копійок (від 0 до 99)
    long long totalCents() const; // Метод-гетер: повертає загальну суму в копійках

    // ── Складені присвоєння ──
    Money& operator+=(const Money& other); // Перевантаження оператора додавання з присвоєнням
    Money& operator-=(const Money& other); // Перевантаження оператора віднімання з присвоєнням
    Money& operator*=(int factor);         // Перевантаження оператора множення на ціле число з присвоєнням
    Money operator-() const;               // Перевантаження унарного мінуса (зміна знаку суми)

private: // Приватна секція класу (інкапсуляція внутрішнього стану)
    long long cents_ = 0; // Поле класу: зберігає всю грошову суму в копійках (за замовчуванням 0)
};

// ── Арифметика ──
Money operator+(Money lhs, const Money& rhs); // Вільна функція: бінарне додавання двох сум
Money operator-(Money lhs, const Money& rhs); // Вільна функція: бінарне віднімання двох сум
Money operator*(Money lhs, int factor);       // Вільна функція: множення грошової суми на ціле число (справа)
Money operator*(int factor, Money rhs);       // Вільна функція: множення цілого числа на грошову суму (зліва)

// ── Порівняння ──
bool operator==(const Money& lhs, const Money& rhs); // Оператор перевірки на рівність
bool operator<(const Money& lhs, const Money& rhs);  // Оператор "менше"
inline bool operator!=(const Money& lhs, const Money& rhs) { return !(lhs == rhs); } // Оператор нерівності (через ==)
inline bool operator>(const Money& lhs, const Money& rhs)  { return rhs < lhs; }     // Оператор "більше" (через <)
inline bool operator<=(const Money& lhs, const Money& rhs) { return !(rhs < lhs); }  // Оператор "менше або дорівнює"
inline bool operator>=(const Money& lhs, const Money& rhs) { return !(lhs < rhs); }  // Оператор "більше або дорівнює"

// ── Виведення / введення ──
std::ostream& operator<<(std::ostream& os, const Money& m); // Оператор виведення суми у потік (формат ГРН.КОП)
std::istream& operator>>(std::istream& is, Money& m);       // Оператор зчитування суми з потоку