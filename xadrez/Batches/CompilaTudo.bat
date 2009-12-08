@ECHO  OFF
REM  Compila o trabalho 

pushd  .

del ..\produto\*.err
del ..\objetos\*.obj


nmake /F..\composicao\TesteLista.make "PRD="

REM nmake /F..\composicao\TesteVertice.make "PRD=" 

REM nmake /F..\composicao\TesteGrafo.make "PRD="

REM nmake /F..\composicao\TesteGerenciador.make "PRD="

REM nmake /F..\composicao\TesteMovimentador.make "PRD="

REM nmake /F..\composicao\TestePartida.make "PRD="


copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

popd
