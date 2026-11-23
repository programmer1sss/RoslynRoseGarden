#include <iostream>
#include <fstream>
#include <memory>
#include "FruitSeedling.h"
#include "OrnamentalShrub.h"
#include "Nursery.h"
#include "NurseryOrder.h"
#include "DiamondExperiment.h"

int main() {
    Nursery nursery;
    nursery.add(std::make_unique<FruitSeedling>(
        "APPLE-M9", "Яблуня Голден Делішес", 2, 145, Money(140, 0), "М9", true));
    nursery.add(std::make_unique<FruitSeedling>(
        "PEAR-SEED", "Груша Конференція", 3, 190, Money(160, 0), "Сіянець груші", false));
    nursery.add(std::make_unique<OrnamentalShrub>(
        "HYDR-01", "Гортензія волотиста", 2, 115, Money(210, 0), "липень–вересень", "біло-рожевий"));
    nursery.add(std::make_unique<OrnamentalShrub>(
        "FORS-02", "Форзиція проміжна", 1, 80, Money(95, 50), "квітень–травень", "яскраво-жовтий"));

    std::cout << "=== Каталог розсадника (" << nursery.size() << " позицій) ===\n";
    for (std::size_t i = 0; i < nursery.size(); ++i) {
        std::cout << "  " << nursery.at(i) << '\n';
    }
    std::cout << "Загальна вартість каталогу: " << nursery.totalCatalogValue() << " грн\n";

    // Збереження та поліморфне завантаження
    {
        std::ofstream out("nursery_poly.txt");
        nursery.save(out);
    }
    Nursery restored;
    {
        std::ifstream in("nursery_poly.txt");
        restored.load(in);
    }
    std::cout << "Відновлено з файлу: " << restored.size()
              << " позицій, сума: " << restored.totalCatalogValue() << " грн\n";

    // Демонстрація композиції (NurseryOrder)
    NurseryOrder order("Олена Коваленко", 10); // знижка 10%
    order.addPlant(std::make_unique<FruitSeedling>(
        "APPLE-M9", "Яблуня Голден Делішес", 2, 145, Money(140, 0), "М9", true));
    order.addPlant(std::make_unique<OrnamentalShrub>(
        "HYDR-01", "Гортензія волотиста", 2, 115, Money(210, 0), "липень–вересень", "біло-рожевий"));

    std::cout << "\n=== Замовлення клієнта: " << order.getCustomerName() << " ===\n"
              << "Сума без знижки: " << order.calculateSubtotal() << " грн\n"
              << "До сплати (-" << order.getDiscountPercent() << "%): "
              << order.calculateTotalWithDiscount() << " грн\n";

    // Експеримент із ромбом
    runDiamondExperiment(std::cout);

    return 0;
}