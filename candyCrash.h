#ifndef CANDYCRASH_H
#define CANDYCRASH_H
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <atomic>
#include <thread>
#include <limits>
#include "linkedlistmatrix.cpp"
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
  LinkedList2D nodes;
  int starsCollected;
  int movestate = 20;
  int score = 0;
  string colors[4] = {"R", "G", "B", "Y"};

public:
  Grid();
  ~Grid();
  void initializeStars();
  void display(bool mode, int time = 0);
  bool swapNodes(Node *node1, Node *node2);
  bool checkForMatch(Node *node);
  bool validateMove(int x1, int y1, int x2, int y2);
  void detectAndRemoveMatches();
  void initializeColors();
  bool hasInitialMatches();
  void reassignMatchedCells();
  void MoveEmptyToTop();
  void hint();
  void wainForHint(int *x1, int *y1, int *x2, int *y2, int *countdown = nullptr);
  void countDown(int *x1, int *y1, int *x2, int *y2);
  void setConsoleColor(const std::string &colorCode);
  void displayMenu();
  void displayStart();
  bool availablemove();

  void displayHowToPlay();

  void displayExit();

  bool collactstars();
  void endgame();
};

#endif