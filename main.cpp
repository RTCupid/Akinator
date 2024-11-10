#include <stdio.h>

#include "Akinator.h"

int main ()
{
    tree_t tree = {};
    AkinatorCtor (&tree);
    NewNode ("Полторашка", tree.root, LEFT);
    NewNode ("Ведёт дискру", tree.root, RIGHT);
    NewNode ("Бурцев", tree.root->right, LEFT);
    NewNode ("Ведёт физос", tree.root->right, RIGHT);
    NewNode ("Нефор", tree.root->right->right, LEFT);
    NewNode ("Колдунов", tree.root->right->right->left, LEFT);
    NewNode ("Овчос", tree.root->right->right->left, RIGHT);
    NewNode ("Чубаров", tree.root->right->right, RIGHT);

    AkinatorGraphviz (&tree);

    AkinatorDtor (&tree);
    return 0;
}

