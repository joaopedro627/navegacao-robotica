#include "caminho.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

Caminho * InicializarCaminho(const char *Sequencia, int xInicial, int yInicial){
	
	Comando *comandos_inicio = NULL;
	Comando *comandos_final = NULL;
	
	int k = 0;//verificacao precoce em caso de inputs errados "LLLLLPOOOO"
	while(Sequencia[k] != '\0'){
		char d = toupper(Sequencia[k]);
		if(d != 'N' && d != 'S' && d != 'L' && d != 'O') {
			return NULL;
		}
		k++;
	}
	
	int i = 0;
	while(Sequencia[i] != '\0'){
		//logica do encadeamento das sequencias de comandos
        
        char dir = toupper(Sequencia[i]);
        
		Comando *novo = (Comando*)malloc(sizeof(Comando));
		novo->Proximo = NULL;
		novo->Direcao = dir;
		
		if(comandos_inicio == NULL){
			comandos_inicio = novo;
			comandos_final = novo;
		}
		else{
			comandos_final->Proximo = novo;
			comandos_final = novo;
		}
		
		i++;
	}
	
	//incializando o ponteiro das posicoes
	Posicao *posicao_inicial = (Posicao*)malloc(sizeof(Posicao));
	posicao_inicial->X = xInicial;
	posicao_inicial->Y = yInicial;
	posicao_inicial->Proximo = NULL;
	
	//inicializando caminho
	Caminho *temp =	(Caminho*)malloc(sizeof(Caminho));
	temp->Inicio = posicao_inicial;
	temp->Fim = NULL;
	temp->Historico = NULL;
	temp->Instrucoes = comandos_inicio;
	temp->N = 0;
	
	//logica de locomocao do robo
	Posicao *historico_posicoes = (Posicao*)malloc(sizeof(Posicao));
	Posicao *final_historico_posicoes = NULL;

	Comando *comando_atual = comandos_inicio;
	
	int valor_posicaoX = 0, valor_posicaoY = 0;
	
	historico_posicoes->X = xInicial;
	historico_posicoes->Y = yInicial;
	historico_posicoes->Proximo = NULL;
	final_historico_posicoes = historico_posicoes;
	
	while(comando_atual!=NULL){
		valor_posicaoX = 0;
		valor_posicaoY = 0;
		
		switch(comando_atual->Direcao){
			case 'N': valor_posicaoY = 1;
				 break;
			case 'S': valor_posicaoY = -1;
				break;
			case 'L': valor_posicaoX = 1;
				break;
			case 'O': valor_posicaoX = -1;
				break;
		}
		
		Posicao *nova = (Posicao*)malloc(sizeof(Posicao));
		
		nova->Proximo = NULL;
		nova->X = final_historico_posicoes->X + valor_posicaoX;
		nova->Y = final_historico_posicoes->Y + valor_posicaoY;
	
		final_historico_posicoes->Proximo = nova;
		final_historico_posicoes = nova;
		
		temp->N++;
		
		comando_atual = comando_atual->Proximo;//logica para pular entre nos
	}//final do while
	
	temp->Historico = historico_posicoes;
	temp->Fim = final_historico_posicoes;
	
	return temp;
}//final da função inicializar caminho

void DestruirCaminho(Caminho * C){
	
	if(C == NULL)//caso noa exista caminho
		return;
	
	Posicao *posicao_temp;
	Posicao *posicao_atual = C->Historico;//passa pelo final tambem
	
	while(posicao_atual != NULL){//logica liberar memoria do ponteiro das posicoes
		posicao_temp = posicao_atual->Proximo;
		free(posicao_atual);
		posicao_atual = posicao_temp;
	}
	
	if (C->Inicio != NULL){//libera o ponteiro do inicio
		free(C->Inicio);
	}
	
	Comando *comando_temp;
	Comando *comando_atual = C->Instrucoes;
	
	while(comando_atual != NULL){//logica liberar memoria do ponteiro dos comandos
		comando_temp = comando_atual->Proximo;
		free(comando_atual);
		comando_atual = comando_temp;
	}
	
	free(C);
}

Posicao * DeterminarFim(Caminho * C){
	if(C == NULL)
		return NULL;
	
	return C->Fim;
}

Posicao * HistoricoPosicoes(Caminho * C){
	if(C == NULL)
		return NULL;
	
	return C->Historico;
}

int CalcularDistanciaTotal(Caminho * C){
	if(C == NULL){
		return -1;
	}
	
	//A formula para calculo da Distancia total e o mesmo que o numero de instrucoes, por isso e desnecessario a implementacao
	return C->N;
}

double CalcularDistanciaGeometrica(Caminho * C){
	
	if(C == NULL){
		return -1.0;
	}
	
	Posicao *final = C->Fim;
	Posicao *inicio = C->Inicio;
	
	int x_inicio = inicio->X, x_final = final->X, y_inicio = inicio->Y, y_final = final->Y;
	
	double distanciageometrica;
	distanciageometrica = sqrt(pow((x_inicio - x_final), 2) + pow(y_inicio - y_final, 2));
	
	return distanciageometrica;
}

int CalcularDistanciaManhattan(Caminho * C){
	
	if(C == NULL)
		return -1;
	
	Posicao *final = C->Fim;
	Posicao *inicio = C->Inicio;
	
	int x_inicio = inicio->X, x_final = final->X, y_inicio = inicio->Y, y_final = final->Y;
	int distanciamanhattan = abs((x_inicio - x_final)) + abs((y_inicio - y_final));
	
	return distanciamanhattan;
}

int ContarInstrucoes(Caminho * C){
	if(C == NULL) //mesma coisa da funcao de distanciaPercorrida
		return -1;
		
	return C->N;
}