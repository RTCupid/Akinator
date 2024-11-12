#ifndef AKINATORBASE_H
    #define AKINATORBASE_H

    errTr_t MakeAkinatorBase (tree_t* akntr, const char* namefile);

    errTr_t InputAkinatorBase (tree_t* akntr, const char* namefile);

    errTr_t RunAkinatorBase (tree_t* akntr);

    bool SizeFile (struct stat* fileInf, const char* nameFile);


#endif
