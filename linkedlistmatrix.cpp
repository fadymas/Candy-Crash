#include "candyCrash.h"

struct node_col {
   
    Node* data;
    node_col* next_col;
    int index ;
    node_col(): data(nullptr),next_col(nullptr) ,int index (-1) {}
};
struct node_row {
    node_row* next_row;
    node_col* col;
    int index ;
    node_row(): col(nullptr),next_row(nullptr),int index (-1) {}
};

class linkedlistmatrix {
private:
    node_row* head_row;
    node_col* head_col;
    int counter;
    int size_row ;
    int size_col ;


public:
    linkedlistmatrix() : head_row(nullptr), head_col(nullptr), counter(-1), size_row(-1) , size_col(-1) {}

    void inserter_next_col(node_row* row ,  node_col* col) {

    }

    void inserter_next_row(node_row* row) {
   if (head_row==nullptr){
    head_row=row;size_row++;
   }else{
    node_row* temp= head_row;
    if (temp->next_row ==nullptr){size_row++;}
    while (temp->next_row !=nullptr)
    { temp =temp->next_row;
    size_row++;
    }
    temp->next_row=row;
   }
    }


    void display() {int i=0;
  node_row* temp= head_row;
    while (temp)
    {
         temp =temp->next_row;
         i++;
    cout << i <<endl;
    }
    }

    // ~linkedlistmatrix() {
     
    //     node_matrix* temp_col = head_col;
    //     while (temp_col != nullptr) {
    //         Node* temp_row = temp_col->row;
    //         while (temp_row != nullptr) {
    //             Node* to_delete = temp_row;
    //             temp_row = temp_row->down;
    //             delete to_delete;
    //         }
    //         node_matrix* to_delete_col = temp_col;
    //         temp_col = temp_col->next_col;
    //         delete to_delete_col;
    //     }
    // }
};
int main(){
    node_row*  nope=new node_row;
    node_row*  nope1=new node_row;
    node_row*  nope3=new node_row;
  linkedlistmatrix v;
  v.inserter_next_row(new node_row);
  v.inserter_next_row(new node_row);
   v.inserter_next_row(new node_row);
  v.display();
    return 0;
}


