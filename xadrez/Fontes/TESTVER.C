/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico do m�dulo VERTICE
*
*  Arquivo gerado:              TESTVER.C
*  Letras identificadoras:      TVER
*
*  Projeto: INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       0	   cev   12/09/2009 In�cio do desenvolvimento
*       1	   cev   19/10/2009 Entrega do trabalho
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa as funcionalidades de teste do m�dulo VERTICE.
*	  Ele deve ser utilizado em conjunto com o Arcabou�o para testes automa-
*	  zados em C da disciplina.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo v�rtice:
*
*     "=criar <Int> <String>"		- chama a fun��o VER_CriarVertice( vtpVertice[<Int>], <String> )
*
*     "=alterar <Int> <String>"
*									- chama a fun��o VER_AlterarValor( vtpVertice[<Int>], <String> )
*
*     "=destruir <Int>"				- chama a fun��o VER_DestruirVertice( vtpVertice[<Int>] )
*
*     "=obter <Int> <String>"		- chama a fun��o VER_ObterValor( vtpVertice[<Int>] ) e compara
*										o valor retornado com o valor <String>
*
*	  "=adicionarsuc <Int> <Int>"	- chama a fun��o VER_AdicionarSucessor( vtpVertice[<Int>], vtpVertice[<Int>] )
*
*
*	  "=removersuc <Int> <Int>"		- chama a fun��o VER_RemoverSucessor( vtpVertice[<Int>], vtpVertice[<Int>] )
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "VERTICE.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_VER_CMD       "=criar"
#define     DESTRUIR_CMD        "=destruir"
#define		OBTER_ID_CMD		"=obterid"
#define		OBTER_VAL_CMD		"=obterval"
#define		ALT_VAL_CMD			"=altval"
#define		ADICIONAR_SUC_CMD	"=adicionarsuc"
#define		REMOVER_SUC_CMD		"=removersuc"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*****  Dados encapsulados no m�dulo  *****/

static VER_tppVertice vtpVertice[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
            /* Vetor de ponteiros para 10 v�rtices */
	  static int vtValorDado[10];
			/* Vetor de ponteiros para valores passados pelo script */

/***********************************************************************
*
*  $FC Fun��o: TVER Efetuar opera��es de teste espec�ficas para v�rtice
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
	  int ixVerticeOri	 = -9 ;
	  int ixVerticeDest	 = -10;
	  TST_tpCondRet Ret ;

      /* Testar VER Criar v�rtice */

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
									  "Retorno errado ao criar v�rtice. " );

         } /* fim ativa: Testar VER Criar v�rtice */

      /* Testar VER Obter id do v�rtice */

         else if ( strcmp( ComandoTeste , OBTER_ID_CMD ) == 0 )
         {
			
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVertice , &IdEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */
printf("%d\n",vtpVertice[ixVertice]);
			 CondRetObtida = VER_ObterId ( vtpVertice[ixVertice] , &IdObtido );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar v�rtice. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( IdEsperado , IdObtido ,
									  "Id do v�rtice est� errado." );

         } /* fim ativa: Testar VER Obter id do v�rtice */
  
	/* Testar VER Destruir v�rtice */

         else if ( strcmp( ComandoTeste , DESTRUIR_CMD ) == 0 )
         {
			
			 NumLidos = LER_LerParametros ( "ii" , 
											&ixVertice ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 VER_DestruirVertice ( vtpVertice[ixVertice] );
			 vtpVertice[ixVertice] = NULL ;
printf("%d\n",vtpVertice[ixVertice]);
			 return TST_CondRetOK ;

         } /* fim ativa: Testar VER Destruir v�rtice */

      /* Testar VER Obter valor do v�rtice */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVertice , &ValorEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = VER_ObterValor ( vtpVertice[ixVertice] , &pValorObtido );

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar v�rtice. " );

			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret ;
			 } /* if */

			 return TST_CompararInt ( ValorEsperado , *pValorObtido ,
									  "Valor do v�rtice est� errado." );

         } /* fim ativa: Testar VER Obter valor do v�rtice */

	/* Testar VER Alterar valor do v�rtice */

         else if ( strcmp( ComandoTeste , ALT_VAL_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVertice , &ValorDado, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 vtValorDado[ixVertice] = ValorDado;

			 CondRetObtida = VER_AlterarValor ( vtpVertice[ixVertice] , &vtValorDado[ixVertice] );

			 return TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar v�rtice. " );

         } /* fim ativa: Testar VER Alterar valor do v�rtice */

	  	/* Testar VER Adicionar sucessor ao v�rtice */

         else if ( strcmp( ComandoTeste , ADICIONAR_SUC_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVerticeOri , &ixVerticeDest, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = VER_AdicionarSucessor ( vtpVertice[ixVerticeOri] , vtpVertice[ixVerticeDest] );

			 return TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar v�rtice. " );

         } /* fim ativa: Testar VER Adicionar sucessor ao v�rtice */

	/* Testar VER Remover sucessor do v�rtice */

         else if ( strcmp( ComandoTeste , REMOVER_SUC_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iii" , 
											&ixVerticeOri , &ixVerticeDest, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = VER_RemoverSucessor ( vtpVertice[ixVerticeOri] , vtpVertice[ixVerticeDest] );

			 return TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar v�rtice. " );

         } /* fim ativa: Testar VER Remover sucessor do v�rtice */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TVER Efetuar opera��es de teste espec�ficas para v�rtice */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

