/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTTRF.C
*  Letras identificadoras:      TTRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo tarefa. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo tarefa:
*
*     "=criar"          - chama a fun��o TRF_CriarTarefa( )
*     "=destruir"       - chama a fun��o TRF_DestruirTarefa( )
*     "=conectar"       - chama a fun��o TRF_ConectarTarefas( )
*     "=alterar"        - chama a fun��o TRF_AlterarTarefa( )
*     "=consultarnome"  - chama a fun��o TRF_ConsultarNomeTarefa( )
*     "=consultardesc"  - chama a fun��o TRF_ConsultarDescricaoTarefa( )
*     "=cadastraridrec" - chama a fun��o TRF_CadastrarIdRecurso( )
*     "=consultaridrec" - chama a fun��o TRF_ConsultarIdRecurso( )
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

#define STRING_DIM 100

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_TRF_CMD               "=criar"
#define     DESTRUIR_TRF_CMD            "=destruir"
#define     CONECTAR_TRF_CMD            "=conectar"
#define     ALTERAR_TRF_CMD             "=alterar"
#define     CONSULTAR_ID_TRF_CMD		    "=consultarid"
#define     CONSULTAR_NOME_TRF_CMD      "=consultarnome"
#define     CONSULTAR_DESC_TRF_CMD      "=consultardesc"
#define     CONSULTAR_DUR_TRF_CMD       "=consultardur"
#define     CADASTRAR_ID_REC_TRF_CMD    "=cadastraridrec"
#define     CONSULTAR_ID_REC_TRF_CMD    "=consultaridrec"
#define     TEM_PREDECESSOR_TRF_CMD     "=tempred"
#define     TEM_SUCESSOR_TRF_CMD        "=temsuc"
#define     CAMINHO_CRITICO_TRF_CMD     "=caminhocritico"

/* Vetor de tarefas para serem usados nos testes */

tcTarefa * tarefas[10];

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TTRF Efetuar opera��es de teste espec�ficas para tarefa
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     tarefa sendo testado.
*
*  $EP Par�metros
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
        int  idConsultado = -1;
        int  duracaoConsultada = -1;
        int  idRecursoObtido = -1;
        int  situacaoObtida = -1;
        int  duracaoObtida = -1;
        char NomeObtido[STRING_DIM];
        char DescricaoObtida[STRING_DIM];
        char * NomeConsultado = (char*)malloc(sizeof(char)*STRING_DIM);
        char * DescricaoConsultada = (char*)malloc(sizeof(char)*STRING_DIM);
        int  NumLidos = -1 ;

        TST_tpCondRet Ret ;

        /* Testar TRF Criar tarefa */

        if ( strcmp( ComandoTeste , CRIAR_TRF_CMD ) == 0 )
        {

            NumLidos = LER_LerParametros( "issii" ,
                                            &TarefaObtida, NomeObtido, DescricaoObtida, &duracaoObtida, &CondRetEsperada ) ;

            if ( NumLidos != 5 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_CriarTarefa(&tarefas[TarefaObtida], NomeObtido, DescricaoObtida, duracaoObtida);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar tarefa." );

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
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
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
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }
             
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao conectar tarefas." );

        } /* fim ativa: Testar TRF Conectar tarefas */

        /* Testar TRF Alterar tarefa */

        else if ( strcmp( ComandoTeste, ALTERAR_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "issii" ,
                                            &TarefaObtida, NomeObtido, DescricaoObtida, &duracaoObtida, &CondRetEsperada ) ;

            if ( NumLidos != 5 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_AlterarTarefa(&tarefas[TarefaObtida], NomeObtido, DescricaoObtida, duracaoObtida);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao alterar tarefa." );

        } /* fim ativa: Testar TRF Alterar tarefas */

        /* Testar TRF Consultar id da tarefa */

        else if ( strcmp( ComandoTeste, CONSULTAR_ID_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "ii" ,
                                            &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_ConsultarIdTarefa(&tarefas[TarefaObtida], &idConsultado);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar id da tarefa." );

        } /* fim ativa: Testar TRF Consultar id da tarefa */

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
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar nome da tarefa." );

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
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar descricao da tarefa." );

        } /* fim ativa: Testar TRF Consultar descricao de tarefa */

        /* Testar TRF Consultar duracao da tarefa */

        else if ( strcmp( ComandoTeste, CONSULTAR_DUR_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "ii" ,
                                            &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_ConsultarDuracaoTarefa(&tarefas[TarefaObtida], &duracaoConsultada);
            }
            else
            {
            return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                    "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar id da tarefa." );

        } /* fim ativa: Testar TRF Consultar duracao da tarefa */


        /* Testar TRF Cadastrar id do recurso da tarefa */

        else if ( strcmp( ComandoTeste, CADASTRAR_ID_REC_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "iii" ,
                                            &TarefaObtida, &idRecursoObtido, &CondRetEsperada ) ;

            if ( NumLidos != 3 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_CadastrarIdRecurso(&tarefas[TarefaObtida], idRecursoObtido);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao cadastrar id do recurso da tarefa." );

        } /* fim ativa: TRF Cadastrar id do recurso da tarefa */

        /* Testar TRF Consultar id do recurso da tarefa */

        else if ( strcmp( ComandoTeste, CONSULTAR_ID_REC_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "ii" ,
                                            &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_ConsultarIdRecurso(&tarefas[TarefaObtida], &idRecursoObtido);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar id do recurso da tarefa." );

        } /* fim ativa: TRF Consultar id do recurso da tarefa */
        
        /* Testar TRF Checa se a lista de predecessores est� vazia */

        else if ( strcmp( ComandoTeste, TEM_PREDECESSOR_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "ii" ,
                                            &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_TemPredecessores(tarefas[TarefaObtida], &situacaoObtida);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar se a tarefa possui predecessores." );

        } /* fim ativa: TRF Checa se a lista de predecessores est� vazia */

        /* Testar TRF Checa se a lista de sucessores est� vazia */

        else if ( strcmp( ComandoTeste, TEM_SUCESSOR_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "ii" ,
                                            &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_TemSucessores(tarefas[TarefaObtida], &situacaoObtida);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar se a tarefa possui sucessores." );

        } /* fim ativa: TRF Checa se a lista de sucessores est� vazia */

        /* Testar TRF Calcula Caminho Cr�tico */

        else if ( strcmp( ComandoTeste, CAMINHO_CRITICO_TRF_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "ii" ,
                                            &TarefaObtida, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( TarefaObtida < 10 && TarefaObtida >= 0 )
            {
                CondRetObtido = TRF_CalculaCaminhoCritico(tarefas[TarefaObtida]);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
                                        "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao calcular o caminho critico." );

        } /* fim ativa: TRF Calcula Caminho Cr�tico */

        return TST_CondRetNaoConhec ;	

    } /* Fim fun��o: TTRF Efetuar opera��es de teste espec�ficas para tarefa */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

