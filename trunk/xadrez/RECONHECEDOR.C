/***************************************************************************
*  $MCI Módulo de implementação: REC Reconhecedor de Xeque Mate
*
*  Arquivo gerado:              RECONHECEDOR.C
*  Letras identificadoras:      REC
*
*  Projeto: INF 1301 Programação Modular
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo , Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   12/set/2009 Início desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
***************************************************************************/
#include "GERENCIADOR.H"
#include "RECONHECEDOR.H"
#include "GRAFO.H"
#include <stdio.h>
#include <stdlib.h>

#define TAM_MOVIMENTO 10
#define REGRASD "REGRASD.TXT"
#define REGRASC "REGRASC.TXT"
#define INX_TIPO 0

/***** Protótipos das funções encapsuladas no módulo *****/

int CodificaPosicao ( char Coluna , int Linha );

REC_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo,  char ColunaCorrente, int LinhaCorrente ,  char ColunaProximo, int LinhaProximo,char TipoDaCasa, GER_tpCorPeca p );

REC_tpCondRet AdicionaProximosDiscretos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente );

REC_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimentos, char Coluna, int Linha );

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: REC  &Adicionar Pecas Ao Grafo
*  ****/

REC_tpCondRet REC_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo ){
	
	/* Declaração das variáveis locais */
	int linha;
	int coluna;
	GER_tpCondRet CondRetGER;
	GRA_tpCondRet CondRetGRA;
	GER_tppPeca pPeca;
	int id;
	
	/* Cria o grafo */
	CondRetGRA = GRA_CriarGrafo ( ppGrafo );
	if ( CondRetGRA != GRA_CondRetOK ){
		return REC_CondRetNaoCriouGrafo;
	}

	/* Percorre o tabuleiro */
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){
			
			/* Obtém a peça do tabuleiro */
			CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if ( CondRetGER != GER_CondRetOK ){
				return REC_CondRetNaoCriouVertice;
			}

			/* Gera o identificador da peça */
			id = CodificaPosicao ( (char)coluna , linha );
			
			/* Insere a peça no grafo com o id gerado */
			CondRetGRA = GRA_InserirVertice ( *ppGrafo , pPeca , id );

			if ( CondRetGRA != GRA_CondRetOK ){

				return REC_CondRetNaoInseriuPeca;
			}
		}
	}

	return REC_CondRetOK ;
} /* Fim da Função: REC  &Adicionar Pecas Ao Grafo */

