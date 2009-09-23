#include "GERENCIADOR_XADREZ.H"
#include "VERTICE.H"

#define NLINHAS 8;
#define NCOLUNAS 8;
#define TAMDISPOSICAO 7;
#define INXTIPO 0;
#define INXCOR 2;
#define INXLINHA 4;
#define INXCOLUNA 6;

typedef struct tgPeca{

	GER_tpTipoPeca Tipo;
		/* tipo da peca */

	GER_tpCorPeca Cor;
		/* cor da peca */

	char* MovimentosPossiveis;
		/* string que determina os movimentos possíveis da peça */

}tpPeca;

typedef tpPeca *** tpTabuleiro;

tpPeca * GER_CriaPeca ( GER_tpTipoPeca tipo , GER_tpCorPeca cor , char* movimentosPossiveis ){
	tpPeca pPeca = ( tpPeca * ) malloc ( sizeof ( tpPeca ) );
	if ( Peca == NULL ){
		return NULL;
	}
	
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;
	pPeca->MovimentosPossiveis = movimentosPossiveis;

	return pPeca;
}

tpCondRet GER_AtribuiPeca ( tpPeca * Peca , GER_tpTipoPeca tipo , GER_tpCorPeca cor , char* movimentosPossiveis ){
	if ( Peca == NULL ){
		return tpCondRetPecaNaoExiste;
	}
	
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;
	pPeca->MovimentosPossiveis = movimentosPossiveis;

	return tpCondRetOK;
}


tpTabuleiro GER_CriaTabuleiro ( void ){
	int linha;
	int coluna;
	/* Cria a matriz do tabuleiro */
	tpPeca * matpPeca[NLINHAS][NCOLUNAS];

	/* Preenche a matriz com ponteiros para peças */
	for ( linha = 0 ; linha < NLINHAS ; linha++ ){
		for ( coluna = 0 ; coluna < NCOLUNAS ; coluna++){
			matpPeca[linha][coluna] = GER_CriaPeca( tpTipoVazia , tpCorSemCor , NULL );
			if ( matpVertice[linha][coluna] == NULL ){
				return NULL;
			}
		}
	}

	return matpPeca;
}
	
GER_tpCondRet GER_PreencheTabuleiro ( char * ArquivoDisposicao , tpTabuleiro Tabuleiro ){
	FILE * arquivo;
	char disposicao[TAMDISPOSICAO];
	tpCondRet CondRet;
	tpPeca * Peca;

	arquivo = fopen ( ArquivoDisposicao , "r" );
	if ( arquivo == NULL ){
		return tpCondRetArqInexistente;
	}

	while ( disposicao = fgets ( disposicao , TAMDISPOSICAO , ArquivoDisposicao != EOF){
		if ( CondRet = ValidaLinha ( disposicao ) != GER_CondRetOK ){
			return CondRet;
		}
		Peca = ObtemPeca ( disposicao , Tabuleiro );
		if ( CondRet = AtribuiPeca( Peca, disposicao[INXTIPO], disposicao[INXCOR], NULL ) != tpCondRetOK){
			return CondRet;
		}
	}

	fclose( arquivo );
}

tpPeca * ObtemPeca ( char * disposicao, tpTabuleiro Tabuleiro ){
	char charLinha = disposicao [INXLINHA];
	char charColuna = disposicao[INXCOLUNA];
	int Linha;
	int Coluna;

	Linha = charLinha - '1';
	Coluna = charColuna - 'A';
	
	return Tabuleiro[Linha][Coluna];
}

tpCondRet ValidaLinha ( char * disposicao ){
	int Linha;
	int Coluna;
	char Tipo = disposicao[INXTIPO];
	char Cor = disposicao[INXCOR];
	char charLinha = disposicao[INXLINHA];
	char charColuna = disposicao[INXCOLUNA];

	Linha = charLinha - '1';
	Coluna = charColuna - 'A';

	if((Linha<0)||(Linha>8)){
		return GER_CondRetArqDispInvalido;
	}
	else if((Coluna<0)||(Coluna>8)){
		return GER_CondRetArqDispInvalido;
	}

	if(
		( Tipo != 'P' )||
		( Tipo != 'T' )||
		( Tipo != 'C' )||
		( Tipo != 'B' )||
		( Tipo != 'D' )||
		( Tipo != 'R' )
		){
			return GER_CondRetArqDispInvalido;
	}

	if(
		( Cor != 'B' )||
		( Cor != 'P' )
		){
			return GER_CondRetArqDispInvalido;
	}
	
	return GER_CondRetOK;
}

