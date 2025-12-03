#pragma once
#include <memory>
#include <string>
#include "npc.h"

class NpcFactory {
    public:
        // Создание NPC по типу
        static std::unique_ptr<Npc> createNpc(
            const std::string& type,
            const std::string& name,
            int x, 
            int y
        );
        
        // Загрузка NPC из строки файла
        // Формат строки: "Тип Имя X Y"
        static std::unique_ptr<Npc> createFromString(const std::string& line);
};