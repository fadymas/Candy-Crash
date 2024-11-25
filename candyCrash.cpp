#include "candyCrash.h"

Node::Node(int pX, int pY, const string &candyColor, bool hasStar) : positionX(pX), positionY(pY), candyColor(candyColor), hasStar(hasStar), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {};

// ToDo: Create The Grid Of Nodes With candys
Grid::Grid() : size(30), starsCollected(0)
{

    

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
           nodes.add(i,j,new Node(i, j, ""));
        }
    };
    

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i > 0)
                nodes.get(i,j)->up = nodes.get(i-1,j);
            if (i < size - 1)
                nodes.get(i,j)->down = nodes.get(i+1,j);
            if (j > 0)
                nodes.get(i,j)->left =nodes.get(i,j-1);
            if (j < size - 1)
                nodes.get(i,j)->right = nodes.get(i,j+1);
        }
    };
    initializeColors();
    initializeStars();
}
void Grid::initializeColors()
{
    srand(time(nullptr));
    const vector<string> colors = {"R", "G", "B", "Y"};
    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            if ( nodes.get(i,j)->candyColor.empty())
            {
                 nodes.get(i,j)->candyColor = colors[rand() % colors.size()];
                counter++;
            }
        }
    }

    // while (hasInitialMatches() && counter < 900)
    // {
    //     detectAndRemoveMatches();
    //     return;
    // }

    while (hasInitialMatches())
    {
        reassignMatchedCells();
    }
}
bool Grid::hasInitialMatches()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Node *node =  nodes.get(i,j);
            if (node && checkForMatch(node))
            {
                return true;
            }
        }
    }
    return false;
}
bool Grid::checkForMatch(Node *node)
{
    if (node == nullptr)
        return false;

    int horCount = 1;
    Node *left = node->left;
    Node *right = node->right;
    while (left && left->candyColor == node->candyColor)
    {
        horCount++;
        left = left->left;
    }
    while (right && right->candyColor == node->candyColor)
    {
        horCount++;
        right = right->right;
    }
    int verCount = 1;
    Node *up = node->up;
    Node *down = node->down;
    while (up && up->candyColor == node->candyColor)
    {
        verCount++;
        up = up->up;
    }
    while (down && down->candyColor == node->candyColor)
    {
        verCount++;
        down = down->down;
    }

    return horCount >= 3 || verCount >= 3;
}
void Grid::reassignMatchedCells()
{
    srand(time(nullptr));
    const vector<string> colors = {"R", "G", "B", "Y"};

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Node *node =  nodes.get(i,j);

            if (node && checkForMatch(node) && !node->hasStar)
            {
                string newColor;
                do
                {
                    newColor = colors[rand() % colors.size()];
                } while (newColor == node->candyColor);
                node->candyColor = newColor;
            }
        }
    }
}
// ToDo: put Stars
void Grid::initializeStars()
{
    srand(time(nullptr));

    int starPlaced = 0;
    while (starPlaced < 5)
    {
        int x = rand() % size;
        int y = rand() % size;
        if (! nodes.get(x,y)->hasStar)
        {
             nodes.get(x,y)->hasStar = true;

            starPlaced++;
        }
    }
}
// ToDo:Swap The candys of Two Nodes
bool Grid::validateMove(int x1, int y1, int x2, int y2)
{
    if (abs(x1 - x2) + abs(y1 - y2) != 1)
    {
        cout << "Invalid move: Nodes are not adjacent.\n";
        return false;
    }
    Node *node1 =  nodes.get(x1,y1);
    Node *node2 = nodes.get(x2,y2);
    swapNodes(node1, node2);
    bool isValid = checkForMatch(node1) || checkForMatch(node2);
    if (!isValid)
    {
        swapNodes(node1, node2);
        cout << "Invalid move: No match created. Try a different move.\n";
    }
    return isValid;
}

bool Grid::swapNodes(Node *node1, Node *node2)
{
    swap(node1->candyColor, node2->candyColor);
    return true;
}

void Grid::detectAndRemoveMatches()
{
    set<Node *> nodesToRemove;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Node *node =  nodes.get(i,j);

            if (checkForMatch(node))
            {
                nodesToRemove.insert(node);
            }
        }
    }
    for (Node *node : nodesToRemove)
    {
        if (!node->hasStar)
        {
            node->candyColor = "";
        }
        else
        {
            cout << "Star collected!\n";
            starsCollected++;
            node->candyColor = "";
            node->hasStar = false;
        }
    }
    MoveEmptyToTop();
}

