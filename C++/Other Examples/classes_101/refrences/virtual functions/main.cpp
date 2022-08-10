#include <iostream>
#include <string>

#include <vector>

using namespace std;
class Tool{

public:
    Tool(string name, double weight){m_name = name; m_weight = weight;}
    virtual string GetName() = 0;

    virtual double GetWeight() = 0;

    virtual void Use(){cout << m_name << " is used." << endl;}

protected:

    string m_name;

    double m_weight;

};


class Hammer: public Tool{

public:

    Hammer(string name, double weight):Tool(name, weight){}

    string GetName(){return "A large " + m_name + " is here.";}


    double GetWeight(){return m_weight;}

    void Use(){cout << m_name << " hammers gracefully." << endl;}

};



class Screwdriver: public Tool{

public:

    Screwdriver(string name, string tipType, double weight) :Tool(name, weight){ m_tipType = tipType;}

    string GetName(){return "A " + m_tipType + " " + m_name + " screwdriver is here.";}

    double GetWeight(){return m_weight;}

    void Use(){cout << m_name << " tightens the screw." << endl;}

private:

    string m_tipType;

};

int main () {

    vector<Tool*> myTools;

    Tool* myHammer = new Hammer("Ball-peen", 21.5);

    Tool* myScrew = new Screwdriver("Snap-on", "Torx", 0.75);

    myTools.push_back(myHammer);

    myTools.push_back(myScrew);

    for(int i = 0; i < 2; i++) {

        cout << myTools.at(i)->GetName() << endl;

        myTools.at(i)->Use();

    }

    for(int i = 0; i < 2; i++){



        delete &myTools.at(i);



    }



    return 0;



}