/*

vigenere.c

Encrypts user string with user keyword.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
 
int main(int argc, string argv[]) {

    // key must be entered at command line. 
    if (argc != 2) {
        printf("Error: \n");
        return 1;
    }            
    char* key = argv[1];
    int keylength = strlen(key);
    
    // run through key, make sure everything is alphabetical.
    for (int c = 0, n = keylength; c < n; c++) {  
        if (!isalpha(key[c])) {
            printf("Error: \n");
            return 1;
        }
    }
    // get string for encryption.
    string s = GetString();
    int cipher;       
                                    
    for (int i = 0, j = 0; i < strlen(s); i++) {
    
        // if string value is alphabetical...                 
        if (isalpha(s[i])) {
        
            // reset key to beginning.
            if (j >= keylength) {
                j = 0;
            }
                
            if(islower(key[j])) {
                key[j] = key[j] - 97;
            }
                
            if(isupper(key[j])) {
                key[j]= key[j] - 65;
            }
            
            // modulo to keep encrypted string within LC alphabet.
            if (islower(s[i])) {
                cipher = (s[i] + key[j]);
                cipher = (((cipher - 97) % 26) + 97);
                printf("%c", cipher);
                j++;
            }
            
            // modulo to keep encrypted string within UC alphabet.
            else {
                cipher = (s[i] + key[j]);
                cipher = (((cipher - 65) % 26) + 65);
                printf("%c", cipher);
                j++;
            }              
        }
        
        // if not alphabetical, just print.            
        else {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
