#include "Database.h"
structura_fisiere str;
fisier_txt structura_fisiere::structura_tabele = fisier_txt("__Structura_tabele.txt");
int main(int argc, char*argv[])
{
    system("color 9f");
    try
    {
        str.executa_comenzi_initiale(argc, argv);
    }
    catch (db_exception e)
    {
        cout << endl << e.what() << endl << endl;
    }
    string comenzi;
    //int x;string** rez = str.fbin[0].citeste_binar(x);
    while (true)
    {
        try
        {
            getline(cin, comenzi);
            auto t1 = chrono::high_resolution_clock::now();
            if (comenzi != "")
            {
                executa_comanda(comenzi, str.db,str.fbin,str.nr_fbin,str.structura_tabele);
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