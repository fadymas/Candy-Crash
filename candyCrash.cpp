#include "candyCrash.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

Node::Node(int pX, int pY, const string &candyColor, bool hasStar) : positionX(pX), positionY(pY), candyColor(candyColor), hasStar(hasStar), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {};

// ToDo: Create The Grid Of Nodes With candys
Grid::Grid() : size(30), starsCollected(0)
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
    const vector<string> colors = {"R", "G", "B", "Y"}; // Define available colors
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
        reassignMatchedCells(); // Reassign colors to cells that are part of an initial match
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
                } while (newColor == node->candyColor); // Ensure new color is different
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
    for (int j = 0; j < size; j++) // iterate through each column
    {
        for (int i = size - 1; i > 0; i--) // iterate upwards from bottom to top
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
            {
                cout << " [";
                cout << nodes[i][j]->candyColor;
                cout << "*]";
            }
            else
            {
                cout << "  [";
                cout << nodes[i][j]->candyColor;
                cout << "]";
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
