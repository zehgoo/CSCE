#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

#define SIZE 10000
using namespace std;

class Container
{
private:
    int key = -1;
	string value = "";

public:
	Container(){}

    Container(int key,string value)
    {
        this->key = key;
        this->value = value;
    }
    //Get Functions

    int Key()
    {
        return key;
    }
    string Value()
    {
        return value;
    }

};  

class OpenHash
{
private:
    vector<vector<Container>> table;

public:
    //Vector of vectors to performing chaining
    OpenHash()
    {
        table = vector<vector<Container>> (SIZE);
    }

    void SetTableCapacity(int size)
    {
        table.reserve(size);
    }

    int Hash(int value)
    {
        int key = ((rand() % SIZE) * value) % SIZE;

        return key;
    }

    bool Insert(int stringLength, string& value)
    {   
        int key = Hash(stringLength);
        Container newContainer(key, value);
        table[key].push_back(newContainer);

        return true;
    }

    // Removes values from the hash table
    bool Remove(int key)
    {
        bool keyFound = false;

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                if (table[i][j].Key() == key)
                {
			        keyFound = true;
                    table[i].erase(table[i].begin(), table[i].end());
                    return keyFound;
                }
            }
        }

        return keyFound;
    }
    // Finds Values inside the hashtable
    void FindValue(int key)
    {
        int count = 0;
        bool keyFound = false;

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                if (table[i][j].Key() == key)
                {
                    count++;
                    keyFound = true;
                    if (count == 1)
                        cout << "Value(s) for Key: " << key << " have been found. \n";
			        // Allows for cleaner formatting when outputting to the console
                    if (table[i].size() <= 1)
                    {
                        cout << table[i][j].Value() << endl;
                    }
                    else
                    {
                        (j == table[i].size() - 1) ? cout << table[i][j].Value() : cout << table[i][j].Value() << " -> ";
                    }
                }

            }
        }
        cout << endl;
        if (!keyFound)
            cout << "Value(s) for key: " << key << " have not been found." << endl;
    }

    void Display()
    {
        for (int i = 0; i < table.size(); i++) 
        {
			cout << i;
		    for (int j = 0; j < table[i].size(); j++)
			    cout << " -> " << table[i][j].Value();
			cout << endl;
		}
    }
};


int main()
{
    OpenHash hash;
    hash.SetTableCapacity(SIZE);

    ifstream readFile;
    string stringValue;

    srand(time(NULL));
    
	readFile.open("data10000");

	if(!readFile.fail())
	{
        int key, x = 0;
        int count = 0;
		readFile.ignore(256, '\n');
		while(!readFile.eof())
		{
			getline(readFile, stringValue);
            x = stringValue.length();
            hash.Insert(x, stringValue);
		}
	}

    int key = rand() % SIZE;
    bool keyRemoved = false;

    hash.Display();
    hash.FindValue(key);
    keyRemoved = hash.Remove(key);

    if(keyRemoved)
        cout << "Value(s) for Key: " << key << " have been removed" << endl;
    else
        cout << "Value(s) for Key: " << key << " have not been removed" << endl;


   // hash.Display();
    return 0;
}