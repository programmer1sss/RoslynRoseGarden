#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Seedling.h"
#include "Nursery.h"
#include "Money.h"

void printSeparator(const std::string& title) {
    std::cout << "\n==========================================\n";
    std::cout << " " << title << "\n";
    std::cout << "==========================================\n";
}

int main() {
    printSeparator("ІНДИВІДУАЛЬНЕ ЗАВДАННЯ: Розсадник рослин");

    // 1. Створюємо розсадник
    Nursery nursery;
    nursery.add(Seedling("APPLE-1", "Антонівка", 2, 150, Money(125, 00)));
    nursery.add(Seedling("PEAR-2",  "Лісова",   1, 120, Money(95,  50)));
    nursery.add(Seedling("PLUM-3",  "Угорка",   3, 180, Money(140, 00)));
    nursery.add(Seedling("APPLE-1", "Антонівка", 2, 150, Money(125, 00))); // дублікат

    std::cout << "Розсадник (" << nursery.size() << " саджанців):\n";
    for (std::size_t i = 0; i < nursery.size(); ++i)
        std::cout << "  " << nursery.at(i) << '\n';

    // 2. Сортування
    std::vector<Seedling> sorted(nursery.items().begin(), nursery.items().end());
    std::sort(sorted.begin(), sorted.end());

    printSeparator("Після сортування (назва → вік → висота)");
    for (const auto& s : sorted)
        std::cout << "  " << s << '\n';

    // 3. Запис у файл
    {
        std::ofstream out("nursery.txt");
        if (!out) { std::cerr << "Помилка запису!\n"; return 1; }
        nursery.save(out);
    }
    std::cout << "\nКаталог збережено в nursery.txt\n";

    // 4. Читання з файлу
    Nursery restored;
    {
        std::ifstream in("nursery.txt");
        if (!in) { std::cerr << "Помилка читання!\n"; return 1; }
        restored.load(in);
    }
    std::cout << "Каталог відновлено: " << restored.size() << " саджанців\n";

    // 5. Перевірка безвтратності
    bool ok = (nursery.size() == restored.size())
           && std::equal(nursery.items().begin(), nursery.items().end(),
                         restored.items().begin());
    std::cout << "\nБезвтратний цикл: " << (ok ? "ТАК" : "НІ") << '\n';

    // 6. Демонстрація операторів Money
    printSeparator("Оператори Money");
    Money total(0, 0);
    for (const auto& s : nursery.items())
        total += s.getPrice();

    std::cout << "Сумарна вартість усіх саджанців: " << total << '\n';
    std::cout << "Середня ціна: " << (total * (1.0 / nursery.size())) << '\n';

    return 0;
}