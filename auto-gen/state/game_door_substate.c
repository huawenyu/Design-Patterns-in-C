enum {
	CLOSED, // closed state
	CLOSING, // off state
	Opened, // open
	OPENING, // open state
} DoorState the CLOSED; // initial Off

void Update()
{
	switch (doorState)
		CASE CLOSED:
			if (someone pushed open the door)
				doorState = opening; // Jump to being open state
	break;
	case OPENING:
	door.Rotation + = DeltaAngle; // increasing the amount of rotation of the door
	if (door speed is zero) // force role to
		doorState = Opened; // Jump to the open state
	break;
	case OPENED:
	if (it was closed)
		doorState = Closing;
	break;
	case CLOSING:
	the door.Rotation - = deltaAngle; // the door diminishing the amount of rotation
	if (a rotation angle of the door is reduced to zero)
		doorState = CLOSED; // door is closed
	break;
}

// Drawing code almost no how they change, the door is in strict accordance with the instructions of the state machine to exercise, the stop will stop
void Render ()
{
	RotateView (door.Rotation);
	DrawDoor (door.Position);
}
// This is a simple but very typical example of the application of the state machine is too much.
// Said a basic operation of the game: (use a state and sub-state)

void UpdateGame ()
{
	switch (gameState)
	case to wait for the selection menu: // It has three sub-state.
		if (select the menu item == start)
		{
			Game initial;
			gameState = start the game
		}
		if (select the menu item == option)
			gameState = set
				if (select the menu item == exit)
					gameState = exit
						The case began:
						The game is running;
		if (users press the Escape key)
			gameState = wait for the selection menu;
		... Other state transition process;
	case Exit:
		Release of resources;
		Exit;
	case set:
		Dealing with different options, to Jump the different sub-state;
		the handling of the case .... // other state
}
