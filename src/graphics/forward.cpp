#include "forward.hpp"
#include "shader.hpp"
#include "effect.hpp"

namespace dxna::graphics {
	ShaderPtr NewShader(GraphicsDevicePtr const& device, cs::BinaryReader& reader) {
		return std::make_shared<Shader>(device, reader);
	}

	EffectTechniquePtr NewEffectTechnique(std::string const& name, std::shared_ptr<EffectPassCollection> const& passes, std::shared_ptr<EffectAnnotationCollection> const& annotations) {
		return std::make_shared<EffectTechnique>(name, passes, annotations);
	}

	EffectTechniqueCollectionPtr NewEffectTechniqueCollection(std::vector<EffectTechniquePtr> const& techniques) {
		return std::make_shared<EffectTechniqueCollection>(techniques);
	}
	
	std::vector<ShaderPtr> NewShaderArray(size_t count) {
		return std::vector<ShaderPtr>(count);
	}
	
	std::vector<EffectTechniquePtr> NewEffectTechniqueArray(size_t count) {
		return std::vector<EffectTechniquePtr>(count);
	}

}