#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <cstring>
#include <cassert>

using namespace std;


#define DEBUG



static void do_extend(const char *t, vector< vector<char> > &array)
{
	vector<char> str;
	char tmp;
	
	assert('[' == *t);
	
	while (']' != *t){
		t++; /*skip [*/
		str.push_back(*t); /*'a-' or 'a,' or 'a'*/
		t++;
		if (',' == *t){ 
			t++;
			str.push_back(*t); 
			t++;
		}else if ('-' == *t){
			tmp = *(t - 1);	 /*start*/
			t++; /*end*/
			tmp++; /*skip start*/
			while (*t != tmp){
				str.push_back(tmp);
				tmp++;
			}
			str.push_back(tmp);
			t++;
		}
	}
	array.push_back(str);
}
static void extend_element(vector<const char *> &s, 
		vector< vector<char> > &array)
{
	for (vector<const char *>::iterator it = s.begin(); 
			it != s.end(); it++){
		do_extend(*it, array);
	}
}


static void print_name(vector<char> &prefix, vector<char> &suffix, 
		vector< vector<char> > &array, vector< vector<char> >::iterator it)
{
	if (array.end() == it){
		for (vector<char>::iterator it1 = prefix.begin(); it1 != prefix.end(); it1++){
			cout << *it1;
		}
		for (vector<char>::iterator it1 = suffix.begin(); it1 != suffix.end(); it1++){
			cout << *it1;
		}
		cout << endl;
	}else{
		/*line it*/
		for (vector<char>::iterator it1 = (*it).begin(); it1 != (*it).end(); it1++){
			suffix.push_back(*it1); /*in*/
			print_name(prefix, suffix, array, it + 1);
			suffix.pop_back(); /*out*/
		}
	}
}


int main()
{
	const char *str = "dev[1-4,7][a-d]";
	vector< vector<char> > array;
	vector<const char *> s;
	vector<char> prefix, suffix;
	const char *t, *t1;

	
	t = strchr(str, '[');

	for (t1 = str; t1 != t; t1++){
		prefix.push_back(*t1);
	}

	t = str;
	while ((t = strchr(t, '['))){
		s.push_back(t);
#ifdef DEBUG
		cout << *t << endl;
#endif
		t++;
	}
#ifdef DEBUG
	cout << s.size() << endl;
#endif


	extend_element(s, array);

#ifdef DEBUG
	for (vector< vector<char> >::iterator it1 = array.begin(); 
			it1 != array.end(); it1++){
		for (vector<char>::iterator it2 = (*it1).begin(); 
				it2 != (*it1).end(); it2++){
			cout << *it2 << " ";
		}
		cout << endl;
	}
#endif

	print_name(prefix, suffix, array, array.begin());

	return 0;
}
