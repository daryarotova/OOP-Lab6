#include "include/arena.h"
#include "include/factory.h"
#include "include/console_observer.h"
#include "include/file_observer.h"
#include <iostream>
#include <memory>

int main() {
    try {
        std::cout << "========================================" << std::endl;
        std::cout << "  Balagur Fate 3 - Dungeon Editor" << std::endl;
        std::cout << "  Variant: Dragon, Elf, Druid" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::endl;

        Arena arena(500, 500);

        auto consoleObserver = std::make_shared<ConsoleObserver>();
        auto fileObserver = std::make_shared<FileObserver>("log.txt");
        
        arena.addObserver(consoleObserver);
        arena.addObserver(fileObserver);

        std::cout << "=== 1. Creating NPCs... ===" << std::endl;
        
        arena.createAndAddNpc("Dragon", "Smaug", 100, 100);
        arena.createAndAddNpc("Dragon", "Drogon", 200, 200);
        
        arena.createAndAddNpc("Elf", "Legolas", 120, 120);
        arena.createAndAddNpc("Elf", "Arwen", 180, 180);
        arena.createAndAddNpc("Elf", "Thranduil", 250, 250);
        
        arena.createAndAddNpc("Druid", "Malfurion", 110, 110);
        arena.createAndAddNpc("Druid", "Cenarius", 220, 220);
        
        std::cout << "Created NPCs: " << arena.getNpcCount() << std::endl;
        std::cout << std::endl;

        std::cout << "=== 2. List of all NPCs on arena: ===" << std::endl;
        arena.printAllNpcs();
        std::cout << std::endl;

        std::cout << "=== 3. Saving NPCs to file 'dungeon_npcs.txt'... ===" << std::endl;
        arena.saveToFile("dungeon_npcs.txt");
        std::cout << "Saved successfully!" << std::endl;
        std::cout << std::endl;

        std::cout << "=== 4. Battle mode test (small range - no fights) ===" << std::endl;
        std::cout << "Starting battle with range: 10 meters" << std::endl;
        std::cout << "--- BATTLE START ---" << std::endl;
        arena.startBattle(10.0);
        std::cout << "--- BATTLE END ---" << std::endl;
        std::cout << "NPCs after small range battle: " << arena.getNpcCount() << std::endl;
        std::cout << std::endl;

        std::cout << "=== 5. Battle mode (real range - fights expected) ===" << std::endl;
        std::cout << "Starting battle with range: 150 meters" << std::endl;
        std::cout << "--- BATTLE START ---" << std::endl;
        arena.startBattle(150.0);
        std::cout << "--- BATTLE END ---" << std::endl;
        std::cout << std::endl;

        std::cout << "=== 6. Survivors list: ===" << std::endl;
        arena.printAllNpcs();
        std::cout << "Survivors: " << arena.getNpcCount() << std::endl;
        std::cout << std::endl;

        std::cout << "=== 7. Clearing arena and loading from file... ===" << std::endl;
        arena.clear();
        arena.loadFromFile("dungeon_npcs.txt");
        std::cout << "Loaded NPCs: " << arena.getNpcCount() << std::endl;
        
        std::cout << "=== 8. Testing different battle scenarios ===" << std::endl;
        
        // Сценарий 1: Дракон против Эльфа (Дракон должен победить)
        std::cout << "\nScenario 1: Dragon vs Elf" << std::endl;
        arena.clear();
        arena.createAndAddNpc("Dragon", "FireDrake", 100, 100);
        arena.createAndAddNpc("Elf", "ForestElf", 105, 105);
        arena.startBattle(50.0);
        
        // Сценарий 2: Эльф против Друида (Эльф должен победить)
        std::cout << "\nScenario 2: Elf vs Druid" << std::endl;
        arena.clear();
        arena.createAndAddNpc("Elf", "SharpShooter", 200, 200);
        arena.createAndAddNpc("Druid", "TreeKeeper", 205, 205);
        arena.startBattle(50.0);
        
        // Сценарий 3: Друид против Дракона (Друид должен победить)
        std::cout << "\nScenario 3: Druid vs Dragon" << std::endl;
        arena.clear();
        arena.createAndAddNpc("Druid", "NatureWalker", 300, 300);
        arena.createAndAddNpc("Dragon", "ScaleBeast", 305, 305);
        arena.startBattle(50.0);
        
        // Сценарий 4: NPC одного типа (не должны сражаться)
        std::cout << "\nScenario 4: Same type NPCs (no fight expected)" << std::endl;
        arena.clear();
        arena.createAndAddNpc("Dragon", "Dragon1", 100, 100);
        arena.createAndAddNpc("Dragon", "Dragon2", 110, 110);
        arena.startBattle(50.0);
        std::cout << "Dragons should still be alive: " << arena.getNpcCount() << std::endl;

        std::cout << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "  Program completed successfully!" << std::endl;
        std::cout << "  Check 'log.txt' for battle events" << std::endl;
        std::cout << "========================================" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}