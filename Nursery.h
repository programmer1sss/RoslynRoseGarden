#pragma once

#include <vector>
#include <iostream>
#include "Seedling.h"

// Розсадник — колекція саджанців з методами save/load.
class Nursery {
public:
    Nursery() = default;

    void add(Seedling s) { items_.push_back(std::move(s)); }

    std::size_t size() const { return items_.size(); }
    Seedling&       at(std::size_t i)       { return items_.at(i); }
    const Seedling& at(std::size_t i) const { return items_.at(i); }

    const std::vector<Seedling>& items() const { return items_; }

    void save(std::ostream& os) const;
    void load(std::istream& is);

private:
    std::vector<Seedling> items_;
};