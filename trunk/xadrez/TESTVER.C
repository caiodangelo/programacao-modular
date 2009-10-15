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
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "VERTICE.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_VER_CMD       "=criar"
#define     DESTRUIR_CMD        "=destruir"
#define		OBTER_ID_CMD		"=obterid"
#define		OBTER_VAL_CMD		"=obterval"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

      static tpVertice * vtpVertice[10];
            /* Vetor de ponteiros para 10 vértices */
	  static int vtValorDado[10];
			/* Vetor de ponteiros para valores passados pelo script */

/***********************************************************************
*
*  $FC Função: TVER Efetuar operações de teste específicas para vértice
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

      VER_tpCondRet CondRetObtida   = VER_CondRetOK ;
      VER_tpCondRet CondRetEsperada = VER_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int IdEsperado	 = -1 ;
	  int IdObtido		 = -2 ;
	  int IdDado		 = -3 ;
	  int ixVertice		 = -4 ;
      int NumLidos       = -5 ;
	  int ValorEsperado	 = -6 ;
	  int ValorObtido	 = -7 ;
	  int * pValorObtido = &ValorObtido ;
	  int ValorDado		 = -8 ;
	  TST_tpCondRet Ret ;

      /* Testar VER Criar vértice */

         if ( strcmp( ComandoTeste , CRIAR_VER_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iiii" , 
											&ixVertice , &ValorDado, &IdDado, &CondRetEsperada ) ;
			 if ( NumLidos != 4 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 vtValorDado[ixVertice] = ValorDado;

			 CondRetObtida = VER_CriarVertice ( &vtpVertice[ixVertice] , &vtValorDado[ixVertice] , IdDado );

			 return TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar vértice. " );

         } /* fim ativa: Testar VER Criar vértice */

      /* Testar VER Obter id do vértice */

         if ( strcmp( ComandoTeste , OBTER_ID_CMD ) == 0 )
         {
			
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVertice , &IdEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = VER_ObterId ( vtpVertice[ixVertice] , &IdObtido );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar vértice. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( IdEsperado , IdObtido ,
									  "Id do vértice está errado." );

         } /* fim ativa: Testar VER Obter id do vértice */
  
	/* Testar VER Destruir vértice */

         if ( strcmp( ComandoTeste , DESTRUIR_CMD ) == 0 )
         {
			
			 NumLidos = LER_LerParametros ( "ii" , 
											&ixVertice ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 VER_DestruirVertice ( &vtpVertice[ixVertice] );

			 return TST_CondRetOK ;

         } /* fim ativa: Testar VER Destruir vértice */

      /* Testar VER Obter valor do vértice */

         if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVertice , &ValorEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = VER_ObterValor ( vtpVertice[ixVertice] , &pValorObtido );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar vértice. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( ValorEsperado , *pValorObtido ,
									  "Valor do vértice está errado." );

         } /* fim ativa: Testar VER Obter valor do vértice */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TVER Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

