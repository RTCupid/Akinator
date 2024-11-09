#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"

#define PS if(0)

void AkinatorDump (tree_t* tree)
{
    tree->log_file = fopen ("log_file.htm", "wt");

    fprintf (tree->log_file, "<FONT SIZE=\"6\"><center>My Akinator:</center><FONT SIZE=\"5\">\n\n");

    MakeDotFile (tree);

    system ("dot -Tpng DumpAkinator.dot -o Akinator.png");

    fprintf (tree->log_file, "<center><img src = Akinator.png ></center>\n\n");

    fclose (tree->log_file);

    PS Pause ();
}

void MakeDotFile (tree_t* tree)
{
    FILE* dot_file = fopen ("DumpAkinator.dot", "wt");

    fprintf (dot_file, "digraph G {\n");
    fprintf (dot_file, "\trankdir = HR;\n");
    fprintf (dot_file, "\tbgcolor=\"#F7F9FB\"\n");

    Print (*tree, tree->root, dot_file);

    fprintf (dot_file, "}\n");
    fclose (dot_file);
}

void Print (tree_t tree, node_t* node, FILE* dot_file)
{
    if (!node)
    {
        return;
    }

    if (node == tree.crnt_node)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#687864\"; "
            "label =  \"{node: %p | text: %s | prnt: %p | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, node->text, node->prnt, node->left, node->right);
    }
    else
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#8FC1E3\"; "
            "label =  \"{node: %p | text: %s | prnt: %p | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, node->text, node->prnt, node->left, node->right);
    }

    if (node->left)
    {
        fprintf (dot_file, "\t node%p:<left> -> node%p [style=bold; weight=1000; ];\n", node, node->left);
    }
    if (node->right)
    {
        fprintf (dot_file, "\t node%p:<right> -> node%p [style=bold; weight=1000; ];\n", node, node->right);
    }

    /*......LEFT......*/
    Print (tree, node->left, dot_file);

    /*......RIGHT......*/
    Print (tree, node->right, dot_file);
}

void Pause ()
{
    printf ("Enter to continue...\n");
    getchar ();
}
