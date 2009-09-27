#include "GERENCIADOR_XADREZ.H"
#include "GRAFO.H"
#include "VERTICE.H"

char * ArquivoRegras = NULL;
/* Esas função exportada vai pegar o tabuleiro e chamar as
		funções auxiliares */
tpPeca * REC_ReconheceXeque ( tpTabuleiro Tabuleiro, tpCorPeca Cor ){
}

/* Essa função encapsulada vai ler a disposição das peças no tabuleiro e
		gerar o grafo com as possibilidades da próxima jogada */
REC_tpCondRet GeraPossiblidades ( tpTabuleiro Tabuleiro ){
	tpGrafo * pGrafo;
	tpVertice * pVertice;
	tpPeca * pPeca;
	int linha; /* verificar padrão para essas variaveis */
	char coluna;
	int ultLinha = GER_ObtemNLinhasTabuleiro ();
	int ultColuna = GER_ObtemNLinhasTabuleiro ();
	GRA_tpCondRet CondRetGRA;
	VER_tpCondRet CondRetVER;
	GER_tpCondRet CondRetGER;

	CondRetGRA = GRA_CriarGrafo ( &pGrafo );
	if ( CondRetGRA != GRA_tpCondRetOK ){
		return REC_tpCondRetNaoCriouGrafo;
	}

	

	for ( linha = 0 ; linha <= ultLinha ; linha++ ){
		for ( coluna = 'A' ; coluna <= ultColuna ; (char)(coluna++) ){
			
			CondRetGER = GER_ObtemPeca ( pPeca , coluna , linha , Tabuleiro );
			if ( CondRegGER != GER_tpCondRetOK ){
				return REC_tpCondRetNaoCriouVertice;
			}

			CondRetVER = VER_CriarVertice ( &pVertice , pPeca );
			if ( CondRetVER != VER_tpCondRetOK ){
				return REC_tpCondRetNaoCriouVertice;
			}

			CondRetGRA = GRA_InserirVertice ( pGrafo , pVertice );
			if ( CondRetGRA != GRA_CondRetOK ){
				return REC_tpCondRetNaoInseriuPeca;
			}

			
		}
	}
}

REC_tpCondRet AdicionaPosicoesSeguintes ( tpPeca * pPeca , tpTabuleiro Tabuleiro ){
}

REC_tpCondRet REC_DeterminaRegras ( char * ArquivoRegras ){

	