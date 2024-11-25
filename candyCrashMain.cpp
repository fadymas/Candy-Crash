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
            while (!(cin >> choice))
            {
                cout << "\nPlease enter a valid integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

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
        while (!(cin >> mode))
        {
            cout << "\nPlease enter a valid integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (mode)
        {
        case 1:
        {
            std::cout << "                                              Welcome to the Candy Crush-inspired Game!                       \n";
            std::cout << std::endl;
            grid.display(false, 180);
            grid.countDown(px1, py1, px2, py2);

            break;
        }
        case 2:
        {
            std::cout << "                                              Welcome to the Candy Crush-inspired Game!                       \n";
            std::cout << std::endl;

            grid.display(true);

            while (grid.availablemove() && !grid.collactstars())
            {

                grid.wainForHint(px1, py1, px2, py2);

                if (grid.validateMove(x1, y1, x2, y2))
                {
                    grid.detectAndRemoveMatches();
                }
                else
                {

                    std::cout << "Try a different move.\n";
                }
                if (!grid.collactstars())
                {
                    grid.display(true);
                }
                else
                {
                    cout << "congratulation";
                }
            }
            break;
        }
        }
        grid.endgame();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "\nDo you want to try again? (y/n): ";
        while (!(cin >> pass))
        {
            cout << "\nPlease enter a valid integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        choice = 0;
    } while (pass == 'y');

    return 0;
}
