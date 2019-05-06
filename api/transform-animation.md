# TransformAnimation

An animation that creates a transformation to be applied to ist sub-tree (composite node)

## Class: TransformAnimation

## create()

* `return` {TransformAnimationSP}

Create shared pointer

## getFloatParam()

* `return` {GLfloat}

Get parameter

## setFloatParam(param)

* `param` {GLfloat}
* `return` {[TransformAnimation][]*}  This pointer for method chaining

Set parameter to be used by animation function

## setVec3Param(param)

* `param` {glm::vec3&}
* `return` {[TransformAnimation][]*}  This pointer for method chaining

Set parameter to be used by animation function

## getMat4Param()

* `return` {glm::mat4&}

Get parameter.

## setMat4Param(param)

* `param` {glm::mat4&}
* `return` {[TransformAnimation][]*}  This pointer for method chaining

Set parameter to be used by animation function

## setStartFunc(startFunc)

* `startFunc` {std::function<void([TransformAnimation][]\*)>} Function object with signature void f([TransformAnimation][]*).
* `return` {[TransformAnimation][]*}  This pointer for method chaining

Set start function f_start that is called when the animation is started as f(this)

## setUpdateFunc(updateFunc)

* `updateFunc` {std::function<void([TransformAnimation][]\*, double, double, double)> Function object with signature void f([TransformAnimation][]*, double, double, double)
* `return` {[TransformAnimation][]*}  This pointer for method chaining

Set update function that is called when the animation is updated as f(this, currTime, diffTime, totalTime) (cf. Animation)

## start(currTime)

* `currTime` {double} --- Current time (seconds)

Start or restart animation with given time, call start function (if defined)

## update(currTime)

* `currTime` {double} --- Current time (seconds)

Update animation with given time, call update function (if defined)

<br>

## Example

```cpp
auto myAnimation = TransformAnimation::create();
float angularVel = 50.f;
glm::vec3 axis(1.f, 0.f, 0.f);
myAnimation->setUpdateFunc(
     [angularVel, axis](TransformAnimation* animation, double currTime, double diffTime, double totalTime) {
       animation->rotate(angularVel * static_cast<GLfloat>(diffTime), axis);
});

aNode->addChild(myAnimation);
myAnimation->addChild(anotherNode);

myViewer.addAnimation(myAnimation);
myViewer.startAnimations();
```

[TransformAnimation]: https://github.com/VoltanaDMG/scg3_v2019/blob/v2019.x/scg3/doc/api/transform-animation.md