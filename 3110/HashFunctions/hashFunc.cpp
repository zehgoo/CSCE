#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>

#define SIZE 10000
using namespace std;

class Bucket
{
private:
    int key = -1;
	string value = "";
	bool isEmpty = true;

public:
	Bucket(){}

    Bucket(int key, string value, bool isEmpty)
    {
        this->key = key;
        this->value = value;
        this->isEmpty = isEmpty;
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

    bool IsEmpty()
    {
        return isEmpty;
    }

};

class ClosedHash
{
private:
    vector<Bucket> bucketVec;

public:
    ClosedHash(){}    
   // Bucket bucket;

    // Used to track used indeces
    vector<int> indexVec;

    int Size()
    {
        return bucketVec.size();
    }

    void SetVectorCapacity(int size)
    {
        bucketVec.reserve (size);
    }

    void Indeces()
    {
        for (int i = 0; i < SIZE; i++)
            indexVec.push_back(i);
    }

    void MarkUsedIndex(int key)
    {
        indexVec.at(key) = -1;
        //cout << "Position: " << key << " in IndexVec is Marked" << endl;
    }

    int Hash1(int value)
    {
        float randNum = rand() % SIZE;
        float temp = randNum / value;

        int key;
        if (temp == 0)
        {
            key = temp;
            //MarkUsedIndex(key);
            return key;
        }
        
        key = ((temp < 1) && (temp > 0)) ? (ceil(temp * 100) / ceil(pow(temp , 2))) : ceil(temp);
        key = key % SIZE;

        return key;
        //bool isInserted = Insert(key,value);
        //cout << "Collision at Hash1" << endl;

        // while(!isInserted)
        // {
        //     key = Hash2(ceil(temp));
        //     isInserted = Insert(key, value);
        // }

        //cout << key << endl;
        // if (temp < 1)
        // {
        //     cout << "key: " << key << endl;  
        //     cout << "Temp: " << temp << endl;
        //     //cout << ceil(temp * 100) << endl;
        //     cout << "RandNum: " << randNum << " " << "Value Length: " <<  valueLength << endl;
        //     return -1;
        // }
        // return 0;
    }

    int Hash2(int key, int i)
    {
        int newKey = rand() % SIZE;
        //int P = 9979;
        //int newKey = (P - (key % P)) * i;

        //cout << "newKey: " << newKey << endl;
        
        return newKey;
    }

    bool Insert(int key, string& value)
    {
        if (indexVec.at(key) == -1)
        {
           // cout << indexVec.at(key) << endl;
            cout << key << ": collision ... rehashing" << endl;
            return false;
        }
        else
        {
            Bucket newBucket(key, value, true);
            bucketVec.at(key) = newBucket;
            MarkUsedIndex(key);
            cout << key << ": Sucess" << endl;
        }
        
        return true;
    }

    bool Remove(int key)
    {
        return true;
    }

    /*string*/ void FindValue(int key)
    {

        return;
    }

    void Display()
    {
        int count = 0;
        for(auto i : bucketVec)
        {
            if(i.Key() != -1)
            {
                cout << i.Value() << endl;
                count++;
            }
        }

        cout << "Count: " << count << endl;
    }

};


int main() 
{
    ClosedHash hash;
    hash.Indeces();
    hash.SetVectorCapacity(SIZE);
    
	srand(time(NULL));
	int key;
    int x = 0, i = 1;
    bool isInserted;

    ifstream readFile;
    string stringValue;
    
	readFile.open("fulldata");

	if(!readFile.fail())
	{
		readFile.ignore(256, '\n');
		while(!readFile.eof())
		{
			getline(readFile, stringValue);
            stringValue.pop_back();
            x = stringValue.length();
            key = hash.Hash1(x);
            isInserted = hash.Insert(key, stringValue);

            while(!isInserted)
            {
                key = (/*hash.Hash1(x) +*/ hash.Hash2(x, i));
                isInserted = hash.Insert(key, stringValue);
                i++;
            }
            // do
            // {
            //     key = (hash.Hash1(key) + hash.Hash2(key));
            // } while (!hash.Insert(key, stringValue));
            

            // (!hash.Insert(key, stringValue))
            // {
            //     key = (hash.Hash1(key) + hash.Hash2(key));
            //     hash.Insert(key, stringValue);
            // }
		}
	}

   //hash.Display();
   //cout << endl;
   cout << hash.Size() << endl;
	
	return 0;
}