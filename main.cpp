#include <stdio.h>

#include "Akinator.h"
#include "AkinatorBase.h"

int main ()
{
    printf ("#Start Akinator!\n\n");

    tree_t akntr = {};
    AkinatorCtor (&akntr);

    MakeAkinatorBase (&akntr, "AkinatorBase.txt");

    /*NewNode ("Полторашка", akntr.root, LEFT);
    NewNode ("Ведёт дискру", akntr.root, RIGHT);
    NewNode ("Бурцев", akntr.root->right, LEFT);
    NewNode ("Ведёт физос", akntr.root->right, RIGHT);
    NewNode ("Нефор", akntr.root->right->right, LEFT);
    NewNode ("Колдунов", akntr.root->right->right->left, LEFT);
    NewNode ("Овчос", akntr.root->right->right->left, RIGHT);
    NewNode ("Чубаров", akntr.root->right->right, RIGHT);*/
#if 0
    node_t* NewNode(const char* text, node_t* left = nullptr, node_t* right = nullptr)
    {
        node_t* node = (node_t*)calloc(1, sizeof(node_t));
        node->text = text;
        node->left = left;
        node->right = right;
        return node;
    }
#endif
    /*
    NewNode("Бурцев")
    NewNode("Бурцев")
    NewNode("Бурцев")
    NewNode
        ( "Полторашка"
        , NewNode
            ( "Ведёт дискру"
                , NewNode("Бурцев")
                , NewNode("Колдунов")
            )
        , NewNode("Чубаров")
        );
    */

    AkinatorGraphviz (&akntr);

    AkinatorGuessPerson (&akntr);

    AkinatorGraphviz (&akntr);

    AkinatorDtor (&akntr);
    printf ("\n#End of programm\n");
    return 0;
}

