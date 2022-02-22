#include <iostream> //POP_2019_12_10_projekt_1_Bartnicki_Michal_EIT _5_180332. Visual Studio 2019.
#include <time.h>
#include <cstdlib>

using namespace std;
struct stringi {
	string a;
	string b;
	string c;
};
int const wiersze = 25;
int const kolumny = 11; //10 kolumn + 1 zarezerwowana na numerowanie wierszy
int const karty = 104;
void losuj(int t[])
{
	int n = 0;
	for (int i = 0; i < karty; i++)
	{
		t[i] = rand() % 13;
	}
	for (int i = 0; i < karty; i++)//badanie czy dana liczba powtórzyla sie max 8 razy
	{
		for (int j = 0; j < karty; j++)
		{

			if (t[i] == t[j])
			{
				n++;
			}
			if (n == 9)
			{
				t[i] = rand() % 13;
				j = -1;
				n = 0;
			}
		}
		n = 0;
	}
}
void grupy(int t[], int t1[], int t2[], int t3[], int t4[], int t5[])
{
	int temp = 54;
	for (int i = 0; i < 10; i++) //przydzielanie liczb kazdej grupie, ktora sluzy do wylozenia do wylozenia(1-5);
	{
		t1[i] = t[temp];
		temp++;
	}
	for (int i = 0; i < 10; i++)
	{
		t2[i] = t[temp];
		temp++;
	}
	for (int i = 0; i < 10; i++)
	{
		t3[i] = t[temp];
		temp++;
	}
	for (int i = 0; i < 10; i++)
	{
		t4[i] = t[temp];
		temp++;
	}
	for (int i = 0; i < 10; i++)
	{
		t5[i] = t[temp];
		temp++;
	}

}
void przydziel(int t[], int tw[wiersze][kolumny], int tz[wiersze][kolumny])
{
	int temp = 0;
	for (int j = 1; j <= 6; j++)
	{
		for (int g = 0; g <= 3; g++)
		{
			tw[j][g] = t[temp];// przydzielenie losowych liczb  polu 6x4
			temp++;
			if (j < 6) tz[j][g] = 14; //przydzielanie liczby 14 tablicy zastepczej, symbolizuje znak ---

		}
	}
	for (int j = 1; j <= 5; j++)
	{

		for (int g = 4; g <= 9; g++)
		{
			tw[j][g] = t[temp];// przydzielenie losowych liczb polu 5x6
			temp++;
			if (j < 5) tz[j][g] = 14;

		}
	}
	for (int i = 0; i <= 9; i++)
	{
		tw[0][i] = i; // przypisanie numer kolumny 1,2,3,4etc;
	}
	for (int i = 7; i < wiersze; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			tw[i][j] = 20; //prawdziwa tabela, 20 symbolizuje w pomocniczej tablicy puste miejsce
			tz[i][j] = 20; //pomocnicza tabela
		}
	}
	for (int i = 4; i <= 9; i++)
	{
		tw[6][i] = 20;
		tz[6][i] = 20;
	}
	for (int i = 0; i <= 9; i++)
	{
		if (i <= 3) tz[6][i] = tw[6][i]; //przypisanie poczatkowych wartosci pomocniczej tabeli, liczby co wyswietlaja sie na poczatku gry
		if (i > 3) tz[5][i] = tw[5][i];
	}
	for (int i = 1; i < wiersze; i++)
	{
		tz[i][10] = i; //przypisanie pomocniczego numeru wiersza  1-24
		tw[i][10] = i;

	}
	tz[0][10] = 450; //450 symbolizuje puste miejsce
	tw[0][10] = 450;

}
bool niemozliwyruch(int czymozna[], int tz[wiersze][kolumny]) //automatyczne sprawdzenie czy gracz moze sie poruszac
{
	int suma = 0;
	bool lose = true;
	int czymozna2[104];
	int temp = 0;
	for (int i = 0; i < 104; i++)
	{
		czymozna2[i] = 0;
	}


	for (int i = 0; i < kolumny - 1; i++)
	{
		for (int j = 1; j < wiersze; j++)
		{
			if (tz[j][i] == 20)
			{
				if (tz[j - 2][i] - tz[j - 1][i] == 1)
				{
					for (int z = 0; z < 13; z++)
					{
						if (tz[j - z - 2][i] - tz[j - 1 - z][i] == 1) //tu sprawdzamy czy jest mozliwosc przeniesienia klocka nizej, tzn np seri 3,4,5 na serie 6
						{
							czymozna2[temp] = tz[j - z - 2][i];
							temp++;
						}
					}
				}
				czymozna[i] = tz[j - 1][i]; //docieramy w kolumnie do 20 wartosci i bierzemy do tablicy klocek nizej od pustego miejsca
				break;
			}
		}

	}
	for (int i = 0; i < kolumny - 1; i++)
	{
		for (int j = 0; j < kolumny - 1; j++)
		{
			if ((czymozna[i] - czymozna[j]) == 1) suma++; //sprawdzamy czy da rade przeniesc ostatni klocek
		}
	}
	for (int i = 0; i < kolumny - 1; i++)
	{
		for (int j = 0; j < temp - 1; j++)
		{
			if (czymozna[i] - czymozna2[j] == 1) suma++; //warunek dla klockow ktore sa nizej, czy da rade je przeniesc
		}
	}
	if (suma == 0) lose = false; //brak ruchu
	suma = 0;
	temp = 0;
	return lose;
}
bool czykoniec(int &n) // sprawdzamy czy gracz wygral
{
	bool koniec = true;
	if (n == 8) koniec = false; //gracz wygral
	return koniec;

}
void wyloz(int tw[wiersze][kolumny], int tz[wiersze][kolumny], int t[], int t1[], int t2[], int t3[], int t4[], int t5[], string c, int &ktory)
{

	if (c == "wyloz")
	{
		for (int i = 0; i < kolumny - 1; i++)
		{
			for (int j = 1; j < wiersze; j++)
			{
				 if (tz[j][i] == 400)
				{
					switch (ktory)
					{
					case 1: tz[j][i] = t1[i]; tw[j][i] = t1[i]; break; //to jest warunek jesli jestesmy w pierwszym wierszu
					case 2: tz[j][i] = t2[i]; tw[j][i] = t2[i]; break;
					case 3: tz[j][i] = t3[i]; tw[j][i] = t3[i]; break;
					case 4: tz[j][i] = t4[i]; tw[j][i] = t4[i]; break;
					case 5: tz[j][i] = t5[i]; tw[j][i] = t5[i]; break;
					}
					break;
				}
				else if (tz[j][i] == 20) //docieramy w kolumnie pierwszego "wolnego" miejsca
				{

					switch (ktory) // ktora tabela, od 1-5
					{
					case 1: tz[j][i] = t1[i]; tw[j][i] = t1[i]; break; // tablicy zastepczej i prawdziwej przydzielamy odpowiednia grupe ktora ma elementy
					case 2: tz[j][i] = t2[i]; tw[j][i] = t1[i]; break;
					case 3: tz[j][i] = t3[i]; tw[j][i] = t3[i]; break;
					case 4: tz[j][i] = t4[i]; tw[j][i] = t4[i]; break;
					case 5: tz[j][i] = t5[i]; tw[j][i] = t5[i]; break;
					}
					break;
				}
			}
		}
		ktory++;
	}
}
void usuwakolumne(int tw[wiersze][kolumny], int tz[wiersze][kolumny], int xa, int ya, int xb, int yb, int &n)
{
	int suma = 0;
	for (int i = 0; i < kolumny - 1; i++)
	{
		for (int j = 0; j <= wiersze; j++)
		{

			if (tz[j][i] == 12) //trafiamy na najwyzsza kartee
			{
				for (int g = j; g < j + 13; g++) //przypisujemy numer wiersza najwiekszej karty
				{
					if (g == 25) break;//zabezpieczenie przed wyjsciem poza tablice
					if ((tz[g][i] - tz[g + 1][i] == 1)) //sprawdzamy czy ponizsze karty sa mniejsze o 1 od siebie
					{
						suma += tz[g][i]; //jak tak to sumujemy
					}
					if (!(tz[g][i] - tz[g + 1][i] == 1)) break; //przerywamy petle jak nie sa rozne o 1
				}
				if (suma == 78) //suma wszystkich kart
				{
					for (int z = j; z < j + 13; z++)
					{
						if (z == 1)
						{
							tz[z][i] = 400; // 400 symbolizuje tez puste miejsce ale na 400 mozemy klasc klocki
							tw[z][i] = 400;
						}
						if (z != 1)
						{
							tz[z][i] = 20; //zamieniamy na puste pole
							tw[z][i] = 20;
						}
					}
					n++; //zwiekszamy n, czyli ile razy usuniemy klocki
				}
			} suma = 0;
		}

	}
}
bool czyruchjestmozliwy(int tz[wiersze][kolumny], int xa, int ya) // sprawdzamy czy gracz moze przeniesc klocki jak niekoniecznie ma je w dobrej kolejnosci
{
	bool sprawdz = true;
	for (int g = 0; g <= 12; g++)
	{

		if (tz[xa + g + 1][ya] == 20) break;
		if (!(tz[xa + g][ya] - tz[xa + g + 1][ya] == 1))
		{
			sprawdz = false;
		}
	}
	return sprawdz;
}


