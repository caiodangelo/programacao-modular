/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4.00   cev   15/09/2009 Cria��o de novos comandos de teste e remo��o de comandos
*								n�o aplic�veis ao novo M�dulo �rvore
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo �rvore. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo �rvore:
*
*     "=criar <Int>"				- chama a fun��o ARV_CriarArvore( vtpArvore[<Int>] )
*
*     "=insfilho <Int> <Char>"
*									- chama a fun��o ARV_InserirFilho( vtpArvore[<Int>], <Char> )
*										Obs. nota��o: <Char>  � o valor do par�metro
*										que se encontra no comando de teste.
*
*     "=irpai <Int>"				- chama a fun��o ARV_IrPai( vtpArvore[<Int>] )
*
*     "=irfilho <Int>"				- chama a fun��o ARV_IrNoFilho( vtpArvore[<Int>] )
*
*     "=irirmao <Int>"				- chama a fun��o ARV_IrNoIrmao( vtpArvore[<Int>] )
*     "=obter" <Char> <Int>"
*									- chama a fun��o ARV_ObterValorCorr( vtpArvore[<Int>] ) e compara
*										o valor retornado com o valor <Char>
*     "=destroi <Int>"				- chama a fun��o ARV_DestruirArvore( vtpArvore[<Int>] )
*     "=exibir <Int>"				- chama a fun��o ARV_ExibirArvore( vtpArvore[<Int>] )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "arvore.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_ARV_CMD       "=criar"
#define		INS_FILHO_CMD		"=insfilho"
#define     IR_PAI_CMD          "=irpai"
#define		IR_IRMAO_CMD		"=irirmao"
#define		IR_FILHO_CMD		"=irfilho"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"
#define		EXIBIR_CMD			"=exibir"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*****  Dados encapsulados no m�dulo  *****/

      static tpArvore * vtpArvore[10];
            /* Vetor de ponteiros para cabe�as de 10 �rvores */

/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     �rvore sendo testado.
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

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  int ixArvore		 = -1;

      int  NumLidos      = -1 ;

      TST_tpCondRet Ret ;

      /* Testar ARV Criar �rvore */

         if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , 
                               &ixArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_CriarArvore( &vtpArvore[ixArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar �rvore." );

         } /* fim ativa: Testar ARV Criar �rvore */

      /* Testar ARV Adicionar filho */

         else if ( strcmp( ComandoTeste , INS_FILHO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &ixArvore, &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirFilho( vtpArvore[ixArvore], ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir � esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho � esquerda */

      /* Testar ARV Ir para n� pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ixArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( vtpArvore[ixArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para n� pai */

      /* Testar ARV Ir para primeiro filho */

         else if ( strcmp( ComandoTeste , IR_FILHO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ixArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoFilho( vtpArvore[ixArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para primeiro filho */

      /* Testar ARV Ir para n� irm�o */

         else if ( strcmp( ComandoTeste , IR_IRMAO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ixArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoIrmao( vtpArvore[ixArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para n� irm�o */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &ixArvore, &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( vtpArvore[ixArvore], &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conte�do do n� est� errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir �rvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "i" ,
                               &ixArvore ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            ARV_DestruirArvore( &vtpArvore[ixArvore] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir �rvore */

	  /* Testar ARV Exibir �rvore */

         else if ( strcmp( ComandoTeste , EXIBIR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "ii" ,
                               &ixArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			printf("\nExibindo a arvore %d\n", ixArvore);
            CondRetObtido = ARV_ExibirArvore( vtpArvore[ixArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao exibir arvore" );

         } /* fim ativa: Testar ARV Exibir �rvore */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

