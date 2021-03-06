	/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   cev   19/09/2009 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo grafo. 
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo grafo:
*
*     "=criargra <Int>"						- chama a fun��o GRA_CriarGrafo
*
*     "=destruirgra <Int>"					- chama a fun��o GRA_DestruirGrafo
*
*     "=inserirver <Int><Int><Int>"			- chama a fun��o GRA_InserirVertice
*
*	  "=excluir <Int>"						- chama a fun��o GRA_ExcluirVertice
*
*	  "=inserirare <Int><Int><Int>"			- chama a fun��o GRA_InserirAresta
*
*	  "=removerare <Int><Int><Int>"			- chama a fun��o GRA_RemoverAresta
*
*	  "=exibirgra <Int>"					- chama a fun��o GRA_ExibirGrafo
*
*	  "=marcarorigem <Int><Int>"			- chama a fun��o GRA_MarcarComoOrigem
*
*	  "=desmarcarorigem <Int><Int>"			- chama a fun��o GRA_DesmarcarComoOrigem
*
*	  "=obtervalorcomid <Int><Int><Int>"	- chama a fun��o GRA_ObterValorComId
*
*	  "=irverticecomid <Int><Int>"			- chama a fun��o GRA_IrVerticeComId
*
*	  "=avancarsucessor <Int><Int>"			- chama a fun��o GRA_AvancarSucessor
*
*	  "=obterant <Int><Int><Int>"			- chama a fun��o GRA_ObterAntecessor
*
*	  "=obtersuc <Int><Int><Int>"			- chama a fun��o GRA_ObterSucessor
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

/* Tabela dos nomes dos comandos de teste espec�ficos */

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
#define		IR_VERTICE_COM_ID_CMD		"=irverticecomid"
#define		AVANCAR_SUCESSOR_CMD		"=avancarsucessor"
#define		OBTER_ANTECESSOR_CMD		"=obterant"
#define		OBTER_SUCESSOR_CMD			"=obtersuc"



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*****  Dados encapsulados no m�dulo  *****/

      static GRA_tppGrafo pGrafo;
            /* Ponteiro para o grafo a ser manipulado */

	  static int vtValorVertice[10];
			/* Vetor de ponteiros para valores de v�rtices */

	  static int vtIdVertice[10];
			/* Vetor de ponteiros para ids de v�rtices */

/***********************************************************************
*
*  $FC Fun��o: TVER Efetuar opera��es de teste espec�ficas para grafo
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
	  int IdObtido			= -8;
	  int * pIdObtido		= &IdObtido;
	  int IdEsperado		= -9;

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
			
            CondRetObtido = GRA_DestruirGrafo( &pGrafo ) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir grafo." );

         } /* fim ativa: Testar GRA Destruir grafo */

		 /* Testar GRA Inserir v�rtice */

         if ( strcmp( ComandoTeste , INSERIR_VER_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &ValorVertice , 
										&IdVertice , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			vtValorVertice[IdVertice] = ValorVertice;
			vtIdVertice[IdVertice] = IdVertice;
			
            CondRetObtido = GRA_InserirVertice( pGrafo, &vtValorVertice[IdVertice], vtIdVertice[IdVertice] );	
			
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir v�rtice." );

         } /* fim ativa: Testar GRA Inserir v�rtice */

		 /* Testar GRA Excluir v�rtice */

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
                                    "Retorno errado ao excluir v�rtice." );

         } /* fim ativa: Testar GRA Excluir v�rtice */

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
                                    "Retorno errado ao inserir aresta." );

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
                                    "Retorno errado ao remover aresta." );

         } /* fim ativa: Testar GRA Remover aresta */

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
                                    "Retorno errado ao exibir grafo." );

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
                                    "Retorno errado ao marcar como origem." );

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
                                    "Retorno errado ao desmarcar como origem." );

         } /* fim ativa: Testar GRA Desmarcar como origem */

		 /* Testar GRA Obter valor com Id */

         if ( strcmp( ComandoTeste , OBTER_VALOR_COM_ID_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &IdVertice , &ValorEsperado ,  
                               &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_ObterValorComId( pGrafo , IdVertice , &pValorObtido );

			Ret = TST_CompararInt ( CondRetEsperada , CondRetObtido , 
									  "Retorno errado ao obter valor com id. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( ValorEsperado , *pValorObtido ,
									  "Valor do v�rtice est� errado." );

         } /* fim ativa: Testar GRA Obter valor com Id */

		 /* Testar GRA Avan�ar sucessor */

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
                                    "Retorno errado ao avan�ar sucessor." );

         } /* fim ativa: Testar GRA Avan�ar sucessor */

		 /* Testar GRA Ir v�rtice com Id */

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
                                    "Retorno errado ao ir v�rtice com id." );

         } /* fim ativa: Testar GRA Ir v�rtice com Id */

		 /* Testar GRA Obter Sucessor */

         if ( strcmp( ComandoTeste , OBTER_SUCESSOR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &IdVertice , &IdEsperado ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_ObterSucessor ( pGrafo , IdVertice , 
									 pIdObtido ) ;

			Ret = TST_CompararInt ( CondRetEsperada , CondRetObtido , 
									  "Retorno errado ao obter sucessor. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( IdEsperado , *pIdObtido ,
									  "Id do v�rtice est� errado." );

         } /* fim ativa: Testar GRA Obter Sucessor */

		 /* Testar GRA Obter Antecessor */

         if ( strcmp( ComandoTeste , OBTER_ANTECESSOR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &IdVertice , &IdEsperado ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = GRA_ObterAntecessor ( pGrafo , IdVertice , 
									 pIdObtido ) ;

			Ret = TST_CompararInt ( CondRetEsperada , CondRetObtido , 
									  "Retorno errado ao obter sucessor. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( IdEsperado , *pIdObtido ,
									  "Id do v�rtice est� errado." );

			 } /* fim ativa: Testar GRA Obter Antecessor */

      return TST_CondRetNaoConhec ;

         } /* Fim fun��o: TGRA Efetuar opera��es de teste espec�ficas para grafo */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

