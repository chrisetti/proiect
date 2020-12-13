#include <iostream>
#include <string>
#include <chrono>
#include "Database.h"
using namespace std;
int main()
{
    //database db();
    string comenzi;
    while (true)
    {
        try
        {
            getline(cin, comenzi);
            auto t1 = chrono::high_resolution_clock::now();
            if (comenzi != "")
            {
                executa_comanda(comenzi);
                auto t2 = chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
                cout << "Comanda s-a executat in " << (float)duration / 1000000 << " secunde" << endl;
            }
            cout << endl;
        }
        catch (db_exception e)
        {
            cout << endl << e.what() << endl << endl;
        }
    }
    return 0;
}