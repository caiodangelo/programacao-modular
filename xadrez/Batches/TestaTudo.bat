REM executa os testes relativos aos m�dulos lista, v�rtice, grafo, gerenciador e reconhecedor

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat


..\produto\testelista		/s..\scripts\testelista		/l..\produto\testelista	/a..\scripts\estatisticas

..\produto\testelista	/s..\scripts\testelistadeturpada	/l..\produto\testelistadeturpada	/a..\scripts\estatisticas

..\produto\testelista		/s..\scripts\testelistadeturpada1	/l..\produto\testelistadeturpada1	/a..\scripts\estatisticas

..\produto\testelista	/s..\scripts\testelistadeturpada2	/l..\produto\testelistadeturpada2	/a..\scripts\estatisticas

..\produto\testelista	/s..\scripts\testelistadeturpada3	/l..\produto\testelistadeturpada3	/a..\scripts\estatisticas

REM..\produto\testevertice		/s..\scripts\testevertice	/l..\produto\testevertice	/a..\scripts\estatisticas	

REM..\produto\testegrafo		/s..\scripts\testegrafo		/l..\produto\testegrafo		/a..\scripts\estatisticas	

REM..\produto\testegerenciador	/s..\scripts\testegerenciador	/l..\produto\testegerenciador	/a..\scripts\estatisticas	

REM..\produto\testemovimentador	/s..\scripts\testemovimentador	/l..\produto\testemovimentador	/a..\scripts\estatisticas

REM..\produto\testepartida	/s..\scripts\testepartida	/l..\produto\testepartida	/a..\scripts\estatisticas	

..\..\ferramnt\exbestat /e..\scripts\estatisticas
