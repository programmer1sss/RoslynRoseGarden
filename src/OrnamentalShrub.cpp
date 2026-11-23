#include "OrnamentalShrub.h"
#include <iomanip>
#include <stdexcept>
#include <sstream>

OrnamentalShrub::OrnamentalShrub(std::string varietyCode,
                                 std::string name,
                                 int ageYears,
                                 int heightCm,
                                 Money basePrice,
                                 std::string bloomingPeriod,
                                 std::string flowerColor)
    : PlantingMaterial(std::move(varietyCode), std::move(name), ageYears, heightCm, basePrice),
      bloomingPeriod_(std::move(bloomingPeriod)),
      flowerColor_(std::move(flowerColor))
{
    if (bloomingPeriod_.empty()) {
        throw std::invalid_argument("OrnamentalShrub: empty blooming period");
    }
    if (flowerColor_.empty()) {
        throw std::invalid_argument("OrnamentalShrub: empty flower color");
    }
}

bool OrnamentalShrub::isSummerBlooming() const {
    return bloomingPeriod_.find("черв") != std::string::npos ||
           bloomingPeriod_.find("лип")  != std::string::npos ||
           bloomingPeriod_.find("серп") != std::string::npos;
}

Money OrnamentalShrub::calculateFinalPrice() const {
    Money price = getBasePrice();
    if (getHeightCm() > 100) {
        // Надбавка 20.00 грн за сформований високий кущ
        price += Money(20, 0);
    }
    return price;
}

std::string OrnamentalShrub::details() const {
    std::ostringstream oss;
    oss << PlantingMaterial::details()
        << " | цвітіння: " << bloomingPeriod_
        << ", колір: " << flowerColor_
        << (isSummerBlooming() ? " [літнє]" : "");
    return oss.str();
}

void OrnamentalShrub::saveRecord(std::ostream& os) const {
    os << "SHRUB "
       << getVarietyCode() << ' '
       << std::quoted(getName()) << ' '
       << getAgeYears() << ' '
       << getHeightCm() << ' '
       << getBasePrice() << ' '
       << std::quoted(bloomingPeriod_) << ' '
       << std::quoted(flowerColor_);
}