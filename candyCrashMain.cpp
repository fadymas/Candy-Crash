#include "candyCrash.cpp"
#include <iostream>

int main()
{
    Grid grid;
    int x1, y1, x2, y2;

    std::cout << "Welcome to the Candy Crush-inspired Game!\n";
    grid.display();

    while (true)
    {
        std::cout << "\nEnter the coordinates of the two nodes you want to swap (e.g., 'x1 y1 x2 y2'): ";
        std::cin >> x1 >> y1 >> x2 >> y2;

        if (grid.validateMove(x1, y1, x2, y2))
        {
            grid.detectAndRemoveMatches();
            grid.display();
        }
        else
        {
            std::cout << "Try a different move.\n";
        }
    }

    return 0;
}
