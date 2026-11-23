#include "Money.h" // Підключення відповідного заголовного файлу класу Money
#include <iomanip> // Підключення маніпуляторів форматування (std::setw, std::setfill)
#include <string>  // Підключення класу рядків std::string

Money::Money(long long hryvnias, int kopecks) // Реалізація конструктора з параметрами
    : cents_(hryvnias * 100 + kopecks) {}     // Переводимо гривні в копійки та додаємо копійки

long long Money::hryvnias() const { return cents_ / 100; }               // Ділимо на 100 націло, отримуючи гривні
int Money::kopecks() const { return static_cast<int>(cents_ % 100); }    // Беремо остачу від ділення на 100 для копійок
long long Money::totalCents() const { return cents_; }                   // Повертаємо загальну кількість копійок

Money& Money::operator+=(const Money& other) { cents_ += other.cents_; return *this; } // Додаємо копійки іншого об'єкта і повертаємо поточний
Money& Money::operator-=(const Money& other) { cents_ -= other.cents_; return *this; } // Віднімаємо копійки іншого об'єкта і повертаємо поточний
Money& Money::operator*=(int factor) { cents_ *= factor; return *this; }               // Множимо копійки на цілий коефіцієнт

Money Money::operator-() const { // Реалізація унарного мінуса
    Money result = *this;        // Створюємо копію поточного об'єкта
    result *= -1;                // Змінюємо знак суми на протилежний
    return result;               // Повертаємо новий об'єкт
}

Money operator+(Money lhs, const Money& rhs) { lhs += rhs; return lhs; } // Додаємо rhs до копії lhs і повертаємо результат
Money operator-(Money lhs, const Money& rhs) { lhs -= rhs; return lhs; } // Віднімаємо rhs від копії lhs і повертаємо результат
Money operator*(Money lhs, int factor) { lhs *= factor; return lhs; }    // Множимо копію lhs на factor і повертаємо результат
Money operator*(int factor, Money rhs) { rhs *= factor; return rhs; }    // Множимо копію rhs на factor (для комутативності)

bool operator==(const Money& lhs, const Money& rhs) { // Перевірка рівності двох об'єктів Money
    return lhs.totalCents() == rhs.totalCents();      // Порівнюємо загальну кількість копійок
}

bool operator<(const Money& lhs, const Money& rhs) {  // Перевірка, чи перша сума менша за другу
    return lhs.totalCents() < rhs.totalCents();       // Порівнюємо загальну кількість копійок
}

std::ostream& operator<<(std::ostream& os, const Money& m) { // Реалізація виведення грошей у потік
    const auto saved = os.flags(); // Зберігаємо поточні налаштування форматування потоку
    
    if (m.totalCents() < 0) { // Якщо сума від'ємна
        os << '-';            // Виводимо знак мінус
    }
    
    long long absCents = m.totalCents();        // Отримуємо загальну кількість копійок
    if (absCents < 0) absCents = -absCents;     // Беремо модуль (абсолютне значення) суми
    
    long long hryv = absCents / 100;            // Виділяємо цілу частину (гривні)
    int kop = static_cast<int>(absCents % 100); // Виділяємо дробову частину (копійки)

    os << hryv << '.' << std::setw(2) << std::setfill('0') << kop; // Виводимо у форматі ГРН.КОП (копійки завжди з 2 цифр)
    
    os.flags(saved); // Відновлюємо початкові прапорці потоку
    return os;       // Повертаємо посилання на потік
}

std::istream& operator>>(std::istream& is, Money& m) { // Реалізація зчитування грошей із потоку
    std::string s;        // Рядок для тимчасового зчитування токена
    if (!(is >> s)) {     // Якщо не вдалося зчитати слово з потоку
        return is;        // Повертаємо потік у стані помилки/кінця файлу
    }

    bool negative = false; // Прапорець від'ємного числа
    std::size_t pos = 0;   // Поточна позиція парсингу в рядку
    if (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) { // Якщо перший символ — знак '+' або '-'
        negative = (s[pos] == '-'); // Запам'ятовуємо, чи є число від'ємним
        ++pos;                      // Зсуваємо позицію на наступний символ
    }

    std::size_t dotPos = s.find('.', pos); // Шукаємо позицію десяткової крапки
    std::string hryvPart;                  // Рядок для частини гривень
    std::string kopPart;                   // Рядок для частини копійок

    if (dotPos == std::string::npos) { // Якщо крапки в рядку немає
        hryvPart = s.substr(pos);      // Весь залишок рядка — це гривні
        kopPart  = "0";                // Копійок немає (0)
    } else {                                        // Якщо крапка знайдена
        hryvPart = s.substr(pos, dotPos - pos);     // Вирізаємо підрядок гривень (від знаку до крапки)
        kopPart  = s.substr(dotPos + 1);            // Вирізаємо підрядок копійок (після крапки)
    }

    auto allDigits = [](const std::string& str) {   // Лямбда-функція для перевірки, чи складається рядок лише з цифр
        if (str.empty()) return false;              // Порожній рядок не є валідним числом
        for (char c : str) {                        // Проходимо по кожному символу рядка
            if (c < '0' || c > '9') return false;   // Якщо символ не цифра — повертаємо false
        }
        return true;                                // Усі символи є цифрами
    };

    if (!allDigits(hryvPart) || (dotPos != std::string::npos && !allDigits(kopPart))) { // Перевіряємо валідність гривень та копійок
        is.setstate(std::ios::failbit); // Встановлюємо прапорець помилки формату в потоці
        return is;                      // Перериваємо зчитування
    }

    long long hryv = 0; // Змінна для накопичення значення гривень
    for (char c : hryvPart) hryv = hryv * 10 + (c - '0'); // Перетворюємо рядок гривень у ціле число

    int kop = 0; // Змінна для значення копійок
    if (dotPos != std::string::npos) { // Якщо в рядку була крапка
        if (kopPart.size() > 2) {      // Якщо після крапки більше 2 цифр (некоректний формат копійок)
            is.setstate(std::ios::failbit); // Встановлюємо помилку потоку
            return is;                      // Виходимо з функції
        }
        while (kopPart.size() < 2) kopPart += '0'; // Доповнюємо нулем справа, якщо введена 1 цифра (напр. "5.5" -> "5.50")
        kop = (kopPart[0] - '0') * 10 + (kopPart[1] - '0'); // Перетворюємо дві цифри копійок у число
    }

    long long total = hryv * 100 + kop; // Обчислюємо загальну кількість копійок
    if (negative) total = -total;       // Застосовуємо знак мінус, якщо число було від'ємним

    m = Money(total / 100, static_cast<int>(total % 100)); // Формуємо новий об'єкт Money і записуємо в m
    return is; // Повертаємо потік
}