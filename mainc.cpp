#include <iostream>
#include <unistd.h>
int main(){
	int a = 10;
	while(true){
		usleep(10000000);
		std::cout << a << std::endl;
	}
	return 0;
}
