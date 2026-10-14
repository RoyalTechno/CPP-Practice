#include <iostream>
using namespace std;

string xorfunc(const char* a, const char* b){
        string result;
	int i = 0;
        while (a[i] != '\0' && b[i] != '\0'){
                result.push_back(a[i] ^ b[i]);
		i++;
        }
        return result;
}

void printbits(const string& word){
        cout << "String as bits:\n";
	
        for (char c : word) {
                for (int i=0; i<8; ++i){
                        if ( (c & 0b10000000) == 0b10000000){
				cout << "1";
			} else {
				cout << "0";
			}
                        c = c<<1;
                }
		cout << " ";
        }
	cout << "\n";
}

int main(int argc, char* argv[]){
	string result;

	if (argc == 2){
		string firstArg;
		getline(cin, firstArg);

		result = xorfunc(firstArg.c_str(),argv[1]);
	} else if (argc == 3){
                result = xorfunc(argv[1],argv[2]);
		printbits(result);
        } else {
		cerr << "Incorrect parameters\n";
                return -1;
	}

        cout << result;
        return 0;
}
