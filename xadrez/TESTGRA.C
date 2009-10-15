/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTGRA.C
*  Letras identificadoras:      TGRA
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
*     módulo grafo. 
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo grafo:
*
*     "=criargra <Int>"				- chama a função GRA_CriarGrafo
*
*     "=destruirgra <Int>"				- chama a função GRA_DestruirGrafo
*
*     "=inserirver <Int>"			- chama a função GRA_InserirVertice
*
*	  "=excluirver <Int>"			- chama a função GRA_ExcluirVertice
*
*	  "=inserirare <Int>"			- chama a função GRA_InserirAresta
*
*	  "=removerare <Int>"			- chama a função GRA_RemoverAresta
*
*	  "=exibirgra <Int>"			- chama a função GRA_ExibirGrafo
*
*	  "=marcarorigem <Int>"			- chama a função GRA_MarcarComoOrigem
*
*	  "=desmarcarorigem <Int>"		- chama a função GRA_DesmarcarComoOrigem
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "GRAFO.H"
#include    "VERTICE.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_GRA_CMD				"=criargra"
#define		DESTRUIR_GRA_CMD			"=destruirgra"
#define		INSERIR_VER_CMD				"=inserirver"
#define		EXCLUIR_VER_CMD				"=excluir"
#define		INSERIR_ARE_CMD				"=inserirare"
#define		REMOVER_ARE_CMD				"=removerare"
#define		EXIBIR_GRA_CMD				"=exibirgra"
#define		MARCAR_ORIGEM_CMD			"=marcarorigem"
#define		DESMARCAR_ORIGEM_CMD		"=desmarcarorigem"
#define		OBTER_VALOR_COM_ID_CMD		"=obtervalorcomid"	
#define		AVANCAR_SUCESSOR_CMD		"=avancarsucessor"
#define		OBTER_VERTICE_COM_ID_CMD	"=obterverticecomid"
#define		IR_VERTICE_COM_ID_CMD		"=irverticecomid"


/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

      static GRA_tppGrafo pGrafo;
            /* Ponteiro para o grafo a ser manipulado */

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

      GRA_tpCondRet CondRetObtido   = GRA_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      //GRA_tppGrafo pGrafo;
	  int IdVertice			= -1 ;
	  int ValorVertice		= -2;
	  int IdVerticeOrigem	= -3;
	  int IdVerticeDestino	= -4;
	  int ValorObtido		= -5 ;
	  int * pValorObtido	= &ValorObtido;
	  int ValorEsperado		= -6;
	  int NumLidos			= -7 ;
	  //int IdObtido		 = -2 ;
	  //int IdDado		 = -3 ;
	  //int ixVertice		 = -4 ;
      //int ValorObtido	 = -7 ;
	  //int * pValorObtido = &ValorObtido ;
	  //int ValorDado		 = -8 ;
	  //int ixVerticeOri	 = -9 ;
	  //int ixVerticeDest	 = -10;

      TST_tpCondRet Ret ;

      /* Testar GRA Criar grafo */

         if ( strcmp( ComandoTeste , CRIAR_GRA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_CriarGrafo ( &pGrafo ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Criar grafo */

		 /* Testar GRA Destruir grafo */

         if ( strcmp( ComandoTeste , DESTRUIR_GRA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_DestruirGrafo( pGrafo ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Destruir grafo */

		 /* Testar GRA Inserir vértice */

         if ( strcmp( ComandoTeste , INSERIR_VER_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &ValorVertice , 
										&IdVertice , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_InserirVertice( pGrafo, &ValorVertice, IdVertice );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Inserir vértice */

		 /* Testar GRA Excluir vértice */

         if ( strcmp( ComandoTeste , EXCLUIR_VER_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_ExcluirVertice ( pGrafo ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Excluir vértice */

		 /* Testar GRA Inserir aresta */

         if ( strcmp( ComandoTeste , INSERIR_ARE_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &IdVerticeOrigem , &IdVerticeDestino , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_InserirAresta( pGrafo, IdVerticeOrigem, 
										IdVerticeDestino );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Inserir aresta */

		 /* Testar GRA Remover aresta */

         if ( strcmp( ComandoTeste , REMOVER_ARE_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &IdVerticeOrigem , &IdVerticeDestino , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_RemoverAresta( pGrafo, IdVerticeOrigem, 
									IdVerticeDestino );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Criar grafo */

		 /* Testar GRA Exibir grafo */

         if ( strcmp( ComandoTeste , EXIBIR_GRA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_ExibirGrafo( pGrafo );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Exibir grafo */

		 /* Testar GRA Marcar como origem */

         if ( strcmp( ComandoTeste , MARCAR_ORIGEM_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" , &IdVertice ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_MarcarComoOrigem( pGrafo, IdVertice );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Marcar como origem */

		 /* Testar GRA Desmarcar como origem */

         if ( strcmp( ComandoTeste , DESMARCAR_ORIGEM_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" , &IdVertice , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_DesmarcarComoOrigem( pGrafo, IdVertice );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Desmarcar como origem */

		 /* Testar GRA Obter valor com Id */

         if ( strcmp( ComandoTeste , OBTER_VALOR_COM_ID_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &IdVertice , &ValorEsperado ,  
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_ObterValorComId( pGrafo , IdVertice , &pValorObtido );

			Ret = TST_CompararInt ( CondRetEsperada , CondRetObtido , 
									  "Retorno errado ao criar vértice. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( ValorEsperado , *pValorObtido ,
									  "Valor do vértice está errado." );

         } /* fim ativa: Testar GRA Obter valor com Id */

		 /* Testar GRA Avançar sucessor */

         if ( strcmp( ComandoTeste , AVANCAR_SUCESSOR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" , &IdVertice , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_AvancarSucessor( pGrafo, IdVertice );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Avançar sucessor */

		 /* Testar GRA Ir vértice com Id */

         if ( strcmp( ComandoTeste , IR_VERTICE_COM_ID_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" , &IdVertice ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_IrVerticeComId( pGrafo , IdVertice);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Ir vértice com Id */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TVER Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

