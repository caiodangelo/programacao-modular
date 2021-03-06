#if ! defined( GERENCIADOR_ )
#define GERENCIADOR_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: GER  Gerenciador de Xadrez
*
*  Arquivo gerado:              GERENCIADOR.H
*  Letras identificadoras:      GER
*
*  Projeto: INF 1301 - Programa��o Modular
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio �D'Angelo , Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     0       cev   12/set/2009 In�cio desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
*  $ED Descri��o do m�dulo
*	Este m�dulo corresponde � implementa��o do gerenciador de jogos de xadrez.
*	Ele define um tipo correspondente �s pe�as do jogo, que possuem um tipo e
*	uma cor. As cores poss�veis s�o preta e branca e os tipos poss�veis corres-
*	pondem �s pe�as do xadrez tradicional ( pe�o, torre, cavalo, bispo, dama e
*	rei ). Tamb�m existe a "pe�a" correspondente a casa vazia do tabuleiro. Des-
*	sa forma, cada casa do tabuleiro possui uma "pe�a" correspondente, mesmo que
*	a casa esteja vazia.
*	Este m�dulo oferece as funcionalidades paraa, a partir de um arquivo com a
*	disposi��o das pe�as, montar um tabuleiro com cada pe�a em sua posi��o cor-
*	reta. Ele n�o oferece suporte � movimenta��o de pe�as. 
*	Em um dado momento, s� pode haver um �nico tabuleiro de xadrez.
*
***************************************************************************/

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pe�a */

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
			   /* Faltou mem�ria ao alocar dados */

	     GER_CondRetArqDispInvalido = 2,
				/* Sintaxe inv�lida do arquivo de disposi��o das pe�as */

		 GER_CondRetArqInexistente = 3,
				/* Arquivo n�o foi encontrado */

		 GER_CondRetPecaNaoExiste = 4,
				/* Pe�a n�o foi encontrada */

		 GER_CondRetTipoInvalido = 5,
				/* Tipo de pe�a � inv�lido */

		 GER_CondRetCorInvalida = 6,
				/* Cor da Pe�a � inv�lida */

		 GER_CondRetErroAoAbrirArq = 7,
				/* N�o conseguiu abrir arquivo corretamente */

		 GER_CondRetErroAoSalvarTabuleiro = 8,
				/* N�o conseguiu salvar o tabuleiro */

   } GER_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: GER Cores de Pe�as
*
*
***********************************************************************/

   typedef enum {

		 GER_CorBranca = 0 ,
               /* Pe�a de cor branca */

	     GER_CorPreta = 1 ,
			   /* Pe�a de cor preta */

		 GER_CorSemCor = 2
				/* Casa vazia */

   } GER_tpCorPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: GER Tipos de Pe�as
*
*
***********************************************************************/

   typedef enum {

		 GER_TipoPeao = 0 ,
               /* Pe�a do tipo pe�o */

	     GER_TipoTorre = 1 ,
			   /* Pe�a do tipo torre */

		 GER_TipoCavalo = 2 ,
               /* Pe�a do tipo cavalo */

	     GER_TipoBispo = 3 ,
			   /* Pe�a do tipo bispo */

		 GER_TipoDama = 4 ,
				/* Pe�a do tipo dama */

	     GER_TipoRei = 5 ,
				/* Pe�a do tipo rei */

		 GER_TipoVazia = 6
				/* Casa vazia */
			   
   } GER_tpTipoPeca ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Criar Pe�a
*
*  $ED Descri��o da fun��o
*     Cria um pe�a da cor e tipo passados por par�metros.
*
*  $EP Par�metros
*     Tipo	- Tipo da pe�a ou casa vazia
*	  Cor	- Cor da pe�a ou casa vazia
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a pe�a.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*	  Tamb�m retornar� NULL se for passada uma cor ou tipo para uma casa
*	  vazia.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   GER_tppPeca GER_CriarPeca ( GER_tpTipoPeca Tipo , GER_tpCorPeca Cor );

