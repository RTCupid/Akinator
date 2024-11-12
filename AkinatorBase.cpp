#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "Akinator.h"
#include "AkinatorBase.h"

errTr_t MakeAkinatorBase (tree_t* akntr, const char* namefile)
{
    FILE* base_file = fopen (namefile, "rt");

    RunAkinatorBase (akntr, base_file);

    fclose (base_file);
    return TREE_OK;
}

void RunAkinatorBase (tree_t* akntr, FILE* base_file)
{
    static int side = -1;

    char symbol = '\0';
    fscanf (base_file, "%c", &symbol);
    printf ("symbol = <%c>\n", symbol);

    if (symbol != '{' && symbol != '}')
    {
        ungetc (symbol, base_file);
        fscanf (base_file, "%[^{}]", akntr->text);
        printf ("skipping text = <%s>\n", akntr->text);
    }
    else
    {
        ungetc (symbol, base_file);
    }
    fscanf (base_file, "%c", &symbol);
    printf ("again symbol = <%c>\n", symbol);
    if (symbol == '{')
    {
        side *= -1;
        fscanf (base_file, "\"%[^\"]\"", akntr->text);
        printf ("text = <%s>\n", akntr->text);

        if (side == 1)
        {
            printf ("side = 1\n");
            NewNode (akntr->text, akntr->crnt_node, LEFT);
            node_t* parent = akntr->crnt_node;
            akntr->crnt_node = akntr->crnt_node->left;

            RunAkinatorBase (akntr, base_file);
            printf ("return\n");

            akntr->crnt_node = parent;
        }
        if (side == -1)
        {
            printf ("side = -1\n");
            NewNode (akntr->text, akntr->crnt_node, RIGHT);
            node_t* parent = akntr->crnt_node;
            akntr->crnt_node = akntr->crnt_node->right;

            RunAkinatorBase (akntr, base_file);
            printf ("return\n");

            akntr->crnt_node = parent;
        }
    }
    else if (symbol == '}')
    {
        side *= -1;
        return;
    }
    return;
}

