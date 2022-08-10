#include <iostream>
using namespace std;

int everyTenth(int start, int finish){

    if (start == finish)
        return finish;
    int sum = 0;
    if (start < finish){
        for (int i = start; i <= finish; i+=10){
            sum += i;
        } // end of for loop

        return sum;
    } // end of if (start < finish)

    else {
        for (int i = finish; i <= start; i+=10){
            sum += i;
        } // end of for loop

        return sum;
    } // End of else

} // End of everytenth

int main() {

    cout << everyTenth(63,85) << endl;
    cout << everyTenth(215,195) << endl;
    cout << everyTenth(-21,-1) << endl;
    cout << everyTenth(10,10) << endl;

    return 0;

}
