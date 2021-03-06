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
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "MOVIMENTADOR.H"
#include	"GERENCIADOR.H"
#include    "PARTIDA.H"

#define		DISPOSICAO				"..\\Definicao\\DISPOSICAO.TXT"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define		INICIAR_PARTIDA_CMD		"=iniciar"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*****  Dados encapsulados no m�dulo  *****/

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
	  
                                      /* inicializa para qualquer coisa */
	  int NumLidos = -1;

	  TST_tpCondRet Ret ;

      /* Testar PAR Iniciar`Partida */

         if ( strcmp( ComandoTeste , INICIAR_PARTIDA_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */


			 /* Iniciar Partida */
			 CondRetObtida = 0;
				 PAR_IniciarPartida();

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "ERRO. " );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 }

			 return Ret;
         } /* fim ativa: Testar MOV Montar Grafo */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TMOV Efetuar opera��es de teste espec�ficas para v�rtice */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

