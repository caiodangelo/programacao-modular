REM executa os testes relativos aos m�dulos v�rtice, grafo, gerenciador e reconhecedor

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testevertice		/s..\scripts\testevertice	/l..\produto\testevertice	/a..\scripts\estatisticas	

..\produto\testegrafo		/s..\scripts\testegrafo		/l..\produto\testegrafo		/a..\scripts\estatisticas	

..\produto\testegerenciador	/s..\scripts\testegerenciador	/l..\produto\testegerenciador	/a..\scripts\estatisticas	

..\produto\testemovimentador	/s..\scripts\testemovimentador	/l..\produto\testemovimentador	/a..\scripts\estatisticas	

..\..\ferramnt\exbestat /e..\scripts\estatisticas
