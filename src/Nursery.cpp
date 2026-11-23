#include "Nursery.h"
#include "FruitSeedling.h"
#include "OrnamentalShrub.h"
#include <iomanip>
#include <stdexcept>

void Nursery::add(std::unique_ptr<PlantingMaterial> item) {
    if (!item) {
        throw std::invalid_argument("Nursery::add: null pointer");
    }
    items_.push_back(std::move(item));
}

Money Nursery::totalCatalogValue() const {
    Money total(0, 0);
    for (const auto& item : items_) {
        total += item->calculateFinalPrice();
    }
    return total;
}

std::size_t Nursery::countByCategory(const std::string& categoryName) const {
    std::size_t count = 0;
    for (const auto& item : items_) {
        if (item->category() == categoryName) {
            ++count;
        }
    }
    return count;
}

void Nursery::save(std::ostream& os) const {
    for (const auto& item : items_) {
        item->saveRecord(os);
        os << '\n';
    }
}

void Nursery::load(std::istream& is) {
    items_.clear();
    std::string type;

    while (is >> type) {
        std::string code, name;
        int age = 0, height = 0;
        Money basePrice;

        if (!(is >> code >> std::quoted(name) >> age >> height >> basePrice)) {
            is.setstate(std::ios::failbit);
            return;
        }

        if (type == "FRUIT") {
            std::string rootstock;
            int dwarfFlag = 0;
            if (!(is >> std::quoted(rootstock) >> dwarfFlag)) {
                is.setstate(std::ios::failbit);
                return;
            }
            items_.push_back(std::make_unique<FruitSeedling>(
                code, name, age, height, basePrice, rootstock, dwarfFlag != 0));
        } else if (type == "SHRUB") {
            std::string period, color;
            if (!(is >> std::quoted(period) >> std::quoted(color))) {
                is.setstate(std::ios::failbit);
                return;
            }
            items_.push_back(std::make_unique<OrnamentalShrub>(
                code, name, age, height, basePrice, period, color));
        } else {
            is.setstate(std::ios::failbit);
            return;
        }
    }
}