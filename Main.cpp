#include "Database.h"
structura_fisiere str;
fisier_txt structura_fisiere::structura_tabele = fisier_txt("__Structura_tabele.txt");
int main(int argc, char*argv[])
{
    system("color 02");
    cout << str.gandalf << endl;
    cout << str.gandalf_db << endl;
    cin.get();
    system("cls");
    system("color 9f");
    try
    {
        str.executa_comenzi_initiale(argc, argv);
        str.plateste_taxe();
    }
    catch (db_exception e)
    {
        cout << endl << e.what() << endl << endl;
    }
    string comenzi;
    while (true)
    {
        try
        {
            getline(cin, comenzi);
            auto t1 = chrono::high_resolution_clock::now();
            if (comenzi != "")
            {
                str.executa_comanda(comenzi);
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