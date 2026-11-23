#include "PlantingMaterial.h"
#include <stdexcept>
#include <sstream>

PlantingMaterial::PlantingMaterial(std::string varietyCode,
                                   std::string name,
                                   int ageYears,
                                   int heightCm,
                                   Money basePrice)
    : varietyCode_(std::move(varietyCode)),
      name_(std::move(name)),
      ageYears_(ageYears),
      heightCm_(heightCm),
      basePrice_(basePrice)
{
    if (varietyCode_.empty()) {
        throw std::invalid_argument("PlantingMaterial: empty variety code");
    }
    if (name_.empty()) {
        throw std::invalid_argument("PlantingMaterial: empty name");
    }
    if (ageYears_ < 0 || heightCm_ < 0) {
        throw std::invalid_argument("PlantingMaterial: negative age or height");
    }
    if (basePrice_.totalCents() < 0) {
        throw std::invalid_argument("PlantingMaterial: negative price");
    }
}

std::string PlantingMaterial::details() const {
    std::ostringstream oss;
    oss << "[" << category() << "] " << varietyCode_ << " \"" << name_ << "\", "
        << ageYears_ << " р., " << heightCm_ << " см, ціна: " << calculateFinalPrice() << " грн";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const PlantingMaterial& item) {
    os << item.details();
    return os;
}