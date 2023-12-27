#include "binarySearchTree.h"
#include "doubleLinkListQueue.h"
#include <stdlib.h>
#include <string.h>



enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,

};

/* 静态函数前置声明 */
static int compareFunc(ELEMENTTYPE val1,ELEMENTTYPE val2);
/* 创建结点 */
static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode * parentNode);
/* 根据指定的值获取二叉搜索树的结点 */
static BSTreeNode * baseAppointValGetBSTreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val);
/* 判断二叉搜索树数度为2 */
static int binarySearchTreeNodeHasTwochildren(BSTreeNode *node);
/* 判断二叉搜索树数度为1 */
static int binarySearchTreeNodeHasOnechildren(BSTreeNode *node);
/* 判断二叉搜索树数度为0 */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node);
/* 前序遍历 */
static int preOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
/* 中序遍历 */
static int inOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
/* 后序遍历 */
static int postOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
/* 获取当前结点的前驱结点 */
static BSTreeNode * bstreeNodePreDecessor(BSTreeNode *node); 
/* 获取当前结点的后继结点 */
static BSTreeNode * bstreeNodeSuccessor(BSTreeNode *node); 

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree, int(*compareFunc)(ELEMENTTYPE val1,ELEMENTTYPE val2) ,int (*printFunc)(ELEMENTTYPE val))
{
    int ret = 0;
    BinarySearchTree * bstree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree, 0 , sizeof(BinarySearchTree) * 1);
    /* 初始化树 */
    {
        bstree->root = NULL;
        bstree->size = 0;
        /* 钩子函数在这边赋值*/
        bstree->compareFunc = compareFunc;
        /* 钩子函数包装器 自定义打印 */
        bstree->printFunc = printFunc;
    }
#if 0
    /* 分配根节点 */
    bstree->root = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree->root, 0 , sizeof(BSTreeNode) * 1);
    /* 初始化根节点 */
    {
        bstree->root->data = 0;
        bstree->root->left = NULL;
        bstree->root->right = NULL;
        bstree->root->parent = NULL;
    }
#else
    bstree->root = createBSTreeNewNode(0, NULL);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
#endif
    *pBstree = bstree;
    return ret;
}

/* 判断二叉搜索树数度为2 */
static int binarySearchTreeNodeHasTwochildren(BSTreeNode *node)
{
    return node->left != NULL && node->right != NULL;
}

/* 判断二叉搜索树数度为1 */
static int binarySearchTreeNodeHasOnechildren(BSTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL))  || ((node->left != NULL) && (node->right != NULL));
}

/* 判断二叉搜索树数度为0 */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 获取当前结点的前驱结点 */
/* 中序遍历搭到结点的前一个结点 */
static BSTreeNode * bstreeNodePreDecessor(BSTreeNode *node)
{
      if (node->left != NULL)
        {
            /* 前驱结点是在左子树的右子树的右子树.. */
            BSTreeNode *travelNode = node->left;
            while (travelNode->right != NULL)
            {
                /*  */
                travelNode = travelNode->right;
            }
            return travelNode;    
        }   

        /* 程序执行到这个地方 说明一定没有左子树。 那就需要向父结点找 */
        while (node->parent != NULL && node == node->parent->left)
        {
            node = node->parent;
        }
        /* node->parent == NULL.*/
        /* node == node->parent->right.*/
        return node->parent;
        
}    

/* 获取当前结点的后继结点 */
/* 后继结点：中序遍历时的比当前结点大的第一个结点 */
static BSTreeNode * bstreeNodeSuccessor(BSTreeNode *node)
{
    if (node->right != NULL)
    {
        BSTreeNode *travelNode = node->right;
        while (travelNode->left != NULL)
        { 
            travelNode = travelNode->left;
        }
        return travelNode;       
    }
    /* 程序执行到这个地方 说明一定没有右子树。 那就需要向父结点找 */
    while (node->parent != NULL && node == node->parent->right)
    {
        node = node->parent;
    }
    return node->parent;
} 

/* 创建结点 */
static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode * parentNode)
{
      /* 分配根节点 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(newBstNode, 0 , sizeof(BSTreeNode) * 1);
    /* 初始化根节点 */
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }

    /* 赋值 */
    newBstNode->data = val;

}

#if 0
static int compareFunc(ELEMENTTYPE val1,ELEMENTTYPE val2)
{
    #if 0
    if (val1 < val2)
    {
        return -1;
    }
    else if (val1 > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    #else
    return val1 - val2;
    #endif
}
#endif

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 空树 */
    if (pBstree->size == 0)
    {
        /* 更新树的节点 */
        (pBstree->size)++;

        pBstree->root->data = val;
        return ret;
    }

    /* travelNode 指向根节点 */
    BSTreeNode * travelNode = pBstree->root;
    BSTreeNode * parentNode = pBstree->root;

    /* 确定符号：到底放在左边还是右边 */
    int cmp = 0;
    while ( travelNode != NULL)
    {
        /* 标记父结点 */
        parentNode = travelNode;
        cmp = pBstree->compareFunc(val, travelNode->data);
        /* 插入元素 < 遍历到的结点 */
        if (val < travelNode->data)
        {
            travelNode = travelNode->left;
        }
        else if (val > travelNode->data)    /* 插入元素 > 遍历到的结点*/
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 插入元素 = 遍历到的结点 */
            return ret;
        }
    }
