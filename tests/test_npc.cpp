#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/dragon.h"
#include "../include/elf.h"
#include "../include/druid.h"
#include <memory>

// Тесты создания NPC
TEST(NpcTest, CreateDragon) {
    Dragon dragon(100, 200, "Smaug");
    
    EXPECT_EQ(dragon.getX(), 100);
    EXPECT_EQ(dragon.getY(), 200);
    EXPECT_EQ(dragon.getName(), "Smaug");
    EXPECT_EQ(dragon.getType(), "Dragon");
}

TEST(NpcTest, CreateElf) {
    Elf elf(150, 250, "Legolas");
    
    EXPECT_EQ(elf.getX(), 150);
    EXPECT_EQ(elf.getY(), 250);
    EXPECT_EQ(elf.getName(), "Legolas");
    EXPECT_EQ(elf.getType(), "Elf");
}

TEST(NpcTest, CreateDruid) {
    Druid druid(50, 75, "Malfurion");
    
    EXPECT_EQ(druid.getX(), 50);
    EXPECT_EQ(druid.getY(), 75);
    EXPECT_EQ(druid.getName(), "Malfurion");
    EXPECT_EQ(druid.getType(), "Druid");
}

// Тест расстояния между NPC
TEST(NpcTest, DistanceCalculation) {
    Dragon dragon1(0, 0, "Dragon1");
    Elf elf1(3, 4, "Elf1");
    
    // Расстояние должно быть 5
    EXPECT_DOUBLE_EQ(dragon1.distanceTo(elf1), 5.0);
}

TEST(NpcTest, DistanceSamePosition) {
    Druid druid1(100, 100, "Druid1");
    Druid druid2(100, 100, "Druid2");
    
    EXPECT_DOUBLE_EQ(druid1.distanceTo(druid2), 0.0);
}

TEST(NpcTest, DistanceSymmetric) {
    Elf elf(10, 20, "Elf1");
    Dragon dragon(50, 80, "Dragon1");
    
    // Расстояние должно быть одинаковым в обе стороны
    EXPECT_DOUBLE_EQ(elf.distanceTo(dragon), dragon.distanceTo(elf));
}

// Тест координат на границах
TEST(NpcTest, BoundaryCoordinates) {
    Dragon dragon1(0, 0, "MinCorner");
    EXPECT_EQ(dragon1.getX(), 0);
    EXPECT_EQ(dragon1.getY(), 0);
    
    Druid druid1(500, 500, "MaxCorner");
    EXPECT_EQ(druid1.getX(), 500);
    EXPECT_EQ(druid1.getY(), 500);
}

TEST(NpcTest, PrintInfo) {
    Dragon dragon(100, 200, "TestDragon");
    Elf elf(150, 250, "TestElf");
    Druid druid(50, 75, "TestDruid");
    
    EXPECT_NO_THROW(dragon.printInfo());
    EXPECT_NO_THROW(elf.printInfo());
    EXPECT_NO_THROW(druid.printInfo());
}