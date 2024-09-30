#include "updc_ca_utils.h"
#include <iostream>
#include <cstring>

UpdcCaUtils::UpdcCaUtils() {
    // Initialize the TEE context directly in the constructor
    TEEC_Result res = TEEC_InitializeContext(nullptr, &context_);
    if (res != TEEC_SUCCESS) {
        std::cerr << "Failed to initialize context: " << res << std::endl;
        // Handle initialization failure appropriately (e.g., throw an exception)
    }
    std::memset(&session_, 0, sizeof(session_));
}

UpdcCaUtils::~UpdcCaUtils() {
    closeSession();
}

TEEC_Result UpdcCaUtils::openSession() {
    TEEC_Operation operation;
    std::memset(&operation, 0, sizeof(operation));
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    TEEC_Result res = TEEC_OpenSession(&context_, &session_, &TA_CSR_UUID, 
                                       TEEC_LOGIN_PUBLIC, nullptr, &operation, nullptr);
    if (res != TEEC_SUCCESS) {
        std::cerr << "Failed to open session: " << res << std::endl;
    }
    return res;
}

TEEC_Result UpdcCaUtils::requestCsr(std::string &csr) {
    TEEC_Operation operation;
    std::memset(&operation, 0, sizeof(operation));
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    char csrBuffer[1024];
    std::memset(csrBuffer, 0, sizeof(csrBuffer));
    operation.params[0].tmpref.buffer = csrBuffer;
    operation.params[0].tmpref.size = sizeof(csrBuffer);

    TEEC_Result res = TEEC_InvokeCommand(&session_, TA_REQUEST_CSR_CMD, &operation, nullptr);
    if (res != TEEC_SUCCESS) {
        std::cerr << "Failed to request CSR: " << res << std::endl;
    } else {
        csr.assign(csrBuffer, operation.params[0].tmpref.size);
        std::cout << "CSR Received: " << csr << std::endl;
    }
    return res;
}

void UpdcCaUtils::closeSession() {
    if (session_.session_id != 0) {
        TEEC_CloseSession(&session_);
        session_.session_id = 0;
    }
    TEEC_FinalizeContext(&context_);
}
