#include "pch.h"
#include "TextWriter.h"


TextWriter::TextWriter(std::wstring text, DirectX::SimpleMath::Vector2 textPosition)
{
	m_output = text;
	m_textPosition = textPosition;
	m_textTint = DirectX::Colors::White.v;
}


TextWriter::~TextWriter()
{
}

void TextWriter::SetTintColour(DirectX::SimpleMath::Color color)
{
	this->m_textTint = color;
}

void TextWriter::Update(std::wstring newText) 
{
	m_output = newText;
}

void TextWriter::Render(std::shared_ptr<SpriteResources> resources)
{
	const wchar_t* myStr = m_output.c_str();
	resources->GetSpriteFont()->DrawString
	(resources->GetSpriteBatch().get()
		, myStr
		, m_textPosition
		, m_textTint
		, 0.f
		, DirectX::SimpleMath::Vector2(0.0f, 0.0f)
	);
}