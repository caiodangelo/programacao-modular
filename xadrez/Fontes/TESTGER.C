/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico do m�dulo geren-
*									ciador de xadrez
*
*  Arquivo gerado:              TESTGER.C
*  Letras identificadoras:      TGER
*
*  Projeto: INF 1301 - Programa��o Modular
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
*     m�dulo gerenciador de xadrez. 
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo v�rtice:
*
*     "=inicializar <CondRetEsp>"			- chama a fun��o GER_InicializarTabuleiro ( )
*
*     "=criarpeca <Tipo> <CondRetEsp>"		- chama a fun��o GER_CriarPeca ( )
*
*	  "=obtertipo <TipoEsp> <CondRetEsp>"	- chama a fun��o GER_ObterTipo ( )
*
*	  "=obtercor <TipoEsp> <CondRetEsp>"	- chama a fun��o GER_ObterCor ( )
*
*	  "=atribuirpeca <TipoPeca> <CorPeca> <CondRetEsp>" - chama a fun��o GER_AtribuirPeca ( )
*
*	  "=obterultlin <Lin> <CondRetEsp>"		- chama a fun��o GER_ObterUltimaLinhaTabuleiro ( )
*
*	  "=obterultcol <Col> <CondRetEsp>"		- chama a fun��o GER_ObterUltimaColunaTabuleiro ( )
*
*	  "=preenchertab <CondRetEsp>"			- chama a fun��o GER_PreencherTabuleiro ( )
*
*	  "=obterpecatab <Col> <Lin> <CondRetEsp>"	- chama a fun��o GER_ObterPecaDoTabuleiro ( )
*
*	  "=destruirpeca"						- chama a fun��o GER_DestruirPeca ( )
*
*	  "=limpartabuleiro"					- chama a fun��o GER_LimparTabuleiro ( )
*
*	  "=obtercodtipo <CharTipo> <IntTipo>"	- chama a fun��o GER_ObterCodigoDoTipo ( )
*
*	  "=obtercodcor <CharCor> <IntCor>" 	- chama a fun��o GER_ObterCodigoDaCor ( )
*
*	  "=obterrei <CorRei> <ColEsp> <LinEsp>"- chama a fun��o GER_ObterRei ( )
*
*	  "=salvar <Arquivo> <CondRetEsp>"		- chama a fun��o GER_SalvarArquivo ( )
*
*	  "=imprimir"							- chama a dun��o GER_ImprimirTabuleiro ( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "GERENCIADOR.H"

#define		DISPOSICAO				"..\\Definicao\\DISPOSICAO3.TXT"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     INICIALIZAR_TAB_CMD     "=inicializar"
#define		CRIAR_PECA_CMD			"=criarpeca"
#define		OBTER_TIPO_CMD			"=obtertipo"
#define		OBTER_COR_CMD			"=obtercor"
#define		ATRIBUIR_PECA_CMD		"=atribuirpeca"
#define		OBTER_ULT_LIN_CMD		"=obterultlin"
#define		OBTER_ULT_COL_CMD		"=obterultcol"
#define		PREENCHER_TAB_CMD		"=preenchertab"
#define		OBTER_PECA_TAB_CMD		"=obterpecatab"
#define		DESTRUIR_PECA_CMD		"=destruirpeca"
#define		LIMPAR_TAB_CMD			"=limpartab"
#define		OBTER_COD_TIPO_CMD		"=obtercodtipo"
#define		OBTER_COD_COR_CMD		"=obtercodcor"
#define		OBTER_REI_CMD			"=obterrei"
#define		MOVER_PECA_CMD			"=moverpeca"
#define		SALVAR_CMD				"=salvar"
#define		IMPRIMIR_TAB_CMD		"=imprimir"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*****  Dados encapsulados no m�dulo  *****/

GER_tppPeca pPeca = NULL;

/***********************************************************************
*
*  $FC Fun��o: TVER Efetuar opera��es de teste espec�ficas para o
*					gerenciador de jogos de xadrez
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     gerenciador sendo testado.
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

      GER_tpCondRet CondRetObtida   = GER_CondRetOK ;
      GER_tpCondRet CondRetEsperada = GER_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
	  int NumLidos			= -1;
	  int TipoPeca			= -2 ;
	  int ValorObtido		= -3;
	  int ValorEsperado		= -4;
	  int CorPeca			= -3;
	  char ColunaEsperada	= '!';
	  char ColunaObtida		= '@';
	  char Coluna			= '#';
	  char CharTipo			= '(' ;
	  char CharCor			= ')' ;
	  int Linha				= -5;
	  char ColunaOrigem		= '!' ;
	  char ColunaDestino	= '@' ;
	  int LinhaOrigem		= -1 ;
	  int LinhaDestino		= -2 ;
	  TST_tpCondRet Ret ;
	  GER_tppPeca pPecaOrigem = NULL ;
	  GER_tppPeca pPecaDestino = NULL ;
	  char Arquivo[70]  ;

      /* Testar GER Inicializar tabuleiro */

         if ( strcmp( ComandoTeste , INICIALIZAR_TAB_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_InicializarTabuleiro ( );

			 return TST_CompararInt ( CondRetEsperada , CondRetObtida , 
									  "Retorno errado ao criar v�rtice. " );

         } /* fim ativa: Testar GER Inicializar tabuleiro */

      /* Testar GER Criar pe�a */

         else if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ii" , 
											&TipoPeca, &CorPeca ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 pPeca = GER_CriarPeca ( TipoPeca , CorPeca );

			 return TST_CondRetOK;

         } /* fim ativa: Testar GER Criar pe�a */

      /* Testar GER Obter tipo da pe�a */

         else if ( strcmp( ComandoTeste , OBTER_TIPO_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ii" , 
											&ValorEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ValorObtido = GER_ObterTipo ( pPeca );

			 return TST_CompararInt ( ValorEsperado , ValorObtido ,
									  "Tipo da pe�a est� errado." );

         } /* fim ativa: Testar GER Obter tipo da pe�a */

	/* Testar GER Obter cor da pe�a */

         else if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ii" , 
											&ValorEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ValorObtido = GER_ObterCor ( pPeca );

			 return TST_CompararInt ( ValorEsperado , ValorObtido ,
									  "Tipo da pe�a est� errado." );

         } /* fim ativa: Testar GER Obter cor da pe�a */

	/* Testar GER Atribuir pe�a */

         else if ( strcmp( ComandoTeste , ATRIBUIR_PECA_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "iii" , 
											&TipoPeca, &CorPeca, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_AtribuirPeca ( pPeca, TipoPeca , CorPeca );

			 return TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Erro ao atribuir pe�a." );

         } /* fim ativa: Testar GER Atribuir pe�a */

	/* Testar GER Obter �ltima linha do tabuleiro */

         else if ( strcmp( ComandoTeste , OBTER_ULT_LIN_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ii" , 
											&ValorEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ValorObtido = GER_ObterUltimaLinhaTabuleiro (  );

			 return TST_CompararInt ( ValorEsperado , ValorObtido ,
									  "N�mero da �ltima linha do tabuleiro est� errado." );

         } /* fim ativa: Testar GER Obter �ltima linha do tabuleiro */

	/* Testar GER Obter �ltima coluna do tabuleiro */

         else if ( strcmp( ComandoTeste , OBTER_ULT_COL_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ci" , 
											&ColunaEsperada, &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ColunaObtida = GER_ObterUltimaColunaTabuleiro (  );

			 return TST_CompararChar ( ColunaEsperada , ColunaObtida ,
									  "N�mero da �ltima coluna do tabuleiro est� errado." );

         } /* fim ativa: Testar GER Obter �ltima coluna do tabuleiro */

      /* Testar GER Preencher tabuleiro */

         else if ( strcmp( ComandoTeste , PREENCHER_TAB_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_PreencherTabuleiro ( DISPOSICAO );

			return TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Retorno n�o esperado ao preencher tabuleiro." );

         } /* fim ativa: Testar GER Preencher tabuleiro */

	/* Testar GER Obter pe�a do tabuleiro */

         else if ( strcmp( ComandoTeste , OBTER_PECA_TAB_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "cii" , 
											&Coluna, &Linha, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_ObterPecaDoTabuleiro ( &pPeca , Coluna , Linha );

  			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Retorno nao esperado ao obter pe�a do tabuleiro." );

			return Ret ;
         } /* fim ativa: Testar GER Obter pe�a do tabuleiro */

	/* Testar GER Destruir pe�a */

         else if ( strcmp( ComandoTeste , DESTRUIR_PECA_CMD ) == 0 )
         {

			 GER_DestruirPeca ( &pPeca );

			 return TST_CondRetOK ;

         } /* fim ativa: Testar GER Destruir pe�a */

	/* Testar GER Limpar tabuleiro */

         else if ( strcmp( ComandoTeste , LIMPAR_TAB_CMD ) == 0 )
         {

			 GER_LimparTabuleiro ( );

			 return TST_CondRetOK ;

         } /* fim ativa: Testar GER Limpar tabuleiro */

	/* Testar GER Obter c�digo do tipo */

         else if ( strcmp( ComandoTeste , OBTER_COD_TIPO_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ci" , 
											&CharTipo, &ValorEsperado ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ValorObtido = GER_ObterCodigoDoTipo ( CharTipo );

  			 Ret = TST_CompararInt ( ValorEsperado , ValorObtido ,
									  "Retorno errado ao obter c�digo do tipo." );

			return Ret ;
         } /* fim ativa: Testar GER Obter c�digo do tipo */

	/* Testar GER Obter c�digo da cor */

         else if ( strcmp( ComandoTeste , OBTER_COD_COR_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "ci" , 
											&CharCor, &ValorEsperado ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ValorObtido = GER_ObterCodigoDaCor ( CharCor );

  			 Ret = TST_CompararInt ( ValorEsperado , ValorObtido ,
									  "Retorno errado ao obter c�digo da cor." );

			return Ret ;
         } /* fim ativa: Testar GER Obter c�digo da cor */

	/* Testar GER Obter rei */

         else if ( strcmp( ComandoTeste , OBTER_REI_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "icii" , 
											&CorPeca, &ColunaEsperada , &ValorEsperado, &CondRetEsperada ) ;
			 if ( NumLidos != 4 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 ValorObtido = GER_ObterRei ( CorPeca , &Coluna , &Linha );

			Ret = TST_CompararInt ( CondRetEsperada , ValorObtido ,
									  "Erro ao obter posi��o do rei." );

			if ( Ret != TST_CondRetOK )
			 {
				 return Ret;
			 }

  			 Ret = TST_CompararChar ( ColunaEsperada , Coluna ,
									  "Retorno errado ao obter coluna do rei." );
			 if ( Ret != TST_CondRetOK )
			 {
				 return Ret;
			 }

			 Ret = TST_CompararInt ( ValorEsperado , Linha ,
									"Retorno errado ao obter linha do rei." );

			return Ret ;
         } /* fim ativa: Testar GER Obter rei */

	/* Testar GER Mover Peca */

         else if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "cicii" , 
											&ColunaOrigem, &LinhaOrigem , &ColunaDestino , &LinhaDestino , &CondRetEsperada ) ;
			 if ( NumLidos != 5 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_ObterPecaDoTabuleiro ( &pPecaOrigem , ColunaOrigem , LinhaOrigem ) ;

			 CondRetObtida = GER_ObterPecaDoTabuleiro ( &pPecaDestino , ColunaDestino , LinhaDestino ) ;

			 CondRetObtida = GER_MoverPeca ( pPecaOrigem , pPecaDestino ) ;

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Retorno errado ao mover peca." );

			 return Ret ;
         } /* fim ativa: Testar GER Mover Peca */

	 /* Testar GER Salvar Tabuleiro */

         else if ( strcmp( ComandoTeste , SALVAR_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "si" , 
											Arquivo , &CondRetEsperada ) ;
			 if ( NumLidos != 2 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_SalvarTabuleiro ( Arquivo ) ;

			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Retorno errado ao mover peca." );

			 return Ret ;
         } /* fim ativa: Testar GER Salvar tabuleiro */

	/* Testar GER Imprimir Tabuleiro */

         else if ( strcmp( ComandoTeste , IMPRIMIR_TAB_CMD ) == 0 )
         {

			 GER_ImprimirTabuleiro (  ) ;

			 return TST_CondRetOK ;
         } /* fim ativa: Testar GER Imprimir tabuleiro */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TGER Efetuar opera��es de teste espec�ficas para o gerenciador de xadrez */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

