/***************************************************************************
*  $MCD Módulo de definição: PAR Realizador de partidas de Xadrez
*
*  Arquivo gerado:              PARTIDA.H
*  Letras identificadoras:      PAR
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   13/nov/2009 Início desenvolvimento
*	  1		  cev	19/nov/2009 Entrega do trabalho
*
*  $ED Descrição do módulo
*     Este módulo implementa as funções para a realização de partidas de xadrez
*
*
/***********************************************************************
*
*  $TC Tipo de dados: PAR Condicoes de retorno
*
*
***********************************************************************/

typedef enum{

	PAR_CondRetOK = 0,
		/* Executou corretamente */

	PAR_CondRetArquivoNaoExiste = 1,
		/* O arquivo passado não existe no diretório especificado */

	PAR_CondRetArquivoInvalido = 2,
		/* O arquivo passado não respeita a sintaxe correta */

	PAR_CondRetFaltouMemoria = 3,
		/* Faltou memória para ser alocada */

}PAR_tpCondRet;

/***** Declarações importadas pelo módulo *****/


/***********************************************************************
*
*  $FC Função: PAR &
*
*  $ED Descrição da função
*
*  $EP Parâmetros
*
*  $FV Valor retornado
*
***********************************************************************/

   void PAR_IniciarPartida();

/***********************************************************************
*
*  $FC Função: PAR &
*
*  $ED Descrição da função
*
*  $EP Parâmetros
*
*  $FV Valor retornado
*
***********************************************************************/
   
   //PAR_tpCondRet PAR_GeraMovimentacoes ( GRA_tppGrafo * ppGrafo );

/***********************************************************************
*
*  $FC Função: PAR &
*
*  $ED Descrição da função
*
*  $EP Parâmetros
*
*  $FV Valor retornado
*	  
*
***********************************************************************/
   
   //PAR_tpCondRet PAR_ReconhecerXequeMate ( char cCor, GRA_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Função: PAR &
*
*  $ED Descrição da função
*
*  $EP Parâmetros
*
*  $FV Valor retornado
*
***********************************************************************/
   
   //PAR_tpCondRet PAR_MoverPeca ( char ColunaOrigem , int LinhaOrigem , char ColunaDestino , int LinhaDestino , GRA_tppGrafo pGrafo );

/***********************************************************************/