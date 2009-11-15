#if ! defined( GERENCIADOR_ )
#define GERENCIADOR_
/***************************************************************************
*
*  $MCD Módulo de definição: GER  Gerenciador de Xadrez
*
*  Arquivo gerado:              GERENCIADOR.H
*  Letras identificadoras:      GER
*
*  Projeto: INF 1301 - Programação Modular
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio ´D'Angelo , Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   12/set/2009 Início desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
*  $ED Descrição do módulo
*	Este módulo corresponde à implementação do gerenciador de jogos de xadrez.
*	Ele define um tipo correspondente às peças do jogo, que possuem um tipo e
*	uma cor. As cores possíveis são preta e branca e os tipos possíveis corres-
*	pondem às peças do xadrez tradicional ( peão, torre, cavalo, bispo, dama e
*	rei ). Também existe a "peça" correspondente a casa vazia do tabuleiro. Des-
*	sa forma, cada casa do tabuleiro possui uma "peça" correspondente, mesmo que
*	a casa esteja vazia.
*	Este módulo oferece as funcionalidades paraa, a partir de um arquivo com a
*	disposição das peças, montar um tabuleiro com cada peça em sua posição cor-
*	reta. Ele não oferece suporte à movimentação de peças. 
*	Em um dado momento, só pode haver um único tabuleiro de xadrez.
*
***************************************************************************/

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct GER_tgPeca * GER_tppPeca;

/***********************************************************************
*
*  $TC Tipo de dados: GER Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

		 GER_CondRetOK = 0 ,
               /* Executou correto */

	     GER_CondRetFaltouMemoria = 1 ,
			   /* Faltou memória ao alocar dados */

	     GER_CondRetArqDispInvalido = 2,
				/* Sintaxe inválida do arquivo de disposição das peças */

		 GER_CondRetArqInexistente = 3,
				/* Arquivo não foi encontrado */

		 GER_CondRetPecaNaoExiste = 4,
				/* Peça não foi encontrada */

		 GER_CondRetTipoInvalido = 5,
				/* Tipo de peça é inválido */

		 GER_CondRetCorInvalida = 6,
				/* Cor da Peça é inválida */

		 GER_CondRetErroAoAbrirArq = 7,
				/* Não conseguiu abrir arquivo corretamente */

		 GER_CondRetErroAoSalvarTabuleiro = 8,
				/* Não conseguiu salvar o tabuleiro */

   } GER_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: GER Cores de Peças
*
*
***********************************************************************/

   typedef enum {

		 GER_CorBranca = 0 ,
               /* Peça de cor branca */

	     GER_CorPreta = 1 ,
			   /* Peça de cor preta */

		 GER_CorSemCor = 2
				/* Casa vazia */

   } GER_tpCorPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: GER Tipos de Peças
*
*
***********************************************************************/

   typedef enum {

		 GER_TipoPeao = 0 ,
               /* Peça do tipo peão */

	     GER_TipoTorre = 1 ,
			   /* Peça do tipo torre */

		 GER_TipoCavalo = 2 ,
               /* Peça do tipo cavalo */

	     GER_TipoBispo = 3 ,
			   /* Peça do tipo bispo */

		 GER_TipoDama = 4 ,
				/* Peça do tipo dama */

	     GER_TipoRei = 5 ,
				/* Peça do tipo rei */

		 GER_TipoVazia = 6
				/* Casa vazia */
			   
   } GER_tpTipoPeca ;

/***********************************************************************
*
*  $FC Função: GER  &Criar Peça
*
*  $ED Descrição da função
*     Cria um peça da cor e tipo passados por parâmetros.
*
*  $EP Parâmetros
*     Tipo	- Tipo da peça ou casa vazia
*	  Cor	- Cor da peça ou casa vazia
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a peça.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*	  Também retornará NULL se for passada uma cor ou tipo para uma casa
*	  vazia.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   GER_tppPeca GER_CriarPeca ( GER_tpTipoPeca Tipo , GER_tpCorPeca Cor );

/***********************************************************************
*
*  $FC Função: GER  &Destruir Peça
*
*  $ED Descrição da função
*     Destroi a peça passada por parâmetro.
*
*  $EP Parâmetros
*     ppPeca - endereço da referência para a peça a ser destruída
*
***********************************************************************/

   void GER_DestruirPeca ( GER_tppPeca * ppPeca  ) ;

