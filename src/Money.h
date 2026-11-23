#pragma once

#include <cstddef>
#include <iostream>

class Money {
public:
    Money() = default;
    Money(long long hryvnias, int kopecks);

    long long hryvnias() const;
    int kopecks() const;
    long long totalCents() const;

    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    Money& operator*=(int factor);
    Money operator-() const;

private:
    long long cents_ = 0;
};

Money operator+(Money lhs, const Money& rhs);
Money operator-(Money lhs, const Money& rhs);
Money operator*(Money lhs, int factor);
Money operator*(int factor, Money rhs);

bool operator==(const Money& lhs, const Money& rhs);
bool operator<(const Money& lhs, const Money& rhs);
inline bool operator!=(const Money& lhs, const Money& rhs) { return !(lhs == rhs); }
inline bool operator>(const Money& lhs, const Money& rhs)  { return rhs < lhs; }
inline bool operator<=(const Money& lhs, const Money& rhs) { return !(rhs < lhs); }
inline bool operator>=(const Money& lhs, const Money& rhs) { return !(lhs < rhs); }

std::ostream& operator<<(std::ostream& os, const Money& m);
std::istream& operator>>(std::istream& is, Money& m);