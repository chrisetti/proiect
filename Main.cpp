#include <iostream>
#include <string>
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
            if (comenzi != "") executa_comanda(comenzi);
            cout << endl;
        }
        catch (db_exception e)
        {
            cout << endl << e.what() << endl << endl;
        }
    }
    return 0;
}