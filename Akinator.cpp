#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"

errTr_t AkinatorCtor (tree_t* tree)
{
    tree->root = (node_t*)calloc (1, sizeof (*tree->root));
    if (!tree->root)
    {
        printf ("ERROR: not enough memory\n"
                "calloc of tree->root returned NULL\n");
        return ERROR_CTOR_TREE;
    }
    tree->root->text = (char*) calloc (SIZE_TEXT, sizeof (char));
    if (!tree->root->text)
    {
        printf ("ERROR: not enough memory\n"
                "calloc of tree->root returned NULL\n");
        return ERROR_CTOR_TREE;
    }

    const char text[SIZE_TEXT] = "Животное";
    for (int i = 0; i < SIZE_TEXT; i++)
    {
        //printf ("i = <%d>\n text[%d] = <%c>\n", i, i, text[i]);
        if (text[i] == '\0' || text[i] == '\n' || text[i] == '\r' || text[i] == '?')
        {
            break;
        }
        tree->root->text[i] = text[i];
    }

    tree->root->left  = NULL;
    tree->root->right = NULL;

    tree->crnt_node = tree->root;

    return TREE_OK;
}

errTr_t NewNode (const char* text, node_t* parrent, brnch_side_t branch_side)
{
    node_t* node = (node_t*)calloc (1, sizeof (*node));
    node->text = (char*) calloc (SIZE_TEXT, sizeof (char));

    for (int i = 0; i < SIZE_TEXT; i++)
    {
        if (text[i] == '\0' || text[i] == '\n' || text[i] == '\r' || text[i] == '?')
        {
            break;
        }
        node->text[i] = text[i];
    }

    node->left  = NULL;
    node->right = NULL;
    node->prnt  = parrent;

    if (branch_side == LEFT)
    {
        parrent->left = node;
    }
    else
    {
        parrent->right = node;
    }

    return TREE_OK;
}

void AkinatorDtor (tree_t* tree)
{
    ClearTree (tree->root);
}

void ClearTree (node_t* node)
{
    if (!node)
    {
        return;
    }
    if (node->left)
    {
        ClearTree (node->left);

    }
    if (node->right)
    {
        ClearTree (node->right);
    }

    free (node->text);
    node->text = NULL;

    free (node);
    node = NULL;
}
