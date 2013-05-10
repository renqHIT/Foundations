#include <iostream>
#include <string>
#include <ext/hash_map>

using namespace std;

unsigned int hashfunc(const string label)
{
	unsigned int hash = 5381;
	int c;
	for( unsigned int i = 0; i < label.size(); i++)
	{
		c = label[i];
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

int main()
{



	return 0;
}
