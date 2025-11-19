#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

int criar_cha(const char *nomeCha) {
    FILE *f = fopen("chas.txt", "a+");
    if (!f) return 0;

    int codigo = 1;
    char linha[150];

    while (fgets(linha, sizeof(linha), f)) {
        int codTemp;
        sscanf(linha, "%d;", &codTemp);
        if (codTemp >= codigo) codigo = codTemp + 1;
    }

    fprintf(f, "%d;%s\n", codigo, nomeCha);

    fclose(f);
    return codigo;
}

int ler_cha(int codigo, char *saida) {
    FILE *f = fopen("chas.txt", "r");
    if (!f) return 0;

    char linha[150];
    while (fgets(linha, sizeof(linha), f)) {
        int codTemp;
        char nome[MAX_NOME];

        sscanf(linha, "%d;%[^\n]", &codTemp, nome);

        if (codTemp == codigo) {
            strcpy(saida, nome);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int remover_cha(int codigo) {
    FILE *f = fopen("chas.txt", "r");
    if (!f) return 0;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(f);
        return 0;
    }

    char linha[150];
    int achou = 0;

    while (fgets(linha, sizeof(linha), f)) {
        int codTemp;
        sscanf(linha, "%d;", &codTemp);

        if (codTemp != codigo) {
            fputs(linha, temp);
        } else {
            achou = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove("chas.txt");
    rename("temp.txt", "chas.txt");

    return achou;
}
