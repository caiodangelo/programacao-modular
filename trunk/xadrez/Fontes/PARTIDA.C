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
#define VERDADEIRO 1
#define FALSO 0



/***** Protótipos das funções encapsuladas no módulo *****/

void IniciarPartida();

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

GRA_tppGrafo pGrafo;

/***************************************************************************
*
*  Função: PAR  &Iniciar Partida
*  ****/

void PAR_IniciarPartida(){

	int ComandoJogar			= VERDADEIRO ;
	char sEntrada[50] ;
	char cEntrada				= '!';
		
	while( ComandoJogar == VERDADEIRO ){
		printf("E hora da diversao!");
		IniciarPartida();
		printf("Deseja jogar uma nova partida?(S para sim e N para nao)\n");
		gets ( sEntrada ) ;
		if ( sscanf ( sEntrada , "%c" , &cEntrada ) == 1 )
		{
			if ( cEntrada == 'S' )
			{
				ComandoJogar = VERDADEIRO ;
			} /* if */
			else if ( cEntrada == 'N' )
			{
				ComandoJogar = FALSO ;
				printf("Obrigado por SE DIVERTIR!!!") ;
			} 
		}		
		}

	return;

	}/* Fim função: PAR &Iniciar Partida */

/***************************************************************************
*
*  Função: &Iniciar Partida
*  ****/

