#include <stdio.h>
#include <stdlib.h>



// Sturktura stromu, obsahuje cislo, znamenko, ukazatel na sv�ho otce, ukazatel na lev�ho a prav�ho syna
typedef struct STROM{
    int cislo;
    char znamenko;
    struct STROM * LSyn;
    struct STROM * PSyn;
    struct STROM * Otec;
}strom;
// struktura prefix je pomocnou strukturou, kter� slou�� k lep�� editaci vstupu.
typedef struct Prefix{
    char znamenko;
    int cislo;
}prefix;

void ZapisDoLeva();
void ZapisDoPrava();
void UkladaniDoStromu();
void vypisL();
void vypisR();

// p�ev�d� vstup, kter� m� podobu pole znak� na pole datov�ho typu prefix. Funkce vrac� ukazatel na pole typu prefix
prefix * poleDoPrefix(char * pole , int k){
        int i = 0;
        prefix * vstup = malloc(sizeof(prefix)*k);
        for(i = 0; i < k; i++){
            if( *(pole + i) >= '0' && *(pole + i) <= '9'){
                (vstup + i)->cislo = *(pole + i) - 48;
                (vstup + i)->znamenko = NULL;
            }
            else{
                (vstup + i)->znamenko = *(pole + i);
                (vstup + i)->cislo = NULL;
            }
        }

        return vstup;
    }


//pomocn� funkce ZapisDoLeva, tak� se zde jedn� o ��ste�nou rekurzi. Stav� pravou ��st stromu.
void ZapisDoPrava(strom * Otec, prefix * vstup, int index){
    strom * syn = malloc(sizeof(strom));
    syn->cislo = NULL;
    syn->LSyn = NULL;
    syn->Otec = NULL;
    syn->PSyn = NULL;
    int a = index;
    if(vstup[a].znamenko != NULL && vstup[a].cislo == NULL)
    {
        Otec->PSyn = syn;
        syn->Otec = Otec;
        syn->znamenko = (vstup + a)->znamenko;
        a = a + 1;
        ZapisDoLeva(syn, vstup, a);
        a = a - 1;
    }
    if((vstup + a)->znamenko == NULL && (vstup + a)->cislo != NULL)
    {
        syn->cislo = (vstup + a)->cislo;
        Otec->PSyn = syn;
        syn->Otec = Otec;
        a = a + 1;
        ZapisDoPrava(Otec->Otec, vstup ,a);
        a = a - 1;
    }
    return;
}

// zde se jedn� o ��ste�nou rekurzi, kter� byu��v� toho �e se lze vracet na sv�ho otce. Rekurzivn� stav� strom.
void ZapisDoLeva(strom * Otec, prefix * vstup, int index){
    strom * syn = malloc(sizeof(strom));
    syn->cislo = NULL;
    syn->LSyn = NULL;
    syn->Otec = NULL;
    syn->PSyn = NULL;
    syn->znamenko = NULL;
    int a = index;
        if((vstup + a)->znamenko != NULL && (vstup + a)->cislo == NULL)
        {
            Otec->LSyn = syn;
            syn->Otec = Otec;
            syn->znamenko = (vstup + a)->znamenko;
            a = a + 1;
            ZapisDoLeva(syn, vstup, a);
            a = a - 1;
        }
        if((vstup + a)->znamenko == NULL && (vstup + a)->cislo != NULL)
        {
            syn->cislo = (vstup + a)->cislo;
            Otec->LSyn = syn;
            syn->Otec = Otec;
            a = a + 1;
            ZapisDoPrava(syn->Otec, vstup ,a);
        }
    return;

}
//konroluje jestli neni zadano prazdne pole. A nasledn� inicializuje stavbu stromu.
void UkladaniDoStromu(prefix * vstup, strom * hlava, int konec){

      if(konec != 0){
        hlava->znamenko = vstup->znamenko;
        ZapisDoLeva(hlava, vstup, 1);
        }
    return;
}
//vypisuje rekurzivn� lev� a prav� syny
void vypisL(strom * hlava){
    if(hlava->cislo == NULL){
        printf(" ( ");
        vypisL(hlava->LSyn);
        printf("%c", hlava->znamenko);
        vypisR(hlava->PSyn);
    }
    else{
       printf(" ( ");
       printf(" %d ", hlava->cislo);
    }

}
//vypisuje rekurzivn� lev� syny stromu
void vypisR(strom * hlava){
    if(hlava->cislo == NULL){
       vypisL(hlava->LSyn);
       printf("%c", hlava->znamenko);
       vypisR(hlava->PSyn);
       printf(" ) ");
    }
    else{
        printf(" %d ", hlava->cislo);
        printf(" ) ");
    }
}
//inicializuje vypsani infixu ze stromu
void infix(strom * hlava){
    vypisL(hlava->LSyn);
    printf(" %c ", hlava->znamenko);
    vypisR(hlava->PSyn);
}

int main()
{

    /* Editace vstupu prob�h� zde. Sta�� do slo�en�ch z�vorek zadat vstup v p��slu�n�m tvaru.*/
    char vstupniData[] = {'-','+','6','5','/','6','-','6','3'};



    int konec = sizeof(vstupniData)/sizeof(char);
    prefix * VstupniData;
    VstupniData = poleDoPrefix(vstupniData, konec);
    strom * hlava = malloc(sizeof(strom));
    hlava->cislo = NULL;
    hlava->LSyn = NULL;
    hlava->PSyn = NULL;
    hlava->znamenko = NULL;
    hlava->Otec = NULL;
    UkladaniDoStromu(VstupniData, hlava, konec);
    infix(hlava);

    return 0;
}
