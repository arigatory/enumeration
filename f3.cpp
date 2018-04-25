#include<stdio.h>
const int LENGTH = 64;

class BinaryVector {

private:
	int n;
	int index;
	char *vector;	
public:
	BinaryVector() {
		n = LENGTH;
		index = 0;
		vector = new char[n+1];
		for (int i = 0 ; i < n; ++i) {
			vector[i]='0';
		}
		vector[n]='\0';
	}
	BinaryVector(int num) {
		n = LENGTH;
		index = 0;
		vector = new char[n+1];
		for (int i = 0 ; i < n; ++i) {
			vector[i]=num+'0';
		}
		vector[n]='\0';
	}
	BinaryVector(int num, char *v) {
		n = num;
		index = 0;
		vector = v;;
	}
	BinaryVector(const BinaryVector& bv) {
		n = LENGTH;
		vector = new char[n+1];
		for (int i=0; i<n; i++) vector[i] = bv.vector[i];
	}
	~BinaryVector() { if (vector != NULL) delete [] vector; }
	void print() {
		printf("%s\n", vector);
	}
	BinaryVector operator+(BinaryVector op2){

			
		char *temp = new char[n+1];
		for (int i = 0; i < n; ++i){
			temp[i] = vector[i]+op2.vector[i];
		}
		temp[n]='\0';
		return BinaryVector(n, temp);
	}

};
int C(int n, int k) {
	if (k > n) {
		return 0;
	}
	int r = 1;
	for (int d = 1; d <= k; ++d) {
		r *= n--;
		r /= d;
	}
	return r;
}

int N(int x,int y) {
	return C(x+y-2,y);
}
	
void Algorithm1(int n, int k, int num, int *K) {
	int t = n-k+1;
	int m = k;
	int Ns = N(t,m) + N(t+1, m-1) -1 - num;
	do {
		if (N(t,m) <= Ns) {
			K[k-m+1] = n - t - m + 2;
			Ns = Ns - N(t,m);
			m = m -1;	
		} else {
			t = t-1;
		}		
	} while (m != 0);
}

int PTB(int x, int y) {
	return C(x+y-2,y-1);
}
void Algorithm2(int n, int k, int num, int *K) {
	int t = n-k+1;
	int m = k;
//	int Ns = N(t,m) + N(t+1, m-1) -1 - num;
	do {
		if (PTB(t,m) <= num) {
			num = num - PTB(t,m);
			t = t - 1;
		} else {
			K[k-m+1]=n-m-t+2;
			m = m -1;
		}

	} while (m != 0);
}

void printArray(int *a, int size) {
	for (int i = 1; i < size; i++) {
		printf("%d",a[i]);
	}
	printf("\n");

}

void printReverse(int *a, int size) {
	for (int i = size - 1; i >=0; i--) {
		printf("%d",a[i]);
	}
	printf("\n");
}

int main() {
//	BinaryVector vect0, vect1(1), vect2(2);
//	vect1.print();
//	vect2.print();
//	vect0.print();
//	(vect0+vect2).print();
	int K[5];
	int vector[6];
	Algorithm2(6,4,0,K);
	printArray(K,5);
	return 0;
}

