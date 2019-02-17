#include <stdio.h>
#include <stdlib.h>




typedef struct STROM{
    int cislo;
    char znamenko;
    struct STROM * LSyn;
    struct STROM * PSyn;
    struct STROM * Otec;
}strom;

typedef struct Prefix{
    char znamenko;
    int cislo;
}prefix;

void ZapisDoLeva();
void ZapisDoPrava();
void UkladaniDoStromu();
void vypisL();
void vypisR();

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

void UkladaniDoStromu(prefix * vstup, strom * hlava, int konec, int index){
      if(index + 1 <= konec){
        if(hlava->znamenko == NULL){
            hlava->znamenko = vstup->znamenko;
        }
        int a = index + 1;
        ZapisDoLeva(hlava, vstup, a);
        }
    return;
}
void vypisL(strom * hlava){
    if(hlava->cislo == NULL){
        vypisL(hlava->LSyn);
        printf("%c", hlava->znamenko);
        vypisR(hlava->PSyn);
    }
    else{
       printf(" ( ");
       printf(" %d ", hlava->cislo);
    }

}

void vypisR(strom * hlava){
    if(hlava->cislo == NULL){
       vypisL(hlava->LSyn);
       printf("%c", hlava->znamenko);
       vypisR(hlava->PSyn);
    }
    else{
        printf(" %d ", hlava->cislo);
        printf(" ) ");
    }
}

void infix(strom * hlava){
    vypisL(hlava->LSyn);
    printf(" %c ", hlava->znamenko);
    vypisR(hlava->PSyn);
    printf(")");
}

int main()
{
    char vstupniData[] = {'-','+','6','5','/','6','-','6','3'};



    int konec = sizeof(vstupniData)/sizeof(char);
    prefix * VstupniData;
    VstupniData = poleDoPrefix(vstupniData, konec);
    int index = 0;
    strom * hlava = malloc(sizeof(strom));
    hlava->cislo = NULL;
    hlava->LSyn = NULL;
    hlava->PSyn = NULL;
    hlava->znamenko = NULL;
    hlava->Otec = NULL;
    UkladaniDoStromu(VstupniData, hlava, konec, index);
    infix(hlava);

    return 0;
}
