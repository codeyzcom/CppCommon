//
// Created by user on 1/11/21.
//

#ifndef CPPREPO_TREE_H
#define CPPREPO_TREE_H


struct node {
    int key_value;
    node *left;
    node *right;
};

class btree {
public:
    btree();
    ~btree();

    void insert(int key);
    node *search(int key);
    void destroy_tree();

private:
    void destroy_tree(node *leaf);
    void insert(int key, node *leaf);
    node *search(int key, node *leaf);

    node *root;
};


#endif //CPPREPO_TREE_H
