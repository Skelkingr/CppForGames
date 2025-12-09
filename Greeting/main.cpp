#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

// We make the function static so that its scope is limited to this file.
static bool IsName(const std::string& name)
{
	return std::all_of(std::begin(name), std::end(name), [](char c) { return std::isalpha(c); });
}

int main()
{
	std::string name = "";
	int age = 0;

	std::cout << "What is your name?" << std::endl;
	std::cin >> name;

	// No alphanum funky names allowed.
	while (!IsName(name))
	{
		std::cout << "ERROR: I expected a name." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> name;
	}

	std::cout << "What is your age?" << std::endl;
	std::cin >> age;

	// Valid numbers only
	while (std::cin.fail())
	{
		std::cout << "ERROR: I expected a number." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> age;
	}

	std::cout << "Hello, " << name;

	if (age < 25)
	{
		std::cout << ". You are only " << age << " years old." << std::endl;
	}
	else if (age < 50)
	{
		std::cout << ". You are already " << age << " years old." << std::endl;
	}
	else
	{
		std::cout << ". You are very wise for your age." << std::endl;
	}

	std::cout << "Press enter to exit..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}