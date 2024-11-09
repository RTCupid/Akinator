#include <stdio.h>

#include "Akinator.h"

int main ()
{
    tree_t tree = {};
    AkinatorCtor (&tree);
    NewNode (12, tree.root, LEFT);
    NewNode (5, tree.root->left, LEFT);
    NewNode (15, tree.root->left, RIGHT);
    NewNode (70, tree.root, RIGHT);
    NewNode (60, tree.root->right, LEFT);

    AkinatorDtor (&tree);
    return 0;
}

