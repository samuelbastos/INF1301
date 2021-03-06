#if ! defined( RECURSO_ )
#define RECURSO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo recurso
*
*  Arquivo gerado:              RECURSO.H
*  Letras identificadoras:      REC
*
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mv - Mauricio Pedro Silva Gon�alves Vieira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   mv   01/05/2017 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar, alterar
*	  consultar e destruir estruturas do tipo Recurso
*     O recurso possui uma cabe�a que cont�m uma refer�ncia para a estrutura recurso
*     O m�dulo admite a cria��o de mais de um recurso
*     Ao iniciar a execu��o do programa n�o existe recurso.
*     Se a cabe�a de um recurso existir o ponteiro recurso dessa estrutura de cabe�a
*	  necessariamente precisa apontar para uma estrutura Recurso diferente de NULL
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

								REC_CondRetRecursoNaoExiste = 1,
												/* O recurso n�o existe */

								REC_CondRetNomeInvalido = 2,
												/* O nome � invalido */

								REC_CondRetFaltouMemoria = 3
												/* Faltou mem�ria ao alocar dados */

				} REC_tpCondRet ;
   

   /***********************************************************************
   *
   *  $TC Tipo de dados: REC cabe�a de uma estrutura de recurso
   *
   *
   ***********************************************************************/

   typedef struct tcRecurso tcRecurso;


/***********************************************************************
*
*  $FC Fun��o: REC Criar recurso
*
*  $ED Descri��o da fun��o
*     Cria uma inst�ncia do tipo Recurso
*
*  $EP Par�metros
*     $P ptRecurso - ponteiro que vai armazenar o recurso que foi criado
*	  $P novoNome - nome que dever� ser colocado dentro do recurso
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*					REC_CondRetNomeInvalido
*
***********************************************************************/

   REC_tpCondRet REC_CriarRecurso(tcRecurso ** ptRecurso, char * novoNome) ;


/***********************************************************************
*
*  $FC Fun��o: REC Destruir recurso
*
*  $ED Descri��o da fun��o
*     Destroi o recurso liberando a memoria alocada para a variavel nome
*	  e depois a memoria alocada pro resto da estrutura
*
***********************************************************************/

   void REC_DestruirRecurso( tcRecurso ** ptRecurso ) ;


/***********************************************************************
*
*  $FC Fun��o: REC Alterar nome do recurso
*
*  $EP Par�metros
*	  $P ptRecurso - Recurso que ter� o nome alterado
*	  $P novoNome - nome que dever� ser colocado dentro do recurso no lugar
*					do nome atual
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	  REC_CondRetRecursoNaoExiste
*	  REC_CondRetNomeInvalido
*
***********************************************************************/

   REC_tpCondRet REC_AlterarNome(tcRecurso * ptRecurso, char * novoNome);


/***********************************************************************
*
*  $FC Fun��o: REC Marca o recurso como ocupado
*
*  $EP Par�metros
*     $P ptRecurso - Recurso que ser� marcada como ocupada
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_MarcarComoOcupada(tcRecurso * ptRecurso);


/***********************************************************************
*
*  $FC Fun��o: REC Marca recurso como dispon�vel
*
*  $EP Par�metros
*     $P ptRecurso - Recurso que ser� marcada como dispon�vel
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_MarcarComoDisponivel(tcRecurso * ptRecurso);


/***********************************************************************
*
*  $FC Fun��o: REC Consulta o Id do recurso
*
*  $EP Par�metros
*     $P ptRecurso - Recurso que ser� consultada
*	  $P id - ponteiro para o local de memoria onde o id do recurso ser�
*			  armazenado para consulta externa
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ConsultarId(tcRecurso * ptRecurso, int * id);


/***********************************************************************
*
*  $FC Fun��o: REC Consulta o nome do recurso
*
*  $EP Par�metros
*     $P ptRecurso - Recurso que ser� consultada
*	  $P pNome - ponteiro para o local de memoria onde o nome do recurso 
*				 ser� armazenado para consulta externa
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ConsultarNome(tcRecurso * ptRecurso, char ** pNome);


/***********************************************************************
*
*  $FC Fun��o: REC Consulta a disponibilidade do Recurso
*
*  $EP Par�metros
*     $P ptRecurso - Recurso que ser� consultada
*	  $P id - ponteiro para o local de memoria onde a disponibilidade do 
*			  recurso ser� armazenada para consulta externa
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ConsultarDisponibilidade(tcRecurso * ptRecurso, int * estaDisponivel);

/***********************************************************************
*
*  $FC Fun��o: REC Imprime informa��es do Recurso
*
*  $EP Par�metros
*     $P ptRecurso - Recurso que ter� suas informa��es impressas
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ImprimeRecurso(tcRecurso * ptRecurso);

#undef RECURSO_EXT

/********** Fim do m�dulo de defini��o: M�dulo recurso **********/

#else
#endif
