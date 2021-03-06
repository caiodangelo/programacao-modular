/***************************************************************************
*  $MCI M�dulo de implementa��o: TBS  Tabela de strings
*
*  Arquivo gerado:              TabStr.C
*  Letras identificadoras:      TBS
*  N�mero identificador:        000
*
*  Nome da base de software:    Gerar e acessar tabelas de strings
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\TABELA.BSW
*
*  Projeto: INF 1301/1628 - Exemplos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs Arndt von Staa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1        avs  20/11/2004  Inicio desenvolvimento
*
***************************************************************************/

#include <string.h>
#include <assert.h>

#define TabStr_OWN
#include "TabStr.H"
#undef TabStr_OWN

#define     DIM_STRING                256
#define     ID_NAO_ENCONTROU            1
#define     STRING_ERRO           "?!?!?"
    /* TMS_MIN_LENGTH deve ser igual ou maior do que o comprimento do
    *  string STRING_ERRO */

#include    "TabelaString.tab"

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpElementoTabela * ProcurarIdString( long idString ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: TBS Obter o tamanho de um string
*  ****/

   int TBS_ObterTamanhoString( long idString )
   {

      tpElementoTabela * pElementoTabela ;

      /* Controlar par�metros */
      #ifdef _DEBUG

         assert( idString >= 1 ) ;
      #endif

      /* Recuperar o descritor do string na tabela */

         pElementoTabela = ProcurarIdString( idString ) ;
         if ( pElementoTabela != NULL )
         {
            return pElementoTabela->tamString ;
         } /* if */

         return TBS_CondRetNaoExiste ;

   } /* Fim fun��o: TBS Obter o tamanho de um string */

/***************************************************************************
*
*  Fun��o: TBS Obter um string contido na tabela
*  ****/

   TBS_tpCondRet TBS_ObterString( long   idString  ,
                                  int    dimString ,
                                  char * pString )
   {

      tpElementoTabela * pElementoTabela ;

      TBS_tpCondRet CondRet = TBS_CondRetOK ;

      char * pStringTabela = NULL ;

      /* Controlar par�metros de obter string */

         assert(  idString  >= 0 ) ;
         assert(( dimString >  TBS_MIN_LENGTH ) && ( dimString <= TBS_MAX_LENGTH )) ;
         assert(  pString   != NULL ) ;

      /* Obter ponteiro para o string na tabela */

         pElementoTabela      = ProcurarIdString( idString ) ;

         if ( pElementoTabela == NULL )
         {
            CondRet = TBS_CondRetNaoExiste ;
            pElementoTabela = ProcurarIdString( ID_NAO_ENCONTROU ) ;
         } /* if */

      /* Tratar erro de forma��o da tabela */

         if ( pElementoTabela == NULL )
         {

            strcpy( pString , STRING_ERRO ) ;
            return TBS_CondRetErroTabela ;

         } /* fim ativa: Tratar erro de forma��o da tabela */

      /* Controlar tamanho no buffer receptor */

         dimString -- ; /* assegurar espa�o para o 0 final */

         if ( dimString >= pElementoTabela->tamString )
         {
            dimString = pElementoTabela->tamString ;
         } else
         {
            CondRet   = TBS_CondRetTruncado ;
         } /* if */

      /* Copiar string para o destino */

         pStringTabela = vtpStringoes[ pElementoTabela->inxSubTabela ]
                                   + pElementoTabela->inxOrigemString ;

         memcpy( pString , pStringTabela , dimString ) ;
         pString[ dimString ] = 0 ;

      return CondRet ;

   } /* Fim fun��o: TBS Obter um string contido na tabela */

/***************************************************************************
*
*  Fun��o: TBS Teste - deturpar idString
*  ****/

   void TBS_TesteDeturparIdString( int idString , int inxElemento )
   {

      assert(( 0 <= inxElemento ) && ( inxElemento < DIM_TABELA_STRING )) ;

      vtTabelaPesquisa[ inxElemento ].idString = idString ;

   } /* Fim fun��o: TBS Teste - deturpar idString */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TBS Procurar string na tabela
*
*  $ED Descri��o da fun��o
*     Ver "TabelaString.tabstr" para detalhes quanto � organiza��o da tabela.
*
*  $EP Par�metros
*     idString - identifica��o do string a procurar
*
*  $FV Valor retornado
*     ponteiro para o elemento da tabela que cont�m o string procurado.
*     Ser� NULL se n�o encontrado.
*
***********************************************************************/

   tpElementoTabela * ProcurarIdString( long idString )
   {

      int Inf  ,
          Sup  ,
          Meio  ;

      tpElementoTabela * pElem = NULL ;

      Inf = 0 ;
      Sup = DIM_TABELA_STRING ;

      while ( Inf <= Sup )
      {
         Meio  = ( Inf + Sup ) / 2 ;
         pElem = &( vtTabelaPesquisa[ Meio ] );
         if ( pElem->idString == idString )
         {
            return pElem ;
         } /* if */
         if ( idString < pElem->idString )
         {
            Sup = Meio - 1 ;
         } else {
            Inf = Meio + 1 ;
         } /* if */

      } /* while */

      return NULL ;

   } /* Fim fun��o: TBS Procurar string na tabela */

/********** Fim do m�dulo de implementa��o: TBS  Tabela de strings **********/

