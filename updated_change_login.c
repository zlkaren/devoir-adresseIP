
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOGIN 50
#define MAX_LINE_LENGTH 100

int main() 
{
    char * query_string = NULL;
    char new_login[30], login[30], password[30];
    char buffer[MAX_LINE_LENGTH];
    
    printf("Content-type: text/html\n\n");
    query_string = getenv("QUERY_STRING");
    
    if (query_string == NULL) {
        printf("<p>Erreur : aucune donnee reçue.</p>\n");
        printf("</body></html>\n");
        return 1;
    }
    
    // Parse query string
    sscanf(query_string, "new_login=%29[^&]&login=%29[^&]&password=%29s", new_login, login, password);
    
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL) {
        printf("<p>Erreur : impossible d'ouvrir le fichier users.txt.</p>\n");
        return 1;
    }
    
    // Read the file content into memory
    char file_content[1000] = "";
    char *position;
    int found = 0;
    
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // Check if the current line contains the login
        if (strstr(buffer, login) != NULL) {
            // Replace the login in the line
            position = strstr(buffer, login);
            strncpy(position, new_login, strlen(new_login));
            // Pad the remaining part of the line to avoid leftover characters
            for (int i = strlen(new_login); i < strlen(login); i++) {
                position[i] = ' ';
            }
            found = 1;
        }
        strcat(file_content, buffer);
    }
    
    // Check if login was found
    if (!found) {
        printf("<p>Erreur : login non trouvé.</p>\n");
        fclose(file);
        return 1;
    }
    
    // Rewrite the updated content back to the file
    freopen("users.txt", "w", file);
    fputs(file_content, file);
    fclose(file);
    
    printf("<html><body><h2>Votre login a ete modifie en : %s</h2></body></html>", new_login);
    
    return 0;
}
