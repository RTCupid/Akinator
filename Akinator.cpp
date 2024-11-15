#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <algorithm>

#include "Akinator.h"
#include "AkinatorBase.h"

errTr_t AkinatorCtor (tree_t* akntr)
{
    akntr->dbg_log_file = fopen ("dbg_log_file.txt", "wt");
    VerifyOpenFile (akntr->dbg_log_file, "AkinatorCtor");

    akntr->text= (char*) calloc (SIZE_TEXT, sizeof (akntr->text));

    akntr->crnt_node = NULL;

    return TREE_OK;
}

node_t* NewNode (tree_t* akntr, const char* text, node_t* left = nullptr, node_t* right = nullptr)
{
    node_t* node = (node_t*)calloc (1, sizeof (*node));

    node->text = text;

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
        VerifyOpenFile (base_file, "AskSaveOrNot");

        WriteBase (akntr->root, base_file, 1);
        WriteBase (akntr->root, stdout, 1);
        fclose (base_file);
    }
    else
    {
        return;
    }
}

void WriteBase (node_t* crnt_node, FILE* file, int level)
{
    WriteTab (level, file);
    fprintf (file, "{");
    fprintf (file, "\"%s\"", crnt_node->text);

    if (crnt_node->left)
    {
        fprintf (file, "\n");

        WriteBase (crnt_node->left , file, level + 1);
        WriteBase (crnt_node->right, file, level + 1);
        WriteTab (level, file);
    }
    fprintf (file, "}\n");
    return;
}

void WriteTab (int level, FILE* file)
{
    for (int i = 1; i < level; i++)
    {
        assert (i < level);
        fprintf (file, "\t");
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

size_t FindDeepTree (tree_t* akntr, node_t* root, size_t deep)
{
    if (!root->left)
    {
        return deep;
    }
    size_t deep_left = FindDeepTree (akntr, root->left, deep + 1);

    size_t deep_right = FindDeepTree (akntr, root->right, deep + 1);

    return (std::max) (deep_left, deep_right);
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

    free (const_cast<char*>(node->text)); // node->text is always owning heap pointer;
    node->text = NULL;

    free (node);
    node = NULL;
}

void VerifyOpenFile (FILE* file, const char* namefunc)
{
    if (file == NULL)
    {
        printf ("ERROR: in func: %s fopen returned nullptr\n", namefunc);
        assert (0);
    }
}
