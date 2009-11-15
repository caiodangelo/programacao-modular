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

/* Tabela dos nomes dos comandos de teste específicos */

#define		INICIAR_PARTIDA_CMD		"=iniciar"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

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

   } /* Fim função: TMOV Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

