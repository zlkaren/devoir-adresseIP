#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void changeMdp();


int main()
 {
   changeMdp();
    return 0;
}

void changeMdp()
{
char * query_string = NULL;
   char login[30] = {0};
   char password[30] = {0};
   char new_password[30] = {0};
   char chaine[100];
   char file_content[1000] = "";
    int found = 0;
   
    printf("content-type: text/html\n\n");
    query_string = getenv("QUERY_STRING");
    
    if (query_string == NULL) {
        printf("<p>Erreur : aucune donnee reçue.</p>\n");
        printf("</body></html>\n");
        exit (1);
    }
    sscanf(query_string, "login=%30[^&]&password=%30[^&]&new_password=%30s" , login ,password, new_password);
    printf("%s", password);
    
      FILE *file = fopen("users.txt", "r+");
    if (file == NULL)
    {
        printf("<p>Erreur : impossible d'ouvrir le fichier users.txt.</p>\n");
        exit (1);
    }

    while (fgets(chaine, sizeof(chaine), file) != NULL)
    {
       
        if (strstr(chaine, login) != NULL && strstr(chaine, password) != NULL) {
            
            char *password_pos = strstr(chaine, password);
            strncpy(password_pos, new_password, strlen(new_password));
           
            for (int i = strlen(new_password); i < strlen(password); i++) {
                password_pos[i] = ' ';
            }
            found = 1;
        }
        strcat(file_content, chaine);
    }

   
    if (!found) {
        printf("Content-type: text/html\\n\\n");
        printf("<html><body><h2>Erreur : login ou mot de passe incorrect.</h2></body></html>");
        fclose(file);
        exit (1);
    }

   
    freopen("users.txt", "w", file);
    fputs(file_content, file);
    fclose(file);

    printf("Content-type: text/html\\n\\n");
    printf("<html><body><h2>Votre mot de passe a ete modifie avec succes.</h2></body></html>");
    	
	
}
