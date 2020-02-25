#include <fstream>
#include <iostream>

bool openFile(ifstream& file, string fileName)
{
	file.open(fileName);
	if (file.is_open())
		return true;
	else
	{
		return false;
	}
}

int main()
{
	const string FILE_IN_NAME = "input.txt";
	ifstream fileForWork;
	openFile(fileForWork, FILE_IN_NAME);


	fileForWork.close();
}
