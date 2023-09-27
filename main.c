#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "pgm.h"
#include "ppm.h"

void sprawdz_komentarz(FILE *file)
	{
	int character;
	
	while ((character = fgetc(file))!= EOF && isspace(character));
		
	if (character == '#') 
		{
			while(fgetc(file) !='\n')
				fseek(file, 1, SEEK_CUR);
		}
	else
		fseek(file, -2, SEEK_CUR);
	}

int wgraj(pgm **pPgm, int *ilosc_obrazow)
	{
		pgm *aPgm;
		FILE* file;

		if((*ilosc_obrazow) >= 1)
			{
				*pPgm = realloc((*pPgm), (*ilosc_obrazow+1)*sizeof(pgm));
				if (*pPgm == NULL)
				{
					return 1;
				}
				(*ilosc_obrazow)++;
			}

		
				aPgm = calloc(1, sizeof(pgm));
				if (aPgm == NULL)
					return 1;
				if (*ilosc_obrazow == 0){(*ilosc_obrazow)++;}
			

		do 
			{
				printf("Podaj nazwe pliku(*.pgm):\n");
				scanf("%s", &aPgm->name_of_file);
		
		file = fopen(aPgm->name_of_file, "r");
		if(file == NULL)
			{
				system("cls");
				printf("Error, cant open file\nTry again\n");
			}
		else
			{
				fscanf(file, "%s", &aPgm->type);
				if (strcmp(aPgm->type, "P2") != 0)
					{
						system("cls");
						printf("INVALID TYPE OF *.pgm\nChoose (.pgm) type [P2]\n");
					}
			}
			}while(strcmp(aPgm->type, "P2") != 0);

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		fscanf (file, "%d", &(aPgm->w));

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		fscanf (file, "%d", &(aPgm->h));

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		fscanf (file, "%d", &(aPgm->max));

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		
		
		aPgm->pixs = malloc(aPgm->h * sizeof(int*));
		if(aPgm->pixs == NULL)
			{
				printf("Nie udalo sie zakalowac\n");
				return 3;
			}

		for (int i = 0; i < aPgm->h; i++)
			{
				aPgm->pixs[i] = (int *)calloc(aPgm->w, sizeof(int));
			}  


		for (int i = 0; i < aPgm->h; i++)
			{
				for (int j = 0; j < aPgm->w; j++)
				{
					fscanf(file, "%d", &aPgm->pixs[i][j]);
					sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
				}
			} 
		pPgm[*ilosc_obrazow-1] = aPgm;
		fclose(file);

	}

int wgrajppm(ppm **pppm, int *ilosc_obrazow)
	{
		ppm *appm;
		FILE* file;

		if((*ilosc_obrazow) >= 1)
			{
				*pppm = realloc((*pppm), (*ilosc_obrazow+1)*sizeof(ppm));
				if (*pppm == NULL)
				{
					return 1;
				}
				(*ilosc_obrazow)++;
			}

		
				appm = calloc(1, sizeof(ppm));
				if (appm == NULL)
					return 1;
				if (*ilosc_obrazow == 0){(*ilosc_obrazow)++;}
			

		do 
			{
				printf("Podaj nazwe pliku(*.ppm):\n");
				scanf("%s", &appm->name_of_file);
		
		file = fopen(appm->name_of_file, "r");
		if(file == NULL)
			{
				system("cls");
				printf("Error, cant open file\nTry again\n");
			}
		else
			{
				fscanf(file, "%s", &appm->type);
				if (strcmp(appm->type, "P3") != 0)
					{
						system("cls");
						printf("INVALID TYPE OF *.ppm\nChoose (.ppm) type [P3]\n");
					}
			}
			}while(strcmp(appm->type, "P3") != 0);

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		fscanf (file, "%d", &(appm->w));

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		fscanf (file, "%d", &(appm->h));

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		fscanf (file, "%d", &(appm->max));

		sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
		
		
		appm->pixs = malloc(appm->h * sizeof(int*));
		if(appm->pixs == NULL)
			{
				printf("Nie udalo sie zakalowac\n");
				return 3;
			}

		for (int i = 0; i < appm->h; i++)
			{
				appm->pixs[i] = calloc(appm->w, sizeof(ppm));
			}  


		for (int i = 0; i < appm->h; i++)
			{
				for (int j = 0; j < appm->w; j++)
				{
					fscanf(file, "%d", &((appm->pixs[i][j]).r));
					fscanf(file, "%d", &appm->pixs[i][j].g);
					fscanf(file, "%d", &appm->pixs[i][j].b);
					sprawdz_komentarz(file); // tu potrzebne sprawdzenie komentarzy
				}
			} 
		pppm[*ilosc_obrazow-1] = appm;
		fclose(file);

	}

