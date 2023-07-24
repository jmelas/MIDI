/************************************************************************************
Copyright 2023 Association of Musical Electronics Industry
Copyright 2023 Microsoft
Driver source code developed by AmeNote. Some components Copyright 2023 AmeNote Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
************************************************************************************/
/*++

Module Name:

    device.c - Device handling events for example driver.

Abstract:

   This file contains the device entry points and callbacks.
    
Environment:

    Kernel-mode Driver Framework

--*/

#include "driver.h"
#include "device.tmh"

#include "Common.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, CopyRegistrySettingsPath)
#pragma alloc_text (PAGE, USBUMPDriverCreateDevice)
#pragma alloc_text (PAGE, USBUMPDriverEvtDevicePrepareHardware)
#pragma alloc_text (PAGE, USBUMPDriverEvtDeviceD0Entry)
#pragma alloc_text (PAGE, USBUMPDriverEvtDeviceD0Exit)
#pragma alloc_text (PAGE, USBUMPDriverSelectInterface)
#pragma alloc_text (PAGE, USBUMPDriverEnumeratePipes)
#pragma alloc_text (NONPAGE, USBUMPDriverEvtReadComplete)
#pragma alloc_text (NONPAGE, USBUMPDriverEvtReadFailed)
#pragma alloc_text (NONPAGE, USBUMPDriverFillReadQueue)
#pragma alloc_text (NONPAGE, USBUMPDriverEvtIoRead)
#pragma alloc_text (NONPAGE, USBUMPDriverEvtIoWrite)
#pragma alloc_text (NONPAGE, USBUMPDriverEvtRequestWriteCompletionRoutineDelete)
#pragma alloc_text (NONPAGE, USBUMPDriverEvtRequestWriteCompletionRoutine)
#pragma alloc_text (NONPAGE, USBUMPDriverSendToUSB)
#endif

UNICODE_STRING g_RegistryPath = { 0 };      // This is used to store the registry settings path for the driver

NTSTATUS
CopyRegistrySettingsPath(
    _In_ PUNICODE_STRING RegistryPath
)
/*++

Routine Description:

Copies the following registry path to a global variable.

\REGISTRY\MACHINE\SYSTEM\ControlSetxxx\Services\<driver>\Parameters

Arguments:

RegistryPath - Registry path passed to DriverEntry

Returns:

NTSTATUS - SUCCESS if able to configure the framework

--*/

{
    // Initializing the unicode string, so that if it is not allocated it will not be deallocated too.
    RtlInitUnicodeString(&g_RegistryPath, nullptr);

    g_RegistryPath.MaximumLength = RegistryPath->Length + sizeof(WCHAR);

    g_RegistryPath.Buffer = (PWCH)ExAllocatePool2(POOL_FLAG_PAGED, g_RegistryPath.MaximumLength, USBUMP_POOLTAG);

    if (g_RegistryPath.Buffer == nullptr)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // ExAllocatePool2 zeros memory.

    RtlAppendUnicodeToString(&g_RegistryPath, RegistryPath->Buffer);

    return STATUS_SUCCESS;
}

NTSTATUS
USBUMPDriverCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
/*++

Routine Description:

    Worker routine called to create a device and its software resources.

Arguments:

    DeviceInit - Pointer to an opaque init structure. Memory for this
                    structure will be freed by the framework when the WdfDeviceCreate
                    succeeds. So don't access the structure after that point.

Return Value:

    NTSTATUS

--*/
{
    WDF_PNPPOWER_EVENT_CALLBACKS pnpPowerCallbacks;
    WDF_OBJECT_ATTRIBUTES   deviceAttributes;
    PDEVICE_CONTEXT deviceContext;
    WDFDEVICE device;
    NTSTATUS status;
    WDF_OBJECT_ATTRIBUTES memoryAttributes;

    PAGED_CODE();

    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpPowerCallbacks);
    pnpPowerCallbacks.EvtDevicePrepareHardware = USBUMPDriverEvtDevicePrepareHardware;
    pnpPowerCallbacks.EvtDeviceD0Entry = USBUMPDriverEvtDeviceD0Entry;
    pnpPowerCallbacks.EvtDeviceD0Exit = USBUMPDriverEvtDeviceD0Exit;

    WdfDeviceInitSetPnpPowerEventCallbacks(DeviceInit, &pnpPowerCallbacks);

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, DEVICE_CONTEXT);

    status = WdfDeviceCreate(&DeviceInit, &deviceAttributes, &device);

    if (NT_SUCCESS(status)) {
        //
        // Get a pointer to the device context structure that we just associated
        // with the device object. We define this structure in the device.h
        // header file. DeviceGetContext is an inline function generated by
        // using the WDF_DECLARE_CONTEXT_TYPE_WITH_NAME macro in device.h.
        // This function will do the type checking and return the device context.
        // If you pass a wrong object handle it will return NULL and assert if
        // run under framework verifier mode.
        //
        deviceContext = DeviceGetContext(device);

        //
        // Initialize the context.
        //


        //
        // Create a device interface so that applications can find and talk
        // to us.
        //
        status = WdfDeviceCreateDeviceInterface(
            device,
            &GUID_DEVINTERFACE_USBUMPDriver,
            NULL // ReferenceString
            );

        if (NT_SUCCESS(status)) {
            //
            // Initialize the I/O Package and any Queues
            //
            status = USBUMPDriverQueueInitialize(device);
        }

        if (NT_SUCCESS(status)) {
            //
            // Create memory for Ring buffer
            //
            WDF_OBJECT_ATTRIBUTES_INIT(&memoryAttributes);
            memoryAttributes.ParentObject = device;
            status = WdfMemoryCreate(
                &memoryAttributes,
                NonPagedPool,
                USBUMP_POOLTAG,
                USBUMPDRIVER_RING_BUF_SIZE * sizeof(UINT32),
                &deviceContext->ReadRingBuf.RingBufMemory,
                NULL
            );
            deviceContext->ReadRingBuf.ringBufSize = USBUMPDRIVER_RING_BUF_SIZE;
            if (!NT_SUCCESS(status))
            {
                TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                    "WdfMemoryCreate failed for ring buffer.\n");
                return status;
            }
        }
    }

    return status;
}

NTSTATUS
USBUMPDriverEvtDevicePrepareHardware(
    _In_ WDFDEVICE Device,
    _In_ WDFCMRESLIST ResourceList,
    _In_ WDFCMRESLIST ResourceListTranslated
    )
