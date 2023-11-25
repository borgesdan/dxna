#include "vertex.hpp"

namespace dxna::graphics {
	VertexDeclarationPtr const VertexPosition::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0)
	}));

	VertexDeclarationPtr const VertexPositionColor::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
			VertexElement(12, VertexElementFormat::Color, VertexElementUsage::Color, 0)}));

	VertexDeclarationPtr const VertexPositionColorNormal::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
			VertexElement(12, VertexElementFormat::Color, VertexElementUsage::Color, 0),
			VertexElement(16, VertexElementFormat::Vector3, VertexElementUsage::Normal, 0)}));

	VertexDeclarationPtr const VertexPositionColorNormalTexture::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
			VertexElement(12, VertexElementFormat::Color, VertexElementUsage::Color, 0),
			VertexElement(16, VertexElementFormat::Vector3, VertexElementUsage::Normal, 0),
			VertexElement(28, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0)}));

	VertexDeclarationPtr const VertexPositionColorTexture::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
			VertexElement(12, VertexElementFormat::Color, VertexElementUsage::Color, 0),
			VertexElement(16, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0)}));

	VertexDeclarationPtr const VertexPositionNormalTexture::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
			VertexElement(12, VertexElementFormat::Vector3, VertexElementUsage::Normal, 0),
			VertexElement(0x18, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0)}));

	VertexDeclarationPtr const VertexPositionTexture::Declaration = New<VertexDeclaration>(
		NewVector<VertexElement>(std::initializer_list<VertexElement>{
		VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),			
			VertexElement(12, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0)}));

	VertexDeclaration::VertexDeclaration(intcs vertexStride, vectorptr<VertexElement> const& elements)
	{
		if (elements == nullptr || elements->empty())
			return; //TODO: lançar exceção?

		auto data = VertexDeclarationData(vertexStride, elements);

		data.Elements = NewVector<VertexElement>(elements->size());
		std::copy(data.Elements->begin(), data.Elements->end(), elements->begin());

		_data.Elements = elements;
	}	
}