int negatyw(pgm *aPgm)
	{
		for (int i = 0; i < aPgm->h; ++i)
		{
			for (int j = 0; j < aPgm->w; ++j)
				{
					aPgm->pixs[i][j] = aPgm->max - aPgm->pixs[i][j];
				}
			
		}
		return 1;
	}

void negatywppm(ppm *aPpm)
	{
		for (int i = 0; i < aPpm->h; ++i)
			{
				for (int j = 0; j < aPpm->w; ++j)
					{
						aPpm->pixs[i][j].r = aPpm->max - aPpm->pixs[i][j].r;
						aPpm->pixs[i][j].g = aPpm->max - aPpm->pixs[i][j].g;
						aPpm->pixs[i][j].b = aPpm->max - aPpm->pixs[i][j].b;
					}
				
			}
	}

void czarnebialeppm(ppm *aPpm)
	{
		for (int i = 0; i < aPpm->h; ++i)
			{
				for (int j = 0; j < aPpm->w; ++j)
					{
						aPpm->pixs[i][j].r = (aPpm->pixs[i][j].r + aPpm->pixs[i][j].g + aPpm->pixs[i][j].b)/3;
						aPpm->pixs[i][j].g = (aPpm->pixs[i][j].r + aPpm->pixs[i][j].g + aPpm->pixs[i][j].b)/3;
						aPpm->pixs[i][j].b = (aPpm->pixs[i][j].r + aPpm->pixs[i][j].g + aPpm->pixs[i][j].b)/3;
					}
				
			}
	}

int obrot90(pgm **aPgm)
	{
		pgm *tmp = calloc(1, sizeof(pgm));
		strcpy(tmp->name_of_file, (*aPgm)->name_of_file);
		strcpy(tmp->type, (*aPgm)->type);
		tmp->w = (*aPgm)->h;
		tmp->h = (*aPgm)->w;
		tmp->max = (*aPgm)->max;
		
		tmp->pixs = malloc(tmp->h * sizeof(int*));
		if(tmp->pixs == NULL)
			{
				printf("Nie udalo sie zakalowac\n");
				return 1;
			}

		for (int i = 0; i < tmp->h; i++)  // kalokacja pamieci na dane 
			{
				tmp->pixs[i] = (int *)calloc(tmp->w, sizeof(int));
			} 

		for (int i = tmp->h; i > 0; i--)
			{
			
				for (int j = 0; j < tmp->w; j++)
					{
						//printf("W:\n");
						tmp->pixs[tmp->h - i][j] = (*aPgm)->pixs[j][i];
					}
			}
		free(*aPgm);
		*aPgm = tmp;
		return 2;

	}

int obrot90ppm(ppm **aPgm)
	{
		ppm *tmp = calloc(1, sizeof(ppm));
		strcpy(tmp->name_of_file, (*aPgm)->name_of_file);
		strcpy(tmp->type, (*aPgm)->type);
		tmp->w = (*aPgm)->h;
		tmp->h = (*aPgm)->w;
		tmp->max = (*aPgm)->max;
		
		tmp->pixs = malloc(tmp->h * sizeof(int*));
		if(tmp->pixs == NULL)
			{
				printf("Nie udalo sie zakalowac\n");
				return 1;
			}

		for (int i = 0; i < tmp->h; i++)  // kalokacja pamieci na dane 
			{
				tmp->pixs[i] = calloc(tmp->w, sizeof(ppm));
			} 

		for (int i = tmp->h; i > 0; i--)
			{
			
				for (int j = 0; j < tmp->w; j++)
					{
						//printf("W:\n");
						tmp->pixs[tmp->h - i][j] = (*aPgm)->pixs[j][i];
					}
			}
		free(*aPgm);
		*aPgm = tmp;
		return 2;
	}

