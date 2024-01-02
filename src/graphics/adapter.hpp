#ifndef DXNA_GRAPHICS_ADAPTER_HPP
#define DXNA_GRAPHICS_ADAPTER_HPP

#include "forward.hpp"
#include "display.hpp"
#include <vector>
#include <string>
#include "../types.hpp"
#include "enumerations.hpp"

namespace dxna::graphics {
	class GraphicsAdapter {
    public:       
        enum class DriverType {
            Hardware,
            Reference,
            FastSoftware
        };

        static void GraphicsAdapter_ctor() {
            PlatformInitializeAdapters(_adapters);
            _adapters->at(0)->_isDefaultAdapter = true;
        }

        static void PlatformInitializeAdapters(vectorptr<GraphicsAdapterPtr>& adapters) {
            //TODO: PlatformInitializeAdapters
        }
       
        static GraphicsAdapterPtr DefaultAdapter() {
            return _adapters->at(0);
        }

        static vectorptr<GraphicsAdapterPtr> Adapter() {
            return _adapters;
        }

        static bool UseReferenceDevice() {
            return UseDriverType == DriverType::Reference;
        }

        void UseReferenceDevice(bool value) {
            UseDriverType = value ? DriverType::Reference : DriverType::Hardware;
        }

        std::string Description() const noexcept {
            return _description;
        }

        int DeviceId() const noexcept {
            return _deviceId;
        }

        int VendorId() const noexcept {
            return _deviceId;
        }

        bool IsDefaultAdapter() const noexcept {
            return _isDefaultAdapter;
        }

        int Revision() const noexcept {
            return _revision;
        }
        
        int SubSystemId() const noexcept {
            return _subSystemId;
        }

        DisplayModeCollectionPtr SupportedDisplayModes() const noexcept {
            return _supportedDisplayModes;
        }

        DisplayModePtr CurrentDisplayMode() const noexcept {
            return _currentDisplayMode;
        }

        bool IsWideScreen() const noexcept {
            const auto minWideScreenAspect = 16.0f / 10.0f;
            return _currentDisplayMode->AspectRatio() >= minWideScreenAspect;
        }

        bool QueryRenderTargetFormat(SurfaceFormat const& format,            
            SurfaceFormat& selectedFormat) const noexcept {

            selectedFormat = format;

            if (selectedFormat == SurfaceFormat::Alpha8
                || selectedFormat == SurfaceFormat::NormalizedByte2 
                || selectedFormat == SurfaceFormat::NormalizedByte4 
                || selectedFormat == SurfaceFormat::Dxt1 
                || selectedFormat == SurfaceFormat::Dxt3 
                || selectedFormat == SurfaceFormat::Dxt5 
                || selectedFormat == SurfaceFormat::Dxt1a 
                || selectedFormat == SurfaceFormat::Dxt1SRgb 
                || selectedFormat == SurfaceFormat::Dxt3SRgb 
                || selectedFormat == SurfaceFormat::Dxt5SRgb)
                selectedFormat = SurfaceFormat::Color;

            return (format == selectedFormat);
        }

        bool IsProfileSupported(GraphicsProfile const& graphicsProfile) {
            return PlatformIsProfileSupported(graphicsProfile);
        }

    public:
        static vectorptr<GraphicsAdapterPtr> _adapters;
        static DriverType UseDriverType;
        static bool UseDebugLayers;       

    private:
        DisplayModeCollectionPtr _supportedDisplayModes;
        DisplayModePtr _currentDisplayMode;
        std::string _description;
        int _deviceId;
        int _vendorId;
        bool _isDefaultAdapter;
        int _revision;
        int _subSystemId;

    private:
        bool PlatformIsProfileSupported(GraphicsProfile const& graphicsProfile) {
            //TODO: PlatformIsProfileSupported
        }
	};
}

#endif