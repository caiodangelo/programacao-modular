REM executa os testes relativos aos módulos vértice, grafo, gerenciador e reconhecedor

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

REM..\produto\testevertice		/s..\scripts\testevertice	/l..\produto\testevertice	/a..\scripts\estatisticas	

REM..\produto\testegrafo		/s..\scripts\testegrafo		/l..\produto\testegrafo		/a..\scripts\estatisticas	

REM..\produto\testegerenciador	/s..\scripts\testegerenciador	/l..\produto\testegerenciador	/a..\scripts\estatisticas	

..\produto\testereconhecedor	/s..\scripts\testereconhecedor	/l..\produto\testereconhecedor	/a..\scripts\estatisticas	

..\..\ferramnt\exbestat /e..\scripts\estatisticas
