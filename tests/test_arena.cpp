#include <gtest/gtest.h>
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include "../include/file_observer.h"
#include <memory>
#include <fstream>
#include <sstream>

TEST(ArenaTest, CreateArena) {
    Arena arena(500, 500);
    EXPECT_EQ(arena.getNpcCount(), 0);
}

TEST(ArenaTest, CreateArenaInvalidSize) {
    EXPECT_THROW({
        Arena arena(600, 600);  // Больше максимума
    }, std::out_of_range);
}

TEST(ArenaTest, AddNpc) {
    Arena arena;
    auto dragon = NpcFactory::createNpc("Dragon", "Smaug", 100, 100);
    arena.addNpc(std::move(dragon));
    
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(ArenaTest, AddMultipleNpcs) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 200, 200));
    arena.addNpc(NpcFactory::createNpc("Druid", "Malfurion", 300, 300));
    
    EXPECT_EQ(arena.getNpcCount(), 3);
}

TEST(ArenaTest, AddNpcDuplicateName) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Duplicate", 100, 100));
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Elf", "Duplicate", 200, 200));
    }, std::invalid_argument);
}

TEST(ArenaTest, AddNpcOutOfBounds) {
    Arena arena(500, 500);
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Dragon", "OutDragon", 600, 100));
    }, std::out_of_range);
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Elf", "OutElf", 100, 600));
    }, std::out_of_range);
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Druid", "NegativeDruid", -10, 100));
    }, std::out_of_range);
}

TEST(ArenaTest, CreateAndAddNpc) {
    Arena arena;
    
    EXPECT_NO_THROW({
        arena.createAndAddNpc("Dragon", "Smaug", 100, 100);
        arena.createAndAddNpc("Elf", "Legolas", 200, 200);
        arena.createAndAddNpc("Druid", "Malfurion", 300, 300);
    });
    
    EXPECT_EQ(arena.getNpcCount(), 3);
}

TEST(ArenaTest, ClearArena) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 200, 200));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    arena.clear();
    EXPECT_EQ(arena.getNpcCount(), 0);
}

TEST(ArenaTest, SaveToFile) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 200));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 150, 250));
    arena.addNpc(NpcFactory::createNpc("Druid", "Malfurion", 50, 75));
    
    std::string filename = "test_save.txt";
    arena.saveToFile(filename);
    
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }
    file.close();
    
    EXPECT_EQ(lineCount, 3);
    
    std::remove(filename.c_str());
}

TEST(ArenaTest, LoadFromFile) {
    std::string filename = "test_load.txt";
    std::ofstream outfile(filename);
    outfile << "Dragon Smaug 100 200\n";
    outfile << "Elf Legolas 150 250\n";
    outfile << "Druid Malfurion 50 75\n";
    outfile.close();
    
    Arena arena;
    arena.loadFromFile(filename);
    
    EXPECT_EQ(arena.getNpcCount(), 3);
    
    std::remove(filename.c_str());
}

TEST(ArenaTest, LoadFromNonExistentFile) {
    Arena arena;
    
    EXPECT_THROW({
        arena.loadFromFile("nonexistent_file.txt");
    }, std::runtime_error);
}

TEST(ArenaTest, SaveAndLoadRoundtrip) {
    std::string filename = "test_roundtrip.txt";
    
    {
        Arena arena1;
        arena1.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 111, 222));
        arena1.addNpc(NpcFactory::createNpc("Elf", "Legolas", 333, 444));
        arena1.saveToFile(filename);
    }
    
    {
        Arena arena2;
        arena2.loadFromFile(filename);
        EXPECT_EQ(arena2.getNpcCount(), 2);
    }
    
    std::remove(filename.c_str());
}

TEST(ArenaTest, AddObserver) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    
    EXPECT_NO_THROW({
        arena.addObserver(observer);
    });
}

TEST(ArenaTest, AddFileObserver) {
    Arena arena;
    auto observer = std::make_shared<FileObserver>("test_observer.txt");
    
    EXPECT_NO_THROW({
        arena.addObserver(observer);
    });
    
    std::remove("test_observer.txt");
}

TEST(ArenaTest, PrintAllNpcs) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Elf", "Legolas", 200, 200));
    
    EXPECT_NO_THROW({
        arena.printAllNpcs();
    });
}

TEST(ArenaTest, BattleNegativeRange) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 100, 100));
    
    EXPECT_THROW({
        arena.startBattle(-10.0);
    }, std::invalid_argument);
}
