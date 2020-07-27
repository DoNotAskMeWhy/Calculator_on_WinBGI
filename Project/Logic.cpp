#include "Functions.h"

#define LGMAX 1000

using namespace std;

//ifstream fin("citire.in");
//ofstream cout("citire.out");

char S[LGMAX], * p, c[LGMAX];

string sol;

map<string, int> numar;
map<int, string> siruri;

long termen();

long factor();

// Functia eval() va "aduna" toti termenii unei expresii/subexpresii.

long eval() {
	long r = termen();
	while (*p == '+' || *p == '-') {
		switch (*p) {
		case '+':
			++p;						// trecem peste semnul "+"
			r += termen();
			break;
		case '-':
			++p;						// trecem peste semnul "-"
			r -= termen();
			break;
		}
	}
	return r;
}

/*
Functia termen() se ocupa de continutul unui termen. Acesta este compus la randul
lui din factori inmultiti.
 */
long termen() {
	long r = factor();
	while (*p == '*' || *p == '/') {
		switch (*p) {
		case '*':
			++p;
			r *= factor();
			break;
		case '/':
			++p;
			r /= factor();
			break;
		}
	}
	return r;
}

/*
Functia factor() va returna valoarea unui singur factor, care poate fi o subexpresie
sau un numar natural
 */
long factor() {
	long r = 0;
	if (*p == '(') {						// avem o subexpresie
		++p;								// trecem peste '('
		r = eval();
		++p;								// trecem peste ')'
	}
	else {
		while (*p >= '0' && *p <= '9') {		// avem un numar
			r = r * 10 + *p - '0';
			++p;
		}
	}
	return r;
}

bool este_operator(char* sir) {
	// verific daca este operator
	if (strstr(sir, "inmultit") != nullptr || strstr(sir, "produsul") != nullptr)
		return true;
	if (strstr(sir, "impartit") != nullptr || strstr(sir, "impartirii") != nullptr)
		return true;
	if (strstr(sir, "adunat") != nullptr || strstr(sir, "plus") != nullptr || strstr(sir, "suma") != nullptr)
		return true;
	if (strstr(sir, "diferenta") != nullptr || strstr(sir, "scazut") != nullptr || strstr(sir, "minus") != nullptr)
		return true;

	return false;
}

bool este_paranteza(char* sir) {
	// verific daca este paranteza
	return strstr(sir, "(") != nullptr || strstr(sir, ")") != nullptr;
}

bool este_util(char* sir) {
	// incerc sa scap de toate cuvintele inutile din sirul solutie
	return strstr(sir, "si") == nullptr && strstr(sir, "de") == nullptr && strstr(sir, "la") == nullptr &&
		strstr(sir, "cu") == nullptr && strstr(sir, "Cat") == nullptr && strstr(sir, "este") == nullptr
		&& strstr(sir, "lui") == nullptr;
}

void init() {
	// intializez "baza de date"
	numar["o"] = 1;
	numar["unu"] = 1;
	numar["un"] = 1;
	numar["doi"] = 2;
	numar["doua"] = 2;
	numar["trei"] = 3;
	numar["patru"] = 4;
	numar["cinci"] = 5;
	numar["sai"] = 6;
	numar["sase"] = 6;
	numar["sapte"] = 7;
	numar["opt"] = 8;
	numar["noua"] = 9;
	numar["zece"] = 10;
	numar["unsprezece"] = 11;
	numar["doisprezece"] = 12;
	numar["treisprezece"] = 13;
	numar["paisprezece"] = 14;
	numar["cincisprezece"] = 15;
	numar["saisprezece"] = 16;
	numar["saptesprezece"] = 17;
	numar["optsprezece"] = 18;
	numar["nouasprezece"] = 19;
	numar["zeci"] = 10;
	numar["sute"] = 100;
	numar["suta"] = 100;
	numar["mii"] = 1000;
	numar["mie"] = 1000;
	numar["milion"] = 1000000;
	numar["milioane"] = 1000000;
	siruri[1] = "unu";
	siruri[2] = "doua";
	siruri[3] = "trei";
	siruri[4] = "patru";
	siruri[5] = "cinci";
	siruri[6] = "sase";
	siruri[7] = "sapte";
	siruri[8] = "opt";
	siruri[9] = "noua";
}

