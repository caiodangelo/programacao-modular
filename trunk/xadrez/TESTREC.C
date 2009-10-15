/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTVER.C
*  Letras identificadoras:      TVER
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   cev   19/09/2009 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo vértice. 
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo vértice:
*
*     "=criar <Int> <String>"		- chama a função VER_CriarVertice( vtpVertice[<Int>], <String> )
*
*     "=alterar <Int> <String>"
*									- chama a função VER_AlterarValor( vtpVertice[<Int>], <String> )
*
*     "=destruir <Int>"				- chama a função VER_DestruirVertice( vtpVertice[<Int>] )
*
*     "=obter <Int> <String>"		- chama a função VER_ObterValor( vtpVertice[<Int>] ) e compara
*										o valor retornado com o valor <String>
*
*	  "=adicionarsuc <Int> <Int>"	- chama a função VER_AdicionarSucessor( vtpVertice[<Int>], vtpVertice[<Int>] )
*
*
*	  "=removersuc <Int> <Int>"		- chama a função VER_RemoverSucessor( vtpVertice[<Int>], vtpVertice[<Int>] )
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "RECONHECEDOR.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define		GERAR_MOV_CMD	"=geramov"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/


/***********************************************************************
*
*  $FC Função: TREC Efetuar operações de teste específicas para vértice
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

      REC_tpCondRet CondRetObtida   = REC_CondRetOK ;
      REC_tpCondRet CondRetEsperada = REC_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
	  int NumLidos = -1;
	  TST_tpCondRet Ret ;

      /* Testar REC Gerar Movimentações */

         if ( strcmp( ComandoTeste , GERAR_MOV_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = REC_GeraMovimentacoes ( );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao gerar movimentacoes. " );

			 return Ret;
         } /* fim ativa: Testar REC Gerar Movimentações */

      
      return TST_CondRetNaoConhec ;

   } /* Fim função: TREC Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

