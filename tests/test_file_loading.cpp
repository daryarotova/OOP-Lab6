#include <gtest/gtest.h>
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include <memory>
#include <fstream>

void createTestDataFile(const std::string& filename) {
    std::ofstream outfile(filename);
    outfile << "Dragon Smaug 100 200\n";
    outfile << "Elf Legolas 150 250\n";
    outfile << "Druid Malfurion 50 75\n";
    outfile << "Dragon Drogon 200 300\n";
    outfile << "Elf Arwen 400 450\n";
    outfile.close();
}

TEST(FileLoadingTest, LoadRealFileAndVerify) {
    std::string filename = "test_data_npcs.txt";
    createTestDataFile(filename);
    
    Arena arena;
    
    ASSERT_NO_THROW({
        arena.loadFromFile(filename);
    });
    
    EXPECT_EQ(arena.getNpcCount(), 5);
    
    std::remove(filename.c_str());
}

TEST(FileLoadingTest, LoadAndPrintNpcs) {
    std::string filename = "test_data_npcs.txt";
    createTestDataFile(filename);
    
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    std::cout << "\n=== Загрузка NPC из файла test_data_npcs.txt ===" << std::endl;
    
    arena.loadFromFile(filename);
    
    std::cout << "Загружено NPC: " << arena.getNpcCount() << std::endl;
    std::cout << "\nСписок загруженных NPC:" << std::endl;
    arena.printAllNpcs();
    
    EXPECT_EQ(arena.getNpcCount(), 5);
    
    std::remove(filename.c_str());
}

TEST(FileLoadingTest, LoadAndTestBattle) {
    std::string filename = "test_data_npcs.txt";
    createTestDataFile(filename);
    
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    arena.loadFromFile(filename);
    EXPECT_EQ(arena.getNpcCount(), 5);
    
    std::cout << "\n=== Тест боя с загруженными NPC ===" << std::endl;
    std::cout << "Начальное количество NPC: " << arena.getNpcCount() << std::endl;
    
    std::cout << "\nЗапуск боя с дальностью 200 метров..." << std::endl;
    arena.startBattle(200.0);
    
    std::cout << "Количество выживших: " << arena.getNpcCount() << std::endl;
    std::cout << "\nВыжившие:" << std::endl;
    arena.printAllNpcs();
    
    EXPECT_LT(arena.getNpcCount(), 5);
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

TEST(FileLoadingTest, LoadSaveAndReload) {
    std::string sourceFile = "source_test_file.txt";
    std::string tempFile = "temp_test_file.txt";
    
    // Создаём исходный файл
    createTestDataFile(sourceFile);
    
    // Первая арена - загружаем и сохраняем
    {
        Arena arena1;
        arena1.loadFromFile(sourceFile);
        size_t originalCount = arena1.getNpcCount();
        
        EXPECT_EQ(originalCount, 5);
        
        // Сохраняем в другой файл
        arena1.saveToFile(tempFile);
    }
    
    // Вторая арена - загружаем из сохранённого файла
    {
        Arena arena2;
        arena2.loadFromFile(tempFile);
        
        EXPECT_EQ(arena2.getNpcCount(), 5);
        
        std::cout << "\n=== Проверка сохранения/загрузки ===" << std::endl;
        std::cout << "Данные успешно сохранены и загружены обратно!" << std::endl;
        arena2.printAllNpcs();
    }
    
    // Удаляем временные файлы
    std::remove(sourceFile.c_str());
    std::remove(tempFile.c_str());
}

TEST(FileLoadingTest, VerifySpecificNpcData) {
    std::string filename = "test_data_npcs.txt";
    createTestDataFile(filename);
    
    Arena arena;
    arena.loadFromFile(filename);
    
    // Проверяем что все 5 NPC загрузились
    EXPECT_EQ(arena.getNpcCount(), 5);
    
    // Создаём арену с дубликатом имени - должна выбросить исключение
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Dragon", "Smaug", 500, 500));
    }, std::invalid_argument);
    
    std::remove(filename.c_str());
}

TEST(FileLoadingTest, BattleWithLoadedNpcs) {
    std::string filename = "test_data_npcs.txt";
    createTestDataFile(filename);
    
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    arena.loadFromFile(filename);
    
    std::cout << "\n=== Детальный тест боя ===" << std::endl;
    std::cout << "Загружено NPC: " << arena.getNpcCount() << std::endl;
    
    std::cout << "\nБой с дальностью 100 метров (только близкие NPC):" << std::endl;
    arena.startBattle(100.0);
    
    std::cout << "\nВыжившие:" << std::endl;
    arena.printAllNpcs();
    std::cout << "Осталось NPC: " << arena.getNpcCount() << std::endl;
    
    EXPECT_GE(arena.getNpcCount(), 1);  // Хотя бы кто-то должен выжить
    
    std::remove(filename.c_str());
}

TEST(FileLoadingTest, LoadFileWithInvalidData) {
    std::string filename = "invalid_test_file.txt";
    
    // Создаём файл с некорректными данными
    std::ofstream outfile(filename);
    outfile << "Dragon Smaug 100 200\n";
    outfile << "InvalidType InvalidName\n";  // Неправильный формат
    outfile << "Elf Legolas 150 250\n";
    outfile.close();
    
    Arena arena;
    
    // Загрузка должна пройти, но некорректная строка будет пропущена
    EXPECT_NO_THROW({
        arena.loadFromFile(filename);
    });
    
    // Должны загрузиться только 2 корректные строки
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    std::remove(filename.c_str());
}