/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
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
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

   void LIS_CriarListaDeListas( void ) ;

   LIS_tpCondRet VerificarElemento( tpElemLista * pElemento ) ;

/*****  Dados encapsulados no módulo  *****/

   LIS_tppLista pListaDeListas = NULL;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
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

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
         CNT_CONTAR( "LIS_DestruirLista" ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
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

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
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

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_InserirElementoApos" ) ;
      #endif

      /* Criar elemento a inserir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

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

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
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

      /* Desencadeia à esquerda */

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

      /* Desencadeia à direita */

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

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
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

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_IrInicioLista" ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_IrFinalLista" ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
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

      /* Tratar avançar para frente */

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

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {
					#ifdef _DEBUG
		    				CNT_CONTAR( "LIS_AvancarElementoCorrente - numElem é Menor Que Zero" ) ;
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

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
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

   } /* Fim função: LIS  &Procurar elemento contendo valor */

/***************************************************************************
*
*  Função: LIS  &Deturpar Lista
*  ****/

   LIS_tpCondRet LIS_DeturparLista( LIS_tppLista pLista ,
                                    LIS_tpModosDeturpacao modoDeturp ,
									int numElem							)
   {

   tpElemLista lixo;
   int outroTipo;

   if( numElem < 0 ){
			numElem = 0;
	   }

   
   if( modoDeturp == DeturpaElimElemCorr ){
	   /* Elimina o elemento corrente da lista */
	   free(pLista->pElemCorr);

	   }
   else if( modoDeturp == DeturpaNuloPtProximo ){
	   /* Atribui NULL ao ponteiro para o próximo nó */
	   ((pLista->pElemCorr)->pProx) = NULL;

	   }
   else if( modoDeturp == DeturpaNuloPtAnterior ){
	   /* Atribui NULL ao ponteiro para o nó anterior */
	   ((pLista->pElemCorr)->pAnt) = NULL;

	   }
   else if( modoDeturp == DeturpaLixoPtProximo ){
	   /* Atribui lixo ao ponteiro para o próximo nó */
	   ((pLista->pElemCorr)->pProx) = &lixo;

	   }
   else if( modoDeturp == DeturpaLixoPtAnterior ){
	   /* Atribui lixo ao ponteiro o nó anterior */
	   ((pLista->pElemCorr)->pAnt) = &lixo;

	   }
   else if( modoDeturp == DeturpaPtConteudo ){
	   /* Atribui NULL ao ponteiro para o conteúdo do nó */
	   ((pLista->pElemCorr)->pValor) = NULL;

	   }
   else if( modoDeturp == DeturpaTipoPtEstrutura ){
	   /* Altera o tipo de estrutura apontado no nó */
	   (pLista->pElemCorr) = &outroTipo;

	   }
   else if( modoDeturp == DeturpaDesencadeia ){
	   /* Desencadeia nó sem liberá-lo com free */

	   (((pLista->pElemCorr)->pAnt)->pProx) = ((pLista->pElemCorr)->pProx);
	   (((pLista->pElemCorr)->pProx)->pAnt) = ((pLista->pElemCorr)->pAnt);
	   ((pLista->pElemCorr)->pProx) = NULL;
	   ((pLista->pElemCorr)->pAnt) = NULL;

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
	   /* Altera o valor numElem na cabeça da lista */
	   (pLista->numElem) = numElem;

	   }
   else if( modoDeturp == DeturpaOrigem ){
	   (pLista->pOrigemLista) = (pLista->pElemCorr);

	   }
   else{
	   return LIS_CondRetParametroInvalido;

	   }
   
	return LIS_CondRetOK;

   } /* Fim função: LIS  &Deturpar Lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
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

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
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

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/*****  Código das funções de verificação do módulo  *****/


#ifdef _DEBUG

/***************************************************************************
*
*  Função: ARV  &Verificar uma Lista
*  ****/

   LIS_tpCondRet LIS_VerificarLista( void * pListaParm )
   {

      LIS_tppLista pLista = NULL ;

      if ( LIS_VerificarCabeca( pListaParm ) != LIS_CondRetOK )
      {
         return LIS_CondRetErroEstrutural ;
      } /* if */

      CED_MarcarEspacoAtivo( pListaParm ) ;

      pLista = ( LIS_tppLista ) ( pListaParm ) ;

      return VerificarElemento( pLista->pOrigemLista ) ;

   } /* Fim função: LIS  &Verificar uma lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar cabeça
*  ****/

   int LIS_VerificarCabeca( void * pCabecaParm )
   {

      LIS_tppLista pLista = NULL ;
	  tpElemLista * pElem = NULL ;
	  int contador = 0 ;
	  int numFalhas = 0;

      /* Verifica o tipo do espaço */

         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            numFalhas++ ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            numFalhas++;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espaço de dados não é cabeça de lista." ) != TST_CondRetOK )
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

		 /* Verifica número de elementos */

		 if ( pLista->pOrigemLista == NULL )
		 {
			 if ( TST_CompararInt( pLista->numElem , 0 ,
                 "Lista vazia com numero de elementos diferente de zero" ) != TST_CondRetOK )
            {
               numFalhas++;
            } /* if */
		 }
		 else
		 {
			 pElem = pLista->pOrigemLista ;
			 while ( pElem != NULL )
			 {
				 contador++ ;
				 if ( contador > pLista->numElem )
				 {
					 break;
				 }
				 pElem = pElem->pProx ;
			 }
			 if ( TST_CompararInt( pLista->numElem , contador ,
                 "Numero de elementos errado" ) != TST_CondRetOK )
            {
               numFalhas++;
            } /* if */
		 }

		 /* Verifica se elemento corrente pertence à lista */

		 if ( pLista->pElemCorr != NULL )
		 {
			 pElem = pLista->pOrigemLista ;
			 while ( pElem != NULL )
			 {
				 if ( pElem == pLista->pElemCorr )
				 {
					 break ;
				 }
				 pElem = pElem->pProx ;
			 }
			 if ( TST_CompararPonteiro( pLista->pElemCorr , pElem ,
                 "Elemento corrente nao pertence a lista" ) != TST_CondRetOK )
			 {
				 numFalhas++;
			 } /* if */

		 }

		 return numFalhas ;

   } /* Fim função: LIS  &Verificar cabeça */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar um elemento
*  ****/

   LIS_tpCondRet LIS_VerificarElemento( void * pElemParm )
   {

      tpElemLista * pElemento     = NULL ;

         if ( pElemParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
            return LIS_CondRetErroEstrutural ;

         } /* if */

         if ( ! CED_VerificarEspaco( pElemParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetErroEstrutural ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoElemento ,
              CED_ObterTipoEspaco( pElemParm ) ,
              "Tipo do espaço de dados não é elemento de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutural ;
         } /* if */

         pElemento     = ( tpElemLista * )( pElemParm ) ;

      /* Verificar próximo */

         if ( pElemento->pProx != NULL  )
         {
            if ( TST_CompararPonteiro( pElemento , pElemento->pProx->pAnt ,
                 "Anterior do próximo não é o próprio." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutural ;
            } /* if */
         }

      /* Verificar Anterior */

         if ( pElemento->pAnt != NULL )
         {
            if ( TST_CompararPonteiro( pElemento , pElemento->pAnt->pProx ,
                 "Próximo do anterior não é o próprio." ) != TST_CondRetOK )
            {
               return LIS_CondRetErroEstrutural ;
            } /* if */
         } /* if */

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar um elemento da lista */

#endif

/***********************************************************************
*
*  $FC Função: LIS  -Explorar verificando os elementos de uma lista
*
*  $ED Descrição da função
*     Percorre recursivamente a lista verificando os elementos à medida que forem
*     visitados. Caso seja encontrado alguma falha, a verificação será
*     suspensa. Portanto, no caso de falha, é possível que nem todos
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

   } /* Fim função: LIS  -Explorar verificando os nós de uma árvore */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

