#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class ClosedHash
{
public:

	vector<string> bucket;

	ClosedHash()
	{
		bucket.reserve(100);
	}
	
	void MidSquareHash(string key)
	{

		int keyLength = key.length();
		//cout << keyLength << endl;
		//cout << key << endl;

		int R;

		if (bucket.empty())
		{
			R = 1;
		}
		else
		{
			R = ceil(log10(bucket.capacity()));
		}
		
		//cout << "R: " << R << endl;
		int keySquared = pow(keyLength, 2);

		//string keySquaredStr = to_string(keySquared);
		int leftDigits = (keySquared - R) / 2;
		cout << leftDigits << endl;
		//string extractedDigits = keySquaredStr.substr(leftDigits, keySquaredStr.length() - (leftDigits * 2));

		//cout << stoi(extractedDigits) % bucket.capacity() << endl;
		// int position = key * key;
		// string positionString = to_string(position);
		// int removeDigits = (positionString.length() - R) / 2;
		// positionString = positionString.substr(removeDigits, positionString.length() - (removeDigits * 2));

		//return stoi(positionString) % size;
	}

	// string findItem(int key)
	// {
	// 	return;
	// }

	void insertItem(string value)
	{
		//bool isValInserted = false;

		//int i = MidSquareHash(key)
		bucket.push_back(value);
		//isValInserted = true;
		//return isValInserted
	}

	// bool removeItem(int key)
	// {

	// 	return;
	// }

	~ClosedHash(){}
};



int main()
{
	ClosedHash hashTable;
	string lastName, firstName;
	ifstream readFile;

	readFile.open("data");

	if(!readFile.fail())
	{
		readFile.ignore(256, '\n');
		while(!readFile.eof())
		{
			getline(readFile, lastName, ',');
			getline(readFile, firstName);

			firstName.pop_back();

			hashTable.MidSquareHash(firstName);
			//break;

			hashTable.insertItem(lastName);
		}
	}

	//cout << hashTable.bucket.size() << endl;

	// for (auto x : hashTable.bucket)
	// {
	// 	cout << x << '\n';
	// }

/*
get length of string and pass it to hashing func (midsquare10)


	return 0;
*/
}