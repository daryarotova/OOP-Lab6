#pragma once
#include <string>
#include "npc.h"

class Dragon : public Npc {
    public:
        Dragon(int x, int y, const std::string& name);

        void accept(Visitor& visitor) override;

        void printInfo() const override;

    private:
        static const std::string kType;
};