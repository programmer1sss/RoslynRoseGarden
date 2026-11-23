#pragma once

#include "PlantingMaterial.h"

class FruitSeedling : public PlantingMaterial {
public:
    FruitSeedling(std::string varietyCode,
                  std::string name,
                  int ageYears,
                  int heightCm,
                  Money basePrice,
                  std::string rootstock,
                  bool isDwarf);

    const std::string& getRootstock() const { return rootstock_; }
    bool isDwarf() const                    { return isDwarf_; }

    // Змістовний власний метод: прогноз врожайності (кг/дерево)
    double expectedYieldKg() const;

    std::string category() const override { return "FRUIT"; }
    Money calculateFinalPrice() const override;
    std::string details() const override;
    void saveRecord(std::ostream& os) const override;

private:
    std::string rootstock_;
    bool isDwarf_ = false;
};