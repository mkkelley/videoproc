#pragma once

#include <QWidget>
#include "Camera.h"

class CameraUI : public QWidget {
    Q_OBJECT
    public:
        virtual ~CameraUI();
    protected:
        CameraUI(QWidget* parent = nullptr);
        void stopCamera();
        void startCamera();
        virtual void afterStart() {};
        virtual void afterStop() {};

        Camera* _cam;
        bool _capturing;
};
