#include <iostream>
#include "Database.h"
#include <regex>
#pragma warning(disable:4996)
//initializare constructori clasa db_exception
db_exception::db_exception() :exception("Comanda invalida") {}
db_exception::db_exception(const char* message) : exception(message) {}
column::column()
{

}

column::column(string nume, int dimensiune, tip Tip, string valoare_implicita)
{
	this->nume = nume;
	this->dimensiune = dimensiune;
	this->Tip = Tip;
	this->valoare_implicita = valoare_implicita;
}

row::row()
{
	valori_rand = nullptr;
	nr_coloane = 0;
}

row::row(string* valori_rand, int nr_coloane)
{
	if (valori_rand != nullptr && nr_coloane > 0)
	{
		this->nr_coloane = nr_coloane;
		this->valori_rand = new string[nr_coloane];
		for (int i = 0; i < nr_coloane; i++)
		{
			this->valori_rand[i] = valori_rand[i];
		}
	}
}

row::row(const row& r)
{
	if (r.valori_rand != nullptr && r.nr_coloane > 0)
	{
		this->nr_coloane = r.nr_coloane;
		this->valori_rand = new string[r.nr_coloane];
		for (int i = 0; i < r.nr_coloane; i++)
		{
			this->valori_rand[i] = r.valori_rand[i];
		}
	}
}

row& row::operator=(const row& r)
{
	if (valori_rand != nullptr)
	{
		delete[] valori_rand;
	}
	if (r.valori_rand != nullptr && r.nr_coloane > 0)
	{
		this->nr_coloane = r.nr_coloane;
		this->valori_rand = new string[r.nr_coloane];
		for (int i = 0; i < r.nr_coloane; i++)
		{
			this->valori_rand[i] = r.valori_rand[i];
		}
	}
	return *this;
}
row::~row()
{
	if (valori_rand != nullptr)
	{
		delete[] valori_rand;
	}
}

table::table()
{
	coloane = nullptr;
	nr_coloane = 0;
	randuri = nullptr;
	nr_randuri = 0;
}

table::table(column* coloane, int nr_coloane, row* randuri, int nr_randuri)
{
	
	if (coloane != nullptr && nr_coloane > 0)
	{
		this->nr_coloane = nr_coloane;
		this->coloane = new column[nr_coloane];
		for (int i = 0; i < nr_coloane; i++)
		{
			this->coloane[i] = coloane[i];
		}
	}
	if (randuri != nullptr && nr_randuri > 0)
	{
		this->nr_randuri = nr_randuri;
		this->randuri = new row[nr_randuri];
		for (int i = 0; i < nr_randuri; i++)
		{
			this->randuri[i] = randuri[i];
		}
	}

}

table::table(const table& t)
{
	if (t.coloane != nullptr && t.nr_coloane > 0)
	{
		this->nr_coloane = t.nr_coloane;
		this->coloane = new column[t.nr_coloane];
		for (int i = 0; i < t.nr_coloane; i++)
		{
			this->coloane[i] = t.coloane[i];
		}
	}
	if (t.randuri != nullptr && t.nr_randuri > 0)
	{
		this->nr_randuri = t.nr_randuri;
		this->randuri = new row[t.nr_randuri];
		for (int i = 0; i < t.nr_randuri; i++)
		{
			this->randuri[i] = t.randuri[i];
		}
	}
}

table&table::operator=(const table& t)
{
	if (coloane != nullptr)
	{
		delete[] coloane;
	}
	if (randuri != nullptr)
	{
		delete[] randuri;
	}
	if (t.coloane != nullptr && t.nr_coloane > 0)
	{
		this->nr_coloane = t.nr_coloane;
		this->coloane = new column[t.nr_coloane];
		for (int i = 0; i < t.nr_coloane; i++)
		{
			this->coloane[i] = t.coloane[i];
		}
	}
	if (t.randuri != nullptr && t.nr_randuri > 0)
	{
		this->nr_randuri = t.nr_randuri;
		this->randuri = new row[t.nr_randuri];
		for (int i = 0; i < t.nr_randuri; i++)
		{
			this->randuri[i] = t.randuri[i];
		}
	}
	return *this;
}

