/**
 * \file main.cpp
 * \brief A simple scg3 example application.
 *
 * Requires C++11 and OpenGL 3.2 (or later versions).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014-2019 Volker Ahlers
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <scg3.h>

#include <chrono> // Neede for struct timer
#include "Timer.h"
//#include <iostream> Already included, see above


using namespace scg;


/**
 * \brief Configuration parameters.
 */
struct SCGConfiguration {
  static const int viewerType = 1;  // 0: simple, 1: customized
  // for customized viewer:
  static const int sceneType = 0;   // 0: teapot, 1: table
};

/**
 * \brief Custom timer
 */
/*struct Timer {
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::milliseconds milliseconds;

	void reset() { start = clock::now(); }

	unsigned long long milliseconds_elapsed() const
	{
		return std::chrono::duration_cast<milliseconds>(clock::now() - start).count();
	}

	private: clock::time_point start = clock::now();
};*/


/**
 * \brief Minimal application using a simple viewer with default renderer, shaders,
 *   camera, and light to create a teapot scene.
 */
void useSimpleViewer();


/**
 * \brief Typical application using a customized viewer to create a teapot or table scene.
 */
void useCustomizedViewer();


/**
 * \brief Create a scene consisting of a Raspberry PI, a camera, and a light.
 */
void createRaspberryPIScene(ViewerSP viewer, CameraSP camera, GroupSP& scene);


/**
 * \brief Create a scene consisting of a teapot, a camera, and a light.
 */
void createTeapotScene(ViewerSP viewer, CameraSP camera, GroupSP& scene);


/**
 * \brief Create a scene consisting of a floor, a table, a teapot, a camera, and a light.
 */
void createTableScene(ViewerSP viewer, CameraSP camera, GroupSP& scene);


/**
 * \brief The main function.
 */
int main() {

  int result = 0;

  try {
    if (SCGConfiguration::viewerType == 0) {
      useSimpleViewer();
    }
    else {
      useCustomizedViewer();
    }
  }
  catch (const std::exception& exc) {
    std::cerr << std::endl << "Exception: " << exc.what() << std::endl;
    result = 1;
  }
  return result;
}


// Minimal application using a simple viewer.
void useSimpleViewer() {

  // create viewer with default renderer, camera, and light
  auto viewer = Viewer::create();
  CameraSP camera;
  GroupSP scene;
  LightSP light;
  viewer->initSimpleRenderer(camera, scene, light);

  // define red material
  //auto matRed = MaterialCore::create();
  //matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
  //      ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
  //      ->setShininess(20.f)
  //      ->init();

  // add teapot shape to scene graph
  //GeometryCoreFactory geometryFactory;
  //auto teapot = Shape::create();
  //teapot->addCore(matRed)
  //      ->addCore(geometryFactory.createTeapot(1.f));
  //light->addChild(teapot);

  // define red material
  auto matPCB = MaterialCore::create();
  matPCB->setAmbientAndDiffuse(glm::vec4(0.027f, 0.341f, 0.f, 0.123f))
	  ->setSpecular(glm::vec4(0.005f, 0.068f, 0.f, 1.f))
	  //->setShininess(20.f)
	  ->init();

  // add Raspberry PI Zero PCB shape to scene graph
  GeometryCoreFactory geometryFactory;
  auto rasp_pcb = Shape::create();
  rasp_pcb->addCore(matPCB)
	  ->addCore(geometryFactory.createModelFromOBJFile("./models/raspberry_pi_pcb.obj"));
  light->addChild(rasp_pcb);

  // move camera backwards, enter main loop
  camera->translate(glm::vec3(0.f, 0.f, 1.f))
        ->dolly(-1.f);
  viewer->startMainLoop();
}


// Typical application using a customized viewer.
void useCustomizedViewer() {

  // create viewer and renderer
  auto viewer = Viewer::create();
  auto renderer = StandardRenderer::create();
  viewer->init(renderer)
        ->createWindow("s c g 3   e x a m p l e", 1024, 768);

  // create camera
  auto camera = PerspectiveCamera::create();
  renderer->setCamera(camera);

  // create scene
  GroupSP scene;
  switch (SCGConfiguration::sceneType) {
  case 0:
    createRaspberryPIScene(viewer, camera, scene);
    break;
  case 1:
    createTableScene(viewer, camera, scene);
    break;
  default:
    throw std::runtime_error("Invalid value of SCGConfiguration::sceneType [main()]");
  }
  renderer->setScene(scene);

  // start animations, enter main loop
  viewer->startAnimations()
        ->startMainLoop();
}

