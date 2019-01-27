#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H
#include <list>
#include <vector>
using std::list;
using std::vector;

#define DEBUG

//����Ҷ�ڵ�,ͨ��m_nActiveLen��m_nEdgeLabelEndPos���Եõ��ڵ��Ӧ���ַ���.���ڷ�֧�ڵ�,Ҳ�����.
struct tagSuffixNode
{
public:
    tagSuffixNode* m_tpChild; //�ӽڵ�,���Ϊ0,˵����Ҷ�ӽڵ�
    tagSuffixNode* m_tpParent; //���ڵ�,���ڵ�ĸ��ڵ�Ϊ0
    tagSuffixNode* m_tpLeftSibling; //���ֵ�
    tagSuffixNode* m_tpRightSibling; //���ֵ�
    tagSuffixNode* m_tpMostRightChild;//�����ӽڵ�
    tagSuffixNode* m_tpSuffixLink; //ָ��ǰ�ڵ��ʾ���Ӵ�������׺����Ӧ�ķ�֧�ڵ�

    int m_nActiveLen; //�ڵ������ַ����ĳ���.    
    int m_nEdgeLabelStartPos; //��߿�ʼ�ַ����±�.���ڷ�֧�ڵ�,ֻ��������ʾ�߶�Ӧ���ַ�����ʲô,������ʾ��������Ҷ�ڵ��ʾ�Ĵ��ж�Ӧλ�õ��ַ����������е��±�.
    int m_nEdgeLabelEndPos; //��߽����ַ����±�
    bool m_bIsLeaf; //�Ƿ���Ҷ�ڵ�

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
    int m_nStrLen; //�ַ�������
    tagSuffixNode* m_tpRoot; //���ڵ�
    tagSuffixNode* m_tpActiveNode; //��ڵ�
    char *m_cpInternalStr; //�ַ����ڴ�洢

    list<tagSuffixNode*> m_tagNodeList; //�������Ľڵ��ָ��
    vector<tagSuffixNode*> m_tagFromNodeVec; //���滹δȷ����׺ָ��ķ�֧�ڵ��ָ�룬�����ж�suffix link
    vector<tagSuffixNode*> m_tagToNodeVec; //�������з�֧�ڵ�
#ifdef DEBUG
    char m_cIndex;
#endif
};

#endif // 
