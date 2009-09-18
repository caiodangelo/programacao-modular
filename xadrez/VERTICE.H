typedef enum {
} VER_tpCondRet;

VER_tpCondRet VER_ObterValor ( tpVertice * Vertice, void * Valor );

VER_tpCondRet VER_CriarVertice ( tpVertice * Vertice, void * Valor );

VER_tpCondRet VER_DestruirVertice ( tpVertice * Vertice );

VER_tpCondRet VER_AlterarValor ( tpVertice * Vertice, void * ValorNovo );