#include <iostream>
#include <string>
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
	else
	{
		this->valori_rand = nullptr;
		this->nr_coloane = 0;
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
	else
	{
		valori_rand = nullptr;
		nr_coloane = 0;
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
	else
	{
		valori_rand = nullptr;
		nr_coloane = 0;
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

table::table(string nume, column* coloane, int nr_coloane, row* randuri, int nr_randuri)
{
	this->nume = nume;
	if (coloane != nullptr && nr_coloane > 0)
	{
		this->nr_coloane = nr_coloane;
		this->coloane = new column[nr_coloane];
		for (int i = 0; i < nr_coloane; i++)
		{
			this->coloane[i] = coloane[i];
		}
	}
	else
	{
		this->nr_coloane = 0;
		this->coloane = nullptr;
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
	else
	{
		this->nr_randuri = 0;
		this->randuri = nullptr;
	}
}

table::table(const table& t)
{
	this->nume = t.nume;
	if (t.coloane != nullptr && t.nr_coloane > 0)
	{
		this->nr_coloane = t.nr_coloane;
		this->coloane = new column[t.nr_coloane];
		for (int i = 0; i < t.nr_coloane; i++)
		{
			this->coloane[i] = t.coloane[i];
		}
	}
	else
	{
		this->nr_coloane = 0;
		this->coloane = nullptr;
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
	else
	{
		this->nr_randuri = 0;
		this->randuri = nullptr;
	}
}

table& table::operator=(const table& t)
{
	if (coloane != nullptr)
	{
		delete[] coloane;
	}
	if (randuri != nullptr)
	{
		delete[] randuri;
	}
	this->nume = t.nume;
	if (t.coloane != nullptr && t.nr_coloane > 0)
	{
		this->nr_coloane = t.nr_coloane;
		this->coloane = new column[t.nr_coloane];
		for (int i = 0; i < t.nr_coloane; i++)
		{
			this->coloane[i] = t.coloane[i];
		}
	}
	else
	{
		this->nr_coloane = 0;
		this->coloane = nullptr;
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
	else
	{
		this->nr_randuri = 0;
		this->randuri = nullptr;
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

database::database()
{
	column* coloane = new column[1];
	column dummy("dummy", 1, text, "X");
	coloane[0] = dummy;
	row* randuri = new row[1];
	string* valori_rand = new string[1];
	valori_rand[0] = "X";
	row X(valori_rand, 1);
	randuri[0] = X;
	table dual("dual", coloane, 1, randuri, 1);
	this->tabele = new table[1];
	this->nr_tabele = 1;
	this->tabele[0] = dual;
}

database::database(table* tabele, int nr_tabele)
{
	if (tabele != nullptr && nr_tabele > 0)
	{
		this->tabele = new table[nr_tabele];
		this->nr_tabele = nr_tabele;
		for (int i = 0; i < nr_tabele; i++)
		{
			this->tabele[i] = tabele[i];
		}
	}
	else
	{
		this->tabele = nullptr;
		this->nr_tabele = 0;
	}
}

database::database(const database& db)
{
	if (db.tabele != nullptr && db.nr_tabele > 0)
	{
		this->tabele = new table[db.nr_tabele];
		this->nr_tabele = db.nr_tabele;
		for (int i = 0; i < db.nr_tabele; i++)
		{
			this->tabele[i] = db.tabele[i];
		}
	}
	else
	{
		this->tabele = nullptr;
		this->nr_tabele = 0;
	}
}
database& database::operator=(const database& db)
{
	if (this->tabele != nullptr)
	{
		delete[] this->tabele;
	}

	if (db.tabele != nullptr && db.nr_tabele > 0)
	{
		this->tabele = new table[db.nr_tabele];
		this->nr_tabele = db.nr_tabele;
		for (int i = 0; i < db.nr_tabele; i++)
		{
			this->tabele[i] = db.tabele[i];
		}
	}
	else
	{
		this->tabele = nullptr;
		this->nr_tabele = 0;
	}
	return *this;
}

database::~database()
{
	if (tabele != nullptr)
	{
		delete[] tabele;
	}
}

row* table::delete_row(int index)
{
	row* aux = new row[nr_randuri - 1];
	int k = 0;
	for (int i = 0; i < nr_randuri; i++)
	{
		if (i != index)
		{
			aux[k++] = randuri[i];
		}
	}
	delete[] randuri;
	return aux;
}

void table::display_table()
{
	cout << "-------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < this->nr_coloane; i++)
	{
		cout << this->coloane[i].nume << "  |  ";
	}
	cout << endl;
	cout << "-------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < this->nr_randuri; i++)
	{
		for (int j = 0; j < this->nr_coloane; j++)
		{
			cout << this->randuri[i].valori_rand[j] << "  |  ";
		}
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------\n";
	}
	if (nr_randuri == 1)
	{
		cout << endl << nr_randuri << " row returned.";
	}
	else
	{
		cout << endl << this->nr_randuri << " rows returned.";
	}

}

void table::insert_into(string* valori)
{
	table aux;
	if (nr_randuri == 0) aux.randuri = NULL;
	else aux.randuri = new row[nr_randuri];
	for (int i = 0;i < nr_randuri;i++)
	{
		aux.randuri[i].nr_coloane = this->nr_coloane;
		aux.randuri[i].valori_rand = new string[nr_coloane];
		for (int j = 0;j < nr_coloane;j++)
			aux.randuri[i].valori_rand[j] = randuri[i].valori_rand[j];
	}
	if(randuri) delete[]randuri;
	randuri = new row[nr_randuri + 1];
	for (int i = 0;i < nr_randuri;i++)
	{
		randuri[i].nr_coloane = aux.randuri[i].nr_coloane;
		randuri[i].valori_rand = new string[nr_coloane];
		for (int j = 0;j < nr_coloane;j++)
			randuri[i].valori_rand[j] = aux.randuri[i].valori_rand[j];
	}
	randuri[nr_randuri].valori_rand = new string[nr_coloane];
	randuri[nr_randuri].nr_coloane = this->nr_coloane;
	for (int i = 0; i < nr_coloane; i++)
	{
		randuri[nr_randuri].valori_rand[i] = valori[i];
	}
	nr_randuri++;
}

void table::delete_from(string nume_coloana, string valoare)
{
	int ok_nume_coloana = 0, nr_rows_deleted = 0;
	for (int i = 0; i < nr_coloane; i++)
	{
		if (coloane[i].nume == nume_coloana)
		{
			ok_nume_coloana = 1;
			for (int j = 0; j < nr_randuri; j++)
			{
				if (randuri[j].valori_rand[i] == valoare)
				{
					randuri = delete_row(j);
					nr_randuri--;
					nr_rows_deleted++;
				}
			}
		}
	}
	if (ok_nume_coloana == 0)
	{
		throw db_exception("Nu exista nicio coloana cu acest nume");
	}
	if (nr_rows_deleted == 1)
	{
		cout << nr_rows_deleted << " row deleted.";
	}
	else
	{
		cout << nr_rows_deleted << " rows deleted.";
	}
}

int table::find_column_index(string coloana_to_find)
{
	for (int i = 0; i < nr_coloane; i++)
	{
		if (coloane[i].nume == coloana_to_find)
		{
			return i;
		}
	}

	throw db_exception("Aceasta coloana nu exista");
}
//TODO de tratat caz *
void table::select(string* nume_coloane, int nr_coloane_afisare, string nume_coloana, string valoare)
{
	int ok_nume_coloana = 0; int nr_rows_returned = 0;bool verifica_where = 1;
	if (nume_coloane[0] == "ALL" && nume_coloane[1] == "COLUMNS")
	{
		nr_coloane_afisare = this->nr_coloane;
		delete[]nume_coloane;
		nume_coloane = new string[nr_coloane_afisare];
		for (int i = 0;i < nr_coloane_afisare;i++)
			nume_coloane[i] = this->coloane[i].nume;
	}
	cout << "--------------------------------------------------------------------------------------\n";
	for (int i = 0;i < nr_coloane_afisare;i++)
	{
		for (int j = 0;j < nr_coloane;j++)
		
			if (this->coloane[j].nume == nume_coloane[i]) cout << nume_coloane[i] << "  |  ";
		
	}
	cout << endl;

	if (nume_coloana == "" && valoare == "")
		verifica_where = 0;


	for (int i = 0; i < nr_coloane; i++)
	{
		if (!verifica_where) 
			nume_coloana = coloane[i].nume;
		if (coloane[i].nume == nume_coloana)
		{
			ok_nume_coloana = 1;
			for (int j = 0; j < nr_randuri; j++)
			{
				if (!verifica_where) valoare = randuri[j].valori_rand[i];
				if (randuri[j].valori_rand[i] == valoare)
				{
					nr_rows_returned++;
					int n = 0;
					cout << "---------------------------------------------------------------------------------------" << endl;
					while (n < nr_coloane_afisare)
					{
						int index = find_column_index(nume_coloane[n]);
						cout << randuri[j].valori_rand[index] << "  |  ";
						n++;
					}
					cout << endl;
				}
			}
			cout << "--------------------------------------------------------------------------------------\n";
			if (!verifica_where) i = nr_coloane;
		}
	}
	if (ok_nume_coloana == 0)
	{
		throw db_exception("Aceasta coloana nu exista");
	}
	if (nr_rows_returned == 1)
	{
		cout << nr_rows_returned << " row returned.";
	}
	else
	{
		cout << endl << nr_rows_returned << " rows returned.";
	}
}

void table::update(string nume_coloana, string nume_coloana_set, string valoare, string valoare_set)
{
	int  nr_rows_updated = 0;
	int index_set = find_column_index(nume_coloana_set);
	
	int index = find_column_index(nume_coloana);
	for (int j = 0; j < nr_randuri; j++)
	{
		if (randuri[j].valori_rand[index] == valoare)
		{
			randuri[j].valori_rand[index_set] = valoare_set;
			nr_rows_updated++;
		}
	}
	
	if (nr_rows_updated == 1)
	{
		cout << nr_rows_updated << " row updated.";
	}
	else
	{
		cout << nr_rows_updated << " rows updated.";
	}
}

int database::find_index(string nume_tabela)
{
	for (int i = 0; i < nr_tabele; i++)
	{
		if (tabele[i].nume == nume_tabela)
		{
			return i;
		}
	}

	throw db_exception("Aceasta tabela nu exista");
}

table* database::delete_table(int index)
{
	table* aux = new table[nr_tabele - 1];
	int k = 0;
	for (int i = 0; i < nr_tabele; i++)
	{
		if (i != index)
		{
			aux[k++] = tabele[i];
		}
	}
	delete[] tabele;
	return aux;
}

void database::create_table(string nume_tabela, int nr_coloane, string* nume_coloane, tip* tipuri_coloane, int* dimensiune, string* valoare_implicita)
{

	for (int i = 0; i < nr_tabele; i++)
	{
		if (tabele[i].nume == nume_tabela)
		{
			throw db_exception("Tabela exista deja. Incercati alt nume.");
		}
	}

	column* coloane = new column[nr_coloane];
	for (int i = 0; i < nr_coloane; i++)
	{
		coloane[i].dimensiune = dimensiune[i];
		coloane[i].nume = nume_coloane[i];
		coloane[i].Tip = tipuri_coloane[i];
		coloane[i].valoare_implicita = valoare_implicita[i];
	}
	database aux;
	aux.nr_tabele = nr_tabele;
	aux.tabele = new table[nr_tabele];
	for (int i = 0;i < nr_tabele;i++) aux.tabele[i] = tabele[i];
	delete[] tabele;
	tabele = new table[nr_tabele + 1];
	for (int i = 0;i < nr_tabele;i++) tabele[i] = aux.tabele[i];
	tabele[nr_tabele++] = table(nume_tabela, coloane, nr_coloane, nullptr, 0);
}



void database::drop_table(string nume_tabela)
{
	int index = find_index(nume_tabela);
	tabele = delete_table(index);
	nr_tabele--;
}

void database::display_table(string nume_tabela)
{
	int index = find_index(nume_tabela);
	tabele[index].display_table();
}

void database::insert_into(string nume_tabela, string* valori)
{
	int index = find_index(nume_tabela);
	tabele[index].insert_into(valori);
}

void database::delete_from(string nume_tabela, string nume_coloana, string valoare)
{
	int index = find_index(nume_tabela);
	tabele[index].delete_from(nume_coloana, valoare);
}

void database::select(string nume_tabela, string* nume_coloane, int nr_coloane_afisare, string nume_coloana, string valoare)
{
	int index = find_index(nume_tabela);
	tabele[index].select(nume_coloane, nr_coloane_afisare, nume_coloana, valoare);
}

void database::update(string nume_tabela, string nume_coloana, string nume_coloana_set, string valoare, string valoare_set)
{
	int index = find_index(nume_tabela);
	tabele[index].update(nume_coloana, nume_coloana_set, valoare, valoare_set);
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
        if (!isalnum(c) && c != '.' && c != '_' && cuvinte[index] != "") index++;
        else if (c == '\'')
        {
            i++;
            while (comenzi[i] != '\'') { cuvinte[index] += comenzi[i];i++; }
        }
        else if (isalnum(c) || c == '.' || c == '_')cuvinte[index] += c;
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
    bool verifica = 0;int i = 1;

    //comanda "create table" dureaza prea mult sa fie verificata regex
    if (regex_match(comenzi, regex(sp0 + "Create" + sp1 + "Table(.*)", regex_constants::icase))) verifica = 1;

	//comanda "update" dureaza prea mult sa fie verificata regex
	if (regex_match(comenzi, regex(sp0 + "update(.*)", regex_constants::icase)))
	{
		verifica = 1;
	}


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
void executa_comanda(string comenzi, database &db)
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

    /*for (int i = 0;i < nr_cuvinte;i++)
        cout << cuvinte[i] << endl;*/

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
		db.create_table(nume_tabel, nr_coloane, nume_coloane, tipuri_coloane, dimensiuni_coloane, valori_implicite);
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
		db.drop_table(nume_tabel);
    }
    //verificare daca comanda este de tip "Display Table"
    else if (cuvinte[0] == "DISPLAY" && cuvinte[1] == "TABLE")
    {
        //Numele tabelului care trebuie afisat
        string nume_tabel = cuvinte[2];
        //afisare mesaj aferent executarii comenzii
        
		db.display_table(nume_tabel);
		
    }
    //verificare daca comanda este de tip "Insert into"
    else if (cuvinte[0] == "INSERT" && cuvinte[1] == "INTO")
    {
        if (nr_cuvinte == 3 || cuvinte[3] != "VALUES") throw db_exception("Lipseste cuvantul cheie \"VALUES\"");
        if (nr_cuvinte == 4) throw db_exception("Nu s-au introdus valori");
        //Numele tabelului
        string nume_tabel = cuvinte[2];
        //Valorile care trebuie introduse in tabel
        string* valori = new string[nr_cuvinte - 4];
        for (int i = 0;i < nr_cuvinte - 4;i++)
            valori[i] = cuvinte[i + 4];
		db.insert_into(nume_tabel, valori);
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
		db.delete_from(nume_tabel, nume_coloana, valoare);
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
			db.select(nume_tabel, nume_coloane, 2, nume_coloana, valoare);

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
			int nr_coloane_afisare = i - 1;
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
			db.select(nume_tabel, nume_coloane,nr_coloane_afisare, nume_coloana, valoare);
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
		db.update(nume_tabel, nume_coloana, nume_coloana_set, valoare, valoare_set);
        cout << "Valoarea din tabelul " << nume_tabel <<
            " a fost modificata" << endl;
    }
    else throw db_exception("Aceasta comanda nu exista");
}