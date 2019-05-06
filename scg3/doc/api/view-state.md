# ViewState

The view state of the application, managed by Viewer and accessible by Controller::checkInput() (or derived classes).

## Class: ViewState

The view state of the application, managed by Viewer and accessible by Controller::checkInput() (or derived classes).

## getWindow()

* `return` {GLFWwindow*}

Get window pointer, called by camera controllers

## setWindow(window)

* `window` {GLFWwindow}

Set window pointer

## isMouseCursorVisible()

* `return` {bool}

Check mouse cursor visibility

## setMouseCursorVisible(isVisible)

* `isVisible` {bool}

Set mouse cursor visibility (default: true/visible)

## isAnimationLocked()

* `return` {bool}

Check locked state of animations

## setAnimationLocked(isLocked)

* `isLocked` {bool}

Set locked state of animations (default: false/unlocked)

## isFrameRateOutput()

* `return` {bool}

Check frame output mode

## setFrameRateOutput(isOutput)

* `isOutput` {bool}

Set frame output mode (default: false/disabled)

## setFrameRateInterval(intervalSec)

* `intervalSec` {double} Interval (seconds) for frame rate computation; 0 deactivates frame rate computation

Set interval for frame rate computation (default: 3 sec)

## getFrameRate()

* `return` {double}

Get current frame rate (FPS)

## updateFrameRate()

Update frame rate, called by [Viewer][]::startMainLoop()


[Viewer]: https://github.com/VoltanaDMG/scg3_v2019/blob/v2019.x/scg3/doc/api/viewer.md