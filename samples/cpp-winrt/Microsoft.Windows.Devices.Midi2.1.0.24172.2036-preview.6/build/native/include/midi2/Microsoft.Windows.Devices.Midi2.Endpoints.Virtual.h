// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_H
#define WINRT_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_H
#include "winrt/base.h"
static_assert(winrt::check_version(CPPWINRT_VERSION, "2.0.240405.15"), "Mismatched C++/WinRT headers.");
#define CPPWINRT_VERSION "2.0.240405.15"
#include "winrt/Microsoft.Windows.Devices.Midi2.h"
#include "winrt/impl/Microsoft.Windows.Devices.Midi2.2.h"
#include "winrt/impl/Microsoft.Windows.Devices.Midi2.ServiceConfig.2.h"
#include "winrt/impl/Windows.Foundation.2.h"
#include "winrt/impl/Windows.Foundation.Collections.2.h"
#include "winrt/impl/Microsoft.Windows.Devices.Midi2.Endpoints.Virtual.2.h"
namespace winrt::impl
{
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiStreamConfigRequestReceivedEventArgs<D>::Timestamp() const
    {
        uint64_t value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs)->get_Timestamp(&value));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiStreamConfigRequestReceivedEventArgs<D>::PreferredMidiProtocol() const
    {
        winrt::Microsoft::Windows::Devices::Midi2::MidiProtocol value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs)->get_PreferredMidiProtocol(reinterpret_cast<int32_t*>(&value)));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiStreamConfigRequestReceivedEventArgs<D>::RequestEndpointTransmitJitterReductionTimestamps() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs)->get_RequestEndpointTransmitJitterReductionTimestamps(&value));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiStreamConfigRequestReceivedEventArgs<D>::RequestEndpointReceiveJitterReductionTimestamps() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs)->get_RequestEndpointReceiveJitterReductionTimestamps(&value));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::DeviceEndpointDeviceId() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->get_DeviceEndpointDeviceId(&value));
        return hstring{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::FunctionBlocks() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->get_FunctionBlocks(&value));
        return winrt::Windows::Foundation::Collections::IMapView<uint8_t, winrt::Microsoft::Windows::Devices::Midi2::MidiFunctionBlock>{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::UpdateFunctionBlock(winrt::Microsoft::Windows::Devices::Midi2::MidiFunctionBlock const& block) const
    {
        bool result{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->UpdateFunctionBlock(*(void**)(&block), &result));
        return result;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::UpdateEndpointName(param::hstring const& name) const
    {
        bool result{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->UpdateEndpointName(*(void**)(&name), &result));
        return result;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::SuppressHandledMessages() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->get_SuppressHandledMessages(&value));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::SuppressHandledMessages(bool value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->put_SuppressHandledMessages(value));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::StreamConfigRequestReceived(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDevice, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiStreamConfigRequestReceivedEventArgs> const& handler) const
    {
        winrt::event_token token{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->add_StreamConfigRequestReceived(*(void**)(&handler), put_abi(token)));
        return token;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::StreamConfigRequestReceived(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDevice, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiStreamConfigRequestReceivedEventArgs> const& handler) const
    {
        return impl::make_event_revoker<D, StreamConfigRequestReceived_revoker>(this, StreamConfigRequestReceived(handler));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDevice<D>::StreamConfigRequestReceived(winrt::event_token const& token) const noexcept
    {
        WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice)->remove_StreamConfigRequestReceived(impl::bind_in(token));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::Name() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_Name(&value));
        return hstring{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::Name(param::hstring const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->put_Name(*(void**)(&value)));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::Description() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_Description(&value));
        return hstring{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::Description(param::hstring const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->put_Description(*(void**)(&value)));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::Manufacturer() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_Manufacturer(&value));
        return hstring{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::Manufacturer(param::hstring const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->put_Manufacturer(*(void**)(&value)));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::DeclaredDeviceIdentity() const
    {
        winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_DeclaredDeviceIdentity(put_abi(value)));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::DeclaredDeviceIdentity(winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->put_DeclaredDeviceIdentity(impl::bind_in(value)));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::DeclaredEndpointInfo() const
    {
        winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_DeclaredEndpointInfo(put_abi(value)));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::DeclaredEndpointInfo(winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->put_DeclaredEndpointInfo(impl::bind_in(value)));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::UserSuppliedInfo() const
    {
        winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_UserSuppliedInfo(put_abi(value)));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::UserSuppliedInfo(winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->put_UserSuppliedInfo(impl::bind_in(value)));
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfig<D>::FunctionBlocks() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig)->get_FunctionBlocks(&value));
        return winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Devices::Midi2::MidiFunctionBlock>{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfigFactory<D>::CreateInstance(param::hstring const& name, param::hstring const& description, param::hstring const& manufacturer, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& declaredEndpointInfo) const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfigFactory)->CreateInstance(*(void**)(&name), *(void**)(&description), *(void**)(&manufacturer), impl::bind_in(declaredEndpointInfo), &value));
        return winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfigFactory<D>::CreateInstance2(param::hstring const& name, param::hstring const& description, param::hstring const& manufacturer, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& declaredEndpointInfo, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const& declaredDeviceIdentity) const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfigFactory)->CreateInstance2(*(void**)(&name), *(void**)(&description), *(void**)(&manufacturer), impl::bind_in(declaredEndpointInfo), impl::bind_in(declaredDeviceIdentity), &value));
        return winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceCreationConfigFactory<D>::CreateInstance3(param::hstring const& name, param::hstring const& description, param::hstring const& manufacturer, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& declaredEndpointInfo, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const& declaredDeviceIdentity, winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo const& userSuppliedInfo) const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfigFactory)->CreateInstance3(*(void**)(&name), *(void**)(&description), *(void**)(&manufacturer), impl::bind_in(declaredEndpointInfo), impl::bind_in(declaredDeviceIdentity), impl::bind_in(userSuppliedInfo), &value));
        return winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig{ value, take_ownership_from_abi };
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceManagerStatics<D>::IsTransportAvailable() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManagerStatics)->get_IsTransportAvailable(&value));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceManagerStatics<D>::AbstractionId() const
    {
        winrt::guid value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManagerStatics)->get_AbstractionId(put_abi(value)));
        return value;
    }
    template <typename D> auto consume_Microsoft_Windows_Devices_Midi2_Endpoints_Virtual_IMidiVirtualDeviceManagerStatics<D>::CreateVirtualDevice(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig const& creationConfig) const
    {
        void* result{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManagerStatics)->CreateVirtualDevice(*(void**)(&creationConfig), &result));
        return winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDevice{ result, take_ownership_from_abi };
    }
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs> : produce_base<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs>
    {
        int32_t __stdcall get_Timestamp(uint64_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<uint64_t>(this->shim().Timestamp());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_PreferredMidiProtocol(int32_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::MidiProtocol>(this->shim().PreferredMidiProtocol());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_RequestEndpointTransmitJitterReductionTimestamps(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().RequestEndpointTransmitJitterReductionTimestamps());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_RequestEndpointReceiveJitterReductionTimestamps(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().RequestEndpointReceiveJitterReductionTimestamps());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice> : produce_base<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice>
    {
        int32_t __stdcall get_DeviceEndpointDeviceId(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<hstring>(this->shim().DeviceEndpointDeviceId());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_FunctionBlocks(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::Foundation::Collections::IMapView<uint8_t, winrt::Microsoft::Windows::Devices::Midi2::MidiFunctionBlock>>(this->shim().FunctionBlocks());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall UpdateFunctionBlock(void* block, bool* result) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *result = detach_from<bool>(this->shim().UpdateFunctionBlock(*reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiFunctionBlock const*>(&block)));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall UpdateEndpointName(void* name, bool* result) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *result = detach_from<bool>(this->shim().UpdateEndpointName(*reinterpret_cast<hstring const*>(&name)));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_SuppressHandledMessages(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().SuppressHandledMessages());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_SuppressHandledMessages(bool value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().SuppressHandledMessages(value);
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall add_StreamConfigRequestReceived(void* handler, winrt::event_token* token) noexcept final try
        {
            zero_abi<winrt::event_token>(token);
            typename D::abi_guard guard(this->shim());
            *token = detach_from<winrt::event_token>(this->shim().StreamConfigRequestReceived(*reinterpret_cast<winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDevice, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiStreamConfigRequestReceivedEventArgs> const*>(&handler)));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall remove_StreamConfigRequestReceived(winrt::event_token token) noexcept final
        {
            typename D::abi_guard guard(this->shim());
            this->shim().StreamConfigRequestReceived(*reinterpret_cast<winrt::event_token const*>(&token));
            return 0;
        }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig> : produce_base<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig>
    {
        int32_t __stdcall get_Name(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<hstring>(this->shim().Name());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_Name(void* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Name(*reinterpret_cast<hstring const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_Description(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<hstring>(this->shim().Description());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_Description(void* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Description(*reinterpret_cast<hstring const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_Manufacturer(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<hstring>(this->shim().Manufacturer());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_Manufacturer(void* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Manufacturer(*reinterpret_cast<hstring const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_DeclaredDeviceIdentity(struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredDeviceIdentity* value) noexcept final try
        {
            zero_abi<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity>(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity>(this->shim().DeclaredDeviceIdentity());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_DeclaredDeviceIdentity(struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredDeviceIdentity value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().DeclaredDeviceIdentity(*reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_DeclaredEndpointInfo(struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredEndpointInfo* value) noexcept final try
        {
            zero_abi<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo>(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo>(this->shim().DeclaredEndpointInfo());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_DeclaredEndpointInfo(struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredEndpointInfo value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().DeclaredEndpointInfo(*reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_UserSuppliedInfo(struct struct_Microsoft_Windows_Devices_Midi2_MidiEndpointUserSuppliedInfo* value) noexcept final try
        {
            zero_abi<winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo>(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo>(this->shim().UserSuppliedInfo());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_UserSuppliedInfo(struct struct_Microsoft_Windows_Devices_Midi2_MidiEndpointUserSuppliedInfo value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().UserSuppliedInfo(*reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_FunctionBlocks(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Devices::Midi2::MidiFunctionBlock>>(this->shim().FunctionBlocks());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfigFactory> : produce_base<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfigFactory>
    {
        int32_t __stdcall CreateInstance(void* name, void* description, void* manufacturer, struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredEndpointInfo declaredEndpointInfo, void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig>(this->shim().CreateInstance(*reinterpret_cast<hstring const*>(&name), *reinterpret_cast<hstring const*>(&description), *reinterpret_cast<hstring const*>(&manufacturer), *reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const*>(&declaredEndpointInfo)));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall CreateInstance2(void* name, void* description, void* manufacturer, struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredEndpointInfo declaredEndpointInfo, struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredDeviceIdentity declaredDeviceIdentity, void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig>(this->shim().CreateInstance2(*reinterpret_cast<hstring const*>(&name), *reinterpret_cast<hstring const*>(&description), *reinterpret_cast<hstring const*>(&manufacturer), *reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const*>(&declaredEndpointInfo), *reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const*>(&declaredDeviceIdentity)));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall CreateInstance3(void* name, void* description, void* manufacturer, struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredEndpointInfo declaredEndpointInfo, struct struct_Microsoft_Windows_Devices_Midi2_MidiDeclaredDeviceIdentity declaredDeviceIdentity, struct struct_Microsoft_Windows_Devices_Midi2_MidiEndpointUserSuppliedInfo userSuppliedInfo, void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig>(this->shim().CreateInstance3(*reinterpret_cast<hstring const*>(&name), *reinterpret_cast<hstring const*>(&description), *reinterpret_cast<hstring const*>(&manufacturer), *reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const*>(&declaredEndpointInfo), *reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const*>(&declaredDeviceIdentity), *reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo const*>(&userSuppliedInfo)));
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManager> : produce_base<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManager>
    {
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManagerStatics> : produce_base<D, winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManagerStatics>
    {
        int32_t __stdcall get_IsTransportAvailable(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().IsTransportAvailable());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_AbstractionId(winrt::guid* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::guid>(this->shim().AbstractionId());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall CreateVirtualDevice(void* creationConfig, void** result) noexcept final try
        {
            clear_abi(result);
            typename D::abi_guard guard(this->shim());
            *result = detach_from<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDevice>(this->shim().CreateVirtualDevice(*reinterpret_cast<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig const*>(&creationConfig)));
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
}
WINRT_EXPORT namespace winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual
{
    inline MidiVirtualDeviceCreationConfig::MidiVirtualDeviceCreationConfig(param::hstring const& name, param::hstring const& description, param::hstring const& manufacturer, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& declaredEndpointInfo) :
        MidiVirtualDeviceCreationConfig(impl::call_factory<MidiVirtualDeviceCreationConfig, IMidiVirtualDeviceCreationConfigFactory>([&](IMidiVirtualDeviceCreationConfigFactory const& f) { return f.CreateInstance(name, description, manufacturer, declaredEndpointInfo); }))
    {
    }
    inline MidiVirtualDeviceCreationConfig::MidiVirtualDeviceCreationConfig(param::hstring const& name, param::hstring const& description, param::hstring const& manufacturer, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& declaredEndpointInfo, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const& declaredDeviceIdentity) :
        MidiVirtualDeviceCreationConfig(impl::call_factory<MidiVirtualDeviceCreationConfig, IMidiVirtualDeviceCreationConfigFactory>([&](IMidiVirtualDeviceCreationConfigFactory const& f) { return f.CreateInstance2(name, description, manufacturer, declaredEndpointInfo, declaredDeviceIdentity); }))
    {
    }
    inline MidiVirtualDeviceCreationConfig::MidiVirtualDeviceCreationConfig(param::hstring const& name, param::hstring const& description, param::hstring const& manufacturer, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredEndpointInfo const& declaredEndpointInfo, winrt::Microsoft::Windows::Devices::Midi2::MidiDeclaredDeviceIdentity const& declaredDeviceIdentity, winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointUserSuppliedInfo const& userSuppliedInfo) :
        MidiVirtualDeviceCreationConfig(impl::call_factory<MidiVirtualDeviceCreationConfig, IMidiVirtualDeviceCreationConfigFactory>([&](IMidiVirtualDeviceCreationConfigFactory const& f) { return f.CreateInstance3(name, description, manufacturer, declaredEndpointInfo, declaredDeviceIdentity, userSuppliedInfo); }))
    {
    }
    inline auto MidiVirtualDeviceManager::IsTransportAvailable()
    {
        return impl::call_factory_cast<bool(*)(IMidiVirtualDeviceManagerStatics const&), MidiVirtualDeviceManager, IMidiVirtualDeviceManagerStatics>([](IMidiVirtualDeviceManagerStatics const& f) { return f.IsTransportAvailable(); });
    }
    inline auto MidiVirtualDeviceManager::AbstractionId()
    {
        return impl::call_factory_cast<winrt::guid(*)(IMidiVirtualDeviceManagerStatics const&), MidiVirtualDeviceManager, IMidiVirtualDeviceManagerStatics>([](IMidiVirtualDeviceManagerStatics const& f) { return f.AbstractionId(); });
    }
    inline auto MidiVirtualDeviceManager::CreateVirtualDevice(winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig const& creationConfig)
    {
        return impl::call_factory<MidiVirtualDeviceManager, IMidiVirtualDeviceManagerStatics>([&](IMidiVirtualDeviceManagerStatics const& f) { return f.CreateVirtualDevice(creationConfig); });
    }
}
namespace std
{
#ifndef WINRT_LEAN_AND_MEAN
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiStreamConfigRequestReceivedEventArgs> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDevice> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfig> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceCreationConfigFactory> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManager> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::IMidiVirtualDeviceManagerStatics> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiStreamConfigRequestReceivedEventArgs> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDevice> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceCreationConfig> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Microsoft::Windows::Devices::Midi2::Endpoints::Virtual::MidiVirtualDeviceManager> : winrt::impl::hash_base {};
#endif
#ifdef __cpp_lib_format
#endif
}
#endif
