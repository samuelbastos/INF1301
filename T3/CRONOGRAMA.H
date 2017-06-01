#if ! defined( CRONOGRAMA_ )
#define CRONOGRAMA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo tarefa
*
*  Arquivo gerado:              CRONOGRAMA.H
*  Letras identificadoras:      CRO
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T3 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar um cronograma
*	  e determinar o seu caminho crítico.
*     A cada momento o módulo admite no máximo um cronograma.
*     Cada cronograma possui uma lista de recursos e uma lista de tarefas.
*     Ao iniciar a execução do programa não existe cronograma.
*
***************************************************************************/
 
#if defined( CRONOGRAMA_OWN )
   #define CRONOGRAMA_EXT
#else
   #define CRONOGRAMA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: CRO Condicoes de retorno
*
*
***********************************************************************/

				typedef enum {

								CRO_CondRetOK = 0,
												/* Executou correto */

								CRO_CondRetFaltouMemoria = 1,
												/* Faltou memória ao alocar os dados */

								CRO_NomeRecursoInvalido = 2,
												/* Nome fornecido para recurso inválido */
				   
				} CRO_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: CRO cabeça de uma estrutura de cronograma
*
*
***********************************************************************/

   typedef struct tcCronograma tcCronograma;

/***********************************************************************
*
*  $FC Função: CRO Criar Cronograma
*
*  $ED Descrição da função
*     Cria uma novo cronograma vazio.
*     Caso já exista um cronograma, este será destruído.
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro passado por referência para apontar para a 
*				                   cabeça do cronograma a ser criado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

   CRO_tpCondRet CRO_CriarCronograma( tcCronograma ** ctCronograma );

/***********************************************************************
*
*  $FC Função: CRO Destruir cronograma
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro passado por referência que aponta para a 
*                       cabeça do cronograma que será destruido
*
*  $ED Descrição da função
*    Destroi o cronograma passado por referência. 
*
***********************************************************************/

   void CRO_DestruirCronograma( tcCronograma ** ctCronograma );

/***********************************************************************
*
*  $FC Função: CRO Insere Tarefa
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*     $P novoNome      - nome da tarefa a ser inserida
*     $P novaDescricao - descricao da tarefa a ser inserida
*
*  $ED Descrição da função
*    Insere uma nova tarefa na lista de tarefas do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

   CRO_tpCondRet CRO_InserirTarefa( tcCronograma * ctCronograma, char * novoNome, char * novaDescricao );

/***********************************************************************
*
*  $FC Função: CRO Insere Recurso
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*     $P novoNome      - nome do recurso a ser inserido
*
*  $ED Descrição da função
*    Insere um novo recurso na lista de recursos do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*					CRO_NomeRecursoInvalido
*
***********************************************************************/

   CRO_tpCondRet CRO_InserirRecurso( tcCronograma * ctCronograma, char * novoNome);

#undef CRONOGRAMA_EXT

/********** Fim do módulo de definição: Módulo cronograma **********/

#else
#endif
