#include <gtest/gtest.h>
#include "../include/combat_visitor.h"
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include "../include/file_observer.h"
#include <memory>
#include <fstream>

TEST(CombatTest, DragonVsDragon) {
    CombatVisitor visitor;
    auto dragon1 = NpcFactory::createNpc("Dragon", "Smaug", 0, 0);
    auto dragon2 = NpcFactory::createNpc("Dragon", "Drogon", 10, 10);
    
    EXPECT_FALSE(visitor.canKill(dragon1.get(), dragon2.get()));
    EXPECT_FALSE(visitor.canKill(dragon2.get(), dragon1.get()));
}

TEST(CombatTest, DragonVsElf) {
    CombatVisitor visitor;
    auto dragon = NpcFactory::createNpc("Dragon", "Smaug", 0, 0);
    auto elf = NpcFactory::createNpc("Elf", "Legolas", 10, 10);
    
    EXPECT_TRUE(visitor.canKill(dragon.get(), elf.get()));
    EXPECT_FALSE(visitor.canKill(elf.get(), dragon.get()));
}

TEST(CombatTest, DragonVsDruid) {
    CombatVisitor visitor;
    auto dragon = NpcFactory::createNpc("Dragon", "Smaug", 0, 0);
    auto druid = NpcFactory::createNpc("Druid", "Malfurion", 10, 10);
    
    EXPECT_FALSE(visitor.canKill(dragon.get(), druid.get()));
    EXPECT_TRUE(visitor.canKill(druid.get(), dragon.get()));
}

TEST(CombatTest, ElfVsElf) {
    CombatVisitor visitor;
    auto elf1 = NpcFactory::createNpc("Elf", "Legolas", 0, 0);
    auto elf2 = NpcFactory::createNpc("Elf", "Arwen", 10, 10);
    
    EXPECT_FALSE(visitor.canKill(elf1.get(), elf2.get()));
    EXPECT_FALSE(visitor.canKill(elf2.get(), elf1.get()));
}

TEST(CombatTest, ElfVsDruid) {
    CombatVisitor visitor;
    auto elf = NpcFactory::createNpc("Elf", "Legolas", 0, 0);
    auto druid = NpcFactory::createNpc("Druid", "Malfurion", 10, 10);
    
    EXPECT_TRUE(visitor.canKill(elf.get(), druid.get()));
    EXPECT_FALSE(visitor.canKill(druid.get(), elf.get()));
}

TEST(CombatTest, DruidVsDruid) {
    CombatVisitor visitor;
    auto druid1 = NpcFactory::createNpc("Druid", "Malfurion", 0, 0);
    auto druid2 = NpcFactory::createNpc("Druid", "Cenarius", 10, 10);
    
    EXPECT_FALSE(visitor.canKill(druid1.get(), druid2.get()));
    EXPECT_FALSE(visitor.canKill(druid2.get(), druid1.get()));
}

TEST(CombatTest, DruidVsDragon) {
    CombatVisitor visitor;
    auto druid = NpcFactory::createNpc("Druid", "Malfurion", 0, 0);
    auto dragon = NpcFactory::createNpc("Dragon", "Smaug", 10, 10);
    
    EXPECT_TRUE(visitor.canKill(druid.get(), dragon.get()));
    EXPECT_FALSE(visitor.canKill(dragon.get(), druid.get()));
}

TEST(CombatTest, BattleOutOfRange) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 0, 0));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 400, 400));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    arena.startBattle(100.0);
    
    EXPECT_EQ(arena.getNpcCount(), 2);
}

TEST(CombatTest, DragonKillsElf) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 110, 110));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 50 метров
    arena.startBattle(50.0);
    
    // Дракон убивает эльфа
    EXPECT_EQ(arena.getNpcCount(), 1);
    
    if (arena.getNpcCount() == 1) {
    }
}

TEST(CombatTest, ElfKillsDruid) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Druid", "Malfurion", 105, 105));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    arena.startBattle(50.0);
    
    // Эльф убивает друида
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(CombatTest, DruidKillsDragon) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Друид и дракон близко
    arena.addNpc(NpcFactory::createNpc("Druid", "Malfurion", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 105, 105));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    arena.startBattle(50.0);
    
    // Друид убивает дракона
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(CombatTest, NoMutualKillPossible) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Дракон и эльф - только дракон убивает эльфа
    arena.addNpc(NpcFactory::createNpc("Dragon", "Dragon1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Elf1", 105, 105));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    arena.startBattle(50.0);
    
    // Должен остаться только дракон
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(CombatTest, ComplexBattleScenario) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Создаём группу NPC разных типов
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 105, 105));
    arena.addNpc(NpcFactory::createNpc("Druid", "Malfurion", 110, 110));
    arena.addNpc(NpcFactory::createNpc("Elf", "Arwen", 115, 115));
    arena.addNpc(NpcFactory::createNpc("Dragon", "Drogon", 120, 120));
    
    EXPECT_EQ(arena.getNpcCount(), 5);
    
    arena.startBattle(100.0);
    EXPECT_LT(arena.getNpcCount(), 5);
}

TEST(CombatTest, DragonsSurviveAlone) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Только драконы
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Dragon", "Drogon", 110, 110));
    arena.addNpc(NpcFactory::createNpc("Dragon", "Toothless", 120, 120));
    
    EXPECT_EQ(arena.getNpcCount(), 3);
    
    arena.startBattle(100.0);
    
    // Драконы не атакуют друг друга - все выживают
    EXPECT_EQ(arena.getNpcCount(), 3);
}

TEST(CombatTest, FileObserverLogging) {
    std::string logfile = "test_combat_log.txt";
    
    Arena arena;
    auto observer = std::make_shared<FileObserver>(logfile);
    arena.addObserver(observer);
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 110, 110));
    
    arena.startBattle(50.0);
    
    // Проверяем что файл создан
    std::ifstream file(logfile);
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    bool hasContent = false;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            hasContent = true;
            break;
        }
    }
    file.close();
    
    EXPECT_TRUE(hasContent);
    
    // Удаляем тестовый файл
    std::remove(logfile.c_str());
}