/*++

Routine Description:

    In this callback, the driver does whatever is necessary to make the
    hardware ready to use.  In the case of a USB device, this involves
    reading and selecting descriptors.

Arguments:

    Device - handle to a device

Return Value:

    NT status value

--*/
{
    NTSTATUS status;
    PDEVICE_CONTEXT pDeviceContext;
    WDF_USB_DEVICE_CREATE_CONFIG createParams;
    WDF_USB_DEVICE_SELECT_CONFIG_PARAMS configParams;

    UNREFERENCED_PARAMETER(ResourceList);
    UNREFERENCED_PARAMETER(ResourceListTranslated);

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    status = STATUS_SUCCESS;
    pDeviceContext = DeviceGetContext(Device);

    //
    // Create a USB device handle so that we can communicate with the
    // underlying USB stack. The WDFUSBDEVICE handle is used to query,
    // configure, and manage all aspects of the USB device.
    // These aspects include device properties, bus properties,
    // and I/O creation and synchronization. We only create the device the first time
    // PrepareHardware is called. If the device is restarted by pnp manager
    // for resource rebalance, we will use the same device handle but then select
    // the interfaces again because the USB stack could reconfigure the device on
    // restart.
    //
    if (pDeviceContext->UsbDevice == NULL) {

        //
        // Specifying a client contract version of 602 enables us to query for
        // and use the new capabilities of the USB driver stack for Windows 8.
        // It also implies that we conform to rules mentioned in MSDN
        // documentation for WdfUsbTargetDeviceCreateWithParameters.
        //
        WDF_USB_DEVICE_CREATE_CONFIG_INIT(&createParams,
                                         USBD_CLIENT_CONTRACT_VERSION_602
                                         );

        status = WdfUsbTargetDeviceCreateWithParameters(Device,
                                                    &createParams,
                                                    WDF_NO_OBJECT_ATTRIBUTES,
                                                    &pDeviceContext->UsbDevice
                                                    );

        if (!NT_SUCCESS(status)) {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                        "WdfUsbTargetDeviceCreateWithParameters failed 0x%x", status);
            return status;
        }
    }

    //
    // Use helper routine to parse descriptors and select interface
    //
    status = USBUMPDriverSelectInterface(Device);
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "USBUMPDriverSelectInterface failed 0x%x", status);
        return status;
    }

    //
    // Use helper routine to Enumerate USB pipes for use
    //
    status = USBUMPDriverEnumeratePipes(Device);

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}

NTSTATUS USBUMPDriverEvtDeviceD0Entry(
    __in  WDFDEVICE Device,
    __in  WDF_POWER_DEVICE_STATE PreviousState
)
/*++

Routine Description:

    In this callback, the framework calls this function when device enters its
    working (D0) state. Occurs when:
        - device enumerated
        - system and all devices return to working state after low power state
        - device returns to working state after it was in low power state
        - Plug and Play manager redistributed system's hardware resources
    For this driver, it will start up the Io Target associated with continuous read.

Arguments:

    Device - handle to a device
    PreviousState - previous state of device

Return Value:

    NT status value

--*/
{
    UNREFERENCED_PARAMETER(PreviousState);

    PDEVICE_CONTEXT  pDeviceContext;

    NTSTATUS status;

    PAGED_CODE();

    pDeviceContext = DeviceGetContext(Device);


    status = WdfIoTargetStart(WdfUsbTargetPipeGetIoTarget(pDeviceContext->MidiInPipe));

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "%!FUNC! Could not start interrupt pipe failed 0x%x", status);
    }

    return status;
}

NTSTATUS USBUMPDriverEvtDeviceD0Exit(
    __in  WDFDEVICE Device,
    __in  WDF_POWER_DEVICE_STATE TargetState
)
/*++

Routine Description:

    In this callback, the framework calls this function when device enters its
    working (D0) state. Occurs when:
        - device enumerated
        - system and all devices return to working state after low power state
        - device returns to working state after it was in low power state
        - Plug and Play manager redistributed system's hardware resources
    For this driver, it will start up the Io Target associated with continuous read.

Arguments:

    Device - handle to a device
    PreviousState - previous state of device

Return Value:

    NT status value

--*/
{
    UNREFERENCED_PARAMETER(TargetState);

    PDEVICE_CONTEXT  pDeviceContext;

    PAGED_CODE();

    pDeviceContext = DeviceGetContext(Device);


    WdfIoTargetStop(
        WdfUsbTargetPipeGetIoTarget(pDeviceContext->MidiInPipe),
        WdfIoTargetCancelSentIo
    );

    return STATUS_SUCCESS;
}


    NTSTATUS status;
