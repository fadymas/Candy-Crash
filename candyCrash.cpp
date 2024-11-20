#include "candyCrash.h"

Node::Node(int pX, int pY, const string &candyColor, bool hasStar) : positionX(pX), positionY(pY), candyColor(candyColor), hasStar(hasStar), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {};

// ToDo: Create The Grid Of Nodes With candys
Grid::Grid() : size(31), starsCollected(0)
{

    nodes.resize(size, vector<Node *>(size, nullptr));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            nodes[i][j] = new Node(i, j, "");
        }
    };

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i > 0)
                nodes[i][j]->up = nodes[i - 1][j];
            if (i < size - 1)
                nodes[i][j]->down = nodes[i + 1][j];
            if (j > 0)
                nodes[i][j]->left = nodes[i][j - 1];
            if (j < size - 1)
                nodes[i][j]->right = nodes[i][j + 1];
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

            if (nodes[i][j]->candyColor.empty())
            {
                nodes[i][j]->candyColor = colors[rand() % colors.size()];
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
            Node *node = nodes[i][j];
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
            Node *node = nodes[i][j];

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
        if (!nodes[x][y]->hasStar)
        {
            nodes[x][y]->hasStar = true;

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
    Node *node1 = nodes[x1][y1];
    Node *node2 = nodes[x2][y2];
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
            Node *node = nodes[i][j];

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
            if (nodes[i][j] && nodes[i][j]->candyColor.empty())
            {
                int k = i - 1;
                while (k >= 0 && nodes[k][j]->candyColor.empty())
                {
                    k--;
                }
                if (k >= 0 && nodes[k][j] && !nodes[k][j]->candyColor.empty())
                {
                    swap(nodes[i][j]->candyColor, nodes[k][j]->candyColor);
                    swap(nodes[i][j]->hasStar, nodes[k][j]->hasStar);
                }
            }
        }
    }
    initializeColors();
}
void Grid::display()
{
    cout << "Stars Collected: " << starsCollected << "/5" << endl;

    cout << "     ";
    for (int i = 0; i < nodes.size(); i++)
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
            if (nodes[i][j]->hasStar)
            {if ("R"== nodes[i][j]->candyColor ){
                setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("31");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }else if ("G"== nodes[i][j]->candyColor )
            {
                setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("32");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }else if ("Y"== nodes[i][j]->candyColor )
            {
               setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("33");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }
            else if ("B"== nodes[i][j]->candyColor )
            {
                 setConsoleColor("0");
                 cout << " [";
                 setConsoleColor("34");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "*]";
            }
            
            }
            else
            { if ("R"== nodes[i][j]->candyColor ){
                setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("31");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "]";
            }else if ("G"== nodes[i][j]->candyColor )
            {
                setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("32");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "]";
            }else if ("Y"== nodes[i][j]->candyColor )
            {
               setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("33");
                cout << nodes[i][j]->candyColor;
                setConsoleColor("0");
                cout << "]";
            }
            else if ("B"== nodes[i][j]->candyColor )
            {
                 setConsoleColor("0");
                 cout << "  [";
                 setConsoleColor("34");
                cout << nodes[i][j]->candyColor;
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
            delete nodes[i][j];
        }
    }
}
void Grid::hint()
{

    for (int i = size - 1; i > 0; i--)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if (nodes[i][j]->hasStar)
            {
                Node *node = nullptr;
                if (nodes[i][j] && nodes[i][j]->down && nodes[i][j]->down->down)
                {
                    node = nodes[i][j]->down->down;
                }
                if (!node)
                {
                    node = nodes[i][j]->up->up;
                }

                if (!node)
                {
                    node = nodes[i][j]->left->left;
                }

                if (!node)
                {
                    node = nodes[i][j]->right->right;
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
            if (nodes[i][j]->hasStar)
            {
                Node *node = nodes[i][j];
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
            Node *node = nodes[i][j];
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