void Grid::MoveEmptyToTop()
{
    for (int j = 0; j < size; j++)
    {
        for (int i = size - 1; i > 0; i--)
        {
            if ( nodes.get(i,j) &&  nodes.get(i,j)->candyColor.empty())
            {
                int k = i - 1;
                while (k >= 0 &&  nodes.get(i,j)->candyColor.empty())
                {
                    k--;
                }
                if (k >= 0 &&  nodes.get(i,j) && ! nodes.get(i,j)->candyColor.empty())
                {
                    swap( nodes.get(i,j)->candyColor,  nodes.get(k,j)->candyColor);
                    swap( nodes.get(i,j)->hasStar,  nodes.get(k,j)->hasStar);
                }
            }
        }
    }
    initializeColors();
}
void Grid::display()
{   
    cout << "                                 Stars Collected: " << starsCollected << "/5" << endl;

    cout << "     ";
    for (int i = 0; i < 30; i++)
    {
        if (i > 9)
        {
            cout << i << "   ";
        }
        else
        {
            cout << i << "    ";
        }
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        if (i > 9)
        {
            cout << i << "";
        }
        else
        {
            cout << i << " ";
        }
        for (int j = 0; j < size; j++)
        {
            if ( nodes.get(i,j)->hasStar)
            {if ("R"==  nodes.get(i,j)->candyColor ){
                setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("31");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }else if ("G"==  nodes.get(i,j)->candyColor )
            {
                setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("32");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }else if ("Y"==  nodes.get(i,j)->candyColor )
            {
               setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("33");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }
            else if ("B"==  nodes.get(i,j)->candyColor )
            {
                 setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("34");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }
            
            }
            else
            { if ("R"==  nodes.get(i,j)->candyColor ){
                setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("31");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "]";
            }else if ("G"==  nodes.get(i,j)->candyColor )
            {
                setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("32");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "]";
            }else if ("Y"==  nodes.get(i,j)->candyColor )
            {
               setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("33");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "]";
            }
            else if ("B"==  nodes.get(i,j)->candyColor )
            {
                 setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("34");
                cout <<  nodes.get(i,j)->candyColor;
                setConsoleColor("0");
                cout << "]";
            }
            
            }
        }
        cout << endl;
    }
}
Grid::~Grid()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            delete  nodes.get(i,j);
        }
    }
}
void Grid::hint()
{

    for (int i = size - 1; i > 0; i--)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if ( nodes.get(i,j)->hasStar)
            {
                Node *node = nullptr;
                if ( nodes.get(i,j) &&  nodes.get(i,j)->down &&  nodes.get(i,j)->down->down)
                {
                    node =  nodes.get(i,j)->down->down;
                }
                if (!node)
                {
                    node =  nodes.get(i,j)->up->up;
                }

                if (!node)
                {
                    node =  nodes.get(i,j)->left->left;
                }

                if (!node)
                {
                    node =  nodes.get(i,j)->right->right;
                }
                if (node->up)
                {
                    swap(node->candyColor, node->up->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->up))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->up->positionX << "," << node->up->positionY << endl;
                        swap(node->candyColor, node->up->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->up->candyColor);
                }

                if (node->down)
                {
                    swap(node->candyColor, node->down->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->down))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->down->positionX << "," << node->down->positionY << endl;
                        swap(node->candyColor, node->down->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->down->candyColor);
                }

                if (node->left)
                {
                    swap(node->candyColor, node->left->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->left))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->left->positionX << "," << node->left->positionY << endl;
                        swap(node->candyColor, node->left->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->left->candyColor);
                }

                if (node->right)
                {
                    swap(node->candyColor, node->right->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->right))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->right->positionX << "," << node->right->positionY << endl;
                        swap(node->candyColor, node->right->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->right->candyColor);
                }
            }
        }
    }

    for (int i = size - 1; i > 0; i--)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if ( nodes.get(i,j)->hasStar)
            {
                Node *node =  nodes.get(i,j);
                if (node->up)
                {
                    swap(node->candyColor, node->up->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->up))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->up->positionX << "," << node->up->positionY << endl;
                        swap(node->candyColor, node->up->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->up->candyColor);
                }

                if (node->down)
                {
                    swap(node->candyColor, node->down->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->down))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->down->positionX << "," << node->down->positionY << endl;
                        swap(node->candyColor, node->down->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->down->candyColor);
                }

                if (node->left)
                {
                    swap(node->candyColor, node->left->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->left))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->left->positionX << "," << node->left->positionY << endl;
                        swap(node->candyColor, node->left->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->left->candyColor);
                }

                if (node->right)
                {
                    swap(node->candyColor, node->right->candyColor);
                    if (checkForMatch(node) || checkForMatch(node->right))
                    {
                        cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->right->positionX << "," << node->right->positionY << endl;
                        swap(node->candyColor, node->right->candyColor);
                        return;
                    }
                    swap(node->candyColor, node->right->candyColor);
                }
            }
        }
    }

    for (int i = size - 1; i > 0; i--)
    {
        for (int j = size - 1; j > 0; j--)
        {
            Node *node =  nodes.get(i,j);
            if (node->up)
            {
                swap(node->candyColor, node->up->candyColor);
                if (checkForMatch(node) || checkForMatch(node->up))
                {
                    cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->up->positionX << "," << node->up->positionY << endl;
                    swap(node->candyColor, node->up->candyColor);
                    return;
                }
                swap(node->candyColor, node->up->candyColor);
            }

            if (node->down)
            {
                swap(node->candyColor, node->down->candyColor);
                if (checkForMatch(node) || checkForMatch(node->down))
                {
                    cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->down->positionX << "," << node->down->positionY << endl;
                    swap(node->candyColor, node->down->candyColor);
                    return;
                }
                swap(node->candyColor, node->down->candyColor);
            }

            if (node->left)
            {
                swap(node->candyColor, node->left->candyColor);
                if (checkForMatch(node) || checkForMatch(node->left))
                {
                    cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->left->positionX << "," << node->left->positionY << endl;
                    swap(node->candyColor, node->left->candyColor);
                    return;
                }
                swap(node->candyColor, node->left->candyColor);
            }

            if (node->right)
            {
                swap(node->candyColor, node->right->candyColor);
                if (checkForMatch(node) || checkForMatch(node->right))
                {
                    cout << "Hint: Move " << node->positionX << "," << node->positionY << " to " << node->right->positionX << "," << node->right->positionY << endl;
                    swap(node->candyColor, node->right->candyColor);
                    return;
                }
                swap(node->candyColor, node->right->candyColor);
            }
        }
    }
}
void Grid::wainForHint(int *x1, int *y1, int *x2, int *y2)
{
    atomic<bool> inputReceived(false);

    thread hintTimer([&]()
                     {
        for (int i = 0; i < 15; i++) {
            if (inputReceived.load()) return;
            this_thread::sleep_for(chrono::seconds(1)); 
        }
        if (!inputReceived.load()) {
            
            hint(); 
            std::cout << "\nEnter the coordinates of the two nodes you want to swap (e.g., 'y1 x1 y2 x2'): ";
        } });

    std::cout << "\nEnter the coordinates of the two nodes you want to swap (e.g., 'y1 x1 y2 x2'): ";
    std::cin >> *x1 >> *y1 >> *x2 >> *y2;
    inputReceived.store(true);
    hintTimer.join();
}

