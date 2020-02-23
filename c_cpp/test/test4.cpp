#include <stdio.h>

class test{
public :
	void out(){
	printf("test test");
	}
};

int main(char*args []){
	test t;
	t.out();
	getchar();
	return 0;
}