#include "Seedling.h"
#include <iomanip>
#include <stdexcept>

Seedling::Seedling(std::string varietyCode,
                   std::string name,
                   int ageYears,
                   int heightCm,
                   Money price)
    : varietyCode_(std::move(varietyCode)),
      name_(std::move(name)),
      ageYears_(ageYears),
      heightCm_(heightCm),
      price_(price)
{
    if (varietyCode_.empty())
        throw std::invalid_argument("Seedling: empty variety code");
    if (name_.empty())
        throw std::invalid_argument("Seedling: empty name");
    if (ageYears_ < 0 || heightCm_ < 0)
        throw std::invalid_argument("Seedling: negative age/height");
}

// ── Виведення ──
std::ostream& operator<<(std::ostream& os, const Seedling& s) {
    const auto saved = os.flags();
    os << s.getVarietyCode() << ' '
       << std::quoted(s.getName()) << ' '
       << s.getAgeYears() << ' '
       << s.getHeightCm() << ' '
       << s.getPrice();
    os.flags(saved);
    return os;
}

// ── Введення ──
std::istream& operator>>(std::istream& is, Seedling& s) {
    std::string code;
    std::string name;
    int age = 0;
    int height = 0;
    Money price;

    if (!(is >> code)) return is;
    if (!(is >> std::quoted(name))) return is;
    if (!(is >> age)) return is;
    if (!(is >> height)) return is;
    if (!(is >> price)) return is;

    if (code.empty() || name.empty() || age < 0 || height < 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    s = Seedling(code, name, age, height, price);
    return is;
}