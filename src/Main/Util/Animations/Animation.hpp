#ifndef MAIN_UTIL_ANIMATION_HPP_
#define MAIN_UTIL_ANIMATION_HPP_


#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation {
private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture* m_texture;
public:
    Animation();

    void addFrame(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    std::size_t getSize() const;
    const sf::IntRect& getFrame(std::size_t n) const;
};


#endif /* MAIN_UTIL_ANIMATION_HPP_ */
