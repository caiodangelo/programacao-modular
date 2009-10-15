#include "GERENCIADOR.H"
#include "RECONHECEDOR.H"
#include "GRAFO.H"
#include <stdio.h>
#include <stdlib.h>



int CodificaPosicao ( char Coluna , int Linha );

tpPeca * REC_ReconheceXeque ( void ){
	return NULL;
}

REC_tpCondRet REC_GeraMovimentacoes ( void ){
	
	GRA_tppGrafo pGrafo;
	tpPeca * pPeca;
	int linha; 
	char coluna;
	int id;

	GRA_tpCondRet CondRetGRA;
	GER_tpCondRet CondRetGER;

	CondRetGRA = GRA_CriarGrafo ( &pGrafo );
	if ( CondRetGRA != GRA_CondRetOK ){
		return REC_CondRetNaoCriouGrafo;
	}

	/* Percorre todas as posições do tabuleiro adicionando as peças ao grafo */

	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){
			
			CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , coluna , linha );
			if ( CondRetGER != GER_CondRetOK ){
				return REC_CondRetNaoCriouVertice;
			}

			id = CodificaPosicao ( coluna , linha );

			CondRetGRA = GRA_InserirVertice ( pGrafo , pPeca , id );
			if ( CondRetGRA != GRA_CondRetOK ){
				return REC_CondRetNaoInseriuPeca;
			}


		}
	}

	/* Percorre todos os vértices checando o arquivo de regras para descobrir quais as posições alcançáveis */

}
REC_tpCondRet REC_DeterminaRegras ( char * ArquivoRegras ){return 0;}

int CodificaPosicao ( char Coluna , int Linha ){
	int NumeroDaLinha = Linha -1;
	int NumeroDaColuna = ( int )( Coluna - 'A' );
	int NumeroDeColunas = ( int )( GER_ObterUltimaColunaTabuleiro ( ) - 'A' ) ;
	
	return ( ( NumeroDaLinha * NumeroDeColunas ) + NumeroDaColuna );
}