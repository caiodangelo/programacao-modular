/***************************************************************************
*  $MCI Módulo de implementação: Módulo grafo
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   cev   19/09/2009 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "GRAFO.H"
#include "VERTICE.H"
#include "LISTA.H"


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de um grafo
*
*
*  $ED Descrição do tipo
*     A cabeça do grafo é o ponto de acesso para um determinado grafo.
*     ...
*
***********************************************************************/

   typedef struct GRA_tgGrafo {

        LIS_tppLista ListaVertices ;
            /* Ponteiro para a lista de vértices do grafo 
			*
			*$EED Assertivas estruturais
			* ... */	 
		LIS_tppLista ListaOrigens ;
			/* Ponteiro para a lista de vértices do grafo 
			*
			*$EED Assertivas estruturais
			* ... */	 
		VER_tppVertice VerticeCorrente;
			  /* Ponteiro para o vértice corrente 
			  *
			  *$EED Assertivas estruturais
			  * ... */

   } GRA_tpGrafo ;
/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

  VER_tppVertice ObtemVerticeComId ( GRA_tppGrafo pGrafo, int idVertice );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA Criar grafo
*  ****/

   GRA_tpCondRet GRA_CriarGrafo ( GRA_tppGrafo * ppGrafo ){

	  if ( *ppGrafo != NULL )
      {
         GRA_DestruirGrafo( *ppGrafo ) ;
      } /* if */

      *ppGrafo = ( GRA_tppGrafo ) malloc( sizeof( GRA_tpGrafo )) ;
      if ( *ppGrafo == NULL )
      {
         return GRA_CondRetFaltouMemoria ;
      } /* if */

      (*ppGrafo)->ListaVertices = LIS_CriarLista( VER_DestruirVertice );
	  
	  (*ppGrafo)->VerticeCorrente = NULL;

	  return GRA_CondRetOK ;

} /* Fim função: GRA Criar grafo */

/***************************************************************************
*
*  Função: GRA Inserir vértice
*  ****/

   GRA_tpCondRet GRA_InserirVertice ( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ){

	   GRA_tpCondRet CondRetGrafo;
	   LIS_tpCondRet CondRetLista;
	   VER_tpCondRet CondRetVertice;

	   int IdVertice;

	   if( pGrafo == NULL )
	   {
		  CondRetGrafo = GRA_CriarGrafo( &pGrafo );

		  if( CondRetGrafo != GRA_CondRetOK )
		  {
			  return CondRetGrafo;
		  } /* if */

	   } /* if */

	   CondRetVertice = VER_ObterId ( pVertice, &IdVertice );

	   if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeNaoExiste;
	   } /* if */

	   if ( ObtemVerticeComId( pGrafo, IdVertice )!= NULL ){
		    return GRA_CondRetIdJahExiste;
	   }/* if */


	   CondRetLista = LIS_InserirElementoAntes( (pGrafo->ListaVertices) , &pVertice );

	   if( CondRetLista == LIS_CondRetOK )
	   {
		   (pGrafo->VerticeCorrente) = pVertice;
		   return GRA_CondRetOK;
	   }
	   else
	   {
		   return GRA_CondRetFaltouMemoria;
	   }

} /* Fim função: GRA Inserir vértice */

