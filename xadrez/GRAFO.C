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

   typedef struct tgGrafo {

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
		tpVertice * VerticeCorrente;
			  /* Ponteiro para o vértice corrente 
			  *
			  *$EED Assertivas estruturais
			  * ... */

   } tpGrafo ;
/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

  tpVertice * ObtemVerticeComId ( tpGrafo * pGrafo, int idVertice );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA Criar grafo
*  ****/

   GRA_tpCondRet GRA_CriarGrafo ( tpGrafo ** ppGrafo ){

	  if ( *ppGrafo != NULL )
      {
         GRA_DestruirGrafo( *ppGrafo ) ;
      } /* if */

      *ppGrafo = ( tpGrafo * ) malloc( sizeof( tpGrafo )) ;
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

   GRA_tpCondRet GRA_InserirVertice ( tpGrafo * pGrafo, tpVertice * pVertice ){

	   GRA_tpCondRet tempGrafo;
	   LIS_tpCondRet tempLista;

	   if( pGrafo == NULL )
	   {
		  tempGrafo = GRA_CriarGrafo( &pGrafo );

		  if( tempGrafo != GRA_CondRetOK )
		  {
			  return tempGrafo;
		  } /* if */

	   } /* if */

	   tempLista = LIS_InserirElementoAntes( (pGrafo->ListaVertices) , &pVertice );

	   if( tempLista == LIS_CondRetOK )
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

   GRA_tpCondRet GRA_ExcluirVertice ( tpGrafo * pGrafo ){

	   LIS_tpCondRet tempLista;

	   if( pGrafo == NULL )
	   {
		  return GRA_CondRetGrafoVazio;
	   } /* if */

	   tempLista = LIS_ExcluirElemento( pGrafo->ListaVertices ) ;

	   if( tempLista == LIS_CondRetOK )
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

   GRA_tpCondRet GRA_MarcarComoOrigem ( tpGrafo * pGrafo, int idVertice ){

		LIS_tpCondRet tempLista;
		tpVertice * pVertice;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
	
		pVertice = ObtemVerticeComId( pGrafo, idVertice ) ;

		if ( pVertice == NULL){
			return GRA_CondRetVerticeInexistente;
		}/* if */

		tempLista = LIS_InserirElementoAntes( pGrafo->ListaOrigens , pVertice ) ;

		if ( tempLista == LIS_CondRetFaltouMemoria){
			return GRA_CondRetFaltouMemoria ;
		} 
		else{
			return GRA_CondRetOK ;
		}/* if */

} /* Fim função: GRA_MarcarComoOrigem */


   /***************************************************************************
*
*  Função: GRA_DesmarcarComoOrigem
*  ****/

   GRA_tpCondRet GRA_DesmarcarComoOrigem ( tpGrafo * pGrafo, int idVertice ){

		LIS_tpCondRet tempLista;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
	
		tempLista = LIS_ProcurarValor( pGrafo->ListaOrigens , &idVertice );
		
		if ( tempLista == LIS_CondRetNaoAchou || tempLista == LIS_CondRetListaVazia ){
			return GRA_CondRetVerticeNaoEhOrigem ;
		} /* if */

		tempLista = LIS_ExcluirElemento( pGrafo->ListaOrigens) ;

		if ( tempLista == LIS_CondRetListaVazia ){
			return GRA_CondRetVerticeNaoEhOrigem ;
		} /* if */
	
		return GRA_CondRetOK;

} /* Fim função: GRA_DesmarcarComoOrigem */

/***************************************************************************
*
*  Função: GRA Inserir aresta
*  ****/

   GRA_tpCondRet GRA_InserirAresta ( tpGrafo * pGrafo, int idVerticeOrigem, 
									int idVerticeDestino ){

		VER_tpCondRet tempVertice;
		tpVertice * pVerticeOrigem;
		tpVertice * pVerticeDestino;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
	
		pVerticeOrigem = ObtemVerticeComId( pGrafo, idVerticeOrigem ) ;
		pVerticeDestino = ObtemVerticeComId( pGrafo, idVerticeDestino ) ;

		if ( pVerticeOrigem == NULL || pVerticeDestino == NULL ){
			return GRA_CondRetVerticeInexistente;
		}/* if */
		
		tempVertice = VER_AdicionarSucessor( pVerticeOrigem, pVerticeDestino ) ;

		if ( tempVertice == VER_CondRetFaltouMemoria ){
			return GRA_CondRetFaltouMemoria;
		} /* if */
		if ( tempVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeInexistente;
		} /* if */
		if ( tempVertice == VER_CondRetVerticeSucessorJahExiste ){
			return GRA_CondRetArestaJaExiste;
		}else {
			return GRA_CondRetOK ;
		} /* if */
	   
} /* Fim função: GRA Inserir aresta */

/***************************************************************************
*
*  Função: GRA Remover aresta
*  ****/

   GRA_tpCondRet GRA_RemoverAresta ( tpGrafo * pGrafo, int idVerticeOrigem, 
									int idVerticeDestino ){

		tpVertice * pVerticeOrigem ;
		tpVertice * pVerticeDestino ;
		VER_tpCondRet tempVertice;
		
		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
		
		pVerticeOrigem = ObtemVerticeComId( pGrafo, idVerticeOrigem ) ;
		pVerticeDestino = ObtemVerticeComId( pGrafo, idVerticeDestino ) ;

		if ( pVerticeOrigem == NULL || pVerticeDestino == NULL ){
			return GRA_CondRetVerticeInexistente;
		}/* if */

		tempVertice = VER_RemoverSucessor( pVerticeOrigem, pVerticeDestino ) ;

		if ( tempVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeInexistente;
		} /* if */
		if ( tempVertice == VER_CondRetVerticeNaoEhSucessor ){
			return GRA_CondRetArestaNaoExiste;
		} else {
			return GRA_CondRetOK ;
		} /* if */
		
} /* Fim função: GRA Remover aresta */


/***************************************************************************
*
*  Função: GRA Exibir grafo
*  ****/

   GRA_tpCondRet GRA_ExibirGrafo ( tpGrafo * pGrafo ){
		return GRA_CondRetOK;
   } /* Fim função: GRA Exibir Grafo */
  

/***************************************************************************
*
*  Função: GRA Destruir grafo
*  ****/

   GRA_tpCondRet GRA_DestruirGrafo ( tpGrafo * pGrafo ){

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

   tpVertice * ObtemVerticeComId ( tpGrafo * pGrafo, int idVertice ){

		LIS_tpCondRet tempLista;
	   
		tempLista = LIS_ProcurarValor( pGrafo->ListaVertices , &idVertice );
		if ( tempLista != LIS_CondRetOK ){
			return NULL;
		}/* if */

		return LIS_ObterValor( pGrafo->ListaVertices );


} /* Fim função: ObtemVerticeComId */



		
/********** Fim do módulo de implementação: Módulo grafo **********/