NTSTATUS
USBUMPDriverSelectInterface(
    _In_ WDFDEVICE    Device
)
/*++

Routine Description:

    Helper routine to parse descriptors for driver and to select
    USB interface. Routine will determine if there is an Alternate
    setting for MIDI Streaming and select it, otherwise default
    to Alt Setting 0.

Arguments:

    Device - handle to a device

Return Value:

    NT status value

*/
{
    NTSTATUS                                status;
    PDEVICE_CONTEXT                         pDeviceContext;
    WDF_USB_DEVICE_INFORMATION              deviceInfo;
    ULONG                                   waitWakeEnable = 0;
    USB_DEVICE_DESCRIPTOR                   deviceDescriptor;
    PUSB_CONFIGURATION_DESCRIPTOR           pConfigurationDescriptor = NULL;
    USHORT                                  configurationDescriptorSize = 0;
    WDF_OBJECT_ATTRIBUTES                   deviceConfigAttrib;
    UCHAR                                   numInterfaces;
    USB_INTERFACE_DESCRIPTOR                interfaceDescriptor;
    UCHAR                                   numberConfiguredPipes;
    WDFUSBPIPE                              pipe;
    WDF_USB_PIPE_INFORMATION                pipeInfo;
    PWDF_USB_INTERFACE_SETTING_PAIR         pSettingPairs = NULL;
    WDF_USB_DEVICE_SELECT_CONFIG_PARAMS     configParams;
    WDF_OBJECT_ATTRIBUTES                   objectAttributes;
    PUSB_STRING_DESCRIPTOR                  pTempBuffer = NULL;
    WDF_REQUEST_SEND_OPTIONS                reqOptions;
    USHORT                                  numChars = 0;

    pDeviceContext = DeviceGetContext(Device);

    //
    // Retrieve USBD version information, port driver capabilites and device
    // capabilites such as speed, power, etc.  
    //
    WDF_USB_DEVICE_INFORMATION_INIT(&deviceInfo);

    status = WdfUsbTargetDeviceRetrieveInformation(
        pDeviceContext->UsbDevice,
        &deviceInfo);
    if (NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "IsDeviceHighSpeed: %s\n",
            (deviceInfo.Traits & WDF_USB_DEVICE_TRAIT_AT_HIGH_SPEED) ? "TRUE" : "FALSE");
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
            "IsDeviceSelfPowered: %s\n",
            (deviceInfo.Traits & WDF_USB_DEVICE_TRAIT_SELF_POWERED) ? "TRUE" : "FALSE");

        waitWakeEnable = deviceInfo.Traits &
            WDF_USB_DEVICE_TRAIT_REMOTE_WAKE_CAPABLE;

        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
            "IsDeviceRemoteWakeable: %s\n",
            waitWakeEnable ? "TRUE" : "FALSE");

        //
        // Save these for use later.
        //
        pDeviceContext->UsbDeviceTraits = deviceInfo.Traits;
    }
    else {
        pDeviceContext->UsbDeviceTraits = 0;
    }


    //
    // Get device descriptor information
    // 
    WdfUsbTargetDeviceGetDeviceDescriptor(
        pDeviceContext->UsbDevice,
        &deviceDescriptor);

    if (deviceDescriptor.bLength)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
            "Fetched device descriptor indicating:\n"
            "  bDeviceClass: 0x%x, bDeviceSubClass: 0x%x, bDeviceProtocol 0x%x\n"
            "  idVendor: 0x%04x, idProduct: 0x%04x\n"
            "  bNumConfigurations: %d\n",
            deviceDescriptor.bDeviceClass, deviceDescriptor.bDeviceSubClass, deviceDescriptor.bDeviceProtocol,
            deviceDescriptor.idVendor, deviceDescriptor.idProduct,
            deviceDescriptor.bNumConfigurations);

        /*
        * Device Descriptor information to consider to capture:
        *   idVendor
        *   idProduct
        *   Manufacture String
        *   Serial number String
        *   Number of configurations
        */
    }
    else {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error getting device descriptor.\n");
    }

    //
    // Get Config Descriptor
    //

    status = WdfUsbTargetDeviceRetrieveConfigDescriptor(
        pDeviceContext->UsbDevice,
        NULL,
        &configurationDescriptorSize
    );
    if (status != STATUS_BUFFER_TOO_SMALL)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Configuration Descriptor Error fetching size.\n");
        return(status);
    }

    WDF_OBJECT_ATTRIBUTES_INIT(&deviceConfigAttrib);
    deviceConfigAttrib.ParentObject = pDeviceContext->UsbDevice;
    status = WdfMemoryCreate(
        &deviceConfigAttrib,
        NonPagedPool,
        USBUMP_POOLTAG,
        configurationDescriptorSize,
        &pDeviceContext->DeviceConfigDescriptorMemory,
        (PVOID*)&pConfigurationDescriptor
    );
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error allocating memory for configuration descriptor.\n");
        return(status);
    }

    // Load configuration descriptor
    status = WdfUsbTargetDeviceRetrieveConfigDescriptor(
        pDeviceContext->UsbDevice,
        pConfigurationDescriptor,
        &configurationDescriptorSize
    );
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error loading configuration descriptor.\n");
        return(status);
    }

    //
    // Get other useful Driver descriptor information
    // 
    // Get Serial Number string as not a current simple property to get
    if (deviceDescriptor.iSerialNumber)
    {
        WDF_REQUEST_SEND_OPTIONS_INIT(&reqOptions, WDF_REQUEST_SEND_OPTION_SYNCHRONOUS);
        WDF_REQUEST_SEND_OPTIONS_SET_TIMEOUT(&reqOptions, WDF_REL_TIMEOUT_IN_SEC(USB_REQ_TIMEOUT_SEC));

        status = WdfUsbTargetDeviceQueryString(
            pDeviceContext->UsbDevice,
            NULL,
            &reqOptions,
            NULL,
            &numChars,
            deviceDescriptor.iSerialNumber,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
        );
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error getting Serial Number string size.\n");
            return(status);
        }

        WDF_OBJECT_ATTRIBUTES_INIT(&deviceConfigAttrib);
        deviceConfigAttrib.ParentObject = pDeviceContext->UsbDevice;
        status = WdfMemoryCreate(
            &deviceConfigAttrib,
            PagedPool,
            USBUMP_POOLTAG,
            (size_t)((numChars + 1) * sizeof(WCHAR)),
            &pDeviceContext->DeviceSNMemory,
            (PVOID*)&pTempBuffer
        );
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error allocating memory for Serial Number.\n");
            return(status);
        }
        RtlZeroMemory(pTempBuffer, (size_t)((numChars + 1) * sizeof(WCHAR)));
        status = WdfUsbTargetDeviceQueryString(
            pDeviceContext->UsbDevice,
            NULL,
            &reqOptions,
            (PUSHORT)pTempBuffer,
            &numChars,
            deviceDescriptor.iSerialNumber,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
        );
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error getting Serial Number string.\n");
            return(status);
        }
    }

    // Device manufacturer (as DevicePropertyManufacturer is driver manufacturer)
    if (deviceDescriptor.iManufacturer)
    {
        WDF_REQUEST_SEND_OPTIONS_INIT(&reqOptions, WDF_REQUEST_SEND_OPTION_SYNCHRONOUS);
        WDF_REQUEST_SEND_OPTIONS_SET_TIMEOUT(&reqOptions, WDF_REL_TIMEOUT_IN_SEC(USB_REQ_TIMEOUT_SEC));

        status = WdfUsbTargetDeviceQueryString(
            pDeviceContext->UsbDevice,
            NULL,
            &reqOptions,
            NULL,
            &numChars,
            deviceDescriptor.iManufacturer,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
        );
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error getting Manufacturer string size.\n");
            return(status);
        }

        WDF_OBJECT_ATTRIBUTES_INIT(&deviceConfigAttrib);
        deviceConfigAttrib.ParentObject = pDeviceContext->UsbDevice;
        status = WdfMemoryCreate(
            &deviceConfigAttrib,
            PagedPool,
            USBUMP_POOLTAG,
            (size_t)((numChars + 1) * sizeof(WCHAR)),
            &pDeviceContext->DeviceManfMemory,
            (PVOID*)&pTempBuffer
        );
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error allocating memory for Manufacturer.\n");
            return(status);
        }
        RtlZeroMemory(pTempBuffer, (size_t)((numChars + 1) * sizeof(WCHAR)));
        status = WdfUsbTargetDeviceQueryString(
            pDeviceContext->UsbDevice,
            NULL,
            &reqOptions,
            (PUSHORT)pTempBuffer,
            &numChars,
            deviceDescriptor.iManufacturer,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
        );
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error getting Manufacturer string.\n");
            return(status);
        }
    }

    // Device name
    WDF_OBJECT_ATTRIBUTES_INIT(&objectAttributes);
    objectAttributes.ParentObject = Device;
    status = WdfDeviceAllocAndQueryProperty(Device,
        DevicePropertyFriendlyName,
        NonPagedPoolNx,
        &objectAttributes,
        &pDeviceContext->DeviceNameMemory);
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Error getting Device Name string.\n");
        return(status);
    }

    //
    // Select target interfaces
    //
    numInterfaces = WdfUsbTargetDeviceGetNumInterfaces(pDeviceContext->UsbDevice);
    // Setup store for setting pairs for use later
    if (numInterfaces >= 2)
    {
        pSettingPairs = (PWDF_USB_INTERFACE_SETTING_PAIR)ExAllocatePool2(
            POOL_FLAG_PAGED,
            sizeof(WDF_USB_INTERFACE_SETTING_PAIR) * numInterfaces,
            USBUMP_POOLTAG
        );
    }
    // Confirm memory declared properly
    if (!pSettingPairs)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "Insufficient Resources\n");
        return(STATUS_INSUFFICIENT_RESOURCES);
    }

    // We expect at least two interfaces (and only currently support two)
    // an Audio Control interface and the MIDI interface
    if (numInterfaces < 2)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "Number of interfaces, %d, less than expected.\n", numInterfaces);
        status = STATUS_SEVERITY_ERROR;
        goto SelectExit;
    }

    // Load and configure pipes for first interface which should be the control interface
    pDeviceContext->UsbControlInterface = WdfUsbTargetDeviceGetInterface(
        pDeviceContext->UsbDevice,
        0
    );

    // Check that is control interface
    WdfUsbInterfaceGetDescriptor(
        pDeviceContext->UsbControlInterface,
        0,
        &interfaceDescriptor
    );
    if (interfaceDescriptor.bInterfaceClass != 1 /*AUDIO*/
        || interfaceDescriptor.bInterfaceSubClass != 1 /*AUDIO_CONTROL*/)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "Device detected does not have AUDIO_CONTROL interface as expected\n");
        status = STATUS_SEVERITY_ERROR;
        goto SelectExit;
    }

    // Setup setting pairs for control interface
    pSettingPairs[0].UsbInterface = pDeviceContext->UsbControlInterface;
    pSettingPairs[0].SettingIndex = 0;

    // Check that next interface is MIDI Streaming Interface
    pDeviceContext->UsbMIDIStreamingInterface = WdfUsbTargetDeviceGetInterface(
        pDeviceContext->UsbDevice,
        1
    );
    // First look if an alternate interface available
    WdfUsbInterfaceGetDescriptor(
        pDeviceContext->UsbMIDIStreamingInterface,
        1,  //alternate interface 1 - see USB Device Class Definition for MIDI Devices, Version 2.0 - Section 3.1
        &interfaceDescriptor
    );
    // If alternate interface 1 does not exist, then the length will be null
    if (interfaceDescriptor.bLength)
    {
        if (interfaceDescriptor.bInterfaceClass != 1 /*AUDIO*/
            || interfaceDescriptor.bInterfaceSubClass != 3 /*MIDI STREAMING*/
            || interfaceDescriptor.bInterfaceProtocol != 0) /*UNUSED*/
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                "Device Class/SubClass/Protocol not 1/3/0 as expected.\n");
            status = STATUS_SEVERITY_ERROR;
            goto SelectExit;
        }
        pDeviceContext->UsbMIDIStreamingAlt = 1;    // store that alternate interface
    }
    else
    {
        // As no additional alternate interface, work to select default 0
        WdfUsbInterfaceGetDescriptor(
            pDeviceContext->UsbMIDIStreamingInterface,
            0, //alternate interface 0, default - see USB Device Class Definition for MIDI Devices
            &interfaceDescriptor
        );
        if (!interfaceDescriptor.bLength /*error fetching descriptor*/
            || interfaceDescriptor.bInterfaceClass != 1 /*AUDIO*/
            || interfaceDescriptor.bInterfaceSubClass != 3 /*MIDI STREAMING*/
            || interfaceDescriptor.bInterfaceProtocol != 0) /*UNUSED*/
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                "Device Class/SubClass/Protocol not 1/3/0 as expected.\n");
            status = STATUS_SEVERITY_ERROR;
            goto SelectExit;
        }
        pDeviceContext->UsbMIDIStreamingAlt = 0;    // store that original interface
    }
    // Setup settings pairs for MIDI streaming interface
    pSettingPairs[1].UsbInterface = pDeviceContext->UsbMIDIStreamingInterface;
    pSettingPairs[1].SettingIndex = pDeviceContext->UsbMIDIStreamingAlt;

    // Prepare to select interface
    WDF_USB_DEVICE_SELECT_CONFIG_PARAMS_INIT_MULTIPLE_INTERFACES(
        &configParams,
        numInterfaces,
        pSettingPairs
    );

    // Select the interfaces
    status = WdfUsbTargetDeviceSelectConfig(
        pDeviceContext->UsbDevice,
        WDF_NO_OBJECT_ATTRIBUTES,
        &configParams
    );
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "Error selecting USB Interfaces.\n");
        goto SelectExit;
    }

