#include <stdio.h>

#include "Akinator.h"
#include "AkinatorBase.h"

int main ()
{
    tree_t akntr = {};
    AkinatorCtor (&akntr);

    MakeAkinatorBase (&akntr, "AkinatorBase.txt");

    NewNode ("Полторашка", akntr.root, LEFT);
    NewNode ("Ведёт дискру", akntr.root, RIGHT);
    NewNode ("Бурцев", akntr.root->right, LEFT);
    NewNode ("Ведёт физос", akntr.root->right, RIGHT);
    NewNode ("Нефор", akntr.root->right->right, LEFT);
    NewNode ("Колдунов", akntr.root->right->right->left, LEFT);
    NewNode ("Овчос", akntr.root->right->right->left, RIGHT);
    NewNode ("Чубаров", akntr.root->right->right, RIGHT);

    AkinatorGraphviz (&akntr);

    AkinatorDtor (&akntr);
    return 0;
}

