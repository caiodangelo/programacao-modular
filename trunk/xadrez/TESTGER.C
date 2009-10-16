/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTGER.C
*  Letras identificadoras:      TGER
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

#include    "GERENCIADOR.H"

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
	  int Linha				= -5;
	  TST_tpCondRet Ret ;

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

         if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
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

         if ( strcmp( ComandoTeste , OBTER_TIPO_CMD ) == 0 )
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

         if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 )
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

         if ( strcmp( ComandoTeste , ATRIBUIR_PECA_CMD ) == 0 )
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

         if ( strcmp( ComandoTeste , OBTER_ULT_LIN_CMD ) == 0 )
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

         if ( strcmp( ComandoTeste , OBTER_ULT_COL_CMD ) == 0 )
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

         if ( strcmp( ComandoTeste , PREENCHER_TAB_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "i" , 
											&CondRetEsperada ) ;
			 if ( NumLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_PreencherTabuleiro ( "DISPOSICAO.TXT" );

			return TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Retorno não esperado ao preencher tabuleiro." );

         } /* fim ativa: Testar GER Preencher tabuleiro */

	/* Testar GER Obter peça do tabuleiro */

         if ( strcmp( ComandoTeste , OBTER_PECA_TAB_CMD ) == 0 )
         {
			 NumLidos = LER_LerParametros ( "cii" , 
											&Coluna, &Linha, &CondRetEsperada ) ;
			 if ( NumLidos != 3 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CondRetObtida = GER_ObterPecaDoTabuleiro ( &pPeca , Coluna , Linha );

  			 Ret = TST_CompararInt ( CondRetEsperada , CondRetObtida ,
									  "Retorno nao esperado ao preencher tabuleiro." );

			return Ret;
         } /* fim ativa: Testar GER Obter peça do tabuleiro */
      return TST_CondRetNaoConhec ;

   } /* Fim função: TGER Efetuar operações de teste específicas para o gerenciador de xadrez */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

