# Algorithms
Algorithms written for the 3rd semester classes.

# Lab 1 - Złożoność

W pliku AL2.c znajdują się (zaimplementowane) funkcje, które dla ustalonej zero-jedynkowej macierzy kwadratowej M rozmiaru n×n wyznaczają jej podmacierz o największej liczbie jedynek (interpretując to graficznie – zacieniowany prostokąt o największym polu). Przeanalizuj kody tych funkcji oraz oszacuj również ich złożoność czasową. Następnie w oparciu o pomiar czasu działania z zadania AL1.1 przetestuj doświadczalnie zaproponowane oszacowania. Ponadto przetestuj, czy i jak zmieniają się te oszacowania dla każdej z funkcji, gdy macierz wejściowa składa się z (a) samych zer, (b) samych jedynek  

Jako rozwiązanie przesłać kod programu wykonującego pomiary z dołączonymi wynikami wygenerowanymi przez ten program dla wszyskich czterech funkcji. Wyniki te można dołączyć np. jako komentarz na końcu kodu programu.

# Lab 2 - Sortowanie kopcowe (Heapsort)

Zaimplementuj omawiany na wykładzie algorytm sortowania przez kopcowanie.(4 pkt.)
Zmodyfikuj procedurę Heapify tak, aby używała iteracji zamiast rekursji. (1 pkt)

Wejście. Liczby zapisane są w kolejnych wierszach pliku tekstowego.

Wyjście. Posortowane liczby z pliku wejściowego zapisane w kolejnych wierszach pliku wyjściowego.

# Lab 3 - Quicksort

Zaimplementuj algorytm sortowania szybkiego omówiony na wykładzie. (3 pkt.)

Zmierz i porównaj czasy działania sortowania dla dwóch rodzajów danych: dane losowe oraz dane skrajnie niekorzystne (np. liczby uprządkowane rosnąco lub malejąco). (1 pkt)

Testy (pomiary czasu) powinny być wykonane dla różnych wielkości tablicy, np. 10000 elementów, 50000 elementów, 100000 elementów i 150000 elementów. 

# Lab 4 - Zliczanie pozycyjne (Radix Sort)

W pliku nazwiskaASCII (ściągniętym z nieistniejącej już chyba strony www.futrega.org/etc/nazwiska.html) znajduje się wykaz zapisów postaci

X Nazwisko

gdzie X jest liczbą typu int określającą popularność nazwiska Nazwisko. Posortuj te zapisy alfabetycznie według nazwisk i wygeneruj nowy plik zawierający tak uporządkowane zapisy. Sortowanie wykonaj na dwa sposoby:
sortowanie pozycyjne jak w zadaniu AL4.6 oraz
sortowanie przez porównania: Quicksort lub Heapsort.
Porównaj rzeczywiste czasy obu sortowań (samych sortowań, bez czytania/zapisu do pliku).
Uwaga: Plik z nazwiskami można przekonwertować tak, aby pozbyć się znaków spoza kodu ASCII.

# Lab 5 - Listy dowiązaniowe (Linked List)

Zaimplementuj strukturę listy dowiązaniowej (jednokierunkowej lub dwukierunkowej) niecyklicznej, bez wartownika, której elementami są słowa (czyli ciągi znaków), oraz operacje
wstaw(s, L) - wstawia słowo s na początek listy L,

drukuj(L) - wypisuje elementy listy L,

szukaj(s, L) - zwraca wskaźnik na węzeł listy zawierający słowo s o ile takie słowo znajduje się na liście L, w przeciwnym wypadku zwraca NULL,

usuń(s, L) - usuwa z listy L węzeł zawierający słowo s o ile takie słowo znajduje się na liście,

kasuj(L) - usuwa wszystkie węzły listy L , zwalniając również zajętą przez nie pamięć (free()).

(ta grupa operacji: razem 3pkt.)
bezpowtorzeń(L) - tworzy kopię listy L, ale bez powtórzeń słów; zwraca wskaźnik na utworzoną kopię. Lista L pozostaje bez zmiany. (0.5 pkt.)

scal(L1,L2) - tworzy listę L3 zawierającą wszystkie słowa z list L1 i L2 (również ze wszystkimi powtórzeniami); zwraca wskaźnik na utworzoną listę. Listy L1 i L2 przestają istnieć (można więc wykorzystać ich węzły do zbudowania listy L3.). Efektywne (pod względem złozoności czasowej) rozwiązanie doczepi po prostu jedną listę do drugiej. (0.5 pkt.)

# Lab 6 - Haszowanie łańcuchowe i haszowanie z adresem otwartym

Zaprogramować – zgodnie z przydzielonym wariantem (zapisanym jako komentarz w ocenie zadania) wybrane operacje na tablicy z haszowaniem z adresowaniem otwartym oraz przeprowadzić testy i pomiary:

Operacje przetestować osobno na małej tablicy, z wydrukiem kontrolnym,
testy/pomiary przeprowadzić na tablicy większego rozmiaru, np. rzędu kilku tysięcy.
W tablicy haszowań mają być struktury zawierające dwa pola:

ilosc – typu int
nazwisko – ciąg znaków

Kluczami mają być nazwiska (patrz schematy zamiany w AL6.2). W tablicy haszowań mogą znajdować się wskaźniki na te struktury bądź całe struktury (lub obiekty). W pliku nazwiskaASCII (ściągniętym z nieistniejącej już chyba strony www.futrega.org/etc/nazwiska.html) znajduje się wykaz zapisów postaci: [liczba typu int] [nazwisko], które można wykorzystać.

Warianty operacji i pomiarów

[W] Operacja WSTAW. Pomiar: średnia ilość prób wykonanych przy wstawianiu elementu (średnia ze wszystkich wstawień) przy różnych wypełnieniach tablicy: 50%, 70% i 90%.
[S] Operacje WSTAW i SZUKAJ. Pomiar: wypełnienie tablicy do 80% i wykonanie pewnej ilości operacji szukaj (np. ostatnich 20) ze zliczaniem i wydrukiem ilości prób przy szukaniu każdego klucza.
[U] Operacje WSTAW i USUŃ. Pomiar: wstawiać elementy aż do wypełnienia tablicy w 80%, potem usunąć połowę wstawionych elementów i następnie znowu dopełnić tablicę innymi elementami do 80%. Po tych operacjach zliczyć i wypisać, ile pozycji w tablicy jest wypełnionych znacznikiem DEL (miejsce po usuniętym elemencie)
Warianty techniki rozwiązywania kolizji
[OL] adresowanie otwarte liniowe
[OK] adresowanie otwarte kwadratowe
[OD] adresowanie otwarte, dwukrotne haszowanie
Możliwe kombinacje wariantów: [W+OL], [W+OK], [W+OD], [S+OL], [S+OK], [S+OD], [U+OL], [U+OK], [U+OD].

# Lab 7 - Binary Search Tree

 Zaimplementuj strukturę danych, wraz z operacjami WSTAW, SZUKAJ, USUŃ, DRUKUJ, która realizuje koncepcję drzewa poszukiwań binarnych, którego kluczami/elementami są liczby całkowite. Przyjąć, że do drzewa wstawiane są klucze o różnych wartościach, a wypisanie (DRUKUJ) wartości węzłów odbywa się np. w porządku in-order (najlepiej z zaznaczaniem przez odstępy zagłębienia węzłów w drzewie) .
