/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTTRF.C
*  Letras identificadoras:      TTRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo tarefa. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo tarefa:
*
*     "=criar"          - chama a função TRF_CriarTarefa( )
*     "=destruir"       - chama a função TRF_DestruirTarefa( )
*     "=conectar"       - chama a função TRF_ConectarTarefas( )
*     "=alterar"        - chama a função TRF_AlterarTarefa( )
*     "=consultarnome"  - chama a função TRF_ConsultarNomeTarefa( )
*     "=consultardesc"  - chama a função TRF_ConsultarDescricaoTarefa( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "tarefa.h"
#include	"lista.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_TRF_CMD          "=criar"
#define     DESTRUIR_TRF_CMD       "=destruir"
#define     CONECTAR_TRF_CMD       "=conectar"
#define     ALTERAR_TRF_CMD        "=alterar"
#define     CONSULTAR_NOME_TRF_CMD "=consultarnome"
#define     CONSULTAR_DESC_TRF_CMD "=consultardesc"

#define STRING_DIM 100

/* Vetor de tarefas para serem usados nos testes */

void * tarefas[10];

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTRF Efetuar operações de teste específicas para tarefa
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     tarefa sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      TRF_tpCondRet CondRetObtido   = TRF_CondRetOK ;
      TRF_tpCondRet CondRetEsperada = TRF_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado   = '?'  ;
      char ValorObtido     = '!'  ;
      char ValorDado       = '\0' ;
	  int  TarefaObtida    = 11  ;
      int  TarefaObtidaAux = 12;
      char NomeObtido[STRING_DIM];
      char DescricaoObtida[STRING_DIM];
      char * NomeConsultado = (char*)malloc(sizeof(char)*STRING_DIM);
      char * DescricaoConsultada = (char*)malloc(sizeof(char)*STRING_DIM);
      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar TRF Criar tarefa */

         if ( strcmp( ComandoTeste , CRIAR_TRF_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "issi" ,
                               &TarefaObtida, NomeObtido, DescricaoObtida, &CondRetEsperada ) ;

            if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( TarefaObtida < 10 && TarefaObtida >= 0 )
			{
				CondRetObtido = TRF_CriarTarefa(&tarefas[TarefaObtida], NomeObtido, DescricaoObtida);
			}
			else
			{
				CondRetObtido = TRF_CondRetAcessoInvalidoVetor;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar TRF Criar tarefa */

      /* Testar TRF Destruir tarefa */

         else if ( strcmp( ComandoTeste , DESTRUIR_TRF_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i", &TarefaObtida ) ;

			if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                TRF_DestruirTarefa( &tarefas[TarefaObtida] ) ;
            }

            return TST_CondRetOK ;

         } /* fim ativa: Testar TRF Destruir tarefa */

      /* Testar TRF Conectar tarefas */

         else if ( strcmp( ComandoTeste, CONECTAR_TRF_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii", &TarefaObtida, &TarefaObtidaAux, &CondRetEsperada ) ;

            if( NumLidos != 3 )
            {
                return TST_CondRetParm ;
            } /* if */

			if ( TarefaObtida < 10 && TarefaObtida >= 0 && TarefaObtida != TarefaObtidaAux &&
                 TarefaObtidaAux < 10 && TarefaObtidaAux >= 0)
			{
				CondRetObtido = TRF_ConectarTarefas(&tarefas[TarefaObtida], &tarefas[TarefaObtidaAux]);
			}
			else
			{
				CondRetObtido = TRF_CondRetAcessoInvalidoVetor;
			}
             
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar TRF Conectar tarefas */

      /* Testar TRF Alterar tarefa */

         else if ( strcmp( ComandoTeste, ALTERAR_TRF_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "issi" ,
                               &TarefaObtida, NomeObtido, DescricaoObtida, &CondRetEsperada ) ;

            if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( TarefaObtida < 10 && TarefaObtida >= 0 )
			{
				CondRetObtido = TRF_AlterarTarefa(&tarefas[TarefaObtida], NomeObtido, DescricaoObtida);
			}
			else
			{
				CondRetObtido = TRF_CondRetAcessoInvalidoVetor;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar TRF Alterar tarefas */

      /* Testar TRF Consultar nome de tarefa */

         else if ( strcmp( ComandoTeste, CONSULTAR_NOME_TRF_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" ,
                               &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( TarefaObtida < 10 && TarefaObtida >= 0 )
			{
				CondRetObtido = TRF_ConsultarNomeTarefa(&tarefas[TarefaObtida], &NomeConsultado);
			}
			else
			{
				CondRetObtido = TRF_CondRetAcessoInvalidoVetor;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar TRF Consultar nome de tarefa */

    /* Testar TRF Consultar descricao de tarefa */

         else if ( strcmp( ComandoTeste, CONSULTAR_DESC_TRF_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" ,
                               &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( TarefaObtida < 10 && TarefaObtida >= 0 )
			{
				CondRetObtido = TRF_ConsultarDescricaoTarefa(&tarefas[TarefaObtida], &DescricaoConsultada);
			}
			else
			{
				CondRetObtido = TRF_CondRetAcessoInvalidoVetor;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar TRF Consultar descricao de tarefa */

      return TST_CondRetNaoConhec ;	

   } /* Fim função: TTRF Efetuar operações de teste específicas para tarefa */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

