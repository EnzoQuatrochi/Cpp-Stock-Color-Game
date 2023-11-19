// Enzo Cinto Quatrochi - 23015904
// Alex Chaves Insel - 21008278

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

#define TAM 6

typedef int stack_element;

#include "stack.h"

typedef struct tubo {
    int numero_elementos;
    Stack pilha;
} Tubo;

void inicializar(Tubo T[]){

    for(int a = 0; a < TAM; ++a){

        initStack(T[a].pilha);
        T[a].numero_elementos = 0;
    }
}

int numeroAleatorio(int contagem[]){

    int numeroAleatorio;

    do {
        numeroAleatorio = rand() % 5 + 1; 
    } while (contagem[numeroAleatorio - 1] >= 5); 

    contagem[numeroAleatorio - 1]++; 

    return numeroAleatorio;
}

void distribuir(Tubo T[]){

    int contagem[5] = {0};  

    for(int c = 0; c < TAM; ++c){

        initStack(T[c].pilha);

        if(c > 0){

            for(int a = 0; a < 5; ++a){

                push(T[c].pilha, numeroAleatorio(contagem));  
            }

            T[c].numero_elementos = 5; 
        }
    }
}

int validarFim(Tubo T[]){

    int pilhaVazia = 0;
    int numerosIguais = 0;

    for(int i = 0; i < TAM; ++i){

        if(T[i].numero_elementos == 0){

            pilhaVazia++;
            numerosIguais += 5;  
        }

        int primeiroElemento = T[i].pilha.local[0];

        for(int j = 1; j < T[i].numero_elementos; ++j){

            if(T[i].pilha.local[j] != primeiroElemento){

                return 1; 
            }
            else{

                numerosIguais++;
            }
        }
    }

    if(pilhaVazia == 1 && numerosIguais == 25){

        return 0;
    }

    return 1; 
}

void mudaCor(int cor){

    HANDLE Saida;
    Saida = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Saida, cor);
}

void printaCor(int I){

    int cor[5] = {2, 4, 6, 7, 5};

    mudaCor(cor[I - 1]);  

    cout << '0';

    mudaCor(15);  
}

void mostrar(Tubo T[]){

    cout << "\n\n\n";
    cout << setw(27) << "TUBOS";
    cout << "\n\n";
    cout << "_________________________________________________" << endl;
    cout << "|       |       |       |       |       |       |" << endl;
    cout << "|   1   |   2   |   3   |   4   |   5   |   6   |" << endl;
    cout << "|_______|_______|_______|_______|_______|_______|" << endl;

    for(int i = 5; i >= 0; --i){

        for(int a = 0; a < TAM; ++a){

            int indice = T[a].numero_elementos - i - 1;
            
            cout << "|   ";

            if(indice >= 0){

                printaCor(T[a].pilha.local[indice]); 
            }
            else{

                cout << " ";
            }

            cout << "   ";
        }

        cout << "|" << endl;
    }

    cout << "|_______|_______|_______|_______|_______|_______|" << endl;
}

int validar(Tubo T[], int origem, int destino){

    if(T[origem - 1].numero_elementos == 0){

        return 1;
    }

    if(T[destino - 1].numero_elementos == 5){

        cout << "\nPilha de destino cheia. Movimento inválido.";
        mostrar(T);

        return 1;
    }

    return 0;
}

int jogada(Tubo T[]){

    int origem, destino;
    int valido;

    do {
        cout << "\n        |  Digite -1 caso queira parar  |" << endl;

        do{
            cout << "\n\nDigite o tubo de origem (1 a 6): ";
            cin >> origem;            
        }while(origem < -2 || origem > 6);

        if(origem == -1){

            cout << "\nEncerrando o programa.";
            exit(0);
        }

        do{
            cout << "\nDigite o tubo de destino (1 a 6): ";
            cin >> destino;
        }while(destino < -2 || destino > 6);

        if(destino == -1){

            cout << "\nEncerrando o programa.";
            exit(0);
        }

        cout << "\n_________________________________________________";

        valido = validar(T, origem, destino);

        if(valido == 0){

            int valorTopoOrigem = T[origem - 1].pilha.local[0]; 

            for(int i = 0; i < T[origem - 1].numero_elementos - 1; i++){

                T[origem - 1].pilha.local[i] = T[origem - 1].pilha.local[i + 1];
            }

            T[origem - 1].numero_elementos--;

            for(int i = T[destino - 1].numero_elementos; i > 0; i--){

                T[destino - 1].pilha.local[i] = T[destino - 1].pilha.local[i - 1];
            }

            T[destino - 1].pilha.local[0] = valorTopoOrigem;
            T[destino - 1].numero_elementos++;

            int jogoVencido = 0;

        }
        else{

            cout << "\n   Movimento Inválido. Por favor, Tente Novamente" << endl;
        }

        int fim = validarFim(T);

        if(fim == 0){

            return 0;
        }

    }while(origem != -1 && destino != -1 && (origem < 1 || origem > 6 || destino < 1 || destino > 6));

    return 1;
}

int main(){

    srand(static_cast<unsigned int>(time(nullptr)));

    Tubo T[TAM];

    int repetir = 1, jogoVencido;

    do {
        inicializar(T);
        distribuir(T);

        do {
            mostrar(T);
            jogoVencido = jogada(T);

            if(jogoVencido == 0){
                break;
            }
        }while(jogoVencido);

        cout << "\n" << endl;
        cout << "\n\n              PARABÉNS! VOCÊ VENCEU!";

        mostrar(T);

        cout << "\nDeseja jogar Novamente? [1 = Sim / 2 = Não]: ";
        cin >> repetir;

    }while(repetir == 1);

    cout << "\nFim do Jogo... Encerrando o programa.";

    return 0;
}