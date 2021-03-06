/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
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
*       4.00   cev   15/09/2009 Extens�o para m�ltiplas �rvores n-�rias
*                               e adi��o de novas fun��es.
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para o primeiro filho.
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para o primeiro irm�o.
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X->pNoPai */

         char Valor ;
               /* Valor do n� */

		 ARV_tpModoVisita Modo;
				/* Modo de visita do n� */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da �rvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o n� corrente da �rvore */

   } tpArvore ;
/*****  Dados encapsulados no m�dulo  *****/

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore, char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   static ARV_tpCondRet MarcarVisitado ( tpArvore * pArvore, ARV_tpModoVisita Modo ) ;

   static void ExibeArvore( tpNoArvore * pNo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( tpArvore ** ppArvore )
   {

      if ( *ppArvore != NULL )
      {
         ARV_DestruirArvore( ppArvore ) ;
      } /* if */

      *ppArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( *ppArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      (*ppArvore)->pNoRaiz = NULL ;
      (*ppArvore)->pNoCorr = NULL ;

	  return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Criar �rvore */

/***************************************************************************
*
*  Fun��o: ARV Destruir �rvore
*  ****/

   void ARV_DestruirArvore( tpArvore ** ppArvore )
   {

      if ( *ppArvore != NULL )
      {
         if ( (*ppArvore)->pNoRaiz != NULL )
         {
            DestroiArvore( (*ppArvore)->pNoRaiz ) ;
         } /* if */
         free( *ppArvore ) ;
		 *ppArvore = NULL ;
      } /* if */

   } /* Fim fun��o: ARV Destruir �rvore */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho 
*  ****/

   ARV_tpCondRet ARV_InserirFilho( tpArvore * pArvore, char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;/* N� corrente */
      tpNoArvore * pNo = NULL;/* N� filho */

      /* Tratar vazio */

         CondRet = CriarNoRaiz( pArvore, ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n�  */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
             
		 /* Se n�o for folha */
         if ( pCorr->pNoEsq != NULL )
		 {
			 pNo = pCorr->pNoEsq ;
			 while ( pNo->pNoDir != NULL )
			 {
				 pNo = pNo->pNoDir ; /* Vai para o fim da lista de filhos */
			 } /* while */
			pNo->pNoDir = CriarNo ( ValorParm ) ;
			if ( pNo->pNoDir == NULL )
			{
				return ARV_CondRetFaltouMemoria ;
			} /* if */
			pNo			= pNo->pNoDir;
			pNo->pNoPai = pCorr ;
		} /* if */

		 /* Se for folha */
		 else if ( pCorr->pNoEsq == NULL )
		 {
			pNo = CriarNo ( ValorParm ) ;
			if ( pNo == NULL )
			{
				return ARV_CondRetFaltouMemoria ;
			} /* if */
			pNo->pNoPai	     = pCorr ;
			pCorr->pNoEsq    = pNo ;			
		 }/* if */

         pArvore->pNoCorr = pNo ;
         return ARV_CondRetOK ;
   } /* Fim fun��o: ARV Adicionar filho */



/***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
*  ****/

   ARV_tpCondRet ARV_IrPai( tpArvore * pArvore )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim fun��o: ARV Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� Filho
*  ****/

   ARV_tpCondRet ARV_IrNoFilho( tpArvore * pArvore )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� filho */

/***************************************************************************
*
*  Fun��o: ARV Ir para irm�o
*  ****/

   ARV_tpCondRet ARV_IrNoIrmao( tpArvore * pArvore )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiIrmao ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� irm�o */

/***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( tpArvore * pArvore, char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Obter valor corrente */

/***********************************************************************
*
*  $FC Fun��o: ARV Exibir �rvore
*
*
***********************************************************************/

	ARV_tpCondRet ARV_ExibirArvore( tpArvore * pArvore )
	{
		tpNoArvore * pCorr ;	
	
		if ( pArvore == NULL )
		{
			printf("Arvore nao existe");
			return ARV_CondRetArvoreNaoExiste ;
		} /* if */
		pCorr = pArvore->pNoRaiz ;
		if ( pCorr == NULL )
		{
			printf("Arvore vazia");
			return ARV_CondRetArvoreVazia ;
		} /* if */
		else{
			printf(" (");
			ExibeArvore( pCorr ) ;
			printf(" )\n");
			
		}

		
		return ARV_CondRetOK;

	} /* Fim fun��o: ARV Exibir �rvore */
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim fun��o: ARV Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore, char ValorParm )
   {

      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste;
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim fun��o: ARV Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {
	   
      if ( pNo->pNoEsq != NULL )
      {
		  DestroiArvore( pNo->pNoEsq ) ;
      } /* if */
	  
      if ( pNo->pNoDir != NULL )
      {
		  DestroiArvore( pNo->pNoDir ) ;
      } /* if */
	  
      free( pNo ) ;
	  
   } /* Fim fun��o: ARV Destruir a estrutura da �rvore */

/***********************************************************************
*
*  $FC Fun��o: ARV Marcar N�
*
*
***********************************************************************/

   ARV_tpCondRet MarcarVisitado( tpArvore * pArvore, ARV_tpModoVisita Modo )
   {

      if ( pArvore == NULL )
	  {
		  return ARV_CondRetArvoreNaoExiste;
	  }
	  else if ( pArvore->pNoCorr == NULL )
	  {
		  return ARV_CondRetArvoreVazia;
	  }
	  else
	  {
		  (pArvore->pNoCorr)->Modo = Modo;
		  return ARV_CondRetOK;
	  }

   } /* Fim fun��o: ARV Marcar N� */

/***********************************************************************
*
*  $FC Fun��o: ARV Exibir �rvore Auxiliar
*
*
***********************************************************************/

	void ExibeArvore( tpNoArvore * pNo )
	{
		printf(" %c", pNo->Valor) ;
		if ( pNo->pNoEsq != NULL )
		{
			printf(" (") ; /* entrou no primeiro filho da lista de irm�os */
			ExibeArvore( pNo->pNoEsq ) ;
			printf(" )") ; /* saiu da lista de irm�os */
		} /* if */

		if ( pNo->pNoDir != NULL )
		{
			ExibeArvore( pNo->pNoDir ) ;			
		} /* if */

	} /* Fim fun��o: ARV Exibir �rvore */
/********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/

