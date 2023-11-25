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

	class IndexBuffer;
	class DynamicIndexBuffer;
	class IVertexType;
	class VertexDeclaration;
	class VertexDeclarationData;
	class VertexBuffer;
	class VertexBufferBindings;

	class TextureCollection;

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
	
	using IndexBufferPtr					= std::shared_ptr<IndexBuffer>;
	using DynamicIndexBufferPtr				= std::shared_ptr<DynamicIndexBuffer>;
	using IVertexTypePtr					= std::shared_ptr<IVertexType>;
	using VertexDeclarationPtr				= std::shared_ptr<VertexDeclaration>;
	using VertexDeclarationDataPtr			= std::shared_ptr<VertexDeclarationData>;
	using VertexBufferPtr					= std::shared_ptr<VertexBuffer>;
	using VertexBufferBindingsPtr			= std::shared_ptr<VertexBufferBindings>;
	
	using TextureCollectionPtr				= std::shared_ptr<TextureCollection>;	
}

#endif