REM   Limpa tudo que sera' regerado


if exist TestaTudo.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

pushd .

cd ..\Batches

cd ..\Composicao
del *.list
del *.make

cd ..\Fontes
del *.err

cd ..\Objetos
del *.obj
del *.lib
del *.build

cd ..\Produto
del *.log
del *.exe
del *.err

cd ..\Scripts
del *.estat


popd

:sai