/***********************************************************************
*
*  $FC Função: GER  &Atribuir Peça
*
*  $ED Descrição da função
*     Altera os atributos das peça.
*
*  $EP Parâmetros
*	  pPeca	- referência para a peça a ser alterada
*     Tipo	- Tipo da peça ou casa vazia
*	  Cor	- Cor da peça ou casa vazia
*
*  $FV Valor retornado
*	  GER_CondRetOK - atribuiu sem problemas
*	  GER_CondRetPecaNaoExiste - a referência passsada não referencia uma peça
*	  GER_CondRetTipoInvalido - o tipo da peça passado é inválido
*	  GER_CondRetCorInvalida - a cor da peça passada é inválida
*
***********************************************************************/

   GER_tpCondRet GER_AtribuirPeca ( GER_tppPeca pPeca , GER_tpTipoPeca Tipo , GER_tpCorPeca Cor );

/***********************************************************************
*
*  $FC Função: GER  &Inicializar Tabuleiro
*
*  $ED Descrição da função
*     Cria o tabuleiro de peças e o preenche com casas vazias.
*
*  $FV Valor retornado
*	  GER_CondRetOK - inicializou sem problemas
*	  GER_CondRetFaltouMemoria - faltou memória para alocar o tabuleiro
*
***********************************************************************/

   GER_tpCondRet GER_InicializarTabuleiro ( void );

/***********************************************************************
*
*  $FC Função: GER  &Limpar Tabuleiro
*
*  $ED Descrição da função
*     Destrói as peças do tabuleiro.
*
***********************************************************************/

   void GER_LimparTabuleiro ( void );
/***********************************************************************
*
*  $FC Função: GER  &Preencher Tabuleiro
*
*  $ED Descrição da função
*     Preenche o tabuleiro com peças de acordo com o arquivo de disposição.
*
*  $EP Parâmetros
*	  ArquivoDisposicao - arquivo contendo a disposição das peças
*		obs: ver LEIAME.TXT para conferir as regras de redação deste arquivo
*
*  $FV Valor retornado
*	  GER_CondRetOK - preencheu sem problemas
*	  GER_CondRetArquivoInexistente - o arquivo passado não foi encontrado
*	  GER_CondRetArqDisposicaoInvalido - se o arquivo passado possui ao me-
*		uma linha que não respeite a sintaxe correta
*	  GER_CondtRetPecaNaoExiste - a peça referenciada não foi encontrada
*	  GER_CondRetTipoInvalido - o tipo da peça passado é inválido
*	  GER_CondRetCorInvalida - a cor da peça passada é inválida	  
*
***********************************************************************/

   GER_tpCondRet GER_PreencherTabuleiro ( char * ArquivoDisposicao );

/***********************************************************************
*
*  $FC Função: GER  &Obter última linha do tabuleiro
*
*  $ED Descrição da função
*     Obtém o número da última linha do tabuleiro.
*
*  $FV Valor retornado
*	  Retorna o número da última linha do tabuleiro.  
*
***********************************************************************/

   int GER_ObterUltimaLinhaTabuleiro ( void );

/***********************************************************************
*
*  $FC Função: GER  &Obter última coluna do tabuleiro
*
*  $ED Descrição da função
*     Obtém a letra da última coluna do tabuleiro.
*
*  $FV Valor retornado
*	  Retorna a letra da última coluna do tabuleiro.  
*
***********************************************************************/

   char GER_ObterUltimaColunaTabuleiro ( void );

/***********************************************************************
*
*  $FC Função: GER  &Obter Peça do Tabuleiro
*
*  $ED Descrição da função
*     Obtém uma peça do tabuleiro dada a posição da peça
*
*  $EP Parâmetros
*	  ppPeca - endereço da referência de onde a peça será armazenada
*	  Coluna - letra da coluna da peça
*	  Linha - número da linha da peça
*
*  $FV Valor retornado
*	  GER_CondRetOK - encontrou sem problemas
*	  GER_CondtRetPecaNaoExiste - a peça não foi encontrada
*
***********************************************************************/

   GER_tpCondRet GER_ObterPecaDoTabuleiro ( GER_tppPeca * ppPeca, char Coluna, int Linha );

