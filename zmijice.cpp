#include <bits/stdc++.h>
//#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <random>

using namespace std;

bool krajIgre;
const int sirina = 20;
const int visina = 20;

bool tekUpaljeno = true;

int x, y, vockaX, vockaY, score;
int repX[100], repY[100];
int nRep;
enum Direkcija {STOP = 0, LEVO, DESNO, GORE, DOLE}; // Zasluzno za pomeranje zmije
Direkcija dir;

random_device rd; // Nasumicni brojevi izmedju 0, 20 na c++ nacin
uniform_int_distribution<int> dist(1, 19);

void menjajBoju(int desiredColor){ 
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);}

void cistiEkran() // Dirketna implementacija komande system("cls"), samo bez treperenja
	{
		HANDLE hOut;
		COORD Position;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		Position.X = 0;
		Position.Y = 0;
		SetConsoleCursorPosition(hOut, Position);
	}

void Setup(){

    krajIgre = false;
    dir = STOP;
    x = sirina / 2;
    y = visina / 2;
    vockaX = dist(rd);
    vockaY = dist(rd);
    score = 0;

    ifstream citanje;
    ofstream upis;
    citanje.open("Rezultat.txt");
    if(!citanje){upis.open("Rezultat.txt"); upis << "Tek napravljen fajl!"; upis.close();}

}
void Crtanje(){

    //system("cls");
    cistiEkran();

    for(int i = 0; i < sirina+2; i++)
        cout << "#";
    cout << endl;

    for(int i = 0; i < visina; i++)
    {
        for(int j = 0; j < sirina; j++){
            if(j == 0){menjajBoju(7); cout << "#"; menjajBoju(7);}
            if(i == y && j == x){menjajBoju('A'); cout << "O"; menjajBoju(7);}
            else if(i == vockaY && j == vockaX){menjajBoju(4); cout << "&"; menjajBoju(7);}
            else{bool stampa = false; 
                for(int k = 0; k < nRep; k++){
                    if(repX[k] == j && repY[k] == i){menjajBoju(2); cout << "o"; menjajBoju(7); stampa = true;}
                }
                if(!stampa)cout << " ";}
            if(j == sirina-1)cout << "#";
        }
        cout << endl;
    }

    for(int i = 0; i < visina+2; i++)
        cout << "#";
    cout << endl;
    menjajBoju(6);
    cout << "Trenutni rezultat je: " << score << endl;
    ifstream citanje;
    citanje.open("Rezultat.txt");
    if(!citanje.is_open()){menjajBoju(4); cout << "Fajl za maksimalnim rezultatom nije moguce otvoriti!"; menjajBoju(7);}
    else {int maks; citanje >> maks; cout << "Maksimalni rezultat je: " << maks;}
    menjajBoju(7);
}
void Ulaz(){

    if(_kbhit()) // Funkcija koje se pozove ako je neko dugme pritisnuto
    {
        switch (_getch()) // Funkcija koja posalje ascii kod dugmeta koje je pritisnuto
        {
        case 'a':
            dir = LEVO;
            break;
        case 'd':
            dir = DESNO;
            break;
        case 'w':
            dir = GORE;
            break;
        case 's':
            dir = DOLE;
            break;

        default:
            break;
        }
    }

}
void Logika(){
    
    int preX = repX[0];
    int preY = repY[0];
    int pre2X, pre2Y;
    repX[0] = x;
    repY[0] = y;
    for(int i = 1; i < nRep; i++)
    {

        pre2X = repX[i];
        pre2Y = repY[i];
        repX[i] = preX;
        repY[i] = preY;
        preX = pre2X;
        preY = pre2Y;

    }
    switch(dir)
    {
        case LEVO:
            x--;
            break;
        case DESNO:
            x++;
            break;
        case GORE:
            y--;
            break;
        case DOLE:
            y++;
            break;
        default:
            break;
    }
    if(x > sirina || x < 0 || y > visina || y < 0){krajIgre = true; menjajBoju(4); cout << '\n' << "Zmija je udarila u zid!" << '\n'; menjajBoju(7);} // Ako zmija udari neku # igrica se prekida
    for(int i = 0; i < nRep; i++)if(repX[i] == x && repY[i] == y){krajIgre = true; menjajBoju(4); cout << '\n' << "Zmija je udarila u samu sebe!" << '\n';  menjajBoju(7);}// Ako zmija udari u samu sebe igra se prekida
    if(x == vockaX && y == vockaY) // Ako su x i y kordinate zmije jendako x i y kordinati vocke onda se rezultat poveca za 1 i nova vocka se pravi
    {

        score++;
        vockaX = dist(rd);
        vockaY = dist(rd);
        nRep++;

    }
}

int main() {

    if(tekUpaljeno == true){system("cls"); tekUpaljeno = false;} // Sluzi samo kako bi se otarasilo svega pre pokretanja igre
    Setup();
    while(!krajIgre) // Sve dok krajIgre nije jednak True
    {

        Sleep(150);
        Crtanje();
        Ulaz();
        Logika();

    }

    ofstream upis;
    ifstream citanje;

    if(krajIgre == true){citanje.open("Rezultat.txt"); int maks; citanje >> maks; citanje.close(); // Ovde se proverava da li je trenutni rezultat veci od prethodnog maksimuma, ako jeste upisuje se trentuni rezultat
    if(score > maks){upis.open("Rezultat.txt"); upis << score; upis.close();}}
    system("pause");

}
