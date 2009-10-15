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

		 GER_CondRetTipoInvalido = 5,

		 GER_CondRetCorInvalida = 6,

   } GER_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: GER Cores de Peças
*
*
***********************************************************************/

   typedef enum {

		 GER_tpCorBranca = 0 ,
               /* Peça de cor branca */

	     GER_tpCorPreta = 1 ,
			   /* Peça de cor preta */

		 GER_tpCorSemCor = 2
				/* Peça vazia */

   } GER_tpCorPeca ;
/***********************************************************************
*
*  $TC Tipo de dados: GER Tipos de Peças
*
*
***********************************************************************/

   typedef enum {

		 GER_tpTipoPeao = 0 ,
               /* Peça do tipo peão */

	     GER_tpTipoTorre = 1 ,
			   /* Peça do tipo torre */

		 GER_tpTipoCavalo = 2 ,
               /* Peça do tipo cavalo */

	     GER_tpTipoBispo = 3 ,
			   /* Peça do tipo bispo */

		 GER_tpTipoDama = 4 ,
				/* Peça do tipo dama */

	     GER_tpTipoRei = 5 ,
				/* Peça do tipo rei */

		 GER_tpTipoVazia = 6
				/* Peça vazia */
			   
   } GER_tpTipoPeca ;

   typedef struct tgPeca * tppPeca;

   tppPeca GER_CriarPeca ( GER_tpTipoPeca tipo , GER_tpCorPeca cor , char* movimentosPossiveis );

   GER_tpCondRet GER_AtribuirPeca ( tppPeca pPeca , GER_tpTipoPeca tipo , GER_tpCorPeca cor , char* movimentosPossiveis );
   
   GER_tpCondRet GER_InicializarTabuleiro ( void );

   GER_tpCondRet GER_PreencherTabuleiro ( char * ArquivoDisposicao );

   int GER_ObterUltimaLinhaTabuleiro ( void );

   char GER_ObterUltimaColunaTabuleiro ( void );

   GER_tpCondRet GER_ObterPecaDoTabuleiro ( tppPeca * pPeca, char coluna, int linha );

   GER_tpTipoPeca GER_ObterTipo ( tppPeca pPeca ) ;

   GER_tpCorPeca GER_ObterCor ( tppPeca pPeca ) ;