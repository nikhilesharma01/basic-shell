#include <stdio.h>

long safe_load(long *p) {
	static const long val = -1;
	return *(p ? p : &val);
}

int main(){
	long x = 2;
	printf("%ld\n", safe_load(&x));
	return 0;
}

/*
Assume val is in %rdx

safe_load:
	movl 4(%esp), %eax
	movl %rdx, %edx
	testl %eax, %eax
	cmove %edx, %eax
	movl (%eax), %eax
	ret
*/