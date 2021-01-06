#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;
//enumerarea pentru tipurile posibile de data
//integer are valoarea 0, real 1 si text 2
enum tip { integer, real, text };

class database;
class table;
class column;
class row;

class column
{
public:
	friend class table;
	string nume;
	int dimensiune;
	tip Tip;
	string valoare_implicita;


	column();
	column(string nume, int dimensiune, tip Tip, string valoare_implicita);

};

class row
{
public:
	friend class table;
	string* valori_rand;
	int nr_coloane;

	row();
	row(string* valori_rand, int nr_coloane);
	row(const row& r);
	row& operator=(const row& r);
	~row();
};

class table
{
public:
	friend class database;
	string nume;
	column* coloane;
	int nr_coloane;
	row* randuri;
	int nr_randuri;


	table();
	table(string nume, column* coloane, int nr_coloane, row* randuri, int nr_randuri);
	table(const table& t);
	table& operator=(const table& t);
	~table();

	void display_table();
	void insert_into(string* valori);
	void delete_from(string nume_coloana, string valoare);
	void select(string* nume_coloane, int nr_coloane_afisare, string nume_coloana, string valoare);
	void update(string nume_coloana, string nume_coloana_set, string valoare, string valoare_set);

	row* delete_row(int index);
	int find_column_index(string coloana_to_find);

};

class database
{
public:
	table* tabele;
	int nr_tabele;

	database();
	database(table* tabele, int nr_tabele);
	database(const database& db);
	database& operator=(const database& db);
	~database();

	void create_table(string nume_tabela, int nr_coloane, string* nume_coloane, tip* tipuri_coloane, int* dimensiune, string* valoare_implicita);
	void drop_table(string nume_tabela);
	void display_table(string nume_tabela);
	void insert_into(string nume_tabela, string* valori, int nr_valori);
	void delete_from(string nume_tabela, string nume_coloana, string valoare);
	void select(string nume_tabela, string* nume_coloane, int nr_coloane_afisare, string nume_coloana, string valoare);
	void update(string nume_tabela, string nume_coloana, string nume_coloana_set, string valoare, string valoare_set);

	table* delete_table(int);
	int find_index(string);
};

//clasa care se va ocupa de erori
class db_exception : public exception
{
public:
	db_exception();
	db_exception(const char*);
	db_exception(string);
};

class fisier_binar
{
public:
	string nume;
	string structura_tabel;
	fisier_binar();
	fisier_binar(string, string);
	string** citeste_binar(int&);
	void scrie_binar_append(string*, int);
	void scrie_binar_sterge(string);
	void scrie_binar_inlocuire(string, string*, int);
};

class fisier_text
{
public:
	string nume;
	virtual string** citeste_text(int&) = 0;
};

class fisier_txt:fisier_text
{
public:
	fisier_txt(string);
	void scrie_text(string*, int);
	string** citeste_text(int&) override;
	void scrie_text_append(string*, int);
	void scrie_text_sterge(string);
};

class fisier_csv :fisier_text
{
public:
	int nr_coloane;
	string** citeste_text(int&) override;
};

class structura_fisiere
{
public:
	fisier_binar* fbin;
	fisier_txt* ftext;
	int nr_fbin;
	int nr_ftext;
	database db;
	static fisier_txt structura_tabele;
	structura_fisiere();
	void executa_comenzi_initiale(int, char* []);
};

//convertire string in uppercase
string toUpper(string);

//numarul de cuvinte din comanda
int get_nr_cuvinte_string(string);

//lista cuvintelor din comanda
string* impartire_comenzi_pe_cuvinte(string);

//capitalizeaza cuvintele din comanda
void capitalizare_comenzi(string*&, int);

//verificare daca comanda are numarul de paranteze deschise
//egal cu cel al parantezelor inchise
void numara_paranteze(string);

//verificare daca comanda poate fi acceptata sintactic
void verificare_regex(string);

//parser
void executa_comanda(string, database&, fisier_binar*&, int&, fisier_txt&);