void insereaza_cifra(int cifra, int& poz) {
	// fac conversia de la caracter la cifra si o pun in vectorul S
	S[poz++] = cifra + '0';
}

void insereaza__numar(int nr, int& poz) {
	int uc, temp[10] = { 0 }, j = 0;
	//sparg numarul si il inserez in vectorul temp in ordine inversa incepand cu pozitia unu cu ajutorul funcitei insereaza cifra
	while (nr > 0) {
		uc = nr % 10;
		temp[++j] = uc;
		nr /= 10;
	}
	while (j >= 1) {
		//afisez numarul
		cout << temp[j];
		//inserez una cate una cifrele numarului in pozitia corespunzatoare in vector
		insereaza_cifra(temp[j], poz);
		j--;
	}
}

void insereaza_operator(char* sir, int& poz) {
	// compar sirul dat si inserez operatorul corespunzator
	if (strstr("inmultitprodusul", sir) != nullptr)
		S[poz++] = '*';
	if (strstr("impartitimpartirii", sir) != nullptr)
		S[poz++] = '/';
	if (strstr("adunatplussuma", sir) != nullptr)
		S[poz++] = '+';
	if (strstr("diferentascazutminus", sir) != nullptr)
		S[poz++] = '-';
	if (strstr(sir, "(") != nullptr)
		S[poz++] = '(';
	if (strstr(sir, ")") != nullptr)
		S[poz++] = ')';
	//afisez expresia
	cout << S[poz - 1];
}

bool este_exponent(char* sir) {
	// am considerat sutele de mii si miliaone niste cazuri speciale de aceea nu sunt aici
	return strstr(sir, "mie") != nullptr || strstr(sir, "zeci") != nullptr ||
		strstr(sir, "sute") != nullptr || strstr(sir, "suta") != nullptr;
}

void convertor_expresie_matematica() {
	int Suma = 0, Suma1 = 0, suma_partiala = 0, poz = 0;
	char* sir;
	bool ramas = false;
	sir = strtok(c, " ?,.");
	while (sir) {
		// daca gasesc un operator verific sa nu am nimic ramas de adunat la suma, introduc numarul care tocmai s-a terminat si operatorul
		if (este_operator(sir) || este_paranteza(sir)) {
			if (Suma != 0 || ramas) {
				if (ramas || Suma1) {
					if (Suma < 1000000)
						Suma += suma_partiala;
					else {
						Suma1 += suma_partiala;
						Suma += Suma1;
						Suma1 = 0;
					}
				}
				insereaza__numar(Suma, poz);
				Suma = 0;
				Suma1 = 0;
				suma_partiala = 0;
				ramas = false;
			}
			insereaza_operator(sir, poz);
		}
		else {
			// daca cuvantul care il am va face parte din expresie
			if (este_util(sir)) {
				// daca trebuie inmultit cu ceea ce am construit pana acum
				if (este_exponent(sir)) {
					if (Suma < 1000000) {
						if (ramas) {
							suma_partiala *= numar[sir];
							Suma += suma_partiala;
							suma_partiala = 0;
							ramas = false;
						}
						else {
							if (Suma != 0)
								Suma *= numar[sir];
							else
								Suma += numar[sir];
						}
					}
					else {
						if (ramas) {
							suma_partiala *= numar[sir];
							Suma1 += suma_partiala;
							suma_partiala = 0;
							ramas = false;
						}
						else {
							if (Suma1 != 0)
								Suma1 *= numar[sir];
							else
								Suma1 += numar[sir];
						}
					}
				}
				else {
					// daca este cazul special de sute de mii sau de milioane
					if (strstr("mii", sir) != NULL || strstr(sir, "milion") != NULL ||
						strstr(sir, "milioane") != NULL) {
						if (Suma < 1000000) {
							if (ramas) {
								Suma += suma_partiala;
								suma_partiala = 0;
								ramas = false;
							}
							Suma *= numar[sir];
						}
						else {
							if (ramas) {
								Suma1 += suma_partiala;
								suma_partiala = 0;
								ramas = false;
							}
							Suma1 *= numar[sir];
							Suma += Suma1;
							Suma1 = 0;
						}
					}
					else {
						// daca nu este inseamna ca am gasit un cuantificator al unei puteri
						suma_partiala = numar[sir];
						ramas = true;
					}
				}
			}
		}
		sir = strtok(nullptr, " .?,");
	}
	// daca am ajuns la finalul expresiei este posibil sa mai fi ramas ceva din numar pe care nu l-am adunat
	if (Suma != 0 || ramas) {
		if (ramas || Suma1) {
			if (Suma < 1000000)
				Suma += suma_partiala;
			else {
				Suma1 += suma_partiala;
				Suma += Suma1;
				Suma1 = 0;
			}
		}
		insereaza__numar(Suma, poz);
	}
}

