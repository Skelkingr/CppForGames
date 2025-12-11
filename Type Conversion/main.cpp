#include <iostream>

int main()
{
	double d = 42.99;
	float f = static_cast<float>(d);
	int i = static_cast<int>(f);
	char c = static_cast<char>(i);
	bool b = static_cast<bool>(c);

	std::cout << d << std::endl;
	std::cout << f << std::endl;
	std::cout << i << std::endl;
	std::cout << c << std::endl;
	std::cout << b << std::endl;

	return 0;
}