/*
 * find the index pair of A, the corresponding subarray 
 * is B
 */ 
#include <iostream>
#include <map>

using namespace std;

void FindConsecutiveSubarrLocation(int A[], int lenA, int B[], int lenB)
{
    map<int, int> bmap;
    map<int, int> windowmap;
    map<int, int> diffmap;
	/*
	 * count the number of the first lenB elements of 'A' and 'B'
	 */
    for(int i = 0; i< lenB; i++){
        if(bmap.count(B[i]) == 0)
            bmap[B[i]] = 1;
        else
            ++bmap[B[i]];
        if(windowmap.count(A[i]) == 0)
            windowmap[A[i]] = 1;
        else
            ++windowmap[A[i]];
    }

    map<int, int>::iterator it = bmap.begin();
    int sameElement = 0;
	/*
	 * get the different set 'A - B'
	 */
    while(it != bmap.end())
    {
        if(windowmap.count((*it).first) != 0)
        {
            diffmap[(*it).first] = windowmap[(*it).first] - (*it).second;
            if(diffmap[(*it).first]  == 0)
                sameElement++;
        }
        else
            diffmap[(*it).first] = -(*it).second;
        it++;
    }

	/*if match*/
    if(sameElement == lenB)
    {
        cout<<"----------find one---------"<<endl;
        cout<<"start index:"<<0<<endl;
        cout<<"end index:"<<lenB-1<<endl;
    }

	/*scan the rest elements*/
    for(int i = lenB; i < lenA; i++)
    {
		/*
		 * the element will slide out the window
		 * Does 'B' have this element?
		 */
        if(diffmap.count(A[i-lenB]) != 0)
        {
			/*yes*/
            diffmap[A[i-lenB]]--;
            if(diffmap[A[i-lenB]] == 0)
				/*1->0: the number of the element is equal*/
                sameElement++;
            else if(diffmap[A[i-lenB]] == -1)
				/*0->-1: equal the last window, but now NOT equal*/
                sameElement--;
        }
		/*
		 * the element will slide in the window
		 * Does 'B' have this element?
		 */
        if(diffmap.count(A[i]) !=0)
        {
			/*yes*/
            diffmap[A[i]]++;
            if(diffmap[A[i]] == 0)
				/*-1->0: not equal to equal*/
                sameElement++;
            else if(diffmap[A[i]] == 1)
				/*0->1: equal to NOT equal*/
                sameElement--;
        }
		/*match*/
        if((unsigned int)sameElement == diffmap.size())
        {
            cout<<"----------find one---------"<<endl;
            cout<<"start index:"<< i-lenB+1 << endl;
            cout<<"end index:"<< i << endl;
        }
    }
}

int main()
{
#if 1
    int A[] = {4, 1, 2, 1, 8, 9, 2, 1, 2, 9, 8, 4, 6};
    int B[] = {1, 1, 2, 8, 9};
#else	
    int A[] = {4, 1, 6, 2, 8, 9, 5, 3, 2, 9, 8, 4, 6};
    int B[] = {6, 1, 2, 9, 8};
#endif
    int lenA = sizeof(A)/sizeof(int);
    int lenB = sizeof(B)/sizeof(int);
    FindConsecutiveSubarrLocation(A, lenA, B, lenB);
    return 0;
}

