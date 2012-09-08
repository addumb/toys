#include <stdlib.h>
#include <stdio.h>

struct tree {
    int value;
    struct tree* left;
    struct tree* right;
};
typedef struct tree tree;

tree* newnode(int value) {
    tree* node = (tree*)malloc(sizeof(tree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

insert(tree* root, int insval) {
    /*
    insert a new node with value insval into tree root

    at each node,
    if insval is less than val, insert it to the left
    if insval is greater than val, insert it to the right
    if left or right are NULL, make a new node to the left or right
    */
    if (insval < root->value) {
        //if root->left is NULL, make it a new node with insval
        if (root->left)
            insert(root->left, insval);
        else
            root->left = newnode(insval);
    } else { //this includes the equal case, HEADS UP
        if (root->right)
            insert(root->right, insval);
        else
            root->right = newnode(insval);
    }
}

printTree(tree* root) {
    if (root) {
        printTree(root->left);
        printf(" %d ", root->value);
        printTree(root->right);
    }
}

main() {
    tree* root = (tree*)malloc(sizeof(tree));

    insert(root, 5);
    insert(root, 1);
    insert(root, 2);
    insert(root, 0);
    insert(root, 6);
    insert(root, 100);
    insert(root, 50);
    printTree(root);

}
