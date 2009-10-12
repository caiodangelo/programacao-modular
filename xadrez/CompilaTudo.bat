@ECHO  OFF
REM  Compila o trabalho 

pushd  .

del *.err
del Trabalho*.exe

del *.obj
nmake /Ftrabalho.make "PRD=" 

copy  *.err  tudo.err

notepad tudo.err

popd
