#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bitset>
using namespace std;


#define Zadanie2_3_K1

#ifdef Zadanie1_4_P

using text = char[50];

enum class Plec { kobieta, mezczyzna };
enum class StanCywilny { wolny, wZwiazku, rozwodnik, wdowiec };
const char* PLEC[] = { "kobieta", "mê¿czyzna" };
const char* STAN_CYWILNY[] = { "wolny", "w Zwi¹zku", "rozwodnik", "wdowiec"};

struct Osoba
{
	text imie, nazwisko;
	int wiek;
	Plec plec;
	StanCywilny stan;
};

short koder(Osoba &o){
	short kod{};
	kod += o.wiek;
	kod = kod << 1;
	kod += (int)o.plec;
	kod = kod << 2;
	kod += (int)o.stan;
	return kod;
}

void dekoder(short kod, int& wiek, Plec& plec, StanCywilny& stan) {
	stan = (StanCywilny)(kod % 4);
	kod = kod >> 2;
	plec = (Plec)(kod % 2);
	kod = kod >> 1;
	wiek = (int)(kod % 128);
}

void zapisz(Osoba osoby[], int n, const char os[100])
{
	FILE* plik = nullptr;
	plik = fopen(os, "w");
	for (size_t i = 0; i < n; i++)
	{
		fprintf(plik, "%s; %s; %hu\n", osoby[i].imie, osoby[i].nazwisko, koder(osoby[i]));
	}
	fclose(plik);
}

void wypelnij(Osoba& o, const text imie,const text nazwisko, int wiek, Plec plec, StanCywilny stan)
{
	strcpy(o.imie, imie);
	strcpy(o.nazwisko, nazwisko);
	o.wiek = wiek;
	o.plec = plec;
	o.stan = stan;
}

void Odczytaj(Osoba& o, int n, const char plik_osoby[100])
{
	FILE* plik = nullptr;
	plik = fopen(plik_osoby, "r");
	text imie, nazwisko;
	short kod{};
	for (size_t i = 0; i <= n; i++)
	{
		fscanf(plik, "%s", imie);
		fscanf(plik, "%s", nazwisko);
		fscanf(plik, "%hu", &kod);
		if (feof(plik))
			throw std::out_of_range("");
	}
	imie[strlen(imie) - 1] = 0;
	nazwisko[strlen(nazwisko) - 1] = 0;
	int wiek;
	Plec plec;
	StanCywilny stan;
	dekoder(kod, wiek, plec, stan);
	wypelnij(o, imie, nazwisko, wiek, plec, stan);
	fclose(plik);
}

ostream& operator<<(ostream& str, Osoba const& o)
{
	str << o.imie<< " " << o.nazwisko << ", " << o.wiek << " lat, P³eæ: " << PLEC[(int)o.plec] << ", Stan Cywilny: " << STAN_CYWILNY[(int)o.stan] << '\n';
	return str;
}


int main() {
	setlocale(LC_ALL, "");
	const int rozmiar = 5;
	Osoba osoby[rozmiar], osoba;
	wypelnij(osoby[0], "£ukasz", "Prokop", 22, Plec::mezczyzna, StanCywilny::wZwiazku);
	wypelnij(osoby[1], "Wojciech", "Tworek", 21, Plec::mezczyzna, StanCywilny::wolny);
	wypelnij(osoby[2], "And¿ej", "???", 35, Plec::mezczyzna, StanCywilny::wdowiec);
	wypelnij(osoby[3], "Andrzela", "???", 27, Plec::kobieta, StanCywilny::rozwodnik);
	wypelnij(osoby[4], "Krzysztof", "Soko³owski", 35, Plec::mezczyzna, StanCywilny::wolny);

	zapisz(osoby, rozmiar, "Osoby.txt");
	cout << "Podaj ID godnoœci [0-4]: ";
	int temp;
	cin >> temp;
	Odczytaj(osoba, temp, "Osoby.txt");
	cout << "GODNOŒÆ Z PLIKU: \n";
	cout << osoba;

}

#endif

#ifdef Zadanie1_4_K1


using text = char[50];
enum class TypPojazdu { motocykl, smaochodOsobowy, smaochodCiezarowy, Ciagnik };

struct Pojazd
{
	text marka, model;
	int rocznik;
	TypPojazdu typ;
	bool dopuszczonyDoRuchu;
};

short Koder(Pojazd pojazd)
{
	short kod{};
	kod += pojazd.rocznik;
	kod = kod << 2;
	kod += (int)pojazd.typ;
	kod = kod << 1;
	kod += (int)pojazd.dopuszczonyDoRuchu;
	return kod;
}

void Dekoder(short kod, bool& dopuszczenie, TypPojazdu& typ, int& rok)
{
	dopuszczenie = (bool)(kod % 2);
	kod = kod >> 1;
	typ = (TypPojazdu)(kod % 4);
	kod = kod >> 2;
	rok = (int)(kod % 2048);
}

void Zapisz(Pojazd pojazdy[], int n, const char samochodziki[100])
{
	FILE* plik = nullptr;
	plik = fopen(samochodziki, "w");
	for (size_t i = 0; i < n; i++)
	{
		fprintf(plik, "%s; %s; %hu\n", pojazdy[i].model, pojazdy[i].marka, Koder(pojazdy[i]));
	}
	fclose(plik);
}

