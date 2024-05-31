#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <doctest.h>
#include <flecs.h>


TEST_CASE("Working flecs library") {
    SUBCASE("Creating world") {
        flecs::world world;
    }

    SUBCASE("Creating entity") {
        flecs::world world;
        auto johnDoe = world.entity();
        CHECK(johnDoe.is_alive() == true);
        johnDoe.destruct();
        CHECK(johnDoe.is_alive() == false);
    }

    SUBCASE("Creating entity with name") {
        flecs::world world;
        const char *name = "Jane Doe";
        auto janeDoe = world.entity(name);
        REQUIRE(janeDoe.is_alive() == true);
        CHECK(janeDoe.name() == name);
        janeDoe.destruct();
    }

    SUBCASE("Look up entity") {
        flecs::world world;
        const char *name = "Jan Duh";
        auto janDuh = world.entity(name);
        REQUIRE(janDuh.is_alive() == true);
        auto lookedUpEntity = world.lookup(name);
        CHECK(janDuh == lookedUpEntity);
        auto mistypedEntity = world.lookup("Jlarp Dee");
        CHECK(janDuh != mistypedEntity);
        janDuh.destruct();
    }

    SUBCASE("Manage component") {
        flecs::world world;
        auto jeefDing = world.entity("Jeef Ding");

        typedef double Health;
        const double healthPoints = 15.28;
        jeefDing.add<Health>();
        jeefDing.set<Health>(healthPoints);
        CHECK(*jeefDing.get<Health>() == healthPoints);

        struct Position {
            double x;
            double y;
        };
        typedef struct Position Position;
        double x = 82.12;
        double y = -12.53;
        jeefDing.set<Position>({x, y});
        Position pos = *jeefDing.get<Position>();
        CHECK(pos.x == x);
        CHECK(pos.y == y);
        jeefDing.destruct();
    }
}