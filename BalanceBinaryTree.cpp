#include <stdio.h>  
#include <stdlib.h>  
/************************************************************************/  
/*                    平衡二叉树---AVL                                  */  
/************************************************************************/  
#define LH +1  
#define EH  0  
#define RH -1  
typedef int ElemType;  
typedef struct BSTNode{  
    ElemType data;  
    int bf;//balance flag  
    struct BSTNode *lchild,*rchild;  
}*PBSTree;  
  
void R_Rotate(PBSTree* p)  
{  
    PBSTree lc = (*p)->lchild;  
    (*p)->lchild = lc->rchild;  
    lc->rchild = *p;  
    *p = lc;  
}  
  
void L_Rotate(PBSTree* p)  
{  
    PBSTree rc = (*p)->rchild;  
    (*p)->rchild = rc->lchild;  
    rc->lchild = *p;  
    *p = rc;  
}  
  
void LeftBalance(PBSTree* T)  
{  
    PBSTree lc,rd;  
    lc = (*T)->lchild;  
    switch (lc->bf)  
    {  
    case LH:  
        (*T)->bf = lc->bf = EH;  
        R_Rotate(T);  
        break;  
    case RH:  
        rd = lc->rchild;  
        switch(rd->bf)  
        {  
        case LH:  
            (*T)->bf = RH;  
            lc->bf = EH;  
            break;  
        case EH:  
            (*T)->bf = lc->bf = EH;  
            break;  
        case RH:  
            (*T)->bf = EH;  
            lc->bf = LH;  
            break;  
        }  
        rd->bf = EH;  
        L_Rotate(&(*T)->lchild);  
        R_Rotate(T);  
        break;  
    }  
}  
  
void RightBalance(PBSTree* T)  
{  
    PBSTree lc,rd;  
    lc= (*T)->rchild;  
    switch (lc->bf)  
    {  
    case RH:  
        (*T)->bf = lc->bf = EH;  
        L_Rotate(T);  
        break;  
    case LH:  
        rd = lc->lchild;  
        switch(rd->bf)  
        {  
        case LH:  
            (*T)->bf = EH;  
            lc->bf = RH;  
            break;  
        case EH:  
            (*T)->bf = lc->bf = EH;  
            break;  
        case RH:  
            (*T)->bf = EH;  
            lc->bf = LH;  
            break;  
        }  
        rd->bf = EH;  
        R_Rotate(&(*T)->rchild);  
        L_Rotate(T);  
        break;  
    }  
}  
  
int InsertAVL(PBSTree* T,ElemType e,bool* taller)  
{  
    if ((*T)==NULL)  
    {  
        (*T)=(PBSTree)malloc(sizeof(BSTNode));  
        (*T)->bf = EH;  
        (*T)->data = e;  
        (*T)->lchild = NULL;  
        (*T)->rchild = NULL;  
    }  
    else if (e == (*T)->data)  
    {  
        *taller = false;  
        return 0;  
    }  
    else if (e < (*T)->data)  
    {  
        if(!InsertAVL(&(*T)->lchild,e,taller))  
            return 0;  
        if(*taller)  
        {  
            switch ((*T)->bf)  
            {  
            case LH:  
                LeftBalance(T);  
                *taller = false;  
                break;  
            case  EH:  
                (*T)->bf = LH;  
                *taller = true;  
                break;  
            case RH:  
                (*T)->bf = EH;  
                *taller = false;  
                break;  
            }  
        }  
    }  
    else  
    {  
        if(!InsertAVL(&(*T)->rchild,e,taller))  
            return 0;  
        if (*taller)  
        {  
            switch ((*T)->bf)  
            {  
            case LH:  
                (*T)->bf = EH;  
                *taller = false;  
                break;  
            case EH:  
                (*T)->bf = RH;  
                *taller = true;  
                break;  
            case  RH:  
                RightBalance(T);  
                *taller = false;  
                break;  
            }  
        }  
    }  
    return 1;  
}  
  
bool FindNode(PBSTree root,ElemType e,PBSTree* pos)  
{  
    PBSTree pt = root;  
    (*pos) = NULL;  
    while(pt)  
    {  
        if (pt->data == e)  
        {  
            //找到节点，pos指向该节点并返回true  
            (*pos) = pt;  
            return true;  
        }  
        else if (pt->data>e)  
        {  
            pt = pt->lchild;  
        }  
        else  
            pt = pt->rchild;  
    }  
    return false;  
}  
void InorderTra(PBSTree root)  
{  
    if(root->lchild)  
        InorderTra(root->lchild);  
    printf("%d ",root->data);  
    if(root->rchild)  
        InorderTra(root->rchild);  
}  
  
int main()  
{  
    int i,nArr[] = {1,23,45,34,98,9,4,35,23};  
    PBSTree root=NULL,pos;  
    bool taller;  
    for (i=0;i<9;i++)  
    {  
        InsertAVL(&root,nArr[i],&taller);  
    }  
    InorderTra(root);  
    if(FindNode(root,103,&pos))  
        printf("\n%d\n",pos->data);  
    else  
        printf("\nNot find this Node\n");  
    return 0;  
}  

