#include "suffixtree.h"
#include <list>
#include <vector>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <iostream>

#include "string_common.h"

using namespace std;

CSuffixTree::CSuffixTree(char *str)
    :m_nActiveLen(0),     
     m_tpRoot(0),    
     m_tpActiveNode(0)
{
    m_nStrLen = strlen(str) + 1;
    m_cpInternalStr = new char[m_nStrLen+1];

    sprintf(m_cpInternalStr, "%s#", str);
#ifdef DEBUG    
    m_cIndex = 'A';
#endif    
}

CSuffixTree::~CSuffixTree()
{
    deleteTree();
    delete[] m_cpInternalStr;
}

void CSuffixTree::deleteTree()
{
    list<tagSuffixNode*>::iterator iter = m_tagNodeList.begin();
    for(; iter != m_tagNodeList.end(); ++iter)
    {
        delete *iter;
    }

    m_tagNodeList.clear();
}


void CSuffixTree::reset(char *str)
{
    deleteTree();

    int tmp = strlen(str);
    if(tmp+1 > m_nStrLen)
    {
        m_nStrLen = tmp+1;
        delete[] m_cpInternalStr;
        m_cpInternalStr = new char[m_nStrLen+1];
    }
    else
    {
        m_nStrLen = tmp+1;
    }
    sprintf(m_cpInternalStr, "%s#", str);

    m_nActiveLen = 0;
    m_nStrLen = 0;
    m_tpActiveNode = 0;
    m_tpRoot = 0;

    m_tagFromNodeVec.clear();
    //reconstruct tree for new string
    construct();
}
void CSuffixTree::construct()
{
    m_tpRoot = __allocNode();
    if(m_tpRoot == 0)
    {
#ifdef DEBUG
        printf("__allocNode error!\n");
#endif
        return;
    }
    m_nActiveLen = 0;
    m_tpRoot->m_nActiveLen = 0;
    //initial active node
    m_tpActiveNode = m_tpRoot;

    m_tagToNodeVec.push_back(m_tpRoot);
    
    for(int i = 0; i<m_nStrLen; i++)
    {
#ifdef DEBUG
        printf("\ninsert %s\n", &(m_cpInternalStr[i]));
        printf("active node:[%c]\n", m_tpActiveNode->m_cIndex);
#endif
        //判断是否有后继节点
        if(m_tpActiveNode->m_tpSuffixLink != 0)
        {
            m_tpActiveNode = m_tpActiveNode->m_tpSuffixLink;
            m_nActiveLen--;
        }
        int pos = i;
        
#ifdef DEBUG        
        printf("new active node:[%c]\n", m_tpActiveNode->m_cIndex);
        printf("pos:%d\n", pos);
        printf("active length:%d\n", m_nActiveLen);
#endif        

        while(true)
        {
            //查找以当前后缀串的开始字符开始的子节点
            tagSuffixNode* node = __findChildBeginWithChar(m_tpActiveNode, m_cpInternalStr[i+m_nActiveLen]);
            //未找到以suffix[i]的开始字符开头的节点
            if(node == 0)
            {
#ifdef DEBUG
                printf("__findChildBeginWithChar null\n");
#endif                
                tagSuffixNode* child = __allocNode();

                //设置开始、结束位置的下标
                child->m_nEdgeLabelStartPos = pos;
                child->m_nEdgeLabelEndPos = m_nStrLen-1;
                //设置叶节点代表的后缀串的长度
                child->m_nActiveLen = m_nStrLen - i;
                //设置父节点
                child->m_tpParent = m_tpActiveNode;
                if( m_tpActiveNode->m_tpChild == 0)
                {
                    m_tpActiveNode->m_tpChild = child;
                    m_tpActiveNode->m_tpMostRightChild = child;
                }
                else
                {
                    m_tpActiveNode->m_tpMostRightChild->m_tpRightSibling = child;
                    child->m_tpLeftSibling = m_tpActiveNode->m_tpMostRightChild;
                    m_tpActiveNode->m_tpMostRightChild = child;
                }

                break;
            }
            else
            {
#ifdef DEBUG
                printf("__findChildBeginWithChar ok\n");
                printf("node start:%d\n", node->m_nEdgeLabelStartPos);
                printf("node end:%d\n", node->m_nEdgeLabelEndPos);
                printf("node index:%c\n", node->m_cIndex);
#endif
                //TODO
                //确定 m_nMinDistance
                int edgeStart = node->m_nEdgeLabelStartPos;
                int strStart = i + m_nActiveLen;
                bool split = false;
            
                for(; edgeStart<=node->m_nEdgeLabelEndPos; edgeStart++, strStart++)
                {
                    if( m_cpInternalStr[edgeStart] != m_cpInternalStr[strStart])
                    {
                        split = true;
                        break;
                    }
                }
                if(!split)
                {
                    m_tpActiveNode = node;
                    m_nActiveLen += node->m_nEdgeLabelEndPos - node->m_nEdgeLabelStartPos + 1;
                    pos += node->m_nEdgeLabelEndPos - node->m_nEdgeLabelStartPos + 1;
                    continue;
                }
                else
                {
                    tagSuffixNode* parent = node->m_tpParent;
                    //new branch node
                    tagSuffixNode* branch = __allocNode();
                    branch->m_bIsLeaf = false;
                    branch->m_nEdgeLabelStartPos = node->m_nEdgeLabelStartPos;
                    branch->m_nEdgeLabelEndPos = edgeStart-1;
                    branch->m_nActiveLen = parent->m_nActiveLen + (branch->m_nEdgeLabelEndPos - branch->m_nEdgeLabelStartPos + 1);
                    //original node
                    node->m_nEdgeLabelStartPos = edgeStart;

                    tagSuffixNode* info = __allocNode();
                    info->m_nEdgeLabelStartPos = strStart;
                    info->m_nEdgeLabelEndPos = m_nStrLen - 1;
                    info->m_nActiveLen = branch->m_nActiveLen + (info->m_nEdgeLabelEndPos - info->m_nEdgeLabelStartPos + 1);

                    branch->m_tpParent = parent;
                    branch->m_tpRightSibling = parent->m_tpChild;
                    parent->m_tpChild->m_tpLeftSibling = branch;
                    parent->m_tpChild = branch;

                    node->m_tpLeftSibling->m_tpRightSibling = node->m_tpRightSibling;
                    if( node->m_tpRightSibling != 0)
                    {
                        node->m_tpRightSibling->m_tpLeftSibling = node->m_tpLeftSibling;
                    }
                    else
                    {
                        parent->m_tpMostRightChild = node->m_tpLeftSibling;
                    }

                    branch->m_tpChild = info;
                    branch->m_tpMostRightChild = node;

                    info->m_tpRightSibling = node;
                    info->m_tpParent = branch;
                    
                    node->m_tpParent = branch;
                    node->m_tpLeftSibling = info;
                    node->m_tpRightSibling = 0;

                    
                    //设置节点的suffix link

                    bool setSuffix = false;
                    vector<tagSuffixNode*>::iterator iter = m_tagToNodeVec.begin();
                    for(; iter != m_tagToNodeVec.end(); ++iter)
                    {
                        tagSuffixNode* tmp = *iter;
                        if( strncmp( &(m_cpInternalStr[branch->m_nEdgeLabelEndPos - branch->m_nActiveLen + 2]), &(m_cpInternalStr[tmp->m_nEdgeLabelEndPos - tmp->m_nActiveLen + 1]), branch->m_nActiveLen - 1) == 0)
                        {
                            branch->m_tpSuffixLink = tmp;
                            setSuffix = true;
                            break;
#ifdef DEBUG
                            printf("branch[%c] suffix_link is branch[%c]\n", tmp->m_cIndex, branch->m_cIndex);
#endif                                
                        }
                    }
                    m_tagToNodeVec.push_back(branch);
                    
                    vector<tagSuffixNode*>::iterator iter2 = m_tagFromNodeVec.begin();
                    for(; iter2 != m_tagFromNodeVec.end(); ++iter2)
                    {
                        tagSuffixNode* tmp = *iter2;
                        //找到后缀节点，结束循环
                        if( strncmp( &(m_cpInternalStr[tmp->m_nEdgeLabelEndPos - tmp->m_nActiveLen + 2]), &(m_cpInternalStr[branch->m_nEdgeLabelEndPos - branch->m_nActiveLen + 1]), tmp->m_nActiveLen - 1) == 0)
                        {
                            tmp->m_tpSuffixLink = branch;
                            m_tagFromNodeVec.erase(iter2);
#ifdef DEBUG
                            printf("branch[%c] suffix_link is branch[%c]\n", tmp->m_cIndex, branch->m_cIndex);
#endif
                            break;
                        }
                    }

                    if( !setSuffix )
                    {
                        m_tagFromNodeVec.push_back(branch);
                    }

                    //已经将新的后缀字符串插入到树中，这时可以结束while了。
                    break;
                }
            }
        }
        //test
#ifdef DEBUG
        printf("print\n");
        printTree();
#endif        
    }
}

