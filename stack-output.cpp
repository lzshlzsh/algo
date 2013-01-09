#include <iostream>
#include <stack>
#include <list>
#include <cstdio>

#define ELENUM 3 

using namespace std;

int counter = 0;
stack<int> mystack;
list<int> result;
list<int> mylist;

void print_result()
{
 for(list<int>::iterator ite = result.begin();
   ite != result.end(); ite++)
 {
  cout<<*ite<<" ";
 }
 stack<int> temp_stack;
 while(!mystack.empty())
 {
  cout<<mystack.top()<<" ";
  temp_stack.push(mystack.top());
  mystack.pop();
 }
 cout<<endl;
 while(!temp_stack.empty())
 {
  mystack.push(temp_stack.top());
  temp_stack.pop();
 }
}

void  stack_seq(int n, int m)
{
 if(n == 0)
 {
  counter++;
  print_result();
  return;
 }
 if(m == 0)
 {
  mystack.push(mylist.front());
  mylist.pop_front();
  stack_seq(n-1,1);
  mylist.push_front(mystack.top());
  mystack.pop();
  return;
 }
 mystack.push(mylist.front());
 mylist.pop_front();
 stack_seq(n-1,m+1);
 mylist.push_front(mystack.top());
 mystack.pop();
 result.push_back(mystack.top());
 mystack.pop();
 stack_seq(n,m-1);
 mystack.push(result.back());
 result.pop_back();

}
void init()
{
 for(int i =1; i <= ELENUM; i ++)
 {
  mylist.push_back(i);
 }
}

int main(void)
{
 init();
 stack_seq(ELENUM,0);
 printf("the total is %d\n",counter);
 return 0;
}
