#include "candyCrash.h"

struct node_matrix {
    node_matrix* next_col;
    Node* row;

    node_matrix() : next_col(nullptr), row(nullptr) {}
};

class linkedlistmatrix {
private:
    Node* head_row;
    node_matrix* head_col;
    int counter;
    int size;

public:
    linkedlistmatrix() : head_row(nullptr), head_col(nullptr), counter(-1), size(0) {}

    void inserter_next_col(node_matrix* col) {
        if (head_col == nullptr) {
            head_col = col; 
        }
        else {
            node_matrix* temp = head_col;
       
            while (temp->next_col != nullptr) {
                temp = temp->next_col;
            }
            temp->next_col = col; 
        }
        col->next_col = nullptr; 
    }

    void inserter_next_row(Node* row) {
        if (head_row == nullptr) {
            head_row = row; 
            row->down = nullptr;
        }
        else {
            Node* temp = head_row;
          
            while (temp->down != nullptr) {
                temp = temp->down;
            }
            temp->down = row; 
            row->down = nullptr; 
        }
    }

    void display() {
        if (head_col == nullptr) {
            cout << "Matrix is empty.\n";
            return;
        }
        node_matrix* temp_col = head_col;
        int col_index = 0;
        while (temp_col != nullptr) {
            cout << "Column " << col_index << ":";
            Node* temp_row = temp_col->row;
            while (temp_row != nullptr) {
                cout << " (" << temp_row->positionX << ", " << temp_row->positionY
                    << ", " << temp_row->candyColor << ")";
                temp_row = temp_row->down;
            }
            cout << endl;
            temp_col = temp_col->next_col;
            col_index++;
        }
    }

    ~linkedlistmatrix() {
     
        node_matrix* temp_col = head_col;
        while (temp_col != nullptr) {
            Node* temp_row = temp_col->row;
            while (temp_row != nullptr) {
                Node* to_delete = temp_row;
                temp_row = temp_row->down;
                delete to_delete;
            }
            node_matrix* to_delete_col = temp_col;
            temp_col = temp_col->next_col;
            delete to_delete_col;
        }
    }
};


