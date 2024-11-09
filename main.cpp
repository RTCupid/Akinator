#include <stdio.h>

#include "Akinator.h"

int main ()
{
    tree_t tree = {};
    AkinatorCtor (&tree);
    NewNode ("Полторашка", tree.root, LEFT);
    NewNode ("Ведёт Дискру", tree.root, RIGHT);
    NewNode ("Бурцев", tree.root->right, LEFT);
    NewNode ("Ведёт Физос", tree.root->right, RIGHT);
    NewNode ("NEFOR", tree.root->right->right, LEFT);
    NewNode ("Колдунов", tree.root->right->right->left, LEFT);
    NewNode ("Овчос", tree.root->right->right->left, RIGHT);
    NewNode ("Чубаров", tree.root->right->right, RIGHT);

    AkinatorDump (&tree);

    AkinatorDtor (&tree);
    return 0;
}

