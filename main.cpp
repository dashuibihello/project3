#include<iostream>
#include<string>
#include<fstream>
#include"Polynomial.h"

void openfile(map<string, polynomail> &goods);
void closefile(map<string, polynomail> &goods);

int main() {
	map<string, polynomail> save;
	openfile(save);
	welcome();
	maininterface(save);
	closefile(save);
	return 0;
}

void openfile(map<string, polynomail> &goods) {
	ifstream fin("save.txt");
	int num;
	fin >> num;
	for (int a = 0; a < num; a++) {
		string name;
		polynomail poly(1);
		int size, index;
		double coeff;
		fin >> name >> size;
		for (int a = 0; a < size; a++) {
			fin >> index >> coeff;
			poly.pol.insert(pair<int, double>(index, coeff));
		}
		goods.insert(pair<string, polynomail>(name, poly));
	}
	fin.close();
}

void closefile(map<string, polynomail> &goods) {
	ofstream fout("save.txt");
	fout << goods.size() << endl;
	map<string, polynomail> ::iterator iter;
	if (!goods.empty())
		for (iter = goods.begin(); iter != goods.end(); ++iter) {
			fout << iter->first << " " << iter->second.pol.size() << " ";
			map<int, double>::iterator it;
			for (it = iter->second.pol.begin(); it != iter->second.pol.end(); ++it) {
				fout << it->first << " " << it->second << " ";
			}
			fout << endl;
		}
	fout.close();
}
