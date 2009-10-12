/***************************************************************************
*  $MCD Módulo de definição: Módulo vértice
*
*  Arquivo gerado:              VERTICE.H
*  Letras identificadoras:      VER
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
*       1.00   cev   25/09/2009 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar vértices.
*	...
*
/***********************************************************************
*
*  $TC Tipo de dados: VER Condicoes de retorno
*
*
***********************************************************************/


typedef enum {
		VER_CondRetOK = 0 ,
               /* Executou correto */

         VER_CondRetVerticeNaoExiste = 1 ,
               /* Vértice não existe */

        VER_CondRetVerticeVazio = 2 ,
               /* Vértice está vazio */

         VER_CondRetFaltouMemoria = 3 ,
               /* Faltou memória ao alocar dados */

		 VER_CondRetVerticeSucessorJahExiste = 4 ,
               /* Vértice destino já é sucessor do vértice origem */

	     VER_CondRetVerticeNaoEhSucessor = 5 ,
				/* Vértice destino não é sucessor do vértice origem */

		VER_CondRetVerticeNaoEhAntecessor = 6 ,
				/* Vértice destino não é antecessor do vértice origem */

} VER_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor de um vértice
*
*
*  $ED Descrição do tipo
*     Um vértice é uma estrutura que armazena um valor de qualquer tipo.
*   ...
*
***********************************************************************/

	typedef struct tgVertice tpVertice ;

/***********************************************************************
*
*  $FC Função: VER Criar vértice
*
*  $ED Descrição da função
*     Cria um novo vértice vazio.
*
*  $EP Parâmetros
*     $P ppVertice - endereço do ponteiro que irá referenciar o vértice criado.
*	  $P Valor - ponteiro para void que irá referenciar o valor do vértice criado.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*       VER_CondRetFaltouMemoria
*
***********************************************************************/

	VER_tpCondRet VER_CriarVertice ( tpVertice ** ppVertice, void * Valor, int idVertice );

/***********************************************************************
*
*  $FC Função: VER Obter valor
*
*  $ED Descrição da função
*     Obtém valor armazenado no vértice.
*
*  $EP Parâmetros
*     $P pVertice - ponteiro que referencia o vértice.
*	  $P Valor - ponteiro para void que referencia o valor do vértice.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*       VER_CondRetVerticeVazio
*
***********************************************************************/

	VER_tpCondRet VER_ObterValor ( tpVertice * pVertice, void ** Valor );

/***********************************************************************
*
*  $FC Função: VER Alterar valor
*
*  $ED Descrição da função
*     Altera o valor armazenado no vértice.
*
*  $EP Parâmetros
*     $P pVertice - ponteiro que referencia o vértice.
*	  $P ValorNovo - ponteiro para void que referencia o novo valor do vértice.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*
***********************************************************************/

	VER_tpCondRet VER_AlterarValor ( tpVertice * pVertice, void * ValorNovo );

/***********************************************************************
*
*  $FC Função: VER Destruir Vertice
*
*  $ED Descrição da função
*     Destrói o vértice.
*
*  $EP Parâmetros
*     $P pVertice - ponteiro que referencia o vértice.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*
***********************************************************************/

	void VER_DestruirVertice ( tpVertice * pVertice );

/***********************************************************************
*
*  $FC Função: VER Adicionar Sucessor
*
*  $ED Descrição da função
*     Adiciona o vértice passado como destino à lista de sucessores
*	  do vértice passado como origem.
*	
*  $EP Parâmetros
*     $P pVerticeOrigem - ponteiro que referencia o vértice de origem.
*	  $P pVerticeDestino - ponteiro que referencia o vértice de destino.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*		VER_CondRetFaltouMemoria;
*		VER_CondRetVerticeSucessorJahExiste
*
***********************************************************************/
	
	VER_tpCondRet VER_AdicionarSucessor ( tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino );

/***********************************************************************
*
*  $FC Função: VER Remover Sucessor
*
*  $ED Descrição da função
*     Remove o vértice passado como destino da lista de sucessores
*	  do vértice passado como origem.
*
*  $EP Parâmetros
*     $P pVerticeOrigem - ponteiro que referencia o vértice de origem.
*	  $P pVerticeDestino - ponteiro que referencia o vértice de destino.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*		VER_CondRetVerticeJaEhSucessor
*
***********************************************************************/

	VER_tpCondRet VER_RemoverSucessor ( tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino );

/***********************************************************************
*
*  $FC Função: VER Obter ID
*
*  $ED Descrição da função
*     Obtém o ID do vértice.
*
*  $EP Parâmetros
*     $P pVertice - ponteiro que referencia o vértice.
*	  $p pIdVertice - ponteiro para armazenar o id a ser retornado
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*
***********************************************************************/

	void VER_ObterId ( tpVertice * pVertice, int * pIdVertice );


/********** Fim do módulo de definição: Módulo vértice **********/
