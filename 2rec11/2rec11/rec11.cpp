/*
  Recitation 11: Linked List Basics
  Written by Giana Yang
  04/19/2019
*/

#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

void splice(Node* target, Node* addList) {
	Node* lastNode = addList;
	Node* after = target->next;
	while (lastNode->next != nullptr) {
		lastNode = lastNode->next;
	}
	target->next = addList;
	lastNode->next = after;
}

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
	while (headPtr) {
		Node* next = headPtr->next;
		delete headPtr;
		headPtr = next;
	}
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listAddHead(result, vals[index - 1]);
	}
	return result;
}

Node* isSublist(Node*& target, Node*& headPtr) {
	Node* walker = headPtr;
	Node* miniwalker1 = nullptr;
	Node* miniwalker2 = target;
	Node* starter = nullptr;
	while (walker != nullptr && miniwalker2 != nullptr) {
		if (walker->data == miniwalker2->data) {
			miniwalker1 = walker;
			starter = walker;
			while (miniwalker1 != nullptr && miniwalker2 != nullptr) {
				if (miniwalker1->data == miniwalker2->data) {
					miniwalker1 = miniwalker1->next;
					miniwalker2 = miniwalker2->next;
				}
				else {
					starter = nullptr;
					miniwalker2 = target;
					break;
				}
			}
		}
		walker = walker->next;
	}
	if (miniwalker1 == nullptr && miniwalker2 != nullptr) {
		starter = nullptr;
	}
	return starter;
}

void listAddAfter(Node* prior, Node* add) {
	prior->next = add;
}

const Node* sharedListBruteForce(const Node* list1, const Node* list2) {
	while (list1) {
		const Node* runner = list2;
		while (runner) {
			if (list1 == runner) return list1;
			runner = runner->next;
		}
		list1 = list1->next;
	}
	return nullptr;
}

const Node* sharedListUsingSet(const Node * list1, const Node * list2) {
	unordered_set<const Node*> stuff;
	while (list1) {
		stuff.insert(list1);
		list1 = list1->next;
	}
	while (list2) {
		if (stuff.find(list2) != stuff.end()) {
			return list2;
		}
		list2 = list2->next;
	}
	return nullptr;
}
//
//Node* sharedListUsingSet(){}

const Node* sharedListUsingSet2(const Node* list1, const Node* list2) {
	int num = 0;
	int num1 = 0;
	const Node* runner1 = list1;
	const Node* runner2 = list2;
	while(runner1) {
		runner1 = runner1->next;
		num++;
	}
	while (runner2) {
		runner2 = runner2->next;
		num1++;
	}
	if (num > num1) {
		for (size_t i = 0; i < (num - num1); ++i) {
			list1 = list1->next;
		}
	}
	if (num1 > num) {
		for (size_t i = 0; i < (num1 - num); ++i) {
			list2 = list2->next;
		}
	}
	while (list1) {
		if (list1 == list2) return list1;
		list1 = list1->next;
		list2 = list2->next;
	}
	return nullptr;
}

void displayWholeList(Node*& headPtr) {
	Node* runner = headPtr;
	while (runner!= nullptr) {
		cout << runner->data << " ";
		runner = runner->next;
	}
	cout << endl;
}

void displayWholeList(const Node*& headPtr) {
	const Node* runner = headPtr;
	while (runner != nullptr) {
		cout << runner->data << " ";
		runner = runner->next;
	}
	cout << endl;
}

int main() {
	Node* list1 = listBuild({ 5,7,9,1 });
	Node* list2 = listBuild({ 6,3,2 });
	cout << "Part One: " << endl;
	cout << "L1: ";
	displayWholeList(list1);
	cout << "L2: ";
	displayWholeList(list2);

	cout << "Target: ";
	displayWholeList(list1->next);
	cout << "Splicing L2 at target in L1" << endl;
	splice(list1->next, list2);
	cout << "L1: ";
	displayWholeList(list1);
	cout << "L2: ";
	displayWholeList(list2);
	cout << "========================" << endl;
	cout << "Part Two: " << endl;
	cout << "Target: ";
	Node* list3 = listBuild({ 1,2,3,2,3,2,4,5,6 });
	displayWholeList(list3);
	Node* list4 = listBuild({ 1 });
	Node* subNode = isSublist(list4, list3);
	cout << "Attempt match: ";
	displayWholeList(list4);
	if (subNode != nullptr) {
		displayWholeList(subNode);
	}
	else if (subNode==nullptr){
		cout << "Failed to match" << endl;
	}

	Node* list5 = listBuild({ 3,9 });
	Node* subNode1 = isSublist(list5, list3);
	cout << "Attempt match: ";
	displayWholeList(list5);
	if (subNode1 != nullptr) {
		displayWholeList(subNode1);
	}
	else {
		cout << "Failed to match" << endl;
	}

	Node* list6 = listBuild({ 2,3 });
	Node* subNode2 = isSublist(list6, list3);
	cout << "Attempt match: ";
	displayWholeList(list6);
	if (subNode2 != nullptr) {
		displayWholeList(subNode2);
	}
	else {
		cout << "Failed to match" << endl;
	}

	Node* list7 = listBuild({ 2,4,5,6 });
	Node* subNode3 = isSublist(list7, list3);
	cout << "Attempt match: ";
	displayWholeList(list7);
	if (subNode3 != nullptr) {
		displayWholeList(subNode3);
	}
	else {
		cout << "Failed to match" << endl;
	}

	Node* list8 = listBuild({ 2,3,2,4 });
	Node* subNode4 = isSublist(list8, list3);
	cout << "Attempt match: ";
	displayWholeList(list8);
	if (subNode4 != nullptr) {
		displayWholeList(subNode4);
	}
	else {
		cout << "Failed to match" << endl;
	}

	Node* list9 = listBuild({ 5,6,7 });
	Node* subNode5 = isSublist(list9, list3);
	cout << "Attempt match: ";
	displayWholeList(list9);
	if (subNode5 != nullptr) {
		displayWholeList(subNode5);
	}
	else {
		cout << "Failed to match" << endl;
	}




	cout << "\nPart three (Brute Force) :\n";

	Node* commonNode = new Node(4, new Node(5));
	Node* list14 = new Node(2, new Node(3, commonNode));
	Node* list15 = new Node(2, new Node(3, new Node(3, commonNode)));
	cout << "L1: ";
	displayWholeList(list14);
	cout << "L2: ";
	displayWholeList(list15);
	cout << "Common Node: ";
	const Node* result = sharedListBruteForce(list14, list15);
	displayWholeList(result);

	cout << "\nPart three (with set) :\n";

	Node* commonNode1 = new Node(4, new Node(5));
	Node* list16 = new Node(2, new Node(3, commonNode1));
	Node* list17 = new Node(2, new Node(3, new Node(3, commonNode1)));
	cout << "L1: ";
	displayWholeList(list16);
	cout << "L2: ";
	displayWholeList(list17);
	cout << "Common Node: ";
	const Node* result1 = sharedListUsingSet2(list16, list17);
	displayWholeList(result1);

	cout << endl;


}