/***********************************************************************
*
*  $FC Fun��o: GER  &Destruir Pe�a
*
*  $ED Descri��o da fun��o
*     Destroi a pe�a passada por par�metro.
*
*  $EP Par�metros
*     ppPeca - endere�o da refer�ncia para a pe�a a ser destru�da
*
***********************************************************************/

   void GER_DestruirPeca ( GER_tppPeca * ppPeca  ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Atribuir Pe�a
*
*  $ED Descri��o da fun��o
*     Altera os atributos das pe�a.
*
*  $EP Par�metros
*	  pPeca	- refer�ncia para a pe�a a ser alterada
*     Tipo	- Tipo da pe�a ou casa vazia
*	  Cor	- Cor da pe�a ou casa vazia
*
*  $FV Valor retornado
*	  GER_CondRetOK - atribuiu sem problemas
*	  GER_CondRetPecaNaoExiste - a refer�ncia passsada n�o referencia uma pe�a
*	  GER_CondRetTipoInvalido - o tipo da pe�a passado � inv�lido
*	  GER_CondRetCorInvalida - a cor da pe�a passada � inv�lida
*
***********************************************************************/

   GER_tpCondRet GER_AtribuirPeca ( GER_tppPeca pPeca , GER_tpTipoPeca Tipo , GER_tpCorPeca Cor );

/***********************************************************************
*
*  $FC Fun��o: GER  &Inicializar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria o tabuleiro de pe�as e o preenche com casas vazias.
*
*  $FV Valor retornado
*	  GER_CondRetOK - inicializou sem problemas
*	  GER_CondRetFaltouMemoria - faltou mem�ria para alocar o tabuleiro
*
***********************************************************************/

   GER_tpCondRet GER_InicializarTabuleiro ( void );

/***********************************************************************
*
*  $FC Fun��o: GER  &Limpar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Destr�i as pe�as do tabuleiro.
*
***********************************************************************/

   void GER_LimparTabuleiro ( void );
/***********************************************************************
*
*  $FC Fun��o: GER  &Preencher Tabuleiro
*
*  $ED Descri��o da fun��o
*     Preenche o tabuleiro com pe�as de acordo com o arquivo de disposi��o.
*
*  $EP Par�metros
*	  ArquivoDisposicao - arquivo contendo a disposi��o das pe�as
*		obs: ver LEIAME.TXT para conferir as regras de reda��o deste arquivo
*
*  $FV Valor retornado
*	  GER_CondRetOK - preencheu sem problemas
*	  GER_CondRetArquivoInexistente - o arquivo passado n�o foi encontrado
*	  GER_CondRetArqDisposicaoInvalido - se o arquivo passado possui ao me-
*		uma linha que n�o respeite a sintaxe correta
*	  GER_CondtRetPecaNaoExiste - a pe�a referenciada n�o foi encontrada
*	  GER_CondRetTipoInvalido - o tipo da pe�a passado � inv�lido
*	  GER_CondRetCorInvalida - a cor da pe�a passada � inv�lida	  
*
***********************************************************************/

   GER_tpCondRet GER_PreencherTabuleiro ( char * ArquivoDisposicao );

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter �ltima linha do tabuleiro
*
*  $ED Descri��o da fun��o
*     Obt�m o n�mero da �ltima linha do tabuleiro.
*
*  $FV Valor retornado
*	  Retorna o n�mero da �ltima linha do tabuleiro.  
*
***********************************************************************/

   int GER_ObterUltimaLinhaTabuleiro ( void );

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter �ltima coluna do tabuleiro
*
*  $ED Descri��o da fun��o
*     Obt�m a letra da �ltima coluna do tabuleiro.
*
*  $FV Valor retornado
*	  Retorna a letra da �ltima coluna do tabuleiro.  
*
***********************************************************************/

   char GER_ObterUltimaColunaTabuleiro ( void );

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter Pe�a do Tabuleiro
*
*  $ED Descri��o da fun��o
*     Obt�m uma pe�a do tabuleiro dada a posi��o da pe�a
*
*  $EP Par�metros
*	  ppPeca - endere�o da refer�ncia de onde a pe�a ser� armazenada
*	  Coluna - letra da coluna da pe�a
*	  Linha - n�mero da linha da pe�a
*
*  $FV Valor retornado
*	  GER_CondRetOK - encontrou sem problemas
*	  GER_CondtRetPecaNaoExiste - a pe�a n�o foi encontrada
*
***********************************************************************/

   GER_tpCondRet GER_ObterPecaDoTabuleiro ( GER_tppPeca * ppPeca, char Coluna, int Linha );

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter Tipo da Pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m o tipo de uma dada pe�a.
*
*  $EP Par�metros
*	  pPeca - refer�ncia para pe�a de que se quer saber o tipo
*
*  $FV Valor retornado
*	  Retorna o tipo da pe�a ou se a casa est� vazia	  
*
***********************************************************************/

   GER_tpTipoPeca GER_ObterTipo ( GER_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter Cor da Pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m a cor de uma dada pe�a.
*
*  $EP Par�metros
*	  pPeca - refer�ncia para pe�a de que se quer saber a cor
*
*  $FV Valor retornado
*	  Retorna a cor da pe�a ou se a casa est� vazia	  
*
***********************************************************************/

   GER_tpCorPeca GER_ObterCor ( GER_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter C�digo da Cor
*
*  $ED Descri��o da fun��o
*     Dada a inicial da cor, obt�m o c�digo desta cor
*
*  $EP Par�metros
*	  Cor - inicial da cor
*
*  $FV Valor retornado
*	  Retorna o c�digo da cor utilizado pelo programa	  
*
***********************************************************************/

   GER_tpCorPeca GER_ObterCodigoDaCor ( char Cor );
   
/***********************************************************************
*
*  $FC Fun��o: GER  &Obter C�digo do Tipo
*
*  $ED Descri��o da fun��o
*     Dada a inicial do tipo da pe�a, obt�m o c�digo deste tipo
*
*  $EP Par�metros
*	  Tipo - inicial do tipo da pe�a
*
*  $FV Valor retornado
*	  Retorna o c�digo do tipo utilizado pelo programa	  
*
***********************************************************************/

   GER_tpTipoPeca GER_ObterCodigoDoTipo ( char Tipo );

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter Rei
*
*  $ED Descri��o da fun��o
*     Obt�m a posi��o do rei da cor dada no tabuleiro
*
*  $EP Par�metros
*	  Cor - cor do rei procurado
*	  pColuna - refer�ncia para onde ser� a letra da coluna
*	  pLinha - refer�ncia para onde ser� armazenado n�mero da linha
*
*  $FV Valor retornado
*	  GER_CondRetOK - encontrou sem problemas
*	  GER_CondRetPecaNaoExiste - a pe�a n�o foi encontrada  
*
***********************************************************************/

   GER_tpCondRet GER_ObterRei ( GER_tpCorPeca Cor , char * pColuna , int * pLinha ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Mover Peca
*
*  $ED Descri��o da fun��o
*     Move uma pe�a no tabuleiro
*
*  $EP Par�metros
*	  pPecaOrigem - ponteiro para a casa onde est� a pe�a
*	  pPecaDestino - ponteiro para a casa para onde vai a pe�a
*
*  $FV Valor retornado
*	  GER_CondRetOK - moveu sem problemas
*
***********************************************************************/

	GER_tpCondRet GER_MoverPeca ( GER_tppPeca pPecaOrigem , GER_tppPeca pPecaDestino ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Alterar Cor da Vez
*
*  $ED Descri��o da fun��o
*     Passa a vez para o outro jogador.
*
***********************************************************************/

	void GER_AlterarCorDaVez ( void ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Obter Cor da Vez
*
*  $ED Descri��o da fun��o
*     Obt�m a cor do jogador da vez.
*
*  $FV Valor retornado
*	  GER_CorBranca ou GER_CorPreta
*
*  $ED Descri��o do m�dulo
*	  S� pode ser chamada ap�s a GER_PreencherTabuleiro j� tiver sido
*	  executada
*
***********************************************************************/

	GER_tpCorPeca GER_ObterCorDaVez ( void ) ;

/***********************************************************************
*
*  $FC Fun��o: GER  &Salvar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Salva o estado atual do jogo em um arquivo de disposi��o
*
*  $EP Par�metros
*	  ArquivoDisposicao - nome do arquivo onde o estado ser� salvo
*
*  $FV Valor retornado
*	  GER_CondRetOK
*	  GER_Arquivo
*
***********************************************************************/

	GER_tpCondRet GER_SalvarTabuleiro ( char * ArquivoDisposicao );

/***********************************************************************
*
*  $FC Fun��o: GER  &Imprimir Tabuleiro
*
*  $ED Descri��o da fun��o
*     Imprime o estado atual do tabuleiro na tela
*
***********************************************************************/

	void GER_ImprimirTabuleiro ( void );

/********** Fim do m�dulo de defini��o: GER  Gerenciador de xadrez **********/

#else
#endif