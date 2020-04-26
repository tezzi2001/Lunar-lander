#include "Dispatcher.h"

vector<Font*> fontGarbage;
vector<Text*> textGarbage;

int main() {
    Configuration cfg = Configuration::getInstance("Resources/global.cfg");

    ContextSettings settings;
    settings.antialiasingLevel = cfg.getAntialiasingLevel();
    RenderWindow window(VideoMode(cfg.getWidth(), cfg.getHeight()), cfg.getAppName(), Style::Fullscreen, settings);
    Image icon;
    icon.loadFromFile(cfg.getIconPath());
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Dispatcher dispatcher = Dispatcher::getInstance(&cfg, window);
    dispatcher.start(window);

    for (Font* font : fontGarbage) {
        if (font) delete font;
    }
    for (Text* text : textGarbage) {
        if (text) delete text;
    }

    return 0;
}