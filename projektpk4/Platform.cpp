#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Platform.h"

}

}

}

}

void Platform::setColor(const sf::Color& color) { rect.setFillColor(color); }
void Platform::setMarginBottom(float margin) { marginBottom = margin; }
void Platform::setStretchFullWidth(bool stretch) { stretchFullWidth = stretch; }