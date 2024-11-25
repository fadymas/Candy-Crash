#include "candyCrash.cpp"
int main()

{

    Grid grid;
    int x1, y1, x2, y2;
    int *px1 = &x1;
    int *py1 = &y1;
    int *px2 = &x2;
    int *py2 = &y2;
    int mode;
    int choice = 0;
    char pass;
    do
    {
        while (choice != 3)
        {
            grid.displayMenu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                grid.displayStart();
                choice = 3;
                break;
            case 2:
                grid.displayHowToPlay();
                break;
            case 3:
                grid.displayExit();

                return 0;
                break;
            default:
                std::cout << "Invalid choice. Please choose again.\n";
            }
        }
        std::cout << "\nwhich mode do you want \n1|Timer\n2|Moves\nenter-> ";
        std::cin >> mode;
        switch (mode)
        {
        case 1:
        {
            std::cout << "                                              Welcome to the Candy Crush-inspired Game!                       \n";
            std::cout << std::endl;
            grid.display(false,180);
            grid.countDown(px1, py1, px2, py2);

            break;
        }
        case 2:
        {
            std::cout << "                                              Welcome to the Candy Crush-inspired Game!                       \n";
            std::cout << std::endl;

            grid.display(true);

            while (grid.availablemove())
            {

                grid.wainForHint(px1, py1, px2, py2);

                if (grid.validateMove(x1, y1, x2, y2))
                {
                    grid.detectAndRemoveMatches();
                    grid.display(true);
                }
                else
                {
                    grid.display(true);
                    std::cout << "Try a different move.\n";
                }
            }
            break;
        }
        }
        std::cout << "\nDo you want to try again? (y/n): ";
        std::cin >> pass;
        choice = 0;
    } while (pass == 'y');

    return 0;
}
