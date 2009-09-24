#include "GERENCIADOR_XADREZ.H"
#include "VERTICE.H"

#define N_LINHAS 8;
#define N_COLUNAS 8;
#define TAM_DISPOSICAO 7;
#define INX_TIPO 0;
#define INX_COR 2;
#define INX_LINHA 4;
#define INX_COLUNA 6;

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
	tpPeca * matpPeca[N_LINHAS][N_COLUNAS];

	/* Preenche a matriz com ponteiros para peças */
	for ( linha = 0 ; linha < N_LINHAS ; linha++ ){
		for ( coluna = 0 ; coluna < N_COLUNAS ; coluna++){
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
	char disposicao[TAM_DISPOSICAO];
	tpCondRet CondRet;
	tpPeca * Peca;

	arquivo = fopen ( ArquivoDisposicao , "r" );
	if ( arquivo == NULL ){
		return tpCondRetArqInexistente;
	}

	while ( disposicao = fgets ( disposicao , TAM_DISPOSICAO , ArquivoDisposicao != EOF){
		if ( CondRet = ValidaLinha ( disposicao ) != GER_CondRetOK ){
			return CondRet;
		}
		Peca = ObtemPeca ( disposicao , Tabuleiro );
		if ( CondRet = AtribuiPeca( Peca, disposicao[INX_TIPO], disposicao[INX_COR], NULL ) != tpCondRetOK){
			return CondRet;
		}
	}

	fclose( arquivo );
}

tpPeca * ObtemPeca ( char * disposicao, tpTabuleiro Tabuleiro ){
	char charLinha = disposicao [INX_LINHA];
	char charColuna = disposicao[INX_COLUNA];
	int Linha;
	int Coluna;

	Linha = charLinha - '1';
	Coluna = charColuna - 'A';
	
	return Tabuleiro[Linha][Coluna];
}

tpCondRet ValidaLinha ( char * disposicao ){
	int Linha;
	int Coluna;
	char Tipo = disposicao[INX_TIPO];
	char Cor = disposicao[INX_COR];
	char charLinha = disposicao[INX_LINHA];
	char charColuna = disposicao[INX_COLUNA];

	Linha = (int) (charLinha - '1');
	Coluna = (int) (charColuna - 'A');

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

tbCondRet GER_ObtemPeca ( tpPeca * pPeca, char coluna, int linha, tpTabuleiro Tabuleiro ){
	int ixColuna = (int) (coluna - 'A');
	int ixLinha = linha - 1;

	if((ixLinha<0)||(ixLinha>N_LINHAS)){
		return GER_CondRetPecaInexistente;
	}
	else if((ixColuna<0)||(ixColuna>N_COLUNAS)){
		return GER_CondRetPecaInexistente;
	}

	pPeca = Tabuleiro[ixLinha][ixColuna];
	return tpCondRetOK;
}

int GER_ObtemUltimaLinhaTabuleiro ( void ){
	return N_LINHAS;
}

char GER_ObtemUltimaColunaTabuleiro ( void ){
	return (char)('A' + N_COLUNAS - 1);
}
