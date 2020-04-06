/**
 * Entry App.
 * This class is meant to be the entry point for process execution,
 * therefore, this process should create all other processes, for their
 * respective partitions
 */

#include <entry.hpp>
#include <test_app.hpp>

Entry::Entry(CLogger* logger)
    : Task(10, 10, 10, HARD, {"EntryApp"}, {"systemManagement"})
{
    this->logger = logger;
}

Entry::~Entry()
{
}

void Entry::Run(void)
{
    logger->Write(*getProcessName().x, LogNotice, "Entry App instantiated");
    logger->Write(*getProcessName().x, LogNotice, "Creating processes...");

    // Define process attributes
    PROCESS_ATTRIBUTE_TYPE flightManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        15000 * HZ,  10, new TestApp(logger, {"flightManagement"}),
        0x8000,      10, HARD,
        {"TestApp1"}};

    PROCESS_ATTRIBUTE_TYPE systemManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        15000 * HZ,  10, new TestApp(logger, {"systemManagement"}),
        0x8000,      10, HARD,
        {"TestApp2"}};

    PROCESS_ATTRIBUTE_TYPE IOProcessingProcess11 = PROCESS_ATTRIBUTE_TYPE{
        15000 * HZ,   10, new TestApp(logger, {"IOProcessing"}),
        0x8000,       10, HARD,
        {"TestApp31"}};

    PROCESS_ATTRIBUTE_TYPE IOProcessingProcess12 = PROCESS_ATTRIBUTE_TYPE{
        500 * HZ,     10, new TestApp(logger, {"IOProcessing"}),
        0x8000,       10, HARD,
        {"TestApp32"}};

    // Create the process
    PROCESS_ID_TYPE returnId1, returnId2, returnId31, returnId32;
    RETURN_CODE_TYPE returnCode1, returnCode2, returnCode31, returnCode32;
    CREATE_PROCESS(&flightManagementProcess, &returnId1, &returnCode1);
    CREATE_PROCESS(&systemManagementProcess, &returnId2, &returnCode2);
    CREATE_PROCESS(&IOProcessingProcess11, &returnId31, &returnCode31);
    CREATE_PROCESS(&IOProcessingProcess12, &returnId32, &returnCode32);

    if (returnCode1 == RETURN_CODE_TYPE::NO_ERROR && returnCode2 == RETURN_CODE_TYPE::NO_ERROR &&
        returnCode31 == RETURN_CODE_TYPE::NO_ERROR &&
        returnCode32 == RETURN_CODE_TYPE::NO_ERROR) {
        logger->Write(*getProcessName().x, LogNotice,
                      "All Processes was successfully created");
    }
    else {
        logger->Write(*getProcessName().x, LogNotice,
                      "Error %s occured, while creating processes");
    }
}