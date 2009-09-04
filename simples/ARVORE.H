#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo árvore
*
*  Arquivo gerado:              ARVORE.H
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
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       4.00   cev   10/09/2009 Extensão para múltiplas árvores n-árias
*                               e adição de novas funções.
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar árvores n-árias.
*     As árvores possuem uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     Uma árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a árvore estiver vazia.
*
***************************************************************************/
 
#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         ARV_CondRetOK = 0 ,
               /* Executou correto */

         ARV_CondRetNaoCriouRaiz = 1 ,
               /* Não criou nó raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da árvore está errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* Não é folha relativa à direção de inserção desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* Árvore não existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* Árvore está vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho */

         ARV_CondRetFaltouMemoria = 8 ,
               /* Faltou memória ao alocar dados */

		 ARV_CondRetNaoPossuiIrmao = 9 ,
			   /* Nó corrente não possui irmão */

   } ARV_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Modos de Visita
*
*
***********************************************************************/

   typedef enum {

         ARV_ModoDePai = 0 ,
               /* Modo de Pai */

         ARV_ModoParaEsq = 1 ,
               /* Modo para Esquerda */

         ARV_ModoParaDir = 2 ,
               /* Modo para Direita */

   } ARV_tpModoVisita ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

	typedef struct tgArvore tpArvore ;

/***********************************************************************
*
*  $FC Função: ARV Criar árvore
*
*  $ED Descrição da função
*     Cria uma nova árvore vazia.
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore a ser criada.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Destruir árvore
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore a ser destruída.
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da árvore, anulando a árvore passada.
*
***********************************************************************/

   void ARV_DestruirArvore(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Adicionar filho
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*     $P pArvore - ponteiro para a árvore em que o filho será inserido
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirFilho(tpArvore * pArvore, char ValorParm) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó pai
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNoEhRaiz
*
***********************************************************************/

   ARV_tpCondRet ARV_IrPai(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó Filho
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoFilho(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó Irmão
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiIrmao  - nó corrente não possui irmão
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoIrmao(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Obter valor corrente
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore.
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ObterValorCorr(tpArvore * pArvore, char * ValorParm) ;

/***********************************************************************
*
*  $FC Função: ARV Exibir árvore
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a árvore a ser exibida.
*
*  $ED Descrição da função
*     Imprime os nós da árvore em ordem prefixada pela esquerda.
*
***********************************************************************/

   void ARV_ExibirArvore(tpArvore * pArvore) ;

#undef ARVORE_EXT

/********** Fim do módulo de definição: Módulo árvore **********/

#else
#endif
