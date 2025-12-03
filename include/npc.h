#pragma once
#include <string>
#include <memory>

class Visitor;

class Npc {
    public:
        Npc(int x, int y, const std::string& type, const std::string& name);

        virtual ~Npc() = default;
        int getX() const;
        int getY() const;
        std::string getType() const;
        std::string getName() const;

        double distanceTo(const Npc& other) const;
        virtual void accept(Visitor& visitor) = 0;

        virtual void printInfo() const;

        friend std::ostream& operator<<(std::ostream& os, const Npc& npc);

    private:
        int x_;
        int y_;
        std::string type_;
        std::string name_;
};