#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct nodo 
{
    double normal;
    double derivda;
    struct nodo * prox;
} nodo ;

nodo * criar_consta(double num)
{
    nodo * novo = malloc(sizeof(nodo));

    novo->normal=num;
    novo->derivda=0;
    novo->prox=NULL;
    
    return novo;
}

nodo * criar_var(double num)
{
    nodo * novo = malloc(sizeof(nodo));

    novo->normal=num;
    novo->derivda=1;
    novo->prox=NULL;
    
    return novo;
}

nodo *push(nodo *antigo, nodo *novo)
{
    if (novo == NULL) 
    {
        printf("novo é NULL\n");
        return antigo;
    }

    if (antigo == NULL)
        return novo;
    
    novo->prox = antigo;

    return novo;
}
int fazer_switch(char * letra)
{
    if (strcmp(letra, "x")==0)
        return 0;
    if ((strcmp(letra, "+")==0)||(strcmp(letra, "-")==0)||(strcmp(letra, "*")==0)||(strcmp(letra, "/")==0)||(strcmp(letra, "^")==0))    
        return 2;
    return 1;    
}

nodo * remo (nodo * pilha)
{
    nodo * aux;
    if (pilha==NULL)
        return pilha;
    aux = pilha->prox;
    free(pilha);
    return aux;
}

nodo * opera(nodo * lista, char * op, double n)
{
    nodo * auxliar;

    if (strcmp(op, "+") == 0)
    {
        (lista->prox)->normal=((lista->prox)->normal)+(lista->normal);
        (lista->prox)->derivda=((lista->prox)->derivda)+(lista->derivda);
        auxliar=remo(lista);
        return auxliar;
    }
    if (strcmp(op, "-") == 0)
    {
        (lista->prox)->normal=((lista->prox)->normal)-(lista->normal);
        (lista->prox)->derivda=((lista->prox)->derivda)-(lista->derivda);
        auxliar=remo(lista);
        return auxliar;
    }
    if (strcmp(op, "*") == 0)
    {
        (lista->prox)->derivda = ((lista->derivda * lista->prox->normal)+(lista->normal * lista->prox->derivda));
        (lista->prox)->normal=(lista->normal*(lista->prox)->normal);
        auxliar=remo(lista);
        return auxliar;
    }
    if (strcmp(op, "/") == 0)
    {
        double fl=lista->prox->derivda, gl=lista->derivda, g=lista->normal, f=lista->prox->normal;
        if ((fl)&&(f)&&(g)&&(gl))
        {
            lista->prox->derivda=(((g*fl)-(f*gl))/(pow(g,2)));
        }
        else
            {
            if (((g)==0)||(fl==0))
                lista->prox->derivda=(((-1)*(f*gl))/(pow(g,2)));
            else
                lista->prox->derivda=(((g*fl)/(pow(g,2))));
            }

        if (lista->prox->normal)
            lista->prox->normal=(lista->prox->normal/(lista->normal));
        else
            lista->prox->normal=0;
        auxliar=remo(lista);
        return auxliar;
    }
    if (strcmp(op, "^") == 0)
    {
        
        (lista->prox)->derivda=((lista->normal)*pow(lista->prox->normal, lista->normal-1)*(lista->prox->derivda));
        (lista->prox)->normal=pow(lista->prox->normal, lista->normal);
        auxliar = remo(lista);
        return auxliar;
    }
    printf("asdadad");
    printf("ERRO %s", op);
    free(lista);
    exit(1);
}

nodo * criar_lista (nodo * pilha, char * fun, double n)
{
    nodo * aux, * orig;
    orig=pilha;

        switch (fazer_switch(fun))
        {
        case 0:
            aux = criar_var(n);
            aux->prox=orig;
            orig=aux;
            break;

        case 1:
            aux = criar_consta(atof(fun));
            aux->prox=orig;
            orig=aux;
            break;

        case 2:
            orig = opera(orig, fun, n);
            break;

        }
    return orig;

}


void liberar(nodo * lista)
{
    nodo * aux = lista;
    while (lista!=NULL)
    {
        aux = lista->prox; 
        free(lista);
        lista = aux;
    }
    return;
}

void impr(nodo * pilha)
{
    while (pilha!=NULL)
    {
        printf("%.5f - %.5f |", pilha->normal, pilha->derivda);
        pilha=pilha->prox;
    }
    printf("\n");
    return;
}

int main ()
{   
    nodo * pilha;
    char fun[256];
    char * token;
    double n;

    fgets(fun, 256, stdin);
    scanf("%lf", &n);

    pilha=criar_consta(0);

    token = strtok(fun," ");

    while (token!=NULL)
    {
        //printf("%s\n", token);
        token[strcspn(token, "\n")] = 0;
        pilha = criar_lista(pilha, token, n);
        //impr(pilha);
        token = strtok(NULL," ");
    }
    printf("%.5f\n%.5f\n", pilha->normal, pilha->derivda);
    //printf("\n\n");
    //impr(pilha);
    liberar(pilha);

    return 0;
}
