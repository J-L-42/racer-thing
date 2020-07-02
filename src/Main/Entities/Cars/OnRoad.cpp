/*
 * OnRoad.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: james
 */

#include "OnRoad.hpp"

OnRoad::OnRoad(float x, float y, sf::Texture* image) : Car(x, y, image) {
    offsetX = 0;
    offsetY = 0;
    prevOffsetX = 0;
    prevOffsetY = 0;

    targetRotation = 0;

    currentNode = nullptr;
    prevNode = nullptr;
}

void OnRoad::findOffsets(float delta) {
    if (targetRotation <= 10 || targetRotation >= 350) {
        if (offsetX > 0)
            offsetX -= offsetSpeed * delta;
        if (offsetX < 0)
            offsetX += offsetSpeed * delta;
        if (offsetY < 80)
            offsetY += offsetSpeed * delta;
    }
    if (targetRotation >= 80 && targetRotation <= 100) {
        if (offsetX > -80)
            offsetX -= offsetSpeed * delta;
        if (offsetY > 0)
            offsetY -= offsetSpeed * delta;
        if (offsetY < 0)
            offsetY += offsetSpeed * delta;
    }
    if (targetRotation >= 170 && targetRotation <= 190) {
        if (offsetX > 0)
            offsetX -= offsetSpeed * delta;
        if (offsetX < 0)
            offsetX += offsetSpeed * delta;
        if (offsetY > -80)
            offsetY -= offsetSpeed * delta;
    }
    if (targetRotation >= 260 && targetRotation <= 280) {
        if (offsetX < 80)
            offsetX += offsetSpeed * delta;
        if (offsetY > 0)
            offsetY -= offsetSpeed * delta;
        if (offsetY < 0)
            offsetY += offsetSpeed * delta;
    }
}

void OnRoad::setCurrentNode(Tile* node) {
    currentNode = node;
}

void OnRoad::setNodes(ArrayList<Tile*> nodes) {
    this->nodes = nodes;
}

OnRoad::~OnRoad() {
    nodes.clear();
}
