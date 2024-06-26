#include <raylib.h>
#include <flecs.h>
#include "flecs_ids.hpp"
#include "GameController.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"
#include "colors.hpp"

// Constructor for GameController
GameController::GameController():
    model(0),
    view(
        // Initialize the view with the position of the cursor
        this->model.world.lookup("Cursor").get<Position>()->x,
        this->model.world.lookup("Cursor").get<Position>()->y
    ) {
    // Initialize the floorQuery with the positions of the floor tiles
    this->floorQuery = this->model.world.query<FloorTag, Position>();
    // Set creatingPath to true to start creating a path
    this->creatingPath = true;
}


// Destructor for GameController
GameController::~GameController() {}

// Main game loop
void GameController::run() {
    // Get the cursor entity
    flecs::entity cursor = this->model.world.lookup("Cursor");


    // Get the current tick and max tick of the cursor
    int cursorTick = cursor.get<Tick>()->tick;
    int cursorMaxTick = cursor.get<Tick>()->maxTick;

    // Get the current position of the cursor
    Position cursorSource = *cursor.get<Position>();
    Position cursorDestination = cursorSource;

    // Initialize entities for farAhead, diagonalLeft, and diagonalRight
    flecs::entity farAhead = this->model.world.entity();
    flecs::entity diagonalLeft = this->model.world.entity();
    flecs::entity diagonalRight = this->model.world.entity();


    // Initialize entities for farAhead, diagonalLeft, and diagonalRight
    if (
        IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) ||
        IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)
    ) {
        // If the up arrow key is pressed and the cursor is at the start of its tick cycle
        if (IsKeyDown(KEY_UP) && cursorTick == 0) {
            // Move the cursor up
            cursorDestination.y -= 1;

            // Find the tile two spaces ahead of the cursor
            farAhead.destruct();
            farAhead = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x &&
                    position.y == cursorSource.y - 2
                );
            });

            // Find the tile diagonally left of the cursor
            diagonalLeft.destruct();
            diagonalLeft = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x - 1 &&
                    position.y == cursorSource.y - 1
                );
            });

            // Find the tile diagonally right of the cursor
            diagonalRight.destruct();
            diagonalRight = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x + 1 &&
                    position.y == cursorSource.y - 1
                );
            });

        } else if (IsKeyDown(KEY_DOWN) && cursorTick == 0) {
            cursorDestination.y += 1;

            farAhead.destruct();
            farAhead = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x &&
                    position.y == cursorSource.y + 2
                );
            });

            diagonalLeft.destruct();
            diagonalLeft = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x + 1 &&
                    position.y == cursorSource.y + 1
                );
            });

            diagonalRight.destruct();
            diagonalRight = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x - 1 &&
                    position.y == cursorSource.y + 1
                );
            });

        } else if (IsKeyDown(KEY_LEFT) && cursorTick == 0) {
            cursorDestination.x -= 1;

            farAhead.destruct();
            farAhead = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x - 2 &&
                    position.y == cursorSource.y
                );
            });

            diagonalLeft.destruct();
            diagonalLeft = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x - 1 &&
                    position.y == cursorSource.y + 1
                );
            });

            diagonalRight.destruct();
            diagonalRight = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x - 1 &&
                    position.y == cursorSource.y - 1
                );
            });

        } else if (IsKeyDown(KEY_RIGHT) && cursorTick == 0) {
            cursorDestination.x += 1;

            farAhead.destruct();
            farAhead = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x + 2 &&
                    position.y == cursorSource.y
                );
            });

            diagonalLeft.destruct();
            diagonalLeft = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x + 1 &&
                    position.y == cursorSource.y - 1
                );
            });

            diagonalRight.destruct();
            diagonalRight = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return (
                    position.x == cursorSource.x + 1 &&
                    position.y == cursorSource.y + 1
                );
            });
        };

        cursor.set<Tick>({
            (cursorTick + 1 + cursorMaxTick) % cursorMaxTick,
            cursorMaxTick
        });
    } else {
        cursor.set<Tick>({0, cursorMaxTick});
    };

    flecs::entity sourceTile = this->floorQuery.find([&](
        FloorTag floorTag, Position position
    ) {
        return position.x == cursorSource.x && position.y == cursorSource.y;
    });

    flecs::entity destinationTile = this->floorQuery.find([&](
        FloorTag floorTag, Position position
    ) {
        return (
            position.x == cursorDestination.x &&
            position.y == cursorDestination.y
        );
    });

    if (!destinationTile) {
        cursorDestination = cursorSource;
        destinationTile = sourceTile;
    } else if (
        farAhead.is_alive() &&
        farAhead.has<PathTag>() &&
        !farAhead.has<PathGoesTo>(destinationTile) &&
        creatingPath
    ) {
        cursorDestination = cursorSource;
        destinationTile = sourceTile;
    } else if (
        diagonalLeft.is_alive() &&
        diagonalLeft.has<PathTag>() &&
        !destinationTile.has<PathGoesTo>(sourceTile) &&
        creatingPath
    ) {
        cursorDestination = cursorSource;
        destinationTile = sourceTile;
    } else if (
        diagonalRight.is_alive() &&
        diagonalRight.has<PathTag>() &&
        !destinationTile.has<PathGoesTo>(sourceTile) &&
        creatingPath
    ) {
        cursorDestination = cursorSource;
        destinationTile = sourceTile;
    };
    
    cursor.set<Position>({cursorDestination.x, cursorDestination.y});
    this->view.camera.target = this->view.transformGridOblique(
        cursorDestination.x,
        cursorDestination.y
    );

    if (
        creatingPath && 
        !destinationTile.has<PathTag>() &&
        (sourceTile != destinationTile) &&
        destinationTile.name() != "Start"
    ) {
        destinationTile.add<PathTag>();
        sourceTile.add<PathGoesTo>(destinationTile);
    } else if (destinationTile.has<PathGoesTo>(sourceTile) && creatingPath) {
        sourceTile.remove<PathTag>();
        destinationTile.remove<PathGoesTo>(sourceTile);
    } else if (destinationTile.name() == "End" && creatingPath) {
        creatingPath = false;
    };


    BeginDrawing();
    ClearBackground(COLOR0);

    BeginMode2D(this->view.camera);
    this->view.drawFloor(this->floorQuery);
    this->view.drawPathWithFilter(this->model.world);
    this->view.drawStartEnd(this->model.world);
    this->view.drawCursor(this->model.world.lookup("Cursor"));
    EndMode2D();

    EndDrawing();
}