SelectExit:
    if (pSettingPairs)
    {
        ExFreePoolWithTag(pSettingPairs, USBUMP_POOLTAG);
    }

    return status;
}

NTSTATUS
USBUMPDriverEnumeratePipes(
    _In_ WDFDEVICE    Device
)
/*++

Routine Description:

    Helper routine to enumerate pipes for use by driver. Also
    configures continuous reader to manage reading USB Bulk or
    Interrupt from the connected device.

Arguments:

    Device - handle to a device

Return Value:

    NT status value

*/
{
    NTSTATUS                                status;
    PDEVICE_CONTEXT                         pDeviceContext;
    UCHAR                                   numberConfiguredPipes;
    WDFUSBPIPE                              pipe;
    WDF_USB_PIPE_INFORMATION                pipeInfo;
    PWDF_USB_INTERFACE_SETTING_PAIR         pSettingPairs = NULL;
    WDF_USB_CONTINUOUS_READER_CONFIG        readerConfig;

    pDeviceContext = DeviceGetContext(Device);

    //
    // Enumerate Pipes
    //
    numberConfiguredPipes = WdfUsbInterfaceGetNumConfiguredPipes(
        pDeviceContext->UsbMIDIStreamingInterface
    );
    if (!numberConfiguredPipes)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "No configured endpoints for MIDI streaming discovered.\n");
        return(STATUS_SEVERITY_ERROR);
    }
    // First make sure past settings for pipes cleared
    pDeviceContext->MidiInPipe = NULL;
    pDeviceContext->MidiOutPipe = NULL;
    // Now look for In and Out Pipes
    for (UCHAR count = 0; count < numberConfiguredPipes; count++)
    {
        WDF_USB_PIPE_INFORMATION_INIT(&pipeInfo);
        pipe = WdfUsbInterfaceGetConfiguredPipe(
            pDeviceContext->UsbMIDIStreamingInterface,
            count,
            &pipeInfo
        );
        if (WdfUsbTargetPipeIsInEndpoint(pipe))
        {
            pDeviceContext->MidiInPipe = pipe;
            pDeviceContext->MidiInPipeType = pipeInfo.PipeType;
            pDeviceContext->MidiInMaxSize = pipeInfo.MaximumPacketSize;
        }
        else if (WdfUsbTargetPipeIsOutEndpoint(pipe))
        {
            pDeviceContext->MidiOutPipe = pipe;
            pDeviceContext->MidiOutPipeType = pipeInfo.PipeType;
            pDeviceContext->MidiOutMaxSize = pipeInfo.MaximumPacketSize;
        }
    }
    // At least one of the endpoints needs to be found
    if (!pDeviceContext->MidiInPipe && !pDeviceContext->MidiOutPipe)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "Neither In or Out Endpoint discovered for MIDI Streaming.\n");
        return(STATUS_SEVERITY_ERROR);
    }

    //
    // Configure continuous reader
    //
    if (pDeviceContext->MidiInPipe) // only if there is an In endpoint
    {
        WDF_USB_CONTINUOUS_READER_CONFIG_INIT(
            &readerConfig,
            USBUMPDriverEvtReadComplete,
            pDeviceContext,
            pDeviceContext->MidiInMaxSize);

        readerConfig.EvtUsbTargetPipeReadersFailed = USBUMPDriverEvtReadFailed;

        status = WdfUsbTargetPipeConfigContinuousReader(
            pDeviceContext->MidiInPipe,
            &readerConfig);

        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                "%!FUNC! WdfUsbTargetPipeConfigContinuousReader failed 0x%x", status);

            return status;
        }
    }
}