void wartosci(int tw[wiersze][kolumny], int tz[wiersze][kolumny], int xa, int ya, int xb, int yb, bool zamia)
{
	bool sprawdz = czyruchjestmozliwy(tz, xa, ya);

	if ((((tw[xb - 1][yb] - tw[xa][ya]) == 1 && tz[xb][yb] == 20 && yb != 10 && ya != 10) || (tz[xb][yb] == 400 && yb != 10 && ya != 10)) && sprawdz == true)  //sprawdzamy czy ruch jest mozliwy
	{
		if (zamia == true)
		{
			tz[xa - 1][ya] = tw[xa - 1][ya]; //odkrywamy klocka wyzej od ktorego sie ruszylismy
		}

		tz[xb][yb] = tw[xa][ya]; //  tu dajemy nowa wartosc klockowi dla wspolrzednej xb,xa(czyli miejsca gdzie chcemy przeniesc) i jest ona rowna klockowi z xa ya(którym sie poruszam)
		tw[xb][yb] = tw[xa][ya]; //nadajemy prawdziwej tablicy wartosc klocka ktorego przenosimy

		for (int g = 0; g <= 12; g++)
		{

			if (tz[xa + g][ya] - tz[xa + g + 1][ya] == 1) {


				tw[xb + g + 1][yb] = tw[xa + g + 1][ya]; //czy mamy pod sobą wiecej niz jedna karta jak tak no to przypisujemy odpowiednio wartosci
				tz[xb + g + 1][yb] = tw[xa + g + 1][ya];
			}
		}
		for (int g = 0; g <= 12; g++) //tutaj nadajemy puste miejsce, z miejsca ktorego sie poruszamy jezeli mamy pod soba jakies klocki
		{

			if (tz[xa + g][ya] - tz[xa + g + 1][ya] == 1)
			{

				for (int z = 0; z <= 12; z++)
				{
					if (xa + z == 25) break; //zabezpieczenie przed wyjsciem z tablicy
					tz[xa + z][ya] = 20;
				}
			}
		}
		if (!(xa == 1))
		{
			tz[xa][ya] = 20; //to przypisujemy wspolrzednej wpisanej(klocka ktorego chcemy przeniesc) puste miejsce 

		}
		if (xa == 1)
		{
			tz[xa][ya] = 400; //400 puste miejsce, ale mozemy przenosic klocek
		}
	}


}
void wypelnij(int tw[wiersze][kolumny], int tz[wiersze][kolumny], int xa, int ya, int xb, int yb, bool zamia, int &n)
{
	string a = "A";
	string b = "B";
	string c = "C";

	wartosci(tw, tz, xa, ya, xb, yb, zamia);
	usuwakolumne(tw, tz, xa, ya, xb, yb, n);
	for (int i = 0; i < wiersze; i++)
	{
		for (int j = 0; j <= kolumny - 1; j++)
		{
			if (j < 10)
			{
				if (tz[i][j] == 14)
					cout << "- ";

				if (tz[i][j] == 10)
					cout << a << " ";
				if (tz[i][j] == 11) // zamian cyfr na literki
					cout << b << " ";
				if (tz[i][j] == 12)
					cout << c << " ";
				if (tz[i][j] == 20 || tz[i][j] == 400)
					cout << "  ";
				if (!(tz[i][j] == 10 || tz[i][j] == 11 || tz[i][j] == 12 || tz[i][j] == 20 || tz[i][j] == 14 || tz[i][j] == 400)) {
					if (i == 0) cout << tw[i][j] << " ";
					else cout << tz[i][j] << " ";
				}
			}
			if (j == 10)
			{
				if (tz[i][j] == 450) cout << "  ";
				if (tz[i][j] != 450) cout << tz[i][j] << " ";
			}




		}

		cout << endl;
	}


}
void gra()
{
	cout << "Co chcesz zrobic?" << endl << endl;
	cout << "1. Wyswietl pomoc" << endl;
	cout << "2. Rozpocznij gre" << endl;

}

