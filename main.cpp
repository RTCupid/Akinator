#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"
#include "AkinatorBase.h"

int main ()
{
    printf ("#Start Akinator!\n\n");

    tree_t akntr = {};
    AkinatorCtor (&akntr);

    MakeAkinatorBase (&akntr, "AkinatorBase.txt");

    printf ("Выберите режим игры:\n");
    printf ("[отгадать персонажа] [получить определение] [сравнить персонажей] [показать дерево]\n");
    printf ("Enter: [q]                     [d]                    [c]                 [t]      \n");

    while (1)
    {
        char action = 0;
        scanf (" %c", &action);

        if (action == 'q')
        {
            AkinatorGuessPerson (&akntr);
        }
        else if (action == 'd')
        {
            char name_person[SIZE_TEXT] = {};
            printf ("Enter name of person:\n");
            scanf (" %s", name_person);

            int* definition = (int*) calloc (akntr.deep, sizeof (*definition));

            if (AkinatorFindDefinition (&akntr, name_person, akntr.root, 0, definition))
            {
                printf ("Person is found\n");
                printf ("%s ", name_person);
                PrintDef (definition, 0);
            }
            else
            {
                printf ("The Person is not in the database\n");
            }
            free (definition);
            definition = NULL;
        }
        else if (action == 'c')
        {
        }
        else if (action == 't')
        {
            printf ("Посмотрите дерево\n\n");
            AkinatorGraphviz (&akntr);
        }
        else if (action == 'e')
        {
            AskSaveOrNot (&akntr, "AkinatorBase.txt");
            break;
        }
        else
        {
            printf ("ERROR: неизвестное действие\n");
            break;
        }

        printf ("Выберите действие:\n");
        printf ("[отгадать персонажа] [получить определение] [сравнить персонажей] [показать дерево] [выйти]\n");
        printf ("Enter: [q]                     [d]                    [c]                 [t]         [e]  \n");
    }

    AkinatorDtor (&akntr);
    printf ("\n#End of programm\n");
    return 0;
}


/*NewNode
    ( "Полторашка"
    , NewNode
        ( "Ведёт дискру"
            , NewNode("Бурцев")
            , NewNode("Колдунов")
        )
    , NewNode("Чубаров")
    );
*/
