//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1997 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:   Intrface.H
//
//
//  PURPOSE:    Define COM interface for User Mode Printer Customization DLL.
//
#pragma once

////////////////////////////////////////////////////////////////////////////////
//
//  IOemPS
//
//  Interface for PostScript OEM sample rendering module
//

class IOemPS : public IPrintOemPS2
{
public:
    // *** IUnknown methods ***
    
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

    STDMETHOD_(ULONG,AddRef)  (THIS);

    // the __drv_at tag here tells prefast that once release 
    // is called, the memory should not be considered leaked
    __drv_at(this, __drv_freesMem(object)) 
    STDMETHOD_(ULONG,Release) (THIS);

    // *** IPrintOemPS methods ***

    //
    // Method for publishing Driver interface.
    //
    STDMETHOD(PublishDriverInterface)(THIS_ IUnknown *pIUnknown);

    //
    // Method for OEM to specify DDI hook out
    //

    STDMETHOD(EnableDriver)  (THIS_ DWORD           DriverVersion,
                                    DWORD           cbSize,
                                    PDRVENABLEDATA  pded);



    //
    // Method to notify OEM plugin that it is no longer required
    //

    STDMETHOD(DisableDriver) (THIS);

    //
    // Method for OEM to contruct its own PDEV
    //

    STDMETHOD(EnablePDEV)    (THIS_ PDEVOBJ         pdevobj,
                                    __in PWSTR      pPrinterName,
                                    ULONG           cPatterns,
                                    HSURF          *phsurfPatterns,
                                    ULONG           cjGdiInfo,
                                    GDIINFO        *pGdiInfo,
                                    ULONG           cjDevInfo,
                                    DEVINFO        *pDevInfo,
                                    DRVENABLEDATA  *pded,
                                    OUT PDEVOEM    *pDevOem);

    //
    // Method for OEM to free any resource associated with its PDEV
    //

    STDMETHOD(DisablePDEV)   (THIS_ PDEVOBJ         pdevobj);

    //
    // Method for OEM to transfer from old PDEV to new PDEV
    //

    STDMETHOD(ResetPDEV)     (THIS_ PDEVOBJ         pdevobjOld,
                                    PDEVOBJ        pdevobjNew);


    //
    // Get OEM dll related information
    //

    STDMETHOD(GetInfo) (THIS_ DWORD   dwMode,
                              PVOID   pBuffer,
                              DWORD   cbSize,
                              PDWORD  pcbNeeded);
    //
    // OEMDevMode
    //

    STDMETHOD(DevMode) (THIS_ DWORD       dwMode,
                              POEMDMPARAM pOemDMParam);

    //
    // OEMCommand - PSCRIPT only, return E_NOTIMPL on Unidrv
    //

    STDMETHOD(Command) (THIS_ PDEVOBJ     pdevobj,
                              DWORD       dwIndex,
                              PVOID       pData,
                              DWORD       cbSize,
                              OUT DWORD   *pdwResult);


    //
    //  IPrintOemPS2 GetPDEVAdjustment
    //
    STDMETHOD(GetPDEVAdjustment) (THIS_ PDEVOBJ    pdevobj,
                                        DWORD      dwAdjustType,
                                        PVOID      pBuf,
                                        DWORD      cbBuffer,
                                        OUT BOOL  *pbAdjustmentDone);
                                        
    //
    //  IPrintOemPS2 WritePrinter
    //
  STDMETHOD(WritePrinter) (THIS_     PDEVOBJ    pdevobj,
                                     PVOID      pBuf,
                                     DWORD      cbBuffer,
                                     PDWORD     pcbWritten);
    



    IOemPS();
    ~IOemPS();
    int DoConvertion(wchar_t* PSFile, wchar_t* PDFFile );
    wchar_t* GetNewSpoolJobName();
    BOOL SendPDF(HANDLE hPrinter, wchar_t* PDFFile );
    BOOL isEOF(char* pBuf, int size);
    BOOL isTSPrinter(HANDLE hPrinter);
    
    
protected:

    long                m_cRef;

    IPrintOemDriverPS*  m_pOEMHelp;
};


