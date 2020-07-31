#include <iostream>
// #include <ctime> // раскомментируйте, если используете Code::Blocks
#include <random> // для std::random_device и std::mt19937
#include <string>

using namespace std;
const int WIDTH = 2;
const int HEIGHT = 3;
void map (string str[]) {
	for (int i = 0; i < WIDTH; i++) {
		cout << str[i];
	}
}



int main()
{
	string str[WIDTH] = { "dsf", "asd"};
	map(str);
}