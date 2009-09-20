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

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para o primeiro filho.
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para o primeiro irmão.
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X->pNoPai */

         char Valor ;
               /* Valor do nó */

		 ARV_tpModoVisita Modo;
				/* Modo de visita do nó */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de um grafo
*
*
*  $ED Descrição do tipo
*     A cabeça do grafo é o ponto de acesso para um determinado grafo.
*     ...
*
***********************************************************************/

   typedef struct tgGrafo {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpGrafo ;
/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

  

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA Criar grafo
*  ****/

   GRA_tpCondRet GRA_CriarGrafo ( tpGrafo ** ppGrafo ){

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

} /* Fim função: GRA Destruir grafo */
		
/********** Fim do módulo de implementação: Módulo grafo **********/