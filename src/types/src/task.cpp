#include <assert.h>
#include <cstring>
#include <process.hpp>
#include <task.hpp>

Task::~Task(void)
{
    // Deconstructing Task
}

void Task::Run(void)
{
    // Base case Task::Run function
}

void Task::Terminate(void)
{
    // Terminate task
}

void Task::WaitForTermination(void)
{
    // Wait for task termination
}

TTaskRegisters* Task::GetRegs(void)
{
    return &registers;
}

// Same approach as CTasks
void Task::InitializeRegs(void)
{
    memset(&registers, 0, sizeof registers);

    registers.x0 = (u64)this; // pParam for TaskEntry()

    assert(pStack != 0);
    registers.sp = (u64)pStack + nStackSize;

    registers.x30 = (u64)&TaskEntry;

    u32 nFPCR;
    asm volatile("mrs %0, fpcr" : "=r"(nFPCR));
    registers.fpcr = nFPCR;
}

// Same approach as CTask
void Task::TaskEntry(void* pParam)
{
    Task* pThis = (Task*)pParam;
    assert(pThis != 0);

    pThis->Run();
}
