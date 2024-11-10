#include <stdio.h>
#include <stdlib.h>

#include"Akinator.h"

void AkinatorGraphviz (tree_t* tree)
{
    tree->log_file = fopen ("log_file.htm", "wt");

    fprintf (tree->log_file, "<FONT SIZE=\"6\"><center>My Akinator:</center><FONT SIZE=\"5\">\n\n");

    MakeDotFileGraphviz (tree);

    system ("dot -Tpng DumpAkinator.dot -o Akinator.png");

    fprintf (tree->log_file, "<center><img src = Akinator.png ></center>\n\n");

    fclose (tree->log_file);
}

void MakeDotFileGraphviz (tree_t* tree)
{
    FILE* dot_file = fopen ("DumpAkinator.dot", "wt");

    fprintf (dot_file, "digraph G {\n");
    fprintf (dot_file, "\trankdir = HR;\n");
    fprintf (dot_file, "\tbgcolor=\"#F7F9FB\"\n");

    PrintGraphviz (*tree, tree->root, dot_file);

    fprintf (dot_file, "}\n");
    fclose (dot_file);
}

void PrintGraphviz (tree_t tree, node_t* node, FILE* dot_file)
{
    if (!node)
    {
        return;
    }

    if (node == tree.root)
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
    PrintGraphviz (tree, node->left, dot_file);

    /*......RIGHT......*/
    PrintGraphviz (tree, node->right, dot_file);
}
