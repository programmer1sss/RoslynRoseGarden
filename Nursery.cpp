#include "Nursery.h"

void Nursery::save(std::ostream& os) const {
    for (const auto& s : items_)
        os << s << '\n';
}

void Nursery::load(std::istream& is) {
    items_.clear();
    Seedling temp;
    while (is >> temp) {
        items_.push_back(temp);
    }
}
