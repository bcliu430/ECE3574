#include <vector>
#include <iostream>

using namespace std;

struct node {
    int data;
    int anotherData;
    vector <node *> children;

};

node *root  = new node;

void traversePost(node * curnode){ // post order  proj1
    for (int  index =0; index < curnode -> children.size(); index++ ){
        traversePost(curnode -> children[index]);
    }
    cout << curnode -> data << endl; 

}

int main (){

    root -> data = 20;


    node *mynewchild = nullptr;
    node *newchild2 = nullptr;

    for (int i =0; i < 5; i++){
        mynewchild = new node;
        mynewchild -> data =i;

        newchild2 = new node;
        newchild2 -> data=35;

        mynewchild -> children.push_back(newchild2);

        root -> children.push_back(mynewchild);
    }


    cout << "Post: " << endl;
    traversePost(root);


    return 0;
}
