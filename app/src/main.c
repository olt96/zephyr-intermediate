#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_A 3
#define PRIO_B 5
#define PRIO_C 7
#define PRIO_COOP (-1)

void thread_a_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_HIGH running");
        k_msleep(100);
    }
}

void thread_b_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_MED running");
        k_msleep(200);
    }
}

void thread_c_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_LOW running");
        k_msleep(300);
    }
}

void thread_coop_fn(void *p1, void *p2, void *p3)
{
    LOG_INF("T_COOP running");
    for(int i = 0; i < 5; i++) {
        LOG_INF("Working iteration - %d" , i+1);
        k_busy_wait(400000);
    }
    LOG_INF("T_COOP Yielding");
    k_yield();
}
K_THREAD_DEFINE(thread_a, STACK_SIZE, thread_a_fn,
                NULL, NULL, NULL, PRIO_A, 0, 0);
K_THREAD_DEFINE(thread_b, STACK_SIZE, thread_b_fn,
                NULL, NULL, NULL, PRIO_B, 0, 0);

K_THREAD_DEFINE(thread_c, STACK_SIZE, thread_c_fn,
                NULL, NULL, NULL, PRIO_C, 0, 0);

K_THREAD_DEFINE(thread_coop, STACK_SIZE, thread_coop_fn,
                NULL, NULL, NULL, PRIO_COOP, 0, 0);

int main(void)
{
    return 0;
}

