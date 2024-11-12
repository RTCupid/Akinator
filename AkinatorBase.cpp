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
    char symbol = '\0';
    fscanf (base_file, "%c", &symbol);

    if (symbol != '{' && symbol != '}')
    {
        ungetc (symbol, base_file);
        fscanf (base_file, "%[^{]", akntr->text);
    }
    else
    {
        ungetc (symbol, base_file);
    }

    fscanf (base_file, "%c", &symbol);

    if (symbol == '{')
    {
        fscanf (base_file, "\"%[^\"]\"", akntr->text);
        printf ("text = <%s>\n", akntr->text);

        //akntr->crnt_node = akntr->root;

        NewNode (akntr->text, akntr->crnt_node, LEFT);
        akntr->crnt_node = akntr->crnt_node->left;
        RunAkinatorBase (akntr, base_file);

        NewNode (akntr->text, akntr->crnt_node, RIGHT);
        akntr->crnt_node = akntr->crnt_node->right;
        RunAkinatorBase (akntr, base_file);

        //errTr_t NewNode (const char* text, node_t* parrent, brnch_side_t branch_side)
    }
    if (symbol == '}')
    {
        printf ("return\n");
        return;
    }
}