void createRaspberryPIScene(ViewerSP viewer, CameraSP camera, GroupSP& scene) {

	ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders");

#ifdef SCG_CPP11_INITIALIZER_LISTS
	// Phong shader
	auto shaderPhong = shaderFactory.createShaderFromSourceFiles(
		{
		  ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
		  ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
		  ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
		  ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
		});

	// Phong shader with texture mapping
	auto shaderPhongTex = shaderFactory.createShaderFromSourceFiles(
		{
		  ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
		  ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
		  ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
		  ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
		});
#else
	// Phong shader
	std::vector<ShaderFile> shaderFiles;
	shaderFiles.push_back(ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER));
	shaderFiles.push_back(ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER));
	shaderFiles.push_back(ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER));
	shaderFiles.push_back(ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER));
	auto shaderPhong = shaderFactory.createShaderFromSourceFiles(shaderFiles);

	// Phong shader with texture mapping
	shaderFiles.clear();
	shaderFiles.push_back(ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER));
	shaderFiles.push_back(ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER));
	shaderFiles.push_back(ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER));
	shaderFiles.push_back(ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER));
	auto shaderPhongTex = shaderFactory.createShaderFromSourceFiles(shaderFiles);
#endif

	// camera controllers
	camera->translate(glm::vec3(0.f, 0.f, 1.f))
		->dolly(-1.f);
#ifdef SCG_CPP11_INITIALIZER_LISTS
	viewer->addControllers(
		{
		  KeyboardController::create(camera),
		  MouseController::create(camera)
		});
#else
	viewer->addController(KeyboardController::create(camera))
		->addController(MouseController::create(camera));
#endif

	auto cameraTrans = TransformAnimation::create();
	// Create Timer
	auto ctimer = Timer::create();
	cameraTrans->setUpdateFunc(
		[ctimer, camera](TransformAnimation * animation, double currTime, double diffTime, double totalTime) {
			if (ctimer->milliseconds_elapsed() > 10) {
				camera->rotateAzimuth(1.f);
				ctimer->reset();
			}
		}
	);
	viewer->addAnimation(cameraTrans);

	// white point light at position (10,10,10)
	auto light = Light::create();
	light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
		->setPosition(glm::vec4(10.f, 10.f, 10.f, 1.f))
		->init();

	// define PCB material
	auto matPCB = MaterialCore::create();
	matPCB->setAmbientAndDiffuse(glm::vec4(0.027f, 0.341f, 0.f, 0.123f))
		->setSpecular(glm::vec4(0.005f, 0.068f, 0.f, 1.f))
		//->setShininess(20.f)
		->init();

	// define PCB holes material
	auto matPCBHoles = MaterialCore::create();
	matPCBHoles->setAmbientAndDiffuse(glm::vec4(1.f, 0.808f, 0.498f, 0.769f))
		->setSpecular(glm::vec4(0.800f, 0.646f, 0.398f, 1.f))
		//->setShininess(20.f)
		->init();

	// define PCB pin holes material
	auto matPCBPinHoles = MaterialCore::create();
	matPCBPinHoles->setAmbientAndDiffuse(glm::vec4(0.965f, 0.875f, 0.600f, 0.813f))
		->setSpecular(glm::vec4(0.675f, 0.612f, 0.420f, 1.f))
		//->setShininess(20.f)
		->init();

	// define PCB pin pair material
	auto matPCBPinPair = MaterialCore::create();
	matPCBPinPair->setAmbientAndDiffuse(glm::vec4(0.667f, 0.698f, 0.769f, 0.711f))
		->setSpecular(glm::vec4(0.333f, 0.349f, 0.384f, 1.f))
		//->setShininess(20.f)
		->init();

	// define Raspberry PI Zero PCB textures
	TextureCoreFactory textureFactory("../scg3/textures;../../scg3/textures");
	auto texPCBRasp = textureFactory.create2DTextureFromFile(
		"rasp_pcb_front.jpg", GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR);

	GeometryCoreFactory geometryFactory;
	// add Raspberry PI Zero PCB shape to scene graph
	auto rasp_pcb = Shape::create();
	rasp_pcb
		->addCore(shaderPhongTex)
		->addCore(matPCB)
		->addCore(geometryFactory.createModelFromOBJFile("./models/rasp_zero_pcb_base_v2.obj"))
		->addCore(texPCBRasp);
	// raspPCB transformation
	auto rasp_pcbTrans = Transformation::create();
	rasp_pcbTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
	// add Raspberry PI Zero PCB Holes shape to scene graph
	auto rasp_pcbholes = Shape::create();
	rasp_pcbholes->addCore(matPCBHoles)
		->addCore(geometryFactory.createModelFromOBJFile("./models/rasp_zero_pcb_mountholes_v2.obj"));
	// raspPCBHoles transformation
	auto rasp_pcbHolesTrans = Transformation::create();
	rasp_pcbHolesTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
	// add Raspberry PI Zero PCB Pin Holes shape to scene graph
	auto rasp_pcbpinholes = Shape::create();
	rasp_pcbpinholes->addCore(matPCBPinHoles)
		->addCore(geometryFactory.createModelFromOBJFile("./models/rasp_zero_pcb_pinholes_v2.obj"));
	// raspPCBHoles transformation
	auto rasp_pcbPinHolesTrans = Transformation::create();
	rasp_pcbPinHolesTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
	// add Raspberry PI Zero Pin Pair shape to scene graph
	auto rasp_pcbpinpair = Shape::create();
	rasp_pcbpinpair->addCore(matPCBPinPair)
		->addCore(geometryFactory.createModelFromOBJFile("./models/rasp_zero_pcb_pinpair_v2.obj"));
	// raspPCBHoles transformation
	auto rasp_pcbPinPairTrans = Transformation::create();
	rasp_pcbPinPairTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));

	// create scene graph
	scene = Group::create();
	scene->addCore(shaderPhong);
	scene->addChild(camera)
		->addChild(light);
	light->addChild(rasp_pcbTrans)
		->addChild(rasp_pcbHolesTrans)
		->addChild(rasp_pcbPinHolesTrans)
		->addChild(rasp_pcbPinPairTrans);
	rasp_pcbTrans->addChild(rasp_pcb);
	rasp_pcbHolesTrans->addChild(rasp_pcbholes);
	rasp_pcbPinHolesTrans->addChild(rasp_pcbpinholes);
	rasp_pcbPinPairTrans->addChild(rasp_pcbpinpair);

	// Rotate camera at Azimuth
	//Timer t;
	/*while (true) {
		if (t.milliseconds_elapsed() > 1000) {
			camera->rotateAzimuth(1.f);
			t.reset();
		}
	}*/
}


