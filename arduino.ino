// vi: noexpandtab:tabstop=4:shiftwidth=4
#include <stdint.h>
#include <stdio.h>

#define RED(str) ("[1;31m" str "[m")
#define YELLOW(str) ("[1;33m" str "[m")
#define GREEN(str) ("[1;32m" str "[m")

#define PINS_ALL                                                               \
	SET(1)                                                                     \
	SET(2)                                                                     \
	SET(3)                                                                     \
	SET(4) SET(5) SET(6) SET(7) SET(8) SET(9) SET(10) SET(11) SET(12) SET(13)

#define PINS_R                                                                 \
	SET(4)                                                                     \
	SET(9)                                                                     \
	SET(12)                                                                    \
	SET(13) CLR(1) CLR(2) CLR(3) CLR(5) CLR(6) CLR(7) CLR(8) CLR(10) CLR(11)

#define PINS_G                                                                 \
	SET(3)                                                                     \
	SET(6)                                                                     \
	SET(7)                                                                     \
	SET(10) CLR(1) CLR(2) CLR(4) CLR(5) CLR(8) CLR(9) CLR(11) CLR(12) CLR(13)

#define PINS_Y                                                                 \
	SET(2)                                                                     \
	SET(5)                                                                     \
	SET(8)                                                                     \
	SET(11) CLR(1) CLR(3) CLR(4) CLR(6) CLR(7) CLR(9) CLR(10) CLR(12) CLR(13)

// Same as PINS_R
#define PINS_P1                                                                \
	SET(4)                                                                     \
	SET(9)                                                                     \
	SET(12)                                                                    \
	SET(13) CLR(1) CLR(2) CLR(3) CLR(5) CLR(6) CLR(7) CLR(8) CLR(10) CLR(11)

#define PINS_P2                                                                \
	SET(2)                                                                     \
	SET(4)                                                                     \
	SET(9)                                                                     \
	SET(11) SET(12) SET(13) CLR(1) CLR(3) CLR(5) CLR(6) CLR(7) CLR(8) CLR(10)

#define PINS_P3                                                                \
	SET(3)                                                                     \
	SET(4)                                                                     \
	SET(9)                                                                     \
	SET(10) CLR(1) CLR(2) CLR(5) CLR(6) CLR(7) CLR(8) CLR(11) CLR(12) CLR(13)

#define PINS_P4                                                                \
	SET(2)                                                                     \
	SET(4)                                                                     \
	SET(9)                                                                     \
	SET(11) CLR(1) CLR(3) CLR(5) CLR(6) CLR(7) CLR(8) CLR(10) CLR(12) CLR(13)

#define PINS_P5                                                                \
	SET(4)                                                                     \
	SET(9)                                                                     \
	SET(12)                                                                    \
	SET(13) CLR(1) CLR(2) CLR(3) CLR(5) CLR(6) CLR(7) CLR(8) CLR(10) CLR(11)

#define PINS_P6                                                                \
	SET(4)                                                                     \
	SET(5)                                                                     \
	SET(8)                                                                     \
	SET(9) SET(12) SET(13) CLR(1) CLR(2) CLR(3) CLR(6) CLR(7) CLR(10) CLR(11)

#define PINS_P7                                                                \
	SET(6)                                                                     \
	SET(7)                                                                     \
	SET(12)                                                                    \
	SET(13) CLR(1) CLR(2) CLR(3) CLR(4) CLR(5) CLR(8) CLR(9) CLR(10) CLR(11)

#define PINS_P8                                                                \
	SET(5)                                                                     \
	SET(8)                                                                     \
	SET(12)                                                                    \
	SET(13) CLR(1) CLR(2) CLR(3) CLR(4) CLR(6) CLR(7) CLR(9) CLR(10) CLR(11)

// Repeat...
static bool states[14] = {0};

static char buf[256];
#define printf(...)                                                            \
	do {                                                                       \
		snprintf(buf, sizeof(buf), __VA_ARGS__);                               \
		Serial.print(buf);                                                     \
	} while(0)

void print_diagram(void) {
	Serial.print("    ");
	Serial.print(states[6] ? GREEN("⬤ ") : "◯ ");
	Serial.print("│    ┆    │ ↑ Nano is here\n");

	Serial.print("    ");
	Serial.print(states[5] ? YELLOW("⬤ ") : "◯ ");
	Serial.print("│    ┆    │   \n");

	Serial.print("    ");
	Serial.print(states[4] ? RED("⬤ ") : "◯ ");
	Serial.print("│    ┆    │");
	Serial.print(states[12] ? RED("⬤ ") : "◯ ");
	Serial.print(states[11] ? YELLOW("⬤ ") : "◯ ");
	Serial.print(states[10] ? GREEN("⬤ ") : "◯ ");
	Serial.print("\n");

	Serial.print("──────┘───      └──────\n");
	Serial.print("                │\n");
	Serial.print("┄┄┄┄┄┄           ┄┄┄┄┄\n");
	Serial.print("      │       \n");
	Serial.print("──────┐     ────┌──────\n");

	Serial.print(states[3] ? GREEN("⬤ ") : "◯ ");
	Serial.print(states[2] ? YELLOW("⬤ ") : "◯ ");
	Serial.print(states[13] ? RED("⬤ ") : "◯ ");
	Serial.print("│    ┆    │");
	Serial.print(states[9] ? RED("⬤ ") : "◯ ");
	Serial.print("\n");

	Serial.print("      │    ┆    │");
	Serial.print(states[8] ? YELLOW("⬤ ") : "◯ ");
	Serial.print("\n");

	Serial.print("      │    ┆    │");
	Serial.print(states[7] ? GREEN("⬤ ") : "◯ ");

	Serial.print("\x1b[11A\x1B[99D");
}

void clear_all(void) {
#define SET(x)                                                                 \
	pinMode((x), OUTPUT);                                                      \
	digitalWrite((x), LOW);

	PINS_ALL
}

void standard(void) {
#define SET(x)                                                                 \
	digitalWrite((x), HIGH);                                                   \
	states[(x)] = true;
#define CLR(x)                                                                 \
	digitalWrite((x), LOW);                                                    \
	states[(x)] = false;

	Serial.print("Phase 1\n");
	PINS_P1
	print_diagram();
	delay(1000);

	Serial.print("Phase 2\n");
	PINS_P2
	print_diagram();
	delay(1000);

	Serial.print("Phase 3\n");
	PINS_P3
	print_diagram();
	delay(5000);

	Serial.print("Phase 4\n");
	PINS_P4
	print_diagram();
	delay(1000);

	Serial.print("Phase 5\n");
	PINS_P5
	print_diagram();
	delay(1000);

	Serial.print("Phase 6\n");
	PINS_P6
	print_diagram();
	delay(1000);

	Serial.print("Phase 7\n");
	PINS_P7
	print_diagram();
	delay(5000);

	Serial.print("Phase 8\n");
	PINS_P8
	print_diagram();
	delay(1000);

#undef SET
#undef CLR
}

void all_together(void) {
#define SET(x) digitalWrite((x), HIGH);
#define CLR(x) digitalWrite((x), LOW);

	PINS_R
	Serial.print("Red phase\n");
	delay(1000);

	PINS_Y
	Serial.print("Yellow phase\n");
	delay(1000);

	PINS_G
	Serial.print("Green phase\n");
	delay(1000);

#undef SET
#undef CLR
}

void loop_around(void) {
#define SET(x)                                                                 \
	digitalWrite((x), HIGH);                                                   \
	printf("Pin: %d\n", x);                                                    \
	delay(1000);                                                               \
	digitalWrite((x), LOW);

	PINS_ALL

#undef X
}

void setup(void) {
	Serial.begin(9600);
	Serial.print("Reset…");
#define SET(x)                                                                 \
	pinMode((x), OUTPUT);                                                      \
	digitalWrite((x), HIGH);

	PINS_ALL

	Serial.print(" done\n");
	delay(1000);
	clear_all();
#undef X
}

void loop(void) {
	standard();
}
