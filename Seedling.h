#pragma once

#include <string>
#include <tuple>
#include <iostream>
#include "Money.h"

// Саджанець — основний клас предметної області.
class Seedling {
public:
    Seedling() = default;

    Seedling(std::string varietyCode,
             std::string name,
             int ageYears,
             int heightCm,
             Money price);

    // ── Гетери ──
    const std::string& getVarietyCode() const { return varietyCode_; }
    const std::string& getName() const        { return name_; }
    int getAgeYears() const                   { return ageYears_; }
    int getHeightCm() const                   { return heightCm_; }
    const Money& getPrice() const             { return price_; }

    // ── Сетери (за потреби) ──
    void setPrice(Money p) { price_ = p; }

private:
    std::string varietyCode_ = "(no-code)";
    std::string name_ = "(unnamed)";
    int ageYears_ = 0;
    int heightCm_ = 0;
    Money price_{0, 0};
};

// ── Порівняння ──
// Рівність — за унікальним кодом сорту.
inline bool operator==(const Seedling& a, const Seedling& b) {
    return a.getVarietyCode() == b.getVarietyCode();
}
inline bool operator!=(const Seedling& a, const Seedling& b) { return !(a == b); }

// Порядок — лексикографічно за трьома полями: назва, вік, висота.
inline bool operator<(const Seedling& a, const Seedling& b) {
    return std::make_tuple(a.getName(), a.getAgeYears(), a.getHeightCm())
         < std::make_tuple(b.getName(), b.getAgeYears(), b.getHeightCm());
}
inline bool operator>(const Seedling& a, const Seedling& b)  { return b < a; }
inline bool operator<=(const Seedling& a, const Seedling& b) { return !(b < a); }
inline bool operator>=(const Seedling& a, const Seedling& b) { return !(a < b); }

// ── Введення / виведення ──
std::ostream& operator<<(std::ostream& os, const Seedling& s);
std::istream& operator>>(std::istream& is, Seedling& s);