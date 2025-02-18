#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree<int> tree;

    /*tree.InsertLoop(200);
    tree.InsertLoop(100);
    tree.InsertLoop(300);
    tree.InsertLoop(50);
    tree.InsertLoop(250);
    tree.InsertLoop(350);
    tree.InsertLoop(70);
    tree.InsertLoop(270);*/

    tree.InsertReq(200);
    tree.InsertReq(100);
    tree.InsertReq(300);
    tree.InsertReq(50);
    tree.InsertReq(250);
    tree.InsertReq(350);
    tree.InsertReq(70);
    tree.InsertReq(270);

    tree.Print();

}
