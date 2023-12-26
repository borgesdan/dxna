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
				//diffuseColorParameter->SetValue(diffuseColor);
			}
		}

		void Direction(Vector3 const& value) {
			direction = value;

			if (enabled && directionParameter != nullptr) {
				//diffuseColorParameter->SetValue(diffuseColor);
			}
		}

		void SpecularColor(Vector3 const& value) {
			specularColor = value;

			if (enabled && specularColorParameter != nullptr) {
				//diffuseColorParameter->SetValue(diffuseColor);
			}
		}

		void Enabled(bool value) {
			if (enabled != value) {
				enabled = value;

				if (enabled) {
					if (diffuseColorParameter != nullptr)
					{
						//diffuseColorParameter.SetValue(diffuseColor);
					}
					if (specularColorParameter != nullptr)
					{
						//specularColorParameter.SetValue(specularColor);
					}
				}
				else {
					if (diffuseColorParameter != nullptr)
					{
						//diffuseColorParameter.SetValue(Vector3.Zero);
					}
					if (specularColorParameter != nullptr)
					{
						//specularColorParameter.SetValue(Vector3.Zero);
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