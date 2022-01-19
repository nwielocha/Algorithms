#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0
/////////////////////////////////////////////
//      PROCEDURY POMOCNICZE               //
/////////////////////////////////////////////
void utworz_MACIERZ(int n, int ***M) {
    // alokuje pamiecz na tablice rozmiaru n x n
    // i wpisuje losowe wartosci 0 / 1
    int i, j;

    (*M) = (int**) malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        (*M)[i] = (int*) malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) 
            (*M)[i][j] = rand() % 2;
    }
}
////////////////////////////////////////////
void utworz_MACIERZ_x(int n, int ***M, int x) {
    // alokuje pamiec na tablice rozmiaru n x n
    // i wpisuje wszedzie wartosci x
    int i, j;

    (*M) = (int**) malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) 
        (*M)[i] = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++)
            (*M)[i][j] = x;
}
//////////////////////////////////////////////
void wypisz_MACIERZ(int n, int **M) {
    // wypisuje wartosci tablicy
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) 
            printf("%d", M[i][j]);
        printf("\n");
    }
}
////////////////////////////////////////////////
void zwolnij_MACIERZ(int n, int **M) {
    // zwalnia pamiec zarezerwowana dla macierzy
    int i;
    for (i = 0; i < n; i++)
        free(M[i]);
    free(M);
}
////////////////////////////////////////////////
//          ALGORYTM PIERWSZY                 //
////////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M) {
    int x1, y1, x2, y2, x, y;
    int max = 0;
    int local_max = 0;

    for (x1 = 0; x1 < n; x1++)
        for (y1 = 0; y1 < n; y1++)
            for (x2 = n - 1; x2 > x1 - 1; x2--)
                for (y2 = n - 1; y2 > y1 - 1; y2--) {
                    local_max = 0;
                    for (x = x1; x < x2 + 1; x++)
                        for (y = y1; y < y2 + 1; y++)
                            local_max += M[x][y];
                    if ((local_max == (x2 - x1 + 1) * (y2 - y1 + 1)) && (local_max > max))
                        max = local_max;
                }
    return max;
}
///////////////////////////////////////////////////
//              ALGORYTM DRUGI                   //
///////////////////////////////////////////////////
int REKURENCJA(int **M, int x1, int y1, int x2, int y2) {
    if ((x2 == x1) && (y2 == y1))
        return M[x1][y1];
    else if ((x2 - x1) > (y2 - y1))
        return REKURENCJA(M, x1, y1, (int)(x1 + x2)/2, y2) * REKURENCJA(M, (int)(x1 + x2 + 1)/2, y1, x2, y2);
    else 
        return REKURENCJA(M, x1, y1, x2, (int)(y1 + y2)/2) * REKURENCJA(M, x1, (int)(y1 + y2 + 1)/2, x2, y2);
}
/////////////////////////////////////////////////////////
int ALGO_REKURENCYJNY(int n, int **M) {
    int x1, y1, x2, y2;
    int max = 0;
    int local_max;

    for (x1 = 0; x1 < n; x1++)
        for (y1 = 0; y1 < n; y1++)
            for (x2 = x1; x2 < n; x2++)
                for (y2 = y1; y2 < n; y2++) {
                    local_max = REKURENCJA(M, x1, y1, x2, y2) * (x2 - x1 + 1) * (y2 - y2 + 1);
                    if (local_max > max)
                        max = local_max;
                }
    return max;
}
//////////////////////////////////////////////////////////
//              ALGORYTM TRZECI                         //
//////////////////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M){
    int x1,x2,y;
    int max=0;
    int iloczyn;
    int **MM;

    utworz_MACIERZ_x(n,&MM,0);

    for(y=0;y<n;y++)
        for(x1=0;x1<n;x1++){
            iloczyn=1;
            for(x2=x1;x2<n;x2++){
                iloczyn*=M[x2][y];
                MM[x1][x2]=iloczyn*(x2-x1+1+MM[x1][x2]);
                if (MM[x1][x2]>max) max=MM[x1][x2];
            }
        }
    return max;
}
/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M){
    int x1,y1,x2,y2,ymax;
    int max=0;
    int local_max=0;

    for(x1=0;x1<n;x1++)
        for(y1=0;y1<n;y1++){
            local_max=0;
            x2=x1;
            ymax=n-1;
            while ((x2<n)&&(M[x2][y1]==1)){
                y2=y1;
                while((y2<ymax+1)&&(M[x2][y2]==1)){
                    y2++;
                }
                ymax=y2-1;
                local_max=(x2-x1+1)*(ymax-y1+1);
                if (local_max>max) max=local_max;
                x2++;
            }
        }
    return max;
}
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
int main() {

    struct timespec tp0, tp1;
    double Tn, Fn, x;
    int n=20; // wymiar macierzy
    int **Macierz;
    srand(time(NULL));

    //utworz_MACIERZ(n,&Macierz);
    //utworz_MACIERZ_x(n,&Macierz,0);
    //utworz_MACIERZ_x(n,&Macierz,1);
    
    printf("Alogrytm Naiwny\n");
    for (int n = 20; n <= 50; n++) {
        utworz_MACIERZ(n, &Macierz);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
        x = ALGO_NAIWNY(n, Macierz);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

        // oszacowana funkcja czasu
        Fn = pow(n, 6) + pow(n, 5) + 3 * pow(n, 4) + pow(n, 3) + 
            pow(n, 2) + n + 4;

        Tn = (tp1.tv_sec + tp1.tv_nsec / MLD) - 
            (tp0.tv_sec + tp0.tv_nsec / MLD);  
       
        printf("n: %5d \tczas: %3.10lf \twspolczynnik: %3.5lf\n", n, Tn, Fn/Tn);

        zwolnij_MACIERZ(n, Macierz);
    }

    printf("Algorytm Rekurencyjny\n");
    for (int n = 20; n <= 50; n++) {
        utworz_MACIERZ(n, &Macierz);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
        x = ALGO_REKURENCYJNY(n, Macierz);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

        // oszacowana funkcja czasu
        Fn = 2 * pow(n, 4) * log(n); 

        Tn = (tp1.tv_sec + tp1.tv_nsec / MLD) - 
            (tp0.tv_sec + tp0.tv_nsec / MLD);

        printf("n: %5d \tczas: %3.10lf \twspolczynnik: %3.5lf\n", n, Tn, Fn/Tn);
        
        zwolnij_MACIERZ(n, Macierz);
    }

    printf("Algorytm Dynamiczny\n");
    for (int n = 20; n <= 50; n++) {
        utworz_MACIERZ(n, &Macierz);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
        x = ALGO_DYNAMICZNY(n, Macierz);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

        // oszacowana funkcja czasu
        Fn = 3 * pow(n, 3) + 2 * pow(n, 2) + n + 5;

        Tn = (tp1.tv_sec + tp1.tv_nsec / MLD) - 
            (tp0.tv_sec + tp0.tv_nsec / MLD);

        printf("n: %5d \tczas: %3.10lf \twspolczynnik: %3.5lf\n", n, Tn, Fn/Tn);
        
        zwolnij_MACIERZ(n, Macierz);
    }

    printf("Algorytm Czuly\n");
    for (int n = 20; n <= 300; n++) {
        utworz_MACIERZ(n, &Macierz);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
        x = ALGO_CZULY(n, Macierz);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

        // oszacowana funkcja czasu
        Fn = pow(n, 4) + 5 * pow(n, 3) + 4 * pow(n, 2) + n + 4; 

        Tn = (tp1.tv_sec + tp1.tv_nsec / MLD) - 
            (tp0.tv_sec + tp0.tv_nsec / MLD);

        printf("n: %5d \tczas: %3.10lf \twspolczynnik: %3.5lf\n", n, Tn, Fn/Tn);
        
        zwolnij_MACIERZ(n, Macierz);
    }

   /* 
    wypisz_MACIERZ(n,Macierz);
    printf("\nWynik 1=%d \n",ALGO_NAIWNY(n,Macierz));
    printf("Wynik 2=%d \n",ALGO_REKURENCYJNY(n,Macierz));
    printf("Wynik 3=%d \n",ALGO_DYNAMICZNY(n,Macierz));
    printf("Wynik 4=%d \n",ALGO_CZULY(n,Macierz));
    zwolnij_MACIERZ(n,Macierz);
    */

    return 1;
}

