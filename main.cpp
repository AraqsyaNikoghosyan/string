#include "string.h"
#include <iostream>
int main() {
	String ob1;
	String ob2("I love programming");
	ob2.append("!!!");
	ob2.insert('_', 5);
	std::cout << ob1.empty() << std::endl;
	std::cout << ob2.empty() << std::endl;
	ob1 = "hello, ";
	ob1.print();
	ob2.print();
	std::cout << ob2[4] << std::endl;
	String ob3("how are");
	String ob4(" you?");
	String ob5 = ob3 + ob4;
	ob5.print();
	return 0;
}
