#include <stdio.h>
#include <stdlib.h>

#include"Akinator.h"
#include "AkinatorBase.h"

void AkinatorGraphviz (tree_t* akntr)
{
    fprintf (akntr->log_file, "<FONT SIZE=\"6\"><center>My Akinator:</center><FONT SIZE=\"5\">\n\n");

    MakeDotFileGraphviz (akntr);

    system ("dot -Tpng DumpAkinator.dot -o Akinator.png");

    fprintf (akntr->log_file, "<center><img src = Akinator.png ></center>\n\n");
}

void MakeDotFileGraphviz (tree_t* akntr)
{
    FILE* dot_file = fopen ("DumpAkinator.dot", "wt");

    fprintf (dot_file, "digraph G {\n");
    fprintf (dot_file, "\trankdir = HR;\n");
    fprintf (dot_file, "\tbgcolor=\"#F7F9FB\"\n");

    PrintGraphviz (*akntr, akntr->root, dot_file);

    fprintf (dot_file, "}\n");
    fclose (dot_file);
}

void PrintGraphviz (tree_t akntr, node_t* node, FILE* dot_file)
{
    if (!node)
    {
        return;
    }

    if (node == akntr.root)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#687864\"; label =  \"%s? \" ];\n", node, node->text);
    }
    else if (node->left && node->right)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#5085A5\"; label =  \"%s? \" ];\n", node, node->text);
    }
    else
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#8FC1E3\"; label =  \"%s \" ];\n", node, node->text);
    }

    if (node->left)
    {
        fprintf (dot_file, "\t node%p -> node%p [label=\"Да\"; style=bold; weight=1000; ];\n", node, node->left);
    }
    if (node->right)
    {
        fprintf (dot_file, "\t node%p -> node%p [label=\"Нет\"; style=bold; weight=1000; ];\n", node, node->right);
    }

    /*......LEFT......*/
    PrintGraphviz (akntr, node->left, dot_file);

    /*......RIGHT......*/
    PrintGraphviz (akntr, node->right, dot_file);
}
