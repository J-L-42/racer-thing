/*
 * Camera.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_ENTITIES_CAMERA_HPP_
#define MAIN_ENTITIES_CAMERA_HPP_


#include "../Util/ExtraMath.hpp"
#include "Cars/Car.hpp"

class Camera {
private:
    float x, y;
    int viewWidth, viewHeight;
    float xBound, yBound;
    Car* focus;
public:
    Camera(float x, float y, int viewWidth, int viewHeight, float xBound, float yBound, Car* focus);

    void update(float delta);
    void setFocus(Car* focus);
    void setView(int viewWidth, int viewHeight);
    void setBounds(float xBound, float yBound);
    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline float getXBound() const { return xBound; }
    inline float getYBound() const { return yBound; }
    inline int getViewWidth() const { return viewWidth; }
    inline int getViewHeight() const { return viewHeight; }
    inline Car* getFocus() const { return focus; }

    ~Camera();
};


#endif /* MAIN_ENTITIES_CAMERA_HPP_ */
