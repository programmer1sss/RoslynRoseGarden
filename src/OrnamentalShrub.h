#pragma once

#include "PlantingMaterial.h"

class OrnamentalShrub : public PlantingMaterial {
public:
    OrnamentalShrub(std::string varietyCode,
                    std::string name,
                    int ageYears,
                    int heightCm,
                    Money basePrice,
                    std::string bloomingPeriod,
                    std::string flowerColor);

    const std::string& getBloomingPeriod() const { return bloomingPeriod_; }
    const std::string& getFlowerColor() const    { return flowerColor_; }

    // Змістовний власний метод: перевірка літнього цвітіння
    bool isSummerBlooming() const;

    std::string category() const override { return "SHRUB"; }
    Money calculateFinalPrice() const override;
    std::string details() const override;
    void saveRecord(std::ostream& os) const override;

private:
    std::string bloomingPeriod_;
    std::string flowerColor_;
};