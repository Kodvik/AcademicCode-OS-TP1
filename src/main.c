/* region README */
/* **********************************************         READ ME          **********************************************
 * Code Structure Feita por: Edgard de Paiva Melo Filho (Não distribuir sem autorização) 
 * Code by: Edgard de Paiva Melo Filho (edgard.filho@sga.pucminas.br) - Computer Engineering Student - PUC Minas
 * Date: 2025-05-02 (YYYY-MM-DD)
 * Version: 1.0
 * Sistemas Operacionais - S1 2025 - Professor: Lucas Bragança
 * **********************************************************************************************************************
 * endregion */

/* region Patch Notes */
/* ********************************************         Patch Notes          ******************************************** 
 * Version 0.1:
 * 
 * Patch notes:
 * - Finished the first version of the code.
 * - Debugged the failure generated in the previous version on the client thread creation.
 * Current development status: 
 * - Complete.
 * Next steps: 
 * - 
 * **********************************************************************************************************************
 * endregion */

/* region Include Section */
/* *******************************************         Include section        ******************************************* */
    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <unistd.h> 
    #include <time.h> 
/* ********************************************************************************************************************** */
/* endregion */

/* region Struct/Typedef Section */
/* *******************************************         Struct/Typedef section        ******************************************* */
#define numClientes 5 // Número de clientes
#define numRecursos 3 // Número de recursos

int disponiveis[numRecursos]; // Vetor de caixas disponíveis
int maximo[numClientes][numRecursos]; // Matriz de recursos máximos
int alocado[numClientes][numRecursos]; // Matriz de recursos alocados
int necessario[numClientes][numRecursos]; // Matriz de recursos necessários

pthread_mutex_t mutex; // Mutex para proteger o acesso aos recursos
/* ********************************************************************************************************************** */
/* endregion */

/* region Function Section */
/* *******************************************         Function section        ******************************************* */

/* region Teste de estado seguro */
/**
 * @brief Função para verificar se o estado é seguro.
 * 
 * @param nenhum
 * 
 * @return Retorna 1 se o estado for seguro, 0 se não for seguro.
 */
int estado_seguro(){
    int trabalho[numRecursos]; // Vetor de trabalho
    int finalizado[numClientes]; // Vetor de clientes finalizados

    // copia os recursos disponiveis para o vetor de trabalho
    for(int i=0; i<numRecursos; i++){
        trabalho[i] = disponiveis[i];
    }

    while (1){
        int encontrado = 0; // Flag para verificar se algum cliente foi encontrado
        for (int i=0; i<numClientes; i++){
            if(!finaliado[i]){ // se o cliente não foi finalizado
                int pode_atender = 1; // Flag para verificar se o cliente pode ser atendido
                for(int j=0; j<numRecursos; j++){
                    if(necessario[i][j] > trabalho[j]){
                        pode_atender = 0; // se o cliente não pode ser atendido, não atende
                        break; // sai do loop
                    }
                }
                if(pode_atender){ // se o cliente pode ser atendido
                    for(int j=0; j<numRecursos; j++){
                        trabalho[j] += alocado[i][j]; // adiciona a matriz de alocados
                    }
                    finalizado[i] = 1; // marca o cliente como finalizado
                    encontrado = 1; // marca que encontrou um cliente
                    //printf("Cliente %d foi atendido\n", i); // para debugar por enquanto, lembrar de tirar depois
                }
            }
        }
        if(!encontrado){ // se não encontrou nenhum cliente, sai do loop
            break; // sai do loop
        }
    }
    for(int i=0; i<numClientes; i++){
        if(!finalizado[i]){
            return 0; // se algum cliente não foi finalizado, retorna 0
        }
    }
    return 1; // se todos os clientes foram finalizados, retorna 1
}

/* region Função para solicitar recursos */
/**
 * @brief Função para solicitar recursos.
 * 
 * @param cliente ID do cliente que está solicitando os recursos.
 * @param requisicao Vetor de recursos solicitados pelo cliente.
 * 
 * @return Retorna 0 se a requisição for aceita, -1 se a requisição for rejeitada.
 */
