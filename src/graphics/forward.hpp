#ifndef DXNA_GRAPHICS_FORWARD_HPP
#define DXNA_GRAPHICS_FORWARD_HPP

#include <memory>
#include "../cs/cs.hpp"

namespace dxna::graphics {
	class GraphicsResource;
	class GraphicsDevice;
	class Shader;

	struct SamplerState;
	struct TargetBlendState;
	struct BlendState;
	struct DepthStencilState;
	struct RasterizerState;

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

	using GraphicsResourcePtr				= std::shared_ptr<GraphicsResource>;
	using GraphicsDevicePtr					= std::shared_ptr<GraphicsDevice>;
	using ShaderPtr							= std::shared_ptr<Shader>;
	using SamplerStatePtr					= std::shared_ptr<SamplerState>;
	using TargetBlendStatePtr				= std::shared_ptr<TargetBlendState>;
	using BlendStatePtr						= std::shared_ptr<BlendState>;
	using DepthStencilStatePtr				= std::shared_ptr<DepthStencilState>;
	using RasterizerStatePtr				= std::shared_ptr<RasterizerState>;
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

	//Obt�m um novo ponteiro para Shader
	ShaderPtr NewShader(GraphicsDevicePtr const& device, cs::BinaryReader& reader);

	//Obt�m um novo ponteiro para EffectTechnique
	EffectTechniquePtr NewEffectTechnique(std::string const& name,
		std::shared_ptr<EffectPassCollection> const& passes,
		std::shared_ptr<EffectAnnotationCollection> const& annotations);

	//Obt�m um novo ponteiro para EffectTechniqueCollection
	EffectTechniqueCollectionPtr NewEffectTechniqueCollection(std::vector<EffectTechniquePtr> const& techniques);

	//Obt�m um vetor de ponteiros de Shader
	std::vector<ShaderPtr> NewShaderArray(size_t count);

	//Obt�m um vetor de ponteiros de EffectTechnique
	std::vector<EffectTechniquePtr> NewEffectTechniqueArray(size_t count);
}


#endif