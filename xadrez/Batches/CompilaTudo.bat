@ECHO  OFF
REM  Compila o trabalho 

pushd  .

del ..\produto\*.err
del ..\objetos\*.obj

nmake /F..\composicao\TesteVertice.make "PRD=" 

nmake /F..\composicao\TesteGrafo.make "PRD="

nmake /F..\composicao\TesteGerenciador.make "PRD="

nmake /F..\composicao\TesteReconhecedor.make "PRD="

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

popd
