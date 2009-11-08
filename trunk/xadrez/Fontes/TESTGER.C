/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico do módulo geren-
*									ciador de xadrez
*
*  Arquivo gerado:              TESTGER.C
*  Letras identificadoras:      TGER
*
*  Projeto: INF 1301 - Programação Modular
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
*     módulo gerenciador de xadrez. 
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo vértice:
*
*     "=inicializar <CondRetEsp>"			- chama a função GER_InicializarTabuleiro ( )
*
*     "=criarpeca <Tipo> <CondRetEsp>"		- chama a função GER_CriarPeca ( )
*
*	  "=obtertipo <TipoEsp> <CondRetEsp>"	- chama a função GER_ObterTipo ( )
*
*	  "=obtercor <TipoEsp> <CondRetEsp>"	- chama a função GER_ObterCor ( )
*
*	  "=atribuirpeca <TipoPeca> <CorPeca> <CondRetEsp>" - chama a função GER_AtribuirPeca ( )
*
*	  "=obterultlin <Lin> <CondRetEsp>"		- chama a função GER_ObterUltimaLinhaTabuleiro ( )
*
*	  "=obterultcol <Col> <CondRetEsp>"		- chama a função GER_ObterUltimaColunaTabuleiro ( )
*
*	  "=preenchertab <CondRetEsp>"			- chama a função GER_PreencherTabuleiro ( )
*
*	  "=obterpecatab <Col> <Lin> <CondRetEsp>"	- chama a função GER_ObterPecaDoTabuleiro ( )
*
*	  "=destruirpeca"						- chama a função GER_DestruirPeca ( )
*
*	  "=limpartabuleiro"					- chama a função GER_LimparTabuleiro ( )
*
*	  "=obtercodtipo <CharTipo> <IntTipo>"	- chama a função GER_ObterCodigoDoTipo ( )
*
*	  "=obtercodcor <CharCor> <IntCor>" 	- chama a função GER_ObterCodigoDaCor ( )
*
*	  "=obterrei <CorRei> <ColEsp> <LinEsp> - chama a função GER_ObterRei ( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "GERENCIADOR.H"

#define		DISPOSICAO				"..\\Definicao\\DISPOSICAO.TXT"

/* Tabela dos nomes dos comandos de teste específicos */

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

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

GER_tppPeca pPeca = NULL;

/***********************************************************************
*
*  $FC Função: TVER Efetuar operações de teste específicas para o
*					gerenciador de jogos de xadrez
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     gerenciador sendo testado.
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
									  "Retorno errado ao criar vértice. " );

         } /* fim ativa: Testar GER Inicializar tabuleiro */

      /* Testar GER Criar peça */

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

         } /* fim ativa: Testar GER Criar peça */

      /* Testar GER Obter tipo da peça */

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
									  "Tipo da peça está errado." );

         } /* fim ativa: Testar GER Obter tipo da peça */

	/* Testar GER Obter cor da peça */

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
									  "Tipo da peça está errado." );

         } /* fim ativa: Testar GER Obter cor da peça */

	/* Testar GER Atribuir peça */

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
									  "Erro ao atribuir peça." );

         } /* fim ativa: Testar GER Atribuir peça */

	/* Testar GER Obter última linha do tabuleiro */

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
									  "Número da última linha do tabuleiro está errado." );

         } /* fim ativa: Testar GER Obter última linha do tabuleiro */

	/* Testar GER Obter última coluna do tabuleiro */

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
									  "Número da última coluna do tabuleiro está errado." );

         } /* fim ativa: Testar GER Obter última coluna do tabuleiro */

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
									  "Retorno não esperado ao preencher tabuleiro." );

         } /* fim ativa: Testar GER Preencher tabuleiro */

	/* Testar GER Obter peça do tabuleiro */

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
									  "Retorno nao esperado ao obter peça do tabuleiro." );

			return Ret ;
         } /* fim ativa: Testar GER Obter peça do tabuleiro */

	/* Testar GER Destruir peça */

         else if ( strcmp( ComandoTeste , DESTRUIR_PECA_CMD ) == 0 )
         {

			 GER_DestruirPeca ( &pPeca );

			 return TST_CondRetOK ;

         } /* fim ativa: Testar GER Destruir peça */

	/* Testar GER Limpar tabuleiro */

         else if ( strcmp( ComandoTeste , LIMPAR_TAB_CMD ) == 0 )
         {

			 GER_LimparTabuleiro ( );

			 return TST_CondRetOK ;

         } /* fim ativa: Testar GER Limpar tabuleiro */

	/* Testar GER Obter código do tipo */

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
									  "Retorno errado ao obter código do tipo." );

			return Ret ;
         } /* fim ativa: Testar GER Obter código do tipo */

	/* Testar GER Obter código da cor */

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
									  "Retorno errado ao obter código da cor." );

			return Ret ;
         } /* fim ativa: Testar GER Obter código da cor */

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
									  "Erro ao obter posição do rei." );

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

      return TST_CondRetNaoConhec ;

   } /* Fim função: TGER Efetuar operações de teste específicas para o gerenciador de xadrez */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

