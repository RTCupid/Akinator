#ifndef AKINATORBASE_H
    #define AKINATORBASE_H

    errTr_t MakeAkinatorBase (tree_t* akntr, const char* namefile);

    void RunAkinatorBase (tree_t* akntr, FILE* base_file, node_t* crnt_node, brnch_side_t branch_side);

    void NewNodeInBranch (tree_t* akntr, node_t* crnt_node, brnch_side_t branch_side);

    void SkipSlashRN (FILE* base_file);
#endif
