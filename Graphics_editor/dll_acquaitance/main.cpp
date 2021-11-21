#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

#include "dynamic_library.hpp"

int (*sum)(int x, int y);

int main()
{
	void* handle = dlopen("./dynamic.so", RTLD_LAZY);
	sum = (int (*)(int, int))dlsym(handle, "num_sum");

	printf("%d\n", sum(10, 20));

	return 0;
}
