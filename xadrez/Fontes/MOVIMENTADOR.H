/***************************************************************************
*  $MCD M�dulo de defini��o: MOV Movimentador de pe�as de Xadrez
*
*  Arquivo gerado:              MOVIMENTADOR.H
*  Letras identificadoras:      MOV
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     0       cev   12/set/2009 In�cio desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa as fun��es para reconhecer se, dado um
*	  tabuleiro de xadrez, um rei est� em xeque mate. Ele parte do ta-
*	  buleiro constru�do pelo m�dulo GERENCIADOR e do arquivo de regras
*	  de movimenta��o para montar um grafo contendo todas as possibili-
*	  dades de movimenta��o de todas as pe�as.
*	  A vers�o corrente ainda n�o implementa o reconhecimento do xeque
*	  mate, mas ela gera o grafo com todos os movimentos poss�veis para
*	  todas as pe�as do tabuleiro.
*
*
/***********************************************************************
*
*  $TC Tipo de dados: MOV Condicoes de retorno
*
*
***********************************************************************/

typedef enum{

	MOV_CondRetOK = 0,
		/* Executou corretamente */

	MOV_CondRetArquivoNaoExiste = 1,
		/* O arquivo passado n�o existe no diret�rio especificado */

	MOV_CondRetArquivoInvalido = 2,
		/* O arquivo passado n�o respeita a sintaxe correta */

	MOV_CondRetFaltouMemoria = 3,
		/* Faltou mem�ria para ser alocada */

	MOV_CondRetNaoCriouGrafo = 4,
		/* O grafo para armazenar as pe�as n�o p�de ser criado */

	MOV_CondRetNaoCriouVertice = 5,
		/* Um v�rtice do grafo n�o p�de ser criado */

	MOV_CondRetNaoInseriuPeca = 6,
		/* N�o conseguiu inserir a pe�a */

	MOV_CondRetErroNaStringDeMovimento = 7,
		/* String de movimento inv�lida */

	MOV_CondRetPosicaoInvalida = 9,
		/* Posi��o inv�lida da pe�a no tabuleiro */

	MOV_CondRetNaoAdicionouProx = 10,
		/* Erro ao adicionar pe�a como pr�xima */

	MOV_CondRetReiNaoExiste = 11,
		/* Rei n�o foi encontrado no tabuleiro */

	MOV_CondRetXequeMate = 12 ,
		/* Rei em Xeque Mate */

	MOV_CondRetNaoEstaEmXequeMate = 13 ,
		/* Rei n�o est� em Xeque Mate */

	MOV_CondRetChegouEmPeca = 14 ,
		/* Sucessor cont�m pe�a */

	MOV_CondRetPecaNaoExiste = 15 ,
		/* Pe�a n�o encontrada */

	MOV_CondRetMovimentoInvalido = 16 ,
		/* Pe�a de origem n�o alcan�a pe�a de destino */

}MOV_tpCondRet;

/***** Declara��es importadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pe�a */

typedef struct GER_tgPeca * GER_tppPeca;

/* Tipo refer�ncia para um grafo */

typedef struct GRA_tgGrafo * GRA_tppGrafo;


/***********************************************************************
*
*  $FC Fun��o: MOV &Adicionar Pe�as ao Grafo
*
*  $ED Descri��o da fun��o
*     Cria um grafo e, a partir do tabuleiro montado pelo m�dulo GERENCI-
*	  ADOR e do arquivo de regras de movimenta��o, constr�i um grafo com 
*	  as movimenta��es poss�veis das pe�as.
*
*  $EP Par�metros
*     ppGrafo - endere�o da refer�ncia que apontar� para o grafo criado
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as pe�as sem problemas
*	  MOV_CondRetNaoCriouGrafo - erro ao criar o grafo
*	  MOV_CondRetNaoCriouVertice - erro ao criar o v�rtice
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir o v�rtice
*
***********************************************************************/

   MOV_tpCondRet MOV_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo );

/***********************************************************************
*
*  $FC Fun��o: MOV &Adicionar Pe�as ao Grafo
*
*  $ED Descri��o da fun��o
*     Cria um grafo e, a partir do tabuleiro montado pelo m�dulo GERENCI-
*	  ADOR e do arquivo de regras de movimenta��o, constr�i um grafo com 
*	  as movimenta��es poss�veis das pe�as.
*
*  $EP Par�metros
*     ppGrafo - endere�o da refer�ncia que apontar� para o grafo criado
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as pe�as sem problemas
*	  MOV_CondRetNaoCriouGrafo - erro ao criar o grafo
*	  MOV_CondRetNaoCriouVertice - erro ao criar o v�rtice
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir o v�rtice
*
***********************************************************************/
   
   MOV_tpCondRet MOV_GeraMovimentacoes ( GRA_tppGrafo * ppGrafo );

/***********************************************************************
*
*  $FC Fun��o: MOV &Reconhecer Xeque Mate
*
*  $ED Descri��o da fun��o
*     A partir do grafo de movimenta��es, reconhece se o rei de uma deter-
*	  minada cor est� em xeque mate.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo de movimenta��es
*	  cCor - letra da cor do rei em poss�vel xeque
*
*  $FV Valor retornado
*	  MOV_CondRetNaoEstaEmXequeMate - rei na cor fonecida n�o est� em xeque mate
*	  MOV_CondRetXequeMate - rei da cor fornecida est� em xeque mate
*	  MOV_CondRetPecaNaoExiste - pe�a presente no tabuleiro f�sico n�o
*	  foi encontrada no grafo
*
***********************************************************************/
   
   MOV_tpCondRet MOV_ReconhecerXequeMate ( char cCor, GRA_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Fun��o: MOV &Mover Pe�a
*
*  $ED Descri��o da fun��o
*     Move uma pe�a do tabuleiro
*
*  $EP Par�metros
*     ColunaOrigem - coluna da casa onde est� a pe�a
*	  LinhaOrigem - linha da casa onde est� a pe�a
*	  ColunaDestino - coluna da casa para onde a pe�a vai
*	  LinhaDestino - linha da casa para onde a pe�a vai
*	  pGrafo - ponteiro para o grafo de movimentos
*
*  $FV Valor retornado
*	  MOV_CondRetOK - moveu corretamente
*	  MOV_CondRetMovimentoInvalido - erro na movimenta��o
*
***********************************************************************/
   
   MOV_tpCondRet MOV_MoverPeca ( char ColunaOrigem , int LinhaOrigem , char ColunaDestino , int LinhaDestino , GRA_tppGrafo pGrafo );
   
/********** Fim do m�dulo de defini��o: M�dulo grafo **********/