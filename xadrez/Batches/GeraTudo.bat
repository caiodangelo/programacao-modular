@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\..\ferramnt

gmake  /b..\xadrez\composicao  /cCompVer.comp
gmake  /b..\xadrez\composicao  /cCompGra.comp
gmake  /b..\xadrez\composicao  /cCompGer.comp
gmake  /b..\xadrez\composicao  /cCompRec.comp

popd
