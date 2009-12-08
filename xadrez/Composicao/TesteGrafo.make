##################################################
###
### Diretivas de MAKE para o construto: TesteGrafo
### Gerado a partir de: CompGra.comp
###
### ----- Arquivo gerado, N�O EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteGrafo


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pespstr              = ..\Fontes
Plista               = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diret�rios para gera��o

Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fespstr              = ..\Fontes
Flista               = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de gera��o

all : limpa \
   $(Fobj)\vertice.obj   $(Fobj)\grafo.obj   $(Fobj)\lista.obj \
   $(Fobj)\testgra.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Depend�ncias de m�dulos objeto a compilar

$(Fobj)\vertice.obj :  {$(Pc)}\vertice.c \
    {$(Ph)}lista.h              {$(Ph)}vertice.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\grafo.obj :  {$(Pc)}\grafo.c \
    {$(Ph)}grafo.h              {$(Ph)}lista.h              {$(Ph)}vertice.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    ..\\tabelas\\idtiposespaco.def {$(Ph)}cespdin.h            {$(Ph)}conta.h              \
    {$(Ph)}generico.h           {$(Ph)}lista.h              {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\testgra.obj :  {$(Pc)}\testgra.c \
    {$(Ph)}generico.h           {$(Ph)}grafo.h              {$(Ph)}lerparm.h            \
    {$(Ph)}tst_espc.h           {$(Ph)}vertice.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Termina��o

Construto : \
   $(Fobj)\vertice.obj   $(Fobj)\grafo.obj   $(Fobj)\lista.obj \
   $(Fobj)\testgra.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteGrafo
###
##################################################

