#include <iostream>
#include <random>
#include <string>

using namespace std;

class simpleRand {
	private:
		int state;
	public:
		simpleRand(int seed) : state(seed) { }
		int getNum(){
			state = (state * 1103515245 + 12345) % (1U << 31);
			return state;
		}
};

int main(int argc,char* argv[]){
	if (argc != 2){
		cerr << "Provide a starting seed";
	}
	int seed = stoi(argv[1]);	
	simpleRand gen1(seed);	
	minstd_rand0 gen2(seed);
	
	for(int i=0; i<10; ++i){
		cout << gen1.getNum() << "   " << gen2() << "\n";
	} 
	
	return 0;
}
