package com.example.updcclient;

import android.os.RemoteException;
import android.util.Log;
import java.util.ArrayList;
import vendor.harman.hardware.updc@1.0.IUpdc;
import vendor.harman.hardware.updc@1.0.Error;

public class UpdcClient {
    private static final String TAG = "UpdcClient";
    private IUpdc updcService;

    public UpdcClient(IUpdc updcService) {
        this.updcService = updcService;
    }

    // Generate UPDC CSR
    public void generateUpdcCsr() {
        try {
            // Create a container for the CSR response
            ArrayList<byte[]> csrResponse = new ArrayList<>();
            Error error = updcService.generateUpdcCsr(csrResponse);
            if (error == Error.SUCCESS && csrResponse.size() > 0) {
                Log.d(TAG, "CSR generated successfully: " + new String(csrResponse.get(0)));
            } else {
                Log.e(TAG, "Failed to generate CSR: " + error);
            }
        } catch (RemoteException e) {
            Log.e(TAG, "RemoteException occurred: ", e);
        }
    }

    // Provision UPDC Certificate
    public void provisionUpdcCert(byte[] cert) {
        try {
            Error error = updcService.provisionUpdcCert(cert);
            if (error == Error.SUCCESS) {
                Log.d(TAG, "Certificate provisioned successfully.");
            } else {
                Log.e(TAG, "Failed to provision certificate: " + error);
            }
        } catch (RemoteException e) {
            Log.e(TAG, "RemoteException occurred: ", e);
        }
    }

    // Get UPDC Certificate
    public void getUpdcCert() {
        try {
            ArrayList<byte[]> certResponse = new ArrayList<>();
            Error error = updcService.getUpdcCert(certResponse);
            if (error == Error.SUCCESS && certResponse.size() > 0) {
                Log.d(TAG, "Certificate retrieved successfully: " + new String(certResponse.get(0)));
            } else {
                Log.e(TAG, "Failed to retrieve certificate: " + error);
            }
        } catch (RemoteException e) {
            Log.e(TAG, "RemoteException occurred: ", e);
        }
    }
}
