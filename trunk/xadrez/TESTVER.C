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
#define		ALT_VAL_CMD			"=alterar"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTRUIR_CMD        "=destruir"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

      static tpVertice * vtpVertice[10];
            /* Vetor de ponteiros para 10 vértices */

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

      VER_tpCondRet CondRetObtido   = VER_CondRetOK ;
      VER_tpCondRet CondRetEsperada = VER_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado[10] = "vaca"  ;
      char ValorObtido[10]  = "cachorro"  ;
      char ValorDado[10]     = "gato" ;
	  int ixVertice		 = -1;

      int  NumLidos      = -1 ;

      TST_tpCondRet Ret ;

      /* Testar VER Criar vértice */

         if ( strcmp( ComandoTeste , CRIAR_VER_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" , 
                               &ixVertice, ValorDado, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VER_CriarVertice( &vtpVertice[ixVertice], ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar vértice." );

         } /* fim ativa: Testar VER Criar vértice */

      /* Testar VER Alterar valor */

         else if ( strcmp( ComandoTeste , ALT_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &ixVertice, ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VER_AlterarValor( vtpVertice[ixVertice], ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao alterar valor." );

         } /* fim ativa: Testar VER Adicionar filho à esquerda */


      /* Testar VER Obter valor  */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &ixVertice, ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VER_ObterValor( vtpVertice[ixVertice], ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararString( ValorEsperado , ValorObtido ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar VER Obter valor corrente */

      /* Testar VER Destruir vértice */

         else if ( strcmp( ComandoTeste , DESTRUIR_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "i" ,
                               &ixVertice ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            VER_DestruirVertice( vtpVertice[ixVertice] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar VER Destruir vértice */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TVER Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