int CSuffixTree::search(char *str)
{
    if(str == 0)
        return -1;
    //TODO
    //添加处理过程

    int len = strlen(str);

    tagSuffixNode* node = 0;
    tagSuffixNode* cur = m_tpRoot;
    for(int i=0; i<len; )
    {
        node = __findChildBeginWithChar(cur, str[i]);
        if(node == 0)
        {
            break;
        }
        else
        {
            int edgeLen = node->m_nEdgeLabelEndPos - node->m_nEdgeLabelStartPos + 1;
            int remain = len - i;
            if( remain <= edgeLen )
            {
                if( strncmp(&(str[i]), &(m_cpInternalStr[node->m_nEdgeLabelStartPos]), remain) != 0)
                {
                    return -1;
                }
                else
                {
                    return node->m_nEdgeLabelEndPos - node->m_nActiveLen + 1;
                }
            }
            else
            {
                if( strncmp(&(str[i]), &(m_cpInternalStr[node->m_nEdgeLabelStartPos]), edgeLen) != 0)
                {
                    return -1;
                }
                else
                {
                    i += edgeLen;
                    cur = node;
                }
            }
        }
    }
    return -1;
}

tagSuffixNode* CSuffixTree::__allocNode()
{
    tagSuffixNode* node = new tagSuffixNode;

    m_tagNodeList.push_back(node);

    node->init();
#ifdef DEBUG    
    node->m_cIndex = m_cIndex;
    m_cIndex++;
#endif    
    return node;
}