VOID USBUMPDriverEvtReadComplete(
    _In_    WDFUSBPIPE Pipe,
    _In_    WDFMEMORY  Buffer,
    _In_    size_t     NumBytesTransferred,
    _In_    WDFCONTEXT Context
)
/*++
Routine Description:

    In this callback for the continuous reader, the data received from the device
    and delivered to streaming interface.

Arguments:

    Pipe - the USB data pipe
    Buffer - the continuous reader provided buffer with transferred data
    NumBytesTransferred - the number of bytes transferred in Buffer
    Context - the provided Device Context

Return Value:

    NONE

--*/
{
    PDEVICE_CONTEXT         pDeviceContext;
    PUCHAR                  pReceivedBuffer;
    NTSTATUS                status;
    ULONG                   size;
    MIDI_CIN_Type           codeIndex;
    WDF_OBJECT_ATTRIBUTES   attributes;
    WDFMEMORY               workingBuffer = NULL;
    size_t                  workingBufferSize;
    size_t                  workingBufferIndex;
    PUCHAR                  pWorkingBuffer;

    pDeviceContext = (PDEVICE_CONTEXT)Context;

    if (NumBytesTransferred)
    {
        pReceivedBuffer = (PUCHAR)WdfMemoryGetBuffer(Buffer, NULL);

        // Confirm that there were bytes transferred
        if (NumBytesTransferred)
        {
            if (NumBytesTransferred % sizeof(UINT32))
            {
                status = STATUS_SEVERITY_WARNING;
                TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                    "Warning, data received from USB device invalid size and will be dropped.\n");
                goto ReadCompleteExit;
            }

            // If Alt setting 0 then we need to process into URB packets for USB MIDI 1.0 to UMP
            if (!pDeviceContext->UsbMIDIStreamingAlt)
            {
                // Create a working buffer
                workingBufferSize = ((NumBytesTransferred * 2) / sizeof(UINT32)) * sizeof(UINT32);
                    // For now assume that could wind up with twice
                    // size in converting from USB MIDI 1.0 to UMP
                    // making sure that overall size even on 32 bit words.
                status = WdfMemoryCreate(
                    NULL,       // attributes
                    NonPagedPool,
                    NULL,       // Pool Tag
                    workingBufferSize,
                    &workingBuffer,
                    NULL
                );
                if (!NT_SUCCESS(status))
                {
                    TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                        "Error creating working buffer for USB MIDI 1.0 to UMP conversion.\n");
                    goto ReadCompleteExit;
                }
                pWorkingBuffer = (PUCHAR)WdfMemoryGetBuffer(workingBuffer, NULL);
                workingBufferIndex = 0;

                for (ULONG count = 0; count < NumBytesTransferred; count += 4)
                {
                    // confirm not a NULL packet
                    if (pReceivedBuffer[count])
                    {
                        // There is a 32 bit data packet, so manage
                        // USB MIDI 1.0 format
                        // Convert to UMP using MIDI Association utilities
                        codeIndex = (MIDI_CIN_Type)(pReceivedBuffer[count] & MIDI_CIN_MASK);

                        // MIDI 1.0 Table 4-1: Code Index Number Classifications
                        switch (codeIndex)
                        {
                        case MIDI_CIN_MISC:
                        case MIDI_CIN_CABLE_EVENT:
                            // These are reserved and unused, possibly issue somewhere, skip this packet
                            TraceEvents(TRACE_LEVEL_WARNING, TRACE_DEVICE,
                                "USB MIDI 1.0 Packet CIN: 0x%02x not handled. Full packet is: 0x%04x\n",
                                codeIndex, *((PUINT32)&pReceivedBuffer[count])
                            );
                            pDeviceContext->streamPkt.total = 0;
                            break;

                        case MIDI_CIN_SYSEX_END_1BYTE:
                        case MIDI_CIN_1BYTE_DATA:
                            pDeviceContext->streamPkt.total = 1;
                            break;

                        case MIDI_CIN_SYSCOM_2BYTE:
                        case MIDI_CIN_SYSEX_END_2BYTE:
                        case MIDI_CIN_PROGRAM_CHANGE:
                        case MIDI_CIN_CHANNEL_PRESSURE:
                            pDeviceContext->streamPkt.total = 2;
                            break;

                        default:
                            pDeviceContext->streamPkt.total = 3;
                            break;
                        }

                        // ***Process MIDI1 data into UMP formatting***
                        for (ULONG index = 1; index <= pDeviceContext->streamPkt.total; index++)
                        {
                            // process byte stream character into converter
                            pDeviceContext->streamToUMP.bytestreamParse(
                                pReceivedBuffer[count + index]);

                            // determine if we have a packet to populate
                            while (pDeviceContext->streamToUMP.availableUMP())
                            {
                                if (workingBufferIndex == workingBufferSize)
                                {
                                    // Clear buffer by submitting read and reset
                                    if ( !USBUMPDriverFillReadQueue(
                                        (PUINT32)pWorkingBuffer,
                                        workingBufferSize / sizeof(UINT32),
                                        pDeviceContext
                                    ))
                                    {
                                        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                                            "Error submitting to read queue prep buffer.\n");
                                        goto ReadCompleteExit;
                                    }
                                    workingBufferIndex = 0; //reset index
                                }

                                // Put the packet into the buffer
                                *(PUINT32)&pWorkingBuffer[workingBufferIndex] =
                                    pDeviceContext->streamToUMP.readUMP();

                                TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
                                    "UMP Packet from USB MIDI 1.0: 0x%04x.\n",
                                    *(PUINT32)&pWorkingBuffer[workingBufferIndex]
                                );
                                // Advance working buffer index
                                workingBufferIndex += sizeof(UINT32);
                            }
                        }
                    }
                }

                // Make sure we submit any UMP not already sent
                if (workingBufferIndex)
                {
                    if ( !USBUMPDriverFillReadQueue(
                        (PUINT32)pWorkingBuffer,
                        workingBufferIndex / sizeof(UINT32),
                        pDeviceContext
                    ))
                    {
                        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                            "Error submitting to read queue prep buffer.\n");
                        goto ReadCompleteExit;
                    }
                }
            }
            else
            {
                // Send Memory to Read Queue
                if ( !USBUMPDriverFillReadQueue(
                    (PUINT32)pReceivedBuffer,
                    NumBytesTransferred / sizeof(UINT32),
                    pDeviceContext
                ))
                {
                    TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                        "Error submitting to read queue prep buffer.\n");
                    goto ReadCompleteExit;
                }
            }
        }
    }

