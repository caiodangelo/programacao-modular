/***************************************************************************
*  $MCD M�dulo de defini��o: M�dulo grafo
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       0	   cev   12/09/2009 In�cio do desenvolvimento
*       1	   cev   19/10/2009 Entrega do trabalho
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar grafos.
*	  Sendo um grafo um conjunto de v�rtices, a no��o completa de grafo
*	  � obtida com a utiliza��o conjunta dos dois m�dulos.
*	  Os grafos criados e manipulados ser�o gen�ricos pois a estrutura 
*	  dos v�rtices propicia isso.
*	  
*
/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da grafo
*
***********************************************************************/

   typedef enum {

		 GRA_CondRetOK = 0 ,
               /* Executou correto */

	     GRA_CondRetFaltouMemoria = 1 ,
			   /* Faltou mem�ria ao alocar dados */

	     GRA_CondRetGrafoInexistente = 2 ,
			/* Grafo n�o existe */

		GRA_CondRetGrafoVazio = 3 ,
			/* Grafo est� vazio */ 

		GRA_CondRetVerticeNaoExiste = 4,
			/* Vertice dado n�o existe */ 
		
		GRA_CondRetIndiceInvalido = 5 ,
			/* �ndice dado n�o corresponde a um v�rtice na Lista de V�rtices */ 
		
		GRA_CondRetArestaJaExiste = 6 ,
			/* Tentou criar uma aresta que j� existe */ 
		
		GRA_CondRetArestaNaoExiste = 7,
			/* Tentou criar uma aresta que j� existe */ 
		
		 GRA_CondRetVerticeNaoEhOrigem = 8,
			/* Vertice dado nao eh origem */ 

		 GRA_CondRetIdJaExiste = 9,
			/* Identificador j� existe no grafo */

		 GRA_CondRetNaoHaOrigens = 10,
			/* Lista de Origens do grafo vazia */

		 GRA_CondRetVerticeNaoEhSucessor = 11,
			/* Vertice dado n�o � sucessor */

		 GRA_CondRetNaoHaSucessores = 12,
			/* N�o h� sucessores do V�rtice dado */

		 GRA_CondRetVerticeVazio = 13,
			/* Vertice dado est� vazio */ 

		 GRA_CondRetNaoHaAntecessores = 14,
			/* N�o h� sucessores do V�rtice dado */

   } GRA_tpCondRet ;


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para a cabe�a de um grafo */

	typedef struct GRA_tgGrafo * GRA_tppGrafo ;

/***** Declara��es importadas pelo m�dulo *****/

	typedef struct VER_tgVertice * VER_tppVertice ;

/***********************************************************************
*  $FC Fun��o: GRA Criar grafo
*
*  $ED Descri��o da fun��o
*     Cria um novo grafo vazio.
*
*  $EP Par�metros
*     $P ppGrafo - endere�o do ponteiro que ir� referenciar o grafo criado.
*
*  $FV Valor retornado
*     GRA_CondRetFaltouMemoria - n�o houve mem�ria suficiente para a aloca��o.
*	  GRA_CondRetOK
*  
***********************************************************************/

  GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* ppGrafo );

/***********************************************************************
*
*  $FC Fun��o: GRA Destruir grafo
*
*  $ED Descri��o da fun��o
*     Destr�i a estrutura e a cabe�a do grafo, anulando o grafo passado.
*
*  $EP Par�metros
*     $P pGrafo - endere�o do ponteiro para a cabe�a do grafo a ser destru�do.
*
*  $FV Valor retornado
*     GRA_CondRetGrafoVazio - grafo passado � vazio.
*	  GRA_CondRetOK
*
***********************************************************************/

  GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo* ppGrafo );


