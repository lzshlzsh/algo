/*
 * delete map entries whoes value is given
 */
#include <iostream>
#include <map>
#include <string>

using namespace std;

typedef map<string, int> Str2Int;
typedef map<string, int>::iterator Str2Int_iterator;

int main()
{
	Str2Int str2int;
	string str = "a";
	int val = 2;

	for (str = "a"; str[0] <= 'z'; str[0]++)
		str2int[str] = (str[0] - 'a') % 10 + 1;

	for (Str2Int_iterator it = str2int.begin(); 
		it != str2int.end(); it++){
		cout << it->first << " ==> " << it->second << endl;
	}
	cout << "****************" << endl;

	/*delete 2*/
	Str2Int_iterator it = str2int.begin(); 

	while (it != str2int.end()){
		if (it->second == val){
			str2int.erase(it++); /*first it++, use its value to erase*/
		}else{
			it++;
		}
	}

	for (Str2Int_iterator it = str2int.begin(); 
		it != str2int.end(); it++){
		cout << it->first << " ==> " << it->second << endl;
	}
	return 0;
}
