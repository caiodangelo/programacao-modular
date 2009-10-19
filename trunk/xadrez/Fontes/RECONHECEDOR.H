/***************************************************************************
*  $MCD Módulo de definição: Módulo reconhecedor de xeque mate
*
*  Arquivo gerado:              RECONHECEDOR.H
*  Letras identificadoras:      REC
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   12/set/2009 Início desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
*  $ED Descrição do módulo
*     Este módulo implementa as funções para reconhecer se, dado um
*	  tabuleiro de xadrez, um rei está em xeque mate. Ele parte do ta-
*	  buleiro construído pelo módulo GERENCIADOR e do arquivo de regras
*	  de movimentação para montar um grafo contendo todas as possibili-
*	  dades de movimentação de todas as peças.
*	  A versão corrente ainda não implementa o reconhecimento do xeque
*	  mate, mas ela gera o grafo com todos os movimentos possíveis para
*	  todas as peças do tabuleiro.
*
*
/***********************************************************************
*
*  $TC Tipo de dados: REC Condicoes de retorno
*
*
***********************************************************************/

typedef enum{

	REC_CondRetOK = 0,
		/* Executou corretamente */

	REC_CondRetArquivoNaoExiste = 1,
		/* O arquivo passado não existe no diretório especificado */

	REC_CondRetArquivoInvalido = 2,
		/* O arquivo passado não respeita a sintaxe correta */

	REC_CondRetFaltouMemoria = 3,
		/* Faltou memória para ser alocada */

	REC_CondRetNaoCriouGrafo = 4,
		/* O grafo para armazenar as peças não pôde ser criado */

	REC_CondRetNaoCriouVertice = 5,
		/* Um vértice do grafo não pôde ser criado */

	REC_CondRetNaoInseriuPeca = 6,
		/* Não conseguiu inserir a peça */

	REC_CondRetErroNaStringDeMovimento = 7,
		/* String de movimento inválida */

	REC_CondRetPosicaoInvalida = 9,
		/* Posição inválida da peça no tabuleiro */

	REC_CondRetNaoAdicionouProx = 10,
		/* Erro ao adicionar peça como próxima */

	REC_CondRetReiNaoExiste = 11,
		/* Rei não foi encontrado no tabuleiro */

	REC_CondRetXequeMate = 12 ,
		/* Rei em Xeque Mate */

	REC_CondRetNaoEstaEmXequeMate = 13 ,
		/* Rei não está em Xeque Mate */

}REC_tpCondRet;

/***** Declarações importadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct GER_tgPeca * GER_tppPeca;

/* Tipo referência para um grafo */

typedef struct GRA_tgGrafo * GRA_tppGrafo;

/***********************************************************************
*
*  $FC Função: REC &Adicionar Peças ao Grafo
*
*  $ED Descrição da função
*     Cria um grafo e, a partir do tabuleiro montado pelo módulo GERENCI-
*	  ADOR e do arquivo de regras de movimentação, constrói um grafo com 
*	  as movimentações possíveis das peças.
*
*  $EP Parâmetros
*     ppGrafo - endereço da referência que apontará para o grafo criado
*
*  $FV Valor retornado
*     REC_CondRetOK - adicionou as peças sem problemas
*	  REC_CondRetNaoCriouGrafo - erro ao criar o grafo
*	  REC_CondRetNaoCriouVertice - erro ao criar o vértice
*	  REC_CondRetNaoInseriuPeca - erro ao inserir o vértice
*
***********************************************************************/

   REC_tpCondRet REC_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo );

/***********************************************************************
*
*  $FC Função: REC &Adicionar Peças ao Grafo
*
*  $ED Descrição da função
*     Cria um grafo e, a partir do tabuleiro montado pelo módulo GERENCI-
*	  ADOR e do arquivo de regras de movimentação, constrói um grafo com 
*	  as movimentações possíveis das peças.
*
*  $EP Parâmetros
*     ppGrafo - endereço da referência que apontará para o grafo criado
*
*  $FV Valor retornado
*     REC_CondRetOK - adicionou as peças sem problemas
*	  REC_CondRetNaoCriouGrafo - erro ao criar o grafo
*	  REC_CondRetNaoCriouVertice - erro ao criar o vértice
*	  REC_CondRetNaoInseriuPeca - erro ao inserir o vértice
*
***********************************************************************/
   
   REC_tpCondRet REC_GeraMovimentacoes ( GRA_tppGrafo * ppGrafo );
   
/********** Fim do módulo de definição: Módulo grafo **********/