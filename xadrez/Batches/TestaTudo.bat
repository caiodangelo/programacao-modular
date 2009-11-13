REM executa os testes relativos aos módulos vértice, grafo, gerenciador e reconhecedor

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testevertice		/s..\scripts\testevertice	/l..\produto\testevertice	/a..\scripts\estatisticas	

REM..\produto\testegrafo		/s..\scripts\testegrafo		/l..\produto\testegrafo		/a..\scripts\estatisticas	

REM..\produto\testegerenciador	/s..\scripts\testegerenciador	/l..\produto\testegerenciador	/a..\scripts\estatisticas	

REM..\produto\testemovimentador	/s..\scripts\testemovimentador	/l..\produto\testemovimentador	/a..\scripts\estatisticas	

..\..\ferramnt\exbestat /e..\scripts\estatisticas
