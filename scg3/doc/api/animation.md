# Animation

The `Animation` module provides the base class for all animations (abstract), providing general functionality.

## Class: Animation

Base class for all animations (abstract), providing general functionality.

## isStarted()

* `return` {bool}

Check if animation has been started at least once.

## isRunning()

* `return` {bool}

Check if animation is running.

## start(currTime)

* `currTime` {double} --- Current time (seconds)

Start or restart animation with given time.
> Note: This method must also be called by derived methods.

## stop()

Stop or pause animation.
> Note: This method must also be called by derived methods.

## reset()

Reset animation, i.e., set all variables to their initial states.
> Note: This method must also be called by derived methods.

## update(currTime)

* `currTime` {double} --- Current time (seconds)

Update animation with given time.
> Note: This method must also be called by derived methods.