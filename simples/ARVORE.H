#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo �rvore
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       4.00   cev   15/09/2009 Extens�o para m�ltiplas �rvores n-�rias
*                               e adi��o de novas fun��es.
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar �rvores n-�rias.
*     As �rvores possuem uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     �rvore e outra para um n� corrente da �rvore.
*     Ao iniciar a execu��o do programa n�o existe �rvore.
*     Uma �rvore poder� estar vazia. Neste caso a raiz e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a �rvore estiver vazia.
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
               /* N�o criou n� raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da �rvore est� errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* N�o � folha relativa � dire��o de inser��o desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* �rvore n�o existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* �rvore est� vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* N� corrente � raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* N� corrente n�o possui filho */

         ARV_CondRetFaltouMemoria = 8 ,
               /* Faltou mem�ria ao alocar dados */

		 ARV_CondRetNaoPossuiIrmao = 9 ,
			   /* N� corrente n�o possui irm�o */

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

	typedef struct tgArvore tpArvore ;

/***********************************************************************
*
*  $FC Fun��o: ARV Criar �rvore
*
*  $ED Descri��o da fun��o
*     Cria uma nova �rvore vazia.
*
*  $EP Par�metros
*     $P ppArvore - endere�o do ponteiro que ir� referenciar a �rvore criada.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore(tpArvore ** pArvore) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir �rvore
*
*  $EP Par�metros
*     $P pArvore - endere�o do ponteiro para a cabe�a da �rvore a ser destru�da.
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da �rvore, anulando a �rvore passada.
*	  O ponteiro passado por refer�ncia recebe o valor de NULL.
*
***********************************************************************/

   void ARV_DestruirArvore(tpArvore ** pArvore) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Adicionar filho
*
*  $EP Par�metros
*     $P ValorParm - valor a ser inserido no novo n�.
*     $P pArvore - ponteiro para a cabe�a da �rvore em que o filho ser� inserido
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
*  $FC Fun��o: ARV Ir para n� pai
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a cabe�a da �rvore.
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
*  $FC Fun��o: ARV Ir para n� Filho
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a cabe�a da �rvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoFilho(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� Irm�o
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a cabe�a da �rvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiIrmao  - n� corrente n�o possui irm�o
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoIrmao(tpArvore * pArvore) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Obter valor corrente
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a cabe�a da �rvore.
*     $P ValorParm - � o par�metro que receber� o valor contido no n�.
*                    Este par�metro � passado por refer�ncia.
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
*  $FC Fun��o: ARV Exibir �rvore
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a �rvore a ser exibida.
*
*  $ED Descri��o da fun��o
*     Imprime os n�s da �rvore em ordem prefixada pela esquerda.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ExibirArvore(tpArvore * pArvore) ;

#undef ARVORE_EXT

/********** Fim do m�dulo de defini��o: M�dulo �rvore **********/

#else
#endif
