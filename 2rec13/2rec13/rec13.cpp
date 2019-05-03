/*
Rec13 - STL
	Topics
	Collections
	Half-open range
	Iterators
	Algorithms
	Functors and Lambdas
	Function Templates
	Maps and sets
Written by Giana Yang, 05/03/2019
*/

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void printList(const list<int>& ilist) {
	for (list<int>::const_iterator iter = ilist.begin(); iter != ilist.end(); ++iter) {
		cout << *iter << endl;
	}
}

void printList_range(const list<int>& ilist) {
	for (int inte : ilist) {
		cout << inte << " ";
	}
	cout << endl;
}

void printOtherList(const list<int>& ilist) {
	for (auto iter = ilist.begin(); iter != ilist.end(); ++++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}

list<int>::const_iterator find(const list<int>& ilist, int integ) {
	for (list<int>::const_iterator iter = ilist.begin(); iter != ilist.end(); ++iter) {
		if (*iter == integ) {
			cout << *iter << endl;
			return iter;
		}
	}
	cout << "Not found" << endl;
	return ilist.end();
}

auto find_Range(const list<int>& ilist, int integ) {
	for (auto iter = ilist.begin(); iter != ilist.end(); ++iter) {
		if (*iter == integ) {
			cout << *iter << endl;
			return iter;
		}
	}
	cout << "Not found" << endl;
	return ilist.end();
}

bool findEven(int num) {
	return(num % 2 == 0);
}


class IsEven {
public:
	bool operator()(int number) {
		return (number % 2 == 0);
	}
};

list<int>::const_iterator ourFind(list<int>::const_iterator begin, list<int>::const_iterator  end, int target) {
	for (list<int>::const_iterator iter = begin; iter != end; ++iter) {
		if (*iter == target) {
			return iter;
		}
	}
	return end;
}

template <class T, class U>
T ourFind(T begin, T end, U target) {
	cout << "In a template" << endl;
	for (T iter = begin; iter != end; ++iter) {
		if (*iter == target) {
			return iter;
		}
	}
	return end;
}

bool find_repeat(const vector<string>& text, const string& word) {
	for (size_t i = 0; i < text.size(); ++i) {
		if (text[i] == word) {
			return true;
		}
	}
	return false;
}
int main() {
	// 1. Create a vector with some values and display using ranged for
	cout << "Task 1:\n";
	vector<int> integer({ 12,2,43,46 });
	for (int integ : integer) {
		cout << integ <<" ";
	}
	cout << endl;
	vector<string> str ({ "Hello","World" });
	for (string str : str) {
		cout << str;
	}
	cout << "\n=======\n";

	// 2. Initalize a list as a copy of values from the vector
	cout << "Task 2:\n";
	list<int>ilist(integer.begin(),integer.end());
	for (int inte : ilist) {
		cout << inte<<" ";
	}
	cout << endl;
	cout << "\n=======\n";

	// 3. Sort the original vector.  Display both the vector and the list
	cout << "Task 3:\n";
	sort(integer.begin(), integer.end());
	for (int integ : integer) {
		cout << integ<<" ";
	}
	cout << endl;
	for (int inte : ilist) {
		cout << inte<<" ";
	}
	cout << "\n=======\n";

	// 4. print every other element of the vector.
	cout << "Task 4:\n";
	for (size_t i = 0; i < integer.size();++++i) {
		cout << integer[i] << " ";
	}
	cout << "\n=======\n";

	// 5. Attempt to print every other element of the list using the
	//    same technique.
	cout << "Task 5:\n";
	/*for (size_t i = 0; i < ilist.size(); ++++i) {
		cout << ilist[i] << " ";
	}*/
	cout << "\n=======\n";

	//
	// Iterators
	//

	// 6. Repeat task 4 using iterators.  Do not use auto;
	cout << "Task 6:\n";
	for (vector<int>::iterator iter = integer.begin(); iter != integer.end();iter+=2) {
		cout << *iter << endl;
	}
	cout << "\n=======\n";

	// 7. Repeat the previous task using the list.  Again, do not use auto.
	//    Note that you cannot use the same simple mechanism to bump
	//    the iterator as in task 6.
	cout << "Task 7:\n";
	for (list<int>::iterator iter = ilist.begin(); iter != ilist.end(); ++ ++iter) {
		cout << *iter << " ";
	}
	cout << "\n=======\n";

	// 8. Sorting a list
	cout << "Task 8:\n";
	ilist.sort();
	for (list<int>::iterator iter = ilist.begin(); iter != ilist.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << "\n=======\n";

	// 9. Calling the function to print the list
	cout << "Task 9:\n";
	printList(ilist);
	cout << "=======\n";

	// 10. Calling the function that prints the list, using ranged-for
	cout << "Task 10:\n";
	printList_range(ilist);
	cout << "=======\n";

	//
	// Auto
	//

	// 11. Calling the function that, using auto, prints alterate
	// items in the list
	cout << "Task 11:\n";
	printOtherList(ilist);
	cout << "=======\n";


	// 12.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 12:\n";
	find(ilist, 12);
	find(ilist, 31);
	cout << "=======\n";

	// 13.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 13:\n";
	find_Range(ilist, 12);
	cout << "=======\n";

	//
	// Generic Algorithms
	//

	// 14. Generic algorithms: find
	cout << "Task 14:\n";
	list<int>::iterator iter=find(ilist.begin(), ilist.end(), 12);
	if (iter == ilist.end()) {
		cout << "not found"<<endl;
	}
	else {
		cout << *iter << endl;
	}
	cout << "=======\n";

	// 15. Generic algorithms: find_if
	cout << "Task 15:\n";
	list<int>::iterator iter2 = find_if(ilist.begin(), ilist.end(), findEven);
	if (iter2 == ilist.end()) {
		cout << "not found" << endl;
	}
	else {
		cout << *iter2 << endl;
	}
	cout << "=======\n";

	// 16. Functor
	cout << "Task 16:\n";
	list<int>::iterator iter3 = find_if(ilist.begin(), ilist.end(), IsEven());
	if (iter3 == ilist.end()) {
		cout << "not found" << endl;
	}
	else {
		cout << *iter3 << endl;
	}
	cout << "=======\n";

	// 17. Lambda
	cout << "Task 17:\n";
	for (int inte : ilist) {
		bool even = [](int inte) {return (inte % 2) == 0; }(inte);
		if (even == true) {
			cout << inte << endl;
			break;
		}
	}


	cout << "=======\n";

	// 18. Generic algorithms: copy to an array
	cout << "Task 18:\n";
	int arr[4];
	copy(ilist.begin(), ilist.end(), arr);
	for (size_t i = 0; i < 4; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	int* iter5 = find(arr, arr + 4, 12);
	if (iter5 != arr + 4) {
		cout << *iter5 << endl;
	}
	else {
		cout << "not found!!" << endl;
	}
	cout << "=======\n";

	//
	// Templated Functions
	//

	// 19. Implement find as a function for lists
	cout << "Task 19:\n";
	const list<int> ilist2 ({ 12,43,2,1 });
	list<int>::const_iterator iter6 = ourFind(ilist2.begin(), ilist2.end(), 43);

	if (iter6 != ilist2.end()) {
		cout << *iter6 << endl;
	}
	else {
		cout << "not found!!" << endl;
	}
	cout << "=======\n";

	// 20. Implement find as a templated function
	cout << "Task 20:\n";
	list<int>::const_iterator iter7 = ourFind(ilist2.begin(),ilist2.end(), 43);
	if (iter7 != ilist2.end()) {
		cout << *iter7 << endl;
	}
	else {
		cout << "not found!!" << endl;
	}
	vector<int>::const_iterator iter8 = ourFind(integer.begin(), integer.end(), 43);
	if (iter8 != integer.end()) {
		cout << *iter8 << endl;
	}
	else {
		cout << "not found!!" << endl;
	}
	cout << "=======\n";

	//
	// Associative collections
	//

	// 21. Using a vector of strings, print a line showing the number
	//     of distinct words and the words themselves.
	cout << "Task 21:\n";
	ifstream ifs;
	ifs.open("pooh-nopunc.txt");
	string word;
	vector<string> text;
	bool in_file = false;
	while (ifs >> word) {
		in_file = find_repeat(text, word);
		if (in_file == false) { text.push_back(word); }
	}
	cout << "There are " << text.size() << "in the text" << endl;
	for (size_t i = 0; i < text.size(); ++i) {
		cout << text[i] << ' ';
	}
	ifs.close();

	cout << "\n=======\n";

	// 22. Repeating previous step, but using the set
	cout << "Task 22:\n";
	ifstream ifs2("pooh-nopunc.txt");
	set<string> text2;
	while (ifs >> word) {
		if (text2.find(word)==text2.end()) { text2.insert(word); }
	}
	cout << "There are " << text.size() << "in the text" << endl;
	for (string item : text2) {
		cout << item<<' ';
	}
	ifs2.close();
	cout << "=======\n";

	// 23. Word co-occurence using map
	cout << "Task 23:\n";
	map<string, vector<int>> wordMap;
	ifstream ifs3("pooh-nopunc.txt");
	int index = 0;
	while (ifs3 >> word) {
		wordMap[word].push_back(index);
		++index;
	}
	for (auto item : wordMap) {
		cout << item.first << ": ";
		for (auto item2 : item.second) {
			cout << item2 << ", ";
		}
		cout << endl;
	}
	ifs3.close();
	cout << "=======\n";
}