void IniciarPartida(){

	int InicioOK				= FALSO ;
	int ContinuaPartida			= VERDADEIRO ;
	int MovimentoOK				= VERDADEIRO ;
	char sEntrada[50] ;
	char cEntrada				= '!';
	char * Disposicao			= "";
	GER_tpCondRet CondRetGER	= GER_CondRetOK ;
	MOV_tpCondRet CondRetMOV	= MOV_CondRetOK ;
	GER_tpCorPeca CorDaVez		= GER_CorBranca ;
	char ColunaOrigem			= '!' ;
	char ColunaDestino			= '@' ;
	int LinhaOrigem				= -1 ;
	int LinhaDestino			= -2 ;
	int NumLidos				= -1 ;
	char cCor					= 'B' ;
	GER_tppPeca pPeca			= NULL ;

	printf ("\n Bem-Vindo ao Jogo de Xadrez do grupo CEV!! \n\n  " ) ;
	while ( InicioOK == FALSO )
	{
		printf ( "Para iniciar nova partida, digite |N|\nPara continuar uma partida antiga, digite |A|\n Para sair digite |S|\n" );
		gets ( sEntrada ) ;
		if ( sscanf ( sEntrada , "%c" , &cEntrada ) == 1 )
		{
			if ( cEntrada == 'N' )
			{
				InicioOK = VERDADEIRO ;
				Disposicao = "..\\Definicao\\DEFAULT.TXT" ;
			} /* if */
			else if ( cEntrada == 'A' )
			{
				InicioOK = VERDADEIRO ;
				Disposicao = "..\\Definicao\\DISPOSICAO.TXT" ;
			} /* if */
			else if ( cEntrada == 'S' )
			{
				return ;
			} /* if */
		} /* if */			
	} /* while */
	
	CondRetGER = GER_InicializarTabuleiro ( ) ;
	if ( CondRetGER != GER_CondRetOK )
	{
		printf ( "Erro ao inicializar o tabuleiro\n" ) ;
		return ;
	} /* if */

	CondRetGER = GER_PreencherTabuleiro ( Disposicao ) ;
	if ( CondRetGER != GER_CondRetOK )
	{
		printf ( "Erro ao preencher o tabuleiro\n" ) ;
		return ;
	} /* if */

	while ( ContinuaPartida == VERDADEIRO )
	{
		GER_ImprimirTabuleiro ( ) ;

		CondRetMOV = MOV_AdicionarPecasAoGrafo ( &pGrafo ) ;
		if ( CondRetMOV != MOV_CondRetOK )
		{
			printf ( "Erro ao adicionar peças ao grafo\n" ) ;
		} /* if */

		CondRetMOV = MOV_GeraMovimentacoes ( &pGrafo ) ;
		if ( CondRetMOV != MOV_CondRetOK )
		{
			printf ( "Erro ao gerar movimentacoes possíveis no grafo\n" ) ;
		} /* if */

		CorDaVez = GER_ObterCorDaVez ( ) ;

		
		do
		{
			MovimentoOK = VERDADEIRO ;
			switch ( CorDaVez )
			{
				case GER_CorBranca :
					printf ( "Vez das Brancas. Entre com a jogada:\n");
					break ;
				case GER_CorPreta :
					printf ( "Vez das Pretas. Entre com a jogada:\n");
					break ;
				default :
					printf ( "Erro ao obter a cor da vez.\n" ) ;
					return ;
			} /* switch */

			gets ( sEntrada ) ;
			if (( strcmp ( sEntrada , "SALVAR" ) == 0 )
				||( strcmp ( sEntrada , "salvar" ) == 0 ) )
			{
				if ( GER_SalvarTabuleiro ( "..\\Definicao\\DISPOSICAO.TXT" ) == GER_CondRetOK )
				{
					printf ( "Jogo Salvo\n" ) ;
					printf ( "Entre com a jogada:\n");
					gets ( sEntrada ) ;
				} /* if */
				else
				{
					printf ( "Erro ao salvar o arquivo" ) ;
					printf ( "Entre com a jogada:\n");
					gets ( sEntrada ) ;
				}
			} /* if */
			if (( strcmp ( sEntrada , "SAIR" ) == 0 )
					||( strcmp ( sEntrada , "sair" ) == 0 ) )
			{
				printf ( "Obrigado por SE DIVERTIR!!!\n" );
				return ;
			} /* else if */
			
			NumLidos = sscanf ( sEntrada , "%c%d %c%d" , 
				&ColunaOrigem , &LinhaOrigem , &ColunaDestino , &LinhaDestino );
			if ( NumLidos != 4 )
			{
				if ( ( NumLidos == 1 ) && ( ColunaOrigem == 'S' ) )
				{
					printf ( "Obrigado por SE DIVERTIR!!!\n" ) ;
					return ;
				} /* if */
				else {
					printf ( "Erro de sintaxe.\n" );
					printf ( "Utilize o formato <ColOrigem><LinOrigem> <ColDestino><LinDestino>\n" ) ;

					MovimentoOK = FALSO ;
				} /* else */				
			} /* if */
			else
			{
				CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , ColunaOrigem , LinhaOrigem ) ;
				if ( CondRetGER != GER_CondRetOK )
				{
					printf ( "Erro ao obter peca a mover" );

					MovimentoOK = FALSO ;
					continue ;
				} /* if */
				if ( GER_ObterCor ( pPeca ) != GER_ObterCorDaVez ( ) )
				{
					if ( GER_ObterCor ( pPeca ) == GER_CorSemCor )
					{
						printf ( "Ah... Esta casa esta vazia... Tente novamente!\n" );
						MovimentoOK = FALSO ;
					} /* if */
					else
					{
						printf ( "Nao eh a sua vez!\n" );
						MovimentoOK = FALSO ;
					}
				} /* if */
				
				else
				{
					CondRetMOV = MOV_MoverPeca ( ColunaOrigem , LinhaOrigem , ColunaDestino , LinhaDestino , pGrafo ) ;
					if ( CondRetMOV != MOV_CondRetOK )
					{
						printf ( "Movimento invalido.\n" );
						printf ( "Tente novamente\n" ) ;

						MovimentoOK = FALSO ;
					} /* if */
				} /* else */
			} /* else */
		} /* do */
		while ( MovimentoOK == FALSO ) ;	
		
		/* Destruir o grafo criado */
		GRA_DestruirGrafo( &pGrafo );

		/* Cria o grafo à partir do tabuleiro */
		CondRetMOV = MOV_AdicionarPecasAoGrafo ( &pGrafo ); 
		CondRetMOV = MOV_GeraMovimentacoes ( &pGrafo );

		GER_AlterarCorDaVez();

		CorDaVez = GER_ObterCorDaVez();

		switch ( CorDaVez )
		{
			case GER_CorBranca:
				cCor = 'B';
				break;
			case GER_CorPreta:
				cCor = 'P';
				break;
			case GER_CorSemCor:
				break ;
			default:
				break;
		}

		/* Verifica se está em xeque-mate */
		CondRetMOV = MOV_ReconhecerXequeMate ( cCor, pGrafo );

		if( CondRetMOV == MOV_CondRetXequeMate )
		{
			ContinuaPartida = FALSO ;
			GER_ImprimirTabuleiro ( );
			printf("Xeque-mate\n") ;
			switch ( CorDaVez )
			{
				case GER_CorBranca:
					printf("Pretas venceram!\n");
					break;
				case GER_CorPreta:
					printf("Brancas venceram!\n");
					break;
				case GER_CorSemCor:
					break ;
				default:
					break;
			}
		}/* if */

		/* Destruir o grafo criado */
		GRA_DestruirGrafo( &pGrafo );

	} /* while */
	
	GER_LimparTabuleiro ( ) ;

	return;

} /* Fim função: &Iniciar Partida */