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

    typedef struct node_t
    {
        char* text;
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
    } tree_t;

    const int SIZE_TEXT = 40;

    errTr_t AkinatorCtor (tree_t* tree);

    void AkinatorDtor (tree_t* tree);

    void AkinatorDump (tree_t* tree);

    void AkinatorGraphviz (tree_t* tree);

    void AkinatorGuessPerson (tree_t* akntr);

    void Pause ();

    void MakeDotFileDump (tree_t* tree);

    void MakeDotFileGraphviz (tree_t* tree);

   void PrintDump (tree_t tree, node_t* node, FILE* dot_file);

   void PrintGraphviz (tree_t tree, node_t* node, FILE* dot_file);

    node_t* NewNode (tree_t* akntr, const char* text, node_t* left, node_t* right);

    void ClearTree (node_t* node);

#endif
