#include <stdio.h>

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
            break;
        }
        else
        {
            printf ("ERROR: неизвестное действие\n");
        }

        printf ("Выберите действие:\n");
        printf ("[отгадать персонажа] [получить определение] [сравнить персонажей] [показать дерево] [выйти]\n");
        printf ("Enter: [q]                     [d]                    [c]                 [t]         [e]  \n");
    }

    AkinatorGraphviz (&akntr);

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
