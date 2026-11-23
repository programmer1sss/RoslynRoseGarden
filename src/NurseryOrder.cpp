#include "NurseryOrder.h"
#include <stdexcept>

NurseryOrder::NurseryOrder(std::string customerName, int discountPercent)
    : customerName_(std::move(customerName)),
      discountPercent_(discountPercent)
{
    if (customerName_.empty()) {
        throw std::invalid_argument("NurseryOrder: empty customer name");
    }
    if (discountPercent_ < 0 || discountPercent_ > 50) {
        throw std::invalid_argument("NurseryOrder: discount must be between 0 and 50%");
    }
}

void NurseryOrder::addPlant(std::unique_ptr<PlantingMaterial> plant) {
    selectedPlants_.add(std::move(plant));
}

Money NurseryOrder::calculateSubtotal() const {
    return selectedPlants_.totalCatalogValue();
}

Money NurseryOrder::calculateTotalWithDiscount() const {
    long long subtotalCents = calculateSubtotal().totalCents();
    long long discountedCents = (subtotalCents * (100 - discountPercent_)) / 100;
    return Money(discountedCents / 100, static_cast<int>(discountedCents % 100));
}