/***********************************************************************
*
*  $FC Fun��o: GRA Inserir v�rtice
*
*  $ED Descri��o da fun��o
*     Insere um v�rtice na lista de v�rtices do grafo.
*	  Cada v�rtice inserido no grafo deve conter um �ndice
*	  arbitrariamente escolhido que ser� passado como par�metro.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo em que o v�rtice ser� inserido.
*	  $P pValor - ponteiro para o valor a ser armazenado no v�rtice
*	  $P idVertice - id �nico do v�rtice a ser inserido
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetVerticeNaoExiste - V�rtice passado como par�metro n�o existe.
*     GRA_CondRetFaltouMemoria - n�o houve mem�ria suficiente para a aloca��o.
*
*	  GRA_CondRetIdJaExiste - caso se tente inserir um v�rtice com um id que j� foi
*							  utilizado, a inser��o n�o ser� feita.
*
*	  GRA_CondRetGrafoInexistente - Grafo passado como par�metro n�o existe.
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, void * pValor, int IdVertice );


/***********************************************************************
*
*  $FC Fun��o: GRA Excluir v�rtice
*
*  $ED Descri��o da fun��o
*     Exclui o v�rtice corrente na cabe�a do grafo.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*
*  $FV Valor retornado
*	  GRA_CondRetGrafoInexistente - Grafo passado n�o existe.
*     GRA_CondRetGrafoVazio - Grafo passado est� vazio.
*	  GRA_CondRetVerticeNaoExiste - o v�rtice dado n�o existe
*	  GRA_CondRetOK
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVertice( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Fun��o: GRA Inserir aresta
*
*  $ED Descri��o da fun��o
*     Insere uma aresta entre os v�rtices passados como par�metros.
*	  Ser� permitido a inser��o de la�os, isto �, arestas em que os v�rtices 
*	  de origem e destino s�o o mesmo.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P idVerticeOrigem - id do v�rtice de origem da aresta.
*     $P idVerticeDestino - id do v�rtice de destino da aresta.
*
*  $FV Valor retornado
*	  GRA_CondRetFaltouMemoria - n�o h� mem�ria para a aloca��o da aresta.
*	  GRA_CondRetGrafoInexistente - grafo passado n�o existe.
*	  GRA_CondRetVerticeNaoExiste - v�rtice de origem ou destino n�o existem.
*	  GRA_CondRetArestaJaExiste - j� existe aresta entre os v�rtices passados.
*	  GRA_CondRetOK
*
***********************************************************************/

	GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
										int idVerticeDestino );


/***********************************************************************
*
*  $FC Fun��o: GRA Remover aresta
*
*  $ED Descri��o da fun��o
*     Remove a aresta que liga os v�rtices passados como par�metros
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P idVerticeOrigem - indice do v�rtice de origem da aresta.
*     $P idVerticeDestino - indice do v�rtice de destino da aresta.
*
*  $FV Valor retornado
*	  GRA_CondRetGrafoInexistente - grafo passado n�o existe.
*	  GRA_CondRetVerticeNaoExiste - v�rtice de origem ou destino n�o existem.
*	  GRA_CondRetArestaNaoExiste - n�o existe aresta entre os v�rtices passados.
*	  GRA_CondRetOK
*
***********************************************************************/

GRA_tpCondRet GRA_RemoverAresta( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
									int idVerticeDestino );


