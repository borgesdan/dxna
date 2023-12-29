#ifndef DXNA_GRAPHICS_LIGHT_HPP
#define DXNA_GRAPHICS_LIGHT_HPP

#include "forward.hpp"
#include "effect.hpp"
#include "../structs.hpp"

namespace dxna::graphics {
	class DirectionalLight {
	public:
		DirectionalLight(
			EffectParameterPtr const& directionParameter,
			EffectParameterPtr const& diffuseColorParameter,
			EffectParameterPtr const& specularColorParameter,
			DirectionalLight const* cloneSource) :
			directionParameter(directionParameter),
			diffuseColorParameter(diffuseColorParameter),
			specularColorParameter(specularColorParameter) {

			if (cloneSource != nullptr) {
				diffuseColor = cloneSource->diffuseColor;
				direction = cloneSource->direction;
				specularColor = cloneSource->specularColor;
				enabled = cloneSource->enabled;
			}
		}

	public:
		EffectParameterPtr diffuseColorParameter;
		EffectParameterPtr directionParameter;
		EffectParameterPtr specularColorParameter;

		constexpr Vector3 DiffuseColor() const noexcept { return diffuseColor; }
		constexpr Vector3 Direction() const noexcept { return direction; }
		constexpr Vector3 SpecularColor() const noexcept { return specularColor; }
		constexpr bool Enabled() const noexcept { return enabled; }

		void DiffuseColor(Vector3 const& value) {
			diffuseColor = value;

			if (enabled && diffuseColorParameter != nullptr) {
				auto data = diffuseColorParameter.get();
				EffectParameterSetData(diffuseColor, data);
			}
		}

		void Direction(Vector3 const& value) {
			direction = value;

			if (enabled && directionParameter != nullptr) {
				auto data = directionParameter.get();
				EffectParameterSetData(diffuseColor, data);
			}
		}

		void SpecularColor(Vector3 const& value) {
			specularColor = value;

			if (enabled && specularColorParameter != nullptr) {				
				auto data = specularColorParameter.get();
				EffectParameterSetData(specularColor, data);
			}
		}

		void Enabled(bool value) {
			if (enabled != value) {
				enabled = value;

				if (enabled) {
					if (diffuseColorParameter != nullptr)
					{
						auto data = diffuseColorParameter.get();
						EffectParameterSetData(diffuseColor, data);
					}
					if (specularColorParameter != nullptr)
					{
						auto data = specularColorParameter.get();
						EffectParameterSetData(diffuseColor, data);
					}
				}
				else {
					if (diffuseColorParameter != nullptr)
					{						
						auto data = diffuseColorParameter.get();
						//auto vec3 = Vector3();
						EffectParameterSetData(Vector3::Zero(), data);
					}
					if (specularColorParameter != nullptr)
					{
						auto data = specularColorParameter.get();
						//auto vec3 = Vector3();
						EffectParameterSetData(Vector3::Zero(), data);
					}
				}
			}
		}

	private:
		Vector3 diffuseColor;
		Vector3 direction;
		Vector3 specularColor;
		bool enabled{ false };
	};
}

#endif