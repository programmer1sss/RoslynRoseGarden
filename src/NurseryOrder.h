#pragma once

#include <string>
#include <memory>
#include "Nursery.h"

// Клас побудовано через КОМПОЗИЦІЮ (містить об'єкт Nursery як поле),
// оскільки замовлення не є різновидом розсадника (відношення has-a, а не is-a).
class NurseryOrder {
public:
    NurseryOrder(std::string customerName, int discountPercent = 0);

    const std::string& getCustomerName() const { return customerName_; }
    int getDiscountPercent() const             { return discountPercent_; }
    std::size_t itemCount() const              { return selectedPlants_.size(); }

    void addPlant(std::unique_ptr<PlantingMaterial> plant);
    Money calculateSubtotal() const;
    Money calculateTotalWithDiscount() const;

private:
    std::string customerName_;
    int discountPercent_ = 0;
    Nursery selectedPlants_; // Композиція
};