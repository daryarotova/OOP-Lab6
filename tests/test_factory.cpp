#include <gtest/gtest.h>
#include "../include/factory.h"
#include "../include/dragon.h"
#include "../include/elf.h"
#include "../include/druid.h"
#include <memory>

TEST(FactoryTest, CreateDragon) {
    auto dragon = NpcFactory::createNpc("Dragon", "Smaug", 100, 200);
    
    ASSERT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_EQ(dragon->getX(), 100);
    EXPECT_EQ(dragon->getY(), 200);
}

TEST(FactoryTest, CreateElf) {
    auto elf = NpcFactory::createNpc("Elf", "Legolas", 150, 250);
    
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->getType(), "Elf");
    EXPECT_EQ(elf->getName(), "Legolas");
    EXPECT_EQ(elf->getX(), 150);
    EXPECT_EQ(elf->getY(), 250);
}

TEST(FactoryTest, CreateDruid) {
    auto druid = NpcFactory::createNpc("Druid", "Malfurion", 50, 75);
    
    ASSERT_NE(druid, nullptr);
    EXPECT_EQ(druid->getType(), "Druid");
    EXPECT_EQ(druid->getName(), "Malfurion");
    EXPECT_EQ(druid->getX(), 50);
    EXPECT_EQ(druid->getY(), 75);
}

TEST(FactoryTest, CreateInvalidType) {
    EXPECT_THROW({
        auto npc = NpcFactory::createNpc("Orc", "Grom", 100, 100);
    }, std::invalid_argument);
}

// Тесты загрузки из строки
TEST(FactoryTest, CreateFromStringDragon) {
    std::string line = "Dragon Smaug 100 200";
    auto dragon = NpcFactory::createFromString(line);
    
    ASSERT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_EQ(dragon->getX(), 100);
    EXPECT_EQ(dragon->getY(), 200);
}

TEST(FactoryTest, CreateFromStringElf) {
    std::string line = "Elf Legolas 300 400";
    auto elf = NpcFactory::createFromString(line);
    
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->getType(), "Elf");
    EXPECT_EQ(elf->getName(), "Legolas");
    EXPECT_EQ(elf->getX(), 300);
    EXPECT_EQ(elf->getY(), 400);
}

TEST(FactoryTest, CreateFromStringDruid) {
    std::string line = "Druid Malfurion 50 75";
    auto druid = NpcFactory::createFromString(line);
    
    ASSERT_NE(druid, nullptr);
    EXPECT_EQ(druid->getType(), "Druid");
    EXPECT_EQ(druid->getName(), "Malfurion");
}

TEST(FactoryTest, CreateFromStringInvalidFormat) {
    std::string line = "Dragon Smaug";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::runtime_error);
}

TEST(FactoryTest, CreateFromStringInvalidType) {
    std::string line = "Orc Grommash 100 200";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::invalid_argument);
}

TEST(FactoryTest, CreateFromStringEmptyLine) {
    std::string line = "";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::runtime_error);
}

TEST(FactoryTest, CreateFromStringOutOfBounds) {
    std::string line = "Dragon Smaug 600 700";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::out_of_range);
}