tagSuffixNode* CSuffixTree::__findChildBeginWithChar(tagSuffixNode* node, char c)
{
    assert(node != 0);

    tagSuffixNode* child = node->m_tpChild;
    while(child != 0)
    {
        if( m_cpInternalStr[child->m_nEdgeLabelStartPos] == c)
            return child;

        child = child->m_tpRightSibling;
    }

    return 0;
}

void CSuffixTree::test()
{
    //printf("%s\n", m_cpInternalStr);
    printTree();
}
void CSuffixTree::printTree()
{
#ifdef DEBUG
    printf("[A]\n");
#endif
    __printHelper(m_tpRoot, 0);
}
void CSuffixTree::__printHelper(tagSuffixNode* node, int level)
{
    int start = node->m_nEdgeLabelStartPos;
    int end = node->m_nEdgeLabelEndPos;
    tagSuffixNode* child = node->m_tpChild;
    if( level > 0 )
    {
        for(int i=0; i<level; i++)
        {
            printf(" |");
        }
        printf(" + ");
        for(int j = start; j <= end; j++)
        {
            printf("%c", m_cpInternalStr[j]);
        }
#ifdef DEBUG        
         printf("[%c]", node->m_cIndex);
//         printf("[%d:%d:%d]", node->m_nEdgeLabelStartPos, node->m_nEdgeLabelEndPos, node->m_nActiveLen);
#endif        
        printf("\n");
    }

    while( child != 0 )
    {
        __printHelper(child, level+1);
        child = child->m_tpRightSibling;
    }
}

int main(int argc, char **argv) {
  int len = 10;
  if (argc >= 2) {
    len = atoi(argv[1]);
  }
  srandom(time(nullptr));
  std::string str;
  common::random_str(str, len);

  CSuffixTree suffix_tree(const_cast<char *>(str.c_str()));
  
  suffix_tree.construct();

  auto sp = random() % len;
  auto pos = suffix_tree.search(const_cast<char *>(str.c_str() + sp));
  if (sp == pos) {
    std::cout << "SUCCESS: search substr at " << sp << std::endl;
  } else {
    std::cout << "FAILURE: search substr at " << sp << std::endl;
  }

  return 0;
}
