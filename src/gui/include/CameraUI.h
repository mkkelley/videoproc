#pragma once

#include <functional>

#include "Camera.h"

class CameraUI : public View {
    public:
        CameraUI();
        /**
         * Calls stopCamera().
         */
        ~CameraUI();

        /**
         * Initialize the first camera on the system, and make it ready for its
         * getNext(Raw)Frame and all other functions. Idempotent.
         */
        void startCamera();
        /**
         * Delete the camera pointer, clean it up. Idempotent.
         */
        void stopCamera();

        virtual cv::Size getSize();
        virtual double getFps();
        virtual cv::Mat getNextRawFrame();
        virtual std::vector<cv::Mat> captureVideo(int frames);

        bool inline isCapturing() const {
            return _cam != nullptr;
        }

        template<class F>
        void afterStart(F&& f) {
            _afterStart = std::move(f);
        }
        template<class F>
        void afterStop(F&& f) {
            _afterStop = std::move(f);
        }
    protected:
        Camera* _cam;
        std::function<void()> _afterStart;
        std::function<void()> _afterStop;
};
