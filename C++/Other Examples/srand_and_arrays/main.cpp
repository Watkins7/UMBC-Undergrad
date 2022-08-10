#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
const int MAX1 = 1000;
const int MIN1 = 500;

int main() {

    // Rand/srand example
    srand(time(NULL));
    for (int i = 0; i < 10;i++){
        cout << (rand() % (MAX1 - MIN1) + 1 + MIN1 ) << endl;
    } //+1 needed to get to 1000


    // Array example
    int num = 0;
    int sum = 0;

    cout << "How many grades do you want to enter?:" << endl;
    cin >> num;

    int numbers[num];

    for (int i = 0; i < num; i++){
        cout << "Enter a score " << i + 1 << endl;
        cin >> numbers[i];
        sum += numbers[i];
    }

    cout << "Your average score was " << double(sum) / num << endl;

    return 0;

}
