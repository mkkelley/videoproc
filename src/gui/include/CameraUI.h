#pragma once

#include <QWidget>
#include "Camera.h"

class CameraUI : public QWidget {
    Q_OBJECT;
    public:
        /**
         * Calls stopCamera().
         */
        virtual ~CameraUI();
    protected:
        CameraUI(QWidget* parent = nullptr);
        /**
         * Initialize the first camera on the system, and make it ready for its
         * getNext(Raw)Frame and all other functions. Idempotent.
         */
        void startCamera();
        /**
         * Delete the camera pointer, clean it up. Idempotent.
         */
        void stopCamera();
        virtual void afterStart() {};
        virtual void afterStop() {};

        bool inline isCapturing() const {
            return _cam != nullptr;
        }

        Camera* _cam;
};
