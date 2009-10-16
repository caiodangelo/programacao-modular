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

/***** Protótipos das funções encapuladas no módulo *****/

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
	GRA_tppGrafo pGrafo = *ppGrafo;
	int linha;
	int coluna;
	GER_tpCondRet CondRetGer;
	GER_tppPeca pPeca;
	char movimentos[TAM_MOVIMENTO];
	GER_tpTipoPeca TipoPeca;

	/* Cria o grafo e adiciona as peças a ele */
	REC_AdicionarPecasAoGrafo ( &pGrafo ) ;
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



/***************************************************************************
*
*  Função: REC  &Adiciona Próximos Discretos
*  ****/
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
}/* Fim da Função: REC  &Adiciona Próximos Discretos */

REC_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento, char ColunaCorrente, int LinhaCorrente ){
	
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

	if ( sscanf ( Movimento , "%*c %s %c",
				&Direcao , &MaxCasas )
				!= 2 )
	{
		return REC_CondRetErroNaStringDeMovimento;
	}

	switch ( Direcao[0] ){
		case 'N': CoefVertical = 1; break;
		case 'S': CoefVertical = -1; break;
		case 'E': CoefVertical = 0; break;
		case 'W': CoefVertical = 0; break;
	}

	switch ( Direcao[1] ){
		case 'N': CoefHorizontal = 0; break;
		case 'S': CoefHorizontal = 0; break;
		case 'E': CoefHorizontal = 1; break;
		case 'W': CoefHorizontal = -1; break;
	}

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


	CorDaPeca = GER_ObterCor ( pPeca );
	if ( CorDaPeca == GER_CorBranca )
	{
		CoefHorizontal = CoefHorizontal * (-1);
		CoefVertical = CoefVertical * (-1);
	}

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

REC_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo, char ColunaCorrente, int LinhaCorrente , char ColunaProximo, int LinhaProximo, char TipoDaCasa, GER_tpCorPeca CorPecaCorrente ){

	int IdCorrente				= -1;
	int IdProximo				= -1;
	GRA_tpCondRet CondRetGRA	= GRA_CondRetOK;
	GER_tpCondRet CondRetGER	= GER_CondRetOK ;
	GER_tppPeca pPeca			= NULL;
	GER_tpTipoPeca TipoDaPeca	= GER_TipoVazia;	
	GER_tpCorPeca CorDaProxPeca	= GER_CorSemCor ;

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

	CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , ColunaProximo , LinhaProximo );
	if ( CondRetGER != GER_CondRetOK )
	{
		return REC_CondRetPosicaoInvalida ;
	} 

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

	CorDaProxPeca = GER_ObterCor ( pPeca );
	if ( CorPecaCorrente == CorDaProxPeca )
	{
		return REC_CondRetPosicaoInvalida ;
	}

	IdCorrente = CodificaPosicao ( (char)ColunaCorrente , LinhaCorrente );
	IdProximo = CodificaPosicao ( (char)ColunaProximo , LinhaProximo );

	CondRetGRA = GRA_InserirAresta ( pGrafo , IdCorrente , IdProximo );
	if ( CondRetGRA != GRA_CondRetOK )
	{
		return REC_CondRetNaoAdicionouProx;
	}

	return REC_CondRetOK;
}

REC_tpCondRet REC_ReconheceXequeMate ( GRA_tppGrafo pGrafo , GER_tpCorPeca CorPeca , int * pIdProx ){

	int LinhaRei					= -1;
	char ColunaRei					= '!' ;
	int IdRei						= -1 ;
	GER_tpCondRet CondRetGER		= GER_CondRetOK ;
	GRA_tpCondRet CondRetGRA		= GRA_CondRetOK ;
	int IdSucessor					= -1 ;
	int IdAntecessor				= -1 ;
	int IdPrimeiroSucessor			= -1 ;
	int IdPrimeiroAntecessor		= -1 ;

	CondRetGER = GER_ObterRei ( CorPeca , &ColunaRei , &LinhaRei  ) ;

	if ( CondRetGER != GER_CondRetOK )
	{
		return REC_CondRetReiNaoExiste ;
	}

	IdRei = CodificaPosicao ( ColunaRei , LinhaRei );
	CondRetGRA = GRA_IrVerticeComId ( pGrafo , IdRei ) ;
	if ( CondRetGRA != GRA_CondRetOK )
	{
		return REC_CondRetReiNaoExiste ;
	}

	CondRetGRA = GRA_ObterSucessor ( pGrafo , IdRei , &IdPrimeiroSucessor );
	if ( CondRetGRA != GRA_CondRetOK )
	{
		pIdProx = NULL ;
		return REC_CondRetXequeMate ;
	}

	do
	{
		CondRetGRA = GRA_ObterSucessor ( pGrafo , IdRei , &IdSucessor );
		if ( CondRetGRA != GRA_CondRetOK )
		{
			pIdProx = NULL ;
			return REC_CondRetXequeMate ;
		}

		CondRetGRA = GRA_ObterAntecessor ( pGrafo , IdSucessor , &IdPrimeiroAntecessor );
		if ( CondRetGRA != GRA_CondRetOK )
		{
				* pIdProx = -1 ;
				return REC_CondRetNaoEstaEmXequeMate ;
		}

		do
		{
			CondRetGRA = GRA_ObterAntecessor ( pGrafo , IdSucessor , &IdAntecessor ) ;
			if ( CondRetGRA != GRA_CondRetOK )
			{
				* pIdProx = -1 ;
				return REC_CondRetNaoEstaEmXequeMate ;
			}

		}
		while ( IdAntecessor != IdPrimeiroAntecessor ) ;
	}
	while ( IdSucessor != IdPrimeiroSucessor ) ;
	
	*pIdProx = -1 ;
	return REC_CondRetXequeMate ;
}

int CodificaPosicao ( char Coluna , int Linha ){
	
	int NumeroDaLinha = Linha -1;
	int NumeroDaColuna = ( int )( Coluna - 'A' )+1;
	int NumeroDeColunas = ( int )( GER_ObterUltimaColunaTabuleiro ( ) - 'A' + 1)  ;

	return ( ( NumeroDaLinha * NumeroDeColunas ) + NumeroDaColuna );
}