/***************************************************************************
*
*  Função: GRA Excluir vértice 
*  ****/

   GRA_tpCondRet GRA_ExcluirVertice ( GRA_tppGrafo pGrafo ){

	   LIS_tpCondRet CondRetLista;

	   if( pGrafo == NULL )
	   {
		  return GRA_CondRetGrafoVazio;
	   } /* if */

	   CondRetLista = LIS_ExcluirElemento( pGrafo->ListaVertices ) ;

	   if( CondRetLista == LIS_CondRetOK )
	   {
		   return GRA_CondRetOK;
	   }
	   else
	   {
		   return GRA_CondRetGrafoVazio;
	   } /* if */

} /* Fim função: GRA Excluir vértice */


   /***************************************************************************
*
*  Função: GRA_MarcarComoOrigem
*  ****/

   GRA_tpCondRet GRA_MarcarComoOrigem ( GRA_tppGrafo pGrafo, int idVertice ){

		LIS_tpCondRet CondRetLista;
		VER_tppVertice pVertice;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */

		pVertice = ObtemVerticeComId( pGrafo, idVertice ) ;

		if ( pVertice == NULL){
			return GRA_CondRetIdInvalido;  /*Conferir essa CONDRET */
		}/* if */

		CondRetLista = LIS_InserirElementoAntes( pGrafo->ListaOrigens , pVertice ) ;

		if ( CondRetLista == LIS_CondRetFaltouMemoria){
			return GRA_CondRetFaltouMemoria ;
		} else{
			return GRA_CondRetOK ;
		}/* if */

} /* Fim função: GRA_MarcarComoOrigem */


   /***************************************************************************
*
*  Função: GRA_DesmarcarComoOrigem
*  ****/

   GRA_tpCondRet GRA_DesmarcarComoOrigem ( GRA_tppGrafo pGrafo, int idVertice ){

		LIS_tpCondRet CondRetLista;
		
		VER_tppVertice pVertice;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */

			
		pVertice = ObtemVerticeComId( pGrafo, idVertice ) ;

		if ( pVertice == NULL){
			return GRA_CondRetVerticeNaoEhOrigem ;
		}/* if */
	
		CondRetLista = LIS_ProcurarValor( pGrafo->ListaOrigens , &pVertice );
		
		if ( CondRetLista == LIS_CondRetNaoAchou || CondRetLista == LIS_CondRetListaVazia ){
			return GRA_CondRetVerticeNaoEhOrigem ;
		} /* if */

		CondRetLista = LIS_ExcluirElemento( pGrafo->ListaOrigens) ;

		if ( CondRetLista == LIS_CondRetListaVazia ){
			return GRA_CondRetVerticeNaoEhOrigem ;
		} /* if */
	
		return GRA_CondRetOK;

} /* Fim função: GRA_DesmarcarComoOrigem */

/***************************************************************************
*
*  Função: GRA Inserir aresta
*  ****/

   GRA_tpCondRet GRA_InserirAresta ( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
									int idVerticeDestino ){

		VER_tpCondRet CondRetVertice;
		VER_tppVertice pVerticeOrigem;
		VER_tppVertice pVerticeDestino;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
	
		pVerticeOrigem = ObtemVerticeComId( pGrafo, idVerticeOrigem ) ;
		pVerticeDestino = ObtemVerticeComId( pGrafo, idVerticeDestino ) ;

		if ( pVerticeOrigem == NULL || pVerticeDestino == NULL ){
			return GRA_CondRetVerticeInexistente;
		}/* if */
		
		CondRetVertice = VER_AdicionarSucessor( pVerticeOrigem, pVerticeDestino ) ;

		if ( CondRetVertice == VER_CondRetFaltouMemoria ){
			return GRA_CondRetFaltouMemoria;
		} /* if */
		if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeInexistente;
		} /* if */
		if ( CondRetVertice == VER_CondRetVerticeSucessorJahExiste ){
			return GRA_CondRetArestaJaExiste;
		}else {
			return GRA_CondRetOK ;
		} /* if */
	   
} /* Fim função: GRA Inserir aresta */

/***************************************************************************
*
*  Função: GRA Remover aresta
*  ****/

   GRA_tpCondRet GRA_RemoverAresta ( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
									int idVerticeDestino ){

		VER_tppVertice pVerticeOrigem ;
		VER_tppVertice pVerticeDestino ;
		VER_tpCondRet CondRetVertice;
		
		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
		
		pVerticeOrigem = ObtemVerticeComId( pGrafo, idVerticeOrigem ) ;
		pVerticeDestino = ObtemVerticeComId( pGrafo, idVerticeDestino ) ;

		if ( pVerticeOrigem == NULL || pVerticeDestino == NULL ){
			return GRA_CondRetVerticeInexistente;
		}/* if */

		VER_RemoverSucessor( pVerticeOrigem, pVerticeDestino ) ;

		if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeInexistente;
		} /* if */
		if ( CondRetVertice == VER_CondRetVerticeNaoEhSucessor ){
			return GRA_CondRetArestaNaoExiste;
		} else {
			return GRA_CondRetOK ;
		} /* if */
		
} /* Fim função: GRA Remover aresta */


