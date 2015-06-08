#include <iostream>

using namespace std;

//atributes
float x;
float y;
float d;

void debug(char* argv[])
{
	cout << "argv[0][0]: " << argv[0][0] << endl;
	cout << "argv[0][1]: " << argv[0][1] << endl;
	cout << "argv[0][2]: " << argv[0][2] << endl;
	cout << "argv[1][0]: " << argv[1][0] << endl;
	cout << "argv[1][1]: " << argv[1][1] << endl;
	cout << "argv[1][2]: " << argv[1][2] << endl;
	cout << "argv[2][0]: " << argv[2][0] << endl;
	cout << "argv[2][1]: " << argv[2][1] << endl;
	cout << "argv[2][2]: " << argv[2][2] << endl;
}

int main(int argc, char* argv[])
{
	//debug(argv);
	for(int i = 0; i < 10; i++)
		cout << "I am alive";
		

	if (argv [1][0] == 'r') //color = red
	{
		x = 20;
		y = 40;
		d = 15;
	}
	else if (argv[1][0] == 'b') //color = blue
	{
		x = 100;
		y = 80;
		d = 40;
	}
	else //invalid input
	{
		cout << "nogo" << endl;
		return -1;
	}
	cout << x;
	cout << y;
	cout << d;
	return 0;
}