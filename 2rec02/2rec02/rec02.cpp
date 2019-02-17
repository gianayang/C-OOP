/*
02/08/2019
Recitation 02 for OOP
Forcus:
	structs,vectors and functions
Written by Giana Yang
*/


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Element {
	vector <string> name;
	int hydrogen;
	int carbon;
};

void openFile(ifstream& ifs);
void fill_in_list(vector<Element>& list, ifstream& file);
size_t find_elem(int hydro, int carbon, vector<Element>& list);
void sortElements(vector<Element>& list);
void display(const vector<Element>& list);


int main() {
	ifstream file;
	openFile(file);
	vector<Element> list;
	fill_in_list(list, file);
	sortElements(list);
	display(list);
	file.close();
}
void openFile(ifstream& ifs)
{
	string filename;
	cout << "filename:";
	cin >> filename;
	ifs.open(filename);
	while (!ifs) {
		cout << "failed to open" << endl;
		cout << "filename:";
		cin >> filename;
		ifs.clear();
		ifs.open(filename);
	}
}


void fill_in_list(vector<Element>& list, ifstream& file) {
	string name;
	char C;
	char H;
	int carbon;
	int hydrogen;
	while (file >> name >> C >> carbon >> H >> hydrogen) {
		size_t index = find_elem(hydrogen, carbon, list);
		if (index != list.size()) {
			list[index].name.push_back(name);
		}
		else {
			Element newElem;
			newElem.name.push_back(name);
			newElem.carbon = carbon;
			newElem.hydrogen = hydrogen;
			list.push_back(newElem);
		}
	}
}

size_t find_elem(int hydro, int carbon, vector<Element>& list) {
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i].carbon == carbon && list[i].hydrogen == hydro) {
			return i;
		}
	}
	return list.size();
}
void sortElements(vector<Element>& list) {
	Element swap;
	for (size_t i = 0; i < list.size(); ++i) {
		bool done = true;
		for (size_t j = 0; j < list.size() - 1 - i; ++j) {
			if (list[j].carbon > list[j + 1].carbon) {
				swap = list[j];
				list[j] = list[j + 1];
				list[j + 1] = swap;
				done = false;
			}
			else if (list[j].carbon == list[j + 1].carbon) {
				if (list[j].hydrogen > list[j + 1].hydrogen) {
					swap = list[j];
					list[j] = list[j + 1];
					list[j + 1] = swap;
					done = false;
				}
			}
			if (done)break;
		}
	}
}

void display(const vector<Element>& list) {
	for (size_t i = 0; i < list.size(); ++i) {
		cout << "C" << list[i].carbon << "H" << list[i].hydrogen << " ";
		for (size_t j = 0; j < list[i].name.size(); ++j) {
			cout << list[i].name[j] << " ";
		}
		cout << endl;
	}

}