/***********************************************************************
*
*  $FC Função: GER  &Obter Tipo da Peça
*
*  $ED Descrição da função
*     Obtém o tipo de uma dada peça.
*
*  $EP Parâmetros
*	  pPeca - referência para peça de que se quer saber o tipo
*
*  $FV Valor retornado
*	  Retorna o tipo da peça ou se a casa está vazia	  
*
***********************************************************************/

   GER_tpTipoPeca GER_ObterTipo ( GER_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Função: GER  &Obter Cor da Peça
*
*  $ED Descrição da função
*     Obtém a cor de uma dada peça.
*
*  $EP Parâmetros
*	  pPeca - referência para peça de que se quer saber a cor
*
*  $FV Valor retornado
*	  Retorna a cor da peça ou se a casa está vazia	  
*
***********************************************************************/

   GER_tpCorPeca GER_ObterCor ( GER_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Função: GER  &Obter Código da Cor
*
*  $ED Descrição da função
*     Dada a inicial da cor, obtém o código desta cor
*
*  $EP Parâmetros
*	  Cor - inicial da cor
*
*  $FV Valor retornado
*	  Retorna o código da cor utilizado pelo programa	  
*
***********************************************************************/

   GER_tpCorPeca GER_ObterCodigoDaCor ( char Cor );
   
/***********************************************************************
*
*  $FC Função: GER  &Obter Código do Tipo
*
*  $ED Descrição da função
*     Dada a inicial do tipo da peça, obtém o código deste tipo
*
*  $EP Parâmetros
*	  Tipo - inicial do tipo da peça
*
*  $FV Valor retornado
*	  Retorna o código do tipo utilizado pelo programa	  
*
***********************************************************************/

   GER_tpTipoPeca GER_ObterCodigoDoTipo ( char Tipo );

/***********************************************************************
*
*  $FC Função: GER  &Obter Rei
*
*  $ED Descrição da função
*     Obtém a posição do rei da cor dada no tabuleiro
*
*  $EP Parâmetros
*	  Cor - cor do rei procurado
*	  pColuna - referência para onde será a letra da coluna
*	  pLinha - referência para onde será armazenado número da linha
*
*  $FV Valor retornado
*	  GER_CondRetOK - encontrou sem problemas
*	  GER_CondRetPecaNaoExiste - a peça não foi encontrada  
*
***********************************************************************/

   GER_tpCondRet GER_ObterRei ( GER_tpCorPeca Cor , char * pColuna , int * pLinha ) ;

/***********************************************************************
*
*  $FC Função: GER  &Mover Peca
*
*  $ED Descrição da função
*     Move uma peça no tabuleiro
*
*  $EP Parâmetros
*	  pPecaOrigem - ponteiro para a casa onde está a peça
*	  pPecaDestino - ponteiro para a casa para onde vai a peça
*
*  $FV Valor retornado
*	  GER_CondRetOK - moveu sem problemas
*
***********************************************************************/

	GER_tpCondRet GER_MoverPeca ( GER_tppPeca pPecaOrigem , GER_tppPeca pPecaDestino ) ;

/***********************************************************************
*
*  $FC Função: GER  &Alterar Cor da Vez
*
*  $ED Descrição da função
*     Passa a vez para o outro jogador.
*
***********************************************************************/

	void GER_AlterarCorDaVez ( void ) ;

/***********************************************************************
*
*  $FC Função: GER  &Obter Cor da Vez
*
*  $ED Descrição da função
*     Obtém a cor do jogador da vez.
*
*  $FV Valor retornado
*	  GER_CorBranca ou GER_CorPreta
*
*  $ED Descrição do módulo
*	  Só pode ser chamada após a GER_PreencherTabuleiro já tiver sido
*	  executada
*
***********************************************************************/

	GER_tpCorPeca GER_ObterCorDaVez ( void ) ;

/***********************************************************************
*
*  $FC Função: GER  &Salvar Tabuleiro
*
*  $ED Descrição da função
*     Salva o estado atual do jogo em um arquivo de disposição
*
*  $EP Parâmetros
*	  ArquivoDisposicao - nome do arquivo onde o estado será salvo
*
*  $FV Valor retornado
*	  GER_CondRetOK
*	  GER_Arquivo
*
***********************************************************************/

	GER_tpCondRet GER_SalvarTabuleiro ( char * ArquivoDisposicao );

/***********************************************************************
*
*  $FC Função: GER  &Imprimir Tabuleiro
*
*  $ED Descrição da função
*     Imprime o estado atual do tabuleiro na tela
*
***********************************************************************/

	void GER_ImprimirTabuleiro ( void );

/********** Fim do módulo de definição: GER  Gerenciador de xadrez **********/

#else
#endif