table::~table()
{
	if (coloane != nullptr)
	{
		delete[] coloane;
	}
	if (randuri != nullptr)
	{
		delete[] randuri;
	}
}

string toUpper(string cuvant)
{
    for (int i = 0;i < cuvant.size();i++)
        cuvant[i] = toupper(cuvant[i]);
    return cuvant;
}

int get_nr_cuvinte_string(string str)
{
    char* c = new char[str.size() + 1];
    strcpy_s(c, str.size() + 1, str.c_str());
    int nr_cuvinte = 0;
    char* token = strtok(c, " ,()=");
    while (token)
    {
        if (token[0] == '\'')
        {
            while (token[strlen(token) - 1] != '\'') token = strtok(NULL, " ,()=");
        }
        nr_cuvinte++;
        token = strtok(NULL, " ,()=");
    }
    if (c) delete[]c;
    return nr_cuvinte;
}

string* impartire_comenzi_pe_cuvinte(string comenzi)
{
    int index = 0;
    int nr_cuvinte = get_nr_cuvinte_string(comenzi);
    string* cuvinte = new string[nr_cuvinte];

    for (int i = 0; i < comenzi.length(); i++)
    {
        char c = comenzi[i];
        if (!isalnum(c) && c != '.' && cuvinte[index] != "") index++;
        else if (c == '\'')
        {
            i++;
            while (comenzi[i] != '\'') { cuvinte[index] += comenzi[i];i++; }
        }
        else if (isalnum(c) || c == '.')cuvinte[index] += c;
    }
    return cuvinte;
}

void capitalizare_comenzi(string*& comenzi, int nr_cuvinte)
{
    for (int i = 0;i < nr_cuvinte;i++)
        comenzi[i] = toUpper(comenzi[i]);
}

void numara_paranteze(string comenzi)
{
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0;i < comenzi.size();i++) 
    {
        if (comenzi[i] == '(') cnt1++;
        else if (comenzi[i] == ')') cnt2++;
    }
    if (cnt1 != cnt2) throw db_exception("Numar incorect de paranteze");
}

