
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete();

int main() 
{
	delete();

    return 0;
}

void delete()
{
		 char* query_string = NULL;
    char login[30] = {0};
    char password[30] = {0};
    char chaine[100] = {0};
    FILE *file, *tempfile;

    printf("content-type: text/html\n\n");

    query_string = getenv("QUERY_STRING");
    if (query_string == NULL) 
    {
        printf("<p>Erreur: aucune donnée reçue.</p>\n");
        exit (1);
    }

    sscanf(query_string, "login=%30[^&]&password=%30s", login, password);

    // Ouvrir le fichier original en lecture et un fichier temporaire en écriture
    file = fopen("users.txt", "r");
    tempfile = fopen("temp.txt", "w");

    if (file == NULL )
     {
        printf("<p>Erreur: impossible d'ouvrir  fichier users</p>\n");
        exit (1);
    }
    if(tempfile == NULL)
    {
		printf("<p>erreur d'ouverture temp</p>");
		exit (1);
	}

    int found = 0;
    while (fgets(chaine, sizeof(chaine), file) != NULL) 
    {
        if (strstr(chaine, login) != NULL && strstr(chaine, password) != NULL) 
        {
            found = 1;
            continue;
        } 
        else
         {
            fputs(chaine, tempfile);
        }
    }

    fclose(file);
    fclose(tempfile);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found) 
    {
        printf("<p>Compte supprime avec succes. Vous allez etre redirige.</p>\n");
        printf("<meta http-equiv=\"refresh\" content=\"2;url=mdp.html\" />");
    } 
    else 
    {
        printf("<p>Erreur: compte non trouve.</p>\n");
    }
}
