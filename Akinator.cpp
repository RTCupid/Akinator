#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "Akinator.h"
#include "AkinatorBase.h"

errTr_t AkinatorCtor (tree_t* akntr)
{
    akntr->log_file = fopen ("log_file.htm", "wt");

    // akntr->root = (node_t*)calloc (1, sizeof (*akntr->root));
    // if (!akntr->root)
    // {
    //     printf ("ERROR: not enough memory\n"
    //             "calloc of tree->root returned NULL\n");
    //     return ERROR_CTOR_TREE;
    // }
    // akntr->root->text = (char*) calloc (SIZE_TEXT, sizeof (char));
    // if (!akntr->root->text)
    // {
    //     printf ("ERROR: not enough memory\n"
    //             "calloc of tree->root returned NULL\n");
    //     return ERROR_CTOR_TREE;
    // }

    akntr->text= (char*) calloc (SIZE_TEXT, sizeof (akntr->text));

    // const char text[SIZE_TEXT] = "Животное";
    // for (int i = 0; i < SIZE_TEXT; i++)
    // {
    //     if (text[i] == '\0' || text[i] == '\n' || text[i] == '\r' || text[i] == '?')
    //     {
    //         break;
    //     }
    //     akntr->root->text[i] = text[i];
    // }

//
//     akntr->root->left  = NULL;
//     akntr->root->right = NULL;
//     akntr->root->prnt = NULL;
//
     akntr->crnt_node = NULL;

    return TREE_OK;
}

errTr_t NewNode (const char* text, node_t* parrent, brnch_side_t branch_side, tree_t* akntr)
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

    if (parrent)
    {
        if (branch_side == LEFT)
        {
            parrent->left = node;
        }
        else
        {
            parrent->right = node;
        }
    }
    if (!parrent && !akntr->root)
    {
        akntr->root = node;
        akntr->crnt_node = akntr->root;
    }

    printf ("New node = <%p>\n\n", node);
    return TREE_OK;
}

void AkinatorDtor (tree_t* akntr)
{
    ClearTree (akntr->root);

    free (akntr->base);
    akntr->base = NULL;

    free (akntr->text);
    akntr->text = NULL;

    akntr->crnt_node = NULL;

    fclose (akntr->log_file);
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
