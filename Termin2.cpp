#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#define War2

#ifdef War1 // na 6

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
		if (k->getUprawnienie() == KatPJ::A)
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

#ifdef War2 // na 4.5

enum class KatPJ { A, B, C, D };

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
class SamochodOsobowy
{
private:
    char m_numerRej[9];
    double m_predkosc;
    int m_liczbaPasazerow;

    void setPredkosc(double i_pred) { m_predkosc = (i_pred > 160) ? i_pred : 160; }
    void setLiczbaPasazerow(int i_lp) { m_liczbaPasazerow = (i_lp > 1) ? i_lp : 1; }

public:
    void setNumerRej(const char* i_num) { strncpy(m_numerRej, i_num, 8); }
    const char* getNumerRej() { return m_numerRej; }
    double getPredkosc() { return m_predkosc; }
    int getLiczbaPasazerow() { return m_liczbaPasazerow; }
};

class Ekipa {
    Kierowca* m_kier[4] = {};
    SamochodOsobowy* m_sam = nullptr;
    int licznik = 0;
public:
    void setWynajem(Kierowca* k, SamochodOsobowy* s) {
        for (size_t i = 0; i < 4; i++) {
            if (m_kier[0]->getUprawnienie() == KatPJ::B) {
                m_kier[i] = k; m_sam = s;
            }
        }
        if (licznik < 4) {
            m_kier[licznik] = k;
            licznik++;
        }
    }

    Ekipa(Kierowca* k[4], SamochodOsobowy* s) {
        setWynajem(*k, s);
    }

    int odczytajStaz()
    {
        for (int i = 0; i < 4; i++) {
            return m_kier[i]->getStaz();
        }
    }
    int odczytajIle()
    {
        return licznik;
    }
};
#endif

#ifdef War3 //na 6

class Kierowca
{
private:
	int m_staz{};
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
public:
	void setPredkosc(double i_pred) { m_predkosc = (i_pred > 260) ? i_pred : 260; }
	void setNumerRej(const char* i_num) { strncpy(m_numerRej, i_num, 8); }
	const char* getNumerRej() { return m_numerRej; }
	double getPredkosc() { return m_predkosc; }
};

class Wypozyczenie
{
private:
	Motor* motocykl{};
	Kierowca* kierowca{};
public:
	Wypozyczenie(Motor* _motor, Kierowca* _kierowca)
		:motocykl(_motor) {
		setKierowca(_kierowca);
	}
	void setKierowca(Kierowca* _kierowca) {
		if (_kierowca->getUprawnienie() == KatPJ::A)
			kierowca = _kierowca;
	}
	void setMotor(Motor* _motor) { motocykl = _motor; }
	const char* getNrRej() {
		return motocykl->getNumerRej();
	}
	int getStaz() {
		return kierowca->getStaz();
	}
	bool sprawdzenie() {
		if (kierowca->getUprawnienie() != KatPJ::A)
		{
			kierowca = nullptr;
			return false;
		}
		return true;
	}
};

#endif

#ifdef War4 // Asocjacja

enum class KatPJ { A, B, C, D };

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
	Kierowca* m_kierowca = nullptr;
public:
	void przypiszKierowce(Kierowca* k)
	{
		if (m_kierowca == nullptr)
		{
			if (k->getUprawnienie() == KatPJ::A)
			{
				m_kierowca = k;
			}
			else throw invalid_argument("BRAK KATEGORII");
		}
		else throw invalid_argument("Przypisanie ju� istnieje");
	}
	void zerwijass() {
		m_kierowca = nullptr;
	}
	Kierowca* kierowca() { return m_kierowca; }
	void setPredkosc(double i_pred) { m_predkosc = (i_pred > 260) ? i_pred : 260; }
	void setNumerRej(const char* i_num) { strncpy(m_numerRej, i_num, 8); }
	const char* getNumerRej() { return m_numerRej; }
	double getPredkosc() { return m_predkosc; }
	Motor(double p, const char* nrR, Kierowca* k) {
		setPredkosc(p);
		setNumerRej(nrR);
		przypiszKierowce(k);
	}
	int pokazstaz()
	{
		if (m_kierowca != nullptr) {
			return m_kierowca->getStaz();
		}
		else return -1;
	}
};

int main() {
	Kierowca k;
	k.setUprawnienie(KatPJ::A);
	Motor m(320.0, "JBC PIS", &k); // Jak-By Co PIS...    ...powoduje b�ad kompilacji

}

#endif

#ifdef War5



#endif

#ifdef Algorytmy

//algorytm.edu.pl
#include<iostream>
using namespace std;

int main1() //Wyszukiwanie najmniejszej warto�ci tablicy
{
	//inicjacja tablicy z przyk�adowymi danymi
	int min, tab[] = { 2, 3, 6, 7, 8, 7, 4, 3, 1, 7 };

	min = tab[0]; //pierwsz� liczb� przypisujemy do zmiennej min

	for (int i = 1; i < 10; i++) //przeszukanie pozosta�ych 9 liczb
		if (min > tab[i])
			min = tab[i];

	cout << "Najmniejsz� wczytan� liczb� jest " << min << endl;

	return 0;
}

#endif
