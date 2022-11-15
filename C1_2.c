#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int coef; //系数
    int exp;  //指数
    struct node *next;
} node, *pStack;

void input(pStack poly1, pStack poly2)//调用输入函数
{
    int coef, exp;
    char ch;
    int stackSize = 0;
    while (scanf("%d", &coef))//系数
    {
        scanf("%d", &exp);//指数
        if (stackSize >= 5)//长度限制为5
        {
            printf("Full!");
            exit(0);
        }
        node *newItem = (node *)malloc(sizeof(node));
        (*newItem).coef = coef;
        (*newItem).exp = exp;
        (*newItem).next = (*poly1).next;
        (*poly1).next = newItem;
        stackSize++;
    }
    scanf("%c", &ch);
    stackSize = 0;
    while (scanf("%d", &coef) != EOF)
    {
        scanf("%d", &exp);
        if (stackSize >= 5)
        {
            printf("Full!");
            exit(0);
        }
        node *newItem = (node *)malloc(sizeof(node));
        (*newItem).coef = coef;
        (*newItem).exp = exp;
        (*newItem).next = (*poly2).next;
        (*poly2).next = newItem;
        stackSize++;
    }
}

void printAndFree(pStack poly1, pStack poly2)
{
    node *itemToPop, *s;
    while ((*poly1).next && (*poly2).next)
    {
        if (((*poly1).next->exp) > ((*poly2).next->exp))
        {
            itemToPop = (*poly1).next;
            (*poly1).next = (*itemToPop).next;
        }
        else
        {
            itemToPop = (*poly2).next;
            (*poly2).next = (*itemToPop).next;
        }
        printf("%d %d ", (*itemToPop).coef, (*itemToPop).exp);
        free(itemToPop);
    }
    if ((*poly1).next == NULL)
    {
        while ((*poly2).next != NULL)
        {
            itemToPop = (*poly2).next;
            (*poly2).next = (*itemToPop).next;
            printf("%d %d ", (*itemToPop).coef, (*itemToPop).exp);
            free(itemToPop);
        }
    }
    else if ((*poly2).next == NULL)
    {
        while ((*poly2).next != NULL)
        {
            itemToPop = (*poly1).next;
            (*poly1).next = (*itemToPop).next;
            printf("%d %d ", (*itemToPop).coef, (*itemToPop).exp);
            free(itemToPop);
        }
    }
}

int main()
{
    pStack poly1 = (pStack)malloc(sizeof(node));
    pStack poly2 = (pStack)malloc(sizeof(node));
    poly1->next = NULL;
    poly2->next = NULL;
    input(poly1, poly2);
    printAndFree(poly1, poly2);
    return 0;
}