void verificare_regex(string comenzi)
{
    string sp0 = "[[:s:]]*";
    string sp1 = "[[:s:]]+";
    string sp01 = "[[:s:]]?";
    string w0 = "[[:w:]]*";
    string w1 = "[[:w:]]+";
    string d0 = "[[:d:]]*";
    string d1 = "[[:d:]]+";
    string caracter = "(.*)";
    string nr_intreg = sp0 + d1 + sp0;
    string nr_real = sp0 + d1 + "\\." + d0 + sp0;
    string grup_cuvinte = "(" + sp0 + caracter + sp0 + ")+";
    string text = "'" + grup_cuvinte + "'";
    string valori = "((" + nr_intreg + ")|(" + nr_real + ")|(" + text + "))";

    //create_table
    string regex_coloana = "(\\(" + sp0 + w1 + sp0 + "," + sp0 + w1 + sp0 + "," + sp0 + d1
        + sp0 + "," + sp0 + valori + sp0 + "\\))";
    string regex_if_not_exists = "(" + sp1 + "if" + sp1 + "not" + sp1 + "exists" + sp0 + ")?";
    string regex_create_table = sp0 + "create" + sp1 + "table" + sp1 + w1 + regex_if_not_exists + sp0;
    string regex_create_table_2 = "\\(" + sp0 + regex_coloana + sp0 + "(" + sp0 + "," + sp0 + regex_coloana + sp0 + ")*" + "\\)" + sp0;
    string regex_create_table_final = regex_create_table + regex_create_table_2;

    //drop table
    string regex_drop_table = sp0 + "Drop" + sp1 + "Table" + sp1 + w1 + sp0;

    //display table
    string regex_display_table = sp0 + "Display" + sp1 + "Table" + sp1 + w1 + sp0;

    //insert into
    string regex_valori_insert = "\\(" + sp0 + valori + sp0 + "(" + "," + sp0 + valori + sp0 + ")*" + sp0 + "\\)" + sp0;
    string regex_insert_into = sp0 + "insert" + sp1 + "into" + sp1 + w1 + sp1 + "values" + sp0 + regex_valori_insert;

    //delete from
    string regex_delete_from = sp0 + "Delete" + sp1 + "from" + sp1 + w1 + sp1 + "where" + sp1 + w1 + sp0 + "=" + sp0 + valori + sp0;

    //select
    string regex_select_all = sp0 + "select" + sp1 + "all" + sp1 + "from" + sp1 + w1 + sp0;
    string regex_select_all_where = regex_select_all + "(" + sp1 + "where" + sp1
        + w1 + sp0 + "=" + sp0 + valori + sp0 + ")?" + sp0;
    string regex_nume_coloane = "\\(" + sp0 + w1 + sp0 + "(" + sp0 + "," + sp0 + w1 + sp0 + ")*" + sp0 + "\\)";
    string regex_select = sp0 + "select" + sp0 + regex_nume_coloane + sp0 + "from" + sp1 + w1 + sp0;
    string regex_select_where = regex_select + "(" + sp1 + "where" + sp1 + w1 + sp0 + "=" + sp0 + valori + sp0 + ")?" + sp0;

    //update
    string regex_update = sp0 + "update" + sp1 + w1 + sp1 + "Set" + sp1 + w1 + sp0 + "=" +
        sp0 + valori + sp1 + "where" + sp1 + w1 + sp0 + "=" + sp0 + valori + sp0;

    string* verifica_regex = new string[8];
    verifica_regex[0] = regex_create_table_final;
    verifica_regex[1] = regex_display_table;
    verifica_regex[2] = regex_insert_into;
    verifica_regex[3] = regex_delete_from;
    verifica_regex[4] = regex_drop_table;
    verifica_regex[5] = regex_select_all_where;
    verifica_regex[6] = regex_select_where;
    verifica_regex[7] = regex_update;

    regex Regex;
    bool verifica = 0;int i = 0;
    while (!verifica && i < 8)
    {
        Regex = regex(verifica_regex[i], regex_constants::icase);
        verifica = regex_match(comenzi, Regex);
        i++;
    }
    delete[]verifica_regex;
    if (!verifica) throw db_exception("Aceasta comanda nu exista");
   
}

