#include "music_ovl_frame.hpp"

MusicOverlayFrame::MusicOverlayFrame(const std::string &title, const std::string &subtitle, const char **description)
    : Element(), m_title(title), m_subtitle(subtitle), m_description(description) {}

MusicOverlayFrame::~MusicOverlayFrame() {
    if (this->m_contentElement != nullptr)
        delete this->m_contentElement;
}

void MusicOverlayFrame::draw(tsl::gfx::Renderer *renderer) {
    renderer->fillScreen(a({0x0, 0x0, 0x0, 0xD}));

    renderer->drawString(this->m_title.c_str(), false, 20, 50, 30, a(0xFFFF));
    renderer->drawString(this->m_subtitle.c_str(), false, 20, 70, 15, a(0xFFFF));

    renderer->drawRect(15, 720 - 73, tsl::cfg::FramebufferWidth - 30, 1, a(0xFFFF));
    renderer->drawString(*this->m_description, false, 15, 693, 23, a(0xFFFF));

    if (this->m_contentElement != nullptr)
        this->m_contentElement->frame(renderer);
}

void MusicOverlayFrame::layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) {
    this->setBoundaries(parentX, parentY, parentWidth, parentHeight);

    if (this->m_contentElement != nullptr) {
        this->m_contentElement->setBoundaries(parentX + 10, parentY + 120, parentWidth - 20, parentHeight - 90 - 100);
        this->m_contentElement->invalidate();
    }
}

tsl::elm::Element *MusicOverlayFrame::requestFocus(tsl::elm::Element *oldFocus, tsl::FocusDirection direction) {
    if (this->m_contentElement != nullptr)
        return this->m_contentElement->requestFocus(oldFocus, direction);
    else
        return nullptr;
}

void MusicOverlayFrame::setContent(tsl::elm::Element *content) {
    if (this->m_contentElement != nullptr)
        delete this->m_contentElement;

    this->m_contentElement = content;

    if (content != nullptr) {
        this->m_contentElement->setParent(this);
        this->invalidate();
    }
}