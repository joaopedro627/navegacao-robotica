#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "caminho.h"

#define MAX_COMANDOS 500

int main() {
    char buffer_sequencia[MAX_COMANDOS];
    char caractere;
    int i = 0;
    
    Caminho *caminho_programa = NULL;
    
    printf("=== Simulador de Navegacao Robotica ===\n");

    // Coleta das direcoes com protecao de buffer overflow
    while (i < MAX_COMANDOS - 1) {
        printf("\nDigite a direcao do comando (N, S, L, O) ou '0' para sair: ");
        
        // O espaco antes do %c consome automaticamente quebras de linha e espacos do buffer
        scanf(" %c", &caractere);
        caractere = toupper(caractere);
        
        if (caractere == '0') {
            printf("\n ======= Finalizando Input ======= \n");
            break;
        }
        
        if (caractere != 'S' && caractere != 'N' && caractere != 'O' && caractere != 'L') {
            printf("ERRO: Direcao '%c' invalida! Tente novamente.\n", caractere);
            continue; // Pula para a proxima iteracao sem incrementar o 'i'
        }
        
        buffer_sequencia[i] = caractere;
        i++;
    }
    
    buffer_sequencia[i] = '\0'; // Finaliza a string de forma segura

    // Seguranca: Verifica se o usuario digitou pelo menos um comando
    if (i == 0) {
        printf("\nNenhum comando registrado. Encerrando programa.\n");
        return 0;
    }
    
    int posicaoX, posicaoY;
    
    printf("\nDigite a posicao X inicial: ");
    scanf("%d", &posicaoX);

    printf("Digite a posicao Y inicial: ");
    scanf("%d", &posicaoY);

    // Inicializa a estrutura utilizando a string montada pelo usuario
    caminho_programa = InicializarCaminho(buffer_sequencia, posicaoX, posicaoY);
    
    // Programacao Defensiva: Valida se a alocacao/inicializacao funcionou
    if (caminho_programa == NULL) {
        printf("\nERRO FATAL: Falha ao inicializar o caminho.\n");
        return 1;
    }
    
    printf("\n------------------------------------");
    printf("\nRelatorio de Navegacao\n");
    printf("------------------------------------\n");
    
    // Historico de posicoes
    Posicao *historico_posicoes = HistoricoPosicoes(caminho_programa);
    printf("Historico: ");
    
    Posicao *posicao_atual = historico_posicoes;
    while (posicao_atual != NULL) {
        printf("(%d, %d) ", posicao_atual->X, posicao_atual->Y);
        posicao_atual = posicao_atual->Proximo;
    }
    
    // Posicao Final
    Posicao *fim_robo = DeterminarFim(caminho_programa);
    if (fim_robo != NULL) {
        printf("\nPosicao final: (%d, %d)", fim_robo->X, fim_robo->Y);
    }
    
    // Metricas
    printf("\nNumero de instrucoes: %d", ContarInstrucoes(caminho_programa));
    printf("\nDistancia geometrica: %.2f", CalcularDistanciaGeometrica(caminho_programa));
    printf("\nDistancia de Manhattan: %d\n", CalcularDistanciaManhattan(caminho_programa));
    printf("------------------------------------\n");
    
    // Libera a memoria dinamica para evitar memory leaks
    DestruirCaminho(caminho_programa);
    
    return 0;
}