void nazwa_pliku(pgm *aPgm, int akcja)
	{
		char tab[30];
		int i = 0;
		if(akcja == 1)
			{
				 strcpy(tab, "Negatyw-");
				do
				{
					tab[i+8] = aPgm->name_of_file[i];
					i++;
				} while ((int)aPgm->name_of_file[i]  != '\0');
				tab[i+8] = '\0';
				strcpy(aPgm->operation_name, tab);

			}

		if(akcja == 2)
			{
				strcpy(tab, "Obrot90-");
				do
				{
					tab[i+8] = aPgm->name_of_file[i];
					i++;
				} while ((int)aPgm->name_of_file[i]  != '\0');
				tab[i+8] = '\0';
				strcpy(aPgm->operation_name, tab);
			}

		if(akcja == 3)
			{
				strcpy(tab, "Szum-");
				do
				{
					tab[i+5] = aPgm->name_of_file[i];
					i++;
				} while ((int)aPgm->name_of_file[i]  != '\0');
				tab[i+5] = '\0';
				strcpy(aPgm->operation_name, tab);
			}

		if(akcja == 4)
			{
				strcpy(tab, "Filtr-");
				do
				{
					tab[i+6] = aPgm->name_of_file[i];
					i++;
				} while ((int)aPgm->name_of_file[i]  != '\0');
				tab[i+6] = '\0';
				strcpy(aPgm->operation_name, tab);
			}
	}

int zapisz(pgm *aPgm, int akcja)
	{
		FILE* file;
		if(akcja == 0){printf("Nie bylo zastosowano zadnych operacji na obrazie\nObraz o takiej nazwie i tresci juz istnieje");}
		else
		{
		nazwa_pliku(aPgm, akcja);
		file = fopen(aPgm->operation_name, "w");
		if (file == NULL)
			{
				printf("Nie udalo sie otworzyc\n");
				return 1;
			}

		fprintf(file, "P2\n");
		fprintf(file, "%d %d\n", aPgm->w, aPgm->h);
		fprintf(file, "%d\n", aPgm->max);

		for (int i = 0; i < aPgm->h; i++)
			{
				
				for (int j = 0; j < aPgm->w; j++)
					{
						fprintf(file, "%d ", aPgm->pixs[i][j]);
					}
				if((i) == aPgm->w) fprintf(file, "\n");
			}
		fclose(file);
		}
	}

int zapiszppm(ppm *appm)
	{
		FILE* file;
		
		char nazwa[20];
		printf("Podaj nazwe pliku wraz z rozszerzeniem (*.ppm): ");
		scanf("%s", nazwa);
		system("cls");
		file = fopen(nazwa, "w");
		if (file == NULL)
			{
				printf("Nie udalo sie otworzyc\n");
				return 1;
			}

		fprintf(file, "P3\n");
		fprintf(file, "%d %d\n", appm->w, appm->h);
		fprintf(file, "%d\n", appm->max);

		for (int i = 0; i < appm->h; i++)
			{
				
				for (int j = 0; j < appm->w; j++)
					{
						fprintf(file, "%d ", appm->pixs[i][j].r);
						fprintf(file, "%d ", appm->pixs[i][j].g);
						fprintf(file, "%d ", appm->pixs[i][j].b);
					}
				if((i) == appm->w) fprintf(file, "\n");
			}
		fclose(file);
		
	}

void wyswiet_nazwe(pgm *aPgm)
	{
		printf("%s\n", aPgm->name_of_file);
	}

void wyswiet_nazweppm(ppm *aPpm)
	{
		printf("%s\n", aPpm->name_of_file);
	}

void wyswietl_baze(pgm **aPgm, int ilosc_obrazow)
	{
		for (int i = ilosc_obrazow; i > 0; i--)
			{
				printf("%d: ", ilosc_obrazow-i+1);
				wyswiet_nazwe(aPgm[ilosc_obrazow-i]); 
			}
		printf("\n");
	}

