#ifndef CANDYCRASH_H
#define CANDYCRASH_H
#include <string>
#include <vector>
using namespace std;

struct Node
{
public:
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    string candyColor;
    int positionX;
    int positionY;
    bool hasStar;

    Node(int pX, int pY, const string &candyColor, bool hasStar = false);
};

class Grid
{
private:
    int const size;
    vector<vector<Node *>> nodes;

public:
    Grid(int const size, vector<vector<Node *>> nodes);
};

#endif