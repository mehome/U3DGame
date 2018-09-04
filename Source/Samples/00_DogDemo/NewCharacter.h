#pragma once

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <SDL/SDL_scancode.h>

using namespace Urho3D;

/*
	This character should be a revised version of the default character,
	with new animations, models, etc.
	TODO:
	-Tie inventory to the character
	-Switch items
	-Look to IK demo to add IK to legs
	-Force first person (eventually)

*/

// Seems to go up in 2^x
const unsigned CTRL_FORWARD = 1;
const unsigned CTRL_BACK = 2;
const unsigned CTRL_LEFT = 4;
const unsigned CTRL_RIGHT = 8;
const unsigned CTRL_JUMP = 16;
const unsigned CTRL_SPRINT = 32;


// Movement value consts
const float MAX_WALK_SPEED = 3.0f; // units/sec
//const float MAX_SPRINT_SPEED = 10.0f; //
const float MAX_SPRINT_SPEED = 22.0f; // was 10
const float ARTIFICIAL_BRAKING_FORCE = 5.0f;

const float WALK_TO_SPRINT_SPEED_ANIM = 6.0f;
const float SPRINT_TO_GALLOP_SPEED_ANIM = 15.0f;

const float WALK_FORCE = 20.0f;
const float SPRINT_FORCE = 35.0f;

const float BRAKING_FRICTION = 3.8f;

const float WALK_FRICTION = 1.0f;
const float SPRINT_FRICTION = 2.0f;
//const float SPRINT_FRICTION = 0.8f;

const float INAIR_MOVE_FORCE = 0.02f;
const float JUMP_FORCE = 15.0f;
const float YAW_SENSITIVITY = 0.1f;
const float INAIR_THRESHOLD_TIME = 0.1f;

const float LIGHTNING_SPEED = MAX_WALK_SPEED + ((MAX_SPRINT_SPEED - MAX_WALK_SPEED) / 2);

/// Character component, responsible for physical movement according to controls, as well as animation.
class NewCharacter : public LogicComponent {
	URHO3D_OBJECT(NewCharacter, LogicComponent);

public:
	///Construct.
	explicit NewCharacter(Context* context);

	/// Register object factory and attributes.
	static void RegisterObject(Context* context);

	/// Handle startup. Called by LogicComponent base class.
	void Start() override;
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep) override;
	void Update(float timeStep) override; //TEMP

	//void Update(float timeStep) override;

	/// Movement controls. Assigned by the main program each frame.
	Controls controls_;

	// Adds a camera to the node
	void setupCamera(Node* parentNode, Node* copyTransformsNode);

	Node* camera;
	Node* itemBoneNodeR;

private:
	/// Handle physics collision event.
	void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

	/// Grounded flag for movement.
	bool onGround_;
	/// Jump flag.
	bool okToJump_;
	/// In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
	float inAirTimer_;

	bool okToSnapPhoto = true;

	float deltaSinceLastTurn = 0.0f;
	float deltaSinceLastChangeCoM = 0.0f;

	Vector3 lastMoveDir;

	float MOVE_FORCE = WALK_FORCE;
	float ACCELERATION_FRICTION = WALK_FRICTION;
	float MAX_SPEED = MAX_WALK_SPEED;

	Node* modelAdjustmentNode_;

	int signRotCoM;
	float speedFactorCoM = 0.0f;

	void makeLightning();

	static const enum LIGHTNING_TYPE {
		FULL_BODY,
		FEET_ONLY,
		HEAD_ONLY,
		TAIL_ONLY,
		TORSO_ONLY
	};

	void makeLightningBones(NewCharacter::LIGHTNING_TYPE lightningType);
	float lightning_elapsedTime = 0.0f;
	float lightning_maxTime = 1.0f;
	float lightningRun_maxTime = 1.0f;
	//bool isSprinting = false;
};