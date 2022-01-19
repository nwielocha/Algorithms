#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DL_LISTY 14029

struct lista_haszujaca {
    int klucz;
    char *slowo;
    struct lista_haszujaca *wsk_listy_h;
};

typedef struct lista_haszujaca lista_haszujaca;

struct tablica_haszujaca {
    struct lista_haszujaca **tablica;
    int *kolizje;
};

typedef struct tablica_haszujaca tablica_haszujaca;

tablica_haszujaca *stworzTabliceHaszujaca() {
    tablica_haszujaca *tablica_haszujaca = NULL;

    if ((tablica_haszujaca = malloc(sizeof(tablica_haszujaca) * 1)) == NULL) 
        return NULL;
    if ((tablica_haszujaca->tablica = malloc(sizeof(lista_haszujaca*) * DL_LISTY)) == NULL) 
        return NULL;
    if ((tablica_haszujaca->kolizje = (int*) calloc(DL_LISTY, sizeof(int))) == NULL) 
        return NULL;

    for (int i = 0; i < DL_LISTY; i++) 
        tablica_haszujaca->tablica[i] = NULL;

    return tablica_haszujaca;
}

int haszowanie(char *slowo) {
    int dlugosc = strlen(slowo);
    int wynik = 0, i;

    for (i = 0; i < dlugosc - 1; i += 2) 
        wynik ^= ((256 * slowo[i]) + slowo[i + 1]);

    if (slowo[i] != 0)
        wynik ^= (256 * slowo[i]);

    return wynik % DL_LISTY;
}

lista_haszujaca *wstawHasz(int klucz, char *string) {
    lista_haszujaca *nowa_para;

    if ((nowa_para = malloc(sizeof(lista_haszujaca))) == NULL)
        return NULL;

    nowa_para->klucz = klucz;

    if ((nowa_para->slowo = strdup(string)) == NULL) 
        return NULL;

    nowa_para->wsk_listy_h = NULL;

    return nowa_para;
}

void ustawListeHaszujaca(tablica_haszujaca *tablica_haszujaca, char *string) {
    int slot = 0;
    lista_haszujaca *nowa_para = NULL;
    lista_haszujaca *lista_haszujaca = NULL;
    lista_haszujaca *poprzednia_lista = NULL;

    slot = haszowanie(string);

    lista_haszujaca = tablica_haszujaca->tablica[slot];

    while (lista_haszujaca != NULL && lista_haszujaca->slowo != NULL && strcmp(string, lista_haszujaca->slowo) != 0) {
        poprzednia_lista = lista_haszujaca;
        lista_haszujaca = lista_haszujaca->wsk_listy_h;
    }

    nowa_para = wstawHasz(slot, string);

    // Poczatek listy powiazanej w tym slocie
    if (lista_haszujaca == tablica_haszujaca->tablica[slot]) {
        nowa_para->wsk_listy_h = lista_haszujaca;
        tablica_haszujaca->tablica[slot] = nowa_para;
    }
    else if (lista_haszujaca == NULL) {
        tablica_haszujaca->kolizje[slot]++;
        poprzednia_lista->wsk_listy_h = nowa_para; 
    }
}

int main() {

    return 0;
}
