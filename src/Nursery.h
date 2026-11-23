#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "PlantingMaterial.h"

class Nursery {
public:
    Nursery() = default;

    // Заборона копіювання (оскільки зберігаються unique_ptr), дозвіл переміщення
    Nursery(const Nursery&) = delete;
    Nursery& operator=(const Nursery&) = delete;
    Nursery(Nursery&&) noexcept = default;
    Nursery& operator=(Nursery&&) noexcept = default;

    void add(std::unique_ptr<PlantingMaterial> item);

    std::size_t size() const { return items_.size(); }
    bool empty() const { return items_.empty(); }

    const PlantingMaterial& at(std::size_t i) const { return *items_.at(i); }
    PlantingMaterial& at(std::size_t i)             { return *items_.at(i); }

    Money totalCatalogValue() const;
    std::size_t countByCategory(const std::string& categoryName) const;

    void save(std::ostream& os) const;
    void load(std::istream& is);

private:
    std::vector<std::unique_ptr<PlantingMaterial>> items_;
};