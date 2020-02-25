#include <fstream>
#include <iostream>

using namespace std;

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

int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		string FILE_IN_NAME = argv[1];
		ifstream fileForWork;
		openFile(fileForWork, FILE_IN_NAME);
	
		fileForWork.close();
	

		string FILE_OUT_NAME = argv[2];
		ofstream fout(FILE_OUT_NAME);
	}

}
