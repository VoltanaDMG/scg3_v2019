# CameraController

Base class for all camera controllers, acting on a Camera node (abstract)

## Class: CameraController

Base class for all camera controllers, acting on a Camera node (abstract).

A typical CameraController offers actions for camera movement and rotation, and potentially for continuous flight of camera. It may further be possible to toggle between fly mode (free camera movement in space) and examine mode (camera movement relative to center point).

## CameraController(camera)

* `camera` {CameraSP}

Constructor with given camera transformation

## setCamera(camera)

* `camera` {CameraSP}

Set camera transformation to act on

## setMoveVelocity(moveVelocity)

* `moveVelocity` {GLfloat}

Set velocity for camera movement

## setRotateVelocity(rotateVelocity)

* `rotateVelocity` {GLfloat}

Set velocity for camera rotation

## setFlightVelocity(flightVelocity)

* `flightVelocity` {GLfloat}

Set velocity for continuous flight of camera

## setFlightVelocityStep(flightVelocityStep)

* `flightVelocityStep`

Set step for changing flight velocity

## checkInput(viewState)

* `viewState` {[ViewState][]*} View state managed by Viewer, may be modified by controller

Check input devices, called by Viewer::startMainLoop()


[ViewState]: https://github.com/VoltanaDMG/scg3_v2019/blob/master/scg3/doc/api/view-state.md