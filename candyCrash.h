#ifndef CANDYCRASH_H
#define CANDYCRASH_H
#include <string>
#include <vector>
using namespace std;

struct Node
{
public:
    Node *right, *left, *up, *down;
    string candyColor;
    int positionX;
    int positionY;
    bool hasStar;

    Node(int pX, int pY, const string &candyColor, bool hasStar = false);
};

class Grid
{
private:
    int size;
    vector<vector<Node *>> nodes;

public:
    Grid();
    ~Grid();
    void initializeStars();
    void display();
    bool swapNodes(Node *node1, Node *node2);
    bool checkForMatch(Node *node);
    bool validateMove(int x1, int y1, int x2, int y2);
    void detectAndRemoveMatches();
    void refillEmptySpaces();
};

#endif