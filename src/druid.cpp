#include "../include/druid.h"
#include "../include/visitor.h"
#include <iostream>

const std::string Druid::kType = "Druid";

Druid::Druid(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

void Druid::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Druid::printInfo() const {
    std::cout << "Druid Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}