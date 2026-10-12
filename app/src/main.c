#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024


#define PRIO_A 3
#define ITERS 10000000
volatile int counter=0;
static struct k_sem done_sem;
static struct k_mutex counter_mutex;

void counter_thread(void *p1, void *p2, void *p3)
{
    for(int i = 0; i < ITERS; i++) {
        k_mutex_lock(&counter_mutex, K_FOREVER);
        counter++;
        k_mutex_unlock(&counter_mutex);
    }
    k_sem_give(&done_sem);
}

K_THREAD_DEFINE(thread_a, STACK_SIZE, counter_thread, NULL, NULL, NULL, PRIO_A, 0, 0);
K_THREAD_DEFINE(thread_b, STACK_SIZE, counter_thread, NULL, NULL, NULL, PRIO_A, 0, 0);

int main(void)
{
    k_mutex_init(&counter_mutex);
    k_sem_init(&done_sem, 0, 2);
    k_sem_take(&done_sem, K_FOREVER);
    k_sem_take(&done_sem, K_FOREVER);
    LOG_INF("Counter value: %d\n", counter);
    return 0;
}

