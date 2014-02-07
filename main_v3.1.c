/*****************
Version 3.1
Changes for the Player:
Variable amount of Players, Loading savegame
Changes in Sourcecode:
Dynamic Memory
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main_v2.1.h"
#define StandardStrich 40
struct Spielerdaten
{
	char Name[15];
	int Punkte;
	int VersucheRunde;
	int VersucheGesamt;
	int Bester;
	int Schlechtester;
};

int main(void)
{
	FILE *pDatei;
	char Load[200] = { 0 };
	char *Token;
	struct Spielerdaten *Spieler;
	char Neues_Spiel = 1;
	int iAnzSpieler = 0, iAnzSpieler_temp = 0;
	int iAktSpieler = 0;
	int iSchlechtester = 0;
	int iBester;
	int iZiel = 0;
	int iWert = 0;
	int iStellen = 0, iStellen_temp = 0;;
	int iRunde = 0;
	int i, j;
	char bRundeEnde = 0;
    char bSpielEnde[10];	
	bSpielEnde[0] = 1;
	
	Titel(" Willkommen bei Zahl V3.1! ");
	//Spiel laden
	pDatei = fopen ("Daten.dat", "r");
	if(pDatei == 0)		//Falls keine Daten.dat gefunden wurde
	{
		 printf("Keinen Spielstand gefunden\n");
	}
	else	//Falls Spielstand gefunden
	{
		printf("Es wurde ein gespeichertes Spiel gefunden!\n");
		fgets(Load, 200, pDatei);
		Token = strtok(Load, ",\n");
		iAnzSpieler_temp = atoi(Token);
		Token = strtok(0, ",\n");
		iStellen_temp = atoi(Token); 
		printf("Ein Spielstand mit %d Spielern und den Zahlen\nvon 0 bis %d\n", iAnzSpieler_temp, iStellen_temp);
		printf("Wollen Sie diesen Spielstand laden?\n0: Neues Spiel\nAlles Andere: Ja ");
		if (getchar() != '0')	//Falls Spielstand geladen werden soll
		{
			Neues_Spiel = 0;
			iAnzSpieler = iAnzSpieler_temp;
			iStellen = iStellen_temp;
			Spieler = (struct Spielerdaten*) malloc(sizeof(struct Spielerdaten) * iAnzSpieler); //Spielspeicher reservieren, Strukturzeiger
			for (i = 0; i < iAnzSpieler; i++)
			{
				fgets(Load, 200, pDatei);	//Zeile mit dem Namen einlesen
				Token = strtok(Load, ",\n");
				strcpy(Spieler[i].Name, Token);
				fgets(Load, 200, pDatei);	//Zeile mit den Werten einlesen
				Token = strtok(Load, ",\n");
				Spieler[i].Punkte = atoi(Token);
		    	Token = 	strtok(0, ",\n");
				Spieler[i].VersucheRunde = atoi(Token);
        		Token = strtok(0, ",\n");
				Spieler[i].VersucheGesamt = atoi(Token);
	    		Token = strtok(0, ",\n");
				Spieler[i].Bester = atoi(Token);
				Token = strtok(0, ",\n");
				Spieler[i].Schlechtester = atoi(Token);
			}
			fclose(pDatei);
			printf("Es wurde ein Spiel mit folgenden Spielern geladen:\n");
			for(i=0;i<iAnzSpieler;i++)
			{
				printf("%s, ", Spieler[i].Name);
			}
			printf("\n");
		}
		//Neues Spiel
		if(Neues_Spiel == 1)
		{
			printf("Ein neues Spiel wurde gestartet.\n");
			iAnzSpieler = Player();
			Spieler = (struct Spielerdaten*) malloc(sizeof(struct Spielerdaten) * iAnzSpieler);
			for (i = 0; i < iAnzSpieler; i++)
			{
				Spieler[i].Bester = 999999;
				Spieler[i].Punkte = 0;
				Spieler[i].VersucheRunde = 0;
				Spieler[i].VersucheGesamt = 0;
				Spieler[i].Schlechtester = 0;
			}
			if (iAnzSpieler > 1)
			{
				printf("Sie spielen mit %d Spielern!\n", iAnzSpieler);
				printf("Geben Sie nun die Namen der Spieler ein!\n");
				for (i = 0; i < iAnzSpieler; i++)
				{
					printf("Spieler %d: ", i + 1);
					scanf("%s", &Spieler[i].Name);
				}
			}
			else
			{
				printf("Sie spielen im Einzelspielermodus!\n");
			}
			iStellen = Stellen();
		}
	 }

	//Spielkonfig
	srand(clock());

	// Start des Spieles
	while (bSpielEnde[0] != '0')	// Hauptspiel
	{
		iRunde++;
		Linie(StandardStrich);
		printf("Runde %d, Zahlen von 0 bis %d\n", iRunde, iStellen);
		bRundeEnde = 0;
		iAktSpieler = 0;
		for (i = 0; i < iAnzSpieler; i++)
		{
			Spieler[i].VersucheRunde = 0;
		}
		while (bRundeEnde == 0)	// Einzelne Runden
		{
			if (iAnzSpieler > 1)
			{
				printf("%s", Spieler[iAktSpieler].Name);
				printf(" ist an der Reihe!\n");
			}
			iZiel = rand() % iStellen;	// Zielwert erstellen
			iWert = iZiel + 1;
			while (iWert != iZiel)	// einzelner zug
			{
				Spieler[iAktSpieler].VersucheRunde++;
				printf("Versuch %d: ", Spieler[iAktSpieler].VersucheRunde);
				scanf("%d", &iWert);
				if (iWert < iZiel)
				{
					printf("Ihr Wert ist zu klein!\n");
				}
				if (iWert > iZiel)
				{
					printf("Ihr Wert ist zu gross!\n");
				}
			}
			Titel("Richtig!");	// zug beendet
			// Jeweils besten versuch ermitteln und speichern 
			if (Spieler[iAktSpieler].VersucheRunde <
				Spieler[iAktSpieler].Bester)
				Spieler[iAktSpieler].Bester =
					Spieler[iAktSpieler].VersucheRunde;

			if (Spieler[iAktSpieler].VersucheRunde >
				Spieler[iAktSpieler].Schlechtester)
				Spieler[iAktSpieler].Schlechtester =
					Spieler[iAktSpieler].VersucheRunde;
			Linie(StandardStrich);
			if (iAktSpieler < iAnzSpieler)
			{
				iAktSpieler++;
			}
			if (iAktSpieler == iAnzSpieler)
			{
				bRundeEnde = 1;
			}
		}
		// runde beendet
		printf("Runde %d beendet!\n", iRunde);

		// schlechtesten der runde ermitteln 
		j = Spieler[0].VersucheRunde;
		iSchlechtester = 0;
		for (i = 0; i < iAnzSpieler; i++)
		{
			if (Spieler[i].VersucheRunde > j)
			{
				j = Spieler[i].VersucheRunde;
				iSchlechtester = i;
			}
			j = Spieler[i].VersucheRunde;
		}

		// besten der runde ermitteln 
		j = Spieler[0].VersucheRunde;
		iBester = 0;
		for (i = 1; i < iAnzSpieler; i++)
		{
			if (Spieler[i].VersucheRunde < j)
			{
				j = Spieler[i].VersucheRunde;
				iBester = i;
			}
			j = Spieler[i].VersucheRunde;
		}
		Spieler[iBester].Punkte++;

		// Ergebnis Ausgabe
		// Versuche anzeigen
		Titel("Rundenergebnisse");
		printf("Anzahl der Versuche:\n");
		for (i = 0; i < iAnzSpieler; i++)
		{
			if (iAnzSpieler > 1)
			{
				printf("%s", Spieler[i].Name);
				printf(": ");
			}
			printf("%d\n", Spieler[i].VersucheRunde);
		}
		if (iAnzSpieler > 1)
		{
			// besten anzeigen 
			printf("%s", Spieler[iBester].Name);
			printf(" hat diese Runde gewonnen!\n");

			// schlechtesten anzeigen 
			printf("%s", Spieler[iSchlechtester].Name);
			printf(" hat diese Runde verloren!\n");
		}
		Titel("Spielergebnisse");
		printf("Punktestand:\n");
		for (i = 0; i < iAnzSpieler; i++)
		{
			if (iAnzSpieler > 1)
			{
				printf("%s", Spieler[i].Name);
				printf(": ");
			}
			printf("%d\n", Spieler[i].Punkte);
		}
		printf("\nBester Versuch:\n");
		for (i = 0; i < iAnzSpieler; i++)
		{
			if (iAnzSpieler > 1)
			{
				printf("%s", Spieler[i].Name);
				printf(": ");
			};
			printf("%d\n", Spieler[i].Bester);
		}
		printf("\nSchlechtester Versuch:\n");
		for (i = 0; i < iAnzSpieler; i++)
		{
			if (iAnzSpieler > 1)
			{
				printf("%s", Spieler[i].Name);
				printf(": ");
			}
			printf("%d\n", Spieler[i].Schlechtester);
		}
       
        //Spiel speichern
       pDatei = fopen ("Daten.dat", "w+");
        if(pDatei == 0)
           printf("Fehler");
        else
        {
			
			fprintf(pDatei,"%d,%d\n" , iAnzSpieler, iStellen);
			for(i=0;i<iAnzSpieler;i++)
			{
        		fprintf(pDatei, "%s\n", Spieler[i].Name);
				fprintf(pDatei, "%d,%d,%d,%d,%d\n", Spieler[i].Punkte, Spieler[i].VersucheRunde, Spieler[i].VersucheGesamt, Spieler[i].Bester, Spieler[i].Schlechtester);

			}
			fclose(pDatei);
			printf("Spiel gespeichert!\n");
        }

		Linie(StandardStrich);
		printf("Neue Runde?\nJa:   Irgendwas\nNein: 0\n");
		fflush(stdin);
		scanf("%s", &bSpielEnde[0]);
	}						
	// spiel beendet
	printf("ENDE");
	free(Spieler);
	return 0;
}