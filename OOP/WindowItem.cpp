#include "WindowItem.h"

WindowItem::WindowItem(string texturePath, RenderWindow* window) {
    this->window = window;
    if(!texture.loadFromFile(texturePath)) printf("texture loading error!\n");
    sprite.setTexture(texture);
}

void WindowItem::render() {
    window->draw(sprite);
}