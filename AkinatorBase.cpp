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

    RunAkinatorBase (akntr, base_file, akntr->crnt_node, LEFT);

    fclose (base_file);
    return TREE_OK;
}

void RunAkinatorBase (tree_t* akntr, FILE* base_file, node_t* crnt_node, brnch_side_t branch_side)
{
    SkipSlashRN (base_file);
    char symbol = '\0';
    fscanf (base_file, "%c", &symbol);
    printf ("start symbol = <%c>\n", symbol);

    if (symbol == '{')
    {
        fscanf (base_file, "\"%[^\"]\"", akntr->text);
        printf ("text = <%s>\n", akntr->text);

        if (branch_side == LEFT)
        {
            NewNode (akntr->text, crnt_node, branch_side, akntr);
            printf ("New node = <%p>\n", crnt_node);
            crnt_node = crnt_node->left;
        }
        if (branch_side == RIGHT)
        {
            NewNode (akntr->text, crnt_node, branch_side, akntr);
            printf ("New node = <%p>\n", crnt_node);
            crnt_node = crnt_node->right;
        }

        SkipSlashRN (base_file);

        fscanf (base_file, "%c", &symbol);
        printf ("end symbol = <%c>\n", symbol);


        if (symbol == '}')
        {
            printf ("return\n");
            return;
        }
        else if (symbol == '{')
        {
            ungetc (symbol, base_file);
            /*......LEFT......*/
            RunAkinatorBase (akntr, base_file, crnt_node, LEFT);
            /*......RIGHT.....*/
            RunAkinatorBase (akntr, base_file, crnt_node, RIGHT);
        }
        else
        {
            printf ("ERROR: unknown symbol \" not a { or }\"\n");
        }
    }
    if (symbol == '}')
    {
        printf ("return\n");
        return;
    }
}

void SkipSlashRN (FILE* base_file)
{
    while (1)
    {
        int ch = fgetc (base_file);
        if (ch == '{' || ch == '}')
        {
            ungetc (ch, base_file);
            break;
        }
    }
}
