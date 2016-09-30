#include <iostream>

#include <concurrency/kernel.h>

/*
	Each thread has a worker object
*/

int main(int argc, char* argv[])
{
	sandcastle::concurrency::kernel::get().init();
	sandcastle::concurrency::kernel::get().launch_main_worker();
}