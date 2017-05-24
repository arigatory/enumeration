// Ivan Panchenko
// Usage: ./a.out [n] where n - is a number to decode to vector
#include <stdio.h>
#include <stdlib.h>
int n = 8;
int r = 3;

void printb(unsigned int num)
{
	for(int i=sizeof(num)*8-1; i>=0; --i){
		if (i<n)
			printf("%d", num&(1<<i)?1:0);
	}
	printf("\n");

}

int main(int argc, char *argv[]) {
	unsigned int v=7; // current permutation of bits
	unsigned int w; // next permutation of bits
	unsigned int t = v | (v - 1); // t gets v's least significant 0 bits set to 1
// Next set to 1 the most significant bit to change,
// set to 0 the least significant ones, and add the necessary 1 bits.
    	//unsigned int t = (v | (v - 1)) + 1;
    	//w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
//	printf("%x  %x\n",v,w);
	int input = 21;
	if (argc > 1)
		input = atoi(argv[1]);
	if (input == 0){
		printb(v);
		return 0;
	}
    	for (int j = 1; j <= input; j++) {
		w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
		v = w;
		t = v | (v - 1); // t gets v's least significant 0 bits set to 1
	}
	printb(w);
	return 0;
}
