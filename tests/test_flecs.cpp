#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <flecs.h>


// Used in: 4, 6
typedef struct {double value;} Health;

// Used in: 4
typedef struct{
    double x;
    double y;
} Position;

// Used in: 5
typedef struct {} StructTag;


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

        auto johnDoe = world.entity();
        CHECK(johnDoe.is_alive() == true);
        johnDoe.destruct();
        CHECK(johnDoe.is_alive() == false);
    }

    SUBCASE("3. Create entity with name and look it up") {
        // An entity can have a name in order to look it up easily

        flecs::world world;

        const char *name = "Jane Doe";
        auto janeDoe = world.entity(name);
        REQUIRE(janeDoe.is_alive() == true);
        CHECK(janeDoe.name() == name);

        auto correctNameLookUp = world.lookup(name);
        CHECK(janeDoe == correctNameLookUp);

        auto wrongNameLookUp = world.lookup("John Doe");
        CHECK(janeDoe != wrongNameLookUp);

        janeDoe.destruct();
    }

    SUBCASE("4. Manage components") {
        // A component is an entity which contains data

        flecs::world world;

        auto johnDoe = world.entity();
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
        auto johnDoe = world.entity().add<StructTag>();
        CHECK(johnDoe.has<StructTag>() == true);
        johnDoe.remove<StructTag>();
        CHECK(johnDoe.has<StructTag>() == false);

        // Entity Tag can be created dynamically at runtime
        auto EntityTag = world.entity();

        auto janeDoe = world.entity().add(EntityTag);
        CHECK(janeDoe.has(EntityTag) == true);
        janeDoe.remove(EntityTag);
        CHECK(janeDoe.has(EntityTag) == false);

        johnDoe.destruct();
        janeDoe.destruct();
    }

    SUBCASE("6. Simple each filter") {
        // A filter is a query whose results are not cached, making it cheap
        // to create.
        // Useful when querying for something not known in advance

        flecs::world world;

        typedef struct {int value;} Speed;

        auto janeDoe = world.entity();
        auto johnDoe = world.entity();

        const double janeDoeHealth = 5.32;
        janeDoe.set<Health>({janeDoeHealth});
        REQUIRE(janeDoe.has<Health>() == true);
        REQUIRE(janeDoe.get<Health>()->value == janeDoeHealth);

        const double johnDoeHealth = 3.76;
        johnDoe.set<Health>({johnDoeHealth});
        REQUIRE(johnDoe.has<Health>() == true);
        REQUIRE(johnDoe.get<Health>()->value == johnDoeHealth);

        const int janeDoeSpeed = 2;
        janeDoe.set<Speed>({janeDoeSpeed});
        REQUIRE(janeDoe.has<Speed>() == true);
        REQUIRE(janeDoe.get<Speed>()->value == janeDoeSpeed);

        const int johnDoeSpeed = 5;
        johnDoe.set<Speed>({johnDoeSpeed});
        REQUIRE(johnDoe.has<Speed>() == true);
        REQUIRE(johnDoe.get<Speed>()->value == johnDoeSpeed);

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
}