void afisare_numar_sir(int poz, int* v) {
	switch (poz) {
	case 9:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			//cout << "o suta" << ' ';
			sol.insert(sol.length(), "o suta ");
			return;
		default:
			//cout << siruri[v[poz]] << ' ' << "sute" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " sute ");
			return;
		}
	case 8:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			switch (v[poz - 1]) {
			case 0:
				//cout << "zece milioane" << ' ';
				sol.insert(sol.length(), "zece milioane ");
				v[poz] = 0;
				return;
			case 1:
				//cout << "unsprezece milioane" << ' ';
				sol.insert(sol.length(), "unsprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 2:
				//cout << "doisprezece milioane" << ' ';
				sol.insert(sol.length(), "doisprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 3:
				//cout << "treisprezece milioane" << ' ';
				sol.insert(sol.length(), "treisprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 4:
				//cout << "paisprezece milioane" << ' ';
				sol.insert(sol.length(), "paisprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 5:
				//cout << "cincisprezece milioane" << ' ';
				sol.insert(sol.length(), "cincisprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 6:
				//cout << "saisprezece milioane" << ' ';
				sol.insert(sol.length(), "saisprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 7:
				//cout << "saptesprezece milioane" << ' ';
				sol.insert(sol.length(), "saptesprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 8:
				//cout << "optsprezece milioane" << ' ';
				sol.insert(sol.length(), "optsprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 9:
				//cout << "nouasprezece milioane" << ' ';
				sol.insert(sol.length(), "nouasprezece milioane ");
				v[poz] = v[poz - 1] = 0;
				return;
			default:
				return;
			}
		default:
			//cout << siruri[v[poz]] << ' ' << "zeci" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " zeci ");
			return;
		}
	case 7:
		if (v[poz + 1] != 0 && v[poz] != 0)
			//cout << "si" << ' ';
			sol.insert(sol.length(), "si ");
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			if (v[poz + 1] || v[poz + 2])
				//cout << "unu" << ' ';
				sol.insert(sol.length(), "unu ");
			else
				//cout << "un" << ' ';
				sol.insert(sol.length(), "un ");
			return;
		default:
			//cout << siruri[v[poz]] << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 6:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			//cout << "o suta" << ' ';
			sol.insert(sol.length(), "o suta ");
			return;
		default:
			//cout << siruri[v[poz]] << ' ' << "sute" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " sute ");
			return;
		}
	case 5:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			switch (v[poz - 1]) {
			case 0:
				//cout << "zece mii" << ' ';
				sol.insert(sol.length(), "zece mii ");
				v[poz] = 0;
				return;
			case 1:
				//cout << "unsprezece mii" << ' ';
				sol.insert(sol.length(), "unsprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 2:
				//cout << "doisprezece mii" << ' ';
				sol.insert(sol.length(), "doisprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 3:
				//cout << "treisprezece mii" << ' ';
				sol.insert(sol.length(), "treisprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 4:
				//cout << "paisprezece mii" << ' ';
				sol.insert(sol.length(), "paisprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 5:
				//cout << "cincisprezece mii" << ' ';
				sol.insert(sol.length(), "cincisprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 6:
				//cout << "saisprezece mii" << ' ';
				sol.insert(sol.length(), "saisprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 7:
				//cout << "saptesprezece mii" << ' ';
				sol.insert(sol.length(), "saptesprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 8:
				//cout << "optsprezece mii" << ' ';
				sol.insert(sol.length(), "optsprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 9:
				//cout << "nouasprezece mii" << ' ';
				sol.insert(sol.length(), "nouasprezece mii ");
				v[poz] = v[poz - 1] = 0;
				return;
			default:
				return;
			}
		default:
			//cout << siruri[v[poz]] << ' ' << "zeci" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " zeci ");
			return;
		}
	case 4:
		if (v[poz + 1] != 0 && v[poz] != 0)
			//cout << "si" << ' ';
			sol.insert(sol.length(), "si ");
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			if (v[poz + 1] || v[poz + 2])
				//cout << "unu" << ' ';
				sol.insert(sol.length(), "unu ");
			else
				//cout << "o" << ' ';
				sol.insert(sol.length(), "o ");
			return;
		default:
			//cout << siruri[v[poz]] << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 3:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			//cout << "o suta" << ' ';
			sol.insert(sol.length(), "o suta ");
			return;
		default:
			//cout << siruri[v[poz]] << ' ' << "sute" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " sute ");
			return;
		}
	case 2:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			switch (v[poz - 1]) {
			case 0:
				//cout << "zece";
				sol.insert(sol.length(), "zece ");
				v[poz] = 0;
				return;
			case 1:
				//cout << "unsprezece";
				sol.insert(sol.length(), "unsprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 2:
				//cout << "doisprezece";
				sol.insert(sol.length(), "doisprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 3:
				//cout << "treisprezece";
				sol.insert(sol.length(), "treisprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 4:
				//cout << "paisprezece";
				sol.insert(sol.length(), "paisprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 5:
				//cout << "cincisprezece";
				sol.insert(sol.length(), "cincisprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 6:
				//cout << "saisprezece";
				sol.insert(sol.length(), "saisprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 7:
				//cout << "saptesprezece";
				sol.insert(sol.length(), "saptesprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 8:
				//cout << "optsprezece";
				sol.insert(sol.length(), "optsprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 9:
				//cout << "nouasprezece";
				sol.insert(sol.length(), "nouasprezece ");
				v[poz] = v[poz - 1] = 0;
				return;
			default:
				return;
			}
		default:
			//cout << siruri[v[poz]] << ' ' << "zeci" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " zeci ");
			return;
		}
	case 1:
		if (v[poz + 1] != 0 && v[poz] != 0)
			//cout << "si" << ' ';
			sol.insert(sol.length(), "si ");
		switch (v[poz]) {
		case 0:
			return;
		case 2:
			//cout << "doi";
			sol.insert(sol.length(), "doi ");
			return;
		default:
			//cout << siruri[v[poz]];
			sol.insert(sol.length(), siruri[v[poz]]);
			return;
		}
	default:
		return;
	}
}

void convertor_numar_sir(int nr) {
	int v[20] = { 0 }, uc, i = 0, j;
	// sparg numarul in cifre si il introduc in vectorul v in ordine inversa incepand de la pozitia 1
	while (nr) {
		uc = nr % 10;
		nr /= 10;
		v[++i] = uc;
	}
	// afisez numarul corespunzator in cuvinte
	for (j = i; j >= 1; j--) {
		afisare_numar_sir(j, v);
		// cazul sutelor de mii
		if (j == 4) {
			if (v[j + 1] > 1 || v[j + 2] >= 1)
				//cout << "de mii" << ' ';
				sol.insert(sol.length(), "de mii ");
			else {
				if (v[j] == 1)
					//cout << "mie" << ' ';
					sol.insert(sol.length(), "mie ");
				else if (v[j] > 1 || v[j + 1] > 1)
					//cout << "mii" << ' ';
					sol.insert(sol.length(), "mii ");
			}
		}
		// cazul milioanelor
		if (j == 7) {
			if (v[j + 1] > 1)
				//cout << "de milioane" << ' ';
				sol.insert(sol.length(), "de milioane ");
			else {
				if (v[j] == 1)
					//cout << "milion" << ' ';
					sol.insert(sol.length(), "milion ");
				else if (v[j] > 1 || v[j + 1] > 1 || v[j + 2] > 1)
					//cout << "milioane" << ' ';
					sol.insert(sol.length(), "milioane ");
			}
		}
	}
}

bool este_operator_en(char* sir) {
	// verific daca este operator
	if (strstr(sir, "multiplied") != nullptr)
		return true;
	if (strstr(sir, "divided") != nullptr)
		return true;
	if (strstr(sir, "plus") != nullptr || strstr(sir, "sum") != nullptr)
		return true;
	if (strstr(sir, "minus") != nullptr || strstr(sir, "difference") != nullptr)
		return true;
	return false;
}

bool este_util_en(char* sir) {
	// incerc sa scap de toate cuvintele inutile din sirul dat
	return strstr("How", sir) == nullptr && strstr("much", sir) == nullptr && strstr("is", sir) == nullptr &&
		strstr("by", sir) == nullptr && strstr("What", sir) == nullptr && strstr("the", sir) == nullptr
		&& strstr("result", sir) == nullptr && strstr("of", sir) == nullptr && strstr("and", sir) == nullptr;
}

void init_en() {
	// intializez "baza de date"
	numar["one"] = 1;
	numar["two"] = 2;
	numar["three"] = 3;
	numar["four"] = 4;
	numar["five"] = 5;
	numar["six"] = 6;
	numar["seven"] = 7;
	numar["eight"] = 8;
	numar["nine"] = 9;
	numar["ten"] = 10;
	numar["eleven"] = 11;
	numar["twelve"] = 12;
	numar["thirteen"] = 13;
	numar["fourteen"] = 14;
	numar["fifteen"] = 15;
	numar["sixteen"] = 16;
	numar["seventeen"] = 17;
	numar["eighteen"] = 18;
	numar["nineteen"] = 19;
	numar["twenty"] = 20;
	numar["thirty"] = 30;
	numar["forty"] = 40;
	numar["fifty"] = 50;
	numar["sixty"] = 60;
	numar["seventy"] = 70;
	numar["eighty"] = 80;
	numar["ninety"] = 90;
	numar["hundred"] = 100;
	numar["thousand"] = 1000;
	numar["thousands"] = 1000;
	numar["million"] = 1000000;
	numar["millions"] = 1000000;
	siruri[1] = "one";
	siruri[2] = "two";
	siruri[3] = "three";
	siruri[4] = "four";
	siruri[5] = "five";
	siruri[6] = "six";
	siruri[7] = "seven";
	siruri[8] = "eight";
	siruri[9] = "nine";
	siruri[20] = "twenty";
	siruri[30] = "thirty";
	siruri[40] = "forty";
	siruri[50] = "fifty";
	siruri[60] = "sixty";
	siruri[70] = "seventy";
	siruri[80] = "eighty";
	siruri[90] = "ninety";
}

void insereaza_operator_en(char* sir, int& poz) {
	// compar sirul dat si inserez operatorul corespunzator
	if (strstr("multiplied", sir) != nullptr)
		S[poz++] = '*';
	if (strstr("divided", sir) != nullptr)
		S[poz++] = '/';
	if (strstr("plussum", sir) != nullptr)
		S[poz++] = '+';
	if (strstr("differenceminus", sir) != nullptr)
		S[poz++] = '-';
	if (strstr(sir, "(") != nullptr)
		S[poz++] = '(';
	if (strstr(sir, ")") != nullptr)
		S[poz++] = ')';
	//afisez expresia
	cout << S[poz - 1];
}

void citire(char* sir) {
	/* for (unsigned short i{ 0 }; i < 1000; i++)
		 c[i] = sir[i];*/
	strcpy(c, sir);
	//cin.getline(c, LGMAX);
}

bool este_exponent_en(char* sir) {
	return strstr("thousand", sir) != nullptr || strstr(sir, "hundred") != nullptr;
}

bool este_multiplu_de_10_en(char* sir) {
	return strstr(sir, "twenty") != nullptr || strstr(sir, "thirty") != nullptr ||
		strstr(sir, "forty") != nullptr || strstr(sir, "fifty") != nullptr ||
		strstr(sir, "sixty") != nullptr || strstr(sir, "seventy") != nullptr ||
		strstr(sir, "eighty") != nullptr || strstr(sir, "ninety") != nullptr;
}

void convertor_expresie_matematica_en() {
	int Suma = 0, Suma1 = 0, suma_partiala = 0, poz = 0;
	char* sir;
	bool ramas = false;
	sir = strtok(c, " ?,.");
	while (sir) {
		// daca gasesc un operator verific sa nu am nimic ramas de adunat la suma, introduc numarul care tocmai s-a terminat si operatorul
		if (este_operator_en(sir) || este_paranteza(sir)) {
			if (Suma != 0 || ramas) {
				if (ramas || Suma1) {
					if (Suma < 1000000)
						Suma += suma_partiala;
					else {
						Suma1 += suma_partiala;
						Suma += Suma1;
						Suma1 = 0;
					}
				}
				insereaza__numar(Suma, poz);
				Suma = 0;
				Suma1 = 0;
				suma_partiala = 0;
				ramas = false;
			}
			insereaza_operator_en(sir, poz);
		}
		else {
			// daca cuvantul care il am va face parte din expresie
			if (este_util_en(sir)) {
				// daca trebuie inmultit cu ceea ce am construit pana acum
				if (este_exponent_en(sir)) {
					if (Suma < 1000000) {
						if (ramas) {
							suma_partiala *= numar[sir];
							Suma += suma_partiala;
							suma_partiala = 0;
							ramas = false;
						}
						else {
							if (Suma != 0)
								Suma *= numar[sir];
							else
								Suma += numar[sir];
						}
					}
					else {
						if (ramas) {
							suma_partiala *= numar[sir];
							Suma1 += suma_partiala;
							suma_partiala = 0;
							ramas = false;
						}
						else {
							if (Suma1 != 0)
								Suma1 *= numar[sir];
							else
								Suma1 += numar[sir];
						}
					}
				}
				else {
					// daca este cazul special de sute de mii sau de milioane
					if (strstr("thousands", sir) != nullptr || strstr("millions", sir) != nullptr) {
						if (Suma < 1000000) {
							if (ramas) {
								Suma += suma_partiala;
								suma_partiala = 0;
								ramas = false;
							}
							Suma *= numar[sir];
						}
						else {
							if (ramas) {
								Suma1 += suma_partiala;
								suma_partiala = 0;
								ramas = false;
							}
							Suma1 *= numar[sir];
							Suma += Suma1;
							Suma1 = 0;
						}
					}
					else {
						if (este_multiplu_de_10_en(sir)) {
							ramas = false;
							if (Suma < 1000000) {
								Suma += numar[sir];
								suma_partiala = 0;
							}
							else {
								Suma1 += numar[sir];
								suma_partiala = 0;
							}
						}
						else {
							suma_partiala = numar[sir];
							ramas = true;
						}
					}
				}
			}
		}
		sir = strtok(nullptr, " .?,");
	}
	// daca am ajuns la finalul expresiei este posibil sa mai fi ramas ceva din numar pe care nu l-am adunat
	if (Suma != 0 || ramas) {
		if (ramas || Suma1) {
			if (Suma < 1000000)
				Suma += suma_partiala;
			else {
				Suma1 += suma_partiala;
				Suma += Suma1;
				Suma1 = 0;
			}
		}
		insereaza__numar(Suma, poz);
	}
}

void copiaza_numar_sir_en(int poz, int* v) {
	switch (poz) {
	case 9:
		switch (v[poz]) {
		case 0:
			return;
		default:
			//cout << siruri[v[poz]] << ' ' << "hundred" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), "hundred ");
			return;
		}
	case 8:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			switch (v[poz - 1]) {
			case 0:
				//cout << "ten millions" << ' ';
				sol.insert(sol.length(), "ten millions ");
				v[poz] = 0;
				return;
			case 1:
				//cout << "eleven  millions" << ' ';
				sol.insert(sol.length(), "eleven millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 2:
				//cout << "twelve millions" << ' ';
				sol.insert(sol.length(), "twele millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 3:
				//cout << "thirteen millions" << ' ';
				sol.insert(sol.length(), "thirteen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 4:
				//cout << "fourteen millions" << ' ';
				sol.insert(sol.length(), "fourteen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 5:
				//cout << "fifteen millions" << ' ';
				sol.insert(sol.length(), "fifteen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 6:
				//cout << "sixteen millions" << ' ';
				sol.insert(sol.length(), "sixteen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 7:
				//cout << "seventeen millions" << ' ';
				sol.insert(sol.length(), "seventeen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 8:
				//cout << "eighteen millions" << ' ';
				sol.insert(sol.length(), "eighteen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 9:
				//cout << "nineteen millions" << ' ';
				sol.insert(sol.length(), "nineteen millions ");
				v[poz] = v[poz - 1] = 0;
				return;
			default:
				return;
			}
		default:
			//cout << siruri[v[poz] * 10] << ' ';
			sol.insert(sol.length(), siruri[v[poz] * 10]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 7:
		switch (v[poz]) {
		case 0:
			return;
		default:
			//cout << siruri[v[poz]] << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 6:
		switch (v[poz]) {
		case 0:
			return;
		default:
			//cout << siruri[v[poz]] << ' ' << "hundred" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " ");
			sol.insert(sol.length(), "hundred ");
			return;
		}
	case 5:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			switch (v[poz - 1]) {
			case 0:
				//cout << "ten thousand" << ' ';
				sol.insert(sol.length(), "ten thousand ");
				v[poz] = 0;
				return;
			case 1:
				//cout << "eleven  thousand" << ' ';
				sol.insert(sol.length(), "eleven thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 2:
				//cout << "twelve thousand" << ' ';
				sol.insert(sol.length(), "twelve thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 3:
				//cout << "thirteen thousand" << ' ';
				sol.insert(sol.length(), "thirteen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 4:
				//cout << "fourteen thousand" << ' ';
				sol.insert(sol.length(), "fourteen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 5:
				//cout << "fifteen thousand" << ' ';
				sol.insert(sol.length(), "fifteen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 6:
				//cout << "sixteen thousand" << ' ';
				sol.insert(sol.length(), "sixteen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 7:
				//cout << "seventeen thousand" << ' ';
				sol.insert(sol.length(), "seventeen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 8:
				//cout << "eighteen thousand" << ' ';
				sol.insert(sol.length(), "eighteen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 9:
				//cout << "nineteen thousand" << ' ';
				sol.insert(sol.length(), "nineteen thousand ");
				v[poz] = v[poz - 1] = 0;
				return;
			default:
				return;
			}
		default:
			//cout << siruri[v[poz] * 10] << ' ';
			sol.insert(sol.length(), siruri[v[poz] * 10]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 4:
		switch (v[poz]) {
		case 0:
			return;
		default:
			//cout << siruri[v[poz]] << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 3:
		switch (v[poz]) {
		case 0:
			return;
		default:
			//cout << siruri[v[poz]] << ' ' << "hundred" << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			sol.insert(sol.length(), " ");
			sol.insert(sol.length(), "hundred ");
			return;
		}
	case 2:
		switch (v[poz]) {
		case 0:
			return;
		case 1:
			switch (v[poz - 1]) {
			case 0:
				//cout << "ten" << ' ';
				sol.insert(sol.length(), "ten ");
				v[poz] = 0;
				return;
			case 1:
				//cout << "eleven" << ' ';
				sol.insert(sol.length(), "eleven ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 2:
				//cout << "twelve" << ' ';
				sol.insert(sol.length(), "twelve ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 3:
				//cout << "thirteen" << ' ';
				sol.insert(sol.length(), "thirteen ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 4:
				//cout << "fourteen" << ' ';
				sol.insert(sol.length(), "fourteen ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 5:
				//cout << "fifteen" << ' ';
				sol.insert(sol.length(), "fifteen ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 6:
				//cout << "sixteen" << ' ';
				sol.insert(sol.length(), "sixteen ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 7:
				//cout << "seventeen" << ' ';
				sol.insert(sol.length(), "seventeen ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 8:
				//cout << "eighteen" << ' ';
				sol.insert(sol.length(), "eighteen ");
				v[poz] = v[poz - 1] = 0;
				return;
			case 9:
				//cout << "nineteen" << ' ';
				sol.insert(sol.length(), "nineteen ");
				v[poz] = v[poz - 1] = 0;
				return;
			default:
				return;
			}
		default:
			//cout << siruri[v[poz] * 10] << ' ';
			sol.insert(sol.length(), siruri[v[poz] * 10]);
			sol.insert(sol.length(), " ");
			return;
		}
	case 1:
		switch (v[poz]) {
		case 0:
			return;
		default:
			//cout << siruri[v[poz]] << ' ';
			sol.insert(sol.length(), siruri[v[poz]]);
			//sol.insert(sol.length(), " ");
			return;
		}
	default:
		return;
	}
}

void convertor_numar_sir_en(int nr) {
	int v[20] = { 0 }, uc, i = 0, j;
	// sparg numarul in cifre si il introduc in vectorul v in ordine inversa incepand de la pozitia 1
	while (nr) {
		uc = nr % 10;
		nr /= 10;
		v[++i] = uc;
	}
	// afisez numarul corespunzator in cuvinte
	for (j = i; j >= 1; j--) {
		copiaza_numar_sir_en(j, v);
		// cazul sutelor de mii
		if (j == 4) {
			if (v[j + 1] >= 1 || v[j + 2] >= 1) {
				//cout << "thousands" << ' ';
				sol.insert(sol.length(), "thousands");
				sol.insert(sol.length(), " ");
			}
			else if (v[j] != 0) {
				//cout << "thousand" << ' ';
				sol.insert(sol.length(), "thousand");
				sol.insert(sol.length(), " ");
			}
		}
		// cazul milioanelor
		if (j == 7) {
			if (v[j + 1] >= 1 || v[j + 2] >= 1) {
				//cout << "millions" << ' ';
				sol.insert(sol.length(), "millions");
				sol.insert(sol.length(), " ");
			}
			else {
				//cout << "million" << ' ';
				sol.insert(sol.length(), "million");
				sol.insert(sol.length(), " ");
			}
		}
	}
}

void afisare_ro() {
	cout << sol;
}

void afisare_en() {
	cout << sol;
}

char* CalculationProcess(char* sir, std::string& rezultatulInLitere, unsigned short limba)
{
	switch (limba)
	{
	case 1:
		init_en();
		citire(sir);
		p = S;
		convertor_expresie_matematica_en();
		cout << '\n';
		convertor_numar_sir_en(eval());
		afisare_en();
		break;
	case 2:
		init();
		citire(sir);
		p = S;
		convertor_expresie_matematica();
		cout << '\n';
		convertor_numar_sir(eval());
		afisare_ro();
		break;
	}
	char* rezultatulOperational{ S };
	rezultatulInLitere = sol;
	cout << '\n';
	sol.clear();
	return rezultatulOperational;
}

void ResettingValues()
{
	memset(c, 0, sizeof(c));
	memset(S, 0, sizeof(S));
}