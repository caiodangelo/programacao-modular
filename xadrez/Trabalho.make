##################################################
###
### Diretivas de MAKE para o construto: Trabalho
### Gerado a partir de: comprec.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
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

### Nomes de diretórios para geração

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


### Regras de geração

all : limpa \
   $(Fobj)\Gerenciador.obj   $(Fobj)\Reconhecedor.obj   $(Fobj)\Grafo.obj \
   $(Fobj)\Vertice.obj   $(Fobj)\Lista.obj   $(Fobj)\TestRec.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\Gerenciador.obj :  {$(Pc)}\Gerenciador.c \
    {$(PDEFAULT)}GERENCIADOR.H        {$(PDEFAULT)}VERTICE.H           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Reconhecedor.obj :  {$(Pc)}\Reconhecedor.c \
    {$(PDEFAULT)}GERENCIADOR.H        {$(PDEFAULT)}GRAFO.H              {$(PDEFAULT)}RECONHECEDOR.H      
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Grafo.obj :  {$(Pc)}\Grafo.c \
    {$(PDEFAULT)}GRAFO.H              {$(PDEFAULT)}LISTA.H              {$(PDEFAULT)}VERTICE.H           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Vertice.obj :  {$(Pc)}\Vertice.c \
    {$(PDEFAULT)}LISTA.H              {$(PDEFAULT)}VERTICE.H           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Lista.obj :  {$(Pc)}\Lista.c \
    {$(PDEFAULT)}LISTA.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\TestRec.obj :  {$(Pc)}\TestRec.c \
    {$(PDEFAULT)}RECONHECEDOR.H       {$(PDEFAULT)}TST_ESPC.H           {$(PDEFAULT)}TST_Espc.h           \
    {$(PDEFAULT)}generico.h           {$(PDEFAULT)}lerparm.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\Gerenciador.obj   $(Fobj)\Reconhecedor.obj   $(Fobj)\Grafo.obj \
   $(Fobj)\Vertice.obj   $(Fobj)\Lista.obj   $(Fobj)\TestRec.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: Trabalho
###
##################################################

