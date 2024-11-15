#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include"Akinator.h"
#include "AkinatorBase.h"

void AkinatorFindDefinition (tree_t* akntr, const char* text)
{

}

void AkinatorGuessPerson (tree_t* akntr)
{
    char answ = '\0';

    while (1)
    {
        if (!akntr->crnt_node->left)
        {
            break;
        }
        printf ("Ваш персонаж %s?\n", akntr->crnt_node->text);
        printf ("Да\\Нет [y\\n]\n");
        scanf (" %c", &answ);

        if (answ == 'y')
        {
            akntr->crnt_node = akntr->crnt_node->left;
        }
        if (answ == 'n')
        {
            akntr->crnt_node = akntr->crnt_node->right;
        }
    }

    printf ("Вы загадали %s?\n", akntr->crnt_node->text);
    printf ("Да\\Нет [y\\n]\n");
    scanf (" %c", &answ);
    if (answ == 'y')
    {
        printf ("Это было легко!\n\n");
        akntr->crnt_node = akntr->root;
    }
    else if (answ == 'n')
    {
        printf ("Не может быть, кто это был?\n");
        char new_node[SIZE_TEXT] = {};
        scanf (" %s", new_node);

        fprintf (akntr->dbg_log_file, "\nakntr->crnt_node->next = %s\n", akntr->crnt_node->text);
        fprintf (akntr->dbg_log_file, "new_node = %s\n", new_node);

        fprintf (akntr->dbg_log_file, "old_node = %s\n", akntr->crnt_node->text);

        akntr->crnt_node->right = NewNode (akntr, akntr->crnt_node->text, NULL, NULL);
        akntr->crnt_node->left  = NewNode (akntr, strdup(new_node), NULL, NULL);

        printf ("Чем %s отличается от %s\n", new_node, akntr->crnt_node->text);

        scanf (" %s", new_node);
        akntr->crnt_node->text = strdup(new_node);

        akntr->deep = FindDeepTree (akntr, akntr->root, 1);

        fprintf (akntr->dbg_log_file, "deep of tree = <%lu>\n", akntr->deep);
        fprintf (akntr->dbg_log_file, "new_question = %s\n", akntr->crnt_node->text);
    }

}

void AkinatorGraphviz (tree_t* akntr)
{
    akntr->log_file = fopen ("log_file.htm", "wt");
    VerifyOpenFile (akntr->log_file, "AkinatorGraphviz");

    fprintf (akntr->log_file, "<FONT SIZE=\"6\"><center>My Akinator:</center><FONT SIZE=\"5\">\n\n");

    MakeDotFileGraphviz (akntr);

    system ("dot -Tpng DumpAkinator.dot -o Akinator.png");

    fprintf (akntr->log_file, "<center><img src = Akinator.png ></center>\n\n");

    fclose (akntr->log_file);
}

void MakeDotFileGraphviz (tree_t* akntr)
{
    FILE* dot_file = fopen ("DumpAkinator.dot", "wt");
    VerifyOpenFile (dot_file, "MakeDotFileGraphviz");

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

