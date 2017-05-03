/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTREC.C
*  Letras identificadoras:      TREC
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mp - Mauricio Pedro Silva Gonçalves Vieira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   mp    01/05/2017 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Recurso. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo recurso:
*
*     "=criar"  <i> <string> 
*				- chama a função REC_CriarRecurso( <i>, <string> )

*     "=destroi" <i>	
*				- chama a função REC_DestruirRecurso( <i> )

	  "=altnome" <i> <string>
				- chama a função para alterar o nome REC_AlterarNome( <i>, <string> )
*
*	  Obs: notação: <i> é o valor do parâmetro que se encontra no comando
*						de teste que é um inteiro e significa qual das ta-
*						refas criadas pelo módulo de testes o comando está
*						se referindo
*					<string> é o valor do parâmetro que se encontra no 
*							 comando de teste que é uma sequencia de 
*							 caracteres que simboliza o nome do recurso
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "recurso.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_REC_CMD       "=criar"
#define     DESTROI_CMD         "=destruir"
#define		ALTERAR_NOME_CMD	"=altnome"

#define		STRING_DIM 100

/* Vetor de recursos para serem usados nos testes */

tpRecurso * recursos[10];


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TREC Efetuar operações de teste específicas para recurso
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     recurso sendo testado.
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

      REC_tpCondRet CondRetObtido   = REC_CondRetOK ;
      REC_tpCondRet CondRetEsperada = REC_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

	  int RecursoObtido = 11;
	  char NomeObtido[STRING_DIM];
	  char * NomeConsultado = (char*)malloc(sizeof(char) * 100);

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar REC Criar Recurso */

         if ( strcmp( ComandoTeste , CRIAR_REC_CMD) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &RecursoObtido, NomeObtido, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_CriarRecurso(&recursos[RecursoObtido], NomeObtido);
			}
			else
			{
				return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar recurso." );

         } /* fim ativa: Testar REC Criar recurso */

      /* Testar REC Destruir recurso */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("i",
								&RecursoObtido);
			if (NumLidos != 1)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				REC_DestruirRecurso(&recursos[RecursoObtido]);
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CondRetOK ;

         } /* fim ativa: Testar REC Destruir recurso */

	/* Testar REC Alterar nome do recurso */

         else if ( strcmp( ComandoTeste , ALTERAR_NOME_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("isi",
								&RecursoObtido, NomeObtido, &CondRetEsperada);
			if (NumLidos != 1)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				REC_DestruirRecurso(&recursos[RecursoObtido]);
			}
			else
			{
				CondRetObtido = TST_CondRetAcessoInvalidoVetor;
				return TST_CompararInt(TST_CondRetOK, CondRetObtido,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CondRetOK ;

         } /* fim ativa: Testar REC Destruir recurso */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TREC Efetuar operações de teste específicas para recurso */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

