#include "DiamondExperiment.h"

void runDiamondExperiment(std::ostream& os) {
    os << "\n=== Експеримент: Ромбоподібне успадкування ===\n";

    // 1. Без virtual: у пам'яті існують ДВА незалежних підоб'єкти PlantRecord
    NonVirtualHybrid nvHybrid("ID-FRUIT-01", "ID-ORN-02", "М9", "рожевий");
    // nvHybrid.getRegistryId(); // ПОМИЛКА КОМПІЛЯЦІЇ: неоднозначність (ambiguous access)
    os << "Без virtual:\n"
       << "  Розмір об'єкта: " << sizeof(nvHybrid) << " байт\n"
       << "  ID через гілку Fruit:      " << nvHybrid.NonVirtualFruit::getRegistryId() << '\n'
       << "  ID через гілку Ornamental: " << nvHybrid.NonVirtualOrnamental::getRegistryId() << '\n'
       << "  Адреса бази Fruit:         " << static_cast<const PlantRecord*>(static_cast<const NonVirtualFruit*>(&nvHybrid)) << '\n'
       << "  Адреса бази Ornamental:    " << static_cast<const PlantRecord*>(static_cast<const NonVirtualOrnamental*>(&nvHybrid)) << '\n';

    // 2. Із virtual: у пам'яті існує ОДИН спільний підоб'єкт PlantRecord
    VirtualHybrid vHybrid("ID-SHARED-99", "М9", "рожевий");
    os << "Із virtual:\n"
       << "  Розмір об'єкта: " << sizeof(vHybrid) << " байт\n"
       << "  Прямий виклик getRegistryId(): " << vHybrid.getRegistryId() << '\n'
       << "  Адреса бази Fruit:         " << static_cast<const PlantRecord*>(static_cast<const VirtualFruit*>(&vHybrid)) << '\n'
       << "  Адреса бази Ornamental:    " << static_cast<const PlantRecord*>(static_cast<const VirtualOrnamental*>(&vHybrid)) << '\n';

    vHybrid.setRegistryId("ID-UPDATED-100");
    os << "  Після зміни через одну гілку:  " << vHybrid.VirtualOrnamental::getRegistryId() << '\n';
}