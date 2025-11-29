# include <iostream>
using namespace std;

int main(){
char sender;
    for (sender = 'A'; sender <= 'D'; sender++)
    {
        int lie_count = 0;
        if ((sender != 'A') == false)
        {
            lie_count ++;
        }
        if ((sender == 'B') == false)
        {
            lie_count++;
        }
        if ((sender != 'B') ==false)
        {
            lie_count++;
        }
        if ((sender == 'C') == false)
        {
            lie_count++;
        }

        if (lie_count == 1)
        {
            cout << sender << endl;
            break;
        }
    }

    return 0;
}