#include <windows.h>

#include <vector>

#include <string>
#include <string.h>
#include <stdlib.h>
#include "funkcje.h"
//#include "resource.rc"


#include <math.h>

#include <objbase.h>
#include <CommCtrl.h>

using namespace std;


			




MSG Komunikat;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

	//-------------------------------- WYPE£NIANIE STRUKTURY
		WNDCLASSEX okno;

	okno.cbSize = sizeof( WNDCLASSEX );
	okno.style = 0;
	okno.lpfnWndProc = WndProc;
	okno.cbClsExtra = 0;
	okno.cbWndExtra = 0;
	okno.hInstance = hInstance;
	okno.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	okno.hCursor = LoadCursor( NULL, IDC_ARROW );
	okno.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
	okno.lpszMenuName = NULL;
	okno.lpszClassName = okno1;
	okno.hIconSm = LoadIcon( NULL, IDI_APPLICATION );




	//-------------------------------- REJESTROWANIE KLASY OKNA
	if( !RegisterClassEx( & okno ) )
	{
		MessageBox( NULL, "B³¹d", "",
			MB_ICONEXCLAMATION | MB_OK );
		return 1;
	}







	//-------------------------------- TWORZENIE OKNA
					

			//--------------------------------MENU G£ÓWNE



					okno_glowne = CreateWindowEx( WS_EX_CLIENTEDGE, okno1, "E-Dziennik", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL );

					if( okno_glowne == NULL )
					{
						MessageBox( NULL, "B³¹d","B³¹d w tworzeniu struktury", MB_ICONEXCLAMATION );
						return 1;
					}

					

					modyfikacja_bazy = CreateWindowEx( 0, "BUTTON", "Modyfikacja bazy", WS_CHILD | WS_VISIBLE,
						300, 25, 200, 50, okno_glowne, ( HMENU ) ID_modyfikacja_bazy, hInstance, NULL );
					wczytanie_bazy = CreateWindowEx( 0, "BUTTON", "Wczytanie bazy", WS_CHILD | WS_VISIBLE,
						300, 175, 200, 50, okno_glowne, ( HMENU ) ID_wczytanie_bazy, hInstance, NULL );
					rozklad_normalny = CreateWindowEx( 0, "BUTTON", "Rozk³ad normalny", WS_CHILD | WS_VISIBLE,
						300, 325, 200, 50, okno_glowne, ( HMENU ) ID_rozklad_normalny, hInstance, NULL );
					wyjscie = CreateWindowEx( 0, "BUTTON", "Wyjœcie", WS_CHILD | WS_VISIBLE,
						300, 475, 200, 50, okno_glowne, ( HMENU ) ID_wyjscie, hInstance, NULL );

					pole_tekstowe = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
						SS_LEFT, 50, 50, 150, 40, okno_glowne, NULL, hInstance, NULL );


			//--------------------------------WYŒWIETLANIE ZAWARTOŒCI BAZY

					okno_modyfikacji = CreateWindowEx( WS_EX_CLIENTEDGE, okno1, "E-Dziennik", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, 1050, 800, NULL, NULL, hInstance, NULL );

					if( okno_modyfikacji == NULL )
					{
						MessageBox( NULL, "B³¹d","B³¹d w tworzeniu struktury", MB_ICONEXCLAMATION );
						return 1;
					}

					

					


			RECT rcl;
			GetClientRect( okno_glowne, & rcl );
			lista_ocen = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT |
			LVS_EDITLABELS, 0, 00, rcl.right - rcl.left, rcl.bottom - rcl.top,
			okno_modyfikacji,( HMENU ) 780, hInstance, NULL );
				
				ListView_SetExtendedListViewStyle( lista_ocen, LVS_EDITLABELS );
				
				LVCOLUMN lvc;
				lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

				lvc.iSubItem = 0;
				lvc.cx = 30;
				lvc.pszText = "Nr.";
				ListView_InsertColumn( lista_ocen, 0, & lvc );

				lvc.iSubItem = 1;
				lvc.cx = 100;
				lvc.pszText = "Numer albumu";
				ListView_InsertColumn( lista_ocen, 1, & lvc );
				
				lvc.iSubItem = 2;
				lvc.cx = 95;
				lvc.pszText = "Imie";
				ListView_InsertColumn( lista_ocen, 2, & lvc );
				
				lvc.iSubItem = 3;
				lvc.cx = 95;
				lvc.pszText = "Nazwisko";
				ListView_InsertColumn( lista_ocen, 3, & lvc );

				lvc.iSubItem = 4;
				lvc.cx = 90;
				lvc.pszText = "Kartkówka I";
				ListView_InsertColumn( lista_ocen, 4, & lvc );

				lvc.iSubItem = 5;
				lvc.cx = 90;
				lvc.pszText = "Kartkówka II";
				ListView_InsertColumn( lista_ocen, 5, & lvc );

				lvc.iSubItem = 6;
				lvc.cx = 90;
				lvc.pszText = "Kolokwium I";
				ListView_InsertColumn( lista_ocen, 6, & lvc );

				lvc.iSubItem = 7;
				lvc.cx = 90;
				lvc.pszText = "Kolokwium II";
				ListView_InsertColumn( lista_ocen, 7, & lvc );


				lvc.iSubItem = 8;
				lvc.cx = 100;
				lvc.pszText = "Œrednia warzona";
				ListView_InsertColumn( lista_ocen, 8, & lvc );
				
			ramka_pola_edycji = CreateWindowEx( 0, "BUTTON", "Opcje Modyfikacji", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			790, 10, 220, 300, okno_modyfikacji, NULL, hInstance, NULL );
			
			ramka_menu_deycji= CreateWindowEx( 0, "BUTTON", "Modyfikacja Ocen", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			10, 600, 700, 150, okno_modyfikacji, NULL, hInstance, NULL );
			
			zapis_bazy = CreateWindowEx( 0, "BUTTON", "Zapisz bazê", WS_CHILD | WS_VISIBLE,
			800, 50, 200, 50, okno_modyfikacji, ( HMENU ) ID_zapis_bazy, hInstance, NULL );
			
			refresh_listy = CreateWindowEx( 0, "BUTTON", "Odœwie¿ liste ocen", WS_CHILD | WS_VISIBLE,
			800, 150, 200, 50, okno_modyfikacji, ( HMENU ) ID_refresh_listy, hInstance, NULL );

			powrót_do_menu = CreateWindowEx( 0, "BUTTON", "Powrót do menu", WS_CHILD | WS_VISIBLE,
			800, 250, 200, 50, okno_modyfikacji, ( HMENU ) ID_powrot_do_menu, hInstance, NULL );

			wprowadzenie_oceny = CreateWindowEx( 0, "BUTTON", "WprowadŸ oceny", WS_CHILD | WS_VISIBLE,
			470, 635, 200, 50, okno_modyfikacji, ( HMENU ) ID_wprowadzenie_oceny, hInstance, NULL );



			//pole_na_ID = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			//30, 650, 40, 20, okno_modyfikacji, NULL, hInstance, NULL );
			//
			//edycja_ocena_1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			//120, 650, 30, 20, okno_modyfikacji, NULL, hInstance, NULL );
			//
			// edycja_ocena_2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			//220, 650, 30, 20, okno_modyfikacji, NULL, hInstance, NULL );
			//
			// edycja_ocena_3 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			//320, 650, 30, 20, okno_modyfikacji, NULL, hInstance, NULL );
			//
			// edycja_ocena_4 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			//420, 650, 30, 20, okno_modyfikacji, NULL, hInstance, NULL );

		//Opisy do textboxów
		opis_nr     = CreateWindowEx(NULL, TEXT("Static"), TEXT("Nr "),       WS_CHILD | WS_VISIBLE, 30,  630, 20, 20, okno_modyfikacji, NULL, NULL, NULL);
		opis_ocena1 = CreateWindowEx(NULL, TEXT("Static"), TEXT("Kart I "),   WS_CHILD | WS_VISIBLE, 120, 630, 40, 20, okno_modyfikacji, NULL, NULL, NULL);
		opis_ocena2 = CreateWindowEx(NULL, TEXT("Static"), TEXT("Kart II: "), WS_CHILD | WS_VISIBLE, 220, 630, 45, 20, okno_modyfikacji, NULL, NULL, NULL);
		opis_ocena3 = CreateWindowEx(NULL, TEXT("Static"), TEXT("Kolos I"),   WS_CHILD | WS_VISIBLE, 320, 630, 50, 20, okno_modyfikacji, NULL, NULL, NULL);
		opis_ocena4 = CreateWindowEx(NULL, TEXT("Static"), TEXT("Kolos II"),  WS_CHILD | WS_VISIBLE, 420, 630, 50, 20, okno_modyfikacji, NULL, NULL, NULL);
								//COMBOBOXY
								 combobox_ID = CreateWindowEx(0,WC_COMBOBOX,0,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
								30, 650, 40, 500, okno_modyfikacji, NULL,hInstance, NULL);
								
								 combobox_ocena_1 = CreateWindowEx(0,WC_COMBOBOX,0,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
								120, 650, 45, 200, okno_modyfikacji,NULL,hInstance, NULL);
								
								 combobox_ocena_2 = CreateWindowEx(0,WC_COMBOBOX,0,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
								220, 650, 45, 200, okno_modyfikacji,NULL,hInstance, NULL);
								
								 combobox_ocena_3 = CreateWindowEx(0,WC_COMBOBOX,0,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
								320, 650, 45, 200, okno_modyfikacji,NULL,hInstance, NULL);
								
								 combobox_ocena_4 = CreateWindowEx(0,WC_COMBOBOX,0,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
								420, 650, 45, 200, okno_modyfikacji,NULL,hInstance, NULL);



								    


      
    // Send the CB_SETCURSEL message to display an initial item 
    //  in the selection field  
									SendMessage(combobox_ocena_1, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);
					//--------------------------------WYŒWIETLANIE ROZK£ADU NORMALNEGO
					
					okno_wykresu = CreateWindowEx( WS_EX_CLIENTEDGE, okno1, "E-Dziennik", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL );
					
					
					powrót_do_menu_rozk³ad = CreateWindowEx( 0, "BUTTON", "Powrót do menu", WS_CHILD | WS_VISIBLE,
						550, 500, 200, 50, okno_wykresu, ( HMENU ) ID_powrót_do_menu_rozk³ad, hInstance, NULL );
					

					
					if( okno_wykresu == NULL )
					{
						MessageBox( NULL, "B³¹d","B³¹d w tworzeniu struktury", MB_ICONEXCLAMATION );
						return 1;
					}

					



	//-------------------------------OTWARCIE PLIKU
	


	//--------------------------------Wyœwietlenie okna

	ShowWindow( okno_glowne, nCmdShow ); 
	UpdateWindow( okno_glowne );






	//-------------------------------- Pêtla komunikatów
	while( GetMessage( & Komunikat, NULL, 0, 0 ) )
	{
		TranslateMessage( & Komunikat );
		DispatchMessage( & Komunikat );
	}
	return Komunikat.wParam;
}

