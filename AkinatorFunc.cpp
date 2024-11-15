#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include"Akinator.h"
#include "AkinatorBase.h"

void AkinatorGuessPerson (tree_t* akntr)
{
    char answ = '\0';

    if (akntr->crnt_node->left)
    {
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
        AkinatorGuessPerson (akntr);
    }
    else
    {
        printf ("Вы загадали %s?\n", akntr->crnt_node->text);
        printf ("Да\\Нет [y\\n]\n");
        scanf (" %c", &answ);
        if (answ == 'y')
        {
            printf ("Это было легко!\n");
            akntr->crnt_node = akntr->root;
        }
        else if (answ == 'n')
        {
            printf ("Не может быть, кто это был?\n");
            char new_node[SIZE_TEXT] = {};
            scanf (" %s", new_node);
            printf ("Чем %s отличается от %s\n", new_node, akntr->crnt_node->text);
            char new_question[SIZE_TEXT] = {};
            scanf (" %s", new_question);

            char old_node[SIZE_TEXT] = {};
            ArrayText (old_node, akntr->crnt_node->text);

            akntr->crnt_node = NewNode (akntr, new_question, NULL, NULL);
            akntr->crnt_node->left  = NewNode (akntr, new_node, NULL, NULL);
            akntr->crnt_node->right = NewNode (akntr, old_node, NULL, NULL);
        }
    }
}

void ArrayText (char old_node[SIZE_TEXT], char* text)
{
    for (int i = 0; i < SIZE_TEXT; i++)
    {
        assert (i < SIZE_TEXT);
        old_node[i] = text[i];
    }
}

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
