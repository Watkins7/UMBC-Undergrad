#include <iostream>
#include <map>
using namespace std;
void  recFunc(char arrChar[], int arrInt[], int arrSize, map<char, int>& aMap)
{


    for (int i = 0; i < arrSize; i++) {

        aMap.insert( pair<char,int>( arrChar[i],arrInt[i] ));

    }



}

int main()
{
    const int arraySize = 3;
    char arrayChar[arraySize]={'a','b','c'};
    int arrayInt[arraySize]={1, 2, 3};
    map<char, int> result;
    recFunc(arrayChar, arrayInt, arraySize, result);
    for (map<char,int>::iterator it = result.begin(); it != result.end(); ++it)
        cout << it->first << " => " << it->second << endl;
//The expected output is:
// a => 1
// b => 2
// c => 3
    return 0;
}
