#ifndef LINKEDLIST2D_H
#define LINKEDLIST2D_H

struct Node ;
struct Matrix {
public:
    Node* data;
    Matrix* right;
    Matrix* down;

    Matrix() ;
};




class LinkedList2D {
private:
    Matrix* head;

public:
    LinkedList2D();
   

    void add(int row, int col, Node *value);
    Node* get(int row, int col) ;
};

#endif 