void wyswietl_bazeppm(ppm **aPpm, int ilosc_obrazow_ppm)
	{
		for (int i = ilosc_obrazow_ppm; i > 0; i--)
			{
				printf("%d: ", ilosc_obrazow_ppm-i+1);
				wyswiet_nazweppm(aPpm[ilosc_obrazow_ppm-i]); 
			}
		printf("\n");
	}

void usun(pgm **aPgm, int ktory, int *ilosc_obrazow)
	{
		for (int i = 0; i < aPgm[ktory-1]->h; ++i)
		{
			free(aPgm[ktory-1]->pixs[i]);
		}
		free(aPgm[ktory-1]->pixs);
		//free(aPgm[ktory-1]);
		for (int i = 0; i < (*ilosc_obrazow - ktory); i++)
			{
				aPgm[ktory-1+i] = aPgm[ktory+i];
			}

		(*ilosc_obrazow)--;
		if(*ilosc_obrazow != 0)
			*aPgm = realloc((*aPgm), (*ilosc_obrazow)*sizeof(pgm));
		printf("%d\n", *ilosc_obrazow);
		
	}

int szum(pgm *aPgm)
	{
		int pixsel = aPgm->max;
		for (int i = 0; i < aPgm->h; ++i)
		{
			for (int j = 0; j < aPgm->w; ++j)
				{
					if ((int)(rand()%20 == 1))
						{
							aPgm->pixs[i][j] = pixsel;
							if(pixsel == aPgm->max)
								pixsel = 0;
							else
								pixsel = aPgm->max;
						}
				}
			
		}

		return 3;
	}

int compare_ints(const void* a, const void* b)
	{
		int arg1 = *(const int*)a;
		int arg2 = *(const int*)b;
		if (arg1 < arg2) return -1;
		if (arg1 > arg2) return 1;
		return 0;
	}

void filtab(int *tab, pgm *aPgm, int i, int j)
	{
		tab[0] = aPgm->pixs[i][j];
		tab[1] = aPgm->pixs[i][j+1];
		tab[2] = aPgm->pixs[i][j+2];
		tab[3] = aPgm->pixs[i+1][j];
		tab[4] = aPgm->pixs[i+1][j+1];
		tab[5] = aPgm->pixs[i+1][j+2];
		tab[6] = aPgm->pixs[i+2][j];
		tab[7] = aPgm->pixs[i+2][j+1];
		tab[8] = aPgm->pixs[i+2][j+2];
	}

int filtr(pgm *aPgm)
	{
		int tab[9];


		for (int i = 0; i < (aPgm->h - 2); ++i)
		{
			for (int j = 0; j < (aPgm->w - 2); ++j)
				{
					filtab(tab, aPgm, i, j);
					qsort(tab, 9, sizeof(int), compare_ints);
					aPgm->pixs[i+1][j+1] = tab[4];
				}
			
		}

		return 4;
	}

void histogram_w_obrazie(pgm *aPgm, int *tab)
	{
		int h, w;
		w = aPgm->max + 1;
		h = w / 2;
		int x = 0;

		for (int i = 0; i < h; ++i)
			{
				for (int j = 0; j < w; ++j)
					{
						x = tab[j] * h;
						x = (int)x/tab[254];
						
						
						if(x < i)
							aPgm->pixs[i][j] = 200;
						else
							aPgm->pixs[i][j] = 0;
					}
					
				
			}

	}

void histogram(pgm *aPgm, int *tab)
	{
		tab = calloc((aPgm->max+1), sizeof(int));

		for (int i = 0; i < aPgm->h; ++i)
			{
				for (int j = 0; j < aPgm->w; ++j)
					{
						tab[aPgm->pixs[i][j]] += 1;
					}
			}

		FILE* plik;
		plik = fopen("Histogram.csv", "w");
		if (plik == NULL)
			printf(" Nie udalo sie otworzyc pliku CSV");
		
		else
			{
			for (int i = 0; i < aPgm->max+1; i++)
				{
					fprintf(plik, "%d;%d\n", i, tab[i]);
				}
			fclose(plik);
			}
		histogram_w_obrazie(aPgm, tab);
	}