/***********************************************************************
*
*  $FC Fun��o: GRA Exibir grafo
*
*  $ED Descri��o da fun��o
*     Exibe o grafo passado como par�metro.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*
*  $FV Valor retornado
*	  GRA_CondRetGrafoInexistente - grafo passado n�o existe.
*	  GRA_CondRetVerticeNaoExiste - erro ao tentar percorrer o grafo.
*	  GRA_CondRetOK
*
***********************************************************************/

	GRA_tpCondRet GRA_ExibirGrafo( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Fun��o: GRA Marcar Como Origem
*
*  $ED Descri��o da fun��o
*     Coloca um v�rtice na lista de origens da cabe�a do grafo
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P idVertice - indice do v�rtice a ser marcado como origem.
*
*  $FV Valor retornado
*	  GRA_CondRetFaltouMemoria - n�o h� mem�ria para a aloca��o da aresta.
*	  GRA_CondRetGrafoInexistente - grafo passado n�o existe.
*	  GRA_CondRetIndiceInvalido - �ndice passado n�o � v�lido
*	  GRA_CondRetOK
*
***********************************************************************/

	 GRA_tpCondRet GRA_MarcarComoOrigem( GRA_tppGrafo pGrafo, int IdVertice );


/***********************************************************************
*
*  $FC Fun��o: GRA Desmarcar Como Origem
*
*  $ED Descri��o da fun��o
*     Coloca um v�rtice na lista de origens da cabe�a do grafo
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P idVertice - indice do v�rtice a ser desmarcado.
*
*  $FV Valor retornado
*	  GRA_CondRetGrafoInexistente - grafo passado n�o existe.
*	  GRA_CondRetVerticeNaoEhOrigem - v�rtice passado n�o � origem ou ID passado � inv�lido
*	  GRA_CondRetOK
*
***********************************************************************/

	 GRA_tpCondRet GRA_DesmarcarComoOrigem( GRA_tppGrafo pGrafo, int IdVertice );


/***********************************************************************
*
*  $FC Fun��o: GRA Obter Valor Com Id
*
*  $ED Descri��o da fun��o
*     Obt�m o valor do v�rtice a partir do seu indice.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P IdVertice - indice do v�rtice que se deseja obter o valor.
*	  $P ppValor - vari�vel do tipo ponteiro para ponteiro para void que 
*				   referenciar� o ponteiro para a estrutura do valor.
*
*  $FV Valor retornado
*	  GRA_CondRetIndiceInvalido - indice passado n�o � v�lido						
*	  GRA_CondRetGrafoInexistente - indice passado n�o � v�lido
*     GRA_CondRetOK - valor retornado por refer�ncia
*
***********************************************************************/
	 
	 GRA_tpCondRet GRA_ObterValorComId( GRA_tppGrafo pGrafo , int IdVertice , void** ppValor );


 /***********************************************************************
*
*  $FC Fun��o: GRA Avancar Sucessor
*
*  $ED Descri��o da fun��o
*     Avan�a para o v�rtice sucessor com o �ndice dado, se o �ndice for sucessor.
*     Se o �ndice n�o for sucessor, v�rtice corrente n�o ser� alterado.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P IdVertice - indice do v�rtice sucessor que se deseja avan�ar.
*
*  $FV Valor retornado
*     GRA_CondRetGrafoInexistente - Grafo passado n�o existe.
*     GRA_CondRetGrafoVazio - Grafo passado est� vazio.
*     GRA_CondRetNaoHaSucessores - V�rtice corrente n�o possui sucessores
*     GRA_CondRetNaoEhSucessor - V�rtice passado n�o � sucessor do corrente.
*     GRA_CondRetOk
*
***********************************************************************/

	 GRA_tpCondRet GRA_AvancarSucessor( GRA_tppGrafo pGrafo, int IdVertice );


/***********************************************************************
*
*  $FC Fun��o: GRA Ir Vertice Com Id
*
*  $ED Descri��o da fun��o
*     Seta o v�rtice passado como �ndice como V�rtice Corrente do grafo.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P IdVertice - indice do v�rtice a ser setado como corrente.
*
*  $FV Valor retornado
*	  GRA_CondRetIdInvalido - id passado � inv�lido
*	  GRA_CondRetOK
*
***********************************************************************/

	 GRA_tpCondRet GRA_IrVerticeComId( GRA_tppGrafo pGrafo , int IdVertice);


/***********************************************************************
*
*  $FC Fun��o: GRA Obter Sucessor
*
*  $ED Descri��o da fun��o
*     Obtem o Id do v�rtice corrente da lista de sucessores de um v�rtice com IdVertice. 
*	  Seta o corrente para o pr�ximo elemento da lista de sucessores.
*	  Se o pr�ximo elemente for NULL, o corrente passa a ser o primeiro elemento
*	  da lista de sucessores, criando assim uma circularidade no percorrimento da lista.
*
*	  O Id do sucessor ser� passado via derefer�ncia.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P IdVertice - indice do v�rtice que se deseja obter sucessor.
*     $P pIdSucessor - ponteiro para o �ndice do v�rtice a ser retornado.
*
*  $FV Valor retornado
	  GRA_CondRetNaoHaSucessores - IdVertice n�o possui sucessores
	  GRA_CondRetIdInvalido	- Indice passado n�o � v�lido
	  GRA_CondRetOK
*
***********************************************************************/
	 
	 GRA_tpCondRet GRA_ObterSucessor ( GRA_tppGrafo pGrafo , int IdVertice , 
									  int * pIdSucessor ) ;


/***********************************************************************
*
*  $FC Fun��o: GRA Obter Antecessor
*
*  $ED Descri��o da fun��o
*     Obt�m o Id do v�rtice corrente da lista de antecessores de um v�rtice com 
*	  IdVertice. 
*	  Seta o corrente para o pr�ximo elemento da lista de antecessores.
*	  Se o pr�ximo elemente for NULL, o corrente passa a ser o primeiro elemento
*	  da lista de antecessores, criando assim uma circularidade no 
*	  percorrimento da lista.
*
*	  O Id do antecessor ser� passado via derefer�ncia.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P IdVertice - indice do v�rtice que se deseja obter antecessor.
*     $P pIdAntecessor - ponteiro para o �ndice do v�rtice a ser retornado.
*
*  $FV Valor retornado
*	  GRA_CondRetNaoHaAntecessores - IdVertice n�o possui antecessores
	  GRA_CondRetIdInvalido	- Indice passado n�o � v�lido
*	  GRA_CondRetOK
*
***********************************************************************/

	 GRA_tpCondRet GRA_ObterAntecessor ( GRA_tppGrafo pGrafo , int IdVertice , int * pIdAntecessor ) ;



/********** Fim do m�dulo de defini��o: M�dulo grafo **********/