#include <iostream>
#include <fstream>
#include "Engine.h"
#include "World.h"
#include "Wall.h"
#include "Player.h"
#include "Goal.h"
#include "Floor.h"

Engine::Engine()
{
	Initilize();
}

Engine::~Engine()
{
	Terminate();
}

void Engine::Initilize()
{
	bRunning = true;
	MyWorld = new World();
}

void Engine::Load(string MapFilename)
{
	//Load
	ifstream MapFile(MapFilename);

	int Y = 0;
	while (MapFile.peek() != EOF)
	{
		char Buffer[1024] = { 0, };
		MapFile.getline(Buffer, 1024);

		for (size_t X = 0; X < strlen(Buffer); ++X)
		{
			char Cursor = Buffer[X];
			switch (Cursor)
			{
			case '#':
				MyWorld->MyActors.push_back(new AWall((unsigned)X, (unsigned)Y, '#', true));
				break;
			case ' ':
				MyWorld->MyActors.push_back(new AFloor((unsigned)X, (unsigned)Y, ' ', false));
				break;
			case 'P':
				MyWorld->MyActors.push_back(new APlayer((unsigned)X, (unsigned)Y, 'P', true));
				break;
			case 'G':
				MyWorld->MyActors.push_back(new APlayer((unsigned)X, (unsigned)Y, 'G', false));
				break;
			case 'M':
				MyWorld->MyActors.push_back(new APlayer((unsigned)X, (unsigned)Y, 'M', true));
				break;
			}
		}
		

		Y++;
	}

	MapFile.close();
}

void Engine::Run()
{
	//Run
	while (bRunning) //1 Frame
	{
		MyWorld->Tick();
		MyWorld->Render();
	}
}

void Engine::Terminate()
{
	delete MyWorld;
	MyWorld = nullptr;
}
