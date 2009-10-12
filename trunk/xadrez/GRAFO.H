/***************************************************************************
*  $MCD Módulo de definição: Módulo grafo
*
*  Arquivo gerado:              GRAFO.H
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
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar grafos
*	...
*
/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

		 GRA_CondRetOK = 0 ,
               /* Executou correto */

	     GRA_CondRetFaltouMemoria = 1 ,
			   /* Faltou memória ao alocar dados */

	     GRA_CondRetGrafoVazio = 2 ,
			   /* Grafo está vazio */

   } GRA_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de um grafo
*
*
*  $ED Descrição do tipo
*     A cabeça de um grafo é o ponto de acesso para um determinado grafo.
*   ...
*
***********************************************************************/

	typedef struct tgGrafo tpGrafo ;

/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
*  $ED Descrição da função
*     Cria um novo grafo vazio.
*
*  $EP Parâmetros
*     $P ppGrafo - endereço do ponteiro que irá referenciar o grafo criado.
*
*  $FV Valor retornado
*     ...
*
***********************************************************************/

   GRA_tpCondRet GRA_CriarGrafo ( tpGrafo ** ppGrafo );


/***********************************************************************
*
*  $FC Função: GRA Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo passado.
*
*  $EP Parâmetros
*     $P pGrafo - endereço do ponteiro para a cabeça do grafo a ser destruído.
*
*  $ED Descrição da função
*     Destrói a estrutura e a cabeça do grafo, anulando o grafo passado.
*	  
*
***********************************************************************/

   GRA_tpCondRet GRA_DestruirGrafo ( tpGrafo * pGrafo );


/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
*  $ED Descrição da função
*     Insere um vértice na lista de vértices do grafo.
*
*  $EP Parâmetros
*     $P pVertice - CONFERIR ESSES PARAMENTROS. ACHO QUE pVertice nao eh void.
*     $P pGrafo - ponteiro para a cabeça do grafo em que o vértice será inserido.

*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetErroEstrutura
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice ( tpGrafo * pGrafo, void * pVertice );


/***********************************************************************
*
*  $FC Função: GRA Excluir vértice
*
*  $ED Descrição da função
*     Exclui o vértice corrente na cabeça do grafo.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*
*  $FV Valor retornado
*     ...
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVertice ( tpGrafo * pGrafo );


/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
*  $ED Descrição da função
*     Insere uma aresta entre os vértices passados como parâmetros.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P pVerticeOrigem - ponteiro para o vértice de origem da aresta.
*     $P pVerticeDestino - ponteiro para o vértice de destino da aresta.
*
*  $FV Valor retornado
*     ...
*
***********************************************************************/

	GRA_tpCondRet GRA_InserirAresta ( tpGrafo * pGrafo, void * pVerticeOrigem, void * pVerticeDestino );


/***********************************************************************
*
*  $FC Função: GRA Remover aresta
*
*  $ED Descrição da função
*     Remove a aresta que liga os vértices passados como parâmetros
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P pVerticeOrigem - ponteiro para o vértice de origem da aresta.
*     $P pVerticeDestino - ponteiro para o vértice de destino da aresta.
*
*  $FV Valor retornado
*     ...
*
***********************************************************************/

	GRA_tpCondRet GRA_RemoverAresta ( tpGrafo * pGrafo, void * pVerticeOrigem, void * pVerticeDestino );


/***********************************************************************
*
*  $FC Função: GRA Exibir grafo
*
*  $ED Descrição da função
*     Exibe o grafo passado como parâmetro.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     
*  $FV Valor retornado
*     ...
*
***********************************************************************/

	GRA_tpCondRet GRA_ExibirGrafo ( tpGrafo * pGrafo );

/********** Fim do módulo de definição: Módulo grafo **********/