#include "candyCrash.cpp"
void countdown(std::atomic<bool>& time_up) {
    std::this_thread::sleep_for(std::chrono::seconds(50));
    time_up = true;
    std::cout << "\n\n\n\n                                          (*_*) game over                                        \n\n\n\n" << std::endl;
}
int main()

{  
  
    Grid grid;
    int x1, y1, x2, y2;
    int *px1 = &x1;
    int *py1 = &y1;
    int *px2 = &x2;
    int *py2 = &y2;
        int choice = 0;
        char pass;
do{
    while (choice != 3) {
       grid.displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                grid.displayStart();
                choice=3;
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

    std::cout << "                                              Welcome to the Candy Crush-inspired Game!                       \n"; std::cout <<std::endl;
  
    grid.display();
   std::atomic<bool> time_up(false);
 
    std::thread timer_thread(countdown, std::ref(time_up));
    while (!time_up)
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
            std::cout<< "Try a different move.\n";
        }
       
    }  std::cout << "Do you want to try again? (y/n): ";
    std::cin>>pass;
   if (timer_thread.joinable()) {
        timer_thread.join();
    } choice=0;}
    while (pass=='y');
    
   
    return 0;
}
