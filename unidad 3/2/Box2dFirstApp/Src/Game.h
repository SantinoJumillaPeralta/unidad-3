#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "Box2DHelper.h"

using namespace sf;
class Game
{
private:
	// Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow* wnd;
	Color clearColor;

	// Objetos de box2d
	b2World* phyWorld;
	SFMLRenderer* debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	// Cuerpo de box2d
	b2Body* ball1;
	b2Body* ball2;

	b2Body* joint;

	b2MouseJoint* mouseJoint;

public:

	// Constructores, destructores e inicializadores
	Game(int ancho, int alto, std::string titulo);
	void CheckCollitions();
	~Game(void);
	// Inicializaci�n del motor de f�sica y los cuerpos del mundo f�sico
	void InitPhysics()
	{
		// Inicializar el mundo f�sico con la gravedad por defecto
		phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

		// Crear un renderer de debug para visualizar el mundo f�sico
		debugRender = new SFMLRenderer(wnd);
		debugRender->SetFlags(UINT_MAX);
		phyWorld->SetDebugDraw(debugRender);

		// Crear el suelo y las paredes est�ticas del mundo f�sico
		b2Body* groundBody = Box2DHelper::CreateComplexRectangularStaticBody(phyWorld, 100, 10, 5);
		groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

		b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
		leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

		b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
		rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

		b2Body* TopWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
		TopWallBody->SetTransform(b2Vec2(50.f, 0.0f), 0.0f);

		ball1 = Box2DHelper::CreateCircularDynamicBody(phyWorld, 1, 1, 1, 1.2f);
		ball1->SetTransform(b2Vec2(60.f, 70.0f), 0.0f);

		ball2 = Box2DHelper::CreateCircularDynamicBody(phyWorld, 1, 1, 1, 1.2f);
		ball2->SetTransform(b2Vec2(50.f, 50.0f), 0.0f);


		Box2DHelper::CreateDistanceJoint(phyWorld, ball1, ball1->GetWorldCenter(), ball2, ball2->GetWorldCenter(), 20.0f, 1.0f, 1.5f);
	}

	// Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
};