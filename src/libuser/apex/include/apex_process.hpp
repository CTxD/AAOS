/*----------------------------------------------------------------*/
/*                                                                */
/* PROCESS constant and type definitions and management services  */
/*                                                                */
/*----------------------------------------------------------------*/

#ifndef APEX_PROCESS
#define APEX_PROCESS

#include "apex_types.hpp"

#define MAX_NUMBER_OF_PROCESSES SYSTEM_LIMIT_NUMBER_OF_PROCESSES

#define MIN_PRIORITY_VALUE 1

#define MAX_PRIORITY_VALUE 63

#define MAX_LOCK_LEVEL 16

typedef NAME_TYPE PROCESS_NAME_TYPE;

typedef APEX_INTEGER PROCESS_ID_TYPE;

#define NULL_PROCESS_ID 0

#define MAIN_PROCESS_ID -1

typedef APEX_INTEGER PROCESS_INDEX_TYPE;

typedef APEX_INTEGER LOCK_LEVEL_TYPE;

typedef APEX_UNSIGNED STACK_SIZE_TYPE;

typedef APEX_INTEGER WAITING_RANGE_TYPE;

typedef APEX_INTEGER PRIORITY_TYPE;

typedef enum {
    DORMANT = 0,
    READY = 1,
    RUNNING = 2,
    WAITING = 3,
    FAULTED = 4
} PROCESS_STATE_TYPE;

typedef enum { SOFT = 0, HARD = 1 } DEADLINE_TYPE;

typedef struct {
    SYSTEM_TIME_TYPE PERIOD;
    SYSTEM_TIME_TYPE TIME_CAPACITY;
    void* ENTRY_POINT; // By using void* it can be either a task, or an address.
    STACK_SIZE_TYPE STACK_SIZE;
    PRIORITY_TYPE BASE_PRIORITY;
    DEADLINE_TYPE DEADLINE;
    PROCESS_NAME_TYPE NAME;
    PROCESS_ID_TYPE ID;
} PROCESS_ATTRIBUTE_TYPE;

typedef struct {
    SYSTEM_TIME_TYPE DEADLINE_TIME;
    PRIORITY_TYPE CURRENT_PRIORITY;
    PROCESS_STATE_TYPE PROCESS_STATE;
    PROCESS_ATTRIBUTE_TYPE ATTRIBUTES;
} PROCESS_STATUS_TYPE;

extern void CREATE_PROCESS(
    /*in */ PROCESS_ATTRIBUTE_TYPE* ATTRIBUTES,
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void SET_PRIORITY(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ PRIORITY_TYPE PRIORITY,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void SUSPEND_SELF(
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void SUSPEND(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void RESUME(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void STOP_SELF();

extern void STOP(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void START(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void DELAYED_START(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ SYSTEM_TIME_TYPE DELAY_TIME,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void LOCK_PREEMPTION(
    /*out*/ LOCK_LEVEL_TYPE* LOCK_LEVEL,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void UNLOCK_PREEMPTION(
    /*out*/ LOCK_LEVEL_TYPE* LOCK_LEVEL,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_MY_ID(
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_PROCESS_ID(
    /*in */ PROCESS_NAME_TYPE PROCESS_NAME,
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_PROCESS_STATUS(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ PROCESS_STATUS_TYPE* PROCESS_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void INITIALIZE_PROCESS_CORE_AFFINITY(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ PROCESSOR_CORE_ID_TYPE PROCESSOR_CORE_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_MY_PROCESSOR_CORE_ID(
    /*in */ PROCESSOR_CORE_ID_TYPE PROCESSOR_CORE_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_MY_INDEX(
    /*in */ PROCESS_INDEX_TYPE PROCESS_INDEX,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

#endif