#if 0
    /* 分配根节点 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(newBstNode, 0 , sizeof(BSTreeNode) * 1);
    /* 初始化根节点 */
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }
    /* 新结点赋值 */
    newBstNode->data = val;

#else
    BSTreeNode * newBstNode = createBSTreeNewNode(val, parentNode);
#endif

    /* 挂在左子树 */
    if ( cmp < 0)
    {
        parentNode->left = newBstNode;
    }
    else
    {
        /* 挂在右子树 */
        parentNode->right = newBstNode;
    }
#if 0
    /* 新结点的parent指针赋值*/
    newBstNode->parent = parentNode;
#endif
    /* 更新树的结点 */
    (pBstree->size)++;     
    return ret;
}

/* 前序遍历 */
/* 根结点 */
static int preOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 根结点 */
    pBstree->printFunc(node->data);
    /* 左子树 */
    preOrderTravel(pBstree, node->left);
    /* 右子树 */
    preOrderTravel(pBstree, node->right);
}

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    preOrderTravel(pBstree,pBstree->root);
    return ret;
}

/* 斐波拉契数列 */
/*  
    # 递归
    f(1) = 1, f(2)= 1
    f(n) = f(n-1) + f(n-2) [n>2 n是整数]
*/
/* 中序遍历 */
/* 左子树 根结点 右子树 */
static int inOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    inOrderTravel(pBstree, node->left);
    /* 根结点 */
    pBstree->printFunc(node->data);
    /* 右子树 */
    inOrderTravel(pBstree, node->left);
}
/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    InOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 后序遍历 */
static int postOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    postOrderTravel(pBstree, node->left);
    /* 右子树 */
    postOrderTravel(pBstree, node->left);
    /* 根结点 */
    pBstree->printFunc(node->data);
    

}
/* 二叉搜索树的后序遍历 */
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    PostOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLevelOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    DoubleLinkListQueue *pQueue = NULL; 
    doubleLinkListQueueInit(&pQueue);

    /* 1.根结点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);

    /* 判断是否为空 */
    BSTreeNode * nodeVal = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&nodeVal);
        #if 0
        printf ("data:%d\n", nodeVal->data);
        #else
        pBstree->printFunc(nodeVal->data);
        #endif
        doubleLinkListQueuePop(pQueue);

        /* 将左子树入队 */
        if (nodeVal->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->left);
        }

        /* 将右子树入队 */
        if (nodeVal->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->right);
        }
    }
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
    
    return ret;
}

/* 根据指定的值获取二叉搜索树的结点 */
static BSTreeNode * baseAppointValGetBSTreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    BSTreeNode * travelNode = pBstree->root;
    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 比较大小*/
        cmp = pBstree->compareFunc(val, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 找到了 */
            return travelNode;
        }
    }
    return NULL;

}

/* 二叉搜索树是否包含指定的元素 */
int binarySearchTreeIsContainAppointVal(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetBSTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 获取二叉搜索树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pBstree, int * pHeight)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }

    if (pBstree->size == 0)
    {
        return 0;
    }
    int ret ;
    DoubleLinkListQueue * pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    doubleLinkListQueuePush(pQueue, pBstree->root);
    /* 树的高度（根结点入队高度为一） */
    int height = 0; 
    /* 树每一层的结点数量 */
    int levelSize = 1;

    BSTreeNode * travelNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);
        levelSize--;

        /* 左子树不为空 */
        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        /* 右子树不为空 */
        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }

        /* 树的当前结点遍历结束 */
        if (levelSize == 0)
        {
            height++;
            doubleLinkListQueueGetSize(pQueue, &levelSize);

        }
        /* 解引用 */
        * pHeight = height;

         /* 释放队列的空间 */
        doubleLinkListQueueDestroy(pQueue);
            
    } 
    return ret; 


}

/* 二叉搜索树的删除 */
int binarySearchTreeDelete(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;

    return ret;
}

/* 二叉搜索树的销毁 */
int binarySearchTreeDestroy(BinarySearchTree *pBstree)
{
    if ( pBstree == NULL)
    {
        return NULL_PTR;
    }

    int ret = 0;
    DoubleLinkListQueue *pQueue = NULL; 
    doubleLinkListQueueInit(&pQueue);
    doubleLinkListQueuePush(pQueue, pBstree->root);
    BSTreeNode * travelNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);

        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }
        /* 右子树不为空 */
        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }

        if (travelNode)
        {
            free(travelNode);
            travelNode = NULL;
        }
    }
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
    /* 释放树 */
    if (pBstree)
    {
        free(pBstree);
        pBstree = NULL;
    }
    

    
}
