#if ! defined( RECURSO_ )
#define RECURSO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo recurso
*
*  Arquivo gerado:              RECURSO.H
*  Letras identificadoras:      REC
*
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mv - Mauricio Pedro Silva Gonçalves Vieira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   mv   01/05/2017 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar, alterar
*	  consultar e destruir estruturas do tipo Recurso
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     A cada momento o módulo admite no máximo uma única árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     A árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*
***************************************************************************/
 
#if defined( RECURSO_OWN )
   #define RECURSO_EXT
#else
   #define RECURSO_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: REC Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         REC_CondRetOK = 0 ,
               /* Executou correto */

         REC_CondRetFaltouMemoria = 1
               /* Faltou memória ao alocar dados */

   } REC_tpCondRet ;
   

   /***********************************************************************
   *
   *  $TC Tipo de dados: REC ponteiro para um Recurso
   *
   *
   ***********************************************************************/

   typedef struct tgRecurso tpRecurso;


/***********************************************************************
*
*  $FC Função: REC Criar árvore
*
*  $ED Descrição da função
*     Cria uma instância do tipo Recurso
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*
***********************************************************************/

   REC_tpCondRet REC_CriarRecurso(tpRecurso ** ptRecurso, char * novoNome) ;


/***********************************************************************
*
*  $FC Função: ARV Destruir recurso
*
*  $ED Descrição da função
*     Destroi o recurso liberando a memoria alocada para a variavel nome
*	  e depois a memoria alocada pro resto da estrutura
*
***********************************************************************/

   void REC_DestruirRecurso( tpRecurso ** ptRecurso ) ;


///***********************************************************************
//*
//*  $FC Função: ARV Adicionar filho à esquerda
//*
//*  $EP Parâmetros
//*     $P ValorParm - valor a ser inserido no novo nó.
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetErroEstrutura
//*     ARV_CondRetFaltouMemoria
//*     ARV_CondRetNaoEhFolha     - caso não seja folha para a esquerda
//*
//***********************************************************************/
//
//   REC_tpCondRet ARV_InserirEsquerda( char ValorParm ) ;
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Adicionar filho à direita
//*
//*  $EP Parâmetros
//*     $P ValorParm - valor a ser inserido no novo nó
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetErroEstrutura
//*     ARV_CondRetFaltouMemoria
//*     ARV_CondRetNaoEhFolha     - caso não seja folha para a direita
//*
//***********************************************************************/
//
//   REC_tpCondRet ARV_InserirDireita( char ValorParm ) ;
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Ir para nó pai
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetArvoreNaoExiste
//*     ARV_CondRetArvoreVazia
//*     ARV_CondRetNoEhRaiz
//*
//***********************************************************************/
//
//   REC_tpCondRet ARV_IrPai( void ) ;
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Ir para nó à esquerda
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetArvoreNaoExiste
//*     ARV_CondRetArvoreVazia
//*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
//*
//***********************************************************************/
//
//   REC_tpCondRet ARV_IrNoEsquerda( void ) ;
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Ir para nó à direita
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetArvoreNaoExiste
//*     ARV_CondRetArvoreVazia
//*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
//*
//***********************************************************************/
//
//   REC_tpCondRet ARV_IrNoDireita( void ) ;
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Obter valor corrente
//*
//*  $EP Parâmetros
//*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
//*                    Este parâmetro é passado por referência.
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetArvoreNaoExiste
//*     ARV_CondRetArvoreVazia
//*
//***********************************************************************/
//
//   REC_tpCondRet ARV_ObterValorCorr( char * ValorParm ) ;

#undef RECURSO_EXT

/********** Fim do módulo de definição: Módulo recurso **********/

#else
#endif
