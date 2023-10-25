#include "User.h"
#include <iostream>

int main()
{
	std::vector<std::pair<int, int>>vect;
	vect.push_back(std::make_pair(2, 2));
	User a = User(1, "Andrei", vect, 2.3);
	a.setId(2);
	std::cout<<a.getId();
}