//functia principala care executa comanda
void executa_comanda(string comenzi)
{

    //verificare sintactica comenzi
    numara_paranteze(comenzi);
    verificare_regex(comenzi);
    //variabila folosita pentru tratarea erorilor
    string mesaj_eroare;
    //comanda primita de la tastatura va fi impartita
    //pe baza separatorilor ,()=' si spatiu liber
    //variabila cuvinte va retine lista de cuvinte 
    //iar variabila nr_cuvinte numarul acestora
    int nr_cuvinte = get_nr_cuvinte_string(comenzi);
    string* cuvinte = impartire_comenzi_pe_cuvinte(comenzi);
    capitalizare_comenzi(cuvinte, nr_cuvinte);
    //afisare cuvinte pe randuri diferite
    for (int i = 0;i < nr_cuvinte;i++)
        cout << cuvinte[i] << endl;

    if (nr_cuvinte <= 2) throw db_exception("Aceasta comanda nu exista");

    //verificare daca comanda este de tip "Create Table"
    if (cuvinte[0] == "CREATE" && cuvinte[1] == "TABLE")
    {
        //eleminare comanda redundanta "if not exists" daca este cazul
        
        if (cuvinte[3] == "IF" && cuvinte[4] == "NOT" && cuvinte[5] == "EXISTS")
        {
            string* aux = new string[nr_cuvinte];
            for (int i = 0;i < nr_cuvinte;i++) aux[i] = cuvinte[i];
            delete[]cuvinte;
            cuvinte = new string[nr_cuvinte - 3];
            for (int i = 0;i < 3;i++) cuvinte[i] = aux[i];
            for (int i = 6;i < nr_cuvinte;i++) cuvinte[i - 3] = aux[i];
            delete[]aux;
            nr_cuvinte -= 3;
        }
        //verificare daca tabelul are coloane
        if (nr_cuvinte == 3)
            throw db_exception("Fiecare tabel trebuie sa aiba cel putin o coloana");

        //Numele tabelului
        string nume_tabel = cuvinte[2];
        //O coloana are obligatoriu 4 cuvinte care o definesc
        if ((nr_cuvinte - 3) % 4 != 0) throw db_exception("Coloane nedeclarate corect");
        int nr_coloane = (nr_cuvinte - 3) / 4;
        //declararare siruri folosite pentru apelarea metodelor
        string* nume_coloane = new string[nr_coloane];
        tip* tipuri_coloane = new tip[nr_coloane];
        int* dimensiuni_coloane = new int[nr_coloane];
        string* valori_implicite = new string[nr_coloane];
        //iterare prin lista de cuvinte
        for (int index = 0;index < nr_coloane;index += 1)
        {
            //numele coloanei
            nume_coloane[index] = cuvinte[4 * index + 3];
            //tipul coloanei, care poate lua doar 3 valori
            string tip_de_data = cuvinte[4 * index + 4];
            if (tip_de_data == "INTEGER") tipuri_coloane[index] = integer;
            else if (tip_de_data == "FLOAT") tipuri_coloane[index] = real;
            else if (tip_de_data == "TEXT") tipuri_coloane[index] = text;
            else
            {
                mesaj_eroare = "Tipul \"" + tip_de_data + "\" nu exista";
                throw db_exception(mesaj_eroare.c_str());
            }
            //dimensiunea coloanei
            sscanf(cuvinte[4 * index + 5].c_str(), "%d", &dimensiuni_coloane[index]);
            //valoarea implicita a coloanei
            valori_implicite[index] = cuvinte[4 * index + 6];
            //afisare coloana la tastatura
            /*cout << nume_coloane[index] << ' ' << tipuri_coloane[index] << ' '
                << dimensiuni_coloane[index] << ' ' << valoare_implicita[index] << endl;*/

        }
        //afisare mesaj aferent executarii comenzii
        cout << endl << "A fost creat tabelul " << nume_tabel << " cu coloanele: ";
        for (int i = 0;i < nr_coloane;i++)
        {
            cout << nume_coloane[i];
            if (i < nr_coloane - 1) cout << ", ";
        }
        cout << endl;
    }
    //verificare daca comanda este de tip "Drop Table"
    else if (cuvinte[0] == "DROP" && cuvinte[1] == "TABLE")
    {
        //Numele tabelului care trebuie sters
        string nume_tabel = cuvinte[2];
        //afisare mesaj aferent executarii comenzii
        cout << "Tabelul " + nume_tabel + " a fost sters" << endl;
    }
    //verificare daca comanda este de tip "Display Table"
    else if (cuvinte[0] == "DISPLAY" && cuvinte[1] == "TABLE")
    {
        //Numele tabelului care trebuie afisat
        string nume_tabel = cuvinte[2];
        //afisare mesaj aferent executarii comenzii
        cout << "Tabelul " + nume_tabel + ":" << endl;
    }
    //verificare daca comanda este de tip "Insert into"
    else if (cuvinte[0] == "INSERT" && cuvinte[1] == "INTO")
    {
        if (nr_cuvinte == 3 || cuvinte[4] != "VALUES") throw db_exception("Lipseste cuvantul cheie \"VALUES\"");
        if (nr_cuvinte == 4) throw db_exception("Nu s-au introdus valori");
        //Numele tabelului
        string nume_tabel = cuvinte[2];
        //Valorile care trebuie introduse in tabel
        string* valori = new string[nr_cuvinte - 4];
        for (int i = 0;i < nr_cuvinte - 4;i++)
            valori[i] = cuvinte[i + 4];
        cout << "S-au introdus valorile in tabelul " << nume_tabel << endl;
    }
    //verificare daca comanda este de tip "Delete from"
    else if (cuvinte[0] == "DELETE" && cuvinte[1] == "FROM")
    {
        if (nr_cuvinte == 3) throw db_exception("Lipseste cuvantul cheie \"WHERE\"");
        if (nr_cuvinte == 4) throw db_exception("Lipseste numele coloanei");
        if (nr_cuvinte == 5) throw db_exception("Lipseste valoarea coloanei");
        string nume_tabel = cuvinte[2];
        string nume_coloana = cuvinte[4];
        string valoare = cuvinte[5];
        cout << "S-a sters randul cu valoarea " << valoare << endl;
    }
    //verificare daca comanda este de tip "Select"
    else if (cuvinte[0] == "SELECT")
    {
        string nume_tabel;
        int i = 1;
        if (cuvinte[1] == "ALL")
        {
            if (nr_cuvinte != 4 && nr_cuvinte != 7) throw db_exception("Aceasta comanda nu exista");
            if (nr_cuvinte == 3) throw db_exception("Lipseste numele tabelului");
            if (cuvinte[2] != "FROM") throw db_exception("Lipseste cuvantul cheie \"FROM\"");
            string* nume_coloane = new string[2];
            nume_coloane[0] = "ALL";
            nume_coloane[1] = "COLUMNS";
            string nume_coloana = "";
            string valoare = "";

            nume_tabel = cuvinte[3];
            if (nr_cuvinte == 7)
                if (cuvinte[4] == "WHERE")
                {
                    nume_coloana = cuvinte[5];
                    valoare = cuvinte[6];
                }
                else throw db_exception("Lipseste cuvantul cheie \"FROM\"");


        }
        else if (cuvinte[i] == "FROM") throw db_exception("Lipsesc coloanele care trebuie selectate");
        else
        {
            if (nr_cuvinte == 3) throw db_exception("Comanda invalida");
            while (cuvinte[i] != "FROM")
            {
                if (cuvinte[i] == "")throw db_exception("Lipseste cuvantul cheie \"FROM\"");
                i++;
            }
            string* nume_coloane = new string[i - 1];
            for (int index = 0;index < i - 1;index++)
                nume_coloane[index] = cuvinte[index + 1];
            if (cuvinte[i + 1] == "") throw db_exception("Lipseste numele tabelului");
            nume_tabel = cuvinte[i + 1];
            string nume_coloana = "";
            string valoare = "";
            if (nr_cuvinte == i + 5)
            {
                if (cuvinte[i + 2] == "WHERE")
                {
                    nume_coloana = cuvinte[i + 3];
                    valoare = cuvinte[i + 4];
                }
                else throw db_exception("Lipseste cuvantul cheie \"FROM\"");
            }
        }
    }
    //verificare daca comanda este de tip "Update"
    else if (cuvinte[0] == "UPDATE")
    {
        if (nr_cuvinte != 8) throw db_exception("Aceasta comanda nu exista");
        if (cuvinte[2] != "SET") throw db_exception("Lipseste cuvantul cheie \"SET\"");
        if (cuvinte[5] != "WHERE") throw db_exception("Lipseste cuvantul cheie \"WHERE\"");
        string nume_tabel = cuvinte[1];
        string nume_coloana_set = cuvinte[3];
        string valoare_set = cuvinte[4];
        string nume_coloana = cuvinte[6];
        string valoare = cuvinte[7];
    }
    else throw db_exception("Aceasta comanda nu exista");
}