ReadCompleteExit:
    if (workingBuffer)
    {
        // if we created a working buffer, be sure to get rid of it
        WdfObjectDelete(workingBuffer);
    }

    // The continuous reader takes care of completion of event and clearing buffer

    return;
}

BOOLEAN USBUMPDriverEvtReadFailed(
    WDFUSBPIPE      Pipe,
    NTSTATUS        status,
    USBD_STATUS     UsbdStatus
)
/*++
Routine Description:

    Callback for continuous reader to indicate that it has failed read.

Arguments:

    Pipe - the USB data pipe
    status - the status of the Pipe read
    USBD_STATUS - status of usb device

Return Value:

    Boolean - true if to try to restart reader

--*/
{
    UNREFERENCED_PARAMETER(Pipe);

    TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
        "%!FUNC! ReadersFailedCallback failed NTSTATUS 0x%x, UsbdStatus 0x%x\n",
        status,
        UsbdStatus);

    return TRUE;
}

BOOLEAN USBUMPDriverFillReadQueue(
    _In_    PUINT32             pBuffer,
    _In_    size_t              bufferSize,
    _In_    PDEVICE_CONTEXT     pDeviceContext
)
/*++
Routine Description:

    Helper routine to fill ring buffer with new information to be picked up by
    the IoEvtRead routine.

Arguments:

    pBuffer - buffer to copy
    bufferSize - the number of bytes in the buffer filled.
    Context - the driver context

Return Value:

    true if successful

--*/
{
    PREAD_RING_TYPE     pRing;
    size_t              index;
    size_t              ringRemain;
    PUINT32             pRingBuffer;

    // Check parameters passed
    if (!pBuffer)
        return false;

    // For convenience
    pRing = &pDeviceContext->ReadRingBuf;
    pRingBuffer = (PUINT32)WdfMemoryGetBuffer(pRing->RingBufMemory, NULL);
    index = 0;

    // Determine if currently processing read IO
    // TODO: Need to figure out how to enable / disable this processing
    if (true && bufferSize)
    {
        // Determine size of buffer remaining
        ringRemain = (pRing->ringBufTail > pRing->ringBufHead)
            ? pRing->ringBufTail - pRing->ringBufHead
            : pRing->ringBufSize - pRing->ringBufHead + pRing->ringBufTail;

        // Is there not enough room to add to buffer
        if (bufferSize > ringRemain)
        {
            TraceEvents(TRACE_LEVEL_WARNING, TRACE_DEVICE,
                "Warning, not enough room in ring buffer. Data lost.\n");
            // TODO - go through the buffer and remove old data, making sure to not split up
            // any UMP data making invalid data stream.
            // this may require spin lock protection, TBD
            // for now, just fail
            return false;
        }

        // Place data into ring buffer
        index = pRing->ringBufHead;
        for (size_t count = 0; count < bufferSize; count++)
        {
            pRingBuffer[index] = pBuffer[count];
            index = (index + 1) % pRing->ringBufSize;
        }
        pRing->ringBufHead = index;
    }
    else
    {
        // probably should clear the ring buffer if there is no
        // IO needed.
    }

    return true;
}

VOID
USBUMPDriverEvtIoRead(
    _In_ WDFQUEUE         Queue,
    _In_ WDFREQUEST       Request,
    _In_ size_t           Length
)
/*++

Routine Description:

    Called by the framework when it receives Read or Write requests.

Arguments:

    Queue - Default queue handle
    Request - Handle to the read/write request
    Length - Length of the data buffer associated with the request.
                 The default property of the queue is to not dispatch
                 zero length read & write requests to the driver and
                 complete is with status success. So we will never get
                 a zero length request.

Return Value:Amy


--*/
{
    NTSTATUS                    status;
    PDEVICE_CONTEXT             pDeviceContext;
    size_t                      requestSize;
    size_t                      numCopied = 0;
    PUINT32                     requestBuffer;
    WDFMEMORY                   requestMemory;
    PREAD_RING_TYPE             pRing;
    PUINT32                     pRingBuf;

    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_DEVICE, "-->USBUMPDriverEvtIoRead\n");

    pDeviceContext = DeviceGetContext(WdfIoQueueGetDevice(Queue));
    pRing = &pDeviceContext->ReadRingBuf;
    pRingBuf = (PUINT32)WdfMemoryGetBuffer(pRing->RingBufMemory, NULL);

    // First check passed parameters
    requestSize = Length / sizeof(UINT32);
    if (!requestSize)
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "%!FUNC! parameter invalid. Insufficient Length %d.\n", Length);
        status = STATUS_INVALID_PARAMETER;
        goto IoEvtReadExit;
    }

    // Get request buffer to write into
    status = WdfRequestRetrieveOutputMemory(Request, &requestMemory);
    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "WdfRequestRetrieveOutputMemory failed %!STATUS!\n", status);
        goto IoEvtReadExit;
    }
    requestBuffer = (PUINT32)WdfMemoryGetBuffer(requestMemory, NULL);

    // Transfer available data into available request buffer
    while ((pRing->ringBufTail != pRing->ringBufHead) && (numCopied < requestSize))
    {
        requestBuffer[numCopied++] = pRingBuf[pRing->ringBufTail++];
        pRing->ringBufTail %= pRing->ringBufSize;
    }

    IoEvtReadExit:
    if (!NT_SUCCESS(status))
    {
        WdfRequestCompleteWithInformation(Request, status, 0);
    }
    else
    {
        WdfRequestCompleteWithInformation(Request, status, numCopied * sizeof(UINT32));
    }

    return;
}

VOID
USBUMPDriverEvtIoWrite(
    _In_ WDFQUEUE         Queue,
    _In_ WDFREQUEST       Request,
    _In_ size_t           Length
)
/*++

Routine Description:

    Called by the framework when it receives Read or Write requests.

Arguments:

    Queue - Default queue handle
    Request - Handle to the read/write request
    Length - Length of the data buffer associated with the request.
                 The default property of the queue is to not dispatch
                 zero length read & write requests to the driver and
                 complete is with status success. So we will never get
                 a zero length request.

Return Value:Amy


--*/
{
    NTSTATUS                    status;
    WDFUSBPIPE                  pipe;
    WDFMEMORY                   reqMemory;
    PDEVICE_CONTEXT             pDeviceContext;
    size_t                      bufferCount = 0;
    PUCHAR                      pBuffer;
    PUCHAR                      pWriteBuffer = NULL;
    size_t                      writeBufferIndex = 0;
    WDFMEMORY                   writeMemory = NULL;
    WDF_OBJECT_ATTRIBUTES       writeMemoryAttributes;
    WDFREQUEST                  usbRequest = NULL;

    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_DEVICE, "-->USBUMPDriverEvtIoWrite\n");

    pDeviceContext = DeviceGetContext(WdfIoQueueGetDevice(Queue));
    pipe = pDeviceContext->MidiOutPipe;

    // 
    // General Error Checking
    // 
    if (Length % sizeof(UINT32)) // expected data is UINT32 array
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "%!FUNC! determined error in past data size not being UIN32 divisible.\n");
        status = STATUS_INVALID_PARAMETER;
        goto DriverEvtIoWriteExit;
    }

    // Get memory to work with
    status = WdfRequestRetrieveInputMemory(Request, &reqMemory);
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "%!FUNC! WdfRequestRetrieveInputBuffer failed\n");
        goto DriverEvtIoWriteExit;
    }
    pBuffer = (PUCHAR)WdfMemoryGetBuffer(reqMemory, NULL);

    // Check type of device connected to
    if (!pDeviceContext->UsbMIDIStreamingAlt)
    {
        //
        // Need to convert from UMP to USB MIDI 1.0 as a USB MIDI 1.0 device connected
        //
        for (bufferCount = 0; bufferCount < Length; bufferCount += sizeof(UINT32))
        {
            // Parse UMP to MIDI stream
            pDeviceContext->umpToStream.UMPStreamParse(*(PUINT32)&pBuffer[bufferCount]);

            while (pDeviceContext->umpToStream.availableBS())
            {
                UCHAR data = pDeviceContext->umpToStream.readBS();

                if (pDeviceContext->midi1UsbPkt.index == 0)
                {
                    //------------- New event packet -------------//
                    uint8_t const msg = data >> 4;

                    pDeviceContext->midi1UsbPkt.index = 2;
                    pDeviceContext->midi1UsbPkt.buffer[1] = data;

                    // Check to see if we're still in a SysEx transmit.
                    if (pDeviceContext->midi1UsbPkt.buffer[0] == MIDI_CIN_SYSEX_START)
                    {
                        if (data == MIDI_STATUS_SYSEX_END)
                        {
                            pDeviceContext->midi1UsbPkt.buffer[0] = MIDI_CIN_SYSEX_END_1BYTE;
                            pDeviceContext->midi1UsbPkt.total = 2;
                        }
                        else
                        {
                            pDeviceContext->midi1UsbPkt.total = 4;
                        }
                    }
                    else if ((msg >= 0x8 && msg <= 0xB) || msg == 0xE)
                    {
                        // Channel Voice Messages
                        pDeviceContext->midi1UsbPkt.buffer[0]
                            = (pDeviceContext->umpToStream.group << 4) | msg;
                        pDeviceContext->midi1UsbPkt.total = 4;
                    }
                    else if (msg == 0xC || msg == 0xD)
                    {
                        // Channel Voice Messages, two-byte variants (Program Change and Channel Pressure)
                        pDeviceContext->midi1UsbPkt.buffer[0]
                            = (pDeviceContext->umpToStream.group << 4) | msg;
                        pDeviceContext->midi1UsbPkt.total = 3;
                    }
                    else if (msg == 0xf)
                    {
                        // System message
                        if (data == MIDI_STATUS_SYSEX_START)
                        {
                            pDeviceContext->midi1UsbPkt.buffer[0] = MIDI_CIN_SYSEX_START;
                            pDeviceContext->midi1UsbPkt.total = 4;
                        }
                        else if (data == MIDI_STATUS_SYSCOM_TIME_CODE_QUARTER_FRAME
                            || data == MIDI_STATUS_SYSCOM_SONG_SELECT)
                        {
                            pDeviceContext->midi1UsbPkt.buffer[0] = MIDI_CIN_SYSCOM_2BYTE;
                            pDeviceContext->midi1UsbPkt.total = 3;
                        }
                        else if (data == MIDI_STATUS_SYSCOM_SONG_POSITION_POINTER)
                        {
                            pDeviceContext->midi1UsbPkt.buffer[0] = MIDI_CIN_SYSCOM_3BYTE;
                            pDeviceContext->midi1UsbPkt.total = 4;
                        }
                        else
                        {
                            pDeviceContext->midi1UsbPkt.buffer[0] = MIDI_CIN_SYSEX_END_1BYTE;
                            pDeviceContext->midi1UsbPkt.total = 2;
                        }
                    }
                    else
                    {
                        // Pack individual bytes if we don't support packing them into words.
                        pDeviceContext->midi1UsbPkt.buffer[0]
                            = pDeviceContext->umpToStream.group << 4 | 0xf;
                        pDeviceContext->midi1UsbPkt.buffer[2] = 0;
                        pDeviceContext->midi1UsbPkt.buffer[3] = 0;
                        pDeviceContext->midi1UsbPkt.index = 2;
                        pDeviceContext->midi1UsbPkt.total = 2;
                    }
                }
                else
                {
                    //------------- On-going (buffering) packet -------------//

                    pDeviceContext->midi1UsbPkt.buffer[pDeviceContext->midi1UsbPkt.index] = data;
                    pDeviceContext->midi1UsbPkt.index++;

                    // See if this byte ends a SysEx.
                    if (pDeviceContext->midi1UsbPkt.buffer[0]
                        == MIDI_CIN_SYSEX_START && data == MIDI_STATUS_SYSEX_END)
                    {
                        pDeviceContext->midi1UsbPkt.buffer[0]
                            = MIDI_CIN_SYSEX_START + (pDeviceContext->midi1UsbPkt.index - 1);
                        pDeviceContext->midi1UsbPkt.total = pDeviceContext->midi1UsbPkt.index;
                    }
                }

                // Add to packet for USB if needed
                if (pDeviceContext->midi1UsbPkt.index == pDeviceContext->midi1UsbPkt.total)
                {
                    // zeroes unused bytes
                    for (uint8_t idx = pDeviceContext->midi1UsbPkt.total; idx < 4; idx++)
                        pDeviceContext->midi1UsbPkt.buffer[idx] = 0;

                    // If currently no write buffer, create one
                    if (!pWriteBuffer)
                    {
                        // Create Request
                        status = WdfRequestCreate(
                            NULL,       // attributes
                            WdfUsbTargetPipeGetIoTarget(pipe),
                            &usbRequest    // retuest object
                        );
                        if (!NT_SUCCESS(status))
                        {
                            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                                "%!FUNC! Error creating request for USB Write with status: 0x%x", status);
                            goto DriverEvtIoWriteExit;
                        }

                        WDF_OBJECT_ATTRIBUTES_INIT(&writeMemoryAttributes);
                        writeMemoryAttributes.ParentObject = usbRequest;

                        // Create Memory Object
                        status = WdfMemoryCreate(
                            &writeMemoryAttributes,
                            NonPagedPool,
                            USBUMP_POOLTAG,
                            pDeviceContext->MidiOutMaxSize,
                            &writeMemory,
                            NULL
                        );
                        if (!NT_SUCCESS(status))
                        {
                            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                                "%!FUNC! could not create WdfMemory with status: 0x%x.\n", status);
                            goto DriverEvtIoWriteExit;
                        }
                        pWriteBuffer = (PUCHAR)WdfMemoryGetBuffer(writeMemory, NULL);
                    }

                    // Write into buffer
                    *(PUINT32)&pWriteBuffer[writeBufferIndex]
                        = *(PUINT32)&pDeviceContext->midi1UsbPkt.buffer[0];
                    writeBufferIndex += sizeof(UINT32);

                    if (writeBufferIndex == pDeviceContext->MidiOutMaxSize)
                    {
                        // Write to buffer
                        if (!USBUMPDriverSendToUSB(
                            usbRequest,
                            writeMemory,
                            pipe,
                            writeBufferIndex,
                            pDeviceContext,
                            true    // delete this request when complete
                        ))
                        {
                            goto DriverEvtIoWriteExit;
                        }

                        // Indicate new buffer needed
                        pWriteBuffer = NULL;
                        writeBufferIndex = 0;
                    }

                    // complete current event packet, reset stream
                    pDeviceContext->midi1UsbPkt.index = pDeviceContext->midi1UsbPkt.total = 0;
                }
            }
        }

        // Check if anything leftover to write to USB
        if (writeBufferIndex)
        {
            // Write to buffer
            if (!USBUMPDriverSendToUSB(
                usbRequest,
                writeMemory,
                pipe,
                writeBufferIndex,
                pDeviceContext,
                true    // delete this request when complete
            ))
            {
                goto DriverEvtIoWriteExit;
            }

            // Indicate new buffer needed
            pWriteBuffer = NULL;
            writeBufferIndex = 0;
        }

        // Indicate we are done with the request
        WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, Length);
    }
    else
    {
        //
        // UMP device, just pass along
        //
        if (Length > pDeviceContext->MidiOutMaxSize)
        {
            // we need to split up the data as too big for single USB URB
        }
        else
        {
            if (!USBUMPDriverSendToUSB(
                Request,
                reqMemory,
                pipe,
                Length,
                pDeviceContext,
                false   // Complete the request
            ))
            {
                goto DriverEvtIoWriteExit;
            }
        }
    }

