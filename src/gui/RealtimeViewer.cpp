#include "RealtimeViewer.h"

#include "MatView.h"

RealtimeViewer::RealtimeViewer()
    :_toggleButton(new QPushButton("Stop")),
    _layout(new QVBoxLayout()),
    _view(new MatView()),
    _cam(new Camera(0))
{
    auto f = _cam->getNextFrame();
    _view->setMat(f);
    _layout->addWidget(_view);
    _layout->addWidget(_toggleButton);
    setLayout(_layout);
}

void RealtimeViewer::handleToggleButton() {

}
