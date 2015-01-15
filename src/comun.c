#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "computos.h"
#include "servidores.h"

/******************************************************************************/
/*                        Defines                                             */
/******************************************************************************/

// TASK 1
#define T1_PRIORITY 5
#define T1_COMP_TIME 10
#define T1_PERIOD 100

// TASK 2
#define T2_PRIORITY 3
#define T2_COMP_TIME 60
#define T2_PERIOD 200

// TASK 3
#define T3_PRIORITY 1
#define T3_COMP_TIME 30
#define T3_PERIOD 400


/******************************************************************************/
/*                        Global variables                                    */
/******************************************************************************/

pthread_t thr_t1;
pthread_t thr_t2;
pthread_t thr_t3;

void task1(void);
void task2(void);
void task3(void);

/*
 *  ======== main ========
 */
void main()
{
    pthread_attr_t thread_attr;
    /* preparar atributos por defecto */ 
    pthread_attr_init(&thread_attr);
    
    /* modificar atributos por defecto */ 
    pthread_attr_*(&thread_attr, SOME_ATRIBUTE_VALUE_PARAMETER);


    /* Create three independent tasks */
    Task_Params_init(&taskParams);
    taskParams.priority = 5;
    tsk1 = Task_create (task1, &taskParams, NULL);

    Task_Params_init(&taskParams);
    taskParams.priority = 3;
    tsk2 = Task_create (task2, &taskParams, NULL);

    Task_Params_init(&taskParams);
    taskParams.priority = 1;
    tsk3 = Task_create (task3, &taskParams, NULL);

    Crear_Servidores () ;

    BIOS_start();
}

/*
 *  ======== task1 ========
 */
void task1(void)
{

    UInt32 next, period = T1_PERIOD ;
    int d ;

    next = Clock_getTicks();

    for (;;) {

        CS (T1_COMP_TIME) ;
        S11 () ;

        next += period ;
        d = next - Clock_getTicks() ;
        if (d < 0) d = 0 ;
        Task_sleep(d);
    }
}

/*
 *  ======== task2 ========
 */
void task2(void)
{

    UInt32 next, period = T2_PERIOD ;
    int d ;

    next = Clock_getTicks();

    for (;;) {

        CS (T2_COMP_TIME) ;
        S21 () ;

        next += period ;
        d = next - Clock_getTicks() ;
        if (d < 0) d = 0 ;
        Task_sleep(d);
    }
}


/*
 *  ======== task3 ========
 */
void task3(void)
{

    UInt32 next, period = T3_PERIOD ;
    int d ;

    next = Clock_getTicks();

    for (;;) {

        S22 () ;
    	CS (T3_COMP_TIME) ;
    	S12 () ;

        next += period ;
        d = next - Clock_getTicks() ;
        if (d < 0) d = 0 ;
        Task_sleep(d);
    }
}