void Wypelnij(Pojazd& p, const text model, const text marka, int rocznik, TypPojazdu typ, bool dopuszczony)
{
	strcpy(p.model, model);
	strcpy(p.marka, marka);
	p.rocznik = rocznik;
	p.typ = typ;
	p.dopuszczonyDoRuchu = dopuszczony;
}

void Odczytaj(Pojazd& pojazd, int n, const char plik_sc[100])
{
	FILE* plik = nullptr;
	plik = fopen(plik_sc, "r");
	text marka, model;
	short kod{};
	for (size_t i = 0; i <= n; i++)
	{
		fscanf(plik, "%s", model);
		fscanf(plik, "%s", marka);
		fscanf(plik, "%hu", &kod);
		if (feof(plik))
			throw std::out_of_range("");
	}
	model[strlen(model) - 1] = 0;
	marka[strlen(marka) - 1] = 0;
	bool dop;
	TypPojazdu typ;
	int rok;
	Dekoder(kod, dop, typ, rok);
	Wypelnij(pojazd, model, marka, rok, typ, dop);
	fclose(plik);
}



ostream& operator<<(ostream& str, Pojazd const& p)
{
	str << p.marka << ", " << p.model << ", " << p.rocznik << ", " << (int)p.typ << ", " << p.dopuszczonyDoRuchu << '\n';
	return str;
}

int main()
{
	setlocale(LC_ALL, "");
	const int rozmiar = 3;
	Pojazd pojazdy[rozmiar], pojazd;
	Wypelnij(pojazdy[0], "Fiesta", "Ford", 2005, TypPojazdu::smaochodOsobowy, 1);
	Wypelnij(pojazdy[1], "Panigale", "Ducati", 2019, TypPojazdu::motocykl, 1);
	Wypelnij(pojazdy[2], "Studentów", "Zaliczenie", 2021, TypPojazdu::Ciagnik, 0);

	Zapisz(pojazdy, rozmiar, "Pojazdy.txt");
	cout << "Podaj jaki pojazd chcesz przeczytac[0-2]: ";
	int zm;
	cin >> zm;
	Odczytaj(pojazd, zm, "Pojazdy.txt");
	cout << "Odczytany pojazd z pliku: \n";
	cout << pojazd;

}
#endif

#ifdef Zadanie2_2_P



#endif

#ifdef Zadanie2_2_K1

enum class KatPJ { A, B, C, D };
enum class TypMotoru { scigacz, crossowy, chopper };

class Kierowca
{
private:
	int m_staz;
	KatPJ m_uprawnienie;
	static Kierowca* m_kierowca;
public:
	void setUprawnienie(KatPJ i_upr) { m_uprawnienie = i_upr; }
	KatPJ getUprawnienie() { return m_uprawnienie; }
	int getStaz() { return m_staz; }
	void zwiekszStaz() { m_staz++; }

	static void setWzor(Kierowca* k) {
		m_kierowca = k;
	}

	bool sprawdzenie() {
		return (m_staz == m_kierowca->m_staz && m_uprawnienie == m_kierowca->m_uprawnienie);
	}

	Kierowca()
	{
		if (m_kierowca == nullptr) {
			setUprawnienie(KatPJ::B);
			m_staz = 0;
		}
		else {
			m_uprawnienie = m_kierowca->m_uprawnienie;
			m_staz = m_kierowca->m_staz;
		}
	}
	Kierowca(int staz, KatPJ upr)
	{
		m_staz = staz;
		setUprawnienie(upr);
	}
};

Kierowca* Kierowca::m_kierowca = nullptr;


#endif

#ifdef Zadanie2_3_P



#endif

#ifdef Zadanie2_3_K1

enum class KatPJ { A, B, C, D };
enum class TypMotoru { scigacz, crossowy, chopper };



class Kierowca
{
private:
	int m_staz;
	KatPJ m_uprawnienie;
public:
	void setUprawnienie(KatPJ i_upr) { m_uprawnienie = i_upr; }
	KatPJ getUprawnienie() { return m_uprawnienie; }
	int getStaz() { return m_staz; }
	void zwiekszStaz() { m_staz++; }
};

class Motor
{
private:
	double m_predkosc;
	char m_numerRej[9];
	TypMotoru m_typ;
public:
	void setPredkosc(double i_pred) { m_predkosc = (i_pred > 260) ? i_pred : 260; }
	void setNumerRej(const char* i_num) { strncpy(m_numerRej, i_num, 8); }
	void setTypMotoru(TypMotoru typ) { m_typ = typ; }
	const char* getNumerRej() { return m_numerRej; }
	double getPredkosc() { return m_predkosc; }
	TypMotoru getTypMotoru() { return m_typ; }
};

class Wypozyczenie
{
private:
	Kierowca* m_kierowca = nullptr;
	Motor* m_motor = nullptr;
public:

	void setWypozyczenie(Kierowca* k, Motor* m) {
		if(k->getUprawnienie() == KatPJ::A)
		m_kierowca = k; m_motor = m;
	}

	Wypozyczenie(Kierowca* k, Motor* m) {
		setWypozyczenie(k, m);
	}

	int odczytajStaz()
	{
		return m_kierowca->getStaz();
	}
	const char* odczytajNumery()
	{
		return m_motor->getNumerRej();
	}

	bool weryfikacja()
	{
		if (m_kierowca->getUprawnienie() != KatPJ::A) {
			m_kierowca = nullptr;
			return false;
		}
		else return true;
	}

};


#endif