#pragma once

#include <string>
#include <iostream>
#include "Money.h"

class PlantingMaterial {
public:
    PlantingMaterial(std::string varietyCode,
                     std::string name,
                     int ageYears,
                     int heightCm,
                     Money basePrice);

    virtual ~PlantingMaterial() = default;

    // Константні геттери
    const std::string& getVarietyCode() const { return varietyCode_; }
    const std::string& getName() const        { return name_; }
    int getAgeYears() const                   { return ageYears_; }
    int getHeightCm() const                   { return heightCm_; }
    const Money& getBasePrice() const         { return basePrice_; }

    void setBasePrice(Money price) { basePrice_ = price; }

    // Поліморфний інтерфейс
    virtual std::string category() const = 0;
    virtual Money calculateFinalPrice() const { return basePrice_; }
    virtual std::string details() const;
    virtual void saveRecord(std::ostream& os) const = 0;

private:
    std::string varietyCode_;
    std::string name_;
    int ageYears_ = 0;
    int heightCm_ = 0;
    Money basePrice_{0, 0};
};

std::ostream& operator<<(std::ostream& os, const PlantingMaterial& item);