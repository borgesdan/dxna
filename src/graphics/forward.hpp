#ifndef DXNA_GRAPHICS_FORWARD_HPP
#define DXNA_GRAPHICS_FORWARD_HPP

#include <memory>

class EffectAnnotation;
class EffectAnnotationCollection;
class EffectParameter;
class EffectParameterCollection;
class EffectPass;
class EffectPassCollection;
class EffectTechnique;
class EffectTechniqueCollection;
class ConstantBuffer;
class ConstantBufferCollection;
class Effect;

using EffectAnnotationPtr = std::shared_ptr<EffectAnnotation>;
using EffectAnnotationCollectionPtr = std::shared_ptr<EffectAnnotationCollection>;
using EffectParameterPtr = std::shared_ptr<EffectParameter>;
using EffectParameterCollectionPtr = std::shared_ptr<EffectParameterCollection>;
using EffectPassPtr = std::shared_ptr<EffectPass>;
using EffectPassCollectionPtr = std::shared_ptr<EffectPassCollection>;
using EffectTechniquePtr = std::shared_ptr<EffectTechnique>;
using EffectTechniqueCollectionPtr = std::shared_ptr<EffectTechniqueCollection>;
using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;
using ConstantBufferCollectionPtr = std::shared_ptr<ConstantBufferCollection>;
using EffectPtr = std::shared_ptr<Effect>;

#endif