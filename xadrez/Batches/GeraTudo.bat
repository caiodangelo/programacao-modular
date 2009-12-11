@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\..\ferramnt

REM gmake  /b..\xadrez\composicao  /cCompVer.comp
REM gmake  /b..\xadrez\composicao  /cCompGra.comp
REM gmake  /b..\xadrez\composicao  /cCompGer.comp
REM gmake  /b..\xadrez\composicao  /cCompMov.comp
REM gmake  /b..\xadrez\composicao  /cCompPar.comp
gmake  /b..\xadrez\composicao  /cCompLis.comp

popd
