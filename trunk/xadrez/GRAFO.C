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
*       1.00   avs   19/09/2009 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "GRAFO.H"
#include "VERTICE.H"
#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor do vértice de um grafo
*
*
*  $ED Descrição do tipo
*     O vértice de um grafo é a estrutura mais elementar do grafo.
*     ...
*
***********************************************************************/

   typedef struct tgVerticeGrafo {

         LIS_tppLista * Sucessores ;
               /* Ponteiro para a lista de vértices que são atingidos
			   *
			   *$EED Assertivas estruturais
			   * ... */

         LIS_tppLista * Antecessores ;
               /* Ponteiro para a lista de vértices que atingem
			   *
			   *$EED Assertivas estruturais
			   * ... */

		 void * Nome;
			   /* Nome do Vértice */

   } tpVerticeGrafo ;

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

         LIS_tppLista * Vertices ;
               /* Ponteiro para a lista de vértices do grafo 
			   *
			   *$EED Assertivas estruturais
			   * ... */	 

		 //tpVerticeGrafo * VerticeCorrente;
			  /* Ponteiro para o vértice corrente 
			  *
			  *$EED Assertivas estruturais
			  * ... */

   } tpGrafo ;
/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

  

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA Criar grafo
*  ****/

   GRA_tpCondRet GRA_CriarGrafo ( tpGrafo ** ppGrafo ){

	    if ( *ppGrafo != NULL )
      {
         GRA_DestruirGrafo( &ppGrafo ) ;
      } /* if */

      *ppGrafo = ( tpGrafo * ) malloc( sizeof( tpGrafo )) ;
      if ( *ppGrafo == NULL )
      {
         return GRA_CondRetFaltouMemoria ;
      } /* if */

      (*ppGrafo)->Vertices = LIS_CriarLista(NULL);/* criar função de destruição de elementos */
	  //(*ppGrafo)->VerticeCorrente = NULL;

	  return GRA_CondRetOK ;

} /* Fim função: GRA Criar grafo */

/***************************************************************************
*
*  Função: GRA Inserir vértice
*  ****/

   GRA_tpCondRet GRA_InserirVertice ( tpGrafo * pGrafo, void * pVertice ){

	   GRA_tpCondRet tempGrafo;
	   LIS_tpCondRet tempLista;

	   //pVertice = ( tpVerticeGrafo * ) malloc( sizeof( tpVerticeGrafo )) ;

	   if( pGrafo == NULL )
	   {
		  tempGrafo = GRA_CriarGrafo(pGrafo);

		  if( tempGrafo != GRA_CondRetOK )
		  {
			  return tempGrafo;
		  } /* if */

	   } /* if */

	   tempLista = LIS_InserirElementoAntes( (pGrafo->Vertices) , &pVertice );

	   if( tempLista == LIS_CondRetOK )
	   {
		   //(pGrafo->VerticeCorrente) = (pGrafo->Vertices);
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

	   GRA_tpCondRet tempGrafo;
	   LIS_tpCondRet tempLista;

	   if( pGrafo == NULL )
	   {
		  return GRA_CondRetGrafoVazio;
	   } /* if */

	   tempLista = LIS_ExcluirElemento( pGrafo->Vertices ) ;

	   if( tempLista == LIS_CondRetOK )
	   {
		   return GRA_CondRetOK;
	   }
	   else
	   {
		   return GRA_CondRetGrafoVazio;
	   }

} /* Fim função: GRA Excluir vértice */



/***************************************************************************
*
*  Função: GRA Inserir aresta
*  ****/

   GRA_tpCondRet GRA_InserirAresta ( tpGrafo * pGrafo, void * pVerticeOrigem, void * pVerticeDestino ){
	   
} /* Fim função: GRA Inserir aresta */

/***************************************************************************
*
*  Função: GRA Remover aresta
*  ****/

   GRA_tpCondRet GRA_RemoverAresta ( tpGrafo * pGrafo, void * pVerticeOrigem, void * pVerticeDestino ){

	   
} /* Fim função: GRA Remover aresta */

/***************************************************************************
*
*  Função: GRA Exibir grafo
*  ****/

   GRA_tpCondRet GRA_ExibirGrafo ( tpGrafo * pGrafo ){

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
	   LIS_DestruirLista(pGrafo->Vertices);
	   //pGrafo->VerticeCorrente = NULL;
	   free(pGrafo);
	   pGrafo = NULL;

	   return GRA_CondRetOK ;

} /* Fim função: GRA Destruir grafo */
		
/********** Fim do módulo de implementação: Módulo grafo **********/