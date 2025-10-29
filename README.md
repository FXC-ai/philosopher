# Philosopher

[Threads, mutex et programmation concurrente en C - codequoi](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)

[[Operating System] The Dining Philosophers Problem](https://medium.com/@jinghua.shih/operating-system-the-dining-philosophers-problem-6f35f210a4e2)

# Comment utiliser des thread

```c
#include <pthread.h>
#include <stdio.h>

void *routine(void *value)
{
	int *cpy_ptr_value = value;
	int cpy_value;
	cpy_value = *cpy_ptr_value;

	printf("Une citation quelconque  %d\n", cpy_value);
	return (NULL);

}
void *routine2(void *value)
{
	int *cpy_ptr_value = value;
	int cpy_value;
	cpy_value = *cpy_ptr_value;

	printf("Vivre et laisser mourir  %d\n", cpy_value);
	return (NULL);

}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;

	int	thread_1;
	int	thread_2;

	thread_1 = 1;
	thread_2 = 2;

	pthread_create(&tid1, NULL, routine, &thread_1);
	pthread_create(&tid2, NULL, routine2, &thread_2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
```

# Exemple de Data Race

```c
#include <pthread.h>
#include <stdio.h>
#define MAX 100000

typedef struct s_test_philo {

	int *count;
	int id_thread;

} t_test_philo;

void *routine(void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	int i;

	printf("Début de processus pour le thread : %d\n", cpy_test_philo->id_thread);
	
	i = 0;
	while (i < MAX)
	{
		(*(cpy_test_philo->count))++;
		//printf("WHAT %d\n", *cpy_ptr_value);
		i++;
	}
	printf("Fin de processus %d pour le thread %d\n", *(cpy_test_philo->count), cpy_test_philo->id_thread);
	
	return (NULL);
}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;

	int shared_value;
	shared_value = 0;
	
	t_test_philo	test_philo;
	test_philo.count = &shared_value;
	test_philo.id_thread = 1;
	
	t_test_philo	test_philo2;
	test_philo2.count = &shared_value;
	test_philo2.id_thread = 2;
	
	pthread_create(&tid1, NULL, routine, &test_philo);
	pthread_create(&tid2, NULL, routine, &test_philo2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("shared value = %d\n", shared_value);

	return 0;
}
```


🧵 Comprendre le comportement du code multi-thread en C
🔍 Sorties observées

Lorsqu’on exécute le programme suivant, on obtient des résultats différents d’une exécution à l’autre :
``` bash
Début de processus pour le thread : 1
Début de processus pour le thread : 2
Fin de processus 92913 pour le thread 1
Fin de processus 182290 pour le thread 2
shared value = 182290
```

ou parfois :

Début de processus pour le thread : 1
Début de processus pour le thread : 2
Fin de processus 100000 pour le thread 1
Fin de processus 200000 pour le thread 2
shared value = 200000

⚠️ Pourquoi la valeur finale change-t-elle ?

On remarque que la valeur partagée (shared_value) n’est jamais exactement la même à la fin de l’exécution.
La raison est simple : la variable partagée n’est pas protégée.

🧠 Explication

Les deux threads accèdent simultanément à la même variable shared_value sans aucune synchronisation (pas de mutex, pas de verrou).
Chaque thread exécute la ligne :

(*cpy_test_philo->count)++;


Ce qui se déroule en plusieurs étapes internes :

Le thread lit la valeur actuelle de shared_value.

Il ajoute 1 à cette valeur.

Il écrit le résultat à la même adresse mémoire.

Le problème :
Ces trois opérations ne sont pas atomiques, c’est-à-dire qu’elles peuvent être interrompues par un autre thread au milieu du processus.

💥 Exemple concret

Imaginons que shared_value vaut 42.

Le thread 1 lit 42.

Le thread 2 lit aussi 42 (presque au même instant).

Le thread 1 écrit 43.

Le thread 2 écrit lui aussi 43.

Résultat : la variable n’a été incrémentée qu’une seule fois, alors que deux incréments étaient attendus.

Ce phénomène est appelé une condition de course (race condition).
C’est un comportement non déterministe : selon la vitesse du processeur et le moment où chaque thread s’exécute, la valeur finale changera.

🧩 Comprendre la ligne clé : (*cpy_test_philo->count)++

Cette syntaxe peut paraître compliquée, mais elle signifie simplement :

« Incrémente la valeur pointée par le pointeur count ».

Décomposition :

cpy_test_philo → pointeur vers une structure t_test_philo.

cpy_test_philo->count → champ count de la structure, c’est un pointeur vers un entier (int *).

(*cpy_test_philo->count) → valeur entière pointée (ici shared_value).

++ → incrémente cette valeur.

Autrement dit :

(*cpy_test_philo->count)++;


est équivalent à :

(* (cpy_test_philo->count))++;


et signifie : ajoute 1 à la variable partagée.

⚠️ Attention :
Si on écrivait cpy_test_philo->count++, on incrémenterait le pointeur lui-même, pas la valeur pointée.
Cela déplacerait le pointeur vers la prochaine case mémoire, provoquant un comportement indéfini.

✅ En résumé
Concept	Explication
shared_value	Variable globale partagée par les deux threads
cpy_test_philo->count	Pointeur vers cette variable
(*cpy_test_philo->count)++	Incrémente la valeur partagée
cpy_test_philo->count++	Déplacerait le pointeur (⚠️ faux ici)
Problème observé	Condition de course due à l’absence de synchronisation
Solution	Protéger la section critique avec un mutex ou une variable atomique

Souhaite-tu que je te montre la version corrigée du code avec un pthread_mutex pour garantir que shared_value soit bien incrémentée à 200000 à chaque exécution ?

# Utilisation de Mutex

```c
#include <pthread.h>
#include <stdio.h>
#define MAX 21000

typedef struct s_test_philo {

	int				count;
	pthread_mutex_t	count_mutex;

} t_test_philo;

void *routine(void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	int i;

	printf("Début de processus %d\n", cpy_test_philo->count);
	
	i = 0;
	while (i < MAX)
	{
		pthread_mutex_lock(&cpy_test_philo->count_mutex);
		(cpy_test_philo->count)++;
		pthread_mutex_unlock(&cpy_test_philo->count_mutex);
		i++;
	}
	printf("Fin de processus %d\n", cpy_test_philo->count);
	return (NULL);
}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;
	
	t_test_philo	test_philo;
	test_philo.count = 0;
	pthread_mutex_init(&(test_philo.count_mutex), NULL);

	pthread_create(&tid1, NULL, routine, &test_philo);
	pthread_create(&tid2, NULL, routine, &test_philo);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("shared value = %d\n", test_philo.count);

	pthread_mutex_destroy(&test_philo.count_mutex);

	return 0;
}
```

# Exemple de Deadblock

```c
#include <pthread.h>
#include <stdio.h>
#define MAX 21000

typedef struct s_test_philo {
	
	int				count;
	pthread_mutex_t	lock_01;
	pthread_mutex_t	lock_02;

} t_test_philo;

void *routine_thread1 (void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	// int i;

	printf("Le thread 1 veut bloquer le lock1\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_01));
	printf("Le thread 1 bloque le lock1\n");

	printf("Le thread 1 veut bloquer le lock2\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_02));
	printf("Le thread 1 bloque le lock2\n");

	cpy_test_philo->count += 1;

	printf("Le thread 1 veut debloquer le lock2\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_02));
	printf("Le thread 1 debloque le lock2\n");

	printf("Le thread 1 veut debloquer le lock1\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_01));
	printf("Le thread 1 debloque le lock1\n");

	printf("TERMINE POUR LE THREAD 1\n\n");

	return (NULL);
}

void *routine_thread2 (void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	// int i;

	printf("Le thread 2 veut bloquer le lock2\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_02)); //le script  attendra jusqu' a ce que le mutex soit blocable
	printf("Le thread 2 bloque le lock2\n");

	printf("Le thread 2 veut bloquer le lock1\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_01));
	printf("Le thread 2 bloque le lock1\n");

	cpy_test_philo->count += 1;

	printf("Le thread 2 veut debloquer le lock1\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_01));
	printf("Le thread 2 debloque le lock1\n");

	printf("Le thread 2 veut debloquer le lock2\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_02));
	printf("Le thread 2 debloque le lock2\n");

	printf("TERMINE POUR LE THREAD 2\n\n");

	return (NULL);
}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;
	
	t_test_philo	test_philo;
	test_philo.count = 0;
	pthread_mutex_init(&(test_philo.lock_01), NULL);
	pthread_mutex_init(&(test_philo.lock_02), NULL);

	pthread_create(&tid1, NULL, routine_thread1, &test_philo);
	pthread_create(&tid2, NULL, routine_thread2, &test_philo);

	pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);

	printf("shared value = %d\n", test_philo.count);

	pthread_mutex_destroy(&test_philo.lock_01);
	pthread_mutex_destroy(&test_philo.lock_02);

	return 0;
}
```

# gettimeofday()

```c
#include <pthread.h>
#include <stdio.h>
#define MAX 21000

typedef struct s_test_philo {
	
	int				count;
	pthread_mutex_t	lock_01;
	pthread_mutex_t	lock_02;

} t_test_philo;

void *routine_thread1 (void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	// int i;

	printf("Le thread 1 veut bloquer le lock1\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_01));
	printf("Le thread 1 bloque le lock1\n");

	printf("Le thread 1 veut bloquer le lock2\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_02));
	printf("Le thread 1 bloque le lock2\n");

	cpy_test_philo->count += 1;

	printf("Le thread 1 veut debloquer le lock2\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_02));
	printf("Le thread 1 debloque le lock2\n");

	printf("Le thread 1 veut debloquer le lock1\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_01));
	printf("Le thread 1 debloque le lock1\n");

	printf("TERMINE POUR LE THREAD 1\n\n");

	return (NULL);
}

void *routine_thread2 (void *test_philo)
{
	t_test_philo *cpy_test_philo = (t_test_philo *) test_philo;
	// int i;

	printf("Le thread 2 veut bloquer le lock2\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_02)); //le script  attendra jusqu' a ce que le mutex soit blocable
	printf("Le thread 2 bloque le lock2\n");

	printf("Le thread 2 veut bloquer le lock1\n");
	pthread_mutex_lock(&(cpy_test_philo->lock_01));
	printf("Le thread 2 bloque le lock1\n");

	cpy_test_philo->count += 1;

	printf("Le thread 2 veut debloquer le lock1\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_01));
	printf("Le thread 2 debloque le lock1\n");

	printf("Le thread 2 veut debloquer le lock2\n");
	pthread_mutex_unlock(&(cpy_test_philo->lock_02));
	printf("Le thread 2 debloque le lock2\n");

	printf("TERMINE POUR LE THREAD 2\n\n");

	return (NULL);
}

int main()
{
	pthread_t	tid1;
	pthread_t	tid2;
	
	t_test_philo	test_philo;
	test_philo.count = 0;
	pthread_mutex_init(&(test_philo.lock_01), NULL);
	pthread_mutex_init(&(test_philo.lock_02), NULL);

	pthread_create(&tid1, NULL, routine_thread1, &test_philo);
	pthread_create(&tid2, NULL, routine_thread2, &test_philo);

	pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);

	printf("shared value = %d\n", test_philo.count);

	pthread_mutex_destroy(&test_philo.lock_01);
	pthread_mutex_destroy(&test_philo.lock_02);

	return 0;
}
```

# Algo pour manager les philosophers (deprecated)

Ceci est une très mauvaise idée. A ne pas reproduire !

```c
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

time_t	calculate_current_time_ms (time_t start_time_ms)
{
	struct timeval current_time;
	time_t	current_time_ms;
	time_t	result;

	gettimeofday(&current_time, NULL);
	current_time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	result = current_time_ms - start_time_ms;
	return (result);
}

time_t	ft_time(void)
{
	struct		timeval	tv;
	time_t		time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_in_mils);
}

void	ft_usleep(time_t time_in_ms)
{
	time_t	current_time;

	current_time = ft_time();
	while ((ft_time() - current_time) <= time_in_ms)
	{
		usleep(25);
		if ((ft_time() - current_time) >= time_in_ms)
			break ;
	}
}

int main()
{
	int id_philo;
	int	nb_philo;
	int id_tour;
	int nb_tour;

	printf("ft_time = %ld\n", ft_time());

	time_t test = ft_time();
	ft_usleep(200);
	printf("ft_time = %ld\n", calculate_current_time_ms(test));

	nb_philo = 3;
	nb_tour = 5;

	id_tour = 0;
	while (id_tour < nb_tour)
	{
		printf("Tour %d\n", id_tour);
		id_philo = 0;
		while (id_philo < nb_philo)
		{			
			printf("id_philo = %d => %d\n", id_philo, ((id_tour + id_philo) % nb_philo) % 2);
			id_philo++;
		}
		printf("\n");	
		id_tour++;
	}
}
```
