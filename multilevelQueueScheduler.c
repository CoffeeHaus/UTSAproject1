#include <stdlib.h>

#include "multilevelQueueScheduler.h"
#undef min
int min( int x, int y );

static const int STEPS_TO_PROMOTION = 50;
static const int FOREGROUND_QUEUE_STEPS = 5;

/* createSchedule
 * input: none
 * output: a schedule
 *
 * Creates and return a schedule struct.
 */
schedule* createSchedule( ) {
    /* TODO: initialize data in schedule */
    struct schedule *newschedule = malloc (sizeof (struct schedule));    
    if(newschedule == NULL)
    {
        return NULL;
    }
    
    newschedule->foreQueue = createQueue();
    newschedule->backQueue = createQueue();
    newschedule->stepsSinceStart = 0;
    return newschedule; /* TODO: Replace with your return value */
}

/* isScheduleUnfinished
 * input: a schedule
 * output: bool (true or false)
 *
 * Check if there are any processes still in the queues.
 * Return TRUE if there is.  Otherwise false.
 */
bool isScheduleUnfinished( schedule *ps ) {
    /* TODO: check if there are any process still in a queue.  Return TRUE if there is. */
    if(!isEmpty(ps->foreQueue) && !isEmpty(ps->backQueue))
    {
        return true;
    }
    return false; /* TODO: Replace with your return value */
}

/* addNewProcessToSchedule
 * input: a schedule, a string, a priority
 * output: void
 *
 * Create a new process with the provided name and priority.
 * Add that process to the appropriate queue
 */
void addNewProcessToSchedule( schedule *ps, char *processName, priority p ) {
    /* TODO: complete this function.
    The function "initializeProcessData" in processSimulator.c will be useful in completing this. */
    printf("%s\n", processName);
    process * newprocess;
    processData * pData = initializeProcessData(processName);
    newprocess->Data =  pData;
    newprocess->name = processName;
    newprocess->FororBack = p;


    if (newprocess->FororBack  == FOREGROUND) { enqueue(ps->foreQueue, newprocess); }
    else {enqueue(ps->backQueue, newprocess);}


    //free( processName ); /* TODO: This is to prevent a memory leak but you should remove it once you create a process to put processName into */
}

/* runNextProcessInSchedule
 * input: a schedule
 * output: a string
 *
 * Use the schedule to determine the next process to run and for how many time steps.
 * Call "runProcess" to attempt to run the process.  You do not need to print anything.
 * You should return the string "runProcess" returns.  You do not need to use/modify this string in any way.
 */
char* runNextProcessInSchedule( schedule *ps ) {
    /* TODO: complete this function.
    The function "runProcess", "promoteProcess", "loadProcessData", and "freeProcessData"
    in processSimulator.c will be useful in completing this.
    You may want to write a helper function to handle promotion */
    char *ret = NULL;
    int numSteps = 0;
    process * proc = NULL;
    /* TODO: Delete the following printf once you get the infinite loop fixed */
    printf("IMPORTANT NOTE: There will be an intinite loop in runNextProcessInSchedule if you get isScheduleUnfinished and addNewProcessToSchedule working correctly\n"); 
    // TODO: Uncomment the code below to dequeue elements from the two Queues and break your code out of the infinite loop
    if( !isEmpty(ps->foreQueue) )
        proc = dequeue(ps->foreQueue);
    else if( !isEmpty(ps->backQueue) )
        proc = dequeue(ps->backQueue);
    
    
    /* your call to runProcess will look something like this: */
     bool b = runProcess( proc, &ret, &numSteps );
    
    return ret; /* TODO: be sure to store the value returned by runProcess in ret */
}

/* freeSchedule
 * input: a schedule
 * output: none
 *
 * Free all of the memory associated with the schedule.
 */
void freeSchedule( schedule *ps ) {
    /* TODO: free any data associated with the schedule as well as the schedule itself.
    the function "freeQueue" in queue.c will be useful in completing this. */
    if (ps != NULL)
    {
        freeQueue(ps->foreQueue);
        freeQueue(ps->foreQueue);
        free(ps);

    }
}

int min( int x, int y ){
    if( x<y )
        return x;
    return y;
}
