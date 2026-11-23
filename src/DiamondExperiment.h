#pragma once

#include <string>
#include <iostream>

// Базовий клас у ромбі: облікова картка рослини
class PlantRecord {
public:
    explicit PlantRecord(std::string registryId = "REG-000")
        : registryId_(std::move(registryId)) {}

    virtual ~PlantRecord() = default;

    const std::string& getRegistryId() const { return registryId_; }
    void setRegistryId(std::string id) { registryId_ = std::move(id); }

private:
    std::string registryId_;
};

// ── 1. БЕЗ віртуального успадкування (проблема дублювання підоб'єкта) ──
class NonVirtualFruit : public PlantRecord {
public:
    NonVirtualFruit(std::string id, std::string rootstock)
        : PlantRecord(std::move(id)), rootstock_(std::move(rootstock)) {}
    const std::string& getRootstock() const { return rootstock_; }
private:
    std::string rootstock_;
};

class NonVirtualOrnamental : public PlantRecord {
public:
    NonVirtualOrnamental(std::string id, std::string flowerColor)
        : PlantRecord(std::move(id)), flowerColor_(std::move(flowerColor)) {}
    const std::string& getFlowerColor() const { return flowerColor_; }
private:
    std::string flowerColor_;
};

// Декоративно-плодовий гібрид без virtual
class NonVirtualHybrid : public NonVirtualFruit, public NonVirtualOrnamental {
public:
    NonVirtualHybrid(std::string fruitId, std::string ornamentalId,
                     std::string rootstock, std::string flowerColor)
        : NonVirtualFruit(std::move(fruitId), std::move(rootstock)),
          NonVirtualOrnamental(std::move(ornamentalId), std::move(flowerColor)) {}
};

// ── 2. ІЗ віртуальним успадкуванням (єдиний спільний підоб'єкт PlantRecord) ──
class VirtualFruit : virtual public PlantRecord {
public:
    VirtualFruit(std::string id, std::string rootstock)
        : PlantRecord(std::move(id)), rootstock_(std::move(rootstock)) {}
    const std::string& getRootstock() const { return rootstock_; }
private:
    std::string rootstock_;
};

class VirtualOrnamental : virtual public PlantRecord {
public:
    VirtualOrnamental(std::string id, std::string flowerColor)
        : PlantRecord(std::move(id)), flowerColor_(std::move(flowerColor)) {}
    const std::string& getFlowerColor() const { return flowerColor_; }
private:
    std::string flowerColor_;
};

// Похідний клас сам ініціалізує віртуальну базу PlantRecord
class VirtualHybrid : public VirtualFruit, public VirtualOrnamental {
public:
    VirtualHybrid(std::string sharedId, std::string rootstock, std::string flowerColor)
        : PlantRecord(std::move(sharedId)),
          VirtualFruit("IGNORED-1", std::move(rootstock)),
          VirtualOrnamental("IGNORED-2", std::move(flowerColor)) {}
};

void runDiamondExperiment(std::ostream& os);