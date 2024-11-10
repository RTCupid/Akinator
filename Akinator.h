#ifndef AKINATOR_H
    #define AKINATOR_H

    enum errTr_t
    {
        TREE_OK = 0,
        ERROR_CTOR_TREE,


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
    } tree_t;

    const int SIZE_TEXT = 30;

    errTr_t AkinatorCtor (tree_t* tree);

    void AkinatorDtor (tree_t* tree);

    void AkinatorDump (tree_t* tree);

    void AkinatorGraphviz (tree_t* tree);

    void Pause ();

    void MakeDotFileDump (tree_t* tree);

    void MakeDotFileGraphviz (tree_t* tree);

   void PrintDump (tree_t tree, node_t* node, FILE* dot_file);

   void PrintGraphviz (tree_t tree, node_t* node, FILE* dot_file);

    errTr_t NewNode (const char* text, node_t* parrent, brnch_side_t branch_side);

    void ClearTree (node_t* node);

#endif
