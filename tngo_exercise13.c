/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 13
 Topic: Binary Tree
 FileName: tngo_exercise13.c
 Date: Jun 4, 2017
 Objective:
 Comments:
 
 **********************************************/
/*
 This assignment deals with binary tree implementation. 
 Read the input values from the input file and implement a binary tree. 
 Create a tree node and add to the tree as you read input from the file. 
 Travers the binary tree in pre-order, post-order and in-order both recursive and non-recursive implementations.  
 Print output after each traversals, prompt the user to delete an element until the user quits. 
 Please do not create an array to delete tree nodes. Print the binary tree output after deletion.
 
 Hint: non-recursive implementations need the use of stack. 
 As you visit the node, you need to stack the node in the required orded for traversal.
 
 Implement both recursive and non-recursive methods.
 references:
 https://www.cs.usfca.edu/~galles/visualization/BST.html
 http://www.algolist.net/Data_structures/Binary_search_tree/Removal
 http://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 http://algorithms.tutorialhorizon.com/inorder-traversal-non-recursive-approach/
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MAXSTACK 200
#define EMPTYSTACK -1
typedef enum {false, true} bool;
FILE *fp1;
FILE *fp2;

typedef struct nodetype {
    int val;
    struct nodetype* left;
    struct nodetype* right;
} NODE;
typedef NODE * NODEPTR;

typedef struct stack {
    int top;
    NODE stackelement[MAXSTACK];
} TREESTACK;
typedef TREESTACK* TREESTACKPTR;

NODE pop(TREESTACK *ts);
void push(TREESTACKPTR ts, NODEPTR n);
NODE peek(TREESTACK *ts);
void resetStackEval(TREESTACK *ts);
int isEmpty(TREESTACK *ts);


void insert (NODE ** tree, NODE * item);
void printout (NODE * tree);
NODEPTR maketree(int);
void intrav(NODEPTR);
void pretrav(NODEPTR);
void posttrav(NODEPTR);

void intrav_stack(NODEPTR);
void pretrav_stack(NODEPTR);
void posttrav_stack(NODEPTR);


NODEPTR get_treenode();
void setbintree(NODEPTR, int);
NODEPTR deleteNode(NODEPTR, int);
NODEPTR minValueNode(NODEPTR);
NODEPTR findNodeIntree(NODEPTR, int key);
NODEPTR buildTree();


//MAIN PROGRAM
int main() {
    
    const char outputFileName[] = "trngo_Btree_13_output.txt";
    fp2 = fopen(outputFileName, "w");
    NODEPTR root = NULL;
    root = buildTree();
    
    printf("\n\nIn-ordered binary tree node infor:\n");
    fprintf(fp2, "\n\nIn-ordered binary tree node infor:\n");
    intrav(root);
    // Search for nodes in Tree
    int number;
    printf("\n-1 to quit. Search for key: ");
    fprintf(fp2, "\n-1 to quit. Search for key: ");
    scanf("%d", &number);
    fprintf(fp2, "%d", number);
    while(number != -1) {
        NODEPTR newRoot = findNodeIntree(root, number);
        if (newRoot != NULL) {
            printf("Key found = %d", newRoot->val);
            fprintf(fp2, "\nKey found = %d", newRoot->val);
        } else {
            printf("Key not found!");
            fprintf(fp2, "\nKey not found!");
        }
        printf("\n-1 to quit. Search for key: ");
        fprintf(fp2, "\n-1 to quit. Search for key: ");
        scanf("%d", &number);
        fprintf(fp2, "%d", number);
    }
    
    // Delete Nodes in Tree
    printf("\n\nIn-ordered binary tree node infor:\n");
    fprintf(fp2, "\n\nIn-ordered binary tree node infor:\n");
    intrav(root);
    printf("\n\n-1 to quit. Please enter a node for deletion: ");
    fprintf(fp2, "\n\n-1 to quit. Please enter a node for deletion: ");
    scanf("%d", &number);
    fprintf(fp2, "%d", number);
    while(number != -1) {
        NODEPTR newRoot = deleteNode (root, number);
        printf("\nTree after deletion of %d: \n", number);
        fprintf(fp2, "\nTree after deletion of %d: \n", number);
        intrav(newRoot);
        printf("\n\n-1 to quit. Please enter a node for deletion: ");
        fprintf(fp2, "\n\n-1 to quit. Please enter a node for deletion: ");
        scanf("%d", &number);
        fprintf(fp2, "%d", number);
    }
    
    root = buildTree();
    printf("\n\nIn-ordered traversal using recursion\n");
    fprintf(fp2, "\n\nIn-ordered traversal using recursion\n");
    intrav(root);
    printf("\n\nIn-ordered traversal using stack\n");
    fprintf(fp2, "\n\nIn-ordered traversal using stack\n");
    intrav_stack(root);
    
    root = buildTree();
    
    printf("\n\nPost-ordered traversal using recursion\n");
    fprintf(fp2, "\n\nPost-ordered traversal using recursion\n");
    posttrav(root);
    printf("\n\nPost-ordered traversal using stack\n");
    fprintf(fp2, "\n\nPost-ordered traversal using stack\n");
    posttrav_stack(root);
    
    root = buildTree();
    
    printf("\n\nPre-ordered traversal using recursion\n");
    fprintf(fp2, "\n\nPre-ordered traversal using recursion\n");
    pretrav(root);
    printf("\n\nPre-ordered traversal using stack\n");
    fprintf(fp2, "\n\nPre-ordered traversal using stack\n");
    pretrav_stack(root);

    fclose(fp2);
    return 0;
}

//build up Binary Tree
NODEPTR buildTree() {
    const char inputFileName[] = "trngo_Btree_13_input.txt";
    fp1 = fopen(inputFileName, "r");
    // read data from text file and build up the Tree
    NODEPTR root = NULL;
    char cdigit;
    char digits[4];
    int digitCounter = -1;
    int readNumberCounter = 0;
    printf("\nBuilding binary tree...");
    fprintf(fp2, "\nBuilding binary tree...");
    if (fp1 != NULL) {
        while ((cdigit = fgetc(fp1)) != EOF) {
            if (cdigit != 44) {
                digits[++digitCounter] = cdigit;
            } else {
                ++readNumberCounter;
                digitCounter = -1;
                int intValue = atoi(digits);
                if (readNumberCounter == 1) {
                    root = maketree(intValue);
                } else {
                    setbintree (root, intValue);
                }
                memset(digits, '\0', 4);
            }
        }
    }
    fclose(fp1);
    return root;
}



//Delete node
NODEPTR deleteNode(NODEPTR root, int key) {
    if (root == NULL) {
        return root;
    }
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    
    // If key is same as root's key, then this is the node
    // to be deleted
    } else {
        // node with no left child or one child
        if (root->left == NULL)
        {
            NODE *temp = root->right;
            free(root);
            return temp;
        }
        // node with no right child or one child
        else if (root->right == NULL)
        {
            NODE *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children
        else {
            // Get the inorder successor (smallest in the right subtree)
            NODE *temp = minValueNode(root->right);
            // Copy the inorder successor's content to this node
            root->val = temp->val;
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->val);
        }
    }
    return root;
}

//return node within a sub-tree with the minimum value of key found in that sub-tree
NODEPTR minValueNode(NODEPTR node)
{
    NODEPTR current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}


//in-ordered traversal using recursion
//Left->Root->Right
void intrav(NODEPTR tree) {
    if (tree != NULL) {
        intrav(tree->left);
        printf("%d ", tree->val);
        fprintf(fp2, "%d ", tree->val);
        intrav(tree->right);
    }
}

//pre-ordered traversal using recursion
//Root->Left->Right
void pretrav(NODEPTR tree) {
    if (tree != NULL) {
        printf("%d ", tree->val);
        fprintf(fp2, "%d ", tree->val);
        pretrav(tree->left);
        pretrav(tree->right);
    }
}

//post-ordered traversal using recursion
//Left->Right->Root
void posttrav(NODEPTR tree) {
    if (tree != NULL) {
        posttrav(tree->left);
        posttrav(tree->right);
        printf("%d ", tree->val);
        fprintf(fp2, "%d ", tree->val);
    }
}

NODEPTR get_treeNode() {
    NODEPTR p;
    p = (NODEPTR) malloc (sizeof (struct nodetype));
    return p;
}

NODEPTR maketree(int x) {
    NODEPTR p;
    p = get_treeNode();
    p->val = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

//Add nodes to tree
void setbintree(NODEPTR p, int x) {
    NODEPTR s = p;
    while (s != NULL) {
        if (s->val == x) {
            printf("\nduplicated entry: %d", x);
            fprintf(fp2, "\nduplicated entry: %d", x);
            return;
        }
        if (s->val > x) {
            if (s->left == NULL) {
                s->left = maketree(x);
                return;
            } else {
                s = s->left;
            }
        } else {
            if (s->right == NULL) {
                s->right = maketree(x);
                return;
            } else {
                s = s->right;
            }
        }
    } //end while
    return;
}

//Find a node in a tree
NODEPTR findNodeIntree(NODEPTR root, int key) {
    if (root == NULL || root->val == key)
        return root;
    
    // Key is greater than root's key
    if (root->val < key) {
        return findNodeIntree(root->right, key);
    } else {
        // Key is smaller than root's key
        return findNodeIntree(root->left, key);
    }
}

//in-ordered traversal using stack
//Left->Root->Right
void intrav_stack(NODEPTR root) {
    NODEPTR current = root;
    bool done = 0;
    TREESTACKPTR newStack = (TREESTACKPTR) malloc (sizeof(TREESTACK));
    newStack->top = -1;
    while (!done)
    {
        if (current != NULL) {
            push(newStack, current);
            current = current->left;
        }   else {
            if (!isEmpty(newStack))
            {
                *root = pop(newStack);
                printf("%d ", root->val);
                fprintf(fp2, "%d ", root->val);
                current = root->right;;
            }
            else {
                done = 1;
            }
        }
    }
    free(newStack);
}

//pre-ordered traversal using stack
//Root->Left->right
void pretrav_stack(NODEPTR root) {
    TREESTACKPTR newStack = (TREESTACKPTR) malloc (sizeof(TREESTACK));
    newStack->top = -1;
    while (root != NULL) {
        printf("%d ", root->val);
        fprintf(fp2, "%d ", root->val);
        if (root->right != NULL) {
            push(newStack, root->right);
        }
        if (root->left != NULL) {
            root = root->left;
        } else {
            *root = pop(newStack);
        }
    }
    free(newStack);
}

//post-ordered traversal using stack
//Left->Right->Root
void posttrav_stack(NODEPTR root) {
    TREESTACKPTR newStack1 = (TREESTACKPTR) malloc (sizeof(TREESTACK));
    TREESTACKPTR newStack2 = (TREESTACKPTR) malloc (sizeof(TREESTACK));
    newStack1->top = -1;
    newStack2->top = -1;
    NODE tempNode;
    push(newStack1, root);
    while (!isEmpty(newStack1)) {
        tempNode = pop(newStack1);
        push(newStack2, &tempNode);
        
        if (tempNode.left != NULL) {
            push(newStack1, tempNode.left);
        }
        if (tempNode.right != NULL) {
            push(newStack1, tempNode.right);
        }
    }
    while (!isEmpty(newStack2)) {
        int tempData = pop(newStack2).val;
        printf("%d ", tempData);
        fprintf(fp2, "%d ", tempData);
    }
    free(newStack1);
    free(newStack2);
}

void push(TREESTACKPTR ts, NODEPTR n) {
    ts->stackelement[++(ts->top)].val = n->val;
    ts->stackelement[(ts->top)].left = (n->left);
    ts->stackelement[(ts->top)].right = (n->right);
}

NODE pop(TREESTACK *sp) {
    if (isEmpty(sp)) {
        printf("%s", "\nStack is underflow!\n");
        fprintf(fp2, "%s", "\nStack is underflow!\n");
        exit (1);
    } else {
        NODE node = sp->stackelement[sp->top];
        sp->stackelement[(sp->top)].val = 0;
        sp->stackelement[(sp->top)].left = NULL;
        sp->stackelement[(sp->top)].right = NULL;
        (sp->top)--;
        return node;
    }
}

NODE peek(TREESTACK *sp) {
    NODE n;
    if (isEmpty(sp)) {
        fprintf(fp2, "\nStack is empty!\n");
        printf("\nStack is empty!\n");
    } else {
        n = sp->stackelement[(sp->top)];
    }
    return n;
}

void resetStackEval(TREESTACK *sp) {
    sp->top = 0;
    for (int i = 0; i < MAXSTACK; i++) {
        sp->stackelement[(sp->top)++].val = 0;
        sp->stackelement[(sp->top)++].left = NULL;
        sp->stackelement[(sp->top)++].right = NULL;
    }
    sp->top = -1;
}

int isEmpty(TREESTACK *sp) {
    if (sp->top == EMPTYSTACK) {
        return TRUE;
    } else {
        return FALSE;
    }
}
