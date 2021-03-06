#include <stdio.h>
#include <stdlib.h>

typedef struct binTree
{
    int value;
    struct binTree *left;
    struct binTree *right;
} binTree;

binTree* createBinTree (int cur)
{
    binTree *temp = (binTree*)malloc(sizeof(binTree));
    if (temp == NULL)
    {
        printf("Malloc failed in createBinTree\n");
        return NULL;
    }
    temp->left = NULL;
    temp->right = NULL;
    temp->value = cur;
    return temp;
}

binTree* addElement(binTree *root, int cur)
{
    if (root == NULL)
    {
        return createBinTree(cur);
    }
    else if (root->value > cur)
    {
        root->left = addElement(root->left, cur);
    }
    else if (root->value < cur)
    {
        root->right = addElement(root->right, cur);
    }
    return root;
}

int hasElement(binTree *root, int cur)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->value < cur)
    {
        isElement(root->right, cur);
    }
    else if (root->value > cur)
    {
        isElement(root->left, cur);
    }
    else if (root->value == cur)
    {
        return 1;
    }
}

binTree* removeElement(binTree* root, int cur)
{
    if (root == NULL)
    {
        printf("This element is not in the tree\n");
        return NULL;
    }
    if (root->value < cur)
    {
        root->right = removeElement(root->right, cur);
    }
    else if (root->value > cur)
    {
        root->left = removeElement(root->left, cur);
    }
    else if (root->value == cur)
    {
        if (root->right && root->left)
        {
            binTree *rootMin = root->right;
            while (rootMin->left)
            {
                rootMin = rootMin->left;
            }
            root->value = rootMin->value;
            root->right = removeElement(root->right, rootMin->value);
            return root;
        }
        else if (root->right)
        {
            binTree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->left)
        {
            binTree *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            free(root);
            return NULL;
        }
    }
    return root;
}

void printDown(binTree *root)
{
    if (root == NULL)
    {
        return;
    }
    printDown(root->right);
    printf("%d ", root->value);
    printDown(root->left);
    return;
}

void printUp(binTree *root)
{
    if (root == NULL)
    {
        return;
    }
    printUp(root->left);
    printf("%d ", root->value);
    printUp(root->right);
    return;
}

void printParenthesis(binTree *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("( %d ", root->value);
    if(root->right)
    {
        printParenthesis(root->right);
    }
    else
    {
        printf(" null ");
    }
    printf(" ");
    if(root->left)
    {
        printParenthesis(root->left);
        printf(" ) ");
    }
    else
    {
        printf(" null) ");
    }
    return;
}

void clearTree(binTree *root)
{
    if (root == NULL)
    {
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    free(root);
    return;
}


int main()
{
    binTree* root = NULL;
    int i = 0;
    while(i == 0)
    {
        char c;
        int cur;
        scanf("%c", &c);
        switch (c)
        {
            case 'a':
                scanf("%d", &cur);
                root = addElement(root, cur);
            break;
            case 'r':
                scanf("%d", &cur);
                root = removeElement(root, cur);
            break;
            case 'i':
                scanf("%d", &cur);
                if(hasElement(root, cur) == 0)
                {
                        printf("Element doesn't belong to tree\n");
                }
                else
                {
                        printf("Element belongs to tree\n");
                }
            break;
            case 'p':
                printParenthesis(root);
                printf("\n");
            break;
             case 'u':
                printUp(root);
                printf("\n");
            break;
             case 'd':
                printDown(root);
                printf("\n");
            break;
            case 'c':
                clearTree(root);
                i = 1;
            break;
        }
    }
    return 0;
}
