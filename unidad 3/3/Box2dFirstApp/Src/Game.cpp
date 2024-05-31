#include "Game.h"
#include "Box2DHelper.h"

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo); // Crea una ventana con las dimensiones y t�tulo especificados
	wnd->setVisible(true); // Hace visible la ventana
	fps = 60; // Establece el l�mite de cuadros por segundo (FPS)
	wnd->setFramerateLimit(fps); // Aplica el l�mite de FPS a la ventana
	frameTime = 1.0f / fps; // Calcula el tiempo por cuadro en segundos
	SetZoom(); // Configura el "zoom" o vista de la c�mara
	InitPhysics(); // Inicializa la simulaci�n de f�sica
}

void Game::Loop()
{
	while (wnd->isOpen()) // Bucle principal del juego que se ejecuta mientras la ventana est� abierta
	{
		wnd->clear(clearColor); // Limpia la ventana con el color de fondo
		DoEvents(); // Maneja los eventos (input del usuario)
		CheckCollitions(); // Verifica colisiones (a implementar)
		UpdatePhysics(); // Actualiza la simulaci�n de f�sica
		DrawGame(); // Dibuja los elementos del juego
		wnd->display(); // Muestra los cambios en la ventana
	}
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8); // Avanza la simulaci�n de f�sica un paso
	phyWorld->ClearForces(); // Limpia las fuerzas acumuladas
	phyWorld->DebugDraw(); // Dibuja la representaci�n de debug de la simulaci�n
}


void Game::DrawGame()
{
	// Funci�n para dibujar los elementos del juego (a implementar)
}

void Game::DoEvents()
{
	Event evt;
	while (wnd->pollEvent(evt)) // Procesa todos los eventos acumulados
	{
		switch (evt.type)
		{
		case Event::Closed: // Si se solicita cerrar la ventana
			wnd->close(); // Cierra la ventana
			break;
		case Event::MouseButtonPressed: // Si se presiona un bot�n del rat�n
			// Crea un cuerpo din�mico con forma triangular en la posici�n del clic
			b2Body* body = Box2DHelper::CreateTriangularDynamicBody(phyWorld, b2Vec2(0.0f, 0.0f), 10.0f, 1.0f, 4.0f, 0.1f);
			Vector2f pos = wnd->mapPixelToCoords(Vector2i(evt.mouseButton.x, evt.mouseButton.y)); // Transforma la posici�n del clic a coordenadas del mundo
			body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f); // Mueve el cuerpo a la posici�n del clic
			break;
		}
	}
}

void Game::CheckCollitions()
{
	// Verificaci�n de colisiones (a implementar)
}

void Game::SetZoom()
{
	View camara;
	camara.setSize(100.0f, 100.0f); // Establece el tama�o de la vista
	camara.setCenter(50.0f, 50.0f); // Centra la vista en un punto del mundo
	wnd->setView(camara); // Aplica la vista a la ventana
}


void Game::InitPhysics()
{
	// Inicializa el mundo de Box2D con una gravedad hacia abajo
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	debugRender = new SFMLRenderer(wnd); // Crea un renderizador de debug para SFML
	debugRender->SetFlags(UINT_MAX); // Configura el renderizador para dibujar todas las formas de debug
	phyWorld->SetDebugDraw(debugRender); // Establece el renderizador de debug para el mundo de Box2D

	// Crea cuerpos est�ticos para simular el suelo y las paredes
	// Tambi�n crea cuerpos din�micos (como c�rculos) y los une con resortes al techo para demostrar la simulaci�n f�sica
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	// Creamos un techo
	b2Body* topWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	topWallBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

	// Creamos un circulo que ataremos al primer resorte
	b2Body* circuloCentral = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 0.5, 0.1f);
	circuloCentral->SetTransform(b2Vec2(50.0f, 50.0f), 0.0f); // Colocamos la pelota central en el centro

	// Atamos la esfera mediante un resorte al techo
	Box2DHelper::CreateDistanceJoint(phyWorld, circuloCentral, circuloCentral->GetWorldCenter(),
		topWallBody, b2Vec2(50.0f, 10.0f), 20.0f, 0.1f, 0.0f);
}


Game::~Game(void)
{
	// Destructor de la clase Game (a implementar si es necesario)
}