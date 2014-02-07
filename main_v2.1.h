int Player();
int Stellen();
void Linie(int);
int NameAusgeben(char[][30], int);
int Titel(char[30]);

int Player()
{
	int iPlayers;
	printf("Wie viele Spieler nehmen an der Runde teil\?\n");
	scanf_s("%d",&iPlayers);
	return iPlayers;
}

int Stellen()
{
	int iStellen;
	int iMultiplikator = 10;
	int i;
	printf("Wie viele Stellen sollen erraten werden?\n");
	scanf_s("%d",&iStellen);
	printf("Sie spielen mit %d Stellen!\n",iStellen);
	for(i = 1; i< iStellen; i++)
	{
		iMultiplikator *= 10;
		}
	return iMultiplikator;
	}
	
void Linie(int iAnzahl)
{
	int i;
	for(i = 0; i < iAnzahl; i++)
	{
		printf("%c", '-');
	}
	printf("\n");
}

int NameAusgeben(char cNamen[][30], int iSpieler)
{
	int i;
    	for(i = 0;i < 15;i++)
    	{
    		printf("%c",cNamen[iSpieler][i]);
    	}
    	return 0;
}

int Titel(char cText[30])
{
	int i, j = 7;
	for(i = 0;(i < 30)&&(j != 0); i++)
	{
		j = cText[i];
	}
	i++;
	Linie(i);
	printf("|%s|\n",cText);
	Linie(i);
	return 0;
	}
	