void createTeapotScene(ViewerSP viewer, CameraSP camera, GroupSP& scene) {

  ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders");

#ifdef SCG_CPP11_INITIALIZER_LISTS
  // Gouraud shader
  auto shaderGouraud = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("simple_gouraud_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("simple_gouraud_frag.glsl", GL_FRAGMENT_SHADER)
      });
#else
  std::vector<ShaderFile> shaderFiles;
  shaderFiles.push_back(ShaderFile("simple_gouraud_vert.glsl", GL_VERTEX_SHADER));
  shaderFiles.push_back(ShaderFile("simple_gouraud_frag.glsl", GL_FRAGMENT_SHADER));
  auto shaderGouraud = shaderFactory.createShaderFromSourceFiles(shaderFiles);
#endif

  // camera controllers
  camera->translate(glm::vec3(0.f, 0.f, 1.f))
        ->dolly(-1.f);
#ifdef SCG_CPP11_INITIALIZER_LISTS
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });
#else
  viewer->addController(KeyboardController::create(camera))
      ->addController(MouseController::create(camera));
#endif

  // white point light at position (10,10,10)
  auto light = Light::create();
  light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
       ->setPosition(glm::vec4(10.f, 10.f, 10.f, 1.f))
       ->init();

  // red material
  auto matRed = MaterialCore::create();
  matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  // teapot shape
  GeometryCoreFactory geometryFactory;
  auto teapotCore = geometryFactory.createTeapot(1.f);
  auto teapot = Shape::create();
  teapot->addCore(matRed)
        ->addCore(teapotCore);

  // teapot transformation
  auto teapotTrans = Transformation::create();
  teapotTrans->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));

  // create scene graph
  scene = Group::create();
  scene->addCore(shaderGouraud);
  scene->addChild(camera)
       ->addChild(light);
  light->addChild(teapotTrans);
  teapotTrans->addChild(teapot);
}


void createTableScene(ViewerSP viewer, CameraSP camera, GroupSP& scene) {

  ShaderCoreFactory shaderFactory("../scg3/shaders;../../scg3/shaders");

#ifdef SCG_CPP11_INITIALIZER_LISTS
  // Phong shader
  auto shaderPhong = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER)
      });

  // Phong shader with texture mapping
  auto shaderPhongTex = shaderFactory.createShaderFromSourceFiles(
      {
        ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER),
        ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER),
        ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER)
      });
#else
  // Phong shader
  std::vector<ShaderFile> shaderFiles;
  shaderFiles.push_back(ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER));
  shaderFiles.push_back(ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER));
  shaderFiles.push_back(ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER));
  shaderFiles.push_back(ShaderFile("texture_none.glsl", GL_FRAGMENT_SHADER));
  auto shaderPhong = shaderFactory.createShaderFromSourceFiles(shaderFiles);

  // Phong shader with texture mapping
  shaderFiles.clear();
  shaderFiles.push_back(ShaderFile("phong_vert.glsl", GL_VERTEX_SHADER));
  shaderFiles.push_back(ShaderFile("phong_frag.glsl", GL_FRAGMENT_SHADER));
  shaderFiles.push_back(ShaderFile("blinn_phong_lighting.glsl", GL_FRAGMENT_SHADER));
  shaderFiles.push_back(ShaderFile("texture2d_modulate.glsl", GL_FRAGMENT_SHADER));
  auto shaderPhongTex = shaderFactory.createShaderFromSourceFiles(shaderFiles);
