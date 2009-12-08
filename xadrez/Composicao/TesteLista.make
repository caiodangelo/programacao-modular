##################################################
###
### Diretivas de MAKE para o construto: TesteLista
### Gerado a partir de: CompLis.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteLista


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pespstr              = ..\Fontes
Plista               = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

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


### Regras de geração

all : limpa \
   $(Fobj)\lista.obj   $(Fobj)\testlis.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    ..\\tabelas\\idtiposespaco.def {$(Ph)}cespdin.h            {$(Ph)}conta.h              \
    {$(Ph)}generico.h           {$(Ph)}lista.h              {$(Ph)}tst_espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\testlis.obj :  {$(Pc)}\testlis.c \
    {$(Ph)}generico.h           {$(Ph)}lerparm.h            {$(Ph)}lista.h              \
    {$(Ph)}tst_espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\lista.obj   $(Fobj)\testlis.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteLista
###
##################################################

