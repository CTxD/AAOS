/*----------------------------------------------------------------*/
/*                                                                */
/* BUFFER constant and type definitions and management services   */
/*                                                                */
/*----------------------------------------------------------------*/

#ifndef APEX_BUFFER
#define APEX_BUFFER

#include "apex_process.hpp"
#include "apex_types.hpp"
#include <vector>

#define MAX_NUMBER_OF_BUFFERS SYSTEM_LIMIT_NUMBER_OF_BUFFERS

typedef NAME_TYPE BUFFER_NAME_TYPE;
typedef APEX_INTEGER BUFFER_ID_TYPE;

typedef struct {
    MESSAGE_RANGE_TYPE NB_MESSAGE;
    MESSAGE_RANGE_TYPE MAX_NB_MESSAGE;
    MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE;
    WAITING_RANGE_TYPE WAITING_PROCESSES;
} BUFFER_STATUS_TYPE;

typedef struct {
    BUFFER_NAME_TYPE bufferName;
    QUEUING_DISCIPLINE_TYPE queingDiscipline;
    BUFFER_STATUS_TYPE buffer;
} Buffer;

typedef std::vector<Buffer> BufferVector;
typedef struct {
    const char* partitionName;
    BufferVector buffers;
} PartitionBuffer;

class ApexBuffer {
private:
    static bool initialised;
    static std::vector<PartitionBuffer> partitionBuffers;

public:
    static void initialiseBuffers();
    static void CREATE_BUFFER(
        /*in */ BUFFER_NAME_TYPE BUFFER_NAME,
        /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
        /*in */ MESSAGE_RANGE_TYPE MAX_NB_MESSAGE,
        /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
        /*out*/ BUFFER_ID_TYPE* BUFFER_ID,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void SEND_BUFFER(
        /*in */ BUFFER_ID_TYPE BUFFER_ID,
        /*in */ MESSAGE_ADDR_TYPE MESSAGE_ADDR, /* by reference */
        /*in */ MESSAGE_SIZE_TYPE LENGTH,
        /*in */ SYSTEM_TIME_TYPE TIME_OUT,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void RECEIVE_BUFFER(
        /*in */ BUFFER_ID_TYPE BUFFER_ID,
        /*in */ SYSTEM_TIME_TYPE TIME_OUT,
        /*out*/ MESSAGE_ADDR_TYPE MESSAGE_ADDR,
        /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void GET_BUFFER_ID(
        /*in */ BUFFER_NAME_TYPE BUFFER_NAME,
        /*out*/ BUFFER_ID_TYPE* BUFFER_ID,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void GET_BUFFER_STATUS(
        /*in */ BUFFER_ID_TYPE BUFFER_ID,
        /*out*/ BUFFER_STATUS_TYPE* BUFFER_STATUS,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);
};

#endif
