#ifndef UPDC_CA_UTILS_H
#define UPDC_CA_UTILS_H

#include <tee_client_api.h>
#include <string>

class UpdcCaUtils {
public:
    UpdcCaUtils();
    ~UpdcCaUtils();

    // Open session with TA
    TEEC_Result openSession();

    // Request a CSR from the TA and return it as a string
    TEEC_Result requestCsr(std::string &csr);

    // Close session and finalize context
    void closeSession();

private:
    TEEC_Context context_;
    TEEC_Session session_;

    // UUID for the TA (Encapsulated and constant for all instances)
    static constexpr TEEC_UUID TA_CSR_UUID = { 
        0x12345678, 0x1234, 0x1234, 
        { 0x12, 0x34, 0x12, 0x34, 0x12, 0x34, 0x12, 0x34 }
    };

    // Command ID for requesting a CSR
    static constexpr uint32_t TA_REQUEST_CSR_CMD = 0x00000001;
};

#endif // UPDC_CA_UTILS_H
