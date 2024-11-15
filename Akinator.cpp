#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "Akinator.h"
#include "AkinatorBase.h"

errTr_t AkinatorCtor (tree_t* akntr)
{
    akntr->dbg_log_file = fopen ("dbg_log_file.txt", "wt");

    akntr->text= (char*) calloc (SIZE_TEXT, sizeof (akntr->text));

    akntr->crnt_node = NULL;

    return TREE_OK;
}

node_t* NewNode (tree_t* akntr, const char* text, node_t* left = nullptr, node_t* right = nullptr)
{
    node_t* node = (node_t*)calloc (1, sizeof (*node));

    node->text = strdup (text);

    node->left  = left;
    node->right = right;

    fprintf (akntr->dbg_log_file, "New node = <%p>\n\n", node);
    return node;
}

void AskSaveOrNot (tree_t* akntr, const char* namefile)
{
    printf ("Сохранить базу?\n");
    printf ("Да\\нет [y\\n]\n");

    char action = 0;
    scanf (" %c", &action);

    if (action == 'y')
    {
        FILE* base_file = fopen (namefile, "wt");
        WriteBase (akntr->root, base_file, 1);
        fclose (base_file);
    }
    else
    {
        return;
    }
}

void WriteBase (node_t* crnt_node, FILE* base_file, int level)
{
    WriteTab (level);
    fprintf (base_file, "{");
    printf ("{");
    fprintf (base_file, "\"%s\"", crnt_node->text);
    printf ("\"%s\"", crnt_node->text);
    if (crnt_node->left)
    {
        fprintf (base_file, "\n");
        printf ("\n");
        WriteBase (crnt_node->left , base_file, level + 1);
        WriteBase (crnt_node->right, base_file, level + 1);
        WriteTab (level);
    }
    fprintf (base_file, "}\n");
    printf ("}\n");
    return;
}

void WriteTab (int level)
{
    for (int i = 1; i < level; i++)
    {
        printf ("\t");
    }
}

void AkinatorDtor (tree_t* akntr)
{
    fclose (akntr->dbg_log_file);

    ClearTree (akntr->root);

    free (akntr->base);
    akntr->base = NULL;

    free (akntr->text);
    akntr->text = NULL;

    akntr->crnt_node = NULL;
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
