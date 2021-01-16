#include "Database.h"
#pragma warning(disable:4996)

//initializare constructori clasa db_exception
db_exception::db_exception() :exception("Comanda invalida") {}
db_exception::db_exception(const char* message) : exception(message) {}
db_exception::db_exception(string message) : db_exception::db_exception(message.c_str()) {}

column::column()
{
	nume = "";
	dimensiune = 0;
	Tip = text;
	valoare_implicita = "";
}
column::column(string nume, int dimensiune, tip Tip, string valoare_implicita)
{
	this->nume = nume;
	this->dimensiune = dimensiune;
	this->Tip = Tip;
	this->valoare_implicita = valoare_implicita;
}
int column::getDimensiune()
{
	return this->dimensiune;
}

void column::setTip(tip Tip)
{
	this->Tip = Tip;
}

tip column::getTip()
{
	return this->Tip;
}

void column::setNume(string nume)
{
	this->nume = nume;
}

string column::getNume()
{
	return this->nume;
}

void column::setDimensiune(int dimensiune)
{
	this->dimensiune = dimensiune;
}

void column::setValoareImplicita(string valoare_implicita)
{
	this->valoare_implicita = valoare_implicita;
}

string column::getValoareImplicita()
{
	return this->valoare_implicita;
}

column column::operator+(string s)
{
	this->nume = this->nume + s;
	return *this;
}

column column::operator++()
{
	this->dimensiune++;
	return *this;
}

column column::operator++(int i)
{
	column copie = *this;
	this->dimensiune++;
	return copie;
}

column::operator int()
{
	return this->dimensiune;
}

bool column::operator!()
{
	return this->dimensiune > 0;
}

bool column::operator<= (column c)
{
	return this->dimensiune <= c.getDimensiune();
}

