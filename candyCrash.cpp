#include "candyCrash.h"
#include <iostream>
#include <vector>
using namespace std;

Node::Node(int pX, int pY, const string &candyColor, bool hasStar) : positionX(pX), positionY(pY), candyColor(candyColor), hasStar(hasStar), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {};

Grid::Grid(int const size, vector<vector<Node *>> nodes) : size(size), nodes(nodes)
{
    nodes.resize(size, vector<Node *>(size, nullptr));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            nodes[i][j] = new Node(i, j, "");
        }
    }
}