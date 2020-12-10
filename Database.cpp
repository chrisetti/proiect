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
    
    if (!verifica) throw db_exception("Aceasta comanda nu exista");
   
}