bool column::operator==(column c)
{

	return (this->nume == c.getNume()) && (this->dimensiune == c.getDimensiune()) && (this->Tip == c.getTip()) && (this->valoare_implicita == c.getValoareImplicita());
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

void row::setValoriRand(string* valori, int nr_coloane)
{
	if (valori != nullptr && nr_coloane != 0)
	{
		for (int i = 0; i < nr_coloane; i++)
		{
			this->valori_rand = valori;
		}
	}
}

string* row::getValoriRand()
{
	return this->valori_rand;
}

void row::setNrColoane(int nr_coloane)
{
	this->nr_coloane = nr_coloane;
}

int row::getNrColoane()
{
	return this->nr_coloane;
}

void table::setNume(string nume)
{
	this->nume = nume;
}

string table::getNume()
{
	return this->nume;
}

void table::setNrColoane(int nr_coloane)
{
	this->nr_coloane = nr_coloane;
}

int table::getNrColoane()
{
	return this->nr_coloane;
}

void table::setNrRanduri(int nr_randuri)
{
	this->nr_randuri = nr_randuri;
}

int table::getNrRanduri()
{
	return this->nr_randuri;
}

void table::setColoane(column* coloane, int nr_coloane)
{
	if (coloane != nullptr && nr_coloane > 0)
	{
		for (int i = 0; i < nr_coloane; i++)
		{
			this->coloane[i] = coloane[i];
		}
	}
}

column* table::getColoane()
{
	return this->coloane;
}

void table::setRanduri(row* randuri, int nr_randuri)
{
	if (randuri != nullptr && nr_randuri > 0)
	{
		for (int i = 0; i < nr_randuri; i++)
		{
			this->randuri[i] = randuri[i];
		}
	}
}

row* table::getRanduri()
{
	return this->randuri;
}


string& row::operator[](int index)
{
	if (index >= 0 && index < nr_coloane)
	{
		return valori_rand[index];
	}
	throw db_exception("Index invalid.");

}

row row::operator++()
{
	this->nr_coloane++;
	return *this;
}

row row::operator++(int i)
{
	row copie = *this;
	this->nr_coloane++;
	return copie;
}

row::operator int()
{
	return this->nr_coloane;
}

bool row::operator!()
{
	return this->nr_coloane > 0;
}

bool row::operator<(row r)
{
	return this->nr_coloane < r.nr_coloane;
}
bool operator<(const row& r1, const row& r2)
{
	return true;
}

bool row::operator==(row r)
{
	if (this->nr_coloane != r.nr_coloane)
	{
		return false;
	}
	for (int i = 0; i < this->nr_coloane; i++)
	{
		if (this->valori_rand[i] != r.valori_rand[i])
		{
			return false;
		}
	}
	return true;
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

column& table:: operator[](int index)
{
	if (index >= 0 && index < nr_coloane)
	{
		return coloane[index];
	}
	throw exception("index invalid");
}

table table::operator+(string s)
{
	this->nume = this->nume + s;
	return *this;
}

table table::operator++(int i)
{
	table copie = *this;
	this->nr_coloane++;
	return copie;
}

table table::operator++()
{
	this->nr_coloane++;
	return *this;
}

table::operator string()
{
	return this->nume;
}

bool table::operator!()
{
	return this->nr_randuri > 0;
}

bool table::operator<= (table t)
{
	return this->nr_randuri <= t.nr_randuri;
}
table& database::operator[](int index)
{
	if (index >= 0 && index < nr_tabele)
	{
		return tabele[index];
	}
}

database::operator int()
{
	return nr_tabele > 0;
}

bool database::operator!()
{
	return this->nr_tabele;
}

database database::operator++()
{
	this->nr_tabele++;
	return *this;
}

database database::operator++(int i)
{
	database copie = *this;
	this->nr_tabele++;
	return copie;
}

bool database::operator<=(database db)
{
	return this->nr_tabele <= db.nr_tabele;
}

bool database::operator==(database db)
{
	if (this->nr_tabele != db.nr_tabele)
	{
		return false;
	}
	return true;
}

void database::setTabele(table* tabele, int nr_tabele)
{
	if (tabele != nullptr && nr_tabele != 0)
	{
		for (int i = 0; i < nr_tabele; i++)
		{
			this->tabele[i] = tabele[i];
		}
	}
}

table* database::getTabele()
{
	return this->tabele;
}

void database::setNrTabele(int nr_tabele)
{
	if (nr_tabele != 0)
	{
		this->nr_tabele;
	}
}

int database::getNrTabele()
{
	return this->nr_tabele;
}
database::database()
{
	column* coloane = new column[1];
	column dummy("DUMMY", 1, text, "X");
	coloane[0] = dummy;
	row* randuri = new row[1];
	string* valori_rand = new string[1];
	valori_rand[0] = "X";
	row X(valori_rand, 1);
	randuri[0] = X;
	table dual("DUAL", coloane, 1, randuri, 1);
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

void table::display_table(string nume_fisier)
{
	ofstream out(nume_fisier);
	cout << left;int lungime_maxima = 0;
	for (int i = 0;i < this->nr_coloane;i++)
	{
		if (lungime_maxima < this->coloane[i].dimensiune)
		{
			lungime_maxima = this->coloane[i].dimensiune;
		}
	}
	if (lungime_maxima > 20) lungime_maxima = 20;
	afisare_linii((5+lungime_maxima)*this->nr_coloane-2);
	for (int i = 0; i < this->nr_coloane; i++)
	{
		cout << setw(lungime_maxima) << this->coloane[i].nume << "  |  ";
		out << this->coloane[i].nume << ' ';
	}
	cout << endl;
	out << endl;
	afisare_linii((5+lungime_maxima)*this->nr_coloane-2);
	for (int i = 0; i < this->nr_randuri; i++)
	{
		for (int j = 0; j < this->nr_coloane; j++)
		{
			cout << setw(lungime_maxima) << this->randuri[i].valori_rand[j] << "  |  ";
			out << this->randuri[i].valori_rand[j] << ' ';
		}
		cout << endl;
		out << endl;
		afisare_linii((5+lungime_maxima)*this->nr_coloane-2);
	}
	if (nr_randuri == 1)
	{
		cout << endl << nr_randuri << " row returned.";
	}
	else
	{
		cout << endl << this->nr_randuri << " rows returned." << endl;
	}

}

void table::insert_into(string* valori)
{
	for (int i = 0;i < this->nr_coloane;i++)
	{
		if (valori[i].length() > this->coloane[i].dimensiune)
		{
			string mesaj_eroare = "Valoarea introdusa pentru coloana " + this->coloane[i].nume + " este prea mare";
			throw db_exception(mesaj_eroare.c_str());
		}
		if (this->coloane[i].Tip == integer)
		{
			if (!regex_match(valori[i], regex("[[:d:]]+")))
				throw db_exception("Valoare invalida pentru INTEGER");
		}
		else if (this->coloane[i].Tip == real)
		{
			if (!regex_match(valori[i], regex("[[:d:]]+(.)?[[:d:]]*")))
				throw db_exception("Valoare invalida pentru FLOAT");
			valori[i] = to_string(stof(valori[i]));
		}
	}
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
				if (coloane[i].Tip == real)
				{
					valoare = to_string(stof(valoare));
				}
				if (randuri[j].valori_rand[i] == valoare)
				{
					randuri = delete_row(j);
					nr_randuri--;
					j--;
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

void table::select(string nume_fisier, string* nume_coloane, int nr_coloane_afisare, string nume_coloana, string valoare)
{
	ofstream out(nume_fisier);
	cout << left;int lungime_maxima = 0;
	for (int i = 0;i < this->nr_coloane;i++)
	{
		if (lungime_maxima < this->coloane[i].dimensiune)
		{
			lungime_maxima = this->coloane[i].dimensiune;
		}
	}
	if (lungime_maxima > 20) lungime_maxima = 20;
	int ok_nume_coloana = 0; int nr_rows_returned = 0;bool verifica_where = 1;
	if (nume_coloane[0] == "ALL" && nume_coloane[1] == "COLUMNS")
	{
		nr_coloane_afisare = this->nr_coloane;
		delete[]nume_coloane;
		nume_coloane = new string[nr_coloane_afisare];
		for (int i = 0;i < nr_coloane_afisare;i++)
			nume_coloane[i] = this->coloane[i].nume;
	}
	afisare_linii((5+lungime_maxima)*nr_coloane_afisare-2);
	for (int i = 0;i < nr_coloane_afisare;i++)
	{
		for (int j = 0;j < nr_coloane;j++)
		
			if (this->coloane[j].nume == nume_coloane[i])
			{
				cout << setw(lungime_maxima) << nume_coloane[i] << "  |  ";
				out << nume_coloane[i] << ' ';
			}
		
	}
	cout << endl;
	out << endl;

	if (nume_coloana == "" && valoare == "")
		verifica_where = 0;


	for (int i = 0; i < nr_coloane; i++)
	{
		if (!verifica_where) 
			nume_coloana = coloane[i].nume;
		if (coloane[i].nume == nume_coloana)
		{
			if (coloane[i].Tip == real)
				valoare = to_string(stof(valoare));
			ok_nume_coloana = 1;
			for (int j = 0; j < nr_randuri; j++)
			{
				if (!verifica_where) valoare = randuri[j].valori_rand[i];
				if (randuri[j].valori_rand[i] == valoare)
				{
					nr_rows_returned++;
					int n = 0;
					afisare_linii((5+lungime_maxima)* nr_coloane_afisare -2);
					while (n < nr_coloane_afisare)
					{
						int index = find_column_index(nume_coloane[n]);
						cout << setw(lungime_maxima) << randuri[j].valori_rand[index] << "  |  ";
						out << randuri[j].valori_rand[index] << ' ';
						n++;
					}
					cout << endl;
					out << endl;
				}
			}
			afisare_linii((5+lungime_maxima)* nr_coloane_afisare -2);
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
	if (this->coloane[index].Tip == real)
		valoare = to_string(stof(valoare));
	for (int j = 0; j < nr_randuri; j++)
	{

		if (randuri[j].valori_rand[index] == valoare)
		{
			if (valoare_set.length() > this->coloane[index_set].dimensiune)
			{
				string mesaj_eroare = "Valoarea introdusa pentru coloana " + this->coloane[index_set].nume + " este prea mare";
				throw db_exception(mesaj_eroare.c_str());
			}
			if (this->coloane[index_set].Tip == integer)
			{
				if (!regex_match(valoare_set, regex("[[:d:]]+")))
					throw db_exception("Valoare invalida pentru INTEGER");
			}
			else if (this->coloane[index_set].Tip == real)
			{
				if (!regex_match(valoare_set, regex("[[:d:]]+(.)?[[:d:]]*")))
					throw db_exception("Valoare invalida pentru FLOAT");
				valoare_set = to_string(stof(valoare_set));
			}
			randuri[j].valori_rand[index_set] = valoare_set;
			nr_rows_updated++;
		}
	}
	
	if (nr_rows_updated == 1)
	{
		cout << nr_rows_updated << " row updated. ";
	}
	else
	{
		cout << nr_rows_updated << " rows updated. ";
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

void database::display_table(string nume_fisier, string nume_tabela)
{
	int index = find_index(nume_tabela);
	tabele[index].display_table(nume_fisier);
}

void database::insert_into(string nume_tabela, string* valori, int nr_valori)
{
	int index = find_index(nume_tabela);
	if (nr_valori > tabele[index].nr_coloane)
	{
		throw db_exception("Prea multe valori de inserat");
	}
	tabele[index].insert_into(valori);
}

void database::delete_from(string nume_tabela, string nume_coloana, string valoare)
{
	int index = find_index(nume_tabela);
	tabele[index].delete_from(nume_coloana, valoare);
}

void database::select(string nume_fisier, string nume_tabela, string* nume_coloane, int nr_coloane_afisare, string nume_coloana, string valoare)
{
	int index = find_index(nume_tabela);
	tabele[index].select(nume_fisier, nume_coloane, nr_coloane_afisare, nume_coloana, valoare);
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
    string sp0 = "\\s*";
    string sp1 = "\\s+";
    string w1 = "\\w+";
    string d0 = "\\d*";
    string d1 = "\\d+";
    string caracter = "(.*)";

    //create_table
	string regex_create_1 =
		sp0 + "create" + sp1 + "table" + sp1 + w1 + sp0 + "(" + sp1 + "if" + sp1 + "not" + sp1 + "exists" + sp0 + ")?" + sp0;
	string regex_coloana = "\\(" + sp0 + w1 + sp0 + "," + sp0 + "(text|float|integer)" + sp0 + "," + sp0 + d1 + sp0 + "," + sp0 + caracter + sp0 + "\\)";
	string regex_create_2 = "\\(" + sp0 + regex_coloana + sp0 + "(," + sp0 + regex_coloana + sp0 + ")*" + sp0 + "\\)" + sp0;
	string regex_create_table = regex_create_1 + regex_create_2;

    //drop table
    string regex_drop_table = sp0 + "Drop" + sp1 + "Table" + sp1 + w1 + sp0;

    //display table
    string regex_display_table = sp0 + "Display" + sp1 + "Table" + sp1 + w1 + sp0;

    //insert into
    string regex_valori_insert = "\\(" + sp0 + caracter + sp0 + "(" + "," + sp0 + caracter + sp0 + ")*" + sp0 + "\\)" + sp0;
    string regex_insert_into = sp0 + "insert" + sp1 + "into" + sp1 + w1 + sp1 + "values" + sp0 + regex_valori_insert;

    //delete from
    string regex_delete_from = sp0 + "Delete" + sp1 + "from" + sp1 + w1 + sp1 + "where" + sp1 + w1 + sp0 + "=" + sp0 + caracter + sp0;

    //select
    string regex_select_all = sp0 + "select" + sp1 + "all" + sp1 + "from" + sp1 + w1 + sp0;
    string regex_select_all_where = regex_select_all + "(" + sp1 + "where" + sp1
        + w1 + sp0 + "=" + sp0 + caracter + sp0 + ")?" + sp0;
    string regex_nume_coloane = "\\(" + sp0 + w1 + sp0 + "(" + sp0 + "," + sp0 + w1 + sp0 + ")*" + sp0 + "\\)";
    string regex_select = sp0 + "select" + sp0 + regex_nume_coloane + sp0 + "from" + sp1 + w1 + sp0;
    string regex_select_where = regex_select + "(" + sp1 + "where" + sp1 + w1 + sp0 + "=" + sp0 + caracter + sp0 + ")?" + sp0;

    //update
    string regex_update = sp0 + "update" + sp1 + w1 + sp1 + "Set" + sp1 + w1 + sp0 + "=" +
        sp0 + caracter + sp1 + "where" + sp1 + w1 + sp0 + "=" + sp0 + caracter + sp0;

	//import
	string regex_import = sp0 + "import" + sp1 + w1 + sp1 + caracter + ".csv";

    string* verifica_regex = new string[9];
    verifica_regex[0] = regex_create_table;
    verifica_regex[1] = regex_display_table;
    verifica_regex[2] = regex_insert_into;
    verifica_regex[3] = regex_delete_from;
    verifica_regex[4] = regex_drop_table;
    verifica_regex[5] = regex_select_all_where;
    verifica_regex[6] = regex_select_where;
    verifica_regex[7] = regex_update;
	verifica_regex[8] = regex_import;

    regex Regex;
    bool verifica = 0;int i = 0;


    while (!verifica && i < 9)
    {
        Regex = regex(verifica_regex[i], regex_constants::icase);
        verifica = regex_match(comenzi, Regex);
        i++;
    }
    delete[]verifica_regex;
    if (!verifica) throw db_exception("Aceasta comanda nu exista");

}


fisier_binar::fisier_binar()
{
	nume = "";
	structura_tabel = "";
}

fisier_binar::fisier_binar(string nume, string structura)
{
	this->nume = "_" + nume + ".bin";
	this->structura_tabel = structura;
}

string** fisier_binar::citeste_binar(int& nr_randuri)
{
	int nr_variabila_coloana = 0, nr_variabila_rand = 0;nr_randuri = 0;
	int aux_int;float aux_float;string aux_string;
	ifstream f(nume, ios::binary);

	char* var_strtok = new char[structura_tabel.length() + 1];
	strcpy_s(var_strtok, structura_tabel.length() + 1, structura_tabel.c_str());
	string buffer[100];int k = 0;
	string** randuri;
	char* token = strtok(var_strtok, " ");
	while (token)
	{
		buffer[k++] = string(token);
		token = strtok(NULL, " ");
	}
	if (var_strtok) delete[]var_strtok;

	while (true)
	{
		if (f.eof()) break;
		for (int i = 0;i < k;i += 2)
		{

			if (buffer[i] == "TEXT")
			{
				int dimensiune;
				f.read((char*)&dimensiune, sizeof(dimensiune));
				char buffer_citire[256];
				f.read(buffer_citire, dimensiune);

			}
			if (buffer[i] == "INTEGER")
			{
				f.read((char*)&aux_int, sizeof(int));
			}
			if (buffer[i] == "FLOAT")
			{
				f.read((char*)&aux_float, sizeof(float));
			}
		}
		nr_randuri++;
	}
	nr_randuri--;
	f.close();f = ifstream(nume, ios::binary);
	randuri = new string * [nr_randuri];
	for (int i = 0;i < nr_randuri;i++)
	{
		randuri[i] = new string[k / 2];
	}
	while (nr_variabila_rand < nr_randuri)
	{
		nr_variabila_coloana = 0;
		for (int i = 0;i < k;i += 2)
		{
			if (buffer[i] == "TEXT")
			{
				int dimensiune;
				f.read((char*)&dimensiune, sizeof(dimensiune));
				char buffer_citire[256];
				f.read(buffer_citire, dimensiune);
				randuri[nr_variabila_rand][nr_variabila_coloana++] = string(buffer_citire);
			}
			if (buffer[i] == "INTEGER")
			{
				f.read((char*)&aux_int, sizeof(int));
				randuri[nr_variabila_rand][nr_variabila_coloana++] = to_string(aux_int);
			}
			if (buffer[i] == "FLOAT")
			{
				f.read((char*)&aux_float, sizeof(float));
				randuri[nr_variabila_rand][nr_variabila_coloana++] = to_string(aux_float);
			}
		}
		nr_variabila_rand++;
		if (f.eof()) break;
	}
	f.close();
	return randuri;
}

void fisier_binar::scrie_binar_append(string* valori, int n)
{
	ofstream g(nume, ios::binary | ios::app);
	int k = 0;
	string* temp = new string[n * 2];
	char* buffer = new char[structura_tabel.length() + 1];
	strcpy_s(buffer, structura_tabel.length() + 1, structura_tabel.c_str());
	char* token = strtok(buffer, " ");
	while (token)
	{
		temp[k++] = string(token);
		token = strtok(NULL, " ");
	}
	k = 0;
	for (int i = 0;i < n;i++)
	{
		int aux;
		int ignore = sscanf(temp[k + 1].c_str(), "%d", &aux);
		if (temp[k] == "TEXT")
		{
			int sz = valori[i].length() + 1;
			g.write((char*)&sz, sizeof(sz));
			g.write((char*)&valori[i][0], sz);
		}
		if (temp[k] == "INTEGER")
		{
			int valoare_int;
			ignore = sscanf(valori[i].c_str(), "%d", &valoare_int);
			g.write((char*)&valoare_int, sizeof(int));
		}
		if (temp[k] == "FLOAT")
		{
			float valoare_float;
			ignore = sscanf(valori[i].c_str(), "%f", &valoare_float);
			g.write((char*)&valoare_float, sizeof(float));
		}
		k += 2;
	}
	g.close();
}

void fisier_binar::scrie_binar_sterge(string valoare, int camp, int nr_coloane)
{
	int nr_randuri;
	fisier_binar temp("temp", this->structura_tabel);
	string** valori = this->citeste_binar(nr_randuri);
	for (int i = 0;i < nr_randuri;i++)
	{
		if (valori[i][camp] != valoare)
		{
			temp.scrie_binar_append(valori[i], nr_coloane);
		}
	}
	remove(this->nume.c_str());
	int ignore = rename(temp.nume.c_str(), this->nume.c_str());
}

void fisier_binar::scrie_binar_inlocuire(string valoare, int camp, string valoare_set, int camp_set, int nr_coloane)
{
	int nr_randuri;
	fisier_binar temp("temp", this->structura_tabel);
	string** valori = this->citeste_binar(nr_randuri);
	for (int i = 0;i < nr_randuri;i++)
	{
		if (valori[i][camp] == valoare)
		{
			valori[i][camp_set] = valoare_set;
		}
		temp.scrie_binar_append(valori[i], nr_coloane);
	}
	remove(this->nume.c_str());
	int ignore = rename(temp.nume.c_str(), this->nume.c_str());
	if (ignore != 0)
	{
		ofstream err(this->nume, ios::binary);
		err.close();
	}
}

fisier_txt::fisier_txt()
{
	nume = "";
}

fisier_txt::fisier_txt(string nume)
{
	this->nume = nume;
}

fisier_txt& fisier_txt::operator=(const fisier_txt& src)
{
	nume = src.nume;
	return *this;
}

void fisier_txt::scrie_text(vector<string> valori, int nr_valori)
{
	ofstream f(nume);
	for (int i = 0;i < nr_valori;i++)
	{
		f << valori[i];
	}
	f.close();
}

string** fisier_txt::citeste_text(int& nr_linii)
{
	ifstream f(nume);
	char buffer[500];
	nr_linii = 0;
	int  i = 0, j = 0;
	int test = f.peek();
	if (!f.good())
	{
		f.close();
		ofstream g(nume);
		g.close();
		return NULL;
	}
	while (true)
	{
		f.getline(buffer, 500);
		nr_linii++;
		if (f.eof()) break;
	}
	f.seekg(SEEK_SET);
	string** sir = new string * [nr_linii];
	for (int i = 0;i < nr_linii;i++)
		sir[i] = new string[500];
	for (int i = 0;i < nr_linii;i++)
	{
		f.getline(buffer, 500);
		char* token = strtok(buffer, ",");
		while (token)
		{
			sir[i][j++] = string(token);
			token = strtok(NULL, ",");
		}
		if (f.eof()) break;
		j = 0;
	}
	f.close();
	return sir;
}

void fisier_txt::scrie_text_append(string* valori, int nr_valori)
{
	ifstream aux(nume);
	bool fisier_gol = (aux.peek() == EOF);
	aux.close();
	ofstream f(nume,ios::app);
	if(!fisier_gol) f << endl;
	for (int i = 0;i < nr_valori;i++)
	{
		f << valori[i];
	}
	f.close();
}

void fisier_txt::scrie_text_sterge(string n)
{
	ifstream f(nume);
	if (!f.good()) throw db_exception("Nu exista fisierul");
	ofstream g("temp.txt");
	bool fisier_gol = true;
	while (true)
	{
		char buffer[500];
		f.getline(buffer,500);
		char* copie = new char[strlen(buffer) + 1];
		strcpy_s(copie, strlen(buffer) + 1, buffer);
		char* token = strtok(buffer, ",");
		if (string(token) != n)
		{
			if (!fisier_gol)g << endl;
			g << copie;
			fisier_gol = false;
		}
		delete[]copie;
		if (f.eof()) break;
	}
	f.close();
	g.close();
	remove(nume.c_str());
	int r = rename("temp.txt", nume.c_str());
}

fisier_csv::fisier_csv()
{
	nr_coloane = 0;
	nume = "";
}

fisier_csv::fisier_csv(string nume, int nr_coloane)
{
	this->nr_coloane = nr_coloane;
	this->nume = nume;
}

string** fisier_csv::citeste_text(int& nr_elemente)
{
	ifstream f(nume);
	if (!f.good())
	{
		throw db_exception("Fisierul nu exista");
	}
	string buffer;
	getline(f, buffer);
	if (!regex_match(buffer, regex("([.,\\d]*|'(.*)')*", regex_constants::icase)))
	{
		throw db_exception("Separatorul corect este ,");
	}
	for (int i = 0;i < buffer.size();i++)
	{
		if (buffer[i] == ',') nr_elemente++;
	}
	nr_elemente++;
	if (nr_elemente % nr_coloane != 0)
	{
		throw db_exception("Numar gresit de elemente introdus");
	}
	nr_elemente /= nr_coloane;
	string** rez = new string * [nr_elemente];
	for (int i = 0;i < nr_elemente;i++)
	{
		rez[i] = new string[nr_coloane];
	}
	char* aux_char = new char[buffer.size() + 1];
	strcpy_s(aux_char, buffer.size() + 1, buffer.c_str());
	char* token = strtok(aux_char, ",");
	int nr = 0, nc = 0;
	while (token)
	{
		rez[nr][nc++] = token;
		if (nc == nr_coloane)
		{
			nr++;
			nc = 0;
		}
		token = strtok(NULL, ",");
	}
	return rez;
}

void fisier_csv::scrie_text(vector<string> valori, int nr_valori)
{
	ofstream g(this->nume);
	for (int i = 0;i < nr_valori;i++)
	{
		g << valori[i];
		if (i != nr_valori - 1) g << ",";
	}
	g.close();
}

structura_fisiere::structura_fisiere()
{
	fbin = NULL;
	ftext = NULL;
	nr_fbin = 0;
	nr_ftext = 0;
}

void structura_fisiere::executa_comenzi_initiale(int argc, char* argv[])
{
	int nr_tabele;
	if (argc > 6)
	{
		throw db_exception("Prea multe argumente pentru functia main");
	}
	string** structura_tabele = this->structura_tabele.citeste_text(nr_tabele);

	for (int i = 0;i < nr_tabele;i++)
	{
		string nume_tabel = structura_tabele[i][0];
		int nr_coloane;
		int ignore = sscanf(structura_tabele[i][1].c_str(), "%d", &nr_coloane);
		string* nume_coloane = new string[nr_coloane];
		tip* tipuri_coloane = new tip[nr_coloane];
		int* dimensiune_coloane = new int[nr_coloane];
		string* valoare_implicita = new string[nr_coloane];
		int k = 0;
		for (int j = 0;j < nr_coloane*4;j+=4)
		{
			nume_coloane[k] = structura_tabele[i][j + 2];
			if (structura_tabele[i][j + 3] == "TEXT") tipuri_coloane[k] = text;
			if (structura_tabele[i][j + 3] == "INTEGER") tipuri_coloane[k] = integer;
			if (structura_tabele[i][j + 3] == "FLOAT") tipuri_coloane[k] = real;
			ignore = sscanf(structura_tabele[i][j + 4].c_str(), "%d", &dimensiune_coloane[k]);
			valoare_implicita[k] = structura_tabele[i][j + 5];
			k++;
		}

		this->db.create_table(nume_tabel, nr_coloane, nume_coloane, tipuri_coloane, dimensiune_coloane, valoare_implicita);

		string* append_tabel = new string[nr_coloane * 4 + 2];
		append_tabel[0] = nume_tabel;
		append_tabel[1] = to_string(nr_coloane);
		k = 0;
		for (int i = 0;i < nr_coloane;i++)
		{
			append_tabel[k++] = nume_coloane[i];
			if (tipuri_coloane[i] == text) append_tabel[k++] = "TEXT";
			if (tipuri_coloane[i] == integer) append_tabel[k++] = "INTEGER";
			if (tipuri_coloane[i] == real) append_tabel[k++] = "FLOAT";
			append_tabel[k++] = to_string(dimensiune_coloane[i]);
			append_tabel[k++] = valoare_implicita[i];
		}
		append_tabel[k - 1].pop_back();

		string structura_fisier_binar = "";

		for (int i = 0;i < nr_coloane;i++)
		{
			structura_fisier_binar += append_tabel[i*4+1];
			structura_fisier_binar += " ";
			structura_fisier_binar += append_tabel[i*4+2];
			structura_fisier_binar += " ";
		}
		structura_fisier_binar.pop_back();

		fisier_binar* aux_bin = new fisier_binar[nr_fbin];
		for (int i = 0;i < nr_fbin;i++) aux_bin[i] = this->fbin[i];
		if (this->fbin) delete[]this->fbin;
		this->fbin = new fisier_binar[nr_fbin + 1];
		for (int i = 0;i < nr_fbin;i++) fbin[i] = aux_bin[i];
		fbin[nr_fbin++] = fisier_binar(nume_tabel,structura_fisier_binar);
		if (aux_bin)delete[]aux_bin;
		cout << "A fost recuperat tabelul " << nume_tabel << " cu coloanele: ";
		for (int i = 0;i < nr_coloane;i++)
		{
			cout << nume_coloane[i];
			if (i < nr_coloane - 1) cout << ", ";
		}
		cout << endl;
		int nr_randuri_citite;
		string** valori_citite_fisier_binar = fbin[nr_fbin - 1].citeste_binar(nr_randuri_citite);
		for (int i = 0;i < nr_randuri_citite;i++)
		{
			db.insert_into(nume_tabel, valori_citite_fisier_binar[i], nr_coloane);
			cout << "S-au introdus valori in tabelul " << nume_tabel << endl;
		}
		
	}

	for (int i = 1;i < argc;i++)
	{
		int nr_comenzi;
		ifstream f(argv[i]);
		if (!f.good())
		{
			throw db_exception("Nu exista fisierul specificat ca argument");
		}
		while (true)
		{
			char buffer[400];
			f.getline(buffer, 400);
			string comenzi = string(buffer);
			executa_comanda(comenzi);
			if (f.eof()) break;
		}
		f.close();
	}
}

//functia principala care executa comanda
void structura_fisiere::executa_comanda(string comenzi)
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
		if (nume_tabel == "TEMP") throw db_exception("Numele tabelului nu poate fi 'temp'");
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
			int ignore = sscanf(cuvinte[4 * index + 5].c_str(), "%d", &dimensiuni_coloane[index]);
			//valoarea implicita a coloanei
			valori_implicite[index] = cuvinte[4 * index + 6];

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

		string* append_tabel = new string[nr_coloane * 4 + 2];
		append_tabel[0] = nume_tabel;
		append_tabel[1] = to_string(nr_coloane);
		int k = 2;
		for (int i = 0;i < nr_coloane;i++)
		{
			append_tabel[k++] = nume_coloane[i];
			if (tipuri_coloane[i] == text) append_tabel[k++] = "TEXT";
			if (tipuri_coloane[i] == integer) append_tabel[k++] = "INTEGER";
			if (tipuri_coloane[i] == real) append_tabel[k++] = "FLOAT";
			append_tabel[k++] = to_string(dimensiuni_coloane[i]);
			append_tabel[k++] = valori_implicite[i];
		}

		string structura_fisier_binar = "";
		for (int i = 0;i < nr_coloane;i++)
		{
			structura_fisier_binar += append_tabel[(i + 1) * 4 - 1];
			structura_fisier_binar += " ";
			structura_fisier_binar += append_tabel[(i + 1) * 4];
			structura_fisier_binar += " ";
		}
		structura_fisier_binar.pop_back();
		fisier_binar fisier(nume_tabel, structura_fisier_binar);
		for (int i = 0;i < k;i++)
		{
			append_tabel[i] += ",";
		}
		append_tabel[k - 1].pop_back();
		structura_tabele.scrie_text_append(append_tabel, nr_coloane * 4 + 2);

		ofstream g(fisier.nume, ios::binary);
		g.close();

		fisier_binar* aux_bin = new fisier_binar[nr_fbin];
		for (int i = 0;i < nr_fbin;i++) aux_bin[i] = fbin[i];
		if (fbin) delete[]fbin;
		fbin = new fisier_binar[nr_fbin + 1];
		for (int i = 0;i < nr_fbin;i++) fbin[i] = aux_bin[i];
		fbin[nr_fbin++] = fisier;
		if (aux_bin)delete[]aux_bin;

	}
	//verificare daca comanda este de tip "Drop Table"
	else if (cuvinte[0] == "DROP" && cuvinte[1] == "TABLE")
	{
		//Numele tabelului care trebuie sters
		string nume_tabel = cuvinte[2];
		//afisare mesaj aferent executarii comenzii
		db.drop_table(nume_tabel);
		cout << "Tabelul " + nume_tabel + " a fost sters" << endl;

		int k = 0;
		fisier_binar* aux_bin = new fisier_binar[nr_fbin];
		for (int i = 0;i < nr_fbin;i++) aux_bin[i] = fbin[i];
		if (fbin) delete[]fbin;
		fbin = new fisier_binar[nr_fbin - 1];
		for (int i = 0;i < nr_fbin;i++)
			if (aux_bin[i].nume != "_" + nume_tabel + ".bin") fbin[k++] = aux_bin[i];
		nr_fbin--;
		if (aux_bin)delete[]aux_bin;
		remove(("_" + nume_tabel + ".bin").c_str());
		structura_tabele.scrie_text_sterge(nume_tabel);
	}
	//verificare daca comanda este de tip "Display Table"
	else if (cuvinte[0] == "DISPLAY" && cuvinte[1] == "TABLE")
	{
		//Numele tabelului care trebuie afisat
		string nume_tabel = cuvinte[2];


		fisier_txt* aux = new fisier_txt[nr_ftext];
		for (int i = 0;i < nr_ftext;i++)
		{
			aux[i] = ftext[i];
		}
		if (ftext)delete[]ftext;
		ftext = new fisier_txt[nr_ftext + 1];
		for (int i = 0;i < nr_ftext;i++)
		{
			ftext[i] = aux[i];
		}
		string nume_fisier = "display_" + to_string(nr_ftext + 1) + ".txt";
		ftext[nr_ftext++] = fisier_txt(nume_fisier);

		//afisare mesaj aferent executarii comenzii
		db.display_table(nume_fisier, nume_tabel);

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
		db.insert_into(nume_tabel, valori, nr_cuvinte - 4);
		cout << "S-au introdus valorile in tabelul " << nume_tabel << endl;
		for (int i = 0;i < nr_fbin;i++)
		{
			if (fbin[i].nume == "_" + nume_tabel + ".bin")
			{
				fbin[i].scrie_binar_append(valori, nr_cuvinte - 4);
			}
		}
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
		int camp = -250;
		int nr_coloane_sters = 0;
		for (int i = 0;i < db.nr_tabele;i++)
		{
			for (int j = 0;j < db.tabele[i].nr_coloane;j++)
			{
				if (db.tabele[i].coloane[j].nume == nume_coloana && db.tabele[i].nume == nume_tabel)
				{
					camp = j;
					nr_coloane_sters = db.tabele[i].nr_coloane;
					if (db.tabele[i].coloane[j].Tip == real)
					{
						valoare = to_string(stof(valoare));
					}
					break;
				}
			}
		}
		for (int i = 0;i < nr_fbin;i++)
		{
			if (fbin[i].nume == "_" + nume_tabel + ".bin")
			{
				fbin[i].scrie_binar_sterge(valoare, camp, nr_coloane_sters);
			}
		}
	}
	//verificare daca comanda este de tip "Select"
	else if (cuvinte[0] == "SELECT")
	{
		string nume_tabel;
		fisier_txt* aux = new fisier_txt[nr_ftext];
		for (int i = 0;i < nr_ftext;i++)
		{
			aux[i] = ftext[i];
		}
		if (ftext)delete[]ftext;
		ftext = new fisier_txt[nr_ftext + 1];
		for (int i = 0;i < nr_ftext;i++)
		{
			ftext[i] = aux[i];
		}
		string nume_fisier = "select_" + to_string(nr_ftext + 1) + ".txt";
		ftext[nr_ftext++] = fisier_txt(nume_fisier);
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


			db.select(nume_fisier, nume_tabel, nume_coloane, 2, nume_coloana, valoare);

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
			db.select(nume_fisier, nume_tabel, nume_coloane, nr_coloane_afisare, nume_coloana, valoare);
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
		int camp = -250, camp_set = -250;
		int nr_coloane_sters = 0;
		for (int i = 0;i < db.nr_tabele;i++)
		{
			for (int j = 0;j < db.tabele[i].nr_coloane;j++)
			{
				if (db.tabele[i].coloane[j].nume == nume_coloana && db.tabele[i].nume == nume_tabel)
				{
					camp = j;
					nr_coloane_sters = db.tabele[i].nr_coloane;
					if (db.tabele[i].coloane[j].Tip == real)
					{
						valoare = to_string(stof(valoare));
					}
				}
				if (db.tabele[i].coloane[j].nume == nume_coloana_set && db.tabele[i].nume == nume_tabel)
				{
					camp_set = j;
					if (db.tabele[i].coloane[j].Tip == real)
					{
						valoare_set = to_string(stof(valoare_set));
					}
				}
			}
		}
		for (int i = 0;i < nr_fbin;i++)
		{
			if (fbin[i].nume == "_" + nume_tabel + ".bin")
			{
				fbin[i].scrie_binar_inlocuire(valoare, camp, valoare_set, camp_set, nr_coloane_sters);
			}
		}
	}
	else if (cuvinte[0] == "IMPORT")
	{
		if (nr_cuvinte != 3)
		{
			throw db_exception("Comanda import are obligatoriu 3 cuvinte");
		}
		int nr_coloane = 0;
		for (int i = 0;i < db.nr_tabele;i++)
		{
			if (db.tabele[i].nume == cuvinte[1])
			{
				nr_coloane = db.tabele[i].nr_coloane;
				break;
			}
		}
		fisier_csv csv(cuvinte[2], nr_coloane);
		int nr_elemente = 0;
		string** valori_csv = csv.citeste_text(nr_elemente);

		for (int i = 0;i < nr_elemente;i++)
		{
			for (int j = 0;j < nr_coloane;j++)
			{
				valori_csv[i][j].erase(remove(valori_csv[i][j].begin(), valori_csv[i][j].end(), '\''), valori_csv[i][j].end());
			}
			db.insert_into(cuvinte[1], valori_csv[i], nr_coloane);
			cout << "S-au introdus valorile in tabelul " << cuvinte[1] << endl;
			for (int k = 0;k < nr_fbin;k++)
			{
				if (fbin[k].nume == "_" + cuvinte[1] + ".bin")
				{
					fbin[k].scrie_binar_append(valori_csv[i], nr_coloane);
				}
			}
		}
	}
	else throw db_exception("Aceasta comanda nu exista");
}

void structura_fisiere::plateste_taxe()
{
	int poz = -1;
	for (int i = 0;i < db.nr_tabele;i++)
	{
		if (db.tabele[i].nume == "PLATITORI_TVA" &&
			db.tabele[i].nr_coloane==3&&
			db.tabele[i].coloane[0].nume=="NUME"&&
			db.tabele[i].coloane[1].nume == "TIP"&&
			db.tabele[i].coloane[2].nume == "VENITURI") poz = i;
	}
	if (poz >= 0)
	{
		table tabel = db.tabele[poz];
		list<row>l;
		for (int i = 0;i < tabel.nr_randuri;i++)
		{
			l.push_back(tabel.randuri[i]);
		}
		vector<platitor_tva*>v;
		for (list<row>::iterator it = l.begin();it != l.end();it++)
		{
			if (it->valori_rand[1] == "FIRMA")
			{
				firma aux = firma(it->valori_rand[0], it->valori_rand[1], stof(it->valori_rand[2]));
				v.push_back(&aux);
			}
			if (it->valori_rand[1] == "PERSOANA JURIDICA")
			{
				persoana_juridica aux = persoana_juridica(it->valori_rand[0], it->valori_rand[1], stof(it->valori_rand[2]));
				v.push_back(&aux);
			}
			if (it->valori_rand[1] == "PERSOANA FIZICA")
			{
				persoana_fizica aux = persoana_fizica(it->valori_rand[0], it->valori_rand[1], stof(it->valori_rand[2]));
				v.push_back(&aux);
			}
		}
		for (int i = 0;i < v.size();i++)
		{
			int nrZile;
			cout << "Introduceti numarul de luni intarziate de entitatea " << tabel.randuri[i].valori_rand[0] << " este : ";
			cin >> nrZile;
			cout << "Entitatea " << tabel.randuri[i].valori_rand[0] << " are de plata " <<
				v[i]->calcul_tva() + v[i]->calcul_restanta(nrZile) << endl;
		}
	}
}

void afisare_linii(int nr)
{
	for (int i = 0;i < nr;i++)
	{
		cout << "-";
	}
	cout << endl;
}

platitor_tva::platitor_tva()
{
	venituri = 0;
}

platitor_tva::platitor_tva(float venituri)
{
	this->venituri = venituri;
}
float platitor_tva::getVenituri()
{
	return this->venituri;
}
void platitor_tva::plateste_taxe()
{
	venituri -= calcul_tva();
}
persoana::persoana()
{
	nume = "";
}
persoana::persoana(string n, float venituri):platitor_tva(venituri)
{
	nume = n;
}

persoana_fizica::persoana_fizica(string c, string n, float venituri):persoana(n,venituri)
{
	cnp = c;
}
float persoana_fizica::calcul_tva()
{
	return 0.24 * getVenituri();
}
float persoana_fizica::calcul_restanta(int nr_luni)
{
	return 0.24 * getVenituri() * 0.05 * nr_luni;
}
persoana_juridica::persoana_juridica(string c, string n, float venituri) :persoana(n, venituri)
{
	cui = c;
}
float persoana_juridica::calcul_tva()
{
	return 0.19 * getVenituri();
}
float persoana_juridica::calcul_restanta(int nr_luni)
{
	return 0.19 * getVenituri() * 0.1 * nr_luni;
}
firma::firma(string a, string c, float venituri) :platitor_tva(venituri)
{
	adresa = a;
	cif = c;
}
float firma::calcul_tva()
{
	return 0.15 * getVenituri();
}
float firma::calcul_restanta(int nr_luni)
{
	return 0.15 * getVenituri() * 0.07 * nr_luni;
}

string structura_fisiere::gandalf_db = R"(

                                                                                                                  ,--,                     
                                                                               ,--.                            ,---.'|                     
                                             ,----..      ,---,              ,--.'|    ,---,       ,---,       |   | :       ,---,.        
                                            /   /   \    '  .' \         ,--,:  : |  .'  .' `\    '  .' \      :   : |     ,'  .' |        
                                           |   :     :  /  ;    '.    ,`--.'`|  ' :,---.'     \  /  ;    '.    |   ' :   ,---.'   |        
                                           .   |  ;. / :  :       \   |   :  :  | ||   |  .`\  |:  :       \   ;   ; '   |   |   .'        
                                           .   ; /--`  :  |   /\   \  :   |   \ | ::   : |  '  |:  |   /\   \  '   | |__ :   :  :          
                                           ;   | ;  __ |  :  ' ;.   : |   : '  '; ||   ' '  ;  :|  :  ' ;.   : |   | :.'|:   |  |-,        
                                           |   : |.' .'|  |  ;/  \   \'   ' ;.    ;'   | ;  .  ||  |  ;/  \   \'   :    ;|   :  ;/|        
                                           .   | '_.' :'  :  | \  \ ,'|   | | \   ||   | :  |  ''  :  | \  \ ,'|   |  ./ |   |   .'        
                                           '   ; : \  ||  |  '  '--'  '   : |  ; .''   : | /  ; |  |  '  '--'  ;   : ;   '   :  '          
                                           '   | '/  .'|  :  :        |   | '`--'  |   | '` ,/  |  :  :        |   ,/    |   |  |          
                                           |   :    /  |  | ,'        '   : |      ;   :  .'    |  | ,'        '---'     |   :  \          
                                            \   \ .'   `--''          ;   |.'      |   ,.'      `--''                    |   | ,'          
                                             `---`                    '---',---,   '---',---,.                           `----'            
                                                                         .'  .' `\    ,'  .'  \                                            
                                                                       ,---.'     \ ,---.' .' |                                            
                                                                       |   |  .`\  ||   |  |: |                                            
                                                                       :   : |  '  |:   :  :  /                                            
                                                                       |   ' '  ;  ::   |    ;                                             
                                                                       '   | ;  .  ||   :     \                                            
                                                                       |   | :  |  '|   |   . |                                            
                                                                       '   : | /  ; '   :  '; |                                            
                                                                       |   | '` ,/  |   |  | ;                                             
                                                                       ;   :  .'    |   :   /                                              
                                                                       |   ,.'      |   | ,'                                               
                                                                       '---'        `----'                                                 
                                                                                                                                           


)";

string structura_fisiere::gandalf =
R"(         ............ ###%#%%&(%*....................................................................................................................................,,,,,,,/#%%%&&&&&&&&&&&&%%%%#%%%%%%
 ....................(#%&&&%%&&(,.............................................................................   ..,***( .......................................,.,,,,,,,,,,%%%%&&&&&&&&&&&&%%%%&%&#%&%%
.................... #%#&&%#((#..........................................................................  ,*******,*//*/#, ./.....................................,,,,,,,(#%%#%%%&&&&&&%%%&%%%%%&&#%&&&
....................##%.(###%&(#%*................................................................... *,*////*//////**,.  /##,..................................,,,,,,,,*###%%%%%%&&&&&&%%%&%%%%%#%%%%&&
.................../%#@ %#%&&%#####/...............................................................,****///*/*(/((((((((/.%,..................................,,,,,,,,,,%%%%&&&&&%%&&&&&%%%%%%&#%%#%%%&&
...................%%(&(##%##%&&%%/,..............................................................*////////((((#(####((((#.................................,,,,,,,,,,,,%%%%%&&&&&&%&&%%%%%%%&%%%%%%%%%%&
.....................&%#%%&&%&&%%%%#.............................................................***//(///(/((((((((#((((((..................................,,,.,,,,.#%%%%&&&&&&%%%%%%%%&&&&&%%%%%%%%&&
.......................#%%@&%@%%##%##/..........................................................*////////(((((#((((((((((((...........................................%%%%&&&&&&%%%%#%%#&&&&&%%%%%%%%&%&
.......,,.,...,..,...,,*%%%&%%&%##&%.,,,,........,,,.......,................................. *///(((((((#######(((((((/((*...........................................,%%%%%&&&%%%%##%%%&&&%&%%%%%&%%%%&
,,,,,,,,,,,,,,,,,,,,,,,,/%&&%&&&&&%#.,,,.,,,,,,,,,,,,..,,,....................,..,...,...   .*,***////////////******/(((((*............................................../%%%&&%%%%%##%&&&&%%%%%%#%%%%%&
,,,,,,,,,,,,,,,,,,,,,,,,,,&#%&&&%&%&#.,,,,,,,,,,,,,,,,,...,.............,,.... ...    ...,/(%#%%%%%###(/***,,,,,,,,..  ...        .................     ...  ...............,%%%%%%%#%%&&&&%%%&%%%%%%#&&
,,,,,,,,,,,,,,,,,,,,,,,,,,(%&&&&&%#%#,,,,,,,,,,,,,,,,,.......,....,.,*%%%%%%%&%&&&&&&&&&&&&&&&&&&%%%%%%%&&&&&&&&&&&%&&&&&&&&%%%%%%%###/*                ......................../&&&%%&&&&%%%%%%%%#%%#&&
,,,,,,,,,,,,,,,,,,,,,,,,,,,@&&&##%%%#,,,,,,,,,,,,,..................%%&&%&&&&&&&&&&&&&&&&&&&&%%%%####%%%###%%%%%%&&%&&%&&&&&&&&%%%%%%%%%%%%/ ..     .   .........................(#%%%&&%%%%%%%%%##%%%&&
,,,,,,,,,,,,,,,,,,,,,,,,,,,,&&%&##%%%,,,,,,,,,,....................#%&&&&&&&&&&&&&&&&&&&&&%&&%&&%%%##%%&%%%%%%%%%%%%%%&&%%%&&&&&&&&%%%%%%%%%%%# ...................................,/&&&%%%%%%%%%#&%%%&&
,,,,,,,,,,,,,,,,,,,,,,,,,,.,.%#&&##%%%.,,..........................*%&&&&&&&&&&&&&&&&&&&&&&&%###(####%%%%%#####%#%%%%%&&&%%%%%&&&&&&&%%%%%%%%%%# . ................................,#&&&%%%%%%%%%%%%%&%&
,,,,,,,,,,,,,,,,,,,,,,,....../&%#&%%%%,.............................*%&&&&&&&&&&&&&&&&&&%%&&%(((##/(####%#%#######%%%%%%%&&%%%%&&&&&&&&%%%%%%%%#...................................(&%&&%%%%%%%%%#%%%%%&
,,,,,,,,,,,,,,,,,,,,,,.,......&%%%%%%%/...............................#&&&&&&&&&&&&&&&&%%%%%%##(/###%%&###((#####%#%%%%%&&&%##%%&&&&&&&&%%%%%%%%..............................,,.,,/*,%%&&%%%%%%%%#%%&%&
,,,,,,,,,,,,,,,,,,,,,,,......,(#%&%&&%%.................................,&%&&&&&&&&&%%&%%%%%##(((#####%%%###(#######%%%%%%&###%%%%%%%%%%%%%%%%%..................,,,,*//(((((((((((###%%%%%%%%%%%%%%%&%&
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.@%%%&%&%&....................................,%&&@%&%%&%&%%%%##(/#%(##%%%#%((((####%%#%%%%%%%##%%%%&&&&&&&&%%&,//(((((///////((((((((((((((((((((###((#%#%%%&&%%%%%#%%%&&
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,/&&&%&&%%.,,,,,,,,,,,,,,,,,,,,,....,,,,,,,,,,,,,,,*&&%%&&######((#%#((((((%##(((####%%%%%%%#%###%%%&%&&&%%&/////////((//((((((((((((((((((((((((((#%%%%#(%%%%&&&%%%%%%&&&
***,,,,,,,,,,,,,,,,,,,,,,,,,,,,,@&%%&%%%,,,,,,,,,,,,,,,,,,,,,,,,,,,,,***,,,,,,,,,///((##((##########((((######%%#%%###%%#%%###(##%%%%(//////(((//(((((((((((((((((((((((####(((#%%%%%%%#%%%%%&%&&###%&&&
**********,,,,,,*************,,,/%%%%%%%&,,,,,***//((//,.,/,,,/////////////*/,*/***///(##(##%#%%##################(##%%##%%##(###%%%(***/(((/((((((((((((((((((((((((((##(((((#%#%%######%%%%%%&&&&&&&&&
,,,,,,,,,,,,,,,,,,,,,,,,,**//////&&%%&%%%((((((((((((//(((*(//((((((((((((/,****,,///(((##(#%#%##########%%######((#%%%%%%%%(#%##%%%%%(#.,*((/(/((((((((((((((((((((((((((((#(##((##%(%##%%%%%#%%%&&&&@&
//*//(((((((((((((/(((((((((((((/%&%%%%%%&/((((((((/////(((((((((((((((///*/*.*/**((//(###########(##(##%#%%####((#(#(%&#%%%#(%#&%%(#%#,,...*(/((((####((((((((#((((#((####(##(###%%#####%%%%%%#%%%%%%&&
(((/((((((((((((((((((((((//((((((&%%&%%&&%((///////((((((//(/((((((/(((,/*,,/(**///(########(%#%##(#(#%%%%#%%########&&&%&%##%%#%##%%%%(,,,,**/(#(##((((###(((((((#########(#((#%####%#%%%%%%%%#%%%%&&%
((((((((((((((((((((((((((((((((((&&%%%&%&&//////((((((((((((((((((((//*(/,%(/*////((#(##(#(###%##(#(#%#%###%#((##(#((%%&%&######%%##%%%%#(//*//(#######(((###############%#(##%&%%%&%%#%%%%%%%%%&&%&&#%
(((((##(((((((((#((((((((//((((((//&%%&%&&&#(((((((((((((((((((((((((((*/,/***///((#((#########%%##(%###%%##%(###%#((#%&&&&##%#(#%%%##%%%##/(/*/,(######(((###########%%###########%&&&(#%%%%%&%%%######
(((##(((((((((#((((/((((((#(#((((((%&%&&&&&&((((((#(#(((((((((((###(((*//#%///(//#/((((%#%###%%%#(#(%#%%%##%%##(###(##%%%&&&%###%%%&&%##%%##(((/%(**########%%#%%%%##########%%%%&%&&&%%##%%##%##&%&&&&@
#((((((########(#(#(#####(((#((((##(&%&&%%&&((((#####((((((#####(/***%#/&(*//(*/(#(/##(##(###%%##((#####%%#####(%%#(%%&&&&&&&##%%%%#%&%%##%##(%/#%%(%#(#(###%###############(########%%%#%%&%%%#%&&&&&&&
####################################%%&&&%%&%####(#########((((((/*/#%##/(#(///(#(####(######%##((###%#%&##%########%%&&&&&&##&%(&&&%%&%###((/####%%#%%#*(((#(((((((((/(((((((###(#%%###%&&&&&&%#%#%%%%&
#############################((((((((&&&&&&%&(((/////((#///(((((/%%&%%#/%#(/(/(#((#########%%%#(((#%%%##%(%%######(%&&&&&&%#&%&%%%%&&&%%%&#####(###%%#%%#%/####%%%%%%%##%%%%%&&%&%&&&&%%%%&&&&&&%%%&%%&%
%###%%%###%####((((((((((((((((###%((%&&&&%%&%%(///(((((((((*#%%%&&%%##&#(%((#(/(###(%##%#%%####(###%%%%#%%###%###%%&&&&&&%%&#%%&&&&%&%%%%#%%%%#%%##%##%%#%%%#%#%#%#######%&%%&%&&%%&&&&&&&&&&&&&&&&&&&&
##%%####%#######%##%########(#(((####(&&&&%%&&((##((((((((%%%%&&&%%%(%%(#((#(((#(###%##%#&%%(#(##%#%%%##%%%%####(##&&&&&&&%%%&&&&&&&&&%&%%%#%&%%%%&%%%##%#%&%/#############(######%%%%%%%%%%%%%&&&&&&&&&
###(##%%###%###%######(((##%#((##((((((&&&&%%%&((%%##%/%%%&&&&&%%%#(%&%##(/(##(########%%%%(####%##%%%%%%%%#(%#%#&&@&&&&&&%&&%%&%%%%&&&%%%#%&&&%#%&&&%%#%#%&&%/###%%%%&%%%%%%%%%%%%%%%%%%&%&&&&&&&&&&&&&
&#%&%%####((((##(###%#%%%%%%####(((((#(#&&&%%&%%(((*&&&&&&&&&&%%###&&&%%#((((#(#((####%%%###(%###%%#%%%%%%######%&&@&&&&%&&&&%&%%%%&&&%%%%%%%&&%%#%&&&%%(%&&&%###%%#%&%%%%%%%%&%%&&&%%%&&%%%%&&%%%%&&&&&
%####%%%%%##%#%%%#######%###%#%%##(((((##%&&%%%%#*%&&&&%&&&&%%#%%%&&&%%##(#%#(#(#####%######%##%%#%#%%%##%##%##&&&&&&&&&%%%%&%&%%%%&%&&%%%#%%%&%%%%&&&%%%#&&&&%%(######%%%##%%%%%%%%%&&&&&&&%%%&&&&&&&&&
#%%%&%#%%%%###(#%%&&%%#%%%%%%##%&%###(((((&&%%%%&%&&&&&&&&&(%%%%%%&&%&%%##(##((((##%%%%########%%#%%%%#%##%#%%&&&&&&&&&&&&&%&&&%%%%&%&&%%%%%%%%&&%#&&%%&&%%&&&%%%(###%%#(#((((#%%%%%%%&&&&&%%&%%%%&&&&&&
#%#%##%%%&%%%&&&%%%%###%&##&%###&%@&%%%####&&&%%%%%&&&&&#%&&&&&&&&&&&&%%#((%#((#(##%%%%####%%#%#%%%%%%#####%&&&&&&&&&&&&&&&&@&%%%&%%%%%%%%%%%%%&&&%#&&%&&&%@&&%%%##,&&&&@@@@@&&&&&&&&&&&&&&&@&&@@&&&&&&&
##%##########%%%%&%##%%%#%%&%%%#(((#((##%%%%&&&%&&&&&&%&&&&&&&&&&%%&&&&%(((((#(#%%%%%#%%#%%##%%%%%%%%###%%&&&&&&&&&&&&&&&&&%&&&%&&%%&&%%%%%%%%%&&&%#%%%%&&&&&&&%%%*&&&&&&&&&&&&&&&&&&&&@&@&&&&&&&&&&&&&&
%#%#######&##%%########(#############%%%%#(#&&&&&&&&&&%&&&&&&&&&&&%%&&##(#####%(%%%#%#%##%#&#%&%%%%%%%#%%&&&&&&&&&&&&&&&&&&%&&&%&&&&%%%%%%%%%%%&&&&%#%%%@&&%@&&&&%##@@&#%&%%&&&&&&&&%&%&&&&&&&&&&&&&&&&&
%%&%##%%#(#####&&&@##((#((#%#(############@(&&&&&&&&@&#%%&&&&&&&&&&%%#%##((#%%#%%%%%%%%##%%%#%&#%%%%%%%&@&&&&&&&&&&&&&&&&&&&%%%&&%&%%&&&%%%%%%%&&&&&%#%#@@&%@&&&&&###@&%%%%%#%#%&&%%%%%%%&&&&&&&&&&&&&&&
%%###%&%%&&%%%%%%%%%###%%%#######/######***((/#&&&&&((((#%%&&&&@@&&%%#(((#%%%%%&&%%%%%%%%%#&%%%%%%%&&&&@@&@&&&&&&&%&&&&&&&&&&%&%&&&%%%%&&&%%%%%&&&&&&%%%@@&%@&&&&&%%%%&%#%%%%%%%%&&&%&%%&&&&&&&&&&&&&&&@
%%%&&&%%&&%##%%%%####%&&&&%%###(#(#&%#(###########%#&####&&&&%&&&#(#%#%%&%%&&&%%%%%%%%&%&#%%%%%&%&&&&@@&@&&&&&&&%&&&&&&&&&&&&%@&%&&&&%%%&&&&%%%%&&&&&&%%@@&&&@@&@&%%%@&%%%&&&%&&&&&&%&&&&&&&&&&&&&&&&&&&
&&%&%%%%#%%%%%%#%%%%%%%########%&&%%%#%@%#%%%@@@&%&&&&@@@&%&&&@%%&&#&&@&%%&&%%%&#%%%&%%%%%&&%&&&&&&&&&@&&&&&&&&&&&&&&&&&&&&&&%%@&%%&&&%%%&&&&%%%&&&&&&&%@@@&&@@@&&%&@@&%%#%#%#&&&&&&&&&@@&@@&&&&&&&&&&@@
%%%%%%%%%%%%##%##%####(#####%@@&%&%%##@#########%####&%@@@&&%&&&&&@@@@@&%&%&%%%%%%#%%&%%%%%&&&&&&&&&@&&@&@@&&&&&&&&&&&&&&&&&&&%%&&%%&&&&%%&&&&%%%&&&&&&%&@@&&@&&&&&@@&&%%&#%&&%&%%&&&&@&%%&%%%&&&&&&&&@@
#########%###%%%%%####%#((#%%%%%&&&(#&&@%%%%&&&&&%%###%%&@&&&&@@&&&@&&@@&&%%%%%&%&%&%&&&&&&@&&&&&&@&@&&&@&@&&&&&&&&&&&&&&&&&&&%&&&&%&&&&&%&&&@&&%&&&&&&&&@@&&&&&&&@@&&&%%%&%%%%&%%%%%%%%%%%&@&&&%&&&&&&&
######%%%%###########(/(#%%%%%%&&%&%%&&&%%%%%#%%%%%&&&#(%@&&&&&@@&&&@@&@&@&&&&%&&&&@&&&&%&&@&&&&&&@&@&@&@&@&&&&&&&&&&&&&&&&&&&%&&@&&%&&&&&%&&@@&&&&&&&&&%@@&@@&&&@@@&&%&%%&%#&&%%%%&&&@&&&&&&&&&&&&&&&&&
%#######%#############%%&&&&&&%##%&%&%@&&%%%##%####(%%%@@@&&&&&@@@&&@@&@&&&%&&&&&&&&&%&&&&&@&&&&&&@@@&&&@@@@&&&&&&&&&&&&&&&&&&&&&&@@&%&&&&&%&@@@&&&&&&&&%@@&@@&@@@@&&&&%%&%%%(%%%%&%%&%&%&&&&&&&&&&&&&&%
)";