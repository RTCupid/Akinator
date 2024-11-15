#ifndef AKINATORBASE_H
    #define AKINATORBASE_H

    errTr_t MakeAkinatorBase (tree_t* akntr, const char* namefile);

    node_t* RunAkinatorBase (tree_t* akntr, FILE* base_file);

    void NewNodeInBranch (tree_t* akntr, node_t* crnt_node, brnch_side_t branch_side);
#endif
