/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico do movimentador de peças de Xadrez
*
*  Arquivo gerado:              TESTMOV.C
*  Letras identificadoras:      TMOV
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   12/set/2009 Início desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo movimentador de peças de Xadrez.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo reconhecedor:
*
*     "=adicionarpecas <CondRetEsp>		- chama a função MOV_AdicionarPecasAoGrafo ( )
*
*	  "=gerarmov <CondRetEsp>			- chama a função MOV_GeraMovimentacoes ( )
*
*	  "=exibir"							- chama a função GRA_ExibirGrafo ( )
*
*	  "=reconhecerxeque <Cor> <CondRetEsp>"	- chama a função MOV_ReconhecerXequeMate ( )
*
*	  "=moverpeca <Col><Lin><Col><Lin><CondRetEsp>	- chama a função MOV_MoverPeca ( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "MOVIMENTADOR.H"
#include	"GERENCIADOR.H"
#include	"GRAFO.H"

#define		DISPOSICAO				"..\\Definicao\\DISPOSICAO.TXT"

/* Tabela dos nomes dos comandos de teste específicos */

#define		ADICIONAR_PECAS_CMD		"=adicionarpecas"
#define		GERAR_MOV_CMD			"=gerarmov"
#define		EXIBIR_CMD				"=exibir"
#define		RECONHECER_XEQUE_MATE_CMD	"=reconhecerxequemate"
#define		MOVER_PECA_CMD			"=moverpeca"
#define		JOGAR_XADREZ_CMD		"=jogarxadrez"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

GRA_tppGrafo pGrafo;

/***********************************************************************
*
*  $FC Função: TMOV Efetuar operações de teste específicas para movimentações
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     vértice sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MOV_tpCondRet CondRetObtida   = MOV_CondRetOK ;
      MOV_tpCondRet CondRetEsperada = MOV_CondRetFaltouMemoria ;
	  GER_tpCondRet CondRetGER		= GER_CondRetOK ;
	  char ColunaOrigem				= '!' ;
	  char ColunaDestino			= '@' ;
	  int LinhaOrigem				= -1 ;
	  int LinhaDestino				= -2 ;
                                      /* inicializa para qualquer coisa */
	  int NumLidos = -1;
	  char CorDada = '!';

	  TST_tpCondRet Ret ;

      /* Testar MOV Montar Grafo */

         if ( strcmp( ComandoTeste , ADICIONAR_PECAS_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */


			 /* Inicializa o tabuleiro */
			 CondRetGER = GER_InicializarTabuleiro ( );
			 if ( CondRetGER != GER_CondRetOK )
			 {
				 return TST_CondRetErro ;
			 }

			 /* Preenche o tabuleiro */
			 CondRetGER = GER_PreencherTabuleiro ( DISPOSICAO );
			 if ( CondRetGER != GER_CondRetOK )
			 {
				 return TST_CondRetErro ;
			 }

			 /* Adiciona as peças ao grafo */
			 CondRetObtida = MOV_AdicionarPecasAoGrafo ( &pGrafo );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao montar o grafo. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 }

			 return Ret;
         } /* fim ativa: Testar MOV Montar Grafo */

	/* Testar MOV Gerar movimentação */

         else if ( strcmp( ComandoTeste , GERAR_MOV_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 /* Adiciona as movimentações das peças */
			 CondRetObtida = MOV_GeraMovimentacoes ( &pGrafo );

			 
			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao montar o grafo. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 }

			 return Ret;
         } /* fim ativa: Testar MOV Adicionar Movimentos */

	/* Testar MOV Exibir Grafo de Movimentação */

         else if ( strcmp( ComandoTeste , EXIBIR_CMD ) == 0 )
         {

			GRA_ExibirGrafo(pGrafo);

			 return TST_CondRetOK;
         } /* fim ativa: Testar MOV Exibir Grafo de Movimentação */

	/* Testar REC Reconhecer Xeque Mate */

         else if ( strcmp( ComandoTeste , RECONHECER_XEQUE_MATE_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ci" , 
											&CorDada , &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 /* Adiciona as movimentações das peças */
			 CondRetObtida = MOV_ReconhecerXequeMate ( CorDada, pGrafo);

			 
			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao reconhecer xeque mate. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return Ret;
         } /* fim ativa: Testar REC Reconhecer Xeque Mate */

	 /* Testar MOV Mover Peça */

         else if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "cicii" , 
											&ColunaOrigem , &LinhaOrigem , &ColunaDestino , &LinhaDestino , &CondRetEsperada ) ;
			 if ( NumLidos != 5 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = MOV_MoverPeca ( ColunaOrigem , LinhaOrigem , ColunaDestino , LinhaDestino , pGrafo ) ;
			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao mover peca " );

			 return Ret;
         } /* fim ativa: Testar MOV Mover Peça */

	 /* Testar MOV Jogar Xadrez */

         else if ( strcmp( ComandoTeste , JOGAR_XADREZ_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = MOV_JogarXadrez(  ) ;
			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao jogar xadrez " );

			 return Ret;
         } /* fim ativa: Testar JogarXadrez */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMOV Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

