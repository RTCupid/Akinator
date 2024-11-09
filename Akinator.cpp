#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"

errTr_t AkinatorCtor (tree_t* tree)
{
    tree->root = (node_t*)calloc (1, sizeof (*tree->root));
    if (!tree->root)
    {
        fprintf (tree->log_file, "ERROR: not enough memory\n"
                                 "calloc of tree->root returned NULL\n");
        return ERROR_CTOR_TREE;
    }
    tree->root->data = 50;

    tree->root->left  = NULL;
    tree->root->right = NULL;

    tree->crnt_node = tree->root;

    AkinatorDump (tree);

    return TREE_OK;
}

void AkinatorDtor (tree_t* tree)
{
    AkinatorDump (tree);
    ClearTree (tree->root);
}

errTr_t AkinatorInsert (tree_t* tree, int data)
{
    AkinatorDump (tree);
    if (data < tree->crnt_node->data)
    {
        if (!tree->crnt_node->left)
        {
            NewNode (data, tree->crnt_node, LEFT);
            tree->crnt_node = tree->root;
            return TREE_OK;
        }
        else
        {
            tree->crnt_node = tree->crnt_node->left;
            AkinatorInsert (tree, data);
        }
    }
    else
    {
        if (!tree->crnt_node->right)
        {
            NewNode (data, tree->crnt_node, RIGHT);
            tree->crnt_node = tree->root;
            return TREE_OK;
        }
        else
        {
            tree->crnt_node = tree->crnt_node->right;
            AkinatorInsert (tree, data);
        }
    }
    return TREE_OK;
}

errTr_t NewNode (int data, node_t* parrent, brnch_side_t branch_side)
{
    node_t* node = (node_t*)calloc (1, sizeof (*node));
    node->data = data;

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

    free (node);
    node = NULL;
}
