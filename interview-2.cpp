#include <iostream>
#include <stack>
#include <iterator>

using namespace std;

typedef struct withindex
{
    int value;
    int index;
}WithIndexSt;

void NearestNumberGreaterThanCurrent(int src[], int dst[], int n)
{
    stack<WithIndexSt> m_stack;
    for(int i = n - 1; i >= 0; i--)
    {
        while(!m_stack.empty())
        {
            if(m_stack.top().value < src[i])
            {
                dst[m_stack.top().index] = i;
                m_stack.pop();
            }
            else
                break;
        }
        WithIndexSt tmpst = {src[i], i};
        m_stack.push(tmpst);
    }
//    dst[0] = -1;
}

int main()
{
    int src[] = {1, 9, 5, 2, 4, 7};
    int nsize = sizeof(src)/sizeof(int);
    int* dst = new int[nsize];
	for (int i = 0; i < nsize; i++)
		dst[i] = -1;
    NearestNumberGreaterThanCurrent(src, dst, nsize);
    copy(src, src+nsize, ostream_iterator<int>(cout, "\t"));
    cout<<endl;
    copy(dst, dst+nsize, ostream_iterator<int>(cout, "\t"));
    cout<<endl;
    delete[] dst;
    return 0;
}

