#include "Core.h"
#include "System.h"
#include "DependentClear.h"
#include "ccollisionutils.h"

int main()
{
	//////////////////////////////////////////////////////////////////
	////Loads core files in for game processes
	coreLoad(Window);
	coreLoad(Time);
	coreLoad(Input);
	coreLoad(Camera);
	coreLoad(Factory);
	coreLoad(Asset);
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	////Loads system files in
	systemLoad(TransformUpdate);
	systemLoad(Rendering);
	systemLoad(textRenderSys);
	systemLoad(trafficSys);
	systemLoad(collisionPrep);
	systemLoad(CollisionDetection);
	systemLoad(StaticCollision);
	systemLoad(collisionResponse);
	systemLoad(RigidbodyDynamics);
	systemLoad(TankDynamics);
	systemLoad(LifeTimeDynamics);
	systemLoad(collisionRender);
	//////////////////////////////////////////////////////////////////
	
	initCore();//Main Game Loop
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	////////Files Loaded in for textures and shaders files
	///Shaders
	core(Asset).loadShader("Flat", "./shaders/simpleShader.vert", "./shaders/simpleShader.frag");
	core(Asset).loadShader("Texture", "./shaders/simpleShader.vert", "./shaders/textureShader.frag");
	core(Asset).loadShader("FontShader", "./shaders/simpleShader.vert", "./shaders/fontShader.frag");
	///Texture Files
	//Track
	core(Asset).loadTexture("Track", "./texture/Track.png");
	//Car Images
	core(Asset).loadTexture("Car1texture", "./texture/car.png");
	core(Asset).loadTexture("Car2texture", "./texture/car2.png");
	core(Asset).loadTexture("Car1Turret", "./texture/carTank.png");
	core(Asset).loadTexture("Car2Turret", "./texture/car2Tank.png");
	//Animations
	core(Asset).loadTexture("Walking", "./texture/WalkingAnimation.png", 4, 6);
	core(Asset).loadTexture("Raka", "./texture/Raka.png", 2, 5);
	core(Asset).loadTexture("Garren", "./texture/GARREN.bmp", 10, 12);
	core(Asset).loadTexture("Draven", "./texture/SPINNERS.bmp", 4, 4);
	core(Asset).loadTexture("Milk", "./texture/CANTMILK.bmp", 4, 6);
	core(Asset).loadTexture("Font", "./texture/font2.png", 8, 16);
	core(Asset).loadTexture("Light", "./texture/trafficLight.png", 1, 3);
	core(Asset).loadTexture("Flag", "./texture/FLAG.bmp", 2, 2);

	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////Vertex for game objects
	///Font
	Vertex font_vertexQ[4] = {  { {-.5, .5, 0, 1 }, { 0, 1, 1, 0 }, { 0, 0 } },
								{ { .5, .5, 0, 1 }, { 0, 1, 1, 0 }, { 1, 0 } },
								{ { .5,-.5, 0, 1 }, { 0, 1, 1, 0 }, { 1, 1 } },
								{ {-.5,-.5, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1 } } };

	///Walking
	Vertex Animation_vertQ[4] = { { { core(Window).width() / 2, core(Window).height() / 2, 0, 1 }, { 0, 1, 1, 0 }, { 0, 0 } },
							      { {                        0, core(Window).height() / 2, 0, 1 }, { 0, 1, 1, 0 }, { 1, 0 } },
								  { {                        0,							0, 0, 1 }, { 0, 1, 1, 0 }, { 1, 1 } },
								  { { core(Window).width() / 2,							0, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1 } } };

	///Track
	Vertex Track_vertQ[4] = { { { core(Window).width(), core(Window).height(), 0, 1 }, { 0, 1, 1, 0 }, { 0, 0 } },
							  { {					 0, core(Window).height(), 0, 1 }, { 0, 1, 1, 0 }, { 1, 0 } },
							  { {					 0,						0, 0, 1 }, { 0, 1, 1, 0 }, { 1, 1 } },
							  { { core(Window).width(),					    0, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1 } } };

	///Car
	Vertex Car_vertexQ[4] = { { { -15, 30, 0, 1 }, { 0, 1, 1, 0 }, { 0, 0 } },
	{ { 15, 30, 0, 1 }, { 0, 1, 1, 0 }, { 1, 0 } },
							   { { 15, -30, 0, 1 }, { 0, 1, 1, 0 }, { 1, 1 } },
							   { {-15,-30, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1 } } };

	///Turret
	Vertex Turret[4] = { { {-10, 10, 0, 1 }, { 1, 0, 1, 0 }, { 0, 0 } },
						 { { 10, 10, 0, 1 }, { 0, 1, 0, 1 }, { 1, 0 } },
						 { { 10,-10, 0, 1 }, { 1, 0, 1, 0 }, { 1, 1 } },
						 { {-10,-10, 0, 1 }, { 0, 1, 0, 1 }, { 0, 1 } } };

	///Bullet
	Vertex Bullet[4] = { { {-5, 5, 0, 1 }, { 1, 0, 1, 0 }, { 0, 0 } },
						 { { 5, 5, 0, 1 }, { 0, 1, 0, 1 }, { 1, 0 } },
						 { { 5,-5, 0, 1 }, { 1, 0, 1, 0 }, { 1, 1 } },
						 { {-5,-5, 0, 1 }, { 0, 1, 0, 1 }, { 0, 1 } } };

	///Light
	Vertex Light[4] = { { { -30, 70, 0, 1 }, { 1, 0, 1, 0 }, { 0, 0 } },
						{ { 30, 70, 0, 1 }, { 0, 1, 0, 1 }, { 1, 0 } },
						{ { 30, -70, 0, 1 }, { 1, 0, 1, 0 }, { 1, 1 } },
						{ { -30, -70, 0, 1 }, { 0, 1, 0, 1 }, { 0, 1 } } };

	///Flag
	Vertex Flag[4] = {  { {-290, 170, 0, 1 }, { 1, 0, 1, 0 }, { 0, 0 } },
						{ { 290, 170, 0, 1 }, { 0, 1, 0, 1 }, { 1, 0 } },
						{ { 290,-170, 0, 1 }, { 1, 0, 1, 0 }, { 1, 1 } },
						{ {-290,-170, 0, 1 }, { 0, 1, 0, 1 }, { 0, 1 } } };
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	///////Triangles for objects
	///font
	Triangle quad[2] = { { 0, 1, 2 }, { 0, 2, 3 } };

	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	
	//////Meshes
	core(Asset).loadMesh("Bullet", Bullet, 4, quad, 2);
	core(Asset).loadMesh("Turret", Turret, 4, quad, 2);
	core(Asset).loadMesh("Car", Car_vertexQ, 4, quad, 2);
	core(Asset).loadMesh("Anime", Animation_vertQ, 4, quad, 2);
	core(Asset).loadMesh("Quad", font_vertexQ, 4, quad, 2);
	core(Asset).loadMesh("TrackMesh", Track_vertQ, 4, quad, 2);
	core(Asset).loadMesh("lightMesh", Light, 4, quad, 2);
	core(Asset).loadMesh("flagMesh", Flag, 4, quad, 2);
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	//////Factory Entities Loading in
	////BackGround
	core(Factory).makeBG(0, 0);

	////Cars
	auto p1 = core(Factory).MakeTank(790, 620, 1); //Car1
	auto p2 = core(Factory).MakeTank(790, 560, 2, 'I', 'K', 'J', 'L', 'U', 'O', 'N'); //Car2
	////Car Names
	core(Factory).makeText(0, 0, "P1",16,24,p1->transform); //Car1 Name
	core(Factory).makeText(0, 0, "P2", 16, 24, p2->transform); //Car2 Name

	////Game borders
	core(Factory).MakeBorder(70, core(Window).height() - 65, vec3Make(1, 0, 0));
	core(Factory).MakeBorder(70, core(Window).height() - 65, vec3Make(0, -1, 0));
	core(Factory).MakeBorder(core(Window).width() - 45, 65, vec3Make(-1, 0, 0));
	core(Factory).MakeBorder(core(Window).width() - 45, 65, vec3Make(0, 1, 0));

	////track hit markers
	//core(Factory).makeLine(725, 590);
	core(Factory).makeCenter(core(Window).width()/2, core(Window).height() / 2);

	////Hud info
	core(Factory).makeLight(core(Window).width() / 2, core(Window).height() / 2,
		core(Factory).makeGate(760, 590, vec3Make(1, 0, 0)), core(Factory).makeGate(820, 590, vec3Make(-1, 0, 0)));
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	runGame(); //end of game loop
}