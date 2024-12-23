#ifndef AKINATOR_H
    #define AKINATOR_H

    #define PS if(1)

    enum errTr_t
    {
        TREE_OK = 0,
        ERROR_CTOR_TREE,
        ERROR_SIZE_FILE,
        ERROR_CALLOC_BASE,
        ERROR_FOPEN_BASE,
        ERROR_FREAD_RETURN_ZERO,
    };

    enum brnch_side_t
    {
        RIGHT = 0,
        LEFT  = 1,
    };

    enum action_t
    {
        QUESS = (int)'q',
        DEFINITION = (int)'d',
        COMPARE = (int)'c',
        TREE = (int)'t',
        EXIT = (int)'e',
    };

    typedef struct node_t
    {
        const char* text;
        node_t* left;
        node_t* right;
        node_t* prnt;
    } node_t;

    typedef struct
    {
        node_t* root;
        node_t* crnt_node;
        FILE* log_file;
        FILE* dbg_log_file;
        char* base;
        size_t nElemBase;
        char* text;
        size_t deep;
    } tree_t;

    const int SIZE_TEXT = 50;

    errTr_t AkinatorCtor (tree_t* tree);

    void VerifyOpenFile (FILE* file, const char* namefunc);

    size_t FindDeepTree (tree_t* akntr, node_t* root, size_t deep);

    void AkinatorDtor (tree_t* tree);

    void AkinatorDump (tree_t* tree);

    void AkinatorGraphviz (tree_t* tree);

    void AkinatorGuessPerson (tree_t* akntr);

    void RunCompare (tree_t* akntr);

    void PrintCompareDef (char name_first_person[SIZE_TEXT], char name_second_person[SIZE_TEXT], int* first_definition, int* second_definition, tree_t* akntr, node_t* crnt_node, int crnt_deep);

    void RunDefinition (tree_t* akntr);

    bool AkinatorFindDefinition (tree_t* akntr, const char* text, node_t* crnt_node, size_t crnt_deep, int* definition);

    void PrintDef (int* definition, int crnt_deep, node_t* crnt_node);

    void AskSaveOrNot (tree_t* akntr, const char* namefile);

    void WriteBase (node_t* crnt_node, FILE* base_file, int level);

    void WriteTab (int level, FILE* file);

    void Pause ();

    void MakeDotFileDump (tree_t* tree);

    void MakeDotFileGraphviz (tree_t* tree);

   void PrintDump (tree_t tree, node_t* node, FILE* dot_file);

   void PrintGraphviz (tree_t tree, node_t* node, FILE* dot_file);

    node_t* NewNode (tree_t* akntr, const char* text, node_t* left, node_t* right);

    void ClearTree (node_t* node);

#endif