/*
Alogrytm Naiwny
n:    20 	czas: 0.0031617030 	wspolczynnik: 21408849597.82750
n:    21 	czas: 0.0047196530 	wspolczynnik: 19163144409.13347
n:    22 	czas: 0.0054554500 	wspolczynnik: 21858409847.03370
n:    23 	czas: 0.0074406900 	wspolczynnik: 20875009978.91325
n:    24 	czas: 0.0120491040 	wspolczynnik: 16604998678.73993
n:    25 	czas: 0.0157964640 	wspolczynnik: 16148829510.19925
n:    26 	czas: 0.0150712070 	wspolczynnik: 21377608442.37625
n:    27 	czas: 0.0216034920 	wspolczynnik: 18672174017.05243
n:    28 	czas: 0.0235792810 	wspolczynnik: 21246084984.52519
n:    29 	czas: 0.0315120180 	wspolczynnik: 19595113711.85432
n:    30 	czas: 0.0371430970 	wspolczynnik: 20347197596.36630
n:    31 	czas: 0.0441517330 	wspolczynnik: 20813094290.09276
n:    32 	czas: 0.0612630950 	wspolczynnik: 18126342000.84080
n:    33 	czas: 0.0647299310 	wspolczynnik: 20611765954.14569
n:    34 	czas: 0.0752767060 	wspolczynnik: 21179052999.47635
n:    35 	czas: 0.0863542290 	wspolczynnik: 21948357781.06477
n:    36 	czas: 0.1073890850 	wspolczynnik: 20880477303.62912
n:    37 	czas: 0.1186530490 	wspolczynnik: 22256022363.15057
n:    38 	czas: 0.1383494460 	wspolczynnik: 22381609811.43358
n:    39 	czas: 0.1622923230 	wspolczynnik: 22280592816.45750
n:    40 	czas: 0.1847675710 	wspolczynnik: 22764523131.60519
n:    41 	czas: 0.2194482380 	wspolczynnik: 22212565552.70222
n:    42 	czas: 0.2551109770 	wspolczynnik: 22065432182.48112
n:    43 	czas: 0.2789662700 	wspolczynnik: 23223987968.15112
n:    44 	czas: 0.3183409750 	wspolczynnik: 23347800376.62447
n:    45 	czas: 0.3634747990 	wspolczynnik: 23387285301.17435
n:    46 	czas: 0.4135477030 	wspolczynnik: 23440564828.86571
n:    47 	czas: 0.4649963500 	wspolczynnik: 23706219332.68939
n:    48 	czas: 0.5219216630 	wspolczynnik: 23952699254.02579
n:    49 	czas: 0.5974325050 	wspolczynnik: 23669915576.48841
n:    50 	czas: 0.6726587820 	wspolczynnik: 23721354691.24076
Algorytm Rekurencyjny
n:    20 	czas: 0.0201688910 	wspolczynnik: 47530344.01035
n:    21 	czas: 0.0298506140 	wspolczynnik: 39670994.25231
n:    22 	czas: 0.0392262040 	wspolczynnik: 36918955.55093
n:    23 	czas: 0.0478150980 	wspolczynnik: 36701371.47392
n:    24 	czas: 0.0619856840 	wspolczynnik: 34020822.86024
n:    25 	czas: 0.0808442970 	wspolczynnik: 31106049.91937
n:    26 	czas: 0.1001613030 	wspolczynnik: 29729483.92173
n:    27 	czas: 0.1249120080 	wspolczynnik: 28044426.92021
n:    28 	czas: 0.1468986430 	wspolczynnik: 27885342.62234
n:    29 	czas: 0.1843533430 	wspolczynnik: 25837604.27853
n:    30 	czas: 0.2193862240 	wspolczynnik: 25115249.52584
n:    31 	czas: 0.2563428810 	wspolczynnik: 24743104.11666
n:    32 	czas: 0.3082726750 	wspolczynnik: 23577097.71075
n:    33 	czas: 0.3665735850 	wspolczynnik: 22623461.77399
n:    34 	czas: 0.4375754850 	wspolczynnik: 21538695.28602
n:    35 	czas: 0.5196745910 	wspolczynnik: 20533019.22846
n:    36 	czas: 0.6153666000 	wspolczynnik: 19562113.85322
n:    37 	czas: 0.7225775700 	wspolczynnik: 18731391.08395
n:    38 	czas: 0.8495288910 	wspolczynnik: 17856630.73994
n:    39 	czas: 0.9979772150 	wspolczynnik: 16985224.89451
n:    40 	czas: 1.1677271060 	wspolczynnik: 16174209.46043
n:    41 	czas: 1.3567473770 	wspolczynnik: 15468859.26544
n:    42 	czas: 1.5633729030 	wspolczynnik: 14878717.13552
n:    43 	czas: 1.8123874040 	wspolczynnik: 14189896.36361
n:    44 	czas: 2.0980704100 	wspolczynnik: 13520524.34706
n:    45 	czas: 2.4040160280 	wspolczynnik: 12986348.83487
n:    46 	czas: 2.7282077220 	wspolczynnik: 12566912.15579
n:    47 	czas: 3.1118920320 	wspolczynnik: 12074642.63288
n:    48 	czas: 3.5534573720 	wspolczynnik: 11566169.63943
n:    49 	czas: 4.0028262840 	wspolczynnik: 11209864.20822
n:    50 	czas: 4.5065625850 	wspolczynnik: 10850906.12757
Algorytm Dynamiczny
n:    20 	czas: 0.0000176000 	wspolczynnik: 1410511363.09754
n:    21 	czas: 0.0000195120 	wspolczynnik: 1470428454.17165
n:    22 	czas: 0.0000220680 	wspolczynnik: 1492613739.36329
n:    23 	czas: 0.0001091670 	wspolczynnik: 344307345.63284
n:    24 	czas: 0.0001770040 	wspolczynnik: 240971955.43455
n:    25 	czas: 0.0001357980 	wspolczynnik: 354607578.89796
n:    26 	czas: 0.0000395820 	wspolczynnik: 1367060785.22517
n:    27 	czas: 0.0000427710 	wspolczynnik: 1415421664.31654
n:    28 	czas: 0.0000440760 	wspolczynnik: 1530470097.04318
n:    29 	czas: 0.0000485210 	wspolczynnik: 1543311143.73902
n:    30 	czas: 0.0001627990 	wspolczynnik: 508817621.72451
n:    31 	czas: 0.0000590180 	wspolczynnik: 1547510928.82347
n:    32 	czas: 0.0000645290 	wspolczynnik: 1555719134.04663
n:    33 	czas: 0.0000753550 	wspolczynnik: 1460115453.52217
n:    34 	czas: 0.0000814920 	wspolczynnik: 1475764492.22684
n:    35 	czas: 0.0000859010 	wspolczynnik: 1526350100.72396
n:    36 	czas: 0.0000919440 	wspolczynnik: 1550954929.12830
n:    37 	czas: 0.0000969280 	wspolczynnik: 1596432403.35217
n:    38 	czas: 0.0001146280 	wspolczynnik: 1461658582.56290
n:    39 	czas: 0.0001227060 	wspolczynnik: 1475420924.73773
n:    40 	czas: 0.0001234780 	wspolczynnik: 1581212847.64544
n:    41 	czas: 0.0001325250 	wspolczynnik: 1585897000.59058
n:    42 	czas: 0.0001410620 	wspolczynnik: 1600991053.60986
n:    43 	czas: 0.0001562950 	wspolczynnik: 1550062381.99846
n:    44 	czas: 0.0001744820 	wspolczynnik: 1487104687.02941
n:    45 	czas: 0.0001722850 	wspolczynnik: 1610558086.91068
n:    46 	czas: 0.0001861340 	wspolczynnik: 1591815573.75870
n:    47 	czas: 0.0001988720 	wspolczynnik: 1588655014.29194
n:    48 	czas: 0.0003081640 	wspolczynnik: 1091746602.44663
n:    49 	czas: 0.0002516260 	wspolczynnik: 1421963549.07270
n:    50 	czas: 0.0002429270 	wspolczynnik: 1564482334.18520
Algorytm Czuly
n:    20 	czas: 0.0000067840 	wspolczynnik: 29720518868.00375
n:    21 	czas: 0.0000115150 	wspolczynnik: 21066000860.78392
n:    22 	czas: 0.0000138720 	wspolczynnik: 20866349485.93997
n:    23 	czas: 0.0000081970 	wspolczynnik: 41822496036.89756
n:    24 	czas: 0.0000081920 	wspolczynnik: 49222167994.65838
n:    25 	czas: 0.0000111610 	wspolczynnik: 42225517441.10393
n:    26 	czas: 0.0000103460 	wspolczynnik: 52927701509.86592
n:    27 	czas: 0.0000114630 	wspolczynnik: 55203960569.37252
n:    28 	czas: 0.0000113690 	wspolczynnik: 63997185332.99358
n:    29 	czas: 0.0000132460 	wspolczynnik: 62858447825.03615
n:    30 	czas: 0.0000129520 	wspolczynnik: 73242279191.84239
n:    31 	czas: 0.0000140540 	wspolczynnik: 76587092656.05292
n:    32 	czas: 0.0000175850 	wspolczynnik: 69181006532.07355
n:    33 	czas: 0.0000178510 	wspolczynnik: 76746344761.86613
n:    34 	czas: 0.0000166970 	wspolczynnik: 92083488054.44621
n:    35 	czas: 0.0000173190 	wspolczynnik: 99309371203.71655
n:    36 	czas: 0.0000204680 	wspolczynnik: 93713113141.07428
n:    37 	czas: 0.0000203160 	wspolczynnik: 104988334333.45244
n:    38 	czas: 0.0000212980 	wspolczynnik: 111058033617.87540
n:    39 	czas: 0.0000214460 	wspolczynnik: 121988389454.09926
n:    40 	czas: 0.0000231260 	wspolczynnik: 124813802635.07123
n:    41 	czas: 0.0000263320 	wspolczynnik: 120656805419.99652
n:    42 	czas: 0.0000244360 	wspolczynnik: 142790882281.99304
n:    43 	czas: 0.0000281470 	wspolczynnik: 135850321517.26776
n:    44 	czas: 0.0000301830 	wspolczynnik: 138548454428.93073
n:    45 	czas: 0.0000326350 	wspolczynnik: 139862080602.82419
n:    46 	czas: 0.0000331440 	wspolczynnik: 150031679943.64670
n:    47 	czas: 0.0000348590 	wspolczynnik: 155130181575.35388
n:    48 	czas: 0.0000358940 	wspolczynnik: 163555023124.48825
n:    49 	czas: 0.0000400870 	wspolczynnik: 158722353900.00476
n:    50 	czas: 0.0000364360 	wspolczynnik: 188962948758.36102
*/




