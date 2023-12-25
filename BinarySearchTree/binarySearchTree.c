#include "binarySearchTree.h"
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

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree)
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
    }
    #if 1
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
    #endif
    *pBstree = bstree;
    return ret;
}

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
        cmp = val - travelNode->data;
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

    if ( cmp < 0)
    {
        parentNode->left = (val的结点);
    }
    else
    {
        parentNode->right = (val的结点);
    }
        
    return ret;
}