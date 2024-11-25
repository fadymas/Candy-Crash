#include <iostream>
#include <stdexcept>

#include "linkedlistmatrix.h"


Matrix::Matrix() : data(nullptr), right(nullptr), down(nullptr) {}

LinkedList2D::LinkedList2D() : head(nullptr) {}



void LinkedList2D::add(int row, int col, Node *value) {
    if (row < 0 || col < 0) return;

    if (!head) {
        head = new Matrix();
    }

    Matrix* row_ptr = head;

    // Navigate to the correct row
    for (int i = 0; i < row; ++i) {
        if (!row_ptr->down) {
            row_ptr->down = new Matrix();
        }
        row_ptr = row_ptr->down;
    }

    // Navigate to the correct column
    for (int j = 0; j < col; ++j) {
        if (!row_ptr->right) {
            row_ptr->right = new Matrix();
        }
        row_ptr = row_ptr->right;
    }

    // Set the value at the node
    row_ptr->data = value;
}

Node* LinkedList2D::get(int row, int col)  {
    if (row < 0 || col < 0) return nullptr;

    Matrix* row_ptr = head;

    // Navigate to the correct row
    for (int i = 0; i < row; ++i) {
        if (!row_ptr) return nullptr;
        row_ptr = row_ptr->down;
    }

    // Navigate to the correct column
    for (int j = 0; j < col; ++j) {
        if (!row_ptr) return nullptr;
        row_ptr = row_ptr->right;
    }

    return row_ptr ? row_ptr->data : nullptr;
}