/***************************************************************************
*
*  Função: GRA Exibir grafo
*  ****/

   GRA_tpCondRet GRA_ExibirGrafo ( GRA_tppGrafo pGrafo ){

	    VER_tppVertice pVertice;

		int IdVertice;

	   	if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */

	   IrInicioLista( pGrafo->ListaVertices ) ;
	  
	   do{
		   pVertice = LIS_ObterValor( pGrafo->ListaVertices ) ;

		   if ( VER_ObterId( pVertice, &IdVertice ) == VER_CondRetVerticeNaoExiste ){
			
			   return GRA_CondRetVerticeInexistente;

		   } else {
			    
			   printf("Vertice %d: \nSucessores: \n", IdVertice);
			   ExibeSucessores( pVertice);

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( pGrafo->ListaVertices, 1 )
		     != LIS_CondRetFimLista ) /* do while */

} /* Fim função: GRA Exibir Grafo */

	 
  

/***************************************************************************
*
*  Função: GRA Destruir grafo
*  ****/

   GRA_tpCondRet GRA_DestruirGrafo ( GRA_tppGrafo pGrafo ){

	   if( pGrafo == NULL )
	   {
		   return GRA_CondRetGrafoVazio;
	   } /* if */

	   LIS_DestruirLista(pGrafo->ListaVertices);
	   LIS_DestruirLista(pGrafo->ListaOrigens);
	  
	   free(pGrafo);
	   pGrafo = NULL;

	   return GRA_CondRetOK ;

} /* Fim função: GRA Destruir grafo */


/***************************************************************************
*
*  Função: ObtemVerticeComId
*  ****/

   VER_tppVertice ObtemVerticeComId ( GRA_tppGrafo pGrafo, int IdVertice ){

	   LIS_tpCondRet CondRetLista;
	   VER_tpCondRet CondRetVertice;

	   int IdAuxiliar;  /* CHECAR NOME DESSA VARIÁVEL */
	   VER_tppVertice pVertice;
		
	   if( pGrafo == NULL )
	   {
		   return NULL;
	   } /* if */

	   IrInicioLista( pGrafo->ListaVertices ) ;
	  
	   do{
		   pVertice = LIS_ObterValor( pGrafo->ListaVertices ) ;

		   if ( VER_ObterId( pVertice, &IdAuxiliar ) == VER_CondRetVerticeNaoExiste ){
			
			   return NULL;

		   } else {
			    
							   
			   if ( IdVertice == IdAuxiliar){
				
					return pVertice; 

			   } /* if */ 

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( pGrafo->ListaVertices, 1 )
		     != LIS_CondRetFimLista ) /* do while */

	   return NULL;

} /* Fim função: ObtemVerticeComId */



/***************************************************************************
*
*  Função: ExibeSucessores
*  ****/

   void ExibeSucessores ( VER_tppVertice pVertice){

		VER_tpCondRet CondRetVertice;
		LIS_tpCondRet CondRetLista;

		int IdVertice;

		LIS_tppLista ListaSucessores = VER_ObterListaSucessores ( pVertice);

		if ( ListaSucessores == NULL ){
			return;
		}/* if */

		IrInicioLista( ListaSucessores ) ;

		do{
		   
			pVertice = LIS_ObterValor( ListaSucessores ) ;

		   if ( VER_ObterId( pVertice, &IdVertice ) == VER_CondRetVerticeNaoExiste ){
			
			   return GRA_CondRetVerticeInexistente;

		   } else {
			    
			   printf(" %d ", IdVertice);

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( ListaSucessores, 1 )
		     != LIS_CondRetFimLista ) /* do while */

		
   return;


} /* Fim função: ExibeSucessores */

		
/********** Fim do módulo de implementação: Módulo grafo **********/