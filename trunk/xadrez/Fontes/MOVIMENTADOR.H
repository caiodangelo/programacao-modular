/***************************************************************************
*  $MCD Módulo de definição: MOV Movimentador de peças de Xadrez
*
*  Arquivo gerado:              MOVIMENTADOR.H
*  Letras identificadoras:      MOV
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
*  $TC Tipo de dados: MOV Condicoes de retorno
*
*
***********************************************************************/

typedef enum{

	MOV_CondRetOK = 0,
		/* Executou corretamente */

	MOV_CondRetArquivoNaoExiste = 1,
		/* O arquivo passado não existe no diretório especificado */

	MOV_CondRetArquivoInvalido = 2,
		/* O arquivo passado não respeita a sintaxe correta */

	MOV_CondRetFaltouMemoria = 3,
		/* Faltou memória para ser alocada */

	MOV_CondRetNaoCriouGrafo = 4,
		/* O grafo para armazenar as peças não pôde ser criado */

	MOV_CondRetNaoCriouVertice = 5,
		/* Um vértice do grafo não pôde ser criado */

	MOV_CondRetNaoInseriuPeca = 6,
		/* Não conseguiu inserir a peça */

	MOV_CondRetErroNaStringDeMovimento = 7,
		/* String de movimento inválida */

	MOV_CondRetPosicaoInvalida = 9,
		/* Posição inválida da peça no tabuleiro */

	MOV_CondRetNaoAdicionouProx = 10,
		/* Erro ao adicionar peça como próxima */

	MOV_CondRetReiNaoExiste = 11,
		/* Rei não foi encontrado no tabuleiro */

	MOV_CondRetXequeMate = 12 ,
		/* Rei em Xeque Mate */

	MOV_CondRetNaoEstaEmXequeMate = 13 ,
		/* Rei não está em Xeque Mate */

	MOV_CondRetChegouEmPeca = 14 ,
		/* Sucessor contém peça */

}MOV_tpCondRet;

/***** Declarações importadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct GER_tgPeca * GER_tppPeca;

/* Tipo referência para um grafo */

typedef struct GRA_tgGrafo * GRA_tppGrafo;


/***********************************************************************
*
*  $FC Função: MOV &Adicionar Peças ao Grafo
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
*     MOV_CondRetOK - adicionou as peças sem problemas
*	  MOV_CondRetNaoCriouGrafo - erro ao criar o grafo
*	  MOV_CondRetNaoCriouVertice - erro ao criar o vértice
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir o vértice
*
***********************************************************************/

   MOV_tpCondRet MOV_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo );

/***********************************************************************
*
*  $FC Função: MOV &Adicionar Peças ao Grafo
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
*     MOV_CondRetOK - adicionou as peças sem problemas
*	  MOV_CondRetNaoCriouGrafo - erro ao criar o grafo
*	  MOV_CondRetNaoCriouVertice - erro ao criar o vértice
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir o vértice
*
***********************************************************************/
   
   MOV_tpCondRet MOV_GeraMovimentacoes ( GRA_tppGrafo * ppGrafo );

/***********************************************************************
*
*  $FC Função: MOV &Reconhecer Xeque Mate
*
*  $ED Descrição da função
*     A partir do grafo de movimentações, reconhece se o rei de uma deter-
*	  minada cor está em xeque mate.
*
*  $EP Parâmetros
*     ppGrafo - referência para o grafo de movimentações
*	  CorRei - cor do rei que pode estar em xeque
*
*  $FV Valor retornado
*	  MOV_CondRetNaoEstaEmXequeMate - rei na cor fonecida não está em xeque mate
*	  MOV_CondRetXequeMate - rei da cor fornecida está em xeque mate
*	  
*
***********************************************************************/
   
   MOV_tpCondRet MOV_ReconhecerXequeMate ( char Cor );

   
/********** Fim do módulo de definição: Módulo grafo **********/