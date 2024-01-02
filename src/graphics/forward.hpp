#ifndef DXNA_GRAPHICS_FORWARD_HPP
#define DXNA_GRAPHICS_FORWARD_HPP

#include <memory>
#include "../cs/cs.hpp"

namespace dxna::graphics {
	class GraphicsResource;
	class GraphicsDevice;	
	struct SamplerInfo;
	struct VertexAttribute;
	class Shader;
	struct SamplerState;
	struct TargetBlendState;
	struct BlendState;
	struct DepthStencilState;
	struct RasterizerState;
	class SamplerStateCollection;
	class Effect;
	class EffectAnnotation;
	class EffectParameter;
	class EffectPass;
	class EffectTechnique;
	class ConstantBuffer;
	class EffectAnnotationCollection;
	class EffectParameterCollection;
	class EffectPassCollection;
	class EffectTechniqueCollection;
	class ConstantBufferCollection;
	class TextureCollection;
	class DirectionalLight;
	class DisplayMode;
	class DisplayModeCollection;
	class GraphicsAdapter;

	using GraphicsResourcePtr				= std::shared_ptr<GraphicsResource>;
	using GraphicsDevicePtr					= std::shared_ptr<GraphicsDevice>;
	using SamplerInfoPtr					= std::shared_ptr<SamplerInfo>;
	using VertexAttributePtr				= std::shared_ptr<VertexAttribute>;
	using ShaderPtr							= std::shared_ptr<Shader>;
	using SamplerStatePtr					= std::shared_ptr<SamplerState>;
	using TargetBlendStatePtr				= std::shared_ptr<TargetBlendState>;
	using BlendStatePtr						= std::shared_ptr<BlendState>;
	using DepthStencilStatePtr				= std::shared_ptr<DepthStencilState>;
	using RasterizerStatePtr				= std::shared_ptr<RasterizerState>;
	using SamplerStateCollectionPtr			= std::shared_ptr<SamplerStateCollection>;
	using EffectPtr							= std::shared_ptr<Effect>;
	using EffectAnnotationPtr				= std::shared_ptr<EffectAnnotation>;
	using EffectParameterPtr				= std::shared_ptr<EffectParameter>;
	using EffectPassPtr						= std::shared_ptr<EffectPass>;
	using EffectTechniquePtr				= std::shared_ptr<EffectTechnique>;
	using ConstantBufferPtr					= std::shared_ptr<ConstantBuffer>;
	using EffectAnnotationCollectionPtr		= std::shared_ptr<EffectAnnotationCollection>;
	using EffectParameterCollectionPtr		= std::shared_ptr<EffectParameterCollection>;
	using EffectPassCollectionPtr			= std::shared_ptr<EffectPassCollection>;
	using EffectTechniqueCollectionPtr		= std::shared_ptr<EffectTechniqueCollection>;
	using ConstantBufferCollectionPtr		= std::shared_ptr<ConstantBufferCollection>;	
	using TextureCollectionPtr				= std::shared_ptr<TextureCollection>;	
	using DirectionalLightPtr				= std::shared_ptr<DirectionalLight>;
	using DisplayModePtr					= std::shared_ptr<DisplayMode>;
	using DisplayModeCollectionPtr			= std::shared_ptr<DisplayModeCollection>;
	using GraphicsAdapterPtr				= std::shared_ptr<GraphicsAdapter>;
}

#endif