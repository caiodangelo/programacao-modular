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
*  $TC Tipo de dados: GRA Descritor da cabeça de um grafo
*
*
*  $ED Descrição do tipo
*     A cabeça do grafo é o ponto de acesso para um determinado grafo.
*     ...
*
***********************************************************************/

   typedef struct tgGrafo {

         LIS_tppLista * Origens ;
               /* Ponteiro para a lista de vértices origem
			   *
			   *$EED Assertivas estruturais
			   * ... */

         LIS_tppLista * Vertices ;
               /* Ponteiro para a lista de vértices do grafo */

		 tpVertice * pVertice ;
			   /* Ponteiro para o vértice corrente */

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

      (*ppGrafo)->Origens = NULL ;
      (*ppGrafo)->Vertices = NULL ;
	  (*ppGrafo)->pVertice = NULL ;

	  return GRA_CondRetOK ;

} /* Fim função: GRA Criar grafo */

/***************************************************************************
*
*  Função: GRA Inserir vértice
*  ****/

   GRA_tpCondRet GRA_InserirVertice ( tpGrafo * pGrafo, tpVertice * pVertice ){

} /* Fim função: GRA Inserir vértice */

/***************************************************************************
*
*  Função: GRA Excluir vértice 
*  ****/

   GRA_tpCondRet GRA_ExcluirVertice ( tpGrafo * pGrafo ){

} /* Fim função: GRA Excluir vértice */



/***************************************************************************
*
*  Função: GRA Inserir aresta
*  ****/

   GRA_tpCondRet GRA_InserirAresta ( tpGrafo * pGrafo, tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino ){

} /* Fim função: GRA Inserir aresta */

/***************************************************************************
*
*  Função: GRA Remover aresta
*  ****/

   GRA_tpCondRet GRA_RemoverAresta ( tpGrafo * pGrafo, tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino ){

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
	   LIS_DestruirLista(pGrafo->Origens);
	   LIS_DestruirLista(pGrafo->Vertices);
	   free(pGrafo);
	   pGrafo = NULL;

	   return GRA_CondRetOK ;

} /* Fim função: GRA Destruir grafo */
		
/********** Fim do módulo de implementação: Módulo grafo **********/