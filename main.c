#include <stdio.h>
#include <stdlib.h>



// Sturktura stromu, obsahuje cislo, znamenko, ukazatel na svého otce, ukazatel na levého a pravého syna
typedef struct STROM{
    int cislo;
    char znamenko;
    struct STROM * LSyn;
    struct STROM * PSyn;
    struct STROM * Otec;
}strom;
// struktura prefix je pomocnou strukturou, která slouží k lepší editaci vstupu.
typedef struct Prefix{
    char znamenko;
    int cislo;
}prefix;

void ZapisDoLeva();
void ZapisDoPrava();
void UkladaniDoStromu();
void vypisL();
void vypisR();

// pøevádí vstup, který má podobu pole znakù na pole datového typu prefix. Funkce vrací ukazatel na pole typu prefix
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


//pomocná funkce ZapisDoLeva, také se zde jedná o èásteènou rekurzi. Staví pravou èást stromu.
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

// zde se jedná o èásteènou rekurzi, která byužívá toho že se lze vracet na svého otce. Rekurzivnì staví strom.
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
//konroluje jestli neni zadano prazdne pole. A naslednì inicializuje stavbu stromu.
void UkladaniDoStromu(prefix * vstup, strom * hlava, int konec){

      if(konec != 0){
        hlava->znamenko = vstup->znamenko;
        ZapisDoLeva(hlava, vstup, 1);
        }
    return;
}
//vypisuje rekurzivnì levé a pravé syny
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
//vypisuje rekurzivnì levé syny stromu
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

    /* Editace vstupu probíhá zde. Staèí do složených závorek zadat vstup v pøíslušném tvaru.*/
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
