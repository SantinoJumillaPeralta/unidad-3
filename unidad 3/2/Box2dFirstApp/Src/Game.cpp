#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>


Game::Game(int ancho, int alto, std::string titulo)
{

    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom();
    InitPhysics();
    mouseJoint = Box2DHelper::CreateMouseJoint(phyWorld, ball2, 1);

}


void Game::Loop()
{
    while (wnd->isOpen())
    {
        wnd->clear(clearColor);
        DoEvents();
        CheckCollitions();
        UpdatePhysics();
        DrawGame();
        wnd->display();
    }
}
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8);
    phyWorld->ClearForces();
    phyWorld->DebugDraw();
}

// Dibujo de los elementos del juego
void Game::DrawGame()
{



}

// Procesamiento de eventos de entrada
void Game::DoEvents()
{




    Event evt;
    while (wnd->pollEvent(evt))
    {

        Vector2f pos = wnd->mapPixelToCoords(Vector2i(evt.mouseButton.x, evt.mouseButton.y));
        mouseJoint->ShiftOrigin(b2Vec2(pos.x, pos.y));


        switch (evt.type)
        {
        case Event::Closed:
            wnd->close(); // Cerrar la ventana si se presiona el botón de cerrar
            break;
        }

        ball1->SetAwake(true);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            ball1->SetLinearVelocity(b2Vec2(-30.0f, 0.0f));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            ball2->SetLinearVelocity(b2Vec2(30.0f, 0.0f));
        }
    }
}

// Comprobación de colisiones (a implementar más adelante)
void Game::CheckCollitions()
{
    // Implementación de la comprobación de colisiones
}

// Configuración de la vista del juego
void Game::SetZoom()
{
    View camara;
    // Posicionamiento y tamaño de la vista
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara); // Asignar la vista a la ventana
}

// Destructor de la clase

Game::~Game(void)
{
    //no deconstructor?
}