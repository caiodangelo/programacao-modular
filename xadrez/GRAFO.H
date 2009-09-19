/***************************************************************************
*
*  $MCD Módulo de definição: Módulo grafo
*
*  Arquivo gerado:              GRAFO.H
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    -
*  Arquivo da base de software: -
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   cev   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar grafos
*	...
*
*
*     As árvores possuem uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     Uma árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a árvore estiver vazia.
*
/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         

   } GRA_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de um grafo
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
*  $FC Função: ARV Destruir grafo
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
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*     $P pArvore - ponteiro para a cabeça da árvore em que o filho será inserido
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice ( tpGrafo * pGrafo, tpVertice * pVertice );


/***********************************************************************
*
*  $FC Função: GRA Excluir vértice
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
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*
*  $FV Valor retornado
*     ...
*
***********************************************************************/

	GRA_tpCondRet GRA_InserirAresta ( tpGrafo * pGrafo, tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino );


/***********************************************************************
*
*  $FC Função: GRA Remover aresta
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P pGrafo - ponteiro para a cabeça do grafo.
*
*  $FV Valor retornado
*     ...
*
***********************************************************************/

	GRA_tpCondRet GRA_RemoverAresta ( tpGrafo * pGrafo, tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino );


/***********************************************************************
*
*  $FC Função: GRA Exibir grafo
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     
*  $FV Valor retornado
*     ...
*
***********************************************************************/

	GRA_tpCondRet GRA_ExibirGrafo ( tpGrafo * pGrafo );

/********** Fim do módulo de definição: Módulo árvore **********/