#endif

  // camera controllers
  camera->translate(glm::vec3(0.f, 0.5f, 1.f))
        ->dolly(-1.f);
#ifdef SCG_CPP11_INITIALIZER_LISTS
  viewer->addControllers(
      {
        KeyboardController::create(camera),
        MouseController::create(camera)
      });
#else
  viewer->addController(KeyboardController::create(camera))
        ->addController(MouseController::create(camera));
#endif

  // lights
  auto light = Light::create();
  light->setDiffuseAndSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
       ->setPosition(glm::vec4(10.f, 10.f, 10.f, 1.f))
       ->init();

  // materials
  auto matRed = MaterialCore::create();
  matRed->setAmbientAndDiffuse(glm::vec4(1.f, 0.5f, 0.5f, 1.f))
        ->setSpecular(glm::vec4(1.f, 1.f, 1.f, 1.f))
        ->setShininess(20.f)
        ->init();

  auto matGreen = MaterialCore::create();
  matGreen->setAmbientAndDiffuse(glm::vec4(0.1f, 0.8f, 0.3f, 1.f))
          ->init();

  auto matWhite = MaterialCore::create();
  matWhite->setAmbientAndDiffuse(glm::vec4(1.f, 1.f, 1.f, 1.f))
          ->setSpecular(glm::vec4(0.5f, 0.5f, 0.5f, 1.f))
          ->setShininess(20.f)
          ->init();

  // textures
  TextureCoreFactory textureFactory("../scg3/textures;../../scg3/textures");
  auto texWood = textureFactory.create2DTextureFromFile(
      "wood_256.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  // set texture matrix
//  texWood->scale2D(glm::vec2(4.f, 4.f));

  // floor shape and transformation
  GeometryCoreFactory geometryFactory;
  auto floorCore = geometryFactory.createCuboid(glm::vec3(20.f, 0.05f, 10.f));
  auto floor = Shape::create();
  floor->addCore(matGreen)
       ->addCore(floorCore);
  auto floorTrans = Transformation::create();
  floorTrans->translate(glm::vec3(0.f, -0.5f, 0.f));

  // teapot shape and transformation
  auto teapotCore = geometryFactory.createTeapot(0.35f);
  auto teapot = Shape::create();
  teapot->addCore(matRed)
        ->addCore(teapotCore);
  auto teapotTrans = Transformation::create();
  teapotTrans->translate(glm::vec3(0.f, 0.9f, 0.f))
             ->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));

  // table group and transformation
  auto table = Group::create();
  table->addCore(shaderPhongTex)
       ->addCore(matWhite)
       ->addCore(texWood);
  auto tableTrans = Transformation::create();
  tableTrans->rotate(30.f, glm::vec3(0.f, 1.f, 0.f));

  auto tableTop = Shape::create(geometryFactory.createCuboid(glm::vec3(1.5f, 0.05f, 1.f)));
  auto tableTopTrans = Transformation::create();
  tableTopTrans->translate(glm::vec3(0.f, 0.5f, 0.f));
  table->addChild(tableTopTrans);
  tableTopTrans->addChild(tableTop);

  auto tableLegCore = geometryFactory.createCuboid(glm::vec3(0.1f, 1.f, 0.1f));
  ShapeSP tableLeg[4];
  TransformationSP tableLegTrans[4];
  for (int i = 0; i < 4; ++i) {
    tableLeg[i] = Shape::create(tableLegCore);
    tableLegTrans[i] = Transformation::create();
    table->addChild(tableLegTrans[i]);
    tableLegTrans[i]->addChild(tableLeg[i]);
  }
  tableLegTrans[0]->translate(glm::vec3( 0.6f, 0.f,  0.35f));
  tableLegTrans[1]->translate(glm::vec3( 0.6f, 0.f, -0.35f));
  tableLegTrans[2]->translate(glm::vec3(-0.6f, 0.f, -0.35f));
  tableLegTrans[3]->translate(glm::vec3(-0.6f, 0.f,  0.35f));

  // create scene graph
  scene = Group::create();
  scene->addCore(shaderPhong);
  scene->addChild(camera)
       ->addChild(light);
  light->addChild(floorTrans)
       ->addChild(tableTrans);
  floorTrans->addChild(floor);
  tableTrans->addChild(table)
            ->addChild(teapotTrans);
  teapotTrans->addChild(teapot);
}
