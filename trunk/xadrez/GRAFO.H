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
*     explorar grafos.
*	...
*
/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da grafo
*
***********************************************************************/

   typedef enum {

		 GRA_CondRetOK = 0 ,
               /* Executou correto */

	     GRA_CondRetFaltouMemoria = 1 ,
			   /* Faltou memória ao alocar dados */

	     GRA_CondRetGrafoInexistente = 2 ,
			/* Grafo não existe */

		GRA_CondRetGrafoVazio = 3 ,
			/* Grafo está vazio */ 

		GRA_CondRetVerticeNaoExiste = 4,
			/* Vertice dado não existe */ 
		
		GRA_CondRetIndiceInvalido = 5 ,
			/* Índice dado não corresponde a um vértice na Lista de Vértices */ 
		
		GRA_CondRetArestaJaExiste = 6 ,
			/* Tentou criar uma aresta que já existe */ 
		
		GRA_CondRetArestaNaoExiste = 7,
			/* Tentou criar uma aresta que já existe */ 
		
		 GRA_CondRetVerticeNaoEhOrigem = 8,
			/* Vertice dado nao eh origem */ 

		 GRA_CondRetIdJaExiste = 9,
			/* Identificador já existe no grafo */

		 GRA_CondRetNaoHaOrigens = 10,
			/* Lista de Origens do grafo vazia */

		 GRA_CondRetVerticeNaoEhSucessor = 11,
			/* Vertice dado não é sucessor */

		 GRA_CondRetNaoHaSucessores = 12,
			/* Não há sucessores do Vértice dado */

   } GRA_tpCondRet ;


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para a cabeça de um grafo */

	typedef struct GRA_tgGrafo * GRA_tppGrafo ;

/***** Declarações importadas pelo módulo *****/

	typedef struct VER_tgVertice * VER_tppVertice ;

	typedef struct VER_tgVertice VER_tpVertice ;

/***********************************************************************
*  $FC Função: GRA Criar grafo
*
*  $ED Descrição da função
*     Cria um novo grafo vazio.
*
*  $EP Parâmetros
*     $P ppGrafo - endereço do ponteiro que irá referenciar o grafo criado.
*
*  $FV Valor retornado
*     GRA_CondRetFaltouMemoria - não houve memória suficiente para a alocação.
*	  GRA_CondRetOK
*  
***********************************************************************/

  GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* ppGrafo );

/***********************************************************************
*
*  $FC Função: GRA Destruir grafo
*
*  $ED Descrição da função
*     Destrói a estrutura e a cabeça do grafo, anulando o grafo passado.
*
*  $EP Parâmetros
*     $P pGrafo - endereço do ponteiro para a cabeça do grafo a ser destruído.
*
*  $FV Valor retornado
*     GRA_CondRetGrafoVazio - grafo passado é vazio.
*	  GRA_CondRetOK
*
***********************************************************************/

  GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
*  $ED Descrição da função
*     Insere um vértice na lista de vértices do grafo.
*	  Cada vértice inserido no grafo deve conter um índice
*	  arbitrariamente escolhido que será passado como parâmetro.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo em que o vértice será inserido.
*	  $P pValor - ponteiro para o valor a ser armazenado no vértice
*	  $P idVertice - id único do vértice a ser inserido
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetVerticeNaoExiste - Vértice passado como parâmetro não existe.
*     GRA_CondRetFaltouMemoria - não houve memória suficiente para a alocação.
*
*	  GRA_CondRetIdJaExiste - caso se tente inserir um vértice com um id que já foi
*							  utilizado, a inserção não será feita.
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, void * pValor, int idVertice );


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
*     GRA_CondRetGrafoVazio - Grafo passado está vazio.
*	  GRA_CondRetOK
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVertice( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
*  $ED Descrição da função
*     Insere uma aresta entre os vértices passados como parâmetros.
*	  Será permitido a inserção de laços, isto é, arestas em que os vértices 
*	  de origem e destino são o mesmo.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P idVerticeOrigem - id do vértice de origem da aresta.
*     $P idVerticeDestino - id do vértice de destino da aresta.
*
*  $FV Valor retornado
*	  GRA_CondRetFaltouMemoria - não há memória para a alocação da aresta.
*	  GRA_CondRetGrafoInexistente - grafo passado não existe.
*	  GRA_CondRetVerticeNaoExiste - vértice de origem ou destino não existem.
*	  GRA_CondRetArestaJaExiste - já existe aresta entre os vértices passados.
*	  GRA_CondRetOK
*
***********************************************************************/

	GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
										int idVerticeDestino );