/***************************************************************************
*
*  Função: REC  &Gera Movimentações
*  ****/
REC_tpCondRet REC_GeraMovimentacoes ( GRA_tppGrafo * ppGrafo ){
	FILE * ArquivoDeRegras;
	GRA_tppGrafo pGrafo = * ppGrafo;
	int linha;
	int coluna;
	GER_tpCondRet CondRetGer;
	GER_tppPeca pPeca;
	char movimentos[TAM_MOVIMENTO];
	GER_tpTipoPeca TipoPeca;

	/* Verifica se o grafo está criado */
	if ( pGrafo == NULL )
	{
		return REC_CondRetNaoCriouGrafo ;
	}

	/* Percorre todas as peças do tabuleiro */
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){

			/* Obtém a peça do tabuleiro */
			CondRetGer = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if (CondRetGer != GER_CondRetOK )
			{
				return REC_CondRetPosicaoInvalida ;
			}

			/* Obtém o tipo da peça */
			TipoPeca = GER_ObterTipo ( pPeca );
			if ( TipoPeca == -1 )
			{
				return REC_CondRetPosicaoInvalida;
			}

			/* Abre o arquivo de regras de movimentação discreta para leitura */
			ArquivoDeRegras = fopen ( REGRASD , "r" );
			if ( ArquivoDeRegras == NULL )
			{
				return REC_CondRetArquivoNaoExiste ;
			}

			/* Busca no arquivo as regras correspondentes àquele tipo */
			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				/* Se a regra corresponder ao tipo, adicionar as peças correspondentes */
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosDiscretos ( pPeca , pGrafo , movimentos, (char)coluna, linha );					
				}
			}

			/* Fecha o arquivo de regras de movimentação discreta */
			fclose( ArquivoDeRegras );

			/* Abre o arquivo de regras de movimentação contínua para leitura */
			ArquivoDeRegras = fopen ( REGRASC , "r" );
			if ( ArquivoDeRegras == NULL )
			{
				return REC_CondRetArquivoNaoExiste ;
			}

			/* Busca no arquivo as regras correspondentes àquele tipo */
			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				/* Se a regra corresponder ao tipo, adicionar as peças correspondentes */
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosContinuos ( pPeca , pGrafo , movimentos, (char)coluna, linha );					
				}
			}

			/* Fecha o arquivo de regras de movimentação contínua */
			fclose( ArquivoDeRegras );

		}
	}

	*ppGrafo = pGrafo;
	return REC_CondRetOK;
} /* Fim da Função: REC  &Gera Movimentações */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: REC -Adiciona Próximas Peças ( Movimentação Discreta )
*
*  $ED Descrição da função
*     Adiciona no grafo as peças alcançadas pela peça atual por um movimento
*	  discreto.
*
*  $EP Parâmetros
*     pPeca - referência para a peça de origem
*	  pGrafo - grafo que contém a peça
*	  Movimento - string que determina a movimentação da peça
*	  ColunaCorrente - letra da coluna onde está a peça
*	  LinhaCorrente - número da linha onde está a peça
*
*  $FV Valor retornado
*     REC_CondRetOK - adicionou as peças sem problemas
*	  REC_CondRetErroNaStringDeMovimento - string de movimentação com sintaxe incorreta
*	  REC_CondRetPosicaoInvalida - peça referida pela string de movimento está numa posição inválida
*	  REC_CondRetNaoInseriuPeca - erro ao inserir a peça
*
***********************************************************************/
REC_tpCondRet AdicionaProximosDiscretos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente ){

	/* Declaração e Inicialização de Variáveis Locais */
	int NumCasasNaVertical		= 0;
	int NumCasasNaHorizontal	= 0;
	char TipoDaCasa				= '!';
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		= '@';
	REC_tpCondRet CondRetREC	= REC_CondRetOK ;
	GER_tpCorPeca CorDaPeca		= GER_CorSemCor ;

	/* Obtém os dados a partir da regra */
	if ( sscanf ( Movimento , "%*c %c %d %d" , 
				&TipoDaCasa , &NumCasasNaVertical , &NumCasasNaHorizontal )
				!= 3)
	{
		return REC_CondRetErroNaStringDeMovimento;
	}

	CorDaPeca = GER_ObterCor ( pPeca ) ;
	if ( CorDaPeca == GER_CorBranca )
	{
		NumCasasNaVertical = NumCasasNaVertical * (-1) ;
		NumCasasNaHorizontal = NumCasasNaHorizontal * (-1) ;
	}

	LinhaDoProximo = LinhaCorrente + NumCasasNaVertical ;
	ColunaDoProximo = ( char )( ColunaCorrente + NumCasasNaHorizontal ) ;

	CondRetREC = AdicionaProximo ( pGrafo , (char)ColunaCorrente , LinhaCorrente , (char)ColunaDoProximo , LinhaDoProximo, (char)TipoDaCasa, CorDaPeca );

	return CondRetREC;
}/* Fim da Função: REC -Adiciona Próximas Peças ( Movimentação Discreta ) */

