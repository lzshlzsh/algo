#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H
#include <list>
#include <vector>
using std::list;
using std::vector;

#define DEBUG

//对于叶节点,通过m_nActiveLen和m_nEdgeLabelEndPos可以得到节点对应的字符串.对于分支节点,也是如此.
struct tagSuffixNode
{
public:
    tagSuffixNode* m_tpChild; //子节点,如果为0,说明是叶子节点
    tagSuffixNode* m_tpParent; //父节点,根节点的父节点为0
    tagSuffixNode* m_tpLeftSibling; //左兄弟
    tagSuffixNode* m_tpRightSibling; //右兄弟
    tagSuffixNode* m_tpMostRightChild;//最右子节点
    tagSuffixNode* m_tpSuffixLink; //指向当前节点表示的子串的最大后缀所对应的分支节点

    int m_nActiveLen; //节点代表的字符串的长度.    
    int m_nEdgeLabelStartPos; //入边开始字符的下标.对于分支节点,只是用来表示边对应的字符串是什么,并不表示其在子孙叶节点表示的串中对应位置的字符在整个串中的下标.
    int m_nEdgeLabelEndPos; //入边结束字符的下标
    bool m_bIsLeaf; //是否是叶节点

    char m_cIndex; //test


public:
    void init()
        {
            m_tpChild = 0;
            m_tpParent = 0;
            m_tpLeftSibling = 0;
            m_tpRightSibling = 0;
            m_tpMostRightChild = 0;
            m_tpSuffixLink = 0;

            m_nEdgeLabelStartPos = 0;
            m_nEdgeLabelEndPos = 0;

            m_nActiveLen = 0;
            m_bIsLeaf = true;
        }
};

class CSuffixTree
{
public:
    CSuffixTree(char *str);
    ~CSuffixTree();
    void deleteTree();
    void construct();
    void reset(char *str);
    int search(char *str);
    tagSuffixNode* getTree();
    void printTree();    
    void test();
private:
    tagSuffixNode* __allocNode();
    tagSuffixNode* __findChildBeginWithChar(tagSuffixNode* node, char c);

    void __printHelper(tagSuffixNode* node, int level);
private:
    int m_nActiveLen;
    int m_nStrLen; //字符串长度
    tagSuffixNode* m_tpRoot; //根节点
    tagSuffixNode* m_tpActiveNode; //活动节点
    char *m_cpInternalStr; //字符串内存存储

    list<tagSuffixNode*> m_tagNodeList; //保存分配的节点的指针
    vector<tagSuffixNode*> m_tagFromNodeVec; //保存还未确定后缀指针的分支节点的指针，用于判定suffix link
    vector<tagSuffixNode*> m_tagToNodeVec; //保存所有分支节点
#ifdef DEBUG
    char m_cIndex;
#endif
};

#endif // 
