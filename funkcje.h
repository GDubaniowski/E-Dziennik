#ifndef funkcje_h
#define funkcje_h

#include <windows.h>
#include <vector>
#include <string>
#include <commctrl.h>
#include <tchar.h>
#include <wchar.h>







using namespace std;

LPSTR okno1 = "Okno rodzic";


#define main_Window_Width 700
#define main_Window_Height 500

//-------- Deklaracje uchwytów dla przycisków i okien

//Menu g³ównego
HWND okno_glowne;
HWND modyfikacja_bazy;
HWND wczytanie_bazy;
HWND rozklad_normalny;
HWND wyjscie;
HWND pole_tekstowe;

#define ID_modyfikacja_bazy 1
#define ID_wczytanie_bazy 2
#define ID_rozklad_normalny 3
#define ID_wyjscie 4

//Okna modyfikacji bazy danych
HWND okno_modyfikacji;
HWND powrót_do_menu;
HWND lista_ocen;
HWND uchwyt_listy_ocen;
HWND zapis_bazy;
HWND wprowadzenie_oceny;
HWND refresh_listy;

//Textboxy do edycji ocen
HWND pole_na_ID;
HWND edycja_ocena_1;
HWND edycja_ocena_2;
HWND edycja_ocena_3;
HWND edycja_ocena_4;

//comboboxy do edycji ocen i wyboru user
	HWND combobox_ID;
	HWND combobox_ocena_1;
	HWND combobox_ocena_2;
	HWND combobox_ocena_3;
	HWND combobox_ocena_4;


//Buffery char z textboxów
LPSTR ID=(LPSTR)GlobalAlloc(GPTR,33);
LPSTR edit_ocena1=(LPSTR)GlobalAlloc(GPTR,33);
LPSTR edit_ocena2=(LPSTR)GlobalAlloc(GPTR,33);
LPSTR edit_ocena3=(LPSTR)GlobalAlloc(GPTR,33);
LPSTR edit_ocena4=(LPSTR)GlobalAlloc(GPTR,33);
			

HWND ramka_pola_edycji;
HWND ramka_menu_deycji;
//Opisy textboksów
HWND opis_nr;
HWND opis_ocena1;
HWND opis_ocena2;
HWND opis_ocena3;
HWND opis_ocena4;


#define ID_zapis_bazy 7
#define ID_refresh_listy 8
#define ID_wprowadzenie_oceny 9



#define ID_powrot_do_menu 5

//Okna z rozk³adem normalnym ocen
HWND okno_wykresu;
HWND powrót_do_menu_rozk³ad;
#define ID_powrót_do_menu_rozk³ad 6	





//---------------------------------------------



typedef struct {
	int numer_albumu;
	char imie[20];
	char nazwisko[20];
	float ocena_1;
	float ocena_2;
	float ocena_3;
	float ocena_4;
	double srednia_ocen;




}dane;


int wybor_menu;
dane*student;
int liczba_studentow;


FILE *plik_baza;











void wyswietlanie_bazydanych_v1(int ilosc_studentow) {

	int waga_kartkowka = 3;
	int waga_kolos = 4;

    LVITEM lvi;
    char buffer[50];

    for (int i = 0; i < ilosc_studentow; ++i)
    {
        memset(&lvi, 0, sizeof(lvi));
        lvi.mask = LVIF_TEXT;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.pszText = buffer;

        sprintf(buffer, "%d", i);
        ListView_InsertItem(lista_ocen, &lvi);

		sprintf(buffer, "%d", student[i].numer_albumu);
        ListView_SetItemText(lista_ocen, i, 1, buffer);

        ListView_SetItemText(lista_ocen, i, 2, student[i].imie);
        ListView_SetItemText(lista_ocen, i, 3, student[i].nazwisko);

        sprintf(buffer, "%.1f", student[i].ocena_1);
        ListView_SetItemText(lista_ocen, i, 4, buffer);

        sprintf(buffer, "%.1f", student[i].ocena_2);
        ListView_SetItemText(lista_ocen, i, 5, buffer);

        sprintf(buffer, "%.1f", student[i].ocena_3);
        ListView_SetItemText(lista_ocen, i, 6, buffer);

        sprintf(buffer, "%.1f", student[i].ocena_4);
        ListView_SetItemText(lista_ocen, i, 7, buffer);

        student[i].srednia_ocen = ((((float)student[i].ocena_1 * waga_kartkowka) + (student[i].ocena_2 * waga_kartkowka) + (student[i].ocena_3 * waga_kolos) + (student[i].ocena_4 * waga_kolos)) / 14);

        sprintf(buffer, "%.2f", student[i].srednia_ocen);
        ListView_SetItemText(lista_ocen, i, 8, buffer);


		}
}


int sortowanie_bazydanych (const void *p1, const void *p2)
{

	int y1 = ((const  dane*)p1)->numer_albumu;
	int y2 = ((const  dane*)p2)->numer_albumu;

	if (y1 < y2)
		return -1;
	else if (y1 > y2)
		return 1;
	else return 0;

}

void zapis_bazydanych_plik(int ilosc_studentow)
{
	FILE *plik_baza;
	

	int i=0;



	plik_baza=fopen("baza.txt","w+");

	fprintf(plik_baza,"%d",ilosc_studentow);
	fwrite(student,sizeof(dane),ilosc_studentow,plik_baza);
	
	fclose(plik_baza);

}





//Zmienne pomocnicze do fucnkji wprowadzaj¹cej zmiany w tablicy struktur
//Funckje przyjmie na wejœciu ka¿dy z nich, zostan¹ one pobrane z text boxów
//jeœli numer albumu bêdzie siê zgadza³ z tym z struktury to oceny zostan¹ nadpisane




void modyfikacja_ocen(char* ID, char* edit_ocena1, char* edit_ocena2, char* edit_ocena3,char* edit_ocena4) {




			int ID_studenta_string = atoi(ID);
			float ocena1_string = atof(edit_ocena1);
			float ocena2_string = atof(edit_ocena2);
			float ocena3_string = atof(edit_ocena3);
			float ocena4_string = atof(edit_ocena4);
			int i = ID_studenta_string;

	student[i].ocena_1 = ocena1_string;
	student[i].ocena_2 = ocena2_string;
	student[i].ocena_3 = ocena3_string;
	student[i].ocena_4 = ocena4_string;


}


#endif


