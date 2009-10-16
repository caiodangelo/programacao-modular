#include "GERENCIADOR.H"
#include "RECONHECEDOR.H"
#include "GRAFO.H"
#include <stdio.h>
#include <stdlib.h>

#define TAM_MOVIMENTO 10
#define REGRAS "REGRAS.TXT"
#define INX_TIPO 0

int CodificaPosicao ( char Coluna , int Linha );
REC_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo,  char ColunaCorrente, int LinhaCorrente ,  char ColunaProximo, int LinhaProximo,char TipoDaCasa );
REC_tpCondRet AdicionaProximosDiscretos ( tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente );
REC_tpCondRet AdicionaProximosContinuos ( tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimentos, char Coluna, int Linha );

tpPeca * REC_ReconheceXeque ( void ){
	return NULL;
}

REC_tpCondRet REC_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo ){
	int linha;
	int coluna;
	GER_tpCondRet CondRetGER;
	GRA_tpCondRet CondRetGRA;
	tppPeca pPeca;
	int id;
	

	CondRetGRA = GRA_CriarGrafo ( ppGrafo );
	if ( CondRetGRA != GRA_CondRetOK ){
		return REC_CondRetNaoCriouGrafo;
	}

	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){
			
			CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if ( CondRetGER != GER_CondRetOK ){
				return REC_CondRetNaoCriouVertice;
			}

			id = CodificaPosicao ( (char)coluna , linha );

			CondRetGRA = GRA_InserirVertice ( *ppGrafo , pPeca , id );
			if ( CondRetGRA != GRA_CondRetOK ){
				return REC_CondRetNaoInseriuPeca;
			}
		}
	}

	return REC_CondRetOK ;
}


REC_tpCondRet REC_GeraMovimentacoes ( void ){
	FILE * ArquivoDeRegras;
	GRA_tppGrafo pGrafo;
	int linha;
	int coluna;
	GER_tpCondRet CondRetGer;
	tppPeca pPeca;
	char movimentos[TAM_MOVIMENTO];
	GER_tpTipoPeca TipoPeca;

	ArquivoDeRegras = fopen ( REGRAS , "r" );
	if ( ArquivoDeRegras == NULL )
	{
		return REC_CondRetArquivoNaoExiste ;
	}

	REC_AdicionarPecasAoGrafo ( &pGrafo ) ;
	if ( pGrafo == NULL )
	{
		//checa qualquer coisa
	}

	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){
			
			CondRetGer = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if (CondRetGer != GER_CondRetOK )
			{
				// faz alguma coisa
			}

			TipoPeca = GER_ObterTipo ( pPeca );

			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosDiscretos ( pPeca , pGrafo , movimentos, (char)coluna, linha );
				}
			}

		}
	}

	return 0;
}
REC_tpCondRet REC_DeterminaRegras ( char * ArquivoRegras ){return 0;}

int CodificaPosicao ( char Coluna , int Linha ){
	int NumeroDaLinha = Linha -1;
	int NumeroDaColuna = ( int )( Coluna - 'A' );
	int NumeroDeColunas = ( int )( GER_ObterUltimaColunaTabuleiro ( ) - 'A' ) ;
	
	return ( ( NumeroDaLinha * NumeroDeColunas ) + NumeroDaColuna );
}

REC_tpCondRet AdicionaProximosDiscretos ( tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente ){

	int NumCasasNaVertical		= 0;
	int NumCasasNaHorizontal	= 0;
	char TipoDaCasa				= '!';
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		= '@';
	REC_tpCondRet CondRetREC	= REC_CondRetOK ;	

	if ( sscanf ( Movimento , "%*c %c %d %d" , 
				&TipoDaCasa , NumCasasNaVertical , &NumCasasNaHorizontal )
				!= 3)
	{
		return REC_CondRetErroNaStringDeMovimento;
	}

	if ( GER_ObterCor ( pPeca ) == GER_tpCorBranca )
	{
		NumCasasNaVertical = NumCasasNaVertical * (-1) ;
		NumCasasNaHorizontal = NumCasasNaHorizontal * (-1) ;
	}

	LinhaDoProximo = LinhaCorrente + NumCasasNaVertical ;
	ColunaDoProximo = ( char )( ColunaCorrente + NumCasasNaHorizontal ) ;

	CondRetREC = AdicionaProximo ( pGrafo , (char)ColunaCorrente , LinhaCorrente , (char)ColunaDoProximo , LinhaDoProximo, (char)TipoDaCasa );
	
	return CondRetREC;
}

REC_tpCondRet AdicionaProximosContinuos ( tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento, char ColunaCorrente, int LinhaCorrente ){
	
	char Direcao[2]				= "";
	int NumMaxDeCasas			= -1;
	int CoefHorizontal			= 0;
	int CoefVertical			= 0;
	int Fator					= 0;
	REC_tpCondRet CondRetREC	= REC_CondRetOK;
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		='@';

	if ( sscanf ( Movimento , "%*c %s %d" ,
				&Direcao , &NumMaxDeCasas )
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

	if ( GER_ObterCor ( pPeca ) == GER_tpCorBranca )
	{
		CoefHorizontal = CoefHorizontal * (-1);
		CoefVertical = CoefVertical * (-1);
	}

	for ( Fator = 0 ; Fator <=NumMaxDeCasas ; Fator++ )
	{
		LinhaDoProximo = LinhaCorrente + Fator * CoefVertical;
		ColunaDoProximo = ( char )( ColunaCorrente + Fator * CoefHorizontal );

		CondRetREC = AdicionaProximo ( pGrafo, ColunaCorrente , LinhaCorrente, ColunaDoProximo, LinhaDoProximo, TipoDaCasa );
		if ( CondRetREC != REC_CondRetOK )
		{
			break;
		}
	}

	return REC_CondRetOK;
}

REC_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo, char ColunaCorrente, int LinhaCorrente , char ColunaProximo, int LinhaProximo, char TipoDaCasa ){

	int IdCorrente				= -1;
	int IdProximo				= -1;
	GRA_tpCondRet CondRetGRA	= GRA_CondRetOK;
	GER_tpCondRet CondRetGER	= GER_CondRetOK ;
	tppPeca pPeca				= NULL;
	GER_tpTipoPeca TipoDaPeca	= GER_tpTipoVazia;	

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
	if (( TipoDaPeca == GER_tpTipoVazia )&&
		( TipoDaCasa == 'C' ))
	{
		return REC_CondRetPosicaoInvalida;
	}
	else if (( TipoDaPeca != GER_tpTipoVazia)&&
			( TipoDaCasa == 'V'))
	{
		return REC_CondRetPosicaoInvalida;
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



