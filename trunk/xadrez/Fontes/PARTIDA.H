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

}PAR_tpCondRet;

/***** Declarações importadas pelo módulo *****/


/***********************************************************************
*
*  $FC Função: PAR &Iniciar Partida
*
*  $ED Descrição da função*
*  Provê ao usuário as opções iniciais para iniciar uma partida ou
*  retomar um jogo salvo.
*
***********************************************************************/

   void PAR_IniciarPartida();

/********** Fim do módulo de definição: PAR Realizador de partidas de Xadrez **********/