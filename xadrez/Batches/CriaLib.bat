ECHO Cria a biblioteca a ser utilizada no trbalho do reconhecedor de xadrez
ECHO assume o arcabouco todo construído e correto

pushd  .

cd  ..\..\arcabouc\objetos
del    *.obj
del    *.lib
nmake /F..\..\arcabouc\composicao\crialib.make  "PRD="
copy   arcaboucoteste.lib ..\..\xadrez\objetos

popd
