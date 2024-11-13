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

    akntr->root = RunAkinatorBase (akntr, base_file);

    fclose (base_file);
    return TREE_OK;
}

node_t* RunAkinatorBase (tree_t* akntr, FILE* base_file)
{
    SkipSlashRN (base_file);
    char symbol = '\0';
    fscanf (base_file, " %c", &symbol);
    printf ("start symbol = <%c>\n", symbol);

    if (symbol == '{')
    {
        fscanf (base_file, "\"%[^\"]\"", akntr->text);
        printf ("text = <%s>\n", akntr->text);

        node_t* node = NewNode (akntr->text, NULL, NULL);

        SkipSlashRN (base_file);

        fscanf (base_file, "%c", &symbol);
        printf ("end symbol = <%c>\n", symbol);

        if (symbol == '}')
        {
            printf ("return\n");
            return node;
        }
        else if (symbol == '{')
        {
            ungetc (symbol, base_file);
            /*......LEFT......*/
            node->left  = RunAkinatorBase (akntr, base_file);
            /*......RIGHT.....*/
            node->right = RunAkinatorBase (akntr, base_file);
        }
        else
        {
            printf ("ERROR: unknown symbol \" not a { or }\"\n");
        }
        return node;
    }
    printf ("ERROR: uncorrect file of base\n");
    return NULL;
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