int solicitar_recursos(int cliente, int requisicao[]){
    pthread_mutex_lock(&mutex); // bloqueia o mutex
    // tive que adicionar o bloqueio do mutex aqui, pois o cliente estava pegando os recursos antes de verificar se tinha recursos suficientes
    // e isso estava causando um deadlock, pois o cliente estava esperando os recursos e o servidor estava esperando o cliente liberar os recursos

    for(int i=0; i<numRecursos; i++){
        if(requisicao[i] > necessario[cliente][i] || requisicao[i] > disponiveis[i]){
            //printf("Cliente %d: Requisição invalida\n", cliente); // para debugar por enquanto, lembrar de tirar depois
            pthread_mutex_unlock(&mutex); // libera o mutex
            return -1; // se a requisição for inválida, retorna -1 (rejeitada)
        }
    }
    
    // alocação temporária dos recursos
    for (int i=0; i<numRecursos; i++){
        disponiveis[i] -= requisicao[i]; // subtrai os recursos disponíveis
        alocado[cliente][i] += requisicao[i]; // adiciona os recursos alocados
        necessario[cliente][i] -= requisicao[i]; // subtrai os recursos necessários
    }

    // verifica se o estado é seguro
    if(!estado_seguro()){
        //reverte a alocação dos recursos
        for(int i=0; i<numRecursos; i++){
            disponiveis[i] += requisicao[i]; // adiciona os recursos disponíveis
            alocado[cliente][i] -= requisicao[i]; // subtrai os recursos alocados
            necessario[cliente][i] += requisicao[i]; // adiciona os recursos necessários
        }
        pthread_mutex_unlock(&mutex); // libera o mutex
        return -1; // se o estado não for seguro, retorna -1 (rejeitada)
    }

    pthread_mutex_unlock(&mutex); // libera o mutex (aqui é o correto, pois o cliente já pegou os recursos e já verificou se o estado é seguro)
    return 0; // se a requisição for aceita, retorna 0 (aceita)
}

/* region Thread de cliente */
/**
 * @brief Função executada por uma thread cliente.
 * 
 * @param arg Ponteiro genérico (void*) que pode ser utilizado para passar dados específicos para a thread.
 *             Geralmente, é convertido para o tipo apropriado dentro da função.
 * 
 * @return Retorna um ponteiro genérico (void*), que pode ser utilizado para passar informações de volta ao chamador.
 *         O tipo exato do retorno depende da implementação específica da função.
 */
void* cliente_func(void* arg){
    int cliente= *(int*)arg; // converte o ponteiro genérico para inteiro (ID do cliente)
    while(1){
        int requisicao[numRecursos]; // vetor de recursos solicitados
        for(int i=0; i<numRecursos; i++){
            requisicao[i] = rand() % (maximo[cliente][i] + 1); // gera um número aleatório entre 0 e o máximo de recursos
        }
        //printf("Cliente %d: Requisição de recursos: ", cliente); // para debugar por enquanto, lembrar de tirar depois
        
        if(solicitar_recursos(cliente, requisicao) == 0){
            printf("Cliente %d recebeu recursos\n", cliente);
            sleep(1); // simula o tempo de uso dos recursos
            liberar_recursos(cliente); // libera os recursos
            printf("Cliente %d liberou recursos\n", cliente);
        }
        sleep(1);
    }
    return NULL; //tive que colocar isso aqui, pois o compilador estava reclamando que a função não retornava nada
}
/* ********************************************************************************************************************** */
/* endregion */

/* region Main Code */
/* ********************************************         Main Code          ******************************************** */
int main(int argc, char* argv[]){
    if(argc != numRecursos+1){// verifica se o numero de argumentos está correto
        fprintf(stderr, "Uso: %s <recurso1> <recurso2> <recurso3>\n", argv[0]);
        exit(1); // se não estiver correto, sai do programa
    }

    srand(time(NULL)); // inicializa o gerador de números aleatórios

    //incializa os recursos disponíveis
    for(int i=0; i<numRecursos; i++){
        disponiveis[i] = atoi(argv[i+1]); // converte os argumentos para inteiros e armazena no vetor de recursos disponíveis
    }

    //inicializa demandas maximas e necessidades
    for(int i=0; i<numClientes; i++){
        for(int j=0; j<numRecursos; j++){
            maximo[i][j] = rand() % (disponiveis[j] + 1); // gera um número aleatório entre 0 e o máximo de recursos
            alocado[i][j] = 0; // inicializa a matriz de alocados com 0
            necessario[i][j] = maximo[i][j]; // inicializa a matriz de necessários com o máximo de recursos
        }
    }

    //inicializa o mutex
    if(pthread_mutex_init(&mutex, NULL) != 0){
        fprintf(stderr, "Erro ao inicializar o mutex\n");
        exit(1); // se não conseguir inicializar o mutex, sai do programa
    }

    pthread_t threads[numClientes]; // vetor de threads
    int ids[numClientes]; // vetor de IDs dos clientes

    for(int i=0; i<numClientes; i++){
        ids[i] = i; //inicializa o vetor de IDs dos clientes
        if(pthread_create(&threads[i], NULL, cliente_func, &ids[i]) != 0){ // cria as threads
            fprintf(stderr, "Erro ao criar a thread do cliente %d\n", i);
            exit(1); // se não conseguir criar a thread, sai do programa
            //coloquei um monte de exit pois estava dando erro de segmentação as vezes, e não sabia o que era
            //como o tempo está curto, só coloquei o exit, depois vou ver o que é
        }
    }

    for(int i=0; i<numClientes; i++){
        pthread_join(threads[i], NULL); // espera as threads terminarem
    }

    pthread_mutex_destroy(&mutex); // destrói o mutex
    return 0; // sai do programa com sucesso
}
/* ********************************************************************************************************************** */
/* endregion */