void menu()
	{
		printf("1-> Wgraj\n");
		printf("2-> Usun aktywny\n");
		printf("3-> Zapisz do pliku\n");
		printf("4-> Wybierz aktywny\n");
		printf("5-> Operacje na obrazie\n");
		printf("6-> Zapisz histogram\n");
		printf("7-> *.PPM obrazy\n");
		printf("0-> Koniec\n");			
	}

void menuppm()
	{
		printf("1-> Wgraj\n");
		printf("2-> Negatyw\n");
		printf("3-> obrot90\n");
		printf("4-> Wybierz aktywny\n");
		printf("5-> Zapisz do pliku\n");
		printf("6-> Czarnebiale\n");
		printf("0-> wyjdz\n");	
	}

void zwolnij_pamiec(pgm **aPgm, int *ilosc_obrazow)
	{	
		while(*ilosc_obrazow != 0)
			{
				for (int i = 0; i < aPgm[*ilosc_obrazow-1]->h; ++i)
					{
						free(aPgm[*ilosc_obrazow-1]->pixs[i]);
					}
				free(aPgm[*ilosc_obrazow-1]->pixs);
				free(aPgm[*ilosc_obrazow-1]);
		
				(*ilosc_obrazow)--;	
			}
		free(aPgm);
	}

void zwolnij_pamiecppm(ppm **aPpm, int *ilosc_obrazow_ppm)
	{	
		while(*ilosc_obrazow_ppm != 0)
			{
				for (int i = 0; i < aPpm[*ilosc_obrazow_ppm-1]->h; ++i)
					{
						free(aPpm[*ilosc_obrazow_ppm-1]->pixs[i]);
					}
				free(aPpm[*ilosc_obrazow_ppm-1]->pixs);
				free(aPpm[*ilosc_obrazow_ppm-1]);
		
				(*ilosc_obrazow_ppm)--;	
			}
		free(aPpm);
	}

