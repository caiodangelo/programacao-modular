/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
#include "Conta.h"
#include "CESPDIN.H"
#include   "..\\Tabelas\\IdTiposEspaco.def"
#include "generico.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } LIS_tpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

   void LIS_CriarListaDeListas( void ) ;

   LIS_tpCondRet VerificarElemento( tpElemLista * pElemento ) ;

/*****  Dados encapsulados no m�dulo  *****/

   LIS_tppLista pListaDeListas = NULL;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {
	   
	   LIS_tpLista * pLista = NULL ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista" ) ;
      #endif

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
      #endif

      return pLista ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
         CNT_CONTAR( "LIS_DestruirLista" ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_EsvaziarLista" ) ;
      #endif

      pElem = pLista->pOrigemLista ;

      while ( pElem != NULL )
      {
		  
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_InserirElementoAntes" ) ;
      #endif

      /* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
		    #ifdef _DEBUG
		    	 CNT_CONTAR( "LIS_InserirElementoAntes - Elemento corrente NULL" ) ;
		    #endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
				#ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_InserirElementoAntes - Elemento no meio da lista" ) ;
				#endif
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
				#ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_InserirElementoAntes - Elemento na origem" ) ;
				#endif
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_InserirElementoApos" ) ;
      #endif

      /* Criar elemento a inserir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
		    #ifdef _DEBUG
		    	 CNT_CONTAR( "LIS_InserirElementoApos - Elemento corrente NULL" ) ;
		    #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
				#ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_InserirElementoApos - Elemento no meio da lista" ) ;
				#endif
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
				#ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_InserirElementoApos - Elemento no fim" ) ;
				#endif
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
		 CNT_CONTAR( "LIS_ExcluirElemento" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		  #ifdef _DEBUG
			 CNT_CONTAR( "LIS_ExcluirElemento - Lista vazia" ) ;
		  #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
			 #ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_ExcluirElemento - Elemento nao tem antecessores" ) ;
			 #endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
 			 #ifdef _DEBUG
		    	 CNT_CONTAR( "LIS_ExcluirElemento - Elemento tem antecessores" ) ;
			 #endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
			 #ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_ExcluirElemento - Elemento nao tem sucessores" ) ;
			 #endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
			 
			 #ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_ExcluirElemento - Elemento tem sucessores" ) ;
			 #endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

		 LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_ObterValor" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
			 #ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_ObterValor - Lista Vazia" ) ;
			 #endif
        return NULL ;
      } /* if */

      return pLista->pElemCorr->pValor ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_IrInicioLista" ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_IrFinalLista" ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_AvancarElementoCorrente" ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
			 #ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_AvancarElementoCorrente - Lista Vazia" ) ;
			 #endif

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {
			 #ifdef _DEBUG
		    		 CNT_CONTAR( "LIS_AvancarElementoCorrente - numElem Maior Que Zero" ) ;
			 #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
					#ifdef _DEBUG
		    				CNT_CONTAR( "LIS_AvancarElementoCorrente - Chegou ao final da Lista, numElem > 0" ) ;
					#endif
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
					#ifdef _DEBUG
		    				CNT_CONTAR( "LIS_AvancarElementoCorrente - Esta no meio da Lista, numElem > 0" ) ;
					#endif

               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {
					#ifdef _DEBUG
		    				CNT_CONTAR( "LIS_AvancarElementoCorrente - numElem � Menor Que Zero" ) ;
					#endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
					#ifdef _DEBUG
		    				CNT_CONTAR( "LIS_AvancarElementoCorrente - Chegou ao final da Lista, numElem < 0" ) ;
					#endif
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
					#ifdef _DEBUG
		    				CNT_CONTAR( "LIS_AvancarElementoCorrente - Esta no meio da Lista, numElem < 0" ) ;
					#endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
		 CNT_CONTAR( "LIS_ProcurarValor" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		    #ifdef _DEBUG
		    	 CNT_CONTAR( "LIS_ProcurarValor - Lista vazia" ) ;
		    #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
		    #ifdef _DEBUG
		    	 CNT_CONTAR( "LIS_ProcurarValor - Valor Encontrado" ) ;
		    #endif
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */
			
		#ifdef _DEBUG
		   	 CNT_CONTAR( "LIS_ProcurarValor - Nao achou" ) ;
		#endif
      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */

/***************************************************************************
*
*  Fun��o: LIS  &Deturpar Lista
*  ****/

   LIS_tpCondRet LIS_DeturparLista( LIS_tppLista pLista ,
                                    LIS_tpModosDeturpacao modoDeturp ,
									int numElem							)
   {

   tpElemLista lixo, *temp;
   int outroTipo;
   temp = pLista->pElemCorr;

   if( numElem < 0 ){
			numElem = 0;
	   }

   
   if( modoDeturp == DeturpaElimElemCorr ){
	   /* Elimina o elemento corrente da lista */
	   (((pLista->pElemCorr)->pAnt)->pProx) = ((pLista->pElemCorr)->pProx);
	   (((pLista->pElemCorr)->pProx)->pAnt) = ((pLista->pElemCorr)->pAnt);
	   free(pLista->pElemCorr);

	   }
   else if( modoDeturp == DeturpaNuloPtProximo ){
	   /* Atribui NULL ao ponteiro para o pr�ximo n� */
	   ((pLista->pElemCorr)->pProx) = NULL;

	   }
   else if( modoDeturp == DeturpaNuloPtAnterior ){
	   /* Atribui NULL ao ponteiro para o n� anterior */
	   ((pLista->pElemCorr)->pAnt) = NULL;

	   }
   else if( modoDeturp == DeturpaLixoPtProximo ){
	   /* Atribui lixo ao ponteiro para o pr�ximo n� */
	   ((pLista->pElemCorr)->pProx) = &lixo;

	   }
   else if( modoDeturp == DeturpaLixoPtAnterior ){
	   /* Atribui lixo ao ponteiro do n� anterior */
	   ((pLista->pElemCorr)->pAnt) = &lixo;

	   }
   else if( modoDeturp == DeturpaPtConteudo ){
	   /* Atribui NULL ao ponteiro para o conte�do do n� */
	   ((pLista->pElemCorr)->pValor) = NULL;

	   }
   else if( modoDeturp == DeturpaTipoPtEstrutura ){
	   /* Altera o tipo de estrutura apontado no n� */
	   (pLista->pElemCorr) = (tpElemLista *) &outroTipo;

	   }
   else if( modoDeturp == DeturpaDesencadeia ){
	   /* Desencadeia n� sem liber�-lo com free */

	   (((pLista->pElemCorr)->pAnt)->pProx) = ((pLista->pElemCorr)->pProx);
	   (((pLista->pElemCorr)->pProx)->pAnt) = ((pLista->pElemCorr)->pAnt);
	   ((pLista->pElemCorr)->pProx) = NULL;
	   ((pLista->pElemCorr)->pAnt) = NULL;
	   (pLista->pElemCorr) = temp;

	   }
   else if( modoDeturp == DeturpaNuloPtCorrente ){
	   /* Atribui NULL ao ponteiro corrente */
	   (pLista->pElemCorr) = NULL;
	   }
   else if( modoDeturp == DeturpaNuloPtOrigem ){
	   /*  Atribui NULL ao ponteiro de origem */
	   (pLista->pOrigemLista) = NULL;
	   }
   else if( modoDeturp == DeturpaNumElem ){
	   /* Altera o valor numElem na cabe�a da lista */
	   (pLista->numElem) = numElem;

	   }
   else if( modoDeturp == DeturpaOrigem ){
	   /* Altera a origem da lista na cabe�a */
	   (pLista->pOrigemLista) = (pLista->pElemCorr);

	   }
   else if( modoDeturp == DeturpaFim ){
	   /* Altera o fim da lista na cabe�a */
	   (pLista->pFimLista) = (pLista->pElemCorr);

	   }
   else{
	   return LIS_CondRetParametroInvalido;

	   }
   
	return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Deturpar Lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElemento ) ;
      #endif

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/*****  C�digo das fun��es de verifica��o do m�dulo  *****/


#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: ARV  &Verificar uma Lista
*  ****/

   int LIS_VerificarLista( void * pListaParm )
   {

      LIS_tppLista pLista = NULL ;
	  tpElemLista * pElemento = NULL ;
	  int numFalhas = 0 ;

      numFalhas = LIS_VerificarCabeca( pListaParm ) ;

      CED_MarcarEspacoAtivo( pListaParm ) ;

      pLista = ( LIS_tppLista ) ( pListaParm ) ;

	  pElemento = pLista->pOrigemLista ;
	  while ( pElemento != NULL )
	  {
		  CED_MarcarEspacoAtivo( pElemento ) ;

		  numFalhas += LIS_VerificarElemento( pElemento ) ;

		  pElemento = pElemento->pProx ;
	  }

      return numFalhas ;

   } /* Fim fun��o: LIS  &Verificar uma lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Verificar cabe�a
*  ****/

   int LIS_VerificarCabeca( void * pCabecaParm )
   {

      LIS_tppLista pLista = NULL ;

	  int numFalhas = 0;

      /* Verifica o tipo do espa�o */

         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabe�a inexistente." ) ;
            numFalhas++ ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            numFalhas++;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espa�o de dados n�o � cabe�a de lista." ) != TST_CondRetOK )
         {
            numFalhas++;
         } /* if */

         pLista = ( LIS_tppLista )( pCabecaParm ) ;

      /* Verifica origem da lista */

         if ( pLista->pOrigemLista != NULL )
         {
            if ( TST_CompararPonteiro( pLista->pOrigemLista->pAnt , NULL ,
                 "Origem possui anterior." ) != TST_CondRetOK )
            {
               numFalhas++;
            } /* if */
         } 

       /* Verifica fim da lista */

         if ( pLista->pFimLista != NULL )
         {
            if ( TST_CompararPonteiro( pLista->pFimLista->pProx , NULL ,
                 "Fim possui sucessor." ) != TST_CondRetOK )
            {
               numFalhas++;
            } /* if */
         } 

		 /* Verifica n�mero de elementos */

		 if ( pLista->pOrigemLista == NULL )
		 {
			 if ( TST_CompararInt( pLista->numElem , 0 ,
                 "Lista vazia com numero de elementos diferente de zero" ) != TST_CondRetOK )
            {
               numFalhas++;
            } /* if */
		 }




		 return numFalhas ;

   } /* Fim fun��o: LIS  &Verificar cabe�a */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Verificar um elemento
*  ****/

   int LIS_VerificarElemento( void * pElemParm )
   {

      tpElemLista * pElemento     = NULL ;
	  int numFalhas = 0 ;

         if ( pElemParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
			numFalhas++;
            return numFalhas ;

         } /* if */

         if ( ! CED_VerificarEspaco( pElemParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            numFalhas++;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoElemento ,
              CED_ObterTipoEspaco( pElemParm ) ,
              "Tipo do espa�o de dados n�o � elemento de lista." ) != TST_CondRetOK )
         {
            numFalhas++ ;
         } /* if */

         pElemento     = ( tpElemLista * )( pElemParm ) ;

      /* Verificar pr�ximo */

         if ( pElemento->pProx != NULL  )
         {
            if ( TST_CompararPonteiro( pElemento , pElemento->pProx->pAnt ,
                 "Anterior do pr�ximo n�o � o pr�prio." ) != TST_CondRetOK )
            {
               numFalhas++ ;
            } /* if */
         }

      /* Verificar Anterior */

         if ( pElemento->pAnt != NULL )
         {
            if ( TST_CompararPonteiro( pElemento , pElemento->pAnt->pProx ,
                 "Pr�ximo do anterior n�o � o pr�prio." ) != TST_CondRetOK )
            {
               numFalhas++ ;
            } /* if */
         } /* if */

      return numFalhas ;

   } /* Fim fun��o: LIS  &Verificar um elemento da lista */

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  -Explorar verificando os elementos de uma lista
*
*  $ED Descri��o da fun��o
*     Percorre recursivamente a lista verificando os elementos � medida que forem
*     visitados. Caso seja encontrado alguma falha, a verifica��o ser�
*     suspensa. Portanto, no caso de falha, � poss�vel que nem todos
*     os elementos da lista sejam visitados.
*
***********************************************************************/

   LIS_tpCondRet VerificarElemento( tpElemLista * pElemento )
   {

      LIS_tpCondRet CondErro = LIS_CondRetOK ;

      if ( pElemento == NULL )
      {
         return LIS_CondRetOK ;
      } /* if */

      CED_MarcarEspacoAtivo( pElemento ) ;

      CondErro = LIS_VerificarElemento( pElemento ) ;

      if ( CondErro == LIS_CondRetOK )
      {
         CondErro = VerificarElemento( pElemento->pProx ) ;
      } /* if */

      return CondErro ;

   } /* Fim fun��o: LIS  -Explorar verificando os n�s de uma �rvore */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

