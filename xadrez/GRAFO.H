typedef enum {
} GRA_tpCondRet;

GRA_tpCondRet GRA_CriarGrafo ( tpGrafo ** pGrafo );

GRA_tpCondRet GRA_InserirVertice ( tpGrafo * Grafo, tpVertice * Vertice );

GRA_tpCondRet GRA_ExcluirVertice ( tpGrafo * Grafo );

GRA_tpCondRet GRA_InserirAresta ( tpGrafo * Grafo, tpVertice * VerticeOrigem, tpVertice * VerticeDestino );

GRA_tpCondRet GRA_RemoverAresta ( tpGrafo * Grafo, tpVertice * VerticeOrigem, tpVertice * VerticeDestino );

GRA_tpCondRet GRA_ExibirGrafo ( tpGrafo * Grafo );

GRA_tpCondRet GRA_DestruirGrafo ( tpGrafo * pGrafo );
