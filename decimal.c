#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void adresse();

int main()
{
	adresse();
	return (0);	
}

void adresse()
{
		char * query_string = NULL;
		int n = 0;
		int i=0;
		printf("content-type: text/html \n\n");
		query_string = getenv("QUERY_STRING");
		if(query_string == NULL)
		{
				printf("erreur de copie");
		}
		while(query_string [i] != '\0')
		{
				if(query_string[i] == '.' && query_string[i+1] != '\0' && query_string[i+1] != '.' && query_string[i+1] != '+')
				{
						n++;
				}
				i++;
		}
		if (n == 3)
		{
				char * ip = NULL;
				ip = strtok(query_string, "=");
				ip = strtok(NULL, ".");
				char * debut = ip;
				int n_debut;
				n_debut = atoi(debut);
				
				ip = strtok(NULL, ".");
				char * deux = ip;
				int  n_deux;
				n_deux = atoi(deux);
				
				ip = strtok(NULL, ".");
				char * trois = ip;
				int n_trois;
				n_trois = atoi(trois);
				
				
				ip = strtok(NULL, ".");
				char * fin = ip;
				int n_fin;
				n_fin = atoi(fin);
				
				if( n_debut >255 ||  n_deux >255 || n_trois >255 || n_fin >255)
				{
						printf("ip invalide");
						printf("<a href = \"decimal.html\"> <button> retour </button></a>");
				}
				
				else
				{
					 if(n_debut < 128)
						{
								printf("ip de classe A");
						}
					if(n_debut > 128 && n_debut < 192)
						{
								printf("ip de classe B");
						}
					if(n_debut > 192 && n_debut < 224)
						{
								printf("ip de classe C");
						}
					if(n_debut > 224 && n_debut < 240)
						{
								printf("ip de classe D");
						}
					if(n_debut >240 && n_debut < 255)
						{
								printf("ip de classe E");
						}
				}
			}
			else
			{
					printf("non ip");
					printf("<a href = \"decimal.html\"> <button> retour </button></a>");
			}
}
