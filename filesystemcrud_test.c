#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "filesystemcrud_functions.c"

int main() {

    FILE *f = fopen("chas.txt", "w");
    if (f) fclose(f);

    int codigo = criar_cha("Camomila");
    assert(codigo > 0);

    char nomeLido[100];
    assert(ler_cha(codigo, nomeLido) == 1);
    assert(strcmp(nomeLido, "Camomila") == 0);

    assert(remover_cha(codigo) == 1);

    assert(ler_cha(codigo, nomeLido) == 0);

    printf("TODOS OS TESTES PASSARAM! \n");
    return 0;
}
