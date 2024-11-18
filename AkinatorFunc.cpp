#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include"Akinator.h"
#include "AkinatorBase.h"

void RunCompare (tree_t* akntr)
{
    char name_first_person[SIZE_TEXT] = {};
    printf ("Enter name of first person:\n");
    scanf (" %s", name_first_person);
    char name_second_person[SIZE_TEXT] = {};
    printf ("Enter name of second person:\n");
    scanf (" %s", name_second_person);

    int* first_definition  = (int*) calloc (akntr->deep, sizeof (*first_definition));
    int* second_definition = (int*) calloc (akntr->deep, sizeof (*second_definition));

    if (!AkinatorFindDefinition (akntr, name_first_person, akntr->root, 0, first_definition))
    {
        printf ("The first Person is not in the database\n");
    }
    if (!AkinatorFindDefinition (akntr, name_second_person, akntr->root, 0, second_definition))
    {
        printf ("The second Person is not in the database\n");
    }

    PrintCompareDef (name_first_person, name_second_person, first_definition, second_definition, akntr);

    free (first_definition);
    first_definition = NULL;
    free (second_definition);
    second_definition = NULL;
}

void PrintCompareDef (char name_first_person[SIZE_TEXT], char name_second_person[SIZE_TEXT], int* first_definition, int* second_definition, tree_t* akntr)
{
    int i = 0;
    if (first_definition[i] == second_definition[i])
        printf ("%s похож на %s тем, что они: \n", name_first_person, name_second_person);

    while (first_definition[i] == second_definition[i])
    {
        printf ("%s", akntr->crnt_node->text);
        i++;
        if (
    }
}

void RunDefinition (tree_t* akntr)
{
    char name_person[SIZE_TEXT] = {};
    printf ("Enter name of person:\n");
    scanf (" %s", name_person);

    int* definition = (int*) calloc (akntr->deep, sizeof (*definition));

    if (AkinatorFindDefinition (akntr, name_person, akntr->root, 0, definition))
    {
        printf ("Person is found\n");
        printf ("%s - ", name_person);
        PrintDef (definition, 0, akntr->root);
        printf ("\n");
    }
    else
    {
        printf ("The Person is not in the database\n");
    }
    free (definition);
    definition = NULL;
}

bool AkinatorFindDefinition (tree_t* akntr, const char* text, node_t* crnt_node, size_t crnt_deep, int* definition)
{
    if (!crnt_node->left)
    {
        if (strcmp (crnt_node->text, text) == 0)
            return true;
        else
            return false;
    }

    if (AkinatorFindDefinition (akntr, text, crnt_node->left, crnt_deep + 1, definition))
    {
        definition[crnt_deep] = 1;
        return true;
    }

    if (AkinatorFindDefinition (akntr, text, crnt_node->right, crnt_deep + 1, definition))
    {
        definition[crnt_deep] = 0;
        return true;
    }
    return false;
}

void PrintDef (int* definition, size_t crnt_deep, node_t* crnt_node)
{
    if (!crnt_node->left)
        return;
    if (definition[crnt_deep])
    {
        printf ("%s ", crnt_node->text);
        PrintDef (definition, crnt_deep + 1, crnt_node->left);
    }
    else
    {
        printf ("Не %s ", crnt_node->text);
        PrintDef (definition, crnt_deep + 1, crnt_node->right);
    }
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
        printf ("Это было легко!\n");
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

        printf ("Больше не проведёшь!\n");
        akntr->crnt_node = akntr->root;
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

