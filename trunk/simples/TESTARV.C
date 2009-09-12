/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
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
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo árvore. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     "=criar <Int>"				- chama a função ARV_CriarArvore( vtpArvore[<Int>] )
*
*     "=insfilho <Int> <Char>"
*									- chama a função ARV_InserirFilho( vtpArvore[<Int>], <Char> )
*										Obs. notação: <Char>  é o valor do parâmetro
*										que se encontra no comando de teste.
*
*     "=irpai <Int>"				- chama a função ARV_IrPai( vtpArvore[<Int>] )
*
*     "=irfilho <Int>"				- chama a função ARV_IrNoFilho( vtpArvore[<Int>] )
*
*     "=irirmao <Int>"				- chama a função ARV_IrNoIrmao( vtpArvore[<Int>] )
*     "=obter" <Char> <Int>"
*									- chama a função ARV_ObterValorCorr( vtpArvore[<Int>] ) e compara
*										o valor retornado com o valor <Char>
*     "=destroi <Int>"				- chama a função ARV_DestruirArvore( vtpArvore[<Int>] )
*     "=exibir <Int>"				- chama a função ARV_ExibirArvore( vtpArvore[<Int>] )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "arvore.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_ARV_CMD       "=criar"
#define		INS_FILHO_CMD		"=insfilho"
#define     IR_PAI_CMD          "=irpai"
#define		IR_IRMAO_CMD		"=irirmao"
#define		IR_FILHO_CMD		"=irfilho"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"
#define		EXIBIR_CMD			"=exibir"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

      static tpArvore * vtpArvore[10];
            /* Vetor de ponteiros para cabeças de 10 árvores */

/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
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

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  int ixArvore		 = -1;

      int  NumLidos      = -1 ;

      TST_tpCondRet Ret ;

      /* Testar ARV Criar árvore */

         if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , 
                               &ixArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			printf("Conteudo: %d \n",vtpArvore[ixArvore]);

            CondRetObtido = ARV_CriarArvore( &vtpArvore[ixArvore] ) ;


			printf("Conteudo: %d \n",vtpArvore[ixArvore]);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar ARV Criar árvore */

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
                                    "Retorno errado ao inserir à esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho à esquerda */

      /* Testar ARV Ir para nó pai */

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

         } /* fim ativa: Testar ARV Ir para nó pai */

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

      /* Testar ARV Ir para nó irmão */

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

         } /* fim ativa: Testar ARV Ir para nó irmão */

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
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir árvore */

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

         } /* fim ativa: Testar ARV Destruir árvore */

	  /* Testar ARV Exibir árvore */

         else if ( strcmp( ComandoTeste , EXIBIR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &ixArvore ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			printf("\nExibindo a árvore %d\n", ixArvore);
            ARV_ExibirArvore( vtpArvore[ixArvore] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Exibir árvore */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TARV Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

