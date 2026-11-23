#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <stdexcept>

#include "FruitSeedling.h"
#include "OrnamentalShrub.h"
#include "Nursery.h"
#include "NurseryOrder.h"
#include "DiamondExperiment.h"

// Тест 1: Валідація інваріантів конструктора базового та похідних класів
TEST(PlantingMaterialTest, ThrowsOnInvalidArguments) {
    EXPECT_THROW(
        FruitSeedling("", "Яблуня", 2, 150, Money(100, 0), "М9", true),
        std::invalid_argument
    );
    EXPECT_THROW(
        FruitSeedling("A-1", "Яблуня", -1, 150, Money(100, 0), "М9", true),
        std::invalid_argument
    );
    EXPECT_THROW(
        FruitSeedling("A-1", "Яблуня", 2, 150, Money(100, 0), "", true),
        std::invalid_argument
    );
    EXPECT_THROW(
        OrnamentalShrub("S-1", "Бузок", 2, 120, Money(100, 0), "", "фіолетовий"),
        std::invalid_argument
    );
}

// Тест 2: Поліморфне обчислення ціни та власні методи FruitSeedling
TEST(FruitSeedlingTest, CalculatesFinalPriceAndYield) {
    FruitSeedling dwarfApple("A-1", "Чемпіон", 3, 150, Money(200, 0), "М9", true);
    FruitSeedling standardPear("P-1", "Дюшес", 2, 170, Money(200, 0), "Сіянець", false);

    EXPECT_EQ(dwarfApple.calculateFinalPrice(), Money(230, 0));
    EXPECT_EQ(standardPear.calculateFinalPrice(), Money(200, 0));

    EXPECT_DOUBLE_EQ(dwarfApple.expectedYieldKg(), 12.0);
    EXPECT_DOUBLE_EQ(standardPear.expectedYieldKg(), 12.0);
}

// Тест 3: Поліморфне обчислення ціни та власні методи OrnamentalShrub
TEST(OrnamentalShrubTest, CalculatesFinalPriceAndBloomingSeason) {
    OrnamentalShrub tallSummer("S-1", "Гортензія", 2, 120, Money(150, 0), "липень–серпень", "білий");
    OrnamentalShrub shortSpring("S-2", "Форзиція", 1, 75, Money(100, 0), "квітень", "жовтий");

    EXPECT_EQ(tallSummer.calculateFinalPrice(), Money(170, 0));
    EXPECT_TRUE(tallSummer.isSummerBlooming());

    EXPECT_EQ(shortSpring.calculateFinalPrice(), Money(100, 0));
    EXPECT_FALSE(shortSpring.isSummerBlooming());
}

// Тест 4: Поліморфна колекція Nursery (unique_ptr, фільтрація, загальна сума)
TEST(NurseryCollectionTest, StoresPolymorphicObjectsAndCalculatesTotal) {
    Nursery nursery;
    nursery.add(std::make_unique<FruitSeedling>("A-1", "Айдаред", 2, 140, Money(100, 0), "М9", true));       // 115.00
    nursery.add(std::make_unique<OrnamentalShrub>("S-1", "Спірея", 2, 110, Money(80, 0), "червень", "білий")); // 100.00

    EXPECT_EQ(nursery.size(), 2u);
    EXPECT_EQ(nursery.countByCategory("FRUIT"), 1u);
    EXPECT_EQ(nursery.countByCategory("SHRUB"), 1u);
    EXPECT_EQ(nursery.totalCatalogValue(), Money(215, 0));
}

// Тест 5: Серіалізація та поліморфне відновлення (save / load)
TEST(NurserySerializationTest, SavesAndRestoresDerivedTypesLosslessly) {
    Nursery original;
    original.add(std::make_unique<FruitSeedling>("F-10", "Слива Стенлей", 2, 160, Money(130, 50), "Алича", false));
    original.add(std::make_unique<OrnamentalShrub>("O-20", "Троянда плетиста", 1, 105, Money(180, 0), "червень–вересень", "червоний"));

    std::stringstream buffer;
    original.save(buffer);

    Nursery loaded;
    loaded.load(buffer);

    ASSERT_EQ(loaded.size(), 2u);
    EXPECT_EQ(loaded.at(0).category(), "FRUIT");
    EXPECT_EQ(loaded.at(1).category(), "SHRUB");
    EXPECT_EQ(loaded.totalCatalogValue(), original.totalCatalogValue());
}

// Тест 6: Композиція в класі NurseryOrder та розрахунок знижки
TEST(NurseryOrderCompositionTest, AppliesDiscountToComposedNurseryItems) {
    NurseryOrder order("Іван Петренко", 20); // 20% знижка
    order.addPlant(std::make_unique<FruitSeedling>("A-1", "Гала", 2, 150, Money(100, 0), "ММ-106", false)); // 100.00
    order.addPlant(std::make_unique<OrnamentalShrub>("S-1", "Самшит", 3, 60, Money(150, 0), "травень", "зелений")); // 150.00

    EXPECT_EQ(order.itemCount(), 2u);
    EXPECT_EQ(order.calculateSubtotal(), Money(250, 0));
    EXPECT_EQ(order.calculateTotalWithDiscount(), Money(200, 0));
}

// Тест 7: Віртуальний деструктор (звільнення ресурсів похідного класу через базу)
TEST(PolymorphismTest, InvokesDerivedDestructorViaBasePointer) {
    struct TrackedPlant : public PlantingMaterial {
        bool* destroyedFlag;
        explicit TrackedPlant(bool* flag)
            : PlantingMaterial("T-1", "Тест", 1, 50, Money(10, 0)), destroyedFlag(flag) {}
        ~TrackedPlant() override { *destroyedFlag = true; }
        std::string category() const override { return "TEST"; }
        void saveRecord(std::ostream&) const override {}
    };

    bool destroyed = false;
    {
        std::unique_ptr<PlantingMaterial> ptr = std::make_unique<TrackedPlant>(&destroyed);
        EXPECT_FALSE(destroyed);
    }
    EXPECT_TRUE(destroyed);
}

// Тест 8: Експеримент із ромбоподібним успадкуванням
TEST(DiamondInheritanceTest, VirtualInheritanceSharesSingleBaseSubobject) {
    NonVirtualHybrid nv("ID-1", "ID-2", "М9", "білий");
    EXPECT_EQ(nv.NonVirtualFruit::getRegistryId(), "ID-1");
    EXPECT_EQ(nv.NonVirtualOrnamental::getRegistryId(), "ID-2");

    VirtualHybrid v("SHARED-ID", "М9", "білий");
    EXPECT_EQ(v.getRegistryId(), "SHARED-ID");
    v.setRegistryId("NEW-ID");
    EXPECT_EQ(v.VirtualFruit::getRegistryId(), "NEW-ID");
    EXPECT_EQ(v.VirtualOrnamental::getRegistryId(), "NEW-ID");
}