#include <iostream>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

int n;
int s;

vector<int>v[900];

vector<int>ask[900];


int far[900];

int result[900];

int have[900];


int find_far(int k)
{
    if(far[k] == k) return k;

    far[k]=find_far(far[k]);

    return far[k];
}



void LCA(int k)
{
    int i, a;

    far[k]=k;

    for(i=0; i<v[k].size(); i++)
    {
        LCA(v[k][i]);
        far[v[k][i]]=k;
    }

    have[k]=1;

    for(i=0; i<ask[k].size(); i++)
    {
        if(have[ask[k][i]] == 1)
        {
            a=find_far(ask[k][i]);
            result[a]++;
        }
    }
}



int main()
{
    int a, b, bu, i;

    char ch;

    while(scanf("%d", &n) == 1)
    {
        int st[900]={0};

        for(i=0; i<n; i++)
        {
            cin >> a >> ch >> ch >> bu >> ch;
            a--;
            while(bu--)
            {
                scanf("%d", &b);
                b--;
                v[a].push_back(b);
                st[b]=1;
            }
        }

        for(i=0; i<n; i++)
        {
            if(st[i] == 0)
            {
                s=i;
                break;
            }
        }

        scanf("%d", &bu);
        while(bu--)
        {
            cin >> ch >> a >> b >> ch;
            a--;
            b--;
            ask[a].push_back(b);
            ask[b].push_back(a);
        }

        memset(have, 0, sizeof(have));
        memset(result, 0, sizeof(result));

        LCA(s);

        for(i=0; i<n; i++)
        {
            if(result[i]!=0)
            {
                printf("%d:%d\n", i+1, result[i]);
            }
            v[i].clear();
            ask[i].clear();
        }
    }
    return 0;
}