void Grid::setConsoleColor(const std::string &colorCode)
{
     std::cout << "\033[" << colorCode << "m";
}

void Grid::displayMenu()
{{
    std::cout << "_______________________________________________________________________________________________________________________________\n";
    std::cout << "                                   _____________________________\n";
    std::cout << "                               1-|           Start               |\n";
    std::cout << "                                   ``````````````````````````````\n";
    std::cout << "                                   ______________________________\n";
    std::cout << "                               2-|           How to Play         |\n";
    std::cout << "                                   ``````````````````````````````\n";
    std::cout << "                                   ______________________________\n";
    std::cout << "                               3-|           Exit                |\n";
    std::cout << "                                   ``````````````````````````````\n";
       std::cout << "_______________________________________________________________________________________________________________________________\n";
    std::cout << "Enter your choice (^_^)  please-> ";
}
}

void Grid::displayStart()
{
    std::cout << "\n                                 Starting the game loading  ...@                                       \n";
 std::cout <<std::endl;
  std::cout <<std::endl;
   cout << "                                  (^__^)       please before you start make sure   make console full screen  and enter to be continue !! _.>" ;

    std::cin.ignore();
    std::cin.get(); 
     std::cout <<std::endl;
  std::cout <<std::endl;
}

void Grid::displayHowToPlay()
{
    std::cout << "\nHow to Play:\n";
    std::cout << "1. Match 3 or more candies *  .\n";
    std::cout << "2. move candy with xy coordinates  display  .\n";
    std::cout << "3. if it's difficult after time will display hint .\n";
    std::cout << "Press any key to return to the main menu.\n";
    std::cin.ignore();
    std::cin.get();
}

void Grid::displayExit()   
 {
    std::cout << "\n                                         Exiting the game...                          \n";
    std::cout << "\n                                         please try agian (~_~) later                  \n";
}
