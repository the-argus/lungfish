#pragma once
#include "raylib.h"
#include "ode/ode.h"

#define OPTIONAL(type) \
typedef struct Opt_##type { \
    unsigned char has; \
    type value; \
} Opt_##type;

typedef struct
{
	Vector2 angle;			  // Camera angle in plane XZ
	int moveControl[6];	   // Move controls (CAMERA_FIRST_PERSON)
} CameraData;

typedef struct Mousestate {
    unsigned char left_pressed;
    unsigned char right_pressed;
    Vector2 position;
    Vector2 virtual_position;
} Mousestate;

typedef struct Keystate {
    unsigned char up;
    unsigned char left;
    unsigned char right;
    unsigned char down;
    unsigned char jump;
} Keystate;

typedef struct Inputstate {
    Mousestate mouse;
    Keystate keys;
} Inputstate;

typedef struct Gamestate {
    Inputstate input;
    Camera *current_camera;
    CameraData camera_data;
} Gamestate;

struct GameObject;

typedef void (*UpdateFunction)(struct GameObject *self, Gamestate *gamestate, float delta_time);
typedef void (*DrawFunction)(struct GameObject *self, Gamestate *gamestate);
typedef void (*CollisionHandler)(dGeomID self, dGeomID other);

// versions of types but they have a true/false for whether or not they
// are valid/populated
typedef dBodyID PhysicsBody;
typedef dGeomID PhysicsGeometry;

OPTIONAL(PhysicsBody)
OPTIONAL(CollisionHandler)

// a physics component always has a geom but not necessarily a body
typedef struct PhysicsComponent {
    unsigned short mask; // 8 bits
    PhysicsGeometry geom;
    Opt_CollisionHandler collision_handler;
    Opt_PhysicsBody body; // this body's UserData should be a pointer to the parent gameobject
} PhysicsComponent;

OPTIONAL(UpdateFunction)
OPTIONAL(DrawFunction)
OPTIONAL(PhysicsComponent)

// THE game object!!!!
// Possible implementations that will use game object:
//  - player/enemies (physics body determines in-world location, needs update and draw)
//  - wall (has a physics GEOM, but no physics body)
//  - particle generator, effect, decorative model (no physics, no update, only draw)
typedef struct GameObject {
    Opt_PhysicsComponent physics;
    Opt_DrawFunction draw;
    Opt_UpdateFunction update;
} GameObject;