//-------------------------------------- OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc( HWND window, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_CLOSE:
		DestroyWindow( window );
		break;
	

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;


	case WM_COMMAND:

		switch( wParam )
		{
		
		
		//--------------------------------------MENU G£ÓWNE	
		case ID_modyfikacja_bazy:
		    
			SetWindowText( pole_tekstowe, "Wybrano opcjê \"Modyfikacja bazy\"" );
			
			CloseWindow(okno_glowne);
			EnableWindow(okno_glowne,FALSE);
			EnableWindow(okno_modyfikacji,TRUE);
			ShowWindow(okno_modyfikacji, SW_RESTORE);
										char buffer_ocena2[100];
										 sprintf(buffer_ocena2, "%.1f", 2.0);
										   SendMessage(combobox_ocena_1, CB_ADDSTRING,0, (LPARAM)buffer_ocena2);
										   SendMessage(combobox_ocena_2, CB_ADDSTRING,0, (LPARAM)buffer_ocena2);
										   SendMessage(combobox_ocena_3, CB_ADDSTRING,0, (LPARAM)buffer_ocena2);
										   SendMessage(combobox_ocena_4, CB_ADDSTRING,0, (LPARAM)buffer_ocena2);
 
										 for (int k = 0; k < liczba_studentow; k++ )
									  {
										  char buffer_int[500];
										  sprintf(buffer_int, "%d", k);
									      SendMessage(combobox_ID, CB_ADDSTRING,0, (LPARAM)buffer_int);
									  }	

										 for (float k = 3; k <=5.5; k=k+0.5 )
										{
										  char buffer_ocena[100];
										  sprintf(buffer_ocena, "%.1f", k);
										   SendMessage(combobox_ocena_1, CB_ADDSTRING,0, (LPARAM)buffer_ocena);
										   SendMessage(combobox_ocena_2, CB_ADDSTRING,0, (LPARAM)buffer_ocena);
										   SendMessage(combobox_ocena_3, CB_ADDSTRING,0, (LPARAM)buffer_ocena);
										   SendMessage(combobox_ocena_4, CB_ADDSTRING,0, (LPARAM)buffer_ocena);
										 }		

										//SendMessage(combobox_ocena_1, CB_ADDSTRING,0, (LPARAM)"NB");
										//SendMessage(combobox_ocena_2, CB_ADDSTRING,0, (LPARAM)"NB");
										//SendMessage(combobox_ocena_3, CB_ADDSTRING,0, (LPARAM)"NB");
										//SendMessage(combobox_ocena_4, CB_ADDSTRING,0, (LPARAM)"NB");
	

			LVITEM lvi;
			lvi.mask = LVIF_TEXT;
			wyswietlanie_bazydanych_v1(liczba_studentow);


		

			

			
		
		    break;
		   
		case ID_wczytanie_bazy:
		    SetWindowText( pole_tekstowe, "Wybrano opcjê \"Wczytanie bazy\"" );
					ListView_DeleteAllItems(lista_ocen);
					plik_baza=fopen("baza.txt","r+");
					fscanf( plik_baza,"%d\n",&liczba_studentow);
					student=(dane*)malloc(liczba_studentow*sizeof(dane));	
					fread(student,sizeof( dane),liczba_studentow,plik_baza);
					fclose(plik_baza);

					qsort (student, liczba_studentow, sizeof(dane), sortowanie_bazydanych); 
			


				

	
			
			
			
			 
			

		    break;
		   


		case ID_rozklad_normalny:
		    SetWindowText( pole_tekstowe, "Wybrano opcjê \"Rozk³ad normalny\"" );
			CloseWindow(okno_glowne);
			EnableWindow(okno_glowne,FALSE);
			EnableWindow(okno_wykresu,TRUE);
			ShowWindow(okno_wykresu, SW_RESTORE);
		    break;
		   

		case ID_wyjscie:
		    MessageBox( window, "Koñczenie pracy programu", "Koniec", MB_ICONINFORMATION );
			DestroyWindow( window );
		    break;
		//--------------------------------------MODYFIKACJA BAZY	   
		case ID_zapis_bazy:	
			if(liczba_studentow==0){
				MessageBox( okno_modyfikacji, "Nie wczytano bazy!", "Komunikat", MB_ICONINFORMATION );
			}
			else{
				zapis_bazydanych_plik(liczba_studentow);
			}
		    break;

		case ID_refresh_listy:
			ListView_DeleteAllItems(lista_ocen);
			wyswietlanie_bazydanych_v1(liczba_studentow);
		    break;

		case ID_powrot_do_menu:
		CloseWindow(okno_modyfikacji);
		EnableWindow(okno_modyfikacji,FALSE);
		EnableWindow(okno_glowne,TRUE);
		ShowWindow(okno_glowne,SW_RESTORE);
		    break;

		case ID_wprowadzenie_oceny:

			if(liczba_studentow==0){
				MessageBox( okno_modyfikacji, "Nie wczytano bazy!", "Komunikat", MB_ICONINFORMATION );
			}
			else{
			 
				GetWindowText(combobox_ID, ID, 10);
				GetWindowText(combobox_ocena_1, edit_ocena1, 10);
				GetWindowText(combobox_ocena_2, edit_ocena2, 10);
				GetWindowText(combobox_ocena_3, edit_ocena3, 10);
				GetWindowText(combobox_ocena_4, edit_ocena4, 10);
				modyfikacja_ocen(ID,edit_ocena1,edit_ocena2,edit_ocena3,edit_ocena4);	
			}
							
			break;
		//--------------------------------------OKNO WYKRESU
		case ID_powrót_do_menu_rozk³ad:
		CloseWindow(okno_wykresu);
		EnableWindow(okno_wykresu,FALSE);
		EnableWindow(okno_glowne,TRUE);
		ShowWindow(okno_glowne,SW_RESTORE);
			break;
		}




	break;



break;


	default:
		return DefWindowProc( window, msg, wParam, lParam );
	}

	return 0;
}



