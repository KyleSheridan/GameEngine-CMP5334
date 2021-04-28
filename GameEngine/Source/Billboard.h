#pragma once
#include "Texture.h"

namespace GE {
    class Billboard {
    public:
        Billboard(Texture* t) {
            billTex = t;

            x = y = z = 0.0f;

            scaleX = scaleY = scaleZ = 1.0f;
        }

        ~Billboard() {}

        float getX() {
            return x;
        }
        float getY() {
            return y;
        }
        float getZ() {
            return z;
        }

        void setX(float val) {
            x = val;
        }
        void setY(float val) {
            y = val;
        }
        void setZ(float val) {
            z = val;
        }

        Texture* getTexture() {
            return billTex;
        }

        float getScaleX() {
            return scaleX;
        }
        float getScaleY() {
            return scaleY;
        }

        void setScaleX(float val) {
            scaleX = val;
        }
        void setScaleY(float val) {
            scaleY = val;
        }

    private:
        float x, y, z;

        float scaleX, scaleY, scaleZ;

        Texture* billTex;
    };
}