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

#include    "VERTICE.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_GRA_CMD			"=criargra"
#define		DESTRUIR_GRA_CMD		"=destruirgra"
#define		INSERIR_VER_CMD			"=inserirver"
#define		EXCLUIR_VER_CMD			"=excluir"
#define		INSERIR_ARE_CMD			"=inserirare"
#define		REMOVER_ARE_CMD			"=removerare"
#define		EXIBIR_GRA_CMD			"=exibirgra"
#define		MARCAR_ORIGEM_CMD		"=marcarorigem"
#define		DESMARCAR_ORIGEM_CMD	"=desmarcarorigem"

/*****  Código das funções exportadas pelo módulo  *****/

/*****  Dados encapsulados no módulo  *****/

      static tpGrafo * pGrafo;
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

      int  NumLidos      = -1 ;

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

      return TST_CondRetNaoConhec ;

   } /* Fim função: TVER Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

