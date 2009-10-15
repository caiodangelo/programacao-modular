#include "GERENCIADOR.H"
#include "VERTICE.H"
#include <stdlib.h>
#include <stdio.h>

#define N_LINHAS 8
#define N_COLUNAS 8
#define TAM_DISPOSICAO 10
#define INX_TIPO 0
#define INX_COR 2
#define INX_LINHA 6
#define INX_COLUNA 4
#define N_TIPOS 7
#define N_CORES 3

typedef struct tgPeca{

	GER_tpTipoPeca Tipo;
		/* tipo da peca */

	GER_tpCorPeca Cor;
		/* cor da peca */

	char* MovimentosPossiveis;
		/* string que determina os movimentos possíveis da peça */

}tpPeca;

typedef struct tgPeca * tppPeca;
tppPeca Tabuleiro[N_LINHAS][N_COLUNAS];

tpPeca * ObtemPeca ( char * disposicao );
GER_tpCondRet ValidaLinha ( char * disposicao );
GER_tpTipoPeca ObtemCodigoDoTipo ( char Tipo );
GER_tpCorPeca ObtemCodigoDaCor ( char Cor );

tpPeca * GER_CriarPeca ( GER_tpTipoPeca tipo , GER_tpCorPeca cor , char* movimentosPossiveis ){
	tpPeca * pPeca = ( tpPeca * ) malloc ( sizeof ( tpPeca ) );
	if ( pPeca == NULL ){
		return NULL;
	}
	
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;
	pPeca->MovimentosPossiveis = movimentosPossiveis;

	return pPeca;
}

GER_tpCondRet GER_AtribuirPeca ( tpPeca * pPeca , GER_tpTipoPeca tipo , GER_tpCorPeca cor , char* movimentosPossiveis ){
	
	if ( pPeca == NULL ){
		return GER_CondRetPecaNaoExiste;
	}

	if( ( tipo < 0 ) ||
		( tipo >= N_TIPOS ) )
	{
		return GER_CondRetTipoInvalido;
	}

	if( ( cor < 0 ) ||
		( cor >= N_CORES ) )
	{
		return GER_CondRetCorInvalida;
	}
	
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;
	pPeca->MovimentosPossiveis = movimentosPossiveis;

	return GER_CondRetOK;
}


GER_tpCondRet GER_InicializarTabuleiro ( void ){
	int linha;
	int coluna;

	/* Preenche o tabuleiro com ponteiros para peças */
	for ( linha = 0 ; linha < N_LINHAS ; linha++ ){
		for ( coluna = 0 ; coluna < N_COLUNAS ; coluna++){
			Tabuleiro[linha][coluna] = GER_CriarPeca( GER_tpTipoVazia , GER_tpCorSemCor , NULL );
			if ( Tabuleiro[linha][coluna] == NULL ){
				return GER_CondRetFaltouMemoria;
			}
		}
	}

	return GER_CondRetOK;
}
	
GER_tpCondRet GER_PreencherTabuleiro ( char * ArquivoDisposicao ){
	FILE * arquivo;
	char disposicao[TAM_DISPOSICAO];
	GER_tpCondRet CondRet;
	tpPeca * pPeca;
	int Tipo;
	int Cor;

	arquivo = fopen ( ArquivoDisposicao , "r" );
	if ( arquivo == NULL ){
		return GER_CondRetArqInexistente;
	}

	while ( fgets ( disposicao , TAM_DISPOSICAO , arquivo )){
		CondRet = ValidaLinha ( disposicao );
		if ( CondRet != GER_CondRetOK ){
			return CondRet;
		}
		pPeca = ObtemPeca ( disposicao );
		Tipo = ObtemCodigoDoTipo ( disposicao[INX_TIPO] );
		Cor = ObtemCodigoDaCor ( disposicao[INX_COR] );
		CondRet = GER_AtribuirPeca( pPeca, Tipo, Cor, NULL );

		if ( CondRet != GER_CondRetOK){
			return CondRet;
		}
	}

	fclose( arquivo );

	return GER_CondRetOK ;
}

tpPeca * ObtemPeca ( char * disposicao ){
	char charLinha = disposicao [INX_LINHA];
	char charColuna = disposicao[INX_COLUNA];
	int Linha;
	int Coluna;

	Linha = charLinha - '1';
	Coluna = charColuna - 'A';
	
	return Tabuleiro[Linha][Coluna];
}

GER_tpCondRet ValidaLinha ( char * disposicao ){
	int Linha;
	int Coluna;
	char Tipo = disposicao[INX_TIPO];
	char Cor = disposicao[INX_COR];
	char charLinha = disposicao[INX_LINHA];
	char charColuna = disposicao[INX_COLUNA];

	Linha = (int) (charLinha - '1');
	Coluna = (int) (charColuna - 'A');

	if((Linha<0)||(Linha>7)){

		return GER_CondRetArqDispInvalido;
	}
	else if((Coluna<0)||(Coluna>7)){

		return GER_CondRetArqDispInvalido;
	}

	if(
		( Tipo != 'P' )&&
		( Tipo != 'T' )&&
		( Tipo != 'C' )&&
		( Tipo != 'B' )&&
		( Tipo != 'D' )&&
		( Tipo != 'R' )
		){

			return GER_CondRetArqDispInvalido;
	}

	if(
		( Cor != 'B' )&&
		( Cor != 'P' )
		){

			return GER_CondRetArqDispInvalido;
	}
	
	return GER_CondRetOK;
}

GER_tpCondRet GER_ObterPecaDoTabuleiro ( tppPeca * ppPeca, char coluna, int linha ){
	int ixColuna = (int) (coluna - 'A');
	int ixLinha = linha - 1;

	if((ixLinha<0)||(ixLinha>=N_LINHAS)){
		return GER_CondRetPecaNaoExiste;
	}
	else if((ixColuna<0)||(ixColuna>=N_COLUNAS)){
		return GER_CondRetPecaNaoExiste;
	}

	*ppPeca = Tabuleiro[ixLinha][ixColuna];
	printf("%tipo: %d, cor: %d\n",(*ppPeca)->Tipo,(*ppPeca)->Cor);
	return GER_CondRetOK;
}

int GER_ObterUltimaLinhaTabuleiro ( void ){
	return N_LINHAS;
}

char GER_ObterUltimaColunaTabuleiro ( void ){
	return (char)('A' + N_COLUNAS - 1);
}

GER_tpTipoPeca GER_ObterTipo ( tppPeca pPeca ) {
	return pPeca->Tipo ;
}

GER_tpCorPeca GER_ObterCor ( tppPeca pPeca ) {
	return pPeca->Cor ;
}

GER_tpTipoPeca ObtemCodigoDoTipo ( char Tipo ){
	switch ( Tipo ){
		case 'P': return GER_tpTipoPeao;
		case 'T': return GER_tpTipoTorre;
		case 'C': return GER_tpTipoCavalo;
		case 'B': return GER_tpTipoBispo;
		case 'D': return GER_tpTipoDama;
		case 'R': return GER_tpTipoRei;
		default:  return GER_tpTipoVazia;
	}
}

GER_tpCorPeca ObtemCodigoDaCor ( char Cor ){
	switch ( Cor ){
		case 'B': return GER_tpCorBranca;
		case 'P': return GER_tpCorPreta;
		default:  return GER_tpCorSemCor;
	}
}