#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMVET 25000

void imprimir(int *v, int tam){
    for(int i = 0; i < tam; i++)
        printf("%4d ", v[i]);
}

//FUNCAO PARA GERAR NUMEROS ALEATORIOS DE 1 A 10.000
int GerarNumerosAleatorios(int *v, int tam){
    printf("\n\tVETOR PRENCHIDO COM NUMEROS ALEATORIOS!\n");
    srand(time(NULL));
    for(int i = 0; i < tam; i++)
        v[i] = 1 + rand() % TAMVET;

    printf("VETOR: \n");
    //imprimir(v, tam);
    return 1;
}

//METODO DE ORDENAÇÃO BUBBLE SORT
void BubbleSort(int *v, int tam){
    int i, j;
    for(i = 0; i < tam - 1; i++){
        for(j = 0; j < tam - i - 1; j++){
            if(v[j] > v[j + 1]){
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

//METODO DE ORDENACAO QUICKSORT
int particiona(int *v, int inicio, int fim){
    int pivo = v[fim];
    int i = inicio - 1;
    for(int j = inicio; j < fim; j++){
        if(v[j] <= pivo){
            i++;
            int aux;
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
    int aux = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = aux;

    return i + 1;
}

void QuickSort(int *v, int inicio, int fim){
    if(inicio < fim){
        int pos = particiona(v, inicio, fim);
        QuickSort(v, inicio, pos - 1);
        QuickSort(v, pos + 1, fim);
    }
}

//METODO DE ORDENACAO SELECTION SORT
void SelectionSort(int *v, int tam){
    for(int i = 0; i < tam - 1; i++){
        int minimo = i;
        for(int j = i + 1; j < tam; j++){
            if(v[j] < v[minimo]){
                minimo = j;
            }
        }
        int aux = v[minimo];
        v[minimo] = v[i];
        v[i] = aux;
    }
}
//METODO DE ORDENACAO INSERTIONSORT

void InsertionSort(int *v, int tam) {
    int i, j, chave;
    for(i = 1; i < tam; i++) {
        chave = v[i];
        j = i - 1;

        while(j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

void QuickSortCorriqe(int *v, int tam) {
    QuickSort(v, 0, tam - 1);
}

double MedirTempoDeOrdenacao(int *v, int tam, void (*metodo_ordenacao)(int*, int)){

    int *vetor = calloc(tam, sizeof(int));
    clock_t Tempoinicial, Tempofinal;

    if(vetor == NULL){
        printf("Erro ao Alocar Memoria em MedirTempoDeOrdenacao\n");
        return 0;
    }

    memcpy(vetor, v, tam * sizeof(int));

    Tempoinicial = clock();
    metodo_ordenacao(vetor, tam);
    Tempofinal = clock();
    double tempo_gasto = (double)(Tempofinal - Tempoinicial) / CLOCKS_PER_SEC;

    free(vetor);

    return tempo_gasto;

}

void imprimirOrd(double *v, char **nomes){
        printf("\n\t----------TEMPO GASTO ----------\n");
    for(int i = 0; i < 4; i++)
        printf("\n\t%s = %lf SEGUNDOS\n", nomes[i], v[i]);

}

int main() {
    double vettempo[4];
    int opcao, valorFIBO, cont = 0;
    int vetor[TAMVET] = {0}; //VETOR COM 1000 ELEMENTOS

    void (*metodos[])(int*, int) = { BubbleSort, QuickSortCorriqe, SelectionSort, InsertionSort };
    char *nomes[] = { "BUBBLE SORT", "QUICKSORT", "SELECTION SORT", "INSERTION SORT" };

    do {
        //MEN
        printf("\n\t--------------MENU--------------\n");
        printf("\n\t1. GERAR NUMEROS ALEATORIOS");
        printf("\n\t2. COMPARAR METODOS DE ORDENACAO");
        printf("\n\t3. SAIR\n");

        printf("\n\tESCOLHA UMA OPCAO: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            	cont = GerarNumerosAleatorios(vetor, TAMVET);
                break;
            case 2:
                if(cont != 1){
                    printf("\n\tVETOR NAO FOI GERADO\n");
                    break;
                }
                for(int i = 0; i < 4; i++)
                    vettempo[i] = MedirTempoDeOrdenacao(vetor, TAMVET, metodos[i]);
                imprimirOrd(vettempo, nomes);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 3);

   return 0;

}
