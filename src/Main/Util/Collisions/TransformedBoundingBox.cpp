#include "TransformedBoundingBox.hpp"

void TransformedBoundingBox::initPoints(const sf::Transformable* object, int offsetX, int offsetY, int width, int height) {
    sf::Transform trans = object->getTransform();
    points[0] = trans.transformPoint(offsetX, offsetY);
    points[1] = trans.transformPoint(offsetX + width, offsetY);
    points[2] = trans.transformPoint(offsetX + width, offsetY + height);
    points[3] = trans.transformPoint(offsetX, offsetY + height);
}

void TransformedBoundingBox::project(const sf::Vector2f& axis, float& min, float& max) {
    min = (points[0].x * axis.x + points[0].y * axis.y);
    max = min;
    for (int i = 1; i < 4; i++) {
        float projection = (points[i].x * axis.x + points[i].y * axis.y);

        if (projection < min)
            min = projection;
        if (projection > max)
            max = projection;
    }
}

bool intersects(const sf::Transformable* self, int selfWidth, int selfHeight, const sf::Transformable* other,
        int otherWidth, int otherHeight, int selfOffsetX, int selfOffsetY, int otherOffsetX, int otherOffsetY) {
    TransformedBoundingBox boxSelf;
    TransformedBoundingBox boxOther;
    boxSelf.initPoints(self, selfOffsetX, selfOffsetY, selfWidth, selfHeight);
    boxOther.initPoints(other, otherOffsetX, otherOffsetY, otherWidth, otherHeight);

    sf::Vector2f axes[4] = {
        sf::Vector2f (boxSelf.points[1].x - boxSelf.points[0].x,
                boxSelf.points[1].y - boxSelf.points[0].y),

        sf::Vector2f (boxSelf.points[1].x - boxSelf.points[2].x,
                boxSelf.points[1].y - boxSelf.points[2].y),

        sf::Vector2f (boxOther.points[0].x - boxOther.points[3].x,
                boxOther.points[0].y - boxOther.points[3].y),

        sf::Vector2f (boxOther.points[0].x - boxOther.points[1].x,
                boxOther.points[0].y - boxOther.points[1].y)
    };

    for (int i = 0; i < 4; i++) {
        float selfMin, selfMax, otherMin, otherMax;

        boxSelf.project(axes[i], selfMin, selfMax);
        boxOther.project(axes[i], otherMin, otherMax);

        if (!(otherMin <= selfMax && otherMax >= selfMin))
            return false;
    }
    return true;
}