/***********************************************************************
*
*  $FC Função: GRA Remover aresta
*
*  $ED Descrição da função
*     Remove a aresta que liga os vértices passados como parâmetros
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P idVerticeOrigem - indice do vértice de origem da aresta.
*     $P idVerticeDestino - indice do vértice de destino da aresta.
*
*  $FV Valor retornado
*	  GRA_CondRetGrafoInexistente - grafo passado não existe.
*	  GRA_CondRetVerticeNaoExiste - vértice de origem ou destino não existem.
*	  GRA_CondRetArestaNaoExiste - não existe aresta entre os vértices passados.
*	  GRA_CondRetOK
*
***********************************************************************/

GRA_tpCondRet GRA_RemoverAresta( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
									int idVerticeDestino );


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
*	  GRA_CondRetGrafoInexistente - grafo passado não existe.
*	  GRA_CondRetVerticeNaoExiste - erro ao tentar percorrer o grafo.
*	  GRA_CondRetOK
*
***********************************************************************/

	GRA_tpCondRet GRA_ExibirGrafo( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Função: GRA Marcar Como Origem
*
*  $ED Descrição da função
*     Coloca um vértice na lista de origens da cabeça do grafo
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P idVertice - indice do vértice a ser marcado como origem.
*
*  $FV Valor retornado
*	  GRA_CondRetFaltouMemoria - não há memória para a alocação da aresta.
*	  GRA_CondRetGrafoInexistente - grafo passado não existe.
*	  GRA_CondRetIndiceInvalido - índice passado não é válido
*	  GRA_CondRetOK
*
***********************************************************************/

	 GRA_tpCondRet GRA_MarcarComoOrigem( GRA_tppGrafo pGrafo, int idVertice );


/***********************************************************************
*
*  $FC Função: GRA Desmarcar Como Origem
*
*  $ED Descrição da função
*     Coloca um vértice na lista de origens da cabeça do grafo
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P idVertice - indice do vértice a ser desmarcado.
*
*  $FV Valor retornado
*	  GRA_CondRetGrafoInexistente - grafo passado não existe.
*	  GRA_CondRetVerticeNaoEhOrigem - vértice passado não é origem ou ID passado é inválido
*	  GRA_CondRetOK
*
***********************************************************************/

	 GRA_tpCondRet GRA_DesmarcarComoOrigem( GRA_tppGrafo pGrafo, int idVertice );


/***********************************************************************
*
*  $FC Função: GRA Obter Valor Com Id
*
*  $ED Descrição da função
*     Obtém o valor do vértice a partir do seu indice.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P IdVertice - indice do vértice que se deseja obter o valor.
*	  $P ppValor - variável do tipo ponteiro para ponteiro para void que 
*				   referenciará o ponteiro para a estrutura do valor.
*
*  $FV Valor retornado
*     ..
*
***********************************************************************/
	 
	 GRA_tpCondRet GRA_ObterValorComId( GRA_tppGrafo pGrafo , int IdVertice , void** ppValor );


 /***********************************************************************
*
*  $FC Função: GRA Avancar Sucessor
*
*  $ED Descrição da função
*     Avança para o vértice sucessor com o índice dado, se o índice for sucessor.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P IdVertice - indice do vértice sucessor que se deseja avançar.
*
*  $FV Valor retornado
*     ..
*
***********************************************************************/

	 GRA_tpCondRet GRA_AvancarSucessor( GRA_tppGrafo pGrafo, int IdVertice );


/***********************************************************************
*
*  $FC Função: Obtem Vértice Com ID
*
*  $ED Descrição da função
*     Obtém o vértice a partir do índice dado.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a cabeça do grafo.
*     $P IdVertice - indice do vértice a ser marcado como origem.
*
*  $FV Valor retornado
*     Retorna o endereço do vértice (tipo VER_tppVertice) caso este seja encontrado
*	  ou NULL caso não seja encontrado nenhum vértice com o índice passado.
*
***********************************************************************/

	 VER_tppVertice ObtemVerticeComId( GRA_tppGrafo pGrafo, int IdVertice );



/********** Fim do módulo de definição: Módulo grafo **********/