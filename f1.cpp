//Ivan Panchenko
//Usage: ./a.out [x] where x is a vector of 0 and 1
#include <stdlib.h>
#include <stdio.h>
const int n = 8;
const int r = 3;

struct q_number {
	int num;
	int den;
	q_number(int a = 0, int b = 0) {num = a; den = b;}
	q_number operator+(q_number op2)
	{
		q_number res(num*op2.den+den*op2.num,den*op2.den);
		return res;
	}
	q_number operator*(q_number op2)
	{
		q_number res(num*op2.num,den*op2.den);
		return res;
	}
};

q_number contract(q_number a)
{
	for (int i = a.num; i > 1; i--){
		if (a.num % i == 0 && a.den % i == 0) {
			a.num /= i;
		   	a.den /= i;
		}
	}
	return a;
}

void print_bin(int*a)//prints binary array where a[0] = number of elements 
{
	for (int i = 1; i <= a[0]; i++){
		printf("%d",a[i]);
	}
	printf("\n");
}

int fac(int m)
{
	int res = 1;
	for (int i = m; i>1; i--)
		res *= i;
	return res;
}

int C(int n, int k)
{
	int res = 1;
	for (int i = n; i > n - k; i--)
			res *= i;
	return res/fac(k);
}

int code(int*a) 
{
	int res = 0;
	for (int i = 1; i < n; i++){
		int x = 0;
		for (int j = 1; j< i; j++)
			x += a[j];
		res += a[i]*C(n-i,r-x);
	//	printf("%d*(%d | %d)  +  ",a[i],N-i-1,r-x);
	}
	return res;
}

int ones(int* x,int k)
{
	int res = 0;
	for (int i = 1; i <= k; i++)
		res += x[i];
	return res;
}

int NS(int *x,int k)
{
	int res = C(n-k,r-ones(x,k));
	return res; 
}

q_number P(int *x,int k){
	q_number res;
	res.num = ((r-ones(x,k-1))*x[k]+(n-k+1-(r-ones(x,k-1)))*(1-x[k]));
	res.den = (n-k+1); 
	return res;
}

q_number q(int *x,int k)
{
	q_number res;
	res.num = x[k]*(n-k+1-r+ones(x,k-1));
	res.den = (n-k+1); 
	return res;
}

q_number ro(int s, int k, int* x)
{
	if (s == 0)
		if (k == 1)
			return P(x,1);
		else
			return P(x,k);
	else
		return contract(ro(s-1,2*k-1,x) * ro(s-1,2*k,x));	
}

q_number lambda(int s,int k,int* x)
{
	if (s == 0)
		if (k == 1)
			return q(x,1);
		else
			return q(x,k);
	else
		return contract(lambda(s-1,2*k-1,x)) + ro(s-1,2*k-1,x)*contract(lambda(s-1,2*k,x));	
}

int code1(int *x)
{
	int nu = 3;
	q_number res = lambda(nu,1,x);
	return res.num *C(n,3) /res.den;
}

void decode(int input, int* x)// x - array of n+1 element
{
	int S = C(n,r);
	q_number y1(n,S); 
	int c[r+1];
	int temp_n = 0;
	int res = 0;
	int j;
	for (int i = r; i > 0; i--){
		j = 0;
		temp_n = 0;
		while (temp_n <= input) {
			res = temp_n;
			temp_n = C(j,i);
			j++;
		}
		c[i] = j-1;
		input -= res;
	}
	for (int i = 1; i<=r; i++){
		x[n+1-c[i]] = 1;
	}

}

void decode1(int input, int* x)// x - array of n+1 element
{
	int c[r+1];
	int temp_n = 0;
	int res = 0;
	int j;
	for (int i = r; i > 0; i--){
		j = 0;
		temp_n = 0;
		while (temp_n <= input) {
			res = temp_n;
			temp_n = C(j,i);
			j++;
		}
		c[i] = j-1;
		input -= res;
	}
	for (int i = 1; i<=x[0]; i++){
		x[i] = 0;
	}
	for (int i = 1; i<=r; i++){
		x[x[0]+1-c[i]] = 1;
	}
}

int main(int argc, const char *argv[])
{
	int x[] = {n,0,1,0,0,0,1,0,1};
	if (argc > 1)
		for (int i = 1; i<=n; i++){
			x[i]=(argv[1][i-1]) - '0';
			printf("%d, ",x[i]);
		}
	print_bin(x);
	printf("%d\n",code(x));
	printf("%d\n",code1(x));
	q_number test = contract(lambda(3,1,x));
	printf("(%d/%d) \n",test.num,test.den);
	int y[] = {n,0,0,0,0,0,0,0,0};
	int z[33] ;
	z[0]=32;
	decode(21,y);
	decode1(30,z);
	print_bin(y);
}
