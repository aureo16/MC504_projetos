# Projeto 1 - Animação Multithreads com Semáforos

## Equipe
- Áureo Henrique e Silva Marques - RA 213374
- Jonas Cardoso Gonçalves - RA 256453
- Lethycia Maia de Souza - RA 256477
- Samuel Nascimento de Souza - RA 244192

## Apresentação da ideia

O objetivo deste projeto é implementar uma aplicação multithread que utiliza semáforos para sincronização das threads e construir um visualizador para analisar o progresso dessa aplicação.
O tema escolhido para desenvolvimento do programa foi o de simular um Restaurante Universitário (“RS”) da Unicamp. Portanto, o personagem principal do nosso projeto é o estudante universitário e suas ações no restaurante são: esperar na fila externa; passar pela catraca; esperar em uma das filas internas; encontrar um assento; comer; e sair do restaurante.

## Uso das threads

Para sincronização dos estudantes (representados pelas threads), os semáforos são utilizados, em cada etapa, da seguinte maneira:
Esperando na fila externa: Os estudantes chegam no restaurante e precisam esperar na fila externa. Para verificarem se chegou sua vez de passar pela catraca, eles aguardam um semáforo de verificação de sua posição (sem_verifFilaExterna). Quando ele consegue o recurso para ver se é sua vez, ele analisa se o verificador de posição é menor que o seu identificador (id). Se for menor, significa que não chegou sua vez, logo, a thread libera o recurso e espera alguns segundos para verificar novamente. Se não, significa que chegou sua vez, então ele incrementa o verificador para chamar a próxima thread. Contudo, o estudante espera primeiramente o semáforo de catraca (sem_catraca) para depois soltar o sem_verifFilaExterna, de modo a evitar que uma thread passe em sua frente e pegue a catraca disponível.
Passando pela catraca e entrando na fila: Estando na catraca, o estudante vai para a tentativa de pegar um lugar na fila. Há duas filas, a tradicional e a vegetariana. É selecionada aleatoriamente uma fila para o estudante entrar. Em seguida, ele tenta pegar um recurso do semáforo da fila interna selecionada (sem_filaInterna). Ele só não conseguirá entrar se a fila estiver lotada, com isso, terá que selecionar mais uma vez a fila e tentar entrar novamente até ter sucesso. Conseguindo um lugar na fila escolhida, a thread insere seu id na lista ligada referente a sua fila e libera o recurso da catraca.
Esperando na fila interna: A análise da posição na fila interna é feita de modo semelhante à da fila externa, com a diferença de que, ao conseguir o recurso para verificar sua posição (sem_verifFilaInterna), a thread compara seu id com o primeiro elemento da lista ligada da fila.
Encontrando um assento e comendo: Quando chega sua vez de pegar comida, ela retira seu id da lista da fila e aguarda um recurso do semáforo de assento (sem_assento). Ao obter um assento, a thread libera tanto sem_verifFilaInterna como sem_filaInterna e fica parada alguns segundos para comer a refeição. Ao terminar, o estudante libera o assento e vai embora do restaurante.

## Destaques de código

Para a inicialização dos semáforos foi utilizado o método "sem_init" da biblioteca "semaphore.h", passando como parâmetros o semáforo a ser inicializado, o valor 0 como segundo parâmetro indica que esse semáforo é compartilhado entre outras threads do mesmo processo, e o terceiro parâmetro indica a quantidade de recursos disponíveis em cada um deles. Para os semáforos referentes às filas internas, foram inicializados um para cada fila.
![funcao_dicas](images/codigo_dicas.png)

Para verificar se a fila interna escolhida ainda possui recursos a serem utilizados, foi usado o método "sem_trywait", que tenta adquirir um recurso da fila, caso não haja nenhum disponível, ele não trava a execução.
![funcao_threads](images/codigo_threads.png)

## Visualização

A imagem abaixo apresenta a visualização construída para analisar o estado da aplicação. O canto superior direito mostra a fila externa para entrar no restaurante. Na entrada, há duas catracas representadas por L (se estiverem livres) ou por O (se estiverem ocupadas). Ao lado, na parte de dentro do restaurante, pode-se ver as duas filas para pegar comida e, abaixo, o refeitório com os assentos. No canto inferior direito, há alguns estudantes que já foram embora. Os estudantes são representados por números.
![Tempos](images/testetempo.png)
