#include <iostream>
#include <vector>
using namespace std;


class Shoe {

public:
    Shoe(){}
    Shoe(int size, string brand) {
        m_size = size;
        m_brand = brand;
    }

    void setBrand(){

    }

    // Virtual function
    void tieShoes(){
        cout << "You have tied your shoes" << endl;
    };

    //
    virtual int getSize(){
        return m_size;
    }

    //Pure virtual function
    virtual string getBrand() = 0;

protected:
    int m_size;
    string m_brand;

private:
    int isNotinChildClass;

};

class Sneakers : public Shoe {

public:
    Sneakers():Shoe(){};
    void run(){};

private:
    bool m_hasLaces;

};

int main(){

    return 0;
};


