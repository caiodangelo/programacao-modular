##################################################
###
### Diretivas de MAKE para o construto: Trabalho
### Gerado a partir de: Trabalho.comp
###
### ----- Arquivo gerado, N�O EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = Trabalho


### Nomes de paths

Pobj                 = .
Perr                 = .
PDEFAULT             = .
Pespstr              = .
Plista               = .
Pc                   = .

### Nomes de diret�rios para gera��o

Fobj                 = .
Ferr                 = .
FDEFAULT             = .
Fespstr              = .
Flista               = .
Fc                   = .

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
   $(Fobj)\Lista.obj   $(Fobj)\Vertice.obj   $(Fobj)\TestGra.obj \
   $(Fobj)\Grafo.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Depend�ncias de m�dulos objeto a compilar

$(Fobj)\Lista.obj :  {$(Pc)}\Lista.c \
    {$(PDEFAULT)}LISTA.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Vertice.obj :  {$(Pc)}\Vertice.c \
    {$(PDEFAULT)}LISTA.H              {$(PDEFAULT)}VERTICE.H           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\TestGra.obj :  {$(Pc)}\TestGra.c \
    {$(PDEFAULT)}GRAFO.H              {$(PDEFAULT)}TST_ESPC.H           {$(PDEFAULT)}TST_Espc.h           \
    {$(PDEFAULT)}generico.h           {$(PDEFAULT)}lerparm.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Grafo.obj :  {$(Pc)}\Grafo.c \
    {$(PDEFAULT)}GRAFO.H              {$(PDEFAULT)}LISTA.H              {$(PDEFAULT)}VERTICE.H           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Termina��o

Construto : \
   $(Fobj)\Lista.obj   $(Fobj)\Vertice.obj   $(Fobj)\TestGra.obj \
   $(Fobj)\Grafo.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: Trabalho
###
##################################################

