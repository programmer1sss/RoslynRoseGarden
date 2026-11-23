#include "FruitSeedling.h"
#include <iomanip>
#include <stdexcept>
#include <sstream>

FruitSeedling::FruitSeedling(std::string varietyCode,
                             std::string name,
                             int ageYears,
                             int heightCm,
                             Money basePrice,
                             std::string rootstock,
                             bool isDwarf)
    : PlantingMaterial(std::move(varietyCode), std::move(name), ageYears, heightCm, basePrice),
      rootstock_(std::move(rootstock)),
      isDwarf_(isDwarf)
{
    if (rootstock_.empty()) {
        throw std::invalid_argument("FruitSeedling: empty rootstock");
    }
}

double FruitSeedling::expectedYieldKg() const {
    // Карликові підщепи раніше входять у плодоношення, але мають менший об'єм крони
    double baseYield = isDwarf_ ? 12.0 : 20.0;
    double ageFactor = (getAgeYears() >= 3) ? 1.0 : (getAgeYears() == 2 ? 0.6 : 0.25);
    return baseYield * ageFactor;
}

Money FruitSeedling::calculateFinalPrice() const {
    long long cents = getBasePrice().totalCents();
    if (isDwarf_) {
        // +15% до вартості за карликову підщепу
        cents = (cents * 115) / 100;
    }
    return Money(cents / 100, static_cast<int>(cents % 100));
}

std::string FruitSeedling::details() const {
    std::ostringstream oss;
    oss << PlantingMaterial::details()
        << " | підщепа: " << rootstock_
        << (isDwarf_ ? " (карликова)" : " (сильноросла)")
        << ", прогноз врожаю: " << expectedYieldKg() << " кг";
    return oss.str();
}

void FruitSeedling::saveRecord(std::ostream& os) const {
    os << "FRUIT "
       << getVarietyCode() << ' '
       << std::quoted(getName()) << ' '
       << getAgeYears() << ' '
       << getHeightCm() << ' '
       << getBasePrice() << ' '
       << std::quoted(rootstock_) << ' '
       << (isDwarf_ ? 1 : 0);
}