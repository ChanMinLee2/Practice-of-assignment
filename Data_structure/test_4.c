#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    int value;
    node *lchild;
    node *rchild;
};

void init(node *root)
{
    root->value = -1;
    root->lchild = NULL;
    root->rchild = NULL;
}

int intmax(int a, int b)
{
    return (a > b) ? a : b;
}

void insert(node *root, int cval, int lval, int rval)
{
    if (root->value == -1)
    {
        root->value = cval;
        
        node* lchild_node = (node*)malloc(sizeof(node));
        node* rchild_node = (node*)malloc(sizeof(node));

        lchild_node->value = lval;
        rchild_node->value = rval;

        root->lchild = lchild_node;
        root->rchild = rchild_node;

        return;
    }
    // 1 위치 찾기
    if (root->value != cval)
    {
        insert(root->lchild,cval,lval,rval);
        insert(root->rchild,cval,lval,rval);
    }
    
    else
    {
        node* lchild_node = (node*)malloc(sizeof(node));
        node* rchild_node = (node*)malloc(sizeof(node));

        lchild_node->value = lval;
        rchild_node->value = rval;
        
        lchild_node->lchild = NULL;
        lchild_node->rchild = NULL;
        rchild_node->lchild = NULL;
        rchild_node->rchild = NULL;
        return;
    }
    
}

int valid(node *root, int cval, int lval, int rval)
{
    if (root->value == cval && root -> lchild == NULL)
    {
        return 1; // valid by rule 2
    }

    else if (root->lchild->value == lval || root->rchild->value == rval)
    {
        return 0; // not valid by rule 3
    }

    // 이 트리에서 모든 노드는 child를 가진다면 항상 두 개를 가진다. -> 단일 차일드 x
    if (root->lchild != NULL && root->rchild != NULL)
    {
        int v1 = valid(root->lchild, cval, lval, rval);
        int v2 = valid(root->rchild, cval, lval, rval);

        return (v1>v2) ? v1 : v2;
    }
}

void inorder_print(node* root)
{
    if (root != NULL)
    {
        inorder_print(root->lchild);
        printf("%d\n", root->value);
        inorder_print(root->rchild);
    }
}

int height(node *root )
{
    if (root == NULL)
    {
        printf("현재 트리는 비어있습니다.");
    }
    
    int r = 0, l = 0;
    if (root->rchild != NULL)
        r = height(root->rchild);  
    if (root->lchild != NULL)
        l = height(root->lchild);   

    return 1 + intmax(r, l); // root의 깊이는 1, 그 이후로 세기.
}

int width(node *root, int (*height)(node *root))
{
    int max_height_left = height(root->lchild);
    int max_height_right = height(root->rchild);
    
    return (max_height_left - 1) + (max_height_right - 1);
}

int search(node* root, int sval)
{
    if (root -> value == sval)
    {
        return 1;
    }
    
    if (root->lchild != NULL && root->rchild != NULL)
    {
        int s1 = search(root->lchild, sval);
        int s2 = search(root->rchild, sval);
        return (s1>s2) ? s1 : s2;
    }

    else if (root->lchild == NULL && root->rchild == NULL)
    {
        return 0;
    }
    
}

int is_leaf_node(node *root, int x)
{

    if (root != NULL)
    {
        if (root->value == x && root->lchild == NULL)
        {
            return 1;
        }
        
        else if (root->lchild != NULL && root->rchild != NULL)
        {
            is_leaf_node(root->lchild, x);
            is_leaf_node(root->rchild, x);
        }
    }
    
}

int main(void)
{
    int i;
    int cval, lval, rval;
    char str[128];

    FILE *fp = fopen("tree.txt", "r+t");
    printf("good open\n");
    node *root = (node*)malloc(sizeof(node));
    printf("good node alloc\n");

    while(fgets(str, 128, fp) != NULL)
    {
        printf("good loop start\n");
        sscanf(str, "%d %d %d", &cval, &lval, &rval);
        printf("good sscanf : %d %d %d\n", cval, lval, rval);
        if(!valid(root, cval, lval, rval))
        {
            printf("Invalid: %d %d %d\n", cval, lval, rval);
            printf("good valid check\n");
            continue;
        }
        insert(root, cval, lval, rval);
        printf("good insert\n");
    }
    fclose(fp);

    inorder_print(root);
    printf("\n");

    printf("Height : %d\n", height(root));
    printf("width  : %d\n", width(root,height));

    system("Pause");
    return 0;
}