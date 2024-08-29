#include <stdio.h>
#include <stdlib.h>

int main() {
    char * query_string = NULL;
	char login[30] ;
	char password[30];
	 
    printf("Content-type: text/html\n\n");
    query_string = getenv("QUERY_STRING");
    
    if (query_string == NULL) {
        printf("<p>Erreur : aucune donnee reçue.</p>\n");
        printf("</body></html>\n");
        return 1;
    }
    sscanf(query_string , "login=%15[^&]&password=%15s", login,password);
    printf("<p> %s <p>", login);
    printf("<html><body>");
    printf("<h2>Options du compte</h2>");
    printf("<form action=\"change_login.cgi\" method=\"get\">");
    printf("<label for=\"new_login\">Modifier le login :</label>");
    printf("<input type=\"text\" name=\"new_login\" required>");

    printf("<input type = \"hidden\" name = \"login\" value = \"%s\" >", login);
	printf("<input type = \"hidden\" name = \"password\" value = \"%s\" >", password);
	
    printf("<input type=\"submit\" value=\"Modifier le login\">");
    printf("</form>");

    printf("<br><br>");

    printf("<form action=\"change_password.cgi\" method=\"get\">");
    printf("<label for=\"new_password\">Modifier le mot de passe :</label>");
    printf("<input type = \"hidden\" name = \"login\" value = \"%s\" >", login);
    printf("<input type = \"hidden\" name = \"password\" value = \"%s\" >", password);
    printf("<input type=\"password\" name=\"new_password\" required>");
    printf("<input type=\"submit\" value=\"Modifier le mot de passe\">");
    printf("</form>");

    printf("<br><br>");

    printf("<form action=\"delete_account.cgi\" method=\"get\">");
    printf("<input type = \"hidden\" name = \"login\" value = \"%s\" >", login);
    printf("<input type = \"hidden\" name = \"password\" value = \"%s\" >", password);
    printf("<input type=\"submit\" value=\"Supprimer le compte\">");
    printf("</form>");

    printf("</body></html>");
    return 0;
}
