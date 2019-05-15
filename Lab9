#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int key;
    unsigned char height;
    struct node* left;
    struct node* right;
};

int height(struct node* p) {
    return p?p->height:0;
}

int bfactor(struct node* p) {
    return height(p->right)-height(p->left);
}

void fixheight(struct node* p) {
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

struct node* rotateright(struct node* p) {
    struct node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

struct node* rotateleft(struct node* q) {
    struct node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

struct node* balance(struct node* p) {
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

struct node* insert(struct node* p, int k) {
    if (!p) {
        p = malloc(sizeof(struct node));
        p->height = 1;
        p->key = k;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    if (k < p->key) {
        p->left = insert(p->left, k);
    }
    else {
        p->right = insert(p->right, k);
    }
    return balance(p);
}

struct node* findmin(struct node* p) {
    return p->left?findmin(p->left):p;
}

struct node* removemin(struct node* p) {
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

void tfree(struct node *p) {
    if (p == NULL)
        return;
    tfree(p -> left);
    tfree(p -> right);
    free(p);
}

int main() {
    struct node *tree = NULL;
    int N = 0, k = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &k);
        tree = insert(tree, k);
    }
    printf("%d", height(tree));
    tfree(tree);
    return 0;
}
