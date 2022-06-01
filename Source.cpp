#include <iostream>
using namespace std;
#include <fstream>
#include <string>
int main() {
	ifstream inFile;
	string name;
	ofstream outFile;
	
	inFile.open("Text.txt");
	outFile.open("mem.txt");
	int j = 0;
	while (inFile.good()) {
		getline(inFile, name);
		for (int i = 9; i >= 2; i -= 2, j++)
		{
			string name_line = { name[i - 1],  name[i] };
			outFile << "mem[" << j << "] = 8'h" << name_line << ";" << endl;

		}
	}

	/*cout << "\nWriting in memory...\n";
	int i = 0;
	while (inFile.good()) {
		getline(inFile, name);
		i++;
	}*/









	return 0;
}