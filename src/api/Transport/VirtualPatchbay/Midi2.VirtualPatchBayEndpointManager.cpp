// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License
// ============================================================================
// This is part of the Windows MIDI Services App API and should be used
// in your Windows application via an official binary distribution.
// Further information: https://github.com/microsoft/MIDI/
// ============================================================================


#include "pch.h"

using namespace wil;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

GUID AbstractionLayerGUID = ABSTRACTION_LAYER_GUID;

_Use_decl_annotations_
HRESULT
CMidi2VirtualPatchBayEndpointManager::Initialize(
    IUnknown* MidiDeviceManager, 
    IUnknown* /*midiEndpointProtocolManager*/
)
{
    TraceLoggingWrite(
        MidiVirtualPatchBayAbstractionTelemetryProvider::Provider(),
        MIDI_TRACE_EVENT_INFO,
        TraceLoggingString(__FUNCTION__, MIDI_TRACE_EVENT_LOCATION_FIELD),
        TraceLoggingPointer(this, "this"),
        TraceLoggingWideString(L"Enter", MIDI_TRACE_EVENT_MESSAGE_FIELD)
    );

    RETURN_HR_IF(E_INVALIDARG, nullptr == MidiDeviceManager);

    RETURN_IF_FAILED(MidiDeviceManager->QueryInterface(__uuidof(IMidiDeviceManagerInterface), (void**)&m_MidiDeviceManager));

    m_TransportAbstractionId = AbstractionLayerGUID;   // this is needed so MidiSrv can instantiate the correct transport
    m_ContainerId = m_TransportAbstractionId;          // we use the transport ID as the container ID for convenience


    return S_OK;
}

HRESULT 
CMidi2VirtualPatchBayEndpointManager::CreateEndpoint(
    )
{
    TraceLoggingWrite(
        MidiVirtualPatchBayAbstractionTelemetryProvider::Provider(),
        MIDI_TRACE_EVENT_INFO,
        TraceLoggingString(__FUNCTION__, MIDI_TRACE_EVENT_LOCATION_FIELD),
        TraceLoggingPointer(this, "this"),
        TraceLoggingWideString(L"Enter", MIDI_TRACE_EVENT_MESSAGE_FIELD)
    );

    return S_OK;
}


HRESULT
CMidi2VirtualPatchBayEndpointManager::Cleanup()
{
    TraceLoggingWrite(
        MidiVirtualPatchBayAbstractionTelemetryProvider::Provider(),
        MIDI_TRACE_EVENT_INFO,
        TraceLoggingString(__FUNCTION__, MIDI_TRACE_EVENT_LOCATION_FIELD),
        TraceLoggingLevel(WINEVENT_LEVEL_INFO),
        TraceLoggingPointer(this, "this")
    );

    AbstractionState::Current().Cleanup();

    m_MidiDeviceManager.reset();
    m_MidiProtocolManager.reset();
    m_DeviceAdded.revoke();
    m_DeviceRemoved.revoke();
    m_DeviceUpdated.revoke();
    m_DeviceStopped.revoke();
    m_DeviceEnumerationCompleted.revoke();

    return S_OK;
}




_Use_decl_annotations_
HRESULT CMidi2VirtualPatchBayEndpointManager::OnDeviceAdded(DeviceWatcher, DeviceInformation addedDevice)
{
    // check our device definition table. If any devices include this
    // device, update that table and check for completeness before
    // enumerating the virtual patch bay device
    UNREFERENCED_PARAMETER(addedDevice);


    return S_OK;
}

_Use_decl_annotations_
HRESULT CMidi2VirtualPatchBayEndpointManager::OnDeviceRemoved(DeviceWatcher, DeviceInformationUpdate update)
{
    // tear down any virtual devices which include this device as an input or output

    UNREFERENCED_PARAMETER(update);

    return S_OK;
}

_Use_decl_annotations_
HRESULT CMidi2VirtualPatchBayEndpointManager::OnDeviceUpdated(DeviceWatcher, DeviceInformationUpdate)
{

    return S_OK;
}

_Use_decl_annotations_
HRESULT CMidi2VirtualPatchBayEndpointManager::OnDeviceStopped(DeviceWatcher, winrt::Windows::Foundation::IInspectable)
{

    return S_OK;
}

_Use_decl_annotations_
HRESULT CMidi2VirtualPatchBayEndpointManager::OnEnumerationCompleted(DeviceWatcher, winrt::Windows::Foundation::IInspectable)
{

    return S_OK;
}