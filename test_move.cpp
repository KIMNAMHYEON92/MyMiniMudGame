#include <vector>
#include <memory>
#include <string>

class Character {
public:
    Character() {}
    virtual ~Character() {}
};

class Monster : public Character {
    std::vector<std::unique_ptr<int>> skills;
public:
    Monster() {}
};

int main() {
    std::vector<Monster> monsters;
    monsters.push_back(Monster());
    return 0;
}
