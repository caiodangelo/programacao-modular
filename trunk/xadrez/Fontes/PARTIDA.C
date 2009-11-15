/***************************************************************************
*  $MCI Módulo de implementação: PAR Realizador de partidas de Xadrez
*
*  Arquivo gerado:              PARTIDA.C
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 Programação Modular
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo , Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   13/nov/2009 Início desenvolvimento
*	  1		  cev	19/nov/2009 Entrega do trabalho
*
***************************************************************************/
#include "GERENCIADOR.H"
#include "MOVIMENTADOR.H"
#include "PARTIDA.H"
#include <stdio.h>
#include <stdlib.h>

#define BRANCAS 0
#define PRETAS 1
#define NOVA 0
#define ANTIGA 1
#define INVALIDO 0
#define OK 1



/***** Protótipos das funções encapsuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: PAR  &Adicionar Pecas Ao Grafo
*  ****/

void PAR_IniciarPartida(){

	char resposta;
	int Validade = INVALIDO;

	while ( Validade != OK){

		printf("\n Bem-Vindo ao Jogo de Xadrez do grupo CEV!! \n\n Para iniciar nova partida, digite ´N´\n Para continuar uma partida antiga, digite ´A´\n");

		scanf("%c", &resposta);

		if( resposta == 'N' ){
			Validade = OK;
		}/*if*/
		if ( resposta == 'A' ){
			Validade = OK;
		}/*if*/
	}/* while*/
	printf("Capturado\n");


	//constroi tabuleiro e grafo à partir do tipo

	//obtem vez

	//chama jogar xadrez

	}/*
PAR_tpCondRet JogaXadrez(){
	//print vez

	//chama realizar movimento while ...

	//alterar vez

	//Verificar Xeque-mate, se estiver jogo acabou - sugere nova partida

	//Senão continua no loop

	}
PAR_tpCondRet RealizaMovimento(){
	//obtem vez
	//se for salvar salva
	//captura movimento, verifica cor e vez, verifica validade/ realiza movimento

	}*/