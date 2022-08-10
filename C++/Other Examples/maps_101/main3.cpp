/*Title: map2.cpp
        Author: CMSC 202
Date: 10/22/2019
Description: This is an example of using the map STL in C++.
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main () {
    multimap<string, int> mapOfWords;
    mapOfWords.insert(make_pair("earth" , 1));
    mapOfWords.insert(make_pair("moon" , 2));
    //  mapOfWords["sun"] = 3;
    //mapOfWords["earth"] = 4;
    //mapOfWords["jupiter"] = 5;
    mapOfWords.insert(make_pair("earth", 5));

    multimap<string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end()){
        cout << it->first << " :: " << it->second << endl;
        it++;
    }

    if(mapOfWords.find("sun") != mapOfWords.end())
        cout << "word sun found" << endl;

    if(mapOfWords.find("mars") == mapOfWords.end())
        cout << "Word mars not found" << endl;

    return 0;
}
