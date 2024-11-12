#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "Akinator.h"
#include "AkinatorBase.h"

errTr_t MakeAkinatorBase (tree_t* akntr, const char* namefile)
{
    InputAkinatorBase (akntr, namefile);

    RunAkinatorBase (akntr);

    return TREE_OK;
}

errTr_t InputAkinatorBase (tree_t* akntr, const char* namefile)
{
//bool InputOnegin (char** Onegin, size_t* sizeOfFile, const char* nameFile)
    struct stat fileInf = {};

    if (!SizeFile (&fileInf, namefile))
    {
        printf ("Error SizeFile!");
        return ERROR_SIZE_FILE;
    }

    akntr->base = (char*)calloc ((size_t)fileInf.st_size + 1, sizeof(char));     // каллочу буффер, чтобы в него считать текст

    if (akntr->base == NULL)
    {
        printf ("akntr->base = NULL");
        return ERROR_CALLOC_BASE;
    }

    FILE* base_file = fopen (namefile, "rt");

    if (base_file == NULL)
    {
        printf ("File opening error\n");
        printf("errno = <%d>\n", errno);
        perror(namefile);
        return ERROR_FOPEN_BASE;
    }

    akntr->nElemBase = fread (akntr->base, sizeof (char), (size_t)fileInf.st_size, base_file); // с помощью fread читаю файл в буффер, сохраняю возвращаемое значение fread ()

    if (akntr->nElemBase == 0)
    {
        printf ("errno = <%d>\n", errno);
        perror (namefile);
        return ERROR_FREAD_RETURN_ZERO;
    }

    fprintf (akntr->log_file, "\nBase:\n%s\n\n\n", akntr->base);
    printf ("\nBase:\n%s\n\n\n", akntr->base);

    fclose (base_file);                                                  // закрываю файл

    //DBG printf ("sizeOfFile = <%d>\n\n", nElemBase);
    return TREE_OK;
}

errTr_t RunAkinatorBase (tree_t* akntr)
{
    for (size_t i = 0; i < akntr->nElemBase; i++)
    {
        if (akntr->base[i] = '{')
        {
        }
    }

    return TREE_OK;
}

bool SizeFile (struct stat* fileInf, const char* nameFile)
{
    int err = stat (nameFile, fileInf);
    if (err != 0)
        {
        printf("Stat err %d\n", err);
        return 0;
        }

    printf ("\n%lu\n", (size_t)(*fileInf).st_size);
    //printf ("count of char = %lu\n", (*fileInf).st_size / sizeof (char));
    return 1;
}
