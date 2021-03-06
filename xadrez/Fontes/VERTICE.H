/***************************************************************************
*  $MCD M�dulo de defini��o: M�dulo v�rtice
*
*  Arquivo gerado:              VERTICE.H
*  Letras identificadoras:      VER
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
*     explorar v�rtices.
*	  Cada v�rtice pode referenciar um tipo arbitr�rio de dados. Cada v�r-
*	  tice tamb�m possui um identificador, uma lista de sucessores e uma
*	  lista de antecessores.
*	
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
               /* V�rtice n�o existe */

        VER_CondRetVerticeVazio = 2 ,
               /* V�rtice est� vazio */

         VER_CondRetFaltouMemoria = 3 ,
               /* Faltou mem�ria ao alocar dados */

		 VER_CondRetVerticeSucessorJahExiste = 4 ,
               /* V�rtice destino j� � sucessor do v�rtice origem */

	     VER_CondRetVerticeNaoEhSucessor = 5 ,
				/* V�rtice destino n�o � sucessor do v�rtice origem */

		VER_CondRetVerticeNaoEhAntecessor = 6 ,
				/* V�rtice destino n�o � antecessor do v�rtice origem */

		 VER_CondRetErroEstrutural = 7 ,
               /* Faltou mem�ria ao alocar dados */


} VER_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor de um v�rtice
*
*
*  $ED Descri��o do tipo
*     Um v�rtice � uma estrutura que armazena um valor de qualquer tipo.
*   ...
*
***********************************************************************/

	typedef struct VER_tgVertice * VER_tppVertice ;


/***** Declara��es importadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

	typedef struct LIS_tagLista * LIS_tppLista ;

/***********************************************************************
*
*  $FC Fun��o: VER Criar v�rtice
*
*  $ED Descri��o da fun��o
*     Cria um novo v�rtice vazio.
*
*  $EP Par�metros
*     $P ppVertice - endere�o do ponteiro que ir� referenciar o v�rtice criado.
*	  $P Valor - ponteiro para void que ir� referenciar o valor do v�rtice criado.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*       VER_CondRetFaltouMemoria
*
***********************************************************************/

	VER_tpCondRet VER_CriarVertice ( VER_tppVertice * ppVertice, void * Valor, int idVertice );


/***********************************************************************
*
*  $FC Fun��o: VER Obter valor
*
*  $ED Descri��o da fun��o
*     Obt�m valor armazenado no v�rtice.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*	  $P Valor - ponteiro para void que referencia o valor do v�rtice.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*       VER_CondRetVerticeVazio
*
***********************************************************************/

	VER_tpCondRet VER_ObterValor ( VER_tppVertice pVertice, void ** ppValor );


/***********************************************************************
*
*  $FC Fun��o: VER Alterar valor
*
*  $ED Descri��o da fun��o
*     Altera o valor armazenado no v�rtice.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*	  $P ValorNovo - ponteiro para void que referencia o novo valor do v�rtice.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*
***********************************************************************/

	VER_tpCondRet VER_AlterarValor ( VER_tppVertice pVertice, void * ValorNovo );


/***********************************************************************
*
*  $FC Fun��o: VER Destruir Vertice
*
*  $ED Descri��o da fun��o
*     Destr�i o v�rtice.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*	  Se o ponteiro passado for nulo a fun��o retorna sem executar
*	  o procedimento de destrui��o
*
***********************************************************************/

	void VER_DestruirVertice ( void * pVertice );


/***********************************************************************
*
*  $FC Fun��o: VER Adicionar Sucessor
*
*  $ED Descri��o da fun��o
*     Adiciona o v�rtice passado como destino � lista de sucessores
*	  do v�rtice passado como origem.
*	
*  $EP Par�metros
*     $P pVerticeOrigem - ponteiro que referencia o v�rtice de origem.
*	  $P pVerticeDestino - ponteiro que referencia o v�rtice de destino.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*		VER_CondRetFaltouMemoria;
*		VER_CondRetVerticeSucessorJahExiste
*
***********************************************************************/
	
	VER_tpCondRet VER_AdicionarSucessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino );


/***********************************************************************
*
*  $FC Fun��o: VER Remover Sucessor
*
*  $ED Descri��o da fun��o
*     Remove o v�rtice passado como destino da lista de sucessores
*	  do v�rtice passado como origem.
*
*  $EP Par�metros
*     $P pVerticeOrigem - ponteiro que referencia o v�rtice de origem.
*	  $P pVerticeDestino - ponteiro que referencia o v�rtice de destino.
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*		VER_CondRetVerticeNaoEhSucessor
*
***********************************************************************/

	VER_tpCondRet VER_RemoverSucessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino );


/***********************************************************************
*
*  $FC Fun��o: VER Obter ID
*
*  $ED Descri��o da fun��o
*     Obt�m o ID do v�rtice.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*	  $p pIdVertice - ponteiro para armazenar o id a ser retornado
*
*  $FV Valor retornado
*     	VER_CondRetOK
*		VER_CondRetVerticeNaoExiste
*
***********************************************************************/

	VER_tpCondRet VER_ObterId ( VER_tppVertice pVertice, int * pIdVertice );


/***********************************************************************
*
*  $FC Fun��o: VER Exibir Sucessores
*
*  $ED Descri��o da fun��o
*     Exibe na tela a lista de sucessores do v�rtice passado.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*
*  $FV Valor retornado
*
***********************************************************************/

	void VER_ExibirSucessores ( VER_tppVertice pVertice );


/***********************************************************************
*
*  $FC Fun��o: VER Obter Lista de Sucessores
*
*  $ED Descri��o da fun��o
*     Obt�m a lista de sucessores do v�rtice passado.
*	  A lista retornada est� com o elemento corrente no in�cio da lista.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*
*  $FV Valor retornado
*     	LIS_tppLista
*		NULL - se o v�rtice n�o existir ou a lista de sucessores
*		estiver vazia
*
***********************************************************************/

	LIS_tppLista VER_ObterListaSucessores ( VER_tppVertice pVertice );


/***********************************************************************
*
*  $FC Fun��o: VER Obter Lista de Antecessores
*
*  $ED Descri��o da fun��o
*     Obt�m a lista de antecessores do v�rtice passado.
*	  A lista retornada est� com o elemento corrente no in�cio da lista.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*
*  $FV Valor retornado
*     	LIS_tppLista
*		NULL - se o v�rtice n�o existir ou a lista de antecessores
*		estiver vazia
*
***********************************************************************/

	LIS_tppLista VER_ObterListaAntecessores ( VER_tppVertice pVertice );

/***********************************************************************
*
*  $FC Fun��o: VER Exibir Antecessores
*
*  $ED Descri��o da fun��o
*     Exibe na tela a lista de antecessores do v�rtice passado.
*
*  $EP Par�metros
*     $P pVertice - ponteiro que referencia o v�rtice.
*
*  $FV Valor retornado
*
***********************************************************************/

	void VER_ExibirAntecessores ( VER_tppVertice pVertice );


/********** Fim do m�dulo de defini��o: M�dulo v�rtice **********/
