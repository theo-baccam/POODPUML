#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <flecs.h>
#define BOB_NAME "Bob"


#include <iostream>
#include <typeinfo>


// Used in: 4, 7, 8, 9, 11
typedef struct {double value;} Health;

// Used in: 4, 7
typedef struct{
    double x;
    double y;
} Position;

// Used in: 5
typedef struct {} StructTag;

// Used in: 6
typedef struct {} Contains;

// Used in: 6
typedef struct {} ComesFrom;

// Used in: 8, 9
typedef struct {int value;} Speed;

// Used in 10;
void addEntity(flecs::world &world) {
    flecs::entity bob = world.entity(BOB_NAME);
}


TEST_CASE("Working flecs framework") {

    SUBCASE("1. Creating world") {
        // The world is the container of all ECS data

        flecs::world world;
    }

    SUBCASE("2. Creating entity") {
        // An entity is a unique ID in the world.
        // They can have 0 to n IDs added to them.
        // An ID is anything that can be added to an entity

        flecs::world world;

        flecs::entity johnDoe = world.entity();
        CHECK(johnDoe.is_alive() == true);
        johnDoe.destruct();
        CHECK(johnDoe.is_alive() == false);
    }

    SUBCASE("3. Create entity with name and look it up") {
        // An entity can have a name in order to look it up easily

        flecs::world world;

        const char *name = "Jane Doe";
        flecs::entity janeDoe = world.entity(name);
        REQUIRE(janeDoe.is_alive() == true);
        CHECK(janeDoe.name() == name);

        flecs::entity correctNameLookUp = world.lookup(name);
        CHECK(janeDoe == correctNameLookUp);

        flecs::entity wrongNameLookUp = world.lookup("John Doe");
        CHECK(janeDoe != wrongNameLookUp);

        janeDoe.destruct();
    }

    SUBCASE("4. Manage components") {
        // A component is an entity which contains data

        flecs::world world;

        flecs::entity johnDoe = world.entity();
        REQUIRE(johnDoe.is_alive() == true);

        // You can `add` a component to an entity without giving a value
        // You can also `set`, which sets a component's value and also adds it
        // if an entity doesn't already have it.

        // By the way, a component can only be a struct or an entity,
        // as far as I know, if you try to set multiple components as aliases
        // of simpler types like int or double, the values will get mixed up.

        const double healthPoints = 15.28;
        johnDoe.add<Health>();
        johnDoe.set<Health>({healthPoints});
        CHECK(johnDoe.has<Health>() == true);
        CHECK(johnDoe.get<Health>()->value == healthPoints);

        double x = 82.12;
        double y = -12.53;
        johnDoe.set<Position>({x, y});
        CHECK(johnDoe.has<Position>() == true);

        johnDoe.destruct();
    }

    SUBCASE("5. Tag management") {
        // Tags are components with no data

        flecs::world world;

        // Struct Tag is fixed at compile time
        flecs::entity johnDoe = world.entity().add<StructTag>();
        CHECK(johnDoe.has<StructTag>() == true);
        johnDoe.remove<StructTag>();
        CHECK(johnDoe.has<StructTag>() == false);

        // Entity Tag can be created dynamically at runtime
        flecs::entity EntityTag = world.entity();

        flecs::entity janeDoe = world.entity().add(EntityTag);
        CHECK(janeDoe.has(EntityTag) == true);
        janeDoe.remove(EntityTag);
        CHECK(janeDoe.has(EntityTag) == false);

        johnDoe.destruct();
        janeDoe.destruct();
    }

    SUBCASE("6. Pair management") {
        // A pair is an id with two entities, can be used to indicate
        // relationships between entities

        flecs::world world;

        flecs::entity antHill = world.entity();
        flecs::entity ant = world.entity();
        REQUIRE(antHill.is_alive() == true);
        REQUIRE(ant.is_alive() == true);

        antHill.add<Contains>(ant);
        ant.add<ComesFrom>(antHill);

        CHECK(antHill.has<Contains>(ant) == true);
        CHECK(ant.has<ComesFrom>(antHill) == true);

        antHill.destruct();
        ant.destruct();
    }

    SUBCASE("7. Type management") {
        // A type, a.k.a. archetype, is an list of IDs possessed by an entity

        flecs::world world;

        // Useful way of creating an entity and adding IDs
        flecs::entity character = world.entity()
            .set<Health>({14.5})
            .set<Position>({32.85, 12.94});
        REQUIRE(character.is_alive() == true);

        CHECK(character.type().str() == "Health, Position");

        character.destruct();
    }

    SUBCASE("8. Simple each filter") {
        // A filter is a query whose results are not cached, making it cheap
        // to create.
        // Useful when querying for something not known in advance

        flecs::world world;


        const double janeDoeHealth = 5.32;
        const int janeDoeSpeed = 2;

        flecs::entity janeDoe = world.entity()
            .set<Health>({janeDoeHealth})
            .set<Speed>({janeDoeSpeed});
        REQUIRE(janeDoe.is_alive() == true);

        REQUIRE(janeDoe.has<Health>() == true);
        REQUIRE(janeDoe.get<Health>()->value == janeDoeHealth);

        REQUIRE(janeDoe.has<Speed>() == true);
        REQUIRE(janeDoe.get<Speed>()->value == janeDoeSpeed);


        const double johnDoeHealth = 3.76;
        const int johnDoeSpeed = 5;

        flecs::entity johnDoe = world.entity()
            .set<Health>({johnDoeHealth})
            .set<Speed>({johnDoeSpeed});
        REQUIRE(johnDoe.is_alive() == true);

        REQUIRE(johnDoe.has<Health>() == true);
        REQUIRE(johnDoe.get<Health>()->value == johnDoeHealth);

        REQUIRE(johnDoe.has<Speed>() == true);
        REQUIRE(johnDoe.get<Speed>()->value == johnDoeSpeed);

        // An each function iterates over each existing entity
        world.each([](Health& health, Speed& speed) {
            health.value -= 1;
            speed.value += 1; 
        });

        CHECK(janeDoe.get<Health>()->value == janeDoeHealth - 1);
        CHECK(johnDoe.get<Health>()->value == johnDoeHealth - 1);
        CHECK(janeDoe.get<Speed>()->value == janeDoeSpeed + 1);
        CHECK(johnDoe.get<Speed>()->value == johnDoeSpeed + 1);

        janeDoe.destruct();
        johnDoe.destruct();
    }

    SUBCASE("9. Creating queries, and iter") {
        // You can create more complex filters/queries as well

        flecs::world world;


        const double janeDoeHealth = 5.32;
        const int janeDoeSpeed = 2;

        flecs::entity janeDoe = world.entity()
            .set<Health>({janeDoeHealth})
            .set<Speed>({janeDoeSpeed});
        REQUIRE(janeDoe.is_alive() == true);

        REQUIRE(janeDoe.has<Health>() == true);
        REQUIRE(janeDoe.get<Health>()->value == janeDoeHealth);

        REQUIRE(janeDoe.has<Speed>() == true);
        REQUIRE(janeDoe.get<Speed>()->value == janeDoeSpeed);


        const double johnDoeHealth = 3.76;
        const int johnDoeSpeed = 5;

        flecs::entity johnDoe = world.entity()
            .set<Health>({johnDoeHealth})
            .set<Speed>({johnDoeSpeed});
        REQUIRE(johnDoe.is_alive() == true);

        REQUIRE(johnDoe.has<Health>() == true);
        REQUIRE(johnDoe.get<Health>()->value == johnDoeHealth);

        REQUIRE(johnDoe.has<Speed>() == true);
        REQUIRE(johnDoe.get<Speed>()->value == johnDoeSpeed);


        const double jayDoeHealth = 9.32;

        flecs::entity jayDoe = world.entity()
            .set<Health>({jayDoeHealth});
        REQUIRE(jayDoe.is_alive() == true);

        REQUIRE(jayDoe.has<Health>() == true);
        REQUIRE(jayDoe.get<Health>()->value == jayDoeHealth);

        REQUIRE(jayDoe.has<Speed>() == false);

        // A query is a cached filter, it is slower to create but faster to
        // iterate through, they are meant to be reused and not to be
        // created in a loop.

        // Here is a query for entities that have Health and Speed components
        // There are more complex operators, for example wildcards, exlusions... 
        flecs::query<Health, Speed> healthSpeedQuery =
            world.query<Health, Speed>();

        // You use iter in order to iterate through each entity which
        // matches an archetype
        healthSpeedQuery.iter([&](flecs::iter& it, Health *h, Speed *s) {
            for (auto i : it) {
                h[i].value += 1;
            };
        });

        // Since Jay Doe doesn't have Speed, his health isn't affected
        CHECK(janeDoe.get<Health>()->value == janeDoeHealth + 1);
        CHECK(johnDoe.get<Health>()->value == johnDoeHealth + 1);
        CHECK(jayDoe.get<Health>()->value == jayDoeHealth);

        janeDoe.destruct();
        johnDoe.destruct();
        jayDoe.destruct();
    }

    SUBCASE("10. Adding entites to a world through function") {
        // Test to see if one can add entities via a function.
        // To be used for Builders

        flecs::world world;

        // If no entity, world.lookup() returns a 0 instead of an entity
        REQUIRE(world.lookup(BOB_NAME) == 0);

        // Add entity through function and check if alive
        addEntity(world);
        CHECK(world.lookup(BOB_NAME).is_alive() == true);
    }

    SUBCASE("11. Finding entities") {
        // Function which allows to find entity if component is equal to x

        flecs::world world;

        flecs::entity johnDoe = world.entity().set<Health>({10});
        REQUIRE(johnDoe.is_alive() == true);
        REQUIRE(johnDoe.get<Health>()->value == 10);

        flecs::query<Health> query = world.query<Health>();

        flecs::entity foundEntity = query.find([](Health& health) {
            return health.value == 10;
        });
        CHECK(foundEntity == johnDoe);

        flecs::entity nonExistantEntity = query.find([](Health& health) {
            return health.value == 1234;
        });
        CHECK(!nonExistantEntity);

        johnDoe.destruct();
    }
}