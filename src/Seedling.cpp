#include "Seedling.h" // Підключення оголошення класу Seedling
#include <iomanip>    // Підключення std::quoted для коректного запису рядків у лапках
#include <stdexcept>  // Підключення стандартних винятків (std::invalid_argument)

Seedling::Seedling(std::string varietyCode, // Реалізація конструктора саджанця
                   std::string name,
                   int ageYears,
                   int heightCm,
                   Money price)
    : varietyCode_(std::move(varietyCode)), // Переміщуємо рядок коду сорту у поле класу (без зайвого копіювання)
      name_(std::move(name)),               // Переміщуємо рядок назви у поле класу
      ageYears_(ageYears),                  // Ініціалізуємо вік
      heightCm_(heightCm),                  // Ініціалізуємо висоту
      price_(price)                         // Ініціалізуємо ціну
{
    if (varietyCode_.empty()) // Перевіряємо, чи не порожній код сорту
        throw std::invalid_argument("Seedling: empty variety code"); // Генеруємо виняток при порожньому коді
    if (name_.empty())        // Перевіряємо, чи не порожня назва
        throw std::invalid_argument("Seedling: empty name");         // Генеруємо виняток при порожній назві
    if (ageYears_ < 0 || heightCm_ < 0) // Перевіряємо, чи не від'ємні вік або висота
        throw std::invalid_argument("Seedling: negative age/height"); // Генеруємо виняток при некоректних числах
}

// ── Виведення ──
std::ostream& operator<<(std::ostream& os, const Seedling& s) { // Реалізація виведення саджанця в потік
    const auto saved = os.flags(); // Зберігаємо поточні прапорці форматування потоку
    os << s.getVarietyCode() << ' '         // Виводимо код сорту та пробіл
       << std::quoted(s.getName()) << ' '   // Виводимо назву в лапках (щоб зберегти пробіли всередині назви)
       << s.getAgeYears() << ' '            // Виводимо вік та пробіл
       << s.getHeightCm() << ' '            // Виводимо висоту та пробіл
       << s.getPrice();                     // Виводимо ціну (викликається operator<< для Money)
    os.flags(saved); // Відновлюємо прапорці потоку
    return os;       // Повертаємо потік
}

// ── Введення ──
std::istream& operator>>(std::istream& is, Seedling& s) { // Реалізація зчитування саджанця з потоку
    std::string code; // Тимчасова змінна для коду сорту
    std::string name; // Тимчасова змінна для назви
    int age = 0;      // Тимчасова змінна для віку
    int height = 0;   // Тимчасова змінна для висоти
    Money price;      // Тимчасова змінна для ціни

    if (!(is >> code)) return is;              // Зчитуємо код сорту; при помилці виходимо
    if (!(is >> std::quoted(name))) return is; // Зчитуємо назву в лапках; при помилці виходимо
    if (!(is >> age)) return is;               // Зчитуємо вік; при помилці виходимо
    if (!(is >> height)) return is;            // Зчитуємо висоту; при помилці виходимо
    if (!(is >> price)) return is;             // Зчитуємо ціну; при помилці виходимо

    if (code.empty() || name.empty() || age < 0 || height < 0) { // Перевіряємо коректність зчитаних даних
        is.setstate(std::ios::failbit); // Якщо дані невалідні, переводимо потік у стан помилки
        return is;                      // Виходимо без зміни об'єкта s
    }

    s = Seedling(code, name, age, height, price); // Створюємо валідний об'єкт і присвоюємо його в s
    return is; // Повертаємо потік
}