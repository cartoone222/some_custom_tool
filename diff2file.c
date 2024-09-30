#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define  MAX_LEN  1000

void printRed(char a){
    printf("\033[0;31m%c\033[0m",a);
}

int main(int argc, char *argv[]){

    FILE* fichier1;
    FILE* fichier2;

    int nomRecupere = 0;

    int fichierNbArg1 = 0;
    int fichierNbArg2 = 0;

    //gestion des argument

    for(int i = 1; i < argc; i++){
        if(nomRecupere == 0){
            fichierNbArg1 = i;
        }else if(nomRecupere == 1){
            fichierNbArg2 = i;
        }else{
            printf("use fichier nomFicher1 nomFicheir2 \n");
            return 0;
        }
        nomRecupere ++;
    }

    //corps du programe

    fichier1 = fopen(argv[fichierNbArg1], "r");
    fichier2 = fopen(argv[fichierNbArg2], "r");

    if (fichier1 == NULL)    {
        printf("Impossible d'ouvrir le fichier %s\n", argv[fichierNbArg1]);
        return 0;
    }

    if (fichier2 == NULL)    {
        printf("Impossible d'ouvrir le fichier %s\n", argv[fichierNbArg2]);
        return 0;
    }

    //______________________________________

    //\033[0;31m
    //\033[0m

    char line1[MAX_LEN], *result1;
    char line2[MAX_LEN], *result2;
    int cpt = 0;

    while(((result1 = fgets(line1,MAX_LEN,fichier1)) != NULL) && ((result2 = fgets(line2,MAX_LEN,fichier2)) != NULL)){
        if(strcmp(result1, result2) != 0){
            printf("%4i : ", cpt);

            int len1 = strlen(result1);
            int len2 = strlen(result2);

            for (int i = 0; i < len1; i++) {
                if (i < len2) {
                    if (result1[i] != result2[i]) {
                        printRed(result1[i]);
                    } else {
                        printf("%c", result1[i]);
                    }
                } else {
                    printRed(result1[i]);
                }
            }

            printf("       ");

            for (int i = 0; i < len2; i++) {
                if (i < len1) {
                    if (result1[i] != result2[i]) {
                        printRed(result2[i]);
                    } else {
                        printf("%c", result2[i]);
                    }
                } else {
                    printRed(result2[i]);
                }
            }
            printf("\n");
        }
        
        cpt++;
    }
    //deinistialisation

    fclose(fichier1);
    fclose(fichier2);

    return 0;
}