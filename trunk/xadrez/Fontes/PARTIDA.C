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
#include "GRAFO.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BRANCAS 0
#define PRETAS 1
#define NOVA 0
#define ANTIGA 1
#define INVALIDO 0
#define OK 1



/***** Protótipos das funções encapsuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

GRA_tppGrafo pGrafo;

/***************************************************************************
*
*  Função: PAR  &Adicionar Pecas Ao Grafo
*  ****/

void PAR_IniciarPartida(){

	char resposta, cCor;
	int Validade = INVALIDO;
	int ControleJogo = 1;
	GER_tpCondRet CondRetGerenciador;
	GRA_tpCondRet CondRetGrafo;
	GER_tpCorPeca Cor;
	char * Disposicao;

	int ErroNaJogada = 0 ;
	char ColunaOrigem = '!' ;
	char ColunaDestino = '@' ;
	int LinhaOrigem = -1 ;
	int LinhaDestino = -2 ;
	MOV_tpCondRet CondRetMovimentador;
	int NumLidos = -1 ;

	while ( Validade != OK){

		printf("\n Bem-Vindo ao Jogo de Xadrez do grupo CEV!! \n\n Para iniciar nova partida, digite |N|\n Para continuar uma partida antiga, digite |A|\n");

		scanf("%c", &resposta);

		if( resposta == 'N' ){
			Validade = OK;
			Disposicao = "..\\Definicao\\DEFAULT.TXT";
		}/*if*/
		if ( resposta == 'A' ){
			Validade = OK;
			Disposicao = "..\\Definicao\\DISPOSICAO.TXT";
		}/*if*/
	}/* while*/

	CondRetGerenciador = GER_InicializarTabuleiro ();

	if( CondRetGerenciador != GER_CondRetOK ){
		printf("Erro ao inicializar tabuleiro\n");
		return;

		}/* if */

	CondRetGerenciador = GER_PreencherTabuleiro ( Disposicao );

	if( CondRetGerenciador != GER_CondRetOK ){
		printf("Erro ao preencher tabuleiro\n");
		return;

		}/* if */	

	while( ControleJogo == 1 ){

	GER_ImprimirTabuleiro();

	/* Cria o grafo à partir do tabuleiro */
	CondRetMovimentador = MOV_AdicionarPecasAoGrafo ( &pGrafo ); 
	CondRetMovimentador = MOV_GeraMovimentacoes ( &pGrafo );

	Cor = GER_ObterCorDaVez();

	if( Cor == GER_CorBranca ){

		printf("Vez das Brancas. Entre com a jogada:\n");

		}
	else if( Cor == GER_CorPreta ){

		printf("Vez das Pretas. Entre com a jogada:\n");

		}/* else if */
	else{
		printf("Erro ao obter cor da peca\n");
		return;

		}/* else */

		ErroNaJogada = 0 ;
			NumLidos = scanf("%c%d %c%d" , &ColunaOrigem , &LinhaOrigem , &ColunaDestino , &LinhaDestino ) ;
			if ( NumLidos != 5 )
			{
				if ( ( NumLidos == 1 ) && ( ColunaOrigem == 'S' ) )
				{
					Disposicao = "..\\Definicao\\DISPOSICAO.TXT";
					CondRetGerenciador = GER_SalvarTabuleiro ( Disposicao );
					if( CondRetGerenciador != GER_CondRetOK ){
						printf("Erro ao salvar tabuleiro\n");

						}
					printf("Obrigado por SE DIVERTIR!!!");
					ControleJogo = 0;
					return;

				}/* if */

			}/* if */

			printf("1- LinhaOrigem: %d - ColunaOrigem: %c - LinhaDestino: %d - ColunaDestino: %c\n",LinhaOrigem,ColunaOrigem,LinhaDestino,ColunaDestino);

			CondRetMovimentador = MOV_MoverPeca ( ColunaOrigem , LinhaOrigem , ColunaDestino , 
																	LinhaDestino , pGrafo );

			printf("CondRetMovimentador: %d\n",CondRetMovimentador);

			if( CondRetMovimentador != MOV_CondRetOK ){

				while( CondRetMovimentador != MOV_CondRetOK ){
					printf("Movimento invalido, insira um movimento valido:\n");
								printf("3- LinhaOrigem: %d - ColunaOrigem: %c - LinhaDestino: %d - ColunaDestino: %c\n",LinhaOrigem,ColunaOrigem,LinhaDestino,ColunaDestino);

					NumLidos = scanf("%c%d %c%d" , &ColunaOrigem , &LinhaOrigem , &ColunaDestino , &LinhaDestino );
								printf("4- LinhaOrigem: %d - ColunaOrigem: %c - LinhaDestino: %d - ColunaDestino: %c\n",LinhaOrigem,ColunaOrigem,LinhaDestino,ColunaDestino);

					if ( NumLidos != 5 )
					{
						if ( ( NumLidos == 1 ) && ( ColunaOrigem == 'S' ) )
						{
							Disposicao = "..\\Definicao\\DISPOSICAO.TXT";
							CondRetGerenciador = GER_SalvarTabuleiro ( Disposicao );
							if( CondRetGerenciador != GER_CondRetOK ){
								printf("Erro ao salvar tabuleiro\n");

								}
							printf("Obrigado por SE DIVERTIR!!!");
							ControleJogo = 0;
							return;

						}/* if */

					}/* if */

					CondRetMovimentador = MOV_MoverPeca ( ColunaOrigem , LinhaOrigem , ColunaDestino , 
																			LinhaDestino , pGrafo );

					}/* while */

				printf("2- LinhaOrigem: %d - ColunaOrigem: %c - LinhaDestino: %d - ColunaDestino: %c\n",LinhaOrigem,ColunaOrigem,LinhaDestino,ColunaDestino);


				}/* if */

			/* Destruir o grafo criado */
			CondRetGrafo = GRA_DestruirGrafo( &pGrafo );

			/* Cria o grafo à partir do tabuleiro */
			CondRetMovimentador = MOV_AdicionarPecasAoGrafo ( &pGrafo ); 
			CondRetMovimentador = MOV_GeraMovimentacoes ( &pGrafo );

			GER_AlterarCorDaVez();

			Cor = GER_ObterCorDaVez();

			switch ( Cor )
			{
				case GER_CorBranca:
					cCor = 'B';
					break;
				case GER_CorPreta:
					cCor = 'P';
					break;
				case GER_CorSemCor:
					continue ;
				default:
					continue;
			}

			/* Verifica se está em xeque-mate */
			CondRetMovimentador = MOV_ReconhecerXequeMate ( cCor, pGrafo);

			if( CondRetMovimentador == MOV_CondRetXequeMate ){
				ControleJogo = 0;
				printf("Xeque-mate\n");
				GER_ImprimirTabuleiro();
				printf("Obrigado por SE DIVERTIR!!!");

				}/* if */

			/* Destruir o grafo criado */
			CondRetGrafo = GRA_DestruirGrafo( &pGrafo );

		}/* while */
	

	//constroi grafo à partir do tabuleiro

	//obtem vez

	//chama jogar xadrez

		return;

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