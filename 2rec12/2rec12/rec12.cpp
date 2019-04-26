/*
Recitation 12: To make a linked list class
Topics:
	Linked lists
	Packaging a data structure as a class
	Iterators
	Copy control
Written by Giana Yang, 04/26/2019
*/

#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
	Node(int data = 0, Node* next = nullptr, Node* before = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
	Node* before;
	/*
	~Node() {
		next = nullptr;
		before = nullptr;
	}*/
};

class List {
	friend ostream& operator <<(ostream& os, const List& list) {
		if (list.header->next != nullptr) {
			for (Node* p = list.header->next; p != list.trailer; p = p->next) {
				os << p->data << " ";
			}
		}
		return os;
	}
public:
	List(const List& rhs) {
		header = new Node();
		trailer = new Node();
		header->next = trailer;
		trailer->before = header;
		iterator ptr(trailer);
		for (List::iterator iter = rhs.begin(); iter != rhs.end(); ++iter) {
			insert(ptr, iter.where->data);
		}
	}
	List() {
		header = new Node();
		trailer = new Node();
		header->next = trailer;
		trailer->before = header;
		listSize = 0;
	};
	int front() const { return header->next->data; }
	int& front() { return header->next->data; }
	int back() const { return trailer->before->data; }
	int& back(){ return trailer->before->data; }
	size_t size() const { return listSize; }
	void push_back(int data) {
		Node* newNode = new Node(data);
		newNode->before = trailer->before;
		trailer->before->next = newNode;
		trailer->before = newNode;
		newNode->next = trailer;
		listSize++;
	}
	void push_front(int data) {
		Node* newNode = new Node(data);
		newNode->before= header;
		newNode->next = header->next;
		header->next->before = newNode;
		header->next = newNode;
		listSize++;
	}
	void pop_back() {
		if (listSize == 0) return;
		Node * pop = trailer->before;
		pop->before->next = trailer;
		trailer->before = pop->before;
		delete pop;
		--listSize;
	}
	void pop_front() {
		if (listSize == 0)return;
		Node* pop = header->next;
		pop->next->before = header;
		header->next = pop->next;
		delete pop;
		--listSize;
	}
	void clear() {
		for (size_t i = 0; i < listSize; ++i) {
			pop_back();
		}
		listSize = 0;
		header->next = trailer;
		trailer->before = header;
	}

	int& operator [] (size_t index){
		Node* ret=header->next;
		for (size_t i = 0; i < index; ++i) {
			ret = ret->next;
		}
		return ret->data;
	}
	int operator [](size_t index) const {
		Node* ret = header->next;
		for (size_t i = 0; i < index; ++i) {
			ret = ret->next;
		}
		return ret->data;
	}

	class iterator {
		friend List;
		friend bool operator!=(const iterator& lhs, const iterator& rhs) {
			return(lhs.where != rhs.where);
		}
		friend bool operator ==(const iterator & lhs, const iterator & rhs) {
			return (lhs.where == rhs.where);
		}
	public:
		iterator(Node * p) :where(p) {}
		iterator& operator++() {
			where = where->next;
			return *this;
		}
		iterator& operator--() {
			where = where->before;
			return *this;
		}

		int& operator*() {
			return where->data;
		}

		int operator*() const {
			return where->data;
		}

	private:
		Node* where;
	};
	iterator begin() { return iterator(header->next); }
	iterator end() { return iterator(trailer); }
	iterator begin()const { return iterator(header->next); }
	iterator end() const { return iterator(trailer); }
	iterator insert(iterator iter, int data) {
		Node* insertor = new Node(data);
		Node* before = iter.where->before;
		before->next = insertor;
		iter.where->before = insertor;
		insertor->before = before;
		insertor->next = iter.where;
		++listSize;
		return iterator(insertor);
	}
	iterator erase(iterator iter) {
		Node* after = iter.where->next;
		iter.where->before->next = after;
		after->before = iter.where->before;
		delete iter.where;
		listSize--;
		return after;
	}
	List& operator =(const List& rhs) {
		clear();
		iterator ptr(trailer);
		for (List::iterator iter = rhs.begin(); iter != rhs.end(); ++iter) {
			insert(ptr, iter.where->data);
		}
		return *this;
	}
	
	~List() {
		cout << "~List" << endl;
		Node* ptr = header;
		Node* next;
		while (ptr->next != nullptr) {
			next = ptr->next;
			delete ptr;
			ptr = next;
		}
		listSize = 0;
		delete trailer;
	}
	
private:
	size_t listSize;
	Node* header;
	Node* trailer;
};

// Task 1
void printListInfo(const List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList) {
	theList.front() = 17;
	theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
	for (size_t i = 0; i < myList.size(); ++i) {
		cout << myList[i] << ' ';
	}
	cout << endl;
}

// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";

	cout << "Modify the first and last items, and display the results\n";
	changeFrontAndBack(myList);
	printListInfo(myList);
	cout << "===================\n";

	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	//Task 2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";

	// Task 3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i * i);
	}
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";

	// Task 4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Now calling a function, printListSlow, to do the same thing\n";
	printListSlow(myList);
	cout << "Finally, for this task, using the index operator to modify\n"
		<< "the data in the third item in the list\n"
		<< "and then using printListSlow to display it again\n";
	myList[2] = 42;
	printListSlow(myList);


	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	// Note you can choose to nest the iterator class or not, your choice.
	//for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
	for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";

	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";

	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";

	// Task 8
	cout << "\n------Task Eight------\n";
	cout << "Copy control\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);
	cout << "Calling doNothing(myList)\n";
	doNothing(myList);
	cout << "Back from doNothing(myList)\n";
	printListInfo(myList);

	cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	List listTwo;
	for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i * i);
	printListInfo(listTwo);
	cout << "listTwo = myList\n";
	listTwo = myList;
	cout << "myList: ";
	printListInfo(myList);
	cout << "listTwo: ";
	printListInfo(listTwo);
	cout << "===================\n";
}