/***********************************************************************
*
*  $FC Função: REC -Adiciona Próximas Peças ( Movimentação Contínua )
*
*  $ED Descrição da função
*     Adiciona no grafo as peças alcançadas pela peça atual por um movimento
*	  contínuo.
*
*  $EP Parâmetros
*     pPeca - referência para a peça de origem
*	  pGrafo - grafo que contém a peça
*	  Movimento - string que determina a movimentação da peça
*	  ColunaCorrente - letra da coluna onde está a peça
*	  LinhaCorrente - número da linha onde está a peça
*
*  $FV Valor retornado
*     REC_CondRetOK - adicionou as peças sem problemas
*	  REC_CondRetErroNaStringDeMovimento - string de movimentação com sintaxe incorreta
*	  REC_CondRetPosicaoInvalida - peça referida pela string de movimento está numa posição inválida
*	  REC_CondRetNaoInseriuPeca - erro ao inserir a peça
*
***********************************************************************/
REC_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento, char ColunaCorrente, int LinhaCorrente ){
	
	/* Declara e inicializa variáveis */
	char Direcao[2]				= "";
	int NumMaxDeCasas			= 0;
	int CoefHorizontal			= 0;
	int CoefVertical			= 0;
	int Fator					= 0;
	REC_tpCondRet CondRetREC	= REC_CondRetOK;
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		='@';
	char MaxCasas				= '#';
	GER_tpCorPeca CorDaPeca		= GER_CorSemCor ;

	/* Obtém os dados a partir da regra */
	if ( sscanf ( Movimento , "%*c %s %c",
				&Direcao , &MaxCasas )
				!= 2 )
	{
		return REC_CondRetErroNaStringDeMovimento;
	}

	/* Verifica as direções possíveis */
	switch ( Direcao[0] ){
		case 'N': CoefVertical = 1; break;
		case 'S': CoefVertical = -1; break;
		case 'E': CoefVertical = 0; break;
		case 'W': CoefVertical = 0; break;
		default: return REC_CondRetErroNaStringDeMovimento ;
	}

	switch ( Direcao[1] ){
		case 'N': CoefHorizontal = 0; break;
		case 'S': CoefHorizontal = 0; break;
		case 'E': CoefHorizontal = 1; break;
		case 'W': CoefHorizontal = -1; break;
		default: return REC_CondRetErroNaStringDeMovimento ;
	}

	/* Verifica o número de casas máximos */
	if ( MaxCasas == 'N' )
	{
		NumMaxDeCasas = GER_ObterUltimaLinhaTabuleiro();
	}
	else if ( ( MaxCasas > '9' )||
		      ( MaxCasas < '0' ) )
	{
		return REC_CondRetErroNaStringDeMovimento;
	}
	else
	{
		NumMaxDeCasas = ( int )( MaxCasas - '0' );
	}


	/* Ajusta coeficiente para peças brancas */
	CorDaPeca = GER_ObterCor ( pPeca );
	if ( CorDaPeca == GER_CorBranca )
	{
		CoefHorizontal = CoefHorizontal * (-1);
		CoefVertical = CoefVertical * (-1);
	}

	/* Adiciona as casas possíveis na direção dada */
	for ( Fator = 1 ; Fator <=NumMaxDeCasas ; Fator++ )
	{
		LinhaDoProximo = LinhaCorrente + Fator * CoefVertical;
		ColunaDoProximo = ( char )( ColunaCorrente + Fator * CoefHorizontal );

		CondRetREC = AdicionaProximo ( pGrafo, ColunaCorrente , LinhaCorrente, ColunaDoProximo, LinhaDoProximo, '?', CorDaPeca );
		if ( CondRetREC != REC_CondRetOK )
		{
			break;
		}
	}

	return REC_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: REC -Adiciona Próxima Peça ( Genérica )
*
*  $ED Descrição da função
*     Adiciona no grafo uma peça como próxima de uma outra
*
*  $EP Parâmetros
*	  pGrafo - grafo que contém a peça
*	  ColunaCorrente - coluna da peça de origem
*	  LinhaCorrente - linha da peça de origem
*	  ColunaProximo - coluna da peça de destino
*	  LinhaPróximo - linha da peça de destino
*	  TipoDaCasa - tipo da casa de destino ( se cheia, vazia ou não importa )
*	  CorPecaCorrente - cor da peça de origem
*
*  $FV Valor retornado
*     REC_CondRetOK - adicionou as peças sem problemas
*	  REC_CondRetErroNaStringDeMovimento - string de movimentação com sintaxe incorreta
*	  REC_CondRetPosicaoInvalida - peça referida pela string de movimento está numa posição inválida
*	  REC_CondRetNaoInseriuPeca - erro ao inserir a peça
*
***********************************************************************/
REC_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo, char ColunaCorrente, int LinhaCorrente , char ColunaProximo, int LinhaProximo, char TipoDaCasa, GER_tpCorPeca CorPecaCorrente ){

	/* Declara e inicializa variáveis locais */
	int IdCorrente				= -1;
	int IdProximo				= -1;
	GRA_tpCondRet CondRetGRA	= GRA_CondRetOK;
	GER_tpCondRet CondRetGER	= GER_CondRetOK ;
	GER_tppPeca pPeca			= NULL;
	GER_tpTipoPeca TipoDaPeca	= GER_TipoVazia;	
	GER_tpCorPeca CorDaProxPeca	= GER_CorSemCor ;

	/* Verifica se a posição das peças é válida */
	if (( LinhaCorrente < 1 )||
		( LinhaProximo < 1 )||
		( LinhaCorrente > GER_ObterUltimaLinhaTabuleiro() )||
		( LinhaProximo > GER_ObterUltimaLinhaTabuleiro() )||
		( ColunaCorrente < 'A' )||
		( ColunaProximo < 'A' )||
		( ColunaCorrente > GER_ObterUltimaColunaTabuleiro() )||
		( ColunaProximo > GER_ObterUltimaColunaTabuleiro() ) )
	{
		return REC_CondRetPosicaoInvalida;
	}

	/* Obtém o sucessor */
	CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , ColunaProximo , LinhaProximo );
	if ( CondRetGER != GER_CondRetOK )
	{
		return REC_CondRetPosicaoInvalida ;
	} 

	/* Obtém o tipo do sucessor e verifica se é válido */
	TipoDaPeca = GER_ObterTipo ( pPeca );
	if (( TipoDaPeca == GER_TipoVazia )&&
		( TipoDaCasa == 'C' ))
	{
		return REC_CondRetPosicaoInvalida;
	}
	else if (( TipoDaPeca != GER_TipoVazia)&&
			( TipoDaCasa == 'V'))
	{
		return REC_CondRetPosicaoInvalida;
	}

	/* Obtém a cor do sucessor */
	CorDaProxPeca = GER_ObterCor ( pPeca );
	if ( CorPecaCorrente == CorDaProxPeca )
	{
		return REC_CondRetPosicaoInvalida ;
	}

	/* Gera os identificadores para as peças */
	IdCorrente = CodificaPosicao ( (char)ColunaCorrente , LinhaCorrente );
	IdProximo = CodificaPosicao ( (char)ColunaProximo , LinhaProximo );

	/* Insere a aresta entre as peças */
	CondRetGRA = GRA_InserirAresta ( pGrafo , IdCorrente , IdProximo );
	if ( CondRetGRA != GRA_CondRetOK )
	{
		return REC_CondRetNaoAdicionouProx;
	}

	return REC_CondRetOK;
} /* Fim da Função: REC -Adiciona Próxima Peça ( Genérica ) */

/***********************************************************************
*
*  $FC Função: REC -Codifica Posição
*
*  $ED Descrição da função
*     A partir da posição da peça no tabuleiro, gera um identificador para a peça
*
*  $EP Parâmetros
*	  Coluna - letra da coluna da peça no tabuleiro
*	  Linha - número da linha da peça no tabuleiro
*
*  $FV Valor retornado
*     Retorna um identificador único para a peça no grafo.
*
***********************************************************************/
int CodificaPosicao ( char Coluna , int Linha ){
	
	int NumeroDaLinha = Linha -1;
	int NumeroDaColuna = ( int )( Coluna - 'A' )+1;
	int NumeroDeColunas = ( int )( GER_ObterUltimaColunaTabuleiro ( ) - 'A' + 1)  ;

	return ( ( NumeroDaLinha * NumeroDeColunas ) + NumeroDaColuna );
} /* Fim da Função: REC Codifica Posição */
