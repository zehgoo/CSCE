#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>

#define SIZE 1000
using namespace std;

class Bucket
{
private:
    int key = -1;
	string value = "";

public:
	Bucket(){}

    Bucket(int key, string value)
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

class ClosedHash
{
private:
    vector<Bucket> bucketVec;

public:
    ClosedHash(){}    
    Bucket bucket;

    // Used to track used indeces
    vector<int> indexVec;
    int x = 0;

    int Size()
    {
        return bucketVec.size();
    }

    void SetBucketVecSize(int size)
    {
        bucketVec.resize(size);
    }

    void Indeces()
    {
        for (int i = 0; i < SIZE; i++)
            indexVec.push_back(i);
    }

    void MarkUsedIndex(int index)
    {
        indexVec.at(index) = -1;
        //cout << "Position: " << key << " in IndexVec is Marked" << endl;
    }

    int Hash(int value)
    {
        int key = ((rand() % SIZE) * value) % SIZE;

        return key;
    }

    int QuadraticProbe(int value)
    {
        int c1 = 1, c2 = 1;

        return ;
    }

    bool Insert(int key, string value)
    {
        int probed = 0;
        if (indexVec.at(key) == -1)
        {
           // cout << indexVec.at(key) << endl;
            cout << x << "\t" <<key << ": collision ... rehashing" << endl;
            return false;
        }
        else
        {
            Bucket newBucket(key, value);
            bucketVec.at(key) = newBucket;
            MarkUsedIndex(key);
            cout << x << "\t" << key << ": Sucess" << endl;
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
        int count2 = 0;
        for(auto i : bucketVec)
        {
            if(i.Key() != -100)
            {
                cout << i.Value() << endl;
                count++;
            }
            else
                count2++;
        }

        cout << "Count: " << count << endl;
        cout << "Count2: " << count2 << endl;
    }

};


int main() 
{
    ClosedHash hash;
    hash.Indeces();
    hash.SetBucketVecSize(SIZE);
    
	srand(time(NULL));
	int key;
    int newKey;
    int i = 0;
    int x;
    bool isInserted;

    ifstream readFile;
    string stringValue;
    
	readFile.open("data");

	if(!readFile.fail())
	{
		readFile.ignore(256, '\n');
		while(!readFile.eof())
		{
			getline(readFile, stringValue);
            x = stringValue.length();
            key = hash.Insert(x, stringValue);
           
		}
	}

   //hash.Display();
   //cout << endl;
   //cout << hash.Size() << endl;
	
	return 0;
}