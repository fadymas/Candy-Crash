#include "candyCrash.cpp"

int main()
{
    Grid grid;
    int x1, y1, x2, y2;
    int *px1 = &x1;
    int *py1 = &y1;
    int *px2 = &x2;
    int *py2 = &y2;

    std::cout << "Welcome to the Candy Crush-inspired Game!\n";
    grid.display();

    while (true)
    {

        grid.wainForHint(px1, py1, px2, py2);

        if (grid.validateMove(x1, y1, x2, y2))
        {
            grid.detectAndRemoveMatches();
            grid.display();
        }
        else
        {
            grid.display();
            std::cout
                << "Try a different move.\n";
        }
    }

    return 0;
}
