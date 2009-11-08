/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico do movimentador de pe�as de Xadrez
*
*  Arquivo gerado:              TESTMOV.C
*  Letras identificadoras:      TMOV
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     0       cev   12/set/2009 In�cio desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo movimentador de pe�as de Xadrez.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo reconhecedor:
*
*     "=adicionarpecas <CondRetEsp>		- chama a fun��o MOV_AdicionarPecasAoGrafo ( )
*
*	  "=gerarmov <CondRetEsp>			- chama a fun��o MOV_GeraMovimentacoes ( )
*
*	  "=exibir"							- chama a fun��o GRA_ExibirGrafo ( )
*
*	  "=reconhecerxeque <Cor> <CondRetEsp>"	- chama a fun��o MOV_ReconhecerXequeMate ( )
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

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define		ADICIONAR_PECAS_CMD		"=adicionarpecas"
#define		GERAR_MOV_CMD			"=gerarmov"
#define		EXIBIR_CMD				"=exibir"
#define		RECONHECER_XEQUE_CMD	"=reconhecerxeque"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*****  Dados encapsulados no m�dulo  *****/

GRA_tppGrafo pGrafo;

/***********************************************************************
*
*  $FC Fun��o: TMOV Efetuar opera��es de teste espec�ficas para movimenta��es
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     v�rtice sendo testado.
*
*  $EP Par�metros
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
                                      /* inicializa para qualquer coisa */
	  int NumLidos = -1;
	  char CorDada = '!';

	  TST_tpCondRet Ret ;

      /* Testar REC Montar Grafo */

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

			 /* Adiciona as pe�as ao grafo */
			 CondRetObtida = MOV_AdicionarPecasAoGrafo ( &pGrafo );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao montar o grafo. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 }

			 return Ret;
         } /* fim ativa: Testar REC Montar Grafo */

	/* Testar REC Gerar movimenta��o */

         else if ( strcmp( ComandoTeste , GERAR_MOV_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 /* Adiciona as movimenta��es das pe�as */
			 CondRetObtida = MOV_GeraMovimentacoes ( &pGrafo );

			 
			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao montar o grafo. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 }

			 return Ret;
         } /* fim ativa: Testar REC Adicionar Movimentos */

	/* Testar REC Exibir Grafo de Movimenta��o */

         else if ( strcmp( ComandoTeste , EXIBIR_CMD ) == 0 )
         {

			GRA_ExibirGrafo(pGrafo);

			 return TST_CondRetOK;
         } /* fim ativa: Testar REC Exibir Grafo de Movimenta��o */

	/* Testar REC Reconhecer Xeque Mate */

         else if ( strcmp( ComandoTeste , RECONHECER_XEQUE_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ci" , 
											&CorDada , &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 /* Adiciona as movimenta��es das pe�as */
			 CondRetObtida = MOV_ReconhecerXequeMate ( CorDada );

			 
			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao reconhecer xeque mate. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 }

			 return Ret;
         } /* fim ativa: Testar REC Reconhecer Xeque Mate */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TMOV Efetuar opera��es de teste espec�ficas para v�rtice */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
