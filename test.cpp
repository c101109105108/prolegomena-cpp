#include <iostream>

struct Target {
    int x, y;
    int distance;
    double timestamp;
    bool islocked;
};

void updateTarget(Target& t) {
    t.x = t.x + 10;
    std::cout << "Coordinates:" << '\n';
    std::cout << t.x << '\n' << t.y;
}

int main()
{
    Target Target1{ 100, 150, 25, 25.50, true };

    updateTarget(Target1);

}

// void updateTarget(Target* t) {t->x = t->x + 10; std::cout << "Coordinates:" << '\n'; std::cout << t->x << '\n' << t->y; 
//Target Target1;Target1.x = 100;Target1.y = 150;Target1.distance = 25;Target1.timestamp = 12.25;Target1.islocked = true;