void opisgry()
{

}
void wyswietl()
{
	system("cls");
	cout << "1. Opis gry" << endl;
	cout << "2. Sposob grania" << endl;
}
void wyb(stringi wybranie)
{
	system("cls");
	if (wybranie.b == "1") {
		cout << "Mamy do dyspozycji 8 kompletow klockow oznaczonych przez 0,1,2,3,4,5,6,7,8,9,A,B,C." << endl;
		cout << "Podana kolejnosc jest jednoczesnie porzadkiem klockow tj. klocki 0 sa najmniejsze," << endl;
		cout << "klocki C sa najwieksze.Na poczatku gry  klocki umieszczone sa w dziesieciu kol " << endl;
		cout << "umnach. W czterech pierwszych kolumnach szczesc klockow a w nastepnych szesciu po " << endl;
		cout << "piec klockow. Poczatkowo tylko ostatni klocek z kazdej kolumny jest widoczny. Klo " << endl;
		cout << "cek zostaje odsloniety jak jest ostatni w kolumnie. Pozostale klocki sa zgrupowane." << endl;
		cout << "w piecu grupach po 10 klockow." << endl << endl << endl;
		cout << "MOZLIWE RUCHY" << endl;
		cout << "Mozemy przelozyc dowolna serie klockow z kolumn na ostatnie miejsce w innej kolumnie" << endl;
		cout << "wtedy i tylko wtedy gdy po takiej operacji dlugosc przekladanej serii zwiekszy sie co" << endl;
		cout << "najmniej o jeden." << endl << endl;
		cout << "Jest mozliwosc przekladania dowolnej dlugosci serii na pusta kolumne" << endl << endl;
		cout << "Wylozenie zgrupowanych klockow- 10klockow z grupy zostaje ustawione jako ostatnie w kolumnach" << endl;
		cout << "Jesli po kilku ruchach powstaje seria dlugosci 13, czyli zawierajacej wszystkie klocki, wtedy" << endl;
		cout << "zostaja automatycznie usuniete z gry" << endl << endl << endl;
		cout << "Wygrana jest wtedy, kiedy pozbedziemy sie wszystkich klockow. Natomiast przegrana jezeli jest brak ruchu" << endl;
	}
	if (wybranie.b == "2")
	{
		cout << "Gra polega na tym, iz uzytkownik podaje wspolrzedne klocka(x,y) ktorym chce sie poruszyc," << endl;
		cout << "do miejsca pod klockiem docelowym, gdzie wspolrzedna 'x' to numer wiersza natomiast " << endl;
		cout << "'y' - numer kolumny. Gracz ma mozliwosc wylozenia 5 grup za pomoca komendy 'WYLOZ'" << endl;
		cout << "na poczatku rundy, zas komenda 'GRAJ' rozpoczynamy runde, w ktorej podajemy wspolrzedne" << endl;
		cout << "Nalezy pamietac, iz wspolrzedne musza byc cyframi!" << endl;
	}
}
int main()
{
	int tab[wiersze][kolumny];//max 19 wierszy, 9 kolumn
	int tabpomocnicza[wiersze][kolumny];
	int tab2[karty];
	int grupa1[10], grupa2[10], grupa3[10], grupa4[10], grupa5[10];
	int czymoznagrac[10];
	int x = 19;
	int y = 9;
	int x1 = 19;
	int y1 = 9;
	int ile = 0;//n
	int ktr = 1;//ktore wylozenie
	int sumacja = 0;
	bool koniec = true;
	bool czyklocek = true;
	bool zamiana = false;
	string co;
	stringi wybor;
	srand(time(NULL));
	losuj(tab2);
	przydziel(tab2, tab, tabpomocnicza);
	grupy(tab2, grupa1, grupa2, grupa3, grupa4, grupa5);


	cout << "Witaj drogi uzytkowniku w grze klocki!" << endl;
	gra();
	cin >> wybor.a;
	if (wybor.a == "1")
	{
		do
		{
			wyswietl();
			cin >> wybor.b;
			wyb(wybor);
			cout << endl;
			gra();
			cin >> wybor.a;
		} while (wybor.a == "1");
	}


	if (wybor.a == "2")
	{
		system("cls");
		while (czykoniec(ile) == true)
		{
			if ((niemozliwyruch(czymoznagrac, tabpomocnicza) == false && ktr > 5)) break;
			system("cls");
			wypelnij(tab, tabpomocnicza, x, y, x1, y1, zamiana, ile);
			if (czykoniec(ile) == false) break;

			cout << "CO CHCESZ ZROBIC? GRAJ/WYLOZ  ";
			cin >> co;
			if (co == "graj") {
				cout << "PODAJ WSPOLRZEDNA KLOCKA KTOREGO CHCESZ PRZENIESC" << endl;
				cin >> x;
				cin >> y;
				cout << "PODAJ WSPOLRZEDNA GDZIE CHCESZ PRZENISC " << endl;
				cin >> x1;
				cin >> y1;
				zamiana = true;
			}
			if (co == "wyloz")
			{
				wyloz(tab, tabpomocnicza, tab2, grupa1, grupa2, grupa3, grupa4, grupa5, co, ktr);
				zamiana = false;
			}

			system("cls");
		}
		if (niemozliwyruch(czymoznagrac, tabpomocnicza) == false && ktr > 5) //nie mozemy wylozyc kart, roznica wynosi 0 czyli nie mozna przeniesc kart
		{
			cout << "PRZYKRO MI PRZEGRALES" << endl << endl << endl;
			wypelnij(tab, tabpomocnicza, x, y, x1, y1, zamiana, ile);

		}
		else if (czykoniec(ile) == false) {
			cout << endl << endl;
			cout << "GRATULACJE WYGRALES!!";
		}
	}
	system("pause");
	return 0;
}