DriverEvtIoWriteExit:

    // Make sure we do not have created memory sitting around
    if (pWriteBuffer && writeMemory && usbRequest)
    {
        // delete the parent object
        WdfObjectDelete(usbRequest);
    }

    return;
}

BOOLEAN USBUMPDriverSendToUSB(
    _In_ WDFREQUEST         usbRequest,
    _In_ WDFMEMORY          reqMemory,
    _In_ WDFUSBPIPE         pipe,
    _In_ size_t             Length,
    _In_ PDEVICE_CONTEXT    pDeviceContext,
    _In_ BOOLEAN            deleteRequest
)
{
    status = WdfUsbTargetPipeFormatRequestForWrite(pipe,
        usbRequest,
        reqMemory,
        NULL); // Offset
    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "WdfUsbTargetPipeFormatRequestForWrite failed 0x%x\n", status);
        goto SendToUSBExit;
    }

    WdfRequestSetCompletionRoutine(
        usbRequest,
        (deleteRequest) ? USBUMPDriverEvtRequestWriteCompletionRoutineDelete
                        : USBUMPDriverEvtRequestWriteCompletionRoutine,
        pipe);

    //
    // Send the request asynchronously.
    //
    if (WdfRequestSend(usbRequest, WdfUsbTargetPipeGetIoTarget(pipe), WDF_NO_SEND_OPTIONS) == FALSE) {
        //
        // Framework couldn't send the request for some reason.
        //
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "WdfRequestSend failed\n");
        status = WdfRequestGetStatus(usbRequest);
        goto SendToUSBExit;
    }

SendToUSBExit:
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_DEVICE, "<-- USBUMPExpEvtIoWrite\n");

    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "%!FUNC! write to USB error with status: 0x%x\n", status);
        if (!deleteRequest)
        {
            WdfRequestCompleteWithInformation(usbRequest, status, 0);
        }
        // else object will be managed by calling function

        return(false);
    }

    return true;
}

VOID
USBUMPDriverEvtRequestWriteCompletionRoutineDelete(
    _In_ WDFREQUEST                  Request,
    _In_ WDFIOTARGET                 Target,
    _In_ PWDF_REQUEST_COMPLETION_PARAMS CompletionParams,
    _In_ WDFCONTEXT                  Context
)
/*++

Routine Description:

    This is the completion routine for writes
    If the irp completes with success, we check if we
    need to recirculate this irp for another stage of
    transfer.

Arguments:

    Context - Driver supplied context
    Device - Device handle
    Request - Request handle
    Params - request completion params

Return Value:
    None

--*/
{
    NTSTATUS    status;
    size_t      bytesWritten = 0;
    PWDF_USB_REQUEST_COMPLETION_PARAMS usbCompletionParams;

    UNREFERENCED_PARAMETER(Target);
    UNREFERENCED_PARAMETER(Context);

    
    status = CompletionParams->IoStatus.Status;

    //
    // For usb devices, we should look at the Usb.Completion param.
    //
    usbCompletionParams = CompletionParams->Parameters.Usb.Completion;

    bytesWritten = usbCompletionParams->Parameters.PipeWrite.Length;

    if (NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
            "Number of bytes written: %I64d\n", (INT64)bytesWritten);
    }
    else {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "Write failed: request Status 0x%x UsbdStatus 0x%x\n",
            status, usbCompletionParams->UsbdStatus);
    }
    
    //WdfRequestCompleteWithInformation(Request, status, bytesWritten);
    WdfObjectDelete(Request);

    return;
}

VOID
USBUMPDriverEvtRequestWriteCompletionRoutine(
    _In_ WDFREQUEST                  Request,
    _In_ WDFIOTARGET                 Target,
    _In_ PWDF_REQUEST_COMPLETION_PARAMS CompletionParams,
    _In_ WDFCONTEXT                  Context
)
/*++

Routine Description:

    This is the completion routine for writes
    If the irp completes with success, we check if we
    need to recirculate this irp for another stage of
    transfer.

Arguments:

    Context - Driver supplied context
    Device - Device handle
    Request - Request handle
    Params - request completion params

Return Value:
    None

--*/
{
    NTSTATUS    status;
    size_t      bytesWritten = 0;
    PWDF_USB_REQUEST_COMPLETION_PARAMS usbCompletionParams;

    UNREFERENCED_PARAMETER(Target);
    UNREFERENCED_PARAMETER(Context);


    status = CompletionParams->IoStatus.Status;

    //
    // For usb devices, we should look at the Usb.Completion param.
    //
    usbCompletionParams = CompletionParams->Parameters.Usb.Completion;

    bytesWritten = usbCompletionParams->Parameters.PipeWrite.Length;

    if (NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
            "Number of bytes written: %I64d\n", (INT64)bytesWritten);
    }
    else {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
            "Write failed: request Status 0x%x UsbdStatus 0x%x\n",
            status, usbCompletionParams->UsbdStatus);
    }

    WdfRequestCompleteWithInformation(Request, status, bytesWritten);
    //WdfObjectDelete(Request);

    return;
}