int main()
	{
		pgm **aPgm_baza;
		pgm *aktywnyPgm;
		int ilosc_obrazow = 0;
		int aktywny_obraz = 0;
		int wybor = 0;
		int akcja = 0;
		int *tab_histogram;
		aPgm_baza = calloc(1, sizeof(pgm));
		if (aPgm_baza == NULL)
			return 1;


		////////////////ppm////////////////
		ppm **aPpm_baza;
		ppm *aktywnyPpm;
		int ilosc_obrazow_ppm = 0;
		int aktywny_obraz_ppm = 0;
		int wybor3 = 0;
		
		aPpm_baza = calloc(1, sizeof(ppm));
		if (aPpm_baza == NULL)
			return 1;
		////////////////ppm////////////////
		
		system("cls");
		do 
			{
				if(aktywny_obraz != 0) {printf("Aktywny obraz: ", aktywny_obraz); wyswiet_nazwe(aktywnyPgm);}
				printf("Ilosc obrazow:%d\n", ilosc_obrazow);
				menu();
				printf("Wybierz funkcje:\n");
				while (scanf("%d", &wybor) == 0)
					{
						while ( getchar() != '\n' );
						printf("Error: Wprowadzona bledna wartosc\nWybierz odpowiednia funkcje\n");
					}
				

				
				switch (wybor)
					{
						case 1:
						system("cls");
						system("dir /w");
						printf("\n\n");
						wgraj(aPgm_baza, &ilosc_obrazow);
						system("cls");
						if(ilosc_obrazow > 0) printf("Obraz zostal wgrany\n\n");
						break;


						case 2:
						if(ilosc_obrazow == 0) 
							{
								system("cls");
								printf("Error: Nie ma wgranych obrazow  :(\n\n");
								break;
							}
						if(aktywny_obraz == 0)
							{
								system("cls");
								printf("Error: Wybierz aktywny obraz  \n\n");
								break;
							}
						usun(aPgm_baza, aktywny_obraz, &ilosc_obrazow);
						system("cls");
						printf("Obraz zostal usuniety\n\n");
						aktywny_obraz = 0;
						break;


						case 3:
						if(ilosc_obrazow == 0) 
							{
								system("cls");
								printf("Error: Nie ma wgranych obrazow  :(\n\n");
								break;
							}
						if(aktywny_obraz == 0)
							{
								system("cls");
								printf("Error: Wybierz aktywny obraz  \n\n");
								break;
							}
						
						zapisz(aktywnyPgm, akcja);
						system("cls");
						if(akcja == 0) printf("Nie bylo zastosowano zadnych operacji na obrazie\nObraz o takiej nazwie i tresci juz istnieje\n\n");
						else printf("Obraz zostal zapisany\n");
						break;


						case 4:
						if(ilosc_obrazow == 0) 
							{
								system("cls");
								printf("Error: Nie ma wgranych obrazow  :(\n\n");
								break;
							}
						system("cls");
						wyswietl_baze(aPgm_baza, ilosc_obrazow);
						printf("Wybierz aktywny obraz:");
						int tmp = akcja;
						do
							{
								while (scanf("%d", &aktywny_obraz) == 0)
								{
									while ( getchar() != '\n' );
									printf("Error: Wprowadzona bledna wartosc\nWybierz odpowiedni obraz\n");
								}
								
								system("cls");
								if((aktywny_obraz <= 0) || (aktywny_obraz > ilosc_obrazow)) printf("Nie istneje obraz pod tym numerem\n");
							}while((aktywny_obraz <= 0) || (aktywny_obraz > ilosc_obrazow));
						aktywnyPgm = aPgm_baza[aktywny_obraz-1];
						if(tmp != akcja) akcja = 0;
						break;


						case 5:
						if(ilosc_obrazow == 0) 
							{
								system("cls");
								printf("Error: Nie ma wgranych obrazow  :(\n\n");
								break;
							}
						if(aktywny_obraz == 0)
							{
								system("cls");
								printf("Error: Wybierz aktywny obraz  \n\n");
								break;
							}
							system("cls");
							printf("1->Obrot90\n2->Negatyw\n3->Szum\n4->Filtr\n");
							int wybor2 = 0;
							printf("Wybierz odpowiednia funkcje:\n");
							while (scanf("%d", &wybor2) == 0)
								{
									while ( getchar() != '\n' );
									printf("Error: Wprowadzona bledna wartosc\nWybierz odpowiednia funkcje\n");
								}
							switch(wybor2)
								{

									case 1:
									akcja = obrot90(&aktywnyPgm);
									system("cls");
									printf("Obraz zostal obrocony\n");
									break;
		
									case 2:
									akcja = negatyw(aktywnyPgm);
									system("cls");
									printf("Nalozono negatyw na obraz\n");
									break;
		
									case 3:
									akcja = szum(aktywnyPgm);
									system("cls");
									printf("Obraz zostal zaszumiony\n");
									break;
		
									case 4:
									akcja = filtr(aktywnyPgm);
									system("cls");
									printf("Obraz zostal odfiltrowany\n");
									break;

									default:
									system("cls");
									printf("Nie istneje taka funkcja\n");
									break;
								}
						
						break;

						case 6:
						if(ilosc_obrazow == 0) 
							{
								system("cls");
								printf("Error: Nie ma wgranych obrazow  :(\n\n");
								break;
							}
						if(aktywny_obraz == 0)
							{
								system("cls");
								printf("Error: Wybierz aktywny obraz  \n\n");
								break;
							}

						system("cls");
						histogram(aktywnyPgm, tab_histogram);
						printf("Histogram zostal zapisany do CSV\n");
						break;

						case 7:  /////////////////////////ppm//////////////////////////

						
							
								system("cls");
								printf("      Podprogram dla obrazow *.ppm\n\n\n");
							do {
								if(aktywny_obraz_ppm != 0) {printf("Aktywny obraz: ", aktywny_obraz_ppm); wyswiet_nazweppm(aktywnyPpm);}
								printf("Ilosc obrazow:%d\n", ilosc_obrazow_ppm);
								menuppm();
								printf("Wybierz odpowiednia funkcje:\n");
								while (scanf("%d", &wybor3) == 0)
									{
										while ( getchar() != '\n' );
										printf("Error: Wprowadzona bledna wartosc\nWybierz odpowiednia funkcje\n");
									}
							switch(wybor3)
								{

									case 1:
									system("cls");
									system("dir /w");
									printf("\n\n");
									wgrajppm(aPpm_baza, &ilosc_obrazow_ppm);
									system("cls");
									printf("      Podprogram dla obrazow *.ppm\n\n\n");
									printf("Obraz ppm zostal wgrany \n");
									break;
		
									case 2:
									if(ilosc_obrazow_ppm == 0) 
										{
											system("cls");
											printf("Error: Nie ma wgranych obrazow  :(\n\n");
											break;
										}
									if(aktywny_obraz_ppm == 0)
										{
											system("cls");
											printf("Error: Wybierz aktywny obraz  \n\n");
											break;
										}
									
									negatywppm(aktywnyPpm);
									system("cls");
									printf("      Podprogram dla obrazow *.ppm\n\n\n");
									printf("Negatyw nalozony\n");
									break;
		
									case 3:
									if(ilosc_obrazow_ppm == 0) 
										{
											system("cls");
											printf("Error: Nie ma wgranych obrazow  :(\n\n");
											break;
										}
									if(aktywny_obraz_ppm == 0)
										{
											system("cls");
											printf("Error: Wybierz aktywny obraz  \n\n");
											break;
										}

									obrot90ppm(&aktywnyPpm);
									system("cls");
									printf("      Podprogram dla obrazow *.ppm\n\n\n");
									printf("Obraz zostal obrocony\n");
									break;
		
									case 4:
									if(ilosc_obrazow_ppm == 0) 
										{
											system("cls");
											printf("Error: Nie ma wgranych obrazow  :(\n\n");
											break;
										}

									system("cls");
									wyswietl_bazeppm(aPpm_baza, ilosc_obrazow_ppm);
									printf("Wybierz aktywny obraz:");
						
									do{
										while (scanf("%d", &aktywny_obraz_ppm) == 0)
										{
											while ( getchar() != '\n' );
											printf("Error: Wprowadzona bledna wartosc\nWybierz odpowiedni obraz\n");
										}
										if((aktywny_obraz_ppm <= 0) || (aktywny_obraz_ppm > ilosc_obrazow_ppm)) printf("Nie istneje obraz pod tym numerem\n");
									}while((aktywny_obraz_ppm <= 0) || (aktywny_obraz_ppm > ilosc_obrazow_ppm));
									system("cls");
									printf("      Podprogram dla obrazow *.ppm\n\n\n");
									aktywnyPpm = aPpm_baza[aktywny_obraz_ppm-1];
							
									break;

									case 5:
									system("cls");
									zapiszppm(aktywnyPpm);
									printf("      Podprogram dla obrazow *.ppm\n\n\n");
									printf("Obraz zostal zapisany\n");
									break;

									case 6:
									if(ilosc_obrazow_ppm == 0) 
										{
											system("cls");
											printf("Error: Nie ma wgranych obrazow  :(\n\n");
											break;
										}
									if(aktywny_obraz_ppm == 0)
										{
											system("cls");
											printf("Error: Wybierz aktywny obraz  \n\n");
											break;
										}
									
									czarnebialeppm(aktywnyPpm);
									czarnebialeppm(aktywnyPpm);
									system("cls");
									printf("      Podprogram dla obrazow *.ppm\n\n\n");
									printf("Obraz odwrocono w czarno-bialy\n");
									break;

									case 0:
									wybor3 = 0;
									break;
									default:
									system("cls");
									printf("Nie istneje taka funkcja\n");
									break;
								}
						
					
						}while(wybor3 !=0);
						system("cls");
						break; ////////////////////////////ppm/////////////////////////

						case 0:
						wybor = 0;
						system("cls");
						break;

						default:
						system("cls");
						printf("Error: Wybrana funkcja nie istneje, Wybierz odpowiednia funkcje\n\n");
						break;
					}

			}while(wybor != 0);

		zwolnij_pamiec(aPgm_baza, &ilosc_obrazow);
		zwolnij_pamiecppm(aPpm_baza, &ilosc_obrazow_ppm);
		//printf("Pamiec zostala zwolniona\n");
		return 0;
	}