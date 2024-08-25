#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void creer_compte(char *login, char *password);
int verifier_utilisateur(char *login, char *password) ;
void afficher_formulaire_ip() ;

int main() {
    char * query_string;
    char new_login[50];
    char new_password[50];
    char login[50];
    char password[50];

    printf("content-type: text/html\n\n");
    printf("<html>\n<head>\n<title>Resultat</title>\n</head>\n<body>\n");

    query_string = getenv("QUERY_STRING");
    if (query_string == NULL) {
        printf("<p>Erreur : aucune donnee reçue.</p>\n");
        printf("</body></html>\n");
        return 1;
    }

    /// creation et connection
    if (sscanf(query_string, "new_login=%49[^&]&new_password=%49[^&]", new_login, new_password) == 2) 
    {
        creer_compte(new_login, new_password);
        
     
        if (verifier_utilisateur(new_login, new_password)) 
        {
            printf("<p> <center><b>Connexion automatique reussie </b></center>!</p>\n");
            afficher_formulaire_ip();  
        } 
        else 
        {
            printf("<p>Erreur lors de la connexion automatique.</p>\n");
        }
    }
   
   /// connexion 
    else if (sscanf(query_string, "login=%49[^&]&password=%49[^&]", login, password) == 2) 
    {
        if (verifier_utilisateur(login, password)) 
        {
            printf("<p>Connexion reussie !</p>\n");
            afficher_formulaire_ip();  
        } 
        else 
        {
            printf("<p>Erreur : login ou mot de passe incorrect.</p>\n");
        }
    }
   

    printf("</body></html>\n");
    return 0;
}

void afficher_formulaire_ip() 
{
    printf("<h2>Entrer l'adresse IP</h2>\n");
    printf("<form action=\"decimal.cgi\" method=\"GET\">\n");
    printf("Adresse IP: <input type=\"text\" name=\"ip\" >\n");
    printf("<input type=\"submit\" value=\"Envoyer\">\n");
    printf("</form>\n");
}

int verifier_utilisateur(char *login, char *password) {
    char file_login[50];
    char file_password[50];
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("<p>Erreur : fichier utilisateur introuvable.</p>\n");
        return 0;
    }

   
    while (fscanf(file, "%s %s", file_login, file_password) != EOF) {
        if (strcmp(login, file_login) == 0 && strcmp(password, file_password) == 0) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}

void creer_compte(char *login, char *password) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("<p>Erreur lors de l'ouverture du fichier utilisateur</p>");
        exit(1);
    }

    fprintf(file, "%s %s\n", login, password);
    fclose(file);
    printf("<p> <center>Compte cree avec succes !!! </center></p>\n");
}
