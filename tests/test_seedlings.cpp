#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Seedling.h"
#include "Nursery.h"

// ── Money: арифметика і порівняння ──
TEST(MoneyTest, AdditionIsCommutative) {
    Money a(10, 50), b(25, 25);
    EXPECT_EQ(a + b, b + a);
}
TEST(MoneyTest, PlusEqualsMatchesPlus) {
    Money a(10, 50), b(25, 25);
    Money s1 = a + b;
    Money s2 = a; s2 += b;
    EXPECT_EQ(s1, s2);
}
TEST(MoneyTest, SixComparisonsConsistent) {
    Money a(10, 0), b(20, 0), c(10, 0);
    EXPECT_TRUE(a == c); EXPECT_FALSE(a != c);
    EXPECT_TRUE(a != b); EXPECT_FALSE(a == b);
    EXPECT_TRUE(a < b);  EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= c); EXPECT_TRUE(a >= c);
}

// ── Seedling: порівняння ──
TEST(SeedlingTest, EqualityByVarietyCode) {
    Seedling a("X-1", "Яблуня", 2, 150, Money(100, 0));
    Seedling b("X-1", "Яблуня", 2, 150, Money(200, 0));
    Seedling c("X-2", "Груша",  2, 150, Money(100, 0));
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
}
TEST(SeedlingTest, SortingByThreeFields) {
    std::vector<Seedling> v;
    v.emplace_back("A", "Груша",  3, 180, Money(0, 0));
    v.emplace_back("B", "Яблуня", 1, 120, Money(0, 0));
    v.emplace_back("C", "Яблуня", 2, 150, Money(0, 0));
    std::sort(v.begin(), v.end());
    EXPECT_EQ(v[0].getName(), "Груша");
    EXPECT_EQ(v[1].getAgeYears(), 1);
    EXPECT_EQ(v[2].getAgeYears(), 2);
}

// ── Seedling: << і >> ──
TEST(SeedlingTest, OutputFormat) {
    Seedling s("APPLE-1", "Антонівка", 2, 150, Money(125, 0));
    std::ostringstream os;
    os << s;
    EXPECT_EQ(os.str(), "APPLE-1 \"Антонівка\" 2 150 125.00");
}
TEST(SeedlingTest, RoundTripSingle) {
    Seedling orig("PEAR-2", "Лісова", 1, 120, Money(95, 50));
    std::ostringstream os; os << orig;
    std::istringstream is(os.str());
    Seedling restored;
    EXPECT_TRUE(static_cast<bool>(is >> restored));
    EXPECT_EQ(restored.getVarietyCode(), orig.getVarietyCode());
    EXPECT_EQ(restored.getName(), orig.getName());
    EXPECT_EQ(restored.getAgeYears(), orig.getAgeYears());
    EXPECT_EQ(restored.getHeightCm(), orig.getHeightCm());
    EXPECT_EQ(restored.getPrice(), orig.getPrice());
}

// ── Nursery: save / load ──
TEST(NurseryTest, SaveLoadRoundTrip) {
    Nursery n;
    n.add(Seedling("A", "Яблуня", 1, 100, Money(50, 0)));
    n.add(Seedling("B", "Груша",  2, 120, Money(70, 25)));
    n.add(Seedling("C", "Слива",  3, 130, Money(90, 50)));

    std::ostringstream os;
    n.save(os);

    Nursery n2;
    std::istringstream is(os.str());
    n2.load(is);

    ASSERT_EQ(n2.size(), n.size());
    EXPECT_TRUE(std::equal(n.items().begin(), n.items().end(),
                           n2.items().begin()));
}

// ── Stream: failbit на зіпсованому рядку ──
TEST(StreamTest, InvalidSeedlingSetsFailbit) {
    std::istringstream in("BAD-CODE \"Name\" -5 150 100.00");
    Seedling s;
    EXPECT_FALSE(static_cast<bool>(in >> s));
    EXPECT_TRUE(in.fail());
}
TEST(StreamTest, InvalidMoneySetsFailbit) {
    std::istringstream in("abc.def");
    Money m;
    EXPECT_FALSE(static_cast<bool>(in >> m));
    EXPECT_TRUE(in.fail());
}
