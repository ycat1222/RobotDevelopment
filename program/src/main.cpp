#include "BeagleBone_Black.hpp"
#include <iostream>
#include <exception>

namespace BBB{
	//無限ループされながら実行される関数
	void run(void);
};


void BBB::run(void){
	
	
}


int main(void){

    try {
		while(true) BBB::run();
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
	catch(...){ }

    return 0;
}