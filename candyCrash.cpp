#include "candyCrash.h"
#include <iostream>
#include <vector>
using namespace std;

Node::Node(int pX, int pY, const string &candyColor, bool hasStar) : positionX(pX), positionY(pY), candyColor(candyColor), hasStar(hasStar), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {};

Grid::Grid() : size(30), nodes(nodes)
{
    srand(time(nullptr));

    nodes.resize(size, vector<Node *>(size, nullptr));
    const vector<string> colors = {"R", "G", "B"};

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            nodes[i][j] = new Node(i, j, colors[rand() % colors.size()]);
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
            nodes[x][y]->candyColor += '*';

            starPlaced++;
        }
    }
}
void Grid::display()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << "[";
            cout << nodes[i][j]->candyColor;
            if (nodes[i][j]->hasStar)
            {
                cout << "]";
            }
            else
            {
                cout << "] ";
            }
        }
        cout << endl;
    }

    /* code */
}
