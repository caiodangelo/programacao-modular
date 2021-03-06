/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste manual
*
*  Arquivo gerado:              TST_ARV.C
*  Letras identificadoras:      TARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\MANUAL.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m o teste do m�dulo �rvore.
*     Ilustra como redigir um programa principal para teste manual.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <process.h>

#include    "arvore.h"

#define     FALSO       0
#define     VERDADEIRO  1
#define     DIM_BUFFER  100

/***********************************************************************
*
*  $TC Tipo de dados: TARV Identificacoes das acoes
*
*
***********************************************************************/

   typedef enum {

         AcaoErro ,
               /* Acao erro */

         AcaoCriarArvore ,
               /* Criar arvore */

         AcaoDestruir  ,
               /* Destruir arvore */

         AcaoInsEsquerda  ,
               /* Inserir aa esquerda */

         AcaoInsDireita  ,
               /* Inserir aa direita */

         AcaoIrEsquerda  ,
               /* Ir no esquerda */

         AcaoIrDireita  ,
               /* Ir no direita */

         AcaoIrPai  ,
               /* Ir no pai */

         AcaoObterValor  ,
               /* Obter valor no corrente */

         AcaoTerminar = 99
               /* Terminar teste */

   } TARV_tpIdAcao ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     �rvore sendo testado.
*
***********************************************************************/

   int main( )
   {

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;

      int  idAcao        = AcaoErro ;

      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      char Buffer[ DIM_BUFFER ] ;

      while ( 1 ) {

      /* Selecionar o teste */

         /* Exibir menu de opcoes de acao */

            printf( "\n\n----------" ) ;
            printf( "\n %3d Criar arvore" ,                  AcaoCriarArvore ) ;
            printf( "\n %3d Destruir arvore" ,               AcaoDestruir    ) ;
            printf( "\n %3d Inserir no' aa esquerda" ,       AcaoInsEsquerda ) ;
            printf( "\n %3d Inserir no' aa direita" ,        AcaoInsDireita  ) ;
            printf( "\n %3d Ir para no' aa filho esquerda" , AcaoIrEsquerda  ) ;
            printf( "\n %3d Ir para no' aa filho direita" ,  AcaoIrDireita   ) ;
            printf( "\n %3d Ir para no' pai" ,               AcaoIrPai       ) ;
            printf( "\n %3d Obter valor do no' corrente" ,   AcaoObterValor  ) ;
            printf( "\n %3d Terminar" ,                      AcaoTerminar    ) ;

         /* Validar a opcao fornecida */

            printf( "\n\nEscolha a opcao :  " ) ;

            idAcao = AcaoErro ;
            Buffer[ 0 ] = 0 ;

            if ( scanf( " %90[^\n]" , Buffer ) == 1 )
            {
               if ( sscanf( Buffer , " %d" , &idAcao ) != 1 )
               {
                  idAcao = AcaoErro ;
               } /* if */
            } /* if */

      /* Efetuar os testes */

         ValorObtido   = '!'  ;
         ValorDado     = '\0' ;
         Buffer[ 0 ]   = 0 ;

         switch ( idAcao ) {

         /* Testar ARV Criar �rvore */

            case AcaoCriarArvore :
            {

               printf( "   Criar a arvore" ) ;

               CondRetObtido = ARV_CriarArvore( ) ;

               printf( "\n   Condicao de retorno: %d" , CondRetObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Criar �rvore */

         /* Testar ARV Adicionar filho � direita */

            case AcaoInsDireita :
            {

               printf( "   Inserir no\' aa direita" ) ;

               printf( "\n   Forneca o caractere a inserir: " ) ;
               if ( scanf( " %c" , &ValorDado ) != 1 )
               {
                  printf( "\nDado errado" ) ;
                  break ;
               } /* if */

               CondRetObtido = ARV_InserirDireita( ValorDado ) ;

               printf( "\n   Condicao de retorno: %d" , CondRetObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Adicionar filho � direita */

         /* Testar ARV Adicionar filho � esquerda */

            case AcaoInsEsquerda :
            {

               printf( "   Inserir no\' aa esquerda" ) ;

               printf( "\n   Forneca o caractere a inserir: " ) ;
               if ( scanf( " %c" , &ValorDado ) != 1 )
               {
                  printf( "\nDado errado" ) ;
                  break ;
               } /* if */

               CondRetObtido = ARV_InserirEsquerda( ValorDado ) ;

               printf( "\n   Condicao de retorno: %d" , CondRetObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Adicionar filho � esquerda */

         /* Testar ARV Ir para n� pai */

            case AcaoIrPai :
            {

               printf( "   Ir para no\' pai" ) ;

               CondRetObtido = ARV_IrPai( ) ;

               printf( "\n   Condicao de retorno: %d" , CondRetObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Ir para n� pai */

         /* Testar ARV Ir para n� � esquerda */

            case AcaoIrEsquerda :
            {

               printf( "   Ir para no\' filho esquerda" ) ;

               CondRetObtido = ARV_IrNoEsquerda( ) ;

               printf( "\n   Condicao de retorno: %d" , CondRetObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Ir para n� � esquerda */

         /* Testar ARV Ir para n� � direita */

            case AcaoIrDireita :
            {

               printf( "   Ir para no\' filho direita" ) ;

               CondRetObtido = ARV_IrNoDireita( ) ;

               printf( "\n   Condicao de retorno: %d" , CondRetObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Ir para n� � direita */

         /* Testar ARV Obter valor corrente */

            case AcaoObterValor :
            {

               printf( "   Obter valor no\' corrente" ) ;

               ValorObtido   = '?' ;
               CondRetObtido = ARV_ObterValorCorr( &ValorObtido ) ;

               printf( "\n   Condicao de retorno: %d  Valor do no: %c" ,
                       CondRetObtido , ValorObtido ) ;

               break ;

            } /* fim ativa: Testar ARV Obter valor corrente */

         /* Testar ARV Destruir �rvore */

            case AcaoDestruir :
            {

               printf( "   Destruir a arvore" ) ;

               ARV_DestruirArvore( ) ;

               printf( "\n   Destruiu" ) ;

               break ;

            } /* fim ativa: Testar ARV Destruir �rvore */

         /* Tratar termino da execucao */

            case AcaoTerminar :
            {

               printf( "\n\nTerminar a execucao\n" ) ;
               exit( 0 ) ;

            } /* fim ativa: Tratar termino da execucao */

         /* Notificar opcao incorreta */

            default :
            {

               printf( "   opcao ilegal" ) ;

               break ;

            } /* fim ativa: Notificar opcao incorreta */

         } /* fim seleciona: Efetuar os testes */

      } /* fim repete: Corpo de TST Efetuar opera��es espec�ficas */

      return 0 ;

   } /* Fim fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore */

/********** Fim do m�dulo de implementa��o: M�dulo de teste manual **********/

