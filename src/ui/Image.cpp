#include "Image.h"
#include "Context.h"
#include "graphics/TextureBuilder.h"

namespace UI {

Image::Image(Context *context, const std::string &filename, StretchMode stretchMode): Widget(context),
	m_stretchMode(stretchMode)
{
	Graphics::TextureBuilder b = Graphics::TextureBuilder::UI(filename);
	m_quad.Reset(new Gui::TexturedQuad(b.GetOrCreateTexture(GetContext()->GetRenderer(), "ui")));

	const Graphics::TextureDescriptor &descriptor = b.GetDescriptor();
	m_initialSize = vector2f(descriptor.dataSize.x*descriptor.texSize.x,descriptor.dataSize.y*descriptor.texSize.y);
}

vector2f Image::PreferredSize()
{
    return m_initialSize;
}

void Image::Layout()
{
	vector2f size = GetSize();

	vector2f activeArea;

	switch (m_stretchMode) {
		case STRETCH_MAX:
			activeArea = size;
			break;

		case STRETCH_PRESERVE: {

			float originalRatio = m_initialSize.x / m_initialSize.y;
			float wantRatio = size.x / size.y;

			// more room on X than Y, use full X, scale Y
			if (wantRatio < originalRatio) {
				activeArea.x = size.x;
				activeArea.y = size.x / originalRatio;
			}

			// more room on Y than X, use full Y, scale X
			else {
				activeArea.x = size.y * originalRatio;
				activeArea.y = size.y;
			}

			break;
		}
		
		default:
			assert(0);
	}

	vector2f activeOffset(std::max(0.0f, (size.x-activeArea.x)/2.0f), std::max(0.0f, (size.y-activeArea.y)/2.0f));

	SetActiveArea(activeArea, activeOffset);
}

void Image::Draw()
{
	Graphics::Renderer *r = GetContext()->GetRenderer();
	r->SetBlendMode(Graphics::BLEND_ALPHA);
	m_quad->Draw(r, GetActiveOffset(), GetActiveArea());
}

}
