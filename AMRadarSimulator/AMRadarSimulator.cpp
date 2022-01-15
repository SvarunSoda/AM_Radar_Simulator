//Author(s): Svarun Soda
//Class: Aerospace & Science Team of College of the Canyons

//// INCLUDES ////

#include <stdio.h>
#include "vector.cpp"
#include <iostream> 
#include <Windows.h>
#include <thread>
#include <chrono>

using namespace std;

//// FUNCTION DECLARATIONS ////

void UpdateRadarRotation(double acceleration);
void DrawLiveFeed();
void DrawDiagram();
void BringCursorBack(int offsetX, int offsetY);
void Delay(long double seconds);

//// GLOBAL VARIABLES ////

Vector3D ReferenceVector;
Vector3D RadarVector;

double CurrentRotation = 0;
double CurrentRotationSpeed = 0;
double RotationAcceleration = 0.001;
double RollingFriction = 0.0009;
double UpdateInterval = 5000;
double TimeElapsed = 0;
int FeedSpaceY = 27;

std::string Diagram[19][17] = {

	{ //0
	"              -----------               ",
	"        -----/     X     \\-----         ",
	"     --/           X           \\--      ",
	"   -/              X              \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //10
	"              -----------               ",
	"        -----/X          \\-----         ",
	"     --/      X                \\--      ",
	"   -/          X                  \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},
	
	{ //20
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/    X                  \\--      ",
	"   -/        X                    \\-    ",
	"  /           X                      \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //30
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/X                      \\--      ",
	"   -/     X                       \\-    ",
	"  /         X                        \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //40
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/X                            \\-    ",
	"  /    X                             \\  ",
	" /        X                           \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //50
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /X                                 \\  ",
	" /    X                               \\ ",
	" /       X                            \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //60
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /X  X                                \\ ",
	" /       X                            \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //70
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /X                                   \\ ",
	"|    X  X                              |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //80
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|X  X                                  |",
	"|      X           X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //90
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|X X X             X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //100
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|      X           X                   |",
	"|X  X                                  |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //110
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|    X  X                              |",
	" \\X                                   / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //120
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|        X                             |",
	" \\X  X                                / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //130
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\       X                            / ",
	" \\    X                               / ",
	"  \\X                                 /  ",
	"   -\\                             /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //140
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\        X                           / ",
	"  \\    X                             /  ",
	"   -\\X                            /-    ",
	"     --\\                       /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //150
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\         X                        /  ",
	"   -\\     X                       /-    ",
	"     --\\X                      /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //160
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\          X                       /  ",
	"   -\\       X                     /-    ",
	"     --\\   X                   /--      ",
	"        -----\\           /-----         ",
	"              -----------                "
	},

	{ //170
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\          X                  /-    ",
	"     --\\      X                /--      ",
	"        -----\\X          /-----         ",
	"              -----------                "
	},

	{ //180
	"              -----------               ",
	"        -----/           \\-----         ",
	"     --/                       \\--      ",
	"   -/                             \\-    ",
	"  /                                  \\  ",
	" /                                    \\ ",
	" /                                    \\ ",
	"|                                      |",
	"|                  X                   |",
	"|                                      |",
	" \\                                    / ",
	" \\                                    / ",
	"  \\                                  /  ",
	"   -\\             X               /-    ",
	"     --\\          X            /--      ",
	"        -----\\    X      /-----         ",
	"              -----------                "
	}

};

//// MAIN FUNCTION ////

int main() {

	cout << "Antimatter Radar Simulator Program\n";
	cout << "Author(s): Svarun Soda";

	cout << "\n\n\n";
	
	// INITIALIZING THE VECTORS

	ReferenceVector.SetName("Reference");
	ReferenceVector.SetStartZ(-1, true);
	ReferenceVector.SetEndZ(1, true);
	ReferenceVector.UpdateLengthFromPoints();

	RadarVector.SetName("Radar");
	RadarVector.SetOtherName(ReferenceVector.GetName());
	RadarVector.SetStartZ(-1, true);
	RadarVector.SetEndZ(1, true);
	RadarVector.UpdateLengthFromPoints();

	// MAIN PROGRAM LOOP
	
	double localTimeElapsed = 0;
	double startTime = time(NULL);

	cout << "The simulation will now commence.\n\nControls:\n- Hold \"A\" on your keyboard to accelerate the radar spin, and hold \"Left Shift\" to accelerate it faster.\n- Hold the \"B\" key to slow down the acceleration.\n- To halt the simulation, hit the \"Escape\" key on your keyboard.\n\n";
	
	system("pause");

	cout << "\n------------------------------------ The simulation has started! ------------------------------------\n\n\n";

	BringCursorBack(0, FeedSpaceY);

	bool isAccelPressed = false;
	bool isFastAccelPressed = false;
	bool isBreakPressed = false;

	while (!(GetKeyState(0x1B) & 0x8000)) { //escape key

		if (isAccelPressed == false) {

			isAccelPressed = GetKeyState(0x41) & 0x8000; //"a" key

			if (isAccelPressed == true) {

				isFastAccelPressed = GetKeyState(0xA0) & 0x8000; //left shift key

			} else if (isBreakPressed == false) {

				isBreakPressed = GetKeyState(0x42) & 0x8000; //"b" key

			}

		}

		if (localTimeElapsed >= UpdateInterval) {

			BringCursorBack(0, -FeedSpaceY);

			double rotAccel = 0;

			if (isAccelPressed == true) {

				rotAccel = RotationAcceleration;

				if (isFastAccelPressed == true) {

					rotAccel = RotationAcceleration * 3;

				}

				isAccelPressed = false;
				isFastAccelPressed = false;

			} else if (isBreakPressed == true) {

				rotAccel = -(RotationAcceleration * 2);

				isBreakPressed = false;

			}

			UpdateRadarRotation(rotAccel);

			TimeElapsed = time(NULL) - startTime;
			
			DrawLiveFeed();

			localTimeElapsed = 0;

		} else {

			localTimeElapsed = localTimeElapsed + 0.1;

		}

	}

	BringCursorBack(0, FeedSpaceY);

	// PROGRAM END

	cout << "\n\n\nPROGRAM EXITED\n\n";

	system("pause");

	return 0;

}

//// RADAR CONTROL FUNCTIONS ////

void UpdateRadarRotation(double acceleration) {

	double nextRotSpeed = CurrentRotationSpeed + (acceleration - RollingFriction);

	if (!(nextRotSpeed < 0)) {

		CurrentRotationSpeed = nextRotSpeed;

	}

	CurrentRotation = RadarVector.BoundValueCircular(CurrentRotation + CurrentRotationSpeed, 180, true);

	RadarVector.RotateVectorEuler(0, CurrentRotationSpeed, 0);
	RadarVector.UpdateLengthFromPoints();
	RadarVector.UpdateRelAngle(ReferenceVector);

}

//// FEED-DRAWING FUNCTIONS ////

void DrawLiveFeed() {

	cout << RadarVector.ToStringRadarLiveFeed(CurrentRotation, CurrentRotationSpeed, TimeElapsed);

	BringCursorBack(0, -FeedSpaceY);

	DrawDiagram();

}

void DrawDiagram() {

	int mapSizeX = 41;
	int mapSizeY = 19;
	int distanceX = 65;

	// DRAWING THE FRAME

	for (int i = 0; i < (mapSizeX + distanceX); i++) {

		cout << " ";

	}

	BringCursorBack(0, 0);

	for (int i = 0; i < mapSizeY; i++) {

		BringCursorBack(distanceX, 1);

		cout << "|";

		if ((i == 0) || (i == (mapSizeY - 1))) {

			for (int j = 0; j < (mapSizeX); j++) {

				BringCursorBack(distanceX + (j + 1), 0);

				cout << "-";

			}

		} else {

			int diagramIdx = (int)(CurrentRotation / 10);
			int printIdx = i - 1;

			std::string diagramToDraw;

			if (diagramIdx < 0) {

				diagramToDraw = Diagram[-diagramIdx][printIdx];

				reverse(diagramToDraw.begin(), diagramToDraw.end());

			} else {

				diagramToDraw = Diagram[diagramIdx][printIdx];

			}

			cout << diagramToDraw;

		}

		BringCursorBack(distanceX + mapSizeX, 0);

		cout << "|";

	}

	BringCursorBack(0, -mapSizeY);

	// DRAWING THE DIAGRAM



}

//// SUPPORTING FUNCTIONS ////

void BringCursorBack(int offsetX, int offsetY) {

	COORD newCursorPos;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	COORD currentCursorPos = consoleInfo.dwCursorPosition;

	newCursorPos.X = offsetX;
	newCursorPos.Y = currentCursorPos.Y + offsetY;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCursorPos);

}

void Delay(long double seconds) {

	std::this_thread::sleep_for(std::chrono::milliseconds(int(seconds * 1000)));

}