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
    //test
    
    persoana_fizica p1("", "Ronaldo", 5000);
    persoana_juridica p2("123", "Becali", 5000);
    firma f("strada gladiolelor 45", "Dove", 5000);
    platitor_tva* pv[] = { &p1,&p2,&f };
    cout << pv[0]->calcul_tva() << ' ' << pv[0]->calcul_restanta(6) << endl;
    cout << pv[1]->calcul_tva() << ' ' << pv[1]->calcul_restanta(6) << endl;
    cout << pv[2]->calcul_tva() << ' ' << pv[2]->calcul_restanta(6) << endl;

    //test
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