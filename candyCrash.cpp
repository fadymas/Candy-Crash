#include "candyCrash.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

Node::Node(int pX, int pY, const string &candyColor, bool hasStar) : positionX(pX), positionY(pY), candyColor(candyColor), hasStar(hasStar), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {};
// ToDo: Create The Grid Of Nodes With candys
Grid::Grid() : size(30)
{
    srand(time(nullptr));

    nodes.resize(size, vector<Node *>(size, nullptr));
    const vector<string> candys = {"R", "G", "B"};

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            nodes[i][j] = new Node(i, j, candys[rand() % candys.size()]);
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
    initializeStars();
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
void Grid::display()
{
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

    /* code */
}
// ToDo:Swap The candys of Two Nodes
bool Grid::swapNodes(Node *node1, Node *node2)
{
    swap(node1->candyColor, node2->candyColor);
    return true;
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
        std::cout << "Invalid move: No match created. Try a different move.\n";
    }
    return isValid;
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
                // Add nodes in the match to nodesToRemove
                Node *temp = node;
                while (temp && temp->candyColor == node->candyColor)
                {
                    nodesToRemove.insert(temp);
                    temp = temp->left;
                }
                temp = node->right;
                while (temp && temp->candyColor == node->candyColor)
                {
                    nodesToRemove.insert(temp);
                    temp = temp->right;
                }

                temp = node->up;
                while (temp && temp->candyColor == node->candyColor)
                {
                    nodesToRemove.insert(temp);
                    temp = temp->up;
                }
                temp = node->down;
                while (temp && temp->candyColor == node->candyColor)
                {
                    nodesToRemove.insert(temp);
                    temp = temp->down;
                }
            }
        }
    }
    for (Node *node : nodesToRemove)
    {
        node->candyColor = "";
        if (node->hasStar)
        {
            std::cout << "Star collected!\n";
            node->hasStar = false;
        }
    }
    refillEmptySpaces();
}
void Grid::refillEmptySpaces()
{

    const vector<string>
        colors = {"R", "B", "G"};
    for (int j = 0; j < size; j++)
    { // Process each column
        bool hasEmptyCells = true;

        // Continue refilling until there are no empty cells in the column
        while (hasEmptyCells)
        {
            hasEmptyCells = false;

            for (int i = size - 1; i > 0; i--)
            { // Start from the bottom row and go upwards
                if (nodes[i][j]->candyColor.empty())
                {
                    // Move the color from the cell above down to the current cell
                    nodes[i][j]->candyColor = nodes[i - 1][j]->candyColor;
                    nodes[i - 1][j]->candyColor = ""; // Clear the cell above
                    hasEmptyCells = true;             // Indicate that we found an empty cell and need another pass
                }
            }

            // After shifting, fill the top cell of the column if it's empty
            if (nodes[0][j]->candyColor.empty())
            {
                nodes[0][j]->candyColor = colors[rand() % colors.size()];
            }
        }
    }
}