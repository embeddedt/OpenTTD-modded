/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file airport_movement.h Heart of the airports and their finite state machines */

#ifndef AIRPORT_MOVEMENT_H
#define AIRPORT_MOVEMENT_H


/**
 * State machine input struct (from external file, etc.)
 * Finite sTate mAchine --> FTA
 */
struct AirportFTAbuildup {
	uint16 position; ///< The position that an airplane is at.
	byte heading;    ///< The current orders (eg. TAKEOFF, HANGAR, ENDLANDING, etc.).
	uint64 block;    ///< The block this position is on on the airport (st->airport.flags).
    uint64 block2;   ///< The block this position is on on the airport (st->airport.flags2).
	byte next;       ///< Next position from this position.
};

///////////////////////////////////////////////////////////////////////
/////*********Movement Positions on Airports********************///////

/**
 * Airport movement data creation macro.
 * @param x     X position.
 * @param y     Y position.
 * @param flags Movement flags.
 * @param dir   Direction.
 */
#define AMD(x, y, flags, dir) { x, y, flags, dir }

/** Dummy airport. */
static const AirportMovingData _airport_moving_data_dummy[] = {
	AMD(    0,    0, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N ),
	AMD(    0,   96, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N ),
	AMD(   96,   96, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N ),
	AMD(   96,    0, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N ),
};

/** Country Airfield (small) 4x3. */
static const AirportMovingData _airport_moving_data_country[22] = {
	AMD(   53,    3, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar
	AMD(   53,   27, 0,                               DIR_N ), // 01 Taxi to right outside depot
	AMD(   32,   23, AMED_EXACTPOS,                   DIR_NW), // 02 Terminal 1
	AMD(   10,   23, AMED_EXACTPOS,                   DIR_NW), // 03 Terminal 2
	AMD(   43,   37, 0,                               DIR_N ), // 04 Going towards terminal 2
	AMD(   24,   37, 0,                               DIR_N ), // 05 Going towards terminal 2
	AMD(   53,   37, 0,                               DIR_N ), // 06 Going for takeoff
	AMD(   61,   40, AMED_EXACTPOS,                   DIR_NE), // 07 Taxi to start of runway (takeoff)
	AMD(    3,   40, AMED_NOSPDCLAMP,                 DIR_N ), // 08 Accelerate to end of runway
	AMD(  -79,   40, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 09 Take off
	AMD(  177,   40, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 10 Fly to landing position in air
	AMD(   56,   40, AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 11 Going down for land
	AMD(    3,   40, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 12 Just landed, brake until end of runway
	AMD(    7,   40, 0,                               DIR_N ), // 13 Just landed, turn around and taxi 1 square
	AMD(   53,   40, 0,                               DIR_N ), // 14 Taxi from runway to crossing
	AMD(    1,  193, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 15 Fly around waiting for a landing spot (north-east)
	AMD(    1,    1, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 16 Fly around waiting for a landing spot (north-west)
	AMD(  257,    1, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 17 Fly around waiting for a landing spot (south-west)
	AMD(  273,   47, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 18 Fly around waiting for a landing spot (south)
	AMD(   44,   37, AMED_HELI_RAISE,                 DIR_N ), // 19 Helicopter takeoff
	AMD(   44,   40, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 20 In position above landing spot helicopter
	AMD(   44,   40, AMED_HELI_LOWER,                 DIR_N ), // 21 Helicopter landing
};

/** Commuter Airfield (small) 5x4. */
static const AirportMovingData _airport_moving_data_commuter[38] = {
	AMD(   69,    3, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar
	AMD(   72,   22, 0,                               DIR_N ), // 01 Taxi to right outside depot
	AMD(    8,   22, AMED_EXACTPOS,                   DIR_SW), // 02 Taxi to right outside depot
	AMD(   24,   36, AMED_EXACTPOS,                   DIR_SE), // 03 Terminal 1
	AMD(   40,   36, AMED_EXACTPOS,                   DIR_SE), // 04 Terminal 2
	AMD(   56,   36, AMED_EXACTPOS,                   DIR_SE), // 05 Terminal 3
	AMD(   40,    8, AMED_EXACTPOS,                   DIR_NE), // 06 Helipad 1
	AMD(   56,    8, AMED_EXACTPOS,                   DIR_NE), // 07 Helipad 2
	AMD(   24,   22, 0,                               DIR_SW), // 08 Taxiing
	AMD(   40,   22, 0,                               DIR_SW), // 09 Taxiing
	AMD(   56,   22, 0,                               DIR_SW), // 10 Taxiing
	AMD(   72,   40, 0,                               DIR_SE), // 11 Airport OUTWAY
	AMD(   72,   54, AMED_EXACTPOS,                   DIR_NE), // 12 Accelerate to end of runway
	AMD(    7,   54, AMED_NOSPDCLAMP,                 DIR_N ), // 13 Release control of runway, for smoother movement
	AMD(    5,   54, AMED_NOSPDCLAMP,                 DIR_N ), // 14 End of runway
	AMD(  -79,   54, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 15 Take off
	AMD(  145,   54, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 16 Fly to landing position in air
	AMD(   73,   54, AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 17 Going down for land
	AMD(    3,   54, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 18 Just landed, brake until end of runway
	AMD(   12,   54, AMED_SLOWTURN,                   DIR_NW), // 19 Just landed, turn around and taxi
	AMD(    8,   32, 0,                               DIR_NW), // 20 Taxi from runway to crossing
	AMD(    1,  149, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 21 Fly around waiting for a landing spot (north-east)
	AMD(    1,    6, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 22 Fly around waiting for a landing spot (north-west)
	AMD(  193,    6, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 23 Fly around waiting for a landing spot (south-west)
	AMD(  225,   62, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 24 Fly around waiting for a landing spot (south)
	/* Helicopter */
	AMD(   80,    0, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 25 Bufferspace before helipad
	AMD(   80,    0, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 26 Bufferspace before helipad
	AMD(   32,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 27 Get in position for Helipad1
	AMD(   48,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 28 Get in position for Helipad2
	AMD(   32,    8, AMED_HELI_LOWER,                 DIR_N ), // 29 Land at Helipad1
	AMD(   48,    8, AMED_HELI_LOWER,                 DIR_N ), // 30 Land at Helipad2
	AMD(   32,    8, AMED_HELI_RAISE,                 DIR_N ), // 31 Takeoff Helipad1
	AMD(   48,    8, AMED_HELI_RAISE,                 DIR_N ), // 32 Takeoff Helipad2
	AMD(   64,   22, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 33 Go to position for Hangarentrance in air
	AMD(   64,   22, AMED_HELI_LOWER,                 DIR_N ), // 34 Land in front of hangar
	AMD(   40,    8, AMED_EXACTPOS,                   DIR_N ), // 35 pre-helitakeoff helipad 1
	AMD(   56,    8, AMED_EXACTPOS,                   DIR_N ), // 36 pre-helitakeoff helipad 2
	AMD(   64,   25, AMED_HELI_RAISE,                 DIR_N ), // 37 Take off in front of hangar
};

/** City Airport (large) 6x6. */
static const AirportMovingData _airport_moving_data_city[] = {
	AMD(   85,    3, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar
	AMD(   85,   22, 0,                               DIR_N ), // 01 Taxi to right outside depot
	AMD(   26,   41, AMED_EXACTPOS,                   DIR_SW), // 02 Terminal 1
	AMD(   56,   22, AMED_EXACTPOS,                   DIR_SE), // 03 Terminal 2
	AMD(   38,    8, AMED_EXACTPOS,                   DIR_SW), // 04 Terminal 3
	AMD(   65,    6, 0,                               DIR_N ), // 05 Taxi to right in infront of terminal 2/3
	AMD(   80,   27, 0,                               DIR_N ), // 06 Taxiway terminals 2-3
	AMD(   44,   63, 0,                               DIR_N ), // 07 Taxi to Airport center
	AMD(   58,   71, 0,                               DIR_N ), // 08 Towards takeoff
	AMD(   72,   85, 0,                               DIR_N ), // 09 Taxi to runway (takeoff)
	AMD(   89,   85, AMED_EXACTPOS,                   DIR_NE), // 10 Taxi to start of runway (takeoff)
	AMD(    3,   85, AMED_NOSPDCLAMP,                 DIR_N ), // 11 Accelerate to end of runway
	AMD(  -79,   85, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 12 Take off
	AMD(  177,   87, AMED_HOLD       | AMED_SLOWTURN, DIR_N ), // 13 Fly to landing position in air
	AMD(   89,   87, AMED_HOLD       | AMED_LAND,     DIR_N ), // 14 Going down for land
	AMD(   20,   87, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 15 Just landed, brake until end of runway
	AMD(   20,   87, 0,                               DIR_N ), // 16 Just landed, turn around and taxi 1 square // NOT USED
	AMD(   36,   71, 0,                               DIR_N ), // 17 Taxi from runway to crossing
	AMD(  160,   87, AMED_HOLD       | AMED_SLOWTURN, DIR_N ), // 18 Fly around waiting for a landing spot (north-east)
	AMD(  140,    1, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 19 Final approach fix
	AMD(  257,    1, AMED_HOLD       | AMED_SLOWTURN, DIR_N ), // 20 Fly around waiting for a landing spot (south-west)
	AMD(  273,   49, AMED_HOLD       | AMED_SLOWTURN, DIR_N ), // 21 Fly around waiting for a landing spot (south)
	AMD(   44,   63, AMED_HELI_RAISE,                 DIR_N ), // 22 Helicopter takeoff
	AMD(   28,   74, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 23 In position above landing spot helicopter
	AMD(   28,   74, AMED_HELI_LOWER,                 DIR_N ), // 24 Helicopter landing
	AMD(  145,    1, AMED_HOLD       | AMED_SLOWTURN, DIR_N ), // 25 Fly around waiting for a landing spot (north-west)
	AMD(  -32,    1, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 26 Initial approach fix (north)
	AMD(  300,  -48, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 27 Initial approach fix (south)
	AMD(  140,  -48, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 28 Intermediate Approach fix (south), IAF (west)
	AMD(  -32,  120, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 29 Initial approach fix (east)
};

/** Metropolitan Airport (metropolitan) - 2 runways. */
static const AirportMovingData _airport_moving_data_metropolitan[28] = {
	AMD(   85,    3, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar
	AMD(   85,   22, 0,                               DIR_N ), // 01 Taxi to right outside depot
	AMD(   26,   41, AMED_EXACTPOS,                   DIR_SW), // 02 Terminal 1
	AMD(   56,   22, AMED_EXACTPOS,                   DIR_SE), // 03 Terminal 2
	AMD(   38,    8, AMED_EXACTPOS,                   DIR_SW), // 04 Terminal 3
	AMD(   65,    6, 0,                               DIR_N ), // 05 Taxi to right in infront of terminal 2/3
	AMD(   80,   27, 0,                               DIR_N ), // 06 Taxiway terminals 2-3
	AMD(   49,   58, 0,                               DIR_N ), // 07 Taxi to Airport center
	AMD(   72,   58, 0,                               DIR_N ), // 08 Towards takeoff
	AMD(   72,   69, 0,                               DIR_N ), // 09 Taxi to runway (takeoff)
	AMD(   89,   69, AMED_EXACTPOS,                   DIR_NE), // 10 Taxi to start of runway (takeoff)
	AMD(    3,   69, AMED_NOSPDCLAMP,                 DIR_N ), // 11 Accelerate to end of runway
	AMD(  -79,   69, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 12 Take off
	AMD(  177,   85, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 13 Fly to landing position in air
	AMD(   89,   85, AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 14 Going down for land
	AMD(    3,   85, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 15 Just landed, brake until end of runway
	AMD(   21,   85, 0,                               DIR_N ), // 16 Just landed, turn around and taxi 1 square
	AMD(   21,   69, 0,                               DIR_N ), // 17 On Runway-out taxiing to In-Way
	AMD(   21,   58, AMED_EXACTPOS,                   DIR_SW), // 18 Taxi from runway to crossing
	AMD(    1,  193, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 19 Fly around waiting for a landing spot (north-east)
	AMD(    1,    1, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 20 Fly around waiting for a landing spot (north-west)
	AMD(  257,    1, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 21 Fly around waiting for a landing spot (south-west)
	AMD(  273,   49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 22 Fly around waiting for a landing spot (south)
	AMD(   44,   58, 0,                               DIR_N ), // 23 Helicopter takeoff spot on ground (to clear airport sooner)
	AMD(   44,   63, AMED_HELI_RAISE,                 DIR_N ), // 24 Helicopter takeoff
	AMD(   15,   54, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 25 Get in position above landing spot helicopter
	AMD(   15,   54, AMED_HELI_LOWER,                 DIR_N ), // 26 Helicopter landing
	AMD(   21,   58, AMED_EXACTPOS,                   DIR_SW), // 27 Transitions after landing to on-ground movement
};

/** International Airport (international) - 2 runways, 6 terminals, dedicated helipad. */
static const AirportMovingData _airport_moving_data_international[53] = {
	AMD(    7,   55, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar 1
	AMD(  100,   21, AMED_EXACTPOS,                   DIR_SE), // 01 In Hangar 2
	AMD(    7,   70, 0,                               DIR_N ), // 02 Taxi to right outside depot (Hangar 1)
	AMD(  100,   36, 0,                               DIR_N ), // 03 Taxi to right outside depot (Hangar 2)
	AMD(   38,   70, AMED_EXACTPOS,                   DIR_SW), // 04 Terminal 1
	AMD(   38,   54, AMED_EXACTPOS,                   DIR_SW), // 05 Terminal 2
	AMD(   38,   38, AMED_EXACTPOS,                   DIR_SW), // 06 Terminal 3
	AMD(   70,   70, AMED_EXACTPOS,                   DIR_NE), // 07 Terminal 4
	AMD(   70,   54, AMED_EXACTPOS,                   DIR_NE), // 08 Terminal 5
	AMD(   70,   38, AMED_EXACTPOS,                   DIR_NE), // 09 Terminal 6
	AMD(  104,   71, AMED_EXACTPOS,                   DIR_NE), // 10 Helipad 1
	AMD(  104,   55, AMED_EXACTPOS,                   DIR_NE), // 11 Helipad 2
	AMD(   22,   87, 0,                               DIR_N ), // 12 Towards Terminals 4/5/6, Helipad 1/2
	AMD(   60,   87, 0,                               DIR_N ), // 13 Towards Terminals 4/5/6, Helipad 1/2
	AMD(   66,   87, 0,                               DIR_N ), // 14 Towards Terminals 4/5/6, Helipad 1/2
	AMD(   86,   87, AMED_EXACTPOS,                   DIR_NW), // 15 Towards Terminals 4/5/6, Helipad 1/2
	AMD(   86,   70, 0,                               DIR_N ), // 16 In Front of Terminal 4 / Helipad 1
	AMD(   86,   54, 0,                               DIR_N ), // 17 In Front of Terminal 5 / Helipad 2
	AMD(   86,   38, 0,                               DIR_N ), // 18 In Front of Terminal 6
	AMD(   86,   22, 0,                               DIR_N ), // 19 Towards Terminals Takeoff (Taxiway)
	AMD(   66,   22, 0,                               DIR_N ), // 20 Towards Terminals Takeoff (Taxiway)
	AMD(   60,   22, 0,                               DIR_N ), // 21 Towards Terminals Takeoff (Taxiway)
	AMD(   38,   22, 0,                               DIR_N ), // 22 Towards Terminals Takeoff (Taxiway)
	AMD(   22,   70, 0,                               DIR_N ), // 23 In Front of Terminal 1
	AMD(   22,   58, 0,                               DIR_N ), // 24 In Front of Terminal 2
	AMD(   22,   38, 0,                               DIR_N ), // 25 In Front of Terminal 3
	AMD(   22,   22, AMED_EXACTPOS,                   DIR_NW), // 26 Going for Takeoff
	AMD(   22,    6, 0,                               DIR_N ), // 27 On Runway-out, prepare for takeoff
	AMD(    3,    6, AMED_EXACTPOS,                   DIR_SW), // 28 Accelerate to end of runway
	AMD(   60,    6, AMED_NOSPDCLAMP,                 DIR_N ), // 29 Release control of runway, for smoother movement
	AMD(  105,    6, AMED_NOSPDCLAMP,                 DIR_N ), // 30 End of runway
	AMD(  190,    6, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 31 Take off
	AMD(  193,  104, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 32 Fly to landing position in air
	AMD(  105,  104, AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 33 Going down for land
	AMD(    3,  104, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 34 Just landed, brake until end of runway
	AMD(   12,  104, AMED_SLOWTURN,                   DIR_N ), // 35 Just landed, turn around and taxi 1 square
	AMD(    7,   84, 0,                               DIR_N ), // 36 Taxi from runway to crossing
	AMD(    1,  209, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 37 Fly around waiting for a landing spot (north-east)
	AMD(    1,    6, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 38 Fly around waiting for a landing spot (north-west)
	AMD(  273,    6, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 39 Fly around waiting for a landing spot (south-west)
	AMD(  305,   81, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 40 Fly around waiting for a landing spot (south)
	/* Helicopter */
	AMD(  128,   80, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 41 Bufferspace before helipad
	AMD(  128,   80, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 42 Bufferspace before helipad
	AMD(   96,   71, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 43 Get in position for Helipad1
	AMD(   96,   55, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 44 Get in position for Helipad2
	AMD(   96,   71, AMED_HELI_LOWER,                 DIR_N ), // 45 Land at Helipad1
	AMD(   96,   55, AMED_HELI_LOWER,                 DIR_N ), // 46 Land at Helipad2
	AMD(  104,   71, AMED_HELI_RAISE,                 DIR_N ), // 47 Takeoff Helipad1
	AMD(  104,   55, AMED_HELI_RAISE,                 DIR_N ), // 48 Takeoff Helipad2
	AMD(  104,   32, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 49 Go to position for Hangarentrance in air
	AMD(  104,   32, AMED_HELI_LOWER,                 DIR_N ), // 50 Land in HANGAR2_AREA to go to hangar
	AMD(    7,   70, AMED_HELI_RAISE,                 DIR_N ), // 51 Takeoff from HANGAR1_AREA
	AMD(  100,   36, AMED_HELI_RAISE,                 DIR_N ), // 52 Takeoff from HANGAR2_AREA
};

/** Intercontinental Airport - 4 runways, 8 terminals, 2 dedicated helipads. */
static const AirportMovingData _airport_moving_data_intercontinental[77] = {
	AMD(    8,   87, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar 1
	AMD(  136,   72, AMED_EXACTPOS,                   DIR_SE), // 01 In Hangar 2
	AMD(    8,  104, 0,                               DIR_N ), // 02 Taxi to right outside depot 1
	AMD(  136,   88, 0,                               DIR_N ), // 03 Taxi to right outside depot 2
	AMD(   56,  120, AMED_EXACTPOS,                   DIR_W ), // 04 Terminal 1
	AMD(   56,  104, AMED_EXACTPOS,                   DIR_SW), // 05 Terminal 2
	AMD(   56,   88, AMED_EXACTPOS,                   DIR_SW), // 06 Terminal 3
	AMD(   56,   72, AMED_EXACTPOS,                   DIR_SW), // 07 Terminal 4
	AMD(   88,  120, AMED_EXACTPOS,                   DIR_N ), // 08 Terminal 5
	AMD(   88,  104, AMED_EXACTPOS,                   DIR_NE), // 09 Terminal 6
	AMD(   88,   88, AMED_EXACTPOS,                   DIR_NE), // 10 Terminal 7
	AMD(   88,   72, AMED_EXACTPOS,                   DIR_NE), // 11 Terminal 8
	AMD(   88,   56, AMED_EXACTPOS,                   DIR_SE), // 12 Helipad 1
	AMD(   72,   56, AMED_EXACTPOS,                   DIR_NE), // 13 Helipad 2
	AMD(   40,  136, 0,                               DIR_N ), // 14 Term group 2 enter 1 a
	AMD(   56,  136, 0,                               DIR_N ), // 15 Term group 2 enter 1 b
	AMD(   88,  136, 0,                               DIR_N ), // 16 Term group 2 enter 2 a
	AMD(  104,  136, 0,                               DIR_N ), // 17 Term group 2 enter 2 b
	AMD(  104,  120, 0,                               DIR_N ), // 18 Term group 2 - opp term 5
	AMD(  104,  104, 0,                               DIR_N ), // 19 Term group 2 - opp term 6 & exit2
	AMD(  104,   88, 0,                               DIR_N ), // 20 Term group 2 - opp term 7 & hangar area 2
	AMD(  104,   72, 0,                               DIR_N ), // 21 Term group 2 - opp term 8
	AMD(  104,   56, 0,                               DIR_N ), // 22 Taxi Term group 2 exit a
	AMD(  104,   40, 0,                               DIR_N ), // 23 Taxi Term group 2 exit b
	AMD(   56,   40, 0,                               DIR_N ), // 24 Term group 2 exit 2a
	AMD(   40,   40, 0,                               DIR_N ), // 25 Term group 2 exit 2b
	AMD(   40,  120, 0,                               DIR_N ), // 26 Term group 1 - opp term 1
	AMD(   40,  104, 0,                               DIR_N ), // 27 Term group 1 - opp term 2 & hangar area 1
	AMD(   40,   88, 0,                               DIR_N ), // 28 Term group 1 - opp term 3
	AMD(   40,   72, 0,                               DIR_N ), // 29 Term group 1 - opp term 4
	AMD(   18,   72, 0,                               DIR_NW), // 30 Outway 1
	AMD(    8,   40, 0,                               DIR_NW), // 31 Airport OUTWAY
	AMD(    8,   24, AMED_EXACTPOS,                   DIR_SW), // 32 Accelerate to end of runway
	AMD(  119,   24, AMED_NOSPDCLAMP,                 DIR_N ), // 33 Release control of runway, for smoother movement
	AMD(  117,   24, AMED_NOSPDCLAMP,                 DIR_N ), // 34 End of runway
	AMD(  197,   24, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 35 Take off
	AMD(  254,   84, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 36 Flying to landing position in air
	AMD(  117,  168, AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 37 Going down for land
	AMD(    8,  168, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 38 Just landed, brake until end of runway
	AMD(    8,  168, 0,                               DIR_N ), // 39 Just landed, turn around and taxi
	AMD(    8,  144, 0,                               DIR_NW), // 40 Taxi from runway
	AMD(    8,  128, 0,                               DIR_NW), // 41 Taxi from runway
	AMD(    8,  120, AMED_EXACTPOS,                   DIR_NW), // 42 Airport entrance
	AMD(   56,  344, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 43 Fly around waiting for a landing spot (north-east)
	AMD( -200,   88, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 44 Fly around waiting for a landing spot (north-west)
	AMD(   56, -168, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 45 Fly around waiting for a landing spot (south-west)
	AMD(  312,   88, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 46 Fly around waiting for a landing spot (south)
	/* Helicopter */
	AMD(   96,   40, AMED_NOSPDCLAMP,                 DIR_N ), // 47 Bufferspace before helipad
	AMD(   96,   40, AMED_NOSPDCLAMP,                 DIR_N ), // 48 Bufferspace before helipad
	AMD(   82,   54, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 49 Get in position for Helipad1
	AMD(   64,   56, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 50 Get in position for Helipad2
	AMD(   81,   55, AMED_HELI_LOWER,                 DIR_N ), // 51 Land at Helipad1
	AMD(   64,   56, AMED_HELI_LOWER,                 DIR_N ), // 52 Land at Helipad2
	AMD(   80,   56, AMED_HELI_RAISE,                 DIR_N ), // 53 Takeoff Helipad1
	AMD(   64,   56, AMED_HELI_RAISE,                 DIR_N ), // 54 Takeoff Helipad2
	AMD(  136,   96, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 55 Go to position for Hangarentrance in air
	AMD(  136,   96, AMED_HELI_LOWER,                 DIR_N ), // 56 Land in front of hangar2
	AMD(  126,  104, 0,                               DIR_SE), // 57 Outway 2
	AMD(  136,  136, 0,                               DIR_NE), // 58 Airport OUTWAY 2
	AMD(  136,  152, AMED_EXACTPOS,                   DIR_NE), // 59 Accelerate to end of runway2
	AMD(   16,  152, AMED_NOSPDCLAMP,                 DIR_N ), // 60 Release control of runway2, for smoother movement
	AMD(   20,  152, AMED_NOSPDCLAMP,                 DIR_N ), // 61 End of runway2
	AMD(  -56,  152, AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 62 Take off2
	AMD(   24,    8, AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 63 Going down for land2
	AMD(  136,    8, AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 64 Just landed, brake until end of runway2in
	AMD(  136,    8, 0,                               DIR_N ), // 65 Just landed, turn around and taxi
	AMD(  136,   24, 0,                               DIR_SE), // 66 Taxi from runway 2in
	AMD(  136,   40, 0,                               DIR_SE), // 67 Taxi from runway 2in
	AMD(  136,   56, AMED_EXACTPOS,                   DIR_NE), // 68 Airport entrance2
	AMD(  -56,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 69 Fly to landing position in air2
	AMD(   88,   40, 0,                               DIR_N ), // 70 Taxi Term group 2 exit - opp heli1
	AMD(   72,   40, 0,                               DIR_N ), // 71 Taxi Term group 2 exit - opp heli2
	AMD(   88,   57, AMED_EXACTPOS,                   DIR_SE), // 72 pre-helitakeoff helipad 1
	AMD(   71,   56, AMED_EXACTPOS,                   DIR_NE), // 73 pre-helitakeoff helipad 2
	AMD(    8,  120, AMED_HELI_RAISE,                 DIR_N ), // 74 Helitakeoff outside depot 1
	AMD(  136,  104, AMED_HELI_RAISE,                 DIR_N ), // 75 Helitakeoff outside depot 2
	AMD(  197,  168, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 76 Fly to landing position in air1
};

 
//** Intercontinental 2 */
static const AirportMovingData _airport_moving_data_intercontinental2[] = {
	AMD(   8,    21, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar
	AMD(   184,  21, AMED_EXACTPOS,                   DIR_SE), // 01 In Hangar2
	AMD(   8,    38, 0,                               DIR_N),  // 02 Taxi outside depot
	AMD(   184,  38, 0,                               DIR_N),  // 03 Taxi outside depot2
	AMD(   24,   22, AMED_EXACTPOS,                   DIR_NW), // 04 Terminal 1
	AMD(   40,   22, AMED_EXACTPOS,                   DIR_NW), // 05 Terminal 2
	AMD(   56,   22, AMED_EXACTPOS,                   DIR_NW), // 06 Terminal 3
	AMD(   72,   22, AMED_EXACTPOS,                   DIR_NW), // 07 Terminal 4
	AMD(   120,  22, AMED_EXACTPOS,                   DIR_NW), // 08 Terminal 5
	AMD(   136,  22, AMED_EXACTPOS,                   DIR_NW), // 09 Terminal 6
	AMD(   152,  22, AMED_EXACTPOS,                   DIR_NW), // 10 Terminal 7
	AMD(   168,  22, AMED_EXACTPOS,                   DIR_NW), // 11 Terminal 8
	AMD(   24,   38, 0,                               DIR_N ), // 12 taxi 1
	AMD(   40,   38, 0,                               DIR_N ), // 13 taxi 2
	AMD(   56,   38, 0,                               DIR_N ), // 14 taxi 3
	AMD(   72,   38, 0,                               DIR_N ), // 15 taxi 4
	AMD(   120,  38, 0,                               DIR_N ), // 16 taxi 5
	AMD(   136,  38, 0,                               DIR_N ), // 17 taxi 6
	AMD(   152,  38, 0,                               DIR_N ), // 18 taxi 7
	AMD(   168,  38, 0,                               DIR_N ), // 19 taxi 8
	AMD(   184,  54, 0,                               DIR_N ), // 20 pre-Fly or Gate?
	AMD(   184,  70, 0,                               DIR_N ), // 21 Fly or Gate?
	AMD(   168,  70, 0,                               DIR_N ), // 22 Answer: Gate
	AMD(   152,  70, 0,                               DIR_N ), // 23 Terminal 7,8 Free?
	AMD(   120,  70, 0,                               DIR_N ), // 24 Terminal 5,6 Free?
	AMD(   72,   70, 0,                               DIR_N ), // 25 Terminal 4 Free?
	AMD(   40,   70, 0,                               DIR_N ), // 26 Terminal 2,3 Free? or DEPO?
	AMD(   8,    70, 0,                               DIR_N ), // 27 pre-pre-outside depot
	AMD(   8,    54, 0,                               DIR_N ), // 28 pre-outside depo
	AMD(   88,   38, 0,                               DIR_N ), // 29 taxi helipad 1
	AMD(   104,  38, 0,                               DIR_N ), // 30 taxi helipad 2
	AMD(   184,  86, 0,                               DIR_N ), // 31 Answer: Fly
	AMD(   184,  102,0,                               DIR_N ), // 32 pre-runway 1 or 2 out crossing
	AMD(   184,  118,0,                               DIR_N ), // 33 runway 1 or 2 out crossing
	AMD(   184,  134,0,                               DIR_N ), // 34 taxi near runway 1
	AMD(   168,  118,0,                               DIR_N ), // 35 taxi near runway 2
	AMD(   8,    118,0,                               DIR_N ), // 36 after land runway 1b (pre-crossing)
	AMD(   24,   102,0,                               DIR_N ), // 37 after land runway 2b (pre-crossing)
	AMD(   8,    102,0,                               DIR_N ), // 38 after land crossing
	AMD(   8,    86, 0,                               DIR_N ), // 39 after crossing - enter airport
	AMD(   184,  150,AMED_EXACTPOS,                   DIR_NE), // 40 taxi to end position
	AMD(   88,   150,AMED_NOSPDCLAMP,                 DIR_N ), // 41 runway end
	AMD(  -2,    150,AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 42 takeoff
	AMD(   156,  118,AMED_EXACTPOS,                   DIR_NE), // 43 taxi to end position 2
	AMD(   56,   118,AMED_NOSPDCLAMP,                 DIR_N ), // 44 runway end 2
	AMD(  -34,   118,AMED_NOSPDCLAMP | AMED_TAKEOFF,  DIR_N ), // 45 takeoff 2
	AMD(   88,   24, AMED_EXACTPOS,                   DIR_NE), // 46 Helipad 1
	AMD(  104,   24, AMED_EXACTPOS,                   DIR_NE), // 47 Helipad 2
	AMD(  224,   134,AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 48 Fly to landing position in air 1
	AMD(  104,   134,AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 49 Going down for land 1
	AMD(    8,   134,AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 50 brake until end 1
	AMD(  256,   102,AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 51 Fly to landing position in air 2
 	AMD(  136,   102,AMED_NOSPDCLAMP | AMED_LAND,     DIR_N ), // 52 Going down for land 2
	AMD(   40,   102,AMED_NOSPDCLAMP | AMED_BRAKE,    DIR_N ), // 53 brake until end 2
	AMD(  136,   280,AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 54 fly around
	AMD(  500,   300,AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 55 fly around
 	AMD(  104,  -40, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 56 fly around
	AMD(  500,  -60, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 57 fly around
	AMD(  104,   70, 0,                               DIR_N ), // 58 taxi
	AMD(   88,   70, 0,                               DIR_N ), // 59 taxi
	AMD(   88,   24, AMED_EXACTPOS,                   DIR_SE), // 60 pre-helitakeoff helipad 1
	AMD(  104,   24, AMED_EXACTPOS,                   DIR_SE), // 61 pre-helitakeoff helipad 2
	AMD(   80,   24, AMED_HELI_RAISE,                 DIR_N ), // 62 Takeoff Helipad1
	AMD(   96,   24, AMED_HELI_RAISE,                 DIR_N ), // 63 Takeoff Helipad2
	AMD(   80,   24, AMED_HELI_LOWER,                 DIR_N ), // 64 Land at Helipad1
	AMD(   96,   24, AMED_HELI_LOWER,                 DIR_N ), // 65 Land at Helipad2
	AMD(  140,    0, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 66 Bufferspace before helipad
	AMD(  140,    0, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 67 Bufferspace before helipad
	AMD(   80,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 68 Get in position for Helipad1
	AMD(   96,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 69 Get in position for Helipad2
	AMD(   88,   70, AMED_HELI_RAISE,                 DIR_N ), // 70 Takeoff from taxi
	AMD(  520,   80, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 71 fly around
	AMD(  520,  160, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 72 fly around
	AMD(  192,   38, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 73 Go to position for Hangarentrance in air
	AMD(  192,   38, AMED_HELI_LOWER,                 DIR_N ), // 74 Land in front of hangar
};

static const AirportMovingData _airport_moving_data_circle[] = {
	AMD(  104,  104, AMED_EXACTPOS,                       DIR_SW ),  // 00 In Hangar 1
	AMD(  104,  136, AMED_EXACTPOS,                       DIR_NW ),  // 01 In Hangar 2
	AMD(  136,  104, AMED_EXACTPOS,                       DIR_SE ),  // 02 In Hangar 3
	AMD(  136,  136, AMED_EXACTPOS,                       DIR_NE ),  // 03 In Hangar 4
	AMD(  120,  104, 0,                                   DIR_N  ),  // 04 Taxi outside depot 1
	AMD(  104,  120, 0,                                   DIR_N  ),  // 05 Taxi outside depot 2
	AMD(  136,  120, 0,                                   DIR_N  ),  // 06 Taxi outside depot 3
	AMD(  120,  136, 0,                                   DIR_N  ),  // 07 Taxi outside depot 4
	AMD(   72,  168, AMED_EXACTPOS,                       DIR_W  ),  // 08 Terminal 1
	AMD(   72,  152, AMED_EXACTPOS,                       DIR_SW ),  // 09 Terminal 2
	AMD(   72,  136, AMED_EXACTPOS,                       DIR_S  ),  // 10 Terminal 3
	AMD(   72,  104, AMED_EXACTPOS,                       DIR_W  ),  // 11 Terminal 4
	AMD(   72,   88, AMED_EXACTPOS,                       DIR_SW ),  // 12 Terminal 5
	AMD(   72,   72, AMED_EXACTPOS,                       DIR_S  ),  // 13 Terminal 6
	AMD(   88,   72, AMED_EXACTPOS,                       DIR_SE ),  // 14 Terminal 7
	AMD(  104,   72, AMED_EXACTPOS,                       DIR_E  ),  // 15 Terminal 8
	AMD(  136,   72, AMED_EXACTPOS,                       DIR_S  ),  // 16 Terminal 9
	AMD(  152,   72, AMED_EXACTPOS,                       DIR_SE ),  // 17 Terminal 10
	AMD(  168,   72, AMED_EXACTPOS,                       DIR_E  ),  // 18 Terminal 11
	AMD(  168,   86, AMED_EXACTPOS,                       DIR_NE ),  // 19 Terminal 12
	AMD(  168,  104, AMED_EXACTPOS,                       DIR_N  ),  // 20 Terminal 13
	AMD(  168,  136, AMED_EXACTPOS,                       DIR_E  ),  // 21 Terminal 14
	AMD(  168,  152, AMED_EXACTPOS,                       DIR_NE ),  // 22 Terminal 15
	AMD(  168,  168, AMED_EXACTPOS,                       DIR_N  ),  // 23 Terminal 16
	AMD(  152,  168, AMED_EXACTPOS,                       DIR_NW ),  // 24 Terminal 17
	AMD(  136,  168, AMED_EXACTPOS,                       DIR_W  ),  // 25 Terminal 18
	AMD(  104,  168, AMED_EXACTPOS,                       DIR_N  ),  // 26 Terminal 19
	AMD(   88,  168, AMED_EXACTPOS,                       DIR_NW ),  // 27 Terminal 20
	AMD(   72,  184, 0,                                   DIR_N  ),  // 28 taxi 1a
	AMD(   56,  168, 0,                                   DIR_N  ),  // 29 taxi 1b
	AMD(   56,  152, 0,                                   DIR_N  ),  // 30 taxi 2
	AMD(   56,  136, 0,                                   DIR_N  ),  // 31 taxi 3a
	AMD(   72,  120, 0,                                   DIR_N  ),  // 32 taxi 3b4b
	AMD(   56,  104, 0,                                   DIR_N  ),  // 33 taxi 4a
	AMD(   56,   88, 0,                                   DIR_N  ),  // 34 taxi 5
	AMD(   56,   72, 0,                                   DIR_N  ),  // 35 taxi 6a
	AMD(   72,   56, 0,                                   DIR_N  ),  // 36 taxi 6b
	AMD(   88,   56, 0,                                   DIR_N  ),  // 37 taxi 7
	AMD(  104,   56, 0,                                   DIR_N  ),  // 38 taxi 8a
	AMD(  120,   72, 0,                                   DIR_N  ),  // 39 taxi 8b9b
	AMD(  136,   56, 0,                                   DIR_N  ),  // 40 taxi 9a
	AMD(  152,   56, 0,                                   DIR_N  ),  // 41 taxi 10
	AMD(  168,   56, 0,                                   DIR_N  ),  // 42 taxi 11a
	AMD(  184,   72, 0,                                   DIR_N  ),  // 43 taxi 11b
	AMD(  184,   88, 0,                                   DIR_N  ),  // 44 taxi 12
	AMD(  184,  104, 0,                                   DIR_N  ),  // 45 taxi 13a
	AMD(  168,  120, 0,                                   DIR_N  ),  // 46 taxi 13b14b
	AMD(  184,  136, 0,                                   DIR_N  ),  // 47 taxi 14a
	AMD(  184,  152, 0,                                   DIR_N  ),  // 48 taxi 15
	AMD(  184,  168, 0,                                   DIR_N  ),  // 49 taxi 16a
	AMD(  168,  184, 0,                                   DIR_N  ),  // 50 taxi 16b
	AMD(  152,  184, 0,                                   DIR_N  ),  // 51 taxi 17
	AMD(  136,  184, 0,                                   DIR_N  ),  // 52 taxi 18a
	AMD(  120,  168, 0,                                   DIR_N  ),  // 53 taxi 18b19b
	AMD(  104,  184, 0,                                   DIR_N  ),  // 54 taxi 19a
	AMD(   88,  184, 0,                                   DIR_N  ),  // 55 taxi 20
	AMD(   56,  184, 0,                                   DIR_N  ),  // 56 taxi 1a to 1b
	AMD(   56,  120, 0,                                   DIR_N  ),  // 57 taxi 3a to 4a x 3b4b
	AMD(   56,   56, 0,                                   DIR_N  ),  // 58 taxi 6a to 6b
	AMD(  120,   56, 0,                                   DIR_N  ),  // 59 taxi 8a to 9a x 8b9b
	AMD(  184,   56, 0,                                   DIR_N  ),  // 60 taxi 11a to 11b
	AMD(  184,  120, 0,                                   DIR_N  ),  // 61 taxi 13a to 14a x 13b14b
	AMD(  184,  184, 0,                                   DIR_N  ),  // 62 taxi 16a to 16b
	AMD(  120,  184, 0,                                   DIR_N  ),  // 63 taxi 18a to 19a x 18b19b
	AMD(   40,  176, 0,                                   DIR_N  ),  // 64 taxi to 1a->1b part 1
	AMD(   48,  184, 0,                                   DIR_N  ),  // 65 taxi to 1a->1b part 2
	AMD(   40,  152, 0,                                   DIR_N  ),  // 66 taxi to 2
	AMD(   48,  120, 0,                                   DIR_N  ),  // 67 taxi from 3a->4a to takeoff part 1
	AMD(   40,  128, 0,                                   DIR_N  ),  // 68 taxi from 3a->4a to takeoff part 2
	AMD(   32,  136, 0,                                   DIR_N  ),  // 69 taxi from 3a->4a to takeoff part 3
	AMD(   48,   88, 0,                                   DIR_N  ),  // 70 taxi from 5 to takeoff part 1
	AMD(   40,   96, 0,                                   DIR_N  ),  // 71 taxi from 5 to takeoff part 2
	AMD(   48,   56, 0,                                   DIR_N  ),  // 72 taxi from 6a->6b to takeoff part 1
	AMD(   40,   64, 0,                                   DIR_N  ),  // 73 taxi from 6a->6b to takeoff part 2
	AMD(   64,   40, 0,                                   DIR_N  ),  // 74 taxi to 6a->6b part 1
	AMD(   56,   48, 0,                                   DIR_N  ),  // 75 taxi to 6a->6b part 2
	AMD(   88,   40, 0,                                   DIR_N  ),  // 76 taxi to 7
	AMD(  120,   48, 0,                                   DIR_N  ),  // 77 taxi from 8a->9a to takeoff part 1
	AMD(  112,   40, 0,                                   DIR_N  ),  // 78 taxi from 8a->9a to takeoff part 2
	AMD(  104,   32, 0,                                   DIR_N  ),  // 79 taxi from 8a->9a to takeoff part 3
	AMD(  152,   48, 0,                                   DIR_N  ),  // 80 taxi from 10 to takeoff part 1
	AMD(  144,   40, 0,                                   DIR_N  ),  // 81 taxi from 10 to takeoff part 2
	AMD(  184,   48, 0,                                   DIR_N  ),  // 82 taxi from 11a->11b to takeoff part 1
	AMD(  176,   40, 0,                                   DIR_N  ),  // 83 taxi from 11a->11b to takeoff part 2
	AMD(  200,   64, 0,                                   DIR_N  ),  // 84 taxi to 11a->11b part 1
	AMD(  192,   56, 0,                                   DIR_N  ),  // 85 taxi to 11a->11b part 2
	AMD(  200,   88, 0,                                   DIR_N  ),  // 86 taxi to 12
	AMD(  192,  120, 0,                                   DIR_N  ),  // 87 taxi from 13a->14a to takeoff part 1
	AMD(  200,  112, 0,                                   DIR_N  ),  // 88 taxi from 13a->14a to takeoff part 2
	AMD(  208,  104, 0,                                   DIR_N  ),  // 89 taxi from 13a->14a to takeoff part 3
	AMD(  192,  152, 0,                                   DIR_N  ),  // 90 taxi from 15 to takeoff part 1
	AMD(  200,  144, 0,                                   DIR_N  ),  // 91 taxi from 15 to takeoff part 2
	AMD(  192,  184, 0,                                   DIR_N  ),  // 92 taxi from 16a->16b to takeoff part 1
	AMD(  200,  176, 0,                                   DIR_N  ),  // 93 taxi from 16a->16b to takeoff part 2
	AMD(  176,  200, 0,                                   DIR_N  ),  // 94 taxi to 16a->16b part 1
	AMD(  184,  192, 0,                                   DIR_N  ),  // 95 taxi to 16a->16b part 2
	AMD(  152,  200, 0,                                   DIR_N  ),  // 96 taxi to 17
	AMD(  120,  192, 0,                                   DIR_N  ),  // 97 taxi from 18a->19a to takeoff part 1
	AMD(  128,  200, 0,                                   DIR_N  ),  // 98 taxi from 18a->19a to takeoff part 2
	AMD(  136,  208, 0,                                   DIR_N  ),  // 99 taxi from 18a->19a to takeoff part 3
	AMD(   88,  192, 0,                                   DIR_N  ),  // 100 taxi from 20 to takeoff part 1
	AMD(   96,  200, 0,                                   DIR_N  ),  // 101 taxi from 20 to takeoff part 2
	AMD(   56,  192, 0,                                   DIR_N  ),  // 102 taxi from 1a->1b to takeoff part 1
	AMD(   64,  200, 0,                                   DIR_N  ),  // 103 taxi from 1a->1b to takeoff part 2
	AMD(   24,   80, 0,                                   DIR_N  ),  // 104 pre takeoff n1
	AMD(   24,   86, 0,                                   DIR_N  ),  // 105 pre takeoff n2p
	AMD(   24,  112, 0,                                   DIR_N  ),  // 106 pre takeoff n3
	AMD(   24,  118, 0,                                   DIR_N  ),  // 107 pre takeoff n4p
	AMD(   24,  136, 0,                                   DIR_N  ),  // 108 pre takeoff n5p
	AMD(   16,  152, 0,                                   DIR_N  ),  // 109 afterland n6
	AMD(   24,  152, 0,                                   DIR_N  ),  // 110 afterland n7ap
	AMD(   24,  160, 0,                                   DIR_N  ),  // 111 afterland n7bp
	AMD(  160,   24, 0,                                   DIR_N  ),  // 112 pre takeoff w1
	AMD(  154,   24, 0,                                   DIR_N  ),  // 113 pre takeoff w2p
	AMD(  128,   24, 0,                                   DIR_N  ),  // 114 pre takeoff w3
	AMD(  122,   24, 0,                                   DIR_N  ),  // 115 pre takeoff w4p
	AMD(  104,   24, 0,                                   DIR_N  ),  // 116 pre takeoff w5p
	AMD(   88,   16, 0,                                   DIR_N  ),  // 117 afterland w6
	AMD(   88,   24, 0,                                   DIR_N  ),  // 118 afterland w7ap
	AMD(   80,   24, 0,                                   DIR_N  ),  // 119 afterland w7bp
	AMD(  216,  160, 0,                                   DIR_N  ),  // 120 pre takeoff s1
	AMD(  216,  154, 0,                                   DIR_N  ),  // 121 pre takeoff s2p
	AMD(  216,  128, 0,                                   DIR_N  ),  // 122 pre takeoff s3
	AMD(  216,  122, 0,                                   DIR_N  ),  // 123 pre takeoff s4p
	AMD(  216,  104, 0,                                   DIR_N  ),  // 124 pre takeoff s5p
	AMD(  224,   88, 0,                                   DIR_N  ),  // 125 afterland s6
	AMD(  216,   88, 0,                                   DIR_N  ),  // 126 afterland s7ap
	AMD(  216,   80, 0,                                   DIR_N  ),  // 127 afterland s7bp
	AMD(   80,  216, 0,                                   DIR_N  ),  // 128 pre takeoff e1
	AMD(   86,  216, 0,                                   DIR_N  ),  // 129 pre takeoff e2p
	AMD(  112,  216, 0,                                   DIR_N  ),  // 130 pre takeoff e3
	AMD(  118,  216, 0,                                   DIR_N  ),  // 131 pre takeoff e4p
	AMD(  136,  216, 0,                                   DIR_N  ),  // 132 pre takeoff e5p
	AMD(  152,  224, 0,                                   DIR_N  ),  // 133 afterland e6
	AMD(  152,  216, 0,                                   DIR_N  ),  // 134 afterland e7ap
	AMD(  160,  216, 0,                                   DIR_N  ),  // 135 afterland e7bp
	AMD(    8,  136, AMED_EXACTPOS,                       DIR_NW ),  // 136 Taxi to start of runway 1b
	AMD(    8,   56, AMED_NOSPDCLAMP,                     DIR_N  ),  // 137 Accelerate to end of runway 1b
	AMD(    8,  -26, AMED_NOSPDCLAMP | AMED_TAKEOFF,      DIR_N  ),  // 138 Take off 1b
	AMD(  104,    8, AMED_EXACTPOS,                       DIR_SW ),  // 139 Taxi to start of runway 2b
	AMD(  182,    8, AMED_NOSPDCLAMP,                     DIR_N  ),  // 140 Accelerate to end of runway 2b
	AMD(  264,    8, AMED_NOSPDCLAMP | AMED_TAKEOFF,      DIR_N  ),  // 141 Take off 2b
	AMD(  232,  104, AMED_EXACTPOS,                       DIR_SE ),  // 142 Taxi to start of runway 3b
	AMD(  232,  182, AMED_NOSPDCLAMP,                     DIR_N  ),  // 143 Accelerate to end of runway 3b
	AMD(  232,  264, AMED_NOSPDCLAMP | AMED_TAKEOFF,      DIR_N  ),  // 144 Take off 3b
	AMD(  136,  232, AMED_EXACTPOS,                       DIR_NE ),  // 145 Taxi to start of runway 4b
	AMD(   56,  232, AMED_NOSPDCLAMP,                     DIR_N  ),  // 146 Accelerate to end of runway 4b
	AMD(  -26,  232, AMED_NOSPDCLAMP | AMED_TAKEOFF,      DIR_N  ),  // 147 Take off 4b
	AMD(    8,  352, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 148 Fly to landing position in air 1a
	AMD(    8,  232, AMED_NOSPDCLAMP | AMED_LAND,         DIR_N  ),  // 149 Going down for land 1a
	AMD(    8,  152, AMED_NOSPDCLAMP | AMED_BRAKE,        DIR_N  ),  // 150 Brake until end of runway 1a
	AMD( -112,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 151 Fly to landing position in air 2a
	AMD(    8,    8, AMED_NOSPDCLAMP | AMED_LAND,         DIR_N  ),  // 152 Going down for land 2a
	AMD(   88,    8, AMED_NOSPDCLAMP | AMED_BRAKE,        DIR_N  ),  // 153 Brake until end of runway 2a
	AMD(  232, -112, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 154 Fly to landing position in air 3a
	AMD(  232,    8, AMED_NOSPDCLAMP | AMED_LAND,         DIR_N  ),  // 155 Going down for land 3a
	AMD(  232,   88, AMED_NOSPDCLAMP | AMED_BRAKE,        DIR_N  ),  // 156 Brake until end of runway 3a
	AMD(  352,  232, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 157 Fly to landing position in air 4a
	AMD(  232,  232, AMED_NOSPDCLAMP | AMED_LAND,         DIR_N  ),  // 158 Going down for land 4a
	AMD(  152,  232, AMED_NOSPDCLAMP | AMED_BRAKE,        DIR_N  ),  // 159 Brake until end of runway 4a
	AMD(   72,  468, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 160 fly around
	AMD( -228,   72, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 161 fly around
 	AMD(  168, -228, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 162 fly around
	AMD(  468,  168, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 163 fly around
	AMD(   40,   40, AMED_EXACTPOS,                       DIR_SE ),  // 164 pre-helitakeoff spot 1
	AMD(   40,   40, AMED_HELI_RAISE,                     DIR_N  ),  // 165 helitakeoff spot 1
 	AMD(  200,  200, AMED_EXACTPOS,                       DIR_SE ),  // 166 pre-helitakeoff spot 2
	AMD(  200,  200, AMED_HELI_RAISE,                     DIR_N  ),  // 167 helitakeoff spot 2
	AMD(   40,  200, AMED_EXACTPOS,                       DIR_SE ),  // 168 pre-helitakeoff spot 3l
	AMD(   40,  200, AMED_HELI_RAISE,                     DIR_N  ),  // 169 helitakeoff spot 3l
 	AMD(  200,   40, AMED_EXACTPOS,                       DIR_SE ),  // 170 pre-helitakeoff spot 4l
	AMD(  200,   40, AMED_HELI_RAISE,                     DIR_N  ),  // 171 helitakeoff spot 4l
	AMD(   40,  192, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 172 Go to position spot 3l
	AMD(   40,  192, AMED_HELI_LOWER,                     DIR_N  ),  // 173 Land in spot 3l
	AMD(  200,   48, AMED_NOSPDCLAMP | AMED_SLOWTURN,     DIR_N  ),  // 174 Go to position spot 4l
	AMD(  200,   48, AMED_HELI_LOWER,                     DIR_N  ),  // 175 Land in spot 4l
};


/** Heliport (heliport). */
static const AirportMovingData _airport_moving_data_heliport[9] = {
	AMD(    5,    9, AMED_EXACTPOS,                   DIR_NE), // 0 - At heliport terminal
	AMD(    2,    9, AMED_HELI_RAISE,                 DIR_N ), // 1 - Take off (play sound)
	AMD(   -3,    9, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 2 - In position above landing spot helicopter
	AMD(   -3,    9, AMED_HELI_LOWER,                 DIR_N ), // 3 - Land
	AMD(    2,    9, 0,                               DIR_N ), // 4 - Goto terminal on ground
	AMD(  -31,   59, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 5 - Circle #1 (north-east)
	AMD(  -31,  -49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 6 - Circle #2 (north-west)
	AMD(   49,  -49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 7 - Circle #3 (south-west)
	AMD(   70,    9, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 8 - Circle #4 (south)
};

/** HeliDepot 2x2 (heliport). */
static const AirportMovingData _airport_moving_data_helidepot[18] = {
	AMD(   24,    4, AMED_EXACTPOS,                   DIR_NE), // 0 - At depot
	AMD(   24,   28, 0,                               DIR_N ), // 1 Taxi to right outside depot
	AMD(    5,   38, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 2 Flying
	AMD(  -15,  -15, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 3 - Circle #1 (north-east)
	AMD(  -15,  -49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 4 - Circle #2 (north-west)
	AMD(   49,  -49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 5 - Circle #3 (south-west)
	AMD(   49,  -15, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 6 - Circle #4 (south-east)
	AMD(    8,   32, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_NW), // 7 - PreHelipad
	AMD(    8,   32, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_NW), // 8 - Helipad
	AMD(    8,   16, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_NW), // 9 - Land
	AMD(    8,   16, AMED_HELI_LOWER,                 DIR_NW), // 10 - Land
	AMD(    8,   24, AMED_HELI_RAISE,                 DIR_N ), // 11 - Take off (play sound)
	AMD(   32,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_NW), // 12 Air to above hangar area
	AMD(   32,   24, AMED_HELI_LOWER,                 DIR_NW), // 13 Taxi to right outside depot
	AMD(    8,   24, AMED_EXACTPOS,                   DIR_NW), // 14 - on helipad1
	AMD(   24,   28, AMED_HELI_RAISE,                 DIR_N ), // 15 Takeoff right outside depot
	AMD(    8,   24, AMED_HELI_RAISE,                 DIR_SW), // 16 - Take off (play sound)
	AMD(    8,   24, AMED_SLOWTURN | AMED_EXACTPOS,   DIR_E ), // 17 - turn on helipad1 for takeoff
};

/** HeliDepot 2x2 (heliport). */
static const AirportMovingData _airport_moving_data_helistation[33] = {
	AMD(    8,    3, AMED_EXACTPOS,                   DIR_SE), // 00 In Hangar2
	AMD(    8,   22, 0,                               DIR_N ), // 01 outside hangar 2
	AMD(  116,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 02 Fly to landing position in air
	AMD(   14,   22, AMED_HELI_RAISE,                 DIR_N ), // 03 Helitakeoff outside hangar1(play sound)
	AMD(   24,   22, 0,                               DIR_N ), // 04 taxiing
	AMD(   40,   22, 0,                               DIR_N ), // 05 taxiing
	AMD(   40,    8, AMED_EXACTPOS,                   DIR_NE), // 06 Helipad 1
	AMD(   56,    8, AMED_EXACTPOS,                   DIR_NE), // 07 Helipad 2
	AMD(   56,   24, AMED_EXACTPOS,                   DIR_NE), // 08 Helipad 3
	AMD(   40,    8, AMED_EXACTPOS,                   DIR_N ), // 09 pre-helitakeoff helipad 1
	AMD(   56,    8, AMED_EXACTPOS,                   DIR_N ), // 10 pre-helitakeoff helipad 2
	AMD(   56,   24, AMED_EXACTPOS,                   DIR_N ), // 11 pre-helitakeoff helipad 3
	AMD(   32,    8, AMED_HELI_RAISE,                 DIR_N ), // 12 Takeoff Helipad1
	AMD(   48,    8, AMED_HELI_RAISE,                 DIR_N ), // 13 Takeoff Helipad2
	AMD(   48,   24, AMED_HELI_RAISE,                 DIR_N ), // 14 Takeoff Helipad3
	AMD(   84,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 15 Bufferspace before helipad
	AMD(   68,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 16 Bufferspace before helipad
	AMD(   32,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 17 Get in position for Helipad1
	AMD(   48,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 18 Get in position for Helipad2
	AMD(   48,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_NE), // 19 Get in position for Helipad3
	AMD(   40,    8, AMED_HELI_LOWER,                 DIR_N ), // 20 Land at Helipad1
	AMD(   48,    8, AMED_HELI_LOWER,                 DIR_N ), // 21 Land at Helipad2
	AMD(   48,   24, AMED_HELI_LOWER,                 DIR_N ), // 22 Land at Helipad3
	AMD(    0,   22, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 23 Go to position for Hangarentrance in air
	AMD(    0,   22, AMED_HELI_LOWER,                 DIR_N ), // 24 Land in front of hangar
	AMD(  148,   -8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 25 Fly around waiting for a landing spot (south-east)
	AMD(  148,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 26 Fly around waiting for a landing spot (south-west)
	AMD(  132,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 27 Fly around waiting for a landing spot (south-west)
	AMD(  100,   24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 28 Fly around waiting for a landing spot (north-east)
	AMD(   84,    8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 29 Fly around waiting for a landing spot (south-east)
	AMD(   84,   -8, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 30 Fly around waiting for a landing spot (south-west)
	AMD(  100,  -24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 31 Fly around waiting for a landing spot (north-west)
	AMD(  132,  -24, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 32 Fly around waiting for a landing spot (north-east)
};

/** Oilrig. */
static const AirportMovingData _airport_moving_data_oilrig[9] = {
	AMD(   31,    9, AMED_EXACTPOS,                   DIR_NE), // 0 - At oilrig terminal
	AMD(   28,    9, AMED_HELI_RAISE,                 DIR_N ), // 1 - Take off (play sound)
	AMD(   23,    9, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 2 - In position above landing spot helicopter
	AMD(   23,    9, AMED_HELI_LOWER,                 DIR_N ), // 3 - Land
	AMD(   28,    9, 0,                               DIR_N ), // 4 - Goto terminal on ground
	AMD(  -31,   69, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 5 - circle #1 (north-east)
	AMD(  -31,  -49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 6 - circle #2 (north-west)
	AMD(   69,  -49, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 7 - circle #3 (south-west)
	AMD(   69,    9, AMED_NOSPDCLAMP | AMED_SLOWTURN, DIR_N ), // 8 - circle #4 (south)
};

#undef AMD

///////////////////////////////////////////////////////////////////////
/////**********Movement Machine on Airports*********************///////
static const byte _airport_entries_dummy[] = {0, 1, 2, 3};
static const AirportFTAbuildup _airport_fta_dummy[] = {
	{ 0, TO_ALL, 0, 0, 3},
	{ 1, TO_ALL, 0, 0, 0},
	{ 2, TO_ALL, 0, 0, 1},
	{ 3, TO_ALL, 0, 0, 2},
	{ MAX_ELEMENTS, TO_ALL, 0, 0, 0 } // end marker. DO NOT REMOVE
};

/* First element of terminals array tells us how many depots there are (to know size of array)
 * this may be changed later when airports are moved to external file  */
static const HangarTileTable _airport_depots_country[] = { {{3, 0}, DIR_SE, 0} };
static const byte _airport_terminal_country[] = {1, 2};
static const byte _airport_entries_country[] = {16, 15, 18, 17};
static const AirportFTAbuildup _airport_fta_country[] = {
 	{  0, HANGAR, NOTHING_block, 0, 1 },
	{  1, 255, AIRPORT_BUSY_block, 0, 0 }, { 1, HANGAR, 0, 0, 0 }, { 1, TERM1, TERM1_block, 0, 2 }, { 1, TERM2, 0, 0, 4 }, { 1, HELITAKEOFF, 0, 0, 19 }, { 1, 0, 0, 0, 6 },
	{  2, TERM1, TERM1_block, 0, 1 },
	{  3, TERM2, TERM2_block, 0, 5 },
	{  4, 255, AIRPORT_BUSY_block, 0, 0 }, { 4, TERM2, 0, 0, 5 }, { 4, HANGAR, 0, 0, 1 }, { 4, TAKEOFF, 0, 0, 6 }, { 4, HELITAKEOFF, 0, 0, 1 },
	{  5, 255, AIRPORT_BUSY_block, 0, 0 }, { 5, TERM2, TERM2_block, 0, 3 }, { 5, 0, 0, 0, 4 },
	{  6, 0, AIRPORT_BUSY_block, 0, 7 },
	/* takeoff */
	{  7, TAKEOFF, AIRPORT_BUSY_block, 0, 8 },
	{  8, STARTTAKEOFF, NOTHING_block, 0, 9 },
	{  9, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* landing */
	{ 10, FLYING, NOTHING_block, 0, 15 }, { 10, LANDING, 0, 0, 11 }, { 10, HELILANDING, 0, 0, 20 },
	{ 11, LANDING, AIRPORT_BUSY_block, 0, 12 },
	{ 12, 0, AIRPORT_BUSY_block, 0, 13 },
	{ 13, ENDLANDING, AIRPORT_BUSY_block, 0, 14 }, { 13, TERM2, 0, 0, 5 }, { 13, 0, 0, 0, 14 },
	{ 14, 0, AIRPORT_BUSY_block, 0, 1 },
	/* In air */
	{ 15, 0, NOTHING_block, 0, 16 },
	{ 16, 0, NOTHING_block, 0, 17 },
	{ 17, 0, NOTHING_block, 0, 18 },
	{ 18, 0, NOTHING_block, 0, 10 },
	{ 19, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 20, HELILANDING, AIRPORT_BUSY_block, 0, 21 },
	{ 21, HELIENDLANDING, AIRPORT_BUSY_block, 0, 1 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

static const HangarTileTable _airport_depots_commuter[] = { {{4, 0}, DIR_SE, 0} };
static const byte _airport_terminal_commuter[] = { 1, 3 };
static const byte _airport_entries_commuter[] = {22, 21, 24, 23};
static const AirportFTAbuildup _airport_fta_commuter[] = {
	{  0, HANGAR, NOTHING_block, 0, 1 }, { 0, HELITAKEOFF, HELIPAD2_block, 0, 1 }, { 0, 0, 0, 0, 1 },
	{  1, 255, TAXIWAY_BUSY_block, 0, 0 }, { 1, HANGAR, 0, 0, 0 }, { 1, TAKEOFF, 0, 0, 11 }, { 1, TERM1, TAXIWAY_BUSY_block, 0, 10 }, { 1, TERM2, TAXIWAY_BUSY_block, 0, 10 }, { 1, TERM3, TAXIWAY_BUSY_block, 0, 10 }, { 1, HELIPAD1, TAXIWAY_BUSY_block, 0, 10 }, { 1, HELIPAD2, TAXIWAY_BUSY_block, 0, 10 }, { 1, HELITAKEOFF, TAXIWAY_BUSY_block, 0, 10 }, { 1, 0, 0, 0, 0 },
	{  2, 255, AIRPORT_ENTRANCE_block, 0, 2 }, { 2, HANGAR, 0, 0, 8 }, { 2, TERM1, 0, 0, 8 }, { 2, TERM2, 0, 0, 8 }, { 2, TERM3, 0, 0, 8 }, { 2, HELIPAD1, 0, 0, 8 }, { 2, HELIPAD2, 0, 0, 8 }, { 2, HELITAKEOFF, 0, 0, 8 }, { 2, 0, 0, 0, 2 },
	{  3, TERM1, TERM1_block, 0, 8 }, { 3, HANGAR, 0, 0, 8 }, { 3, TAKEOFF, 0, 0, 8 }, { 3, 0, 0, 0, 3 },
	{  4, TERM2, TERM2_block, 0, 9 }, { 4, HANGAR, 0, 0, 9 }, { 4, TAKEOFF, 0, 0, 9 }, { 4, 0, 0, 0, 4 },
	{  5, TERM3, TERM3_block, 0, 10 }, { 5, HANGAR, 0, 0, 10 }, { 5, TAKEOFF, 0, 0, 10 }, { 5, 0, 0, 0, 5 },
	{  6, HELIPAD1, HELIPAD1_block, 0, 6 }, { 6, HANGAR, TAXIWAY_BUSY_block, 0, 9 }, { 6, HELITAKEOFF, 0, 0, 35 },
	{  7, HELIPAD2, HELIPAD2_block, 0, 7 }, { 7, HANGAR, TAXIWAY_BUSY_block, 0, 10 }, { 7, HELITAKEOFF, 0, 0, 36 },
	{  8, 255, TAXIWAY_BUSY_block, 0, 8 }, { 8, TAKEOFF, TAXIWAY_BUSY_block, 0, 9 }, { 8, HANGAR, TAXIWAY_BUSY_block, 0, 9 }, { 8, TERM1, TERM1_block, 0, 3 }, { 8, 0, TAXIWAY_BUSY_block, 0, 9 },
	{  9, 255, TAXIWAY_BUSY_block, 0, 9 }, { 9, TAKEOFF, TAXIWAY_BUSY_block, 0, 10 }, { 9, HANGAR, TAXIWAY_BUSY_block, 0, 10 }, { 9, TERM2, TERM2_block, 0, 4 }, { 9, HELIPAD1, HELIPAD1_block, 0, 6 }, { 9, HELITAKEOFF, HELIPAD1_block, 0, 6 }, { 9, TERM1, TAXIWAY_BUSY_block, 0, 8 }, { 9, 0, TAXIWAY_BUSY_block, 0, 10 },
	{ 10, 255, TAXIWAY_BUSY_block, 0, 10 }, { 10, TERM3, TERM3_block, 0, 5 }, { 10, HELIPAD1, 0, 0, 9 }, { 10, HELIPAD2, HELIPAD2_block, 0, 7 }, { 10, HELITAKEOFF, HELIPAD2_block, 0, 7 }, { 10, TAKEOFF, TAXIWAY_BUSY_block, 0, 1 }, { 10, HANGAR, TAXIWAY_BUSY_block, 0, 1 }, { 10, 0, TAXIWAY_BUSY_block, 0, 9 },
	{ 11, 0, OUT_WAY_block, 0, 12 },
	/* takeoff */
	{ 12, TAKEOFF, RUNWAY_IN_OUT_block, 0, 13 },
	{ 13, 0, RUNWAY_IN_OUT_block, 0, 14 },
	{ 14, STARTTAKEOFF, RUNWAY_IN_OUT_block, 0, 15 },
	{ 15, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* landing */
	{ 16, FLYING, NOTHING_block, 0, 21 }, { 16, LANDING, IN_WAY_block, 0, 17 }, { 16, HELILANDING, 0, 0, 25 },
	{ 17, LANDING, RUNWAY_IN_OUT_block, 0, 18 },
	{ 18, 0, RUNWAY_IN_OUT_block, 0, 19 },
	{ 19, 0, RUNWAY_IN_OUT_block, 0, 20 },
	{ 20, ENDLANDING, IN_WAY_block, 0, 2 },
	/* In Air */
	{ 21, 0, NOTHING_block, 0, 22 },
	{ 22, 0, NOTHING_block, 0, 23 },
	{ 23, 0, NOTHING_block, 0, 24 },
	{ 24, 0, NOTHING_block, 0, 16 },
	/* Helicopter -- stay in air in special place as a buffer to choose from helipads */
	{ 25, HELILANDING, PRE_HELIPAD_block, 0, 26 },
	{ 26, HELIENDLANDING, PRE_HELIPAD_block, 0, 26 }, { 26, HELIPAD1, 0, 0, 27 }, { 26, HELIPAD2, 0, 0, 28 }, { 26, HANGAR, 0, 0, 33 },
	{ 27, 0, NOTHING_block, 0, 29 }, // helipad1 approach
	{ 28, 0, NOTHING_block, 0, 30 },
	/* landing */
	{ 29, 255, NOTHING_block, 0, 0 }, { 29, HELIPAD1, HELIPAD1_block, 0, 6 },
	{ 30, 255, NOTHING_block, 0, 0 }, { 30, HELIPAD2, HELIPAD2_block, 0, 7 },
	/* Helicopter -- takeoff */
	{ 31, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 32, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 33, 0, TAXIWAY_BUSY_block, 0, 34 }, // need to go to hangar when waiting in air
	{ 34, 0, TAXIWAY_BUSY_block, 0, 1 },
	{ 35, 0, HELIPAD1_block, 0, 31 },
	{ 36, 0, HELIPAD2_block, 0, 32 },
	{ 37, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

static const HangarTileTable _airport_depots_city[] = { {{5, 0}, DIR_SE, 0} };
static const byte _airport_terminal_city[] = { 1, 3 };
static const byte _airport_entries_city[] = {26, 29, 27, 28};
static const AirportFTAbuildup _airport_fta_city[] = {
	{  0, HANGAR, NOTHING_block, 0, 1 }, { 0, TAKEOFF, OUT_WAY_block, 0, 1 }, { 0, 0, 0, 0, 1 },
	{  1, 255, TAXIWAY_BUSY_block, 0, 0 }, { 1, HANGAR, 0, 0, 0 }, { 1, TERM2, 0, 0, 6 }, { 1, TERM3, 0, 0, 6 }, { 1, 0, 0, 0, 7 }, // for all else, go to 7
	{  2, TERM1, TERM1_block, 0, 7 }, { 2, TAKEOFF, OUT_WAY_block, 0, 7 }, { 2, 0, 0, 0, 7 },
	{  3, TERM2, TERM2_block, 0, 5 }, { 3, TAKEOFF, OUT_WAY_block, 0, 6 }, { 3, 0, 0, 0, 6 },
	{  4, TERM3, TERM3_block, 0, 5 }, { 4, TAKEOFF, OUT_WAY_block, 0, 5 }, { 4, 0, 0, 0, 5 },
	{  5, 255, TAXIWAY_BUSY_block, 0, 0 }, { 5, TERM2, TERM2_block, 0, 3 }, { 5, TERM3, TERM3_block, 0, 4 }, { 5, 0, 0, 0, 6 },
	{  6, 255, TAXIWAY_BUSY_block, 0, 0 }, { 6, TERM2, TERM2_block, 0, 3 }, { 6, TERM3, 0, 0, 5 }, { 6, HANGAR, 0, 0, 1 }, { 6, 0, 0, 0, 7 },
	{  7, 255, TAXIWAY_BUSY_block, 0, 0 }, { 7, TERM1, TERM1_block, 0, 2 }, { 7, TAKEOFF, OUT_WAY_block, 0, 8 }, { 7, HELITAKEOFF, 0, 0, 22 }, { 7, HANGAR, 0, 0, 1 }, { 7, 0, 0, 0, 6 },
	{  8, 0, OUT_WAY_block, 0, 9 },
	{  9, 0, RUNWAY_IN_OUT_block, 0, 10 },
	/* takeoff */
	{ 10, TAKEOFF, RUNWAY_IN_OUT_block, 0, 11 },
	{ 11, STARTTAKEOFF, NOTHING_block, 0, 12 },
	{ 12, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* landing */
	{ 13, FLYING, NOTHING_block, 0, 18 }, { 13, LANDING, 0, 0, 14 }, { 13, HELILANDING, 0, 0, 23 },
	{ 14, LANDING, RUNWAY_IN_OUT_block, 0, 15 },
	{ 15, 0, RUNWAY_IN_OUT_block, 0, 17 },
	{ 16, 0, RUNWAY_IN_OUT_block, 0, 17 }, // not used, left for compatibility
	{ 17, ENDLANDING, IN_WAY_block, 0, 7 },
	/* In Air */
	{ 18, 0, NOTHING_block, 0, 25 },
	{ 19, 0, NOTHING_block, 0, 20 },
	{ 20, 0, NOTHING_block, 0, 21 },
	{ 21, 0, NOTHING_block, 0, 13 },
	/* helicopter */
	{ 22, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 23, HELILANDING, IN_WAY_block, 0, 24 },
	{ 24, HELIENDLANDING, IN_WAY_block, 0, 17 },
	{ 25, 0, NOTHING_block, 0, 20},
	{ 26, 0, NOTHING_block, 0, 19},
	{ 27, 0, NOTHING_block, 0, 28},
	{ 28, 0, NOTHING_block, 0, 19},
	{ 29, 0, NOTHING_block, 0, 26},
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

static const HangarTileTable _airport_depots_metropolitan[] = { {{5, 0}, DIR_SE, 0} };
static const byte _airport_terminal_metropolitan[] = { 1, 3 };
static const byte _airport_entries_metropolitan[] = {20, 19, 22, 21};
static const AirportFTAbuildup _airport_fta_metropolitan[] = {
	{  0, HANGAR, NOTHING_block, 0, 1 },
	{  1, 255, TAXIWAY_BUSY_block, 0, 0 }, { 1, HANGAR, 0, 0, 0 }, { 1, TERM2, 0, 0, 6 }, { 1, TERM3, 0, 0, 6 }, { 1, 0, 0, 0, 7 }, // for all else, go to 7
	{  2, TERM1, TERM1_block, 0, 7 },
	{  3, TERM2, TERM2_block, 0, 6 },
	{  4, TERM3, TERM3_block, 0, 5 },
	{  5, 255, TAXIWAY_BUSY_block, 0, 0 }, { 5, TERM2, TERM2_block, 0, 3 }, { 5, TERM3, TERM3_block, 0, 4 }, { 5, 0, 0, 0, 6 },
	{  6, 255, TAXIWAY_BUSY_block, 0, 0 }, { 6, TERM2, TERM2_block, 0, 3 }, { 6, TERM3, 0, 0, 5 }, { 6, HANGAR, 0, 0, 1 }, { 6, 0, 0, 0, 7 },
	{  7, 255, TAXIWAY_BUSY_block, 0, 0 }, { 7, TERM1, TERM1_block, 0, 2 }, { 7, TAKEOFF, 0, 0, 8 }, { 7, HELITAKEOFF, 0, 0, 23 }, { 7, HANGAR, 0, 0, 1 }, { 7, 0, 0, 0, 6 },
	{  8, 0, OUT_WAY_block, 0, 9 },
	{  9, 0, RUNWAY_OUT_block, 0, 10 },
	/* takeoff */
	{ 10, TAKEOFF, RUNWAY_OUT_block, 0, 11 },
	{ 11, STARTTAKEOFF, NOTHING_block, 0, 12 },
	{ 12, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* landing */
	{ 13, FLYING, NOTHING_block, 0, 19 }, { 13, LANDING, 0, 0, 14 }, { 13, HELILANDING, 0, 0, 25 },
	{ 14, LANDING, RUNWAY_IN_block, 0, 15 },
	{ 15, 0, RUNWAY_IN_block, 0, 16 },
	{ 16, 255, RUNWAY_IN_block, 0, 0 }, { 16, ENDLANDING, IN_WAY_block, 0, 17 },
	{ 17, 255, RUNWAY_OUT_block, 0, 0 }, { 17, ENDLANDING, IN_WAY_block, 0, 18 },
	{ 18, ENDLANDING, IN_WAY_block, 0, 27 },
	/* In Air */
	{ 19, 0, NOTHING_block, 0, 20 },
	{ 20, 0, NOTHING_block, 0, 21 },
	{ 21, 0, NOTHING_block, 0, 22 },
	{ 22, 0, NOTHING_block, 0, 13 },
	/* helicopter */
	{ 23, 0, NOTHING_block, 0, 24 },
	{ 24, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 25, HELILANDING, IN_WAY_block, 0, 26 },
	{ 26, HELIENDLANDING, IN_WAY_block, 0, 18 },
	{ 27, 255, TAXIWAY_BUSY_block, 0, 27 }, { 27, TERM1, TERM1_block, 0, 2 }, { 27, 0, 0, 0, 7 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

static const HangarTileTable _airport_depots_international[] = { {{0, 3}, DIR_SE, 0}, {{6, 1}, DIR_SE, 1} };
static const byte _airport_terminal_international[] = { 2, 3, 3 };
static const byte _airport_entries_international[] = { 38, 37, 40, 39 };
static const AirportFTAbuildup _airport_fta_international[] = {
	{  0, HANGAR, NOTHING_block, 0, 2 }, { 0, 255, TERM_GROUP1_block, 0, 0 }, { 0, 255, TERM_GROUP2_ENTER1_block, 0, 1 }, { 0, HELITAKEOFF, HELIPAD1_block, 0, 2 }, { 0, 0, 0, 0, 2 },
	{  1, HANGAR, NOTHING_block, 0, 3 }, { 1, 255, HANGAR2_AREA_block, 0, 1 }, { 1, HELITAKEOFF, HELIPAD2_block, 0, 3 }, { 1, 0, 0, 0, 3 },
	{  2, 255, AIRPORT_ENTRANCE_block, 0, 0 }, { 2, HANGAR, 0, 0, 0 }, { 2, TERM4, 0, 0, 12 }, { 2, TERM5, 0, 0, 12 }, { 2, TERM6, 0, 0, 12 }, { 2, HELIPAD1, 0, 0, 12 }, { 2, HELIPAD2, 0, 0, 12 }, { 2, HELITAKEOFF, 0, 0, 12 }, { 2, 0, 0, 0, 23 },
	{  3, 255, HANGAR2_AREA_block, 0, 0 }, { 3, HANGAR, 0, 0, 1 }, { 3, 0, 0, 0, 18 },
	{  4, TERM1, TERM1_block, 0, 23 }, { 4, HANGAR, AIRPORT_ENTRANCE_block, 0, 23 }, { 4, 0, 0, 0, 23 },
	{  5, TERM2, TERM2_block, 0, 24 }, { 5, HANGAR, AIRPORT_ENTRANCE_block, 0, 24 }, { 5, 0, 0, 0, 24 },
	{  6, TERM3, TERM3_block, 0, 25 }, { 6, HANGAR, AIRPORT_ENTRANCE_block, 0, 25 }, { 6, 0, 0, 0, 25 },
	{  7, TERM4, TERM4_block, 0, 16 }, { 7, HANGAR, HANGAR2_AREA_block, 0, 16 }, { 7, 0, 0, 0, 16 },
	{  8, TERM5, TERM5_block, 0, 17 }, { 8, HANGAR, HANGAR2_AREA_block, 0, 17 }, { 8, 0, 0, 0, 17 },
	{  9, TERM6, TERM6_block, 0, 18 }, { 9, HANGAR, HANGAR2_AREA_block, 0, 18 }, { 9, 0, 0, 0, 18 },
	{ 10, HELIPAD1, HELIPAD1_block, 0, 10 }, { 10, HANGAR, HANGAR2_AREA_block, 0, 16 }, { 10, HELITAKEOFF, 0, 0, 47 },
	{ 11, HELIPAD2, HELIPAD2_block, 0, 11 }, { 11, HANGAR, HANGAR2_AREA_block, 0, 17 }, { 11, HELITAKEOFF, 0, 0, 48 },
	{ 12, 0, TERM_GROUP2_ENTER1_block, 0, 13 },
	{ 13, 0, TERM_GROUP2_ENTER1_block, 0, 14 },
	{ 14, 0, TERM_GROUP2_ENTER2_block, 0, 15 },
	{ 15, 0, TERM_GROUP2_ENTER2_block, 0, 16 },
	{ 16, 255, TERM_GROUP2_block, 0, 0 }, { 16, TERM4, TERM4_block, 0, 7 }, { 16, HELIPAD1, HELIPAD1_block, 0, 10 }, { 16, HELITAKEOFF, HELIPAD1_block, 0, 10 }, { 16, 0, 0, 0, 17 },
	{ 17, 255, TERM_GROUP2_block, 0, 0 }, { 17, TERM5, TERM5_block, 0, 8 }, { 17, TERM4, 0, 0, 16 }, { 17, HELIPAD1, 0, 0, 16 }, { 17, HELIPAD2, HELIPAD2_block, 0, 11 }, { 17, HELITAKEOFF, HELIPAD2_block, 0, 11 }, { 17, 0, 0, 0, 18 },
	{ 18, 255, TERM_GROUP2_block, 0, 0 }, { 18, TERM6, TERM6_block, 0, 9 }, { 18, TAKEOFF, 0, 0, 19 }, { 18, HANGAR, HANGAR2_AREA_block, 0, 3 }, { 18, 0, 0, 0, 17 },
	{ 19, 0, TERM_GROUP2_EXIT1_block, 0, 20 },
	{ 20, 0, TERM_GROUP2_EXIT1_block, 0, 21 },
	{ 21, 0, TERM_GROUP2_EXIT2_block, 0, 22 },
	{ 22, 0, TERM_GROUP2_EXIT2_block, 0, 26 },
	{ 23, 255, TERM_GROUP1_block, 0, 0 }, { 23, TERM1, TERM1_block, 0, 4 }, { 23, HANGAR, AIRPORT_ENTRANCE_block, 0, 2 }, { 23, 0, 0, 0, 24 },
	{ 24, 255, TERM_GROUP1_block, 0, 0 }, { 24, TERM2, TERM2_block, 0, 5 }, { 24, TERM1, 0, 0, 23 }, { 24, HANGAR, 0, 0, 23 }, { 24, 0, 0, 0, 25 },
	{ 25, 255, TERM_GROUP1_block, 0, 0 }, { 25, TERM3, TERM3_block, 0, 6 }, { 25, TAKEOFF, 0, 0, 26 }, { 25, 0, 0, 0, 24 },
	{ 26, 255, TAXIWAY_BUSY_block, 0, 0 }, { 26, TAKEOFF, 0, 0, 27 }, { 26, 0, 0, 0, 25 },
	{ 27, 0, OUT_WAY_block, 0, 28 },
	/* takeoff */
	{ 28, TAKEOFF, OUT_WAY_block, 0, 29 },
	{ 29, 0, RUNWAY_OUT_block, 0, 30 },
	{ 30, STARTTAKEOFF, NOTHING_block, 0, 31 },
	{ 31, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* landing */
	{ 32, FLYING, NOTHING_block, 0, 37 }, { 32, LANDING, 0, 0, 33 }, { 32, HELILANDING, 0, 0, 41 },
	{ 33, LANDING, RUNWAY_IN_block, 0, 34 },
	{ 34, 0, RUNWAY_IN_block, 0, 35 },
	{ 35, 0, RUNWAY_IN_block, 0, 36 },
	{ 36, ENDLANDING, IN_WAY_block, 0, 36 }, { 36, 255, TERM_GROUP1_block, 0, 0 }, { 36, 255, TERM_GROUP2_ENTER1_block, 0, 1 }, { 36, TERM4, 0, 0, 12 }, { 36, TERM5, 0, 0, 12 }, { 36, TERM6, 0, 0, 12 }, { 36, 0, 0, 0, 2 },
	/* In Air */
	{ 37, 0, NOTHING_block, 0, 38 },
	{ 38, 0, NOTHING_block, 0, 39 },
	{ 39, 0, NOTHING_block, 0, 40 },
	{ 40, 0, NOTHING_block, 0, 32 },
	/* Helicopter -- stay in air in special place as a buffer to choose from helipads */
	{ 41, HELILANDING, PRE_HELIPAD_block, 0, 42 },
	{ 42, HELIENDLANDING, PRE_HELIPAD_block, 0, 42 }, { 42, HELIPAD1, 0, 0, 43 }, { 42, HELIPAD2, 0, 0, 44 }, { 42, HANGAR, 0, 0, 49 },
	{ 43, 0, NOTHING_block, 0, 45 },
	{ 44, 0, NOTHING_block, 0, 46 },
	/* landing */
	{ 45, 255, NOTHING_block, 0, 0 }, { 45, HELIPAD1, HELIPAD1_block, 0, 10 },
	{ 46, 255, NOTHING_block, 0, 0 }, { 46, HELIPAD2, HELIPAD2_block, 0, 11 },
	/* Helicopter -- takeoff */
	{ 47, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 48, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 49, 0, HANGAR2_AREA_block, 0, 50 }, // need to go to hangar when waiting in air
	{ 50, 0, HANGAR2_AREA_block, 0, 3 },
	{ 51, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 52, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

/* intercontinental */
static const HangarTileTable _airport_depots_intercontinental[] = { {{0, 5}, DIR_SE, 0}, {{8, 4}, DIR_SE, 1} };
static const byte _airport_terminal_intercontinental[] = { 2, 4, 4 };
static const byte _airport_entries_intercontinental[] = { 44, 43, 46, 45 };
static const AirportFTAbuildup _airport_fta_intercontinental[] = {
	{  0, HANGAR, NOTHING_block, 0, 2 }, { 0, 255, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 0 }, { 0, 255, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 1 }, { 0, TAKEOFF, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 2 }, { 0, 0, 0, 0, 2 },
	{  1, HANGAR, NOTHING_block, 0, 3 }, { 1, 255, HANGAR2_AREA_block, 0, 1 }, { 1, 255, HANGAR2_AREA_block, 0, 0 }, { 1, 0, 0, 0, 3 },
	{  2, 255, HANGAR1_AREA_block, 0, 0 }, { 2, 255, TERM_GROUP1_block, 0, 0 }, { 2, 255, TERM_GROUP1_block, 0, 1 }, { 2, HANGAR, 0, 0, 0 }, { 2, TAKEOFF, TERM_GROUP1_block, 0, 27 }, { 2, TERM5, 0, 0, 26 }, { 2, TERM6, 0, 0, 26 }, { 2, TERM7, 0, 0, 26 }, { 2, TERM8, 0, 0, 26 }, { 2, HELIPAD1, 0, 0, 26 }, { 2, HELIPAD2, 0, 0, 26 }, { 2, HELITAKEOFF, 0, 0, 74 }, { 2, 0, 0, 0, 27 },
	{  3, 255, HANGAR2_AREA_block, 0, 0 }, { 3, HANGAR, 0, 0, 1 }, { 3, HELITAKEOFF, 0, 0, 75 }, {3, TAKEOFF, 0, 0, 59}, { 3, 0, 0, 0, 20 },
	{  4, TERM1, TERM1_block, 0, 26 }, { 4, HANGAR, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 26 }, { 4, 0, 0, 0, 26 },
	{  5, TERM2, TERM2_block, 0, 27 }, { 5, HANGAR, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 27 }, { 5, 0, 0, 0, 27 },
	{  6, TERM3, TERM3_block, 0, 28 }, { 6, HANGAR, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 28 }, { 6, 0, 0, 0, 28 },
	{  7, TERM4, TERM4_block, 0, 29 }, { 7, HANGAR, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 29 }, { 7, 0, 0, 0, 29 },
	{  8, TERM5, TERM5_block, 0, 18 }, { 8, HANGAR, HANGAR2_AREA_block, 0, 18 }, { 8, 0, 0, 0, 18 },
	{  9, TERM6, TERM6_block, 0, 19 }, { 9, HANGAR, HANGAR2_AREA_block, 0, 19 }, { 9, 0, 0, 0, 19 },
	{ 10, TERM7, TERM7_block, 0, 20 }, { 10, HANGAR, HANGAR2_AREA_block, 0, 20 }, { 10, 0, 0, 0, 20 },
	{ 11, TERM8, TERM8_block, 0, 21 }, { 11, HANGAR, HANGAR2_AREA_block, 0, 21 }, { 11, 0, 0, 0, 21 },
	{ 12, HELIPAD1, HELIPAD1_block, 0, 12 }, { 12, HANGAR, 0, 0, 70 }, { 12, HELITAKEOFF, 0, 0, 72 },
	{ 13, HELIPAD2, HELIPAD2_block, 0, 13 }, { 13, HANGAR, 0, 0, 71 }, { 13, HELITAKEOFF, 0, 0, 73 },
	{ 14, 0, TERM_GROUP2_ENTER1_block, 0, 15 },
	{ 15, 0, TERM_GROUP2_ENTER1_block, 0, 16 },
	{ 16, 0, TERM_GROUP2_ENTER2_block, 0, 17 },
	{ 17, 0, TERM_GROUP2_ENTER2_block, 0, 18 },
	{ 18, 255, TERM_GROUP2_block, 0, 0 }, { 18, TERM5, TERM5_block, 0, 8 }, { 18, TAKEOFF, 0, 0, 19 }, { 18, HELITAKEOFF, HELIPAD1_block, 0, 19 }, { 18, 0, TERM_GROUP2_EXIT1_block, 0, 19 },
	{ 19, 255, TERM_GROUP2_block, 0, 0 }, { 19, TERM6, TERM6_block, 0, 9 }, { 19, TERM5, 0, 0, 18 }, { 19, TAKEOFF, 0, 0, 57 }, { 19, HELITAKEOFF, HELIPAD1_block, 0, 20 }, { 19, 0, TERM_GROUP2_EXIT1_block, 0, 20 }, // add exit to runway out 2
	{ 20, 255, TERM_GROUP2_block, 0, 0 }, { 20, TERM7, TERM7_block, 0, 10 }, { 20, TERM5, 0, 0, 19 }, { 20, TERM6, 0, 0, 19 }, { 20, HANGAR, HANGAR2_AREA_block, 0, 3 }, { 20, TAKEOFF, 0, 0, 19 }, { 20, 0, TERM_GROUP2_EXIT1_block, 0, 21 },
	{ 21, 255, TERM_GROUP2_block, 0, 0 }, { 21, TERM8, TERM8_block, 0, 11 }, { 21, HANGAR, HANGAR2_AREA_block, 0, 20 }, { 21, TERM5, 0, 0, 20 }, { 21, TERM6, 0, 0, 20 }, { 21, TERM7, 0, 0, 20 }, { 21, TAKEOFF, 0, 0, 20 }, { 21, 0, TERM_GROUP2_EXIT1_block, 0, 22 },
	{ 22, 255, TERM_GROUP2_block, 0, 0 }, { 22, HANGAR, 0, 0, 21 }, { 22, TERM5, 0, 0, 21 }, { 22, TERM6, 0, 0, 21 }, { 22, TERM7, 0, 0, 21 }, { 22, TERM8, 0, 0, 21 }, { 22, TAKEOFF, 0, 0, 21 }, { 22, 0, 0, 0, 23 },
	{ 23, 0, TERM_GROUP2_EXIT1_block, 0, 70 },
	{ 24, 0, TERM_GROUP2_EXIT2_block, 0, 25 },
	{ 25, 255, TERM_GROUP2_EXIT2_block, 0, 0 }, { 25, HANGAR, HANGAR1_AREA_block | TERM_GROUP1_block, 0, 29 }, { 25, 0, 0, 0, 29 },
	{ 26, 255, TERM_GROUP1_block, 0, 0 }, { 26, TERM1, TERM1_block, 0, 4 }, { 26, HANGAR, HANGAR1_AREA_block, 0, 27 }, { 26, TERM5, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, TERM6, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, TERM7, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, TERM8, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, HELIPAD1, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, HELIPAD2, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, HELITAKEOFF, TERM_GROUP2_ENTER1_block, 0, 14 }, { 26, 0, 0, 0, 27 },
	{ 27, 255, TERM_GROUP1_block, 0, 0 }, { 27, TERM2, TERM2_block, 0, 5 }, { 27, HANGAR, HANGAR1_AREA_block, 0, 2 }, { 27, TERM1, 0, 0, 26 }, { 27, TERM5, 0, 0, 26 }, { 27, TERM6, 0, 0, 26 }, { 27, TERM7, 0, 0, 26 }, { 27, TERM8, 0, 0, 26 }, { 27, HELIPAD1, 0, 0, 14 }, { 27, HELIPAD2, 0, 0, 14 }, { 27, 0, 0, 0, 28 },
	{ 28, 255, TERM_GROUP1_block, 0, 0 }, { 28, TERM3, TERM3_block, 0, 6 }, { 28, HANGAR, HANGAR1_AREA_block, 0, 27 }, { 28, TERM1, 0, 0, 27 }, { 28, TERM2, 0, 0, 27 }, { 28, TERM4, 0, 0, 29 }, { 28, TERM5, 0, 0, 14 }, { 28, TERM6, 0, 0, 14 }, { 28, TERM7, 0, 0, 14 }, { 28, TERM8, 0, 0, 14 }, { 28, HELIPAD1, 0, 0, 14 }, { 28, HELIPAD2, 0, 0, 14 }, { 28, 0, 0, 0, 29 },
	{ 29, 255, TERM_GROUP1_block, 0, 0 }, { 29, TERM4, TERM4_block, 0, 7 }, { 29, HANGAR, HANGAR1_AREA_block, 0, 27 }, { 29, TAKEOFF, 0, 0, 30 }, { 29, 0, 0, 0, 28 },
	{ 30, 0, OUT_WAY_block2, 0, 31 },
	{ 31, 0, OUT_WAY_block, 0, 32 },
	/* takeoff */
	{ 32, TAKEOFF, RUNWAY_OUT_block, 0, 33 },
	{ 33, 0, RUNWAY_OUT_block, 0, 34 },
	{ 34, STARTTAKEOFF, NOTHING_block, 0, 35 },
	{ 35, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* landing */
	{ 36, 0, 0, 0, 0 },
	{ 37, LANDING, RUNWAY_IN_block, 0, 38 },
	{ 38, 0, RUNWAY_IN_block, 0, 39 },
	{ 39, 0, RUNWAY_IN_block, 0, 40 },
	{ 40, ENDLANDING, RUNWAY_IN_block, 0, 41 },
	{ 41, 0, IN_WAY_block, 0, 42 },
	{ 42, 255, IN_WAY_block, 0, 0 }, { 42, 255, TERM_GROUP1_block, 0, 0 }, { 42, 255, TERM_GROUP1_block, 0, 1 }, { 42, HANGAR, 0, 0, 2 }, { 42, 0, 0, 0, 26 },
	/* In Air */
	{ 43, 0, 0, 0, 44 },
	{ 44, FLYING, 0, 0, 45 }, { 44, HELILANDING, 0, 0, 47 }, { 44, LANDING, 0, 0, 69 }, { 44, 0, 0, 0, 45 },
	{ 45, 0, 0, 0, 46 },
	{ 46, FLYING, 0, 0, 43 }, { 46, LANDING, 0, 0, 76 }, { 46, 0, 0, 0, 43 },
	/* Helicopter -- stay in air in special place as a buffer to choose from helipads */
	{ 47, HELILANDING, PRE_HELIPAD_block, 0, 48 },
	{ 48, HELIENDLANDING, PRE_HELIPAD_block, 0, 48 }, { 48, HELIPAD1, 0, 0, 49 }, { 48, HELIPAD2, 0, 0, 50 }, { 48, HANGAR, 0, 0, 55 },
	{ 49, 0, NOTHING_block, 0, 51 },
	{ 50, 0, NOTHING_block, 0, 52 },
	/* landing */
	{ 51, 255, NOTHING_block, 0, 0 }, { 51, HELIPAD1, HELIPAD1_block, 0, 12 }, { 51, HANGAR, 0, 0, 55 }, { 51, 0, 0, 0, 12 },
	{ 52, 255, NOTHING_block, 0, 0 }, { 52, HELIPAD2, HELIPAD2_block, 0, 13 }, { 52, HANGAR, 0, 0, 55 }, { 52, 0, 0, 0, 13 },
	/* Helicopter -- takeoff */
	{ 53, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 54, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 55, 0, HANGAR2_AREA_block, 0, 56 }, // need to go to hangar when waiting in air
	{ 56, 0, HANGAR2_AREA_block, 0, 3 },
	/* runway 2 out support */
	{ 57, 255, OUT_WAY2_block, 0, 0 }, { 57, TAKEOFF, 0, 0, 58 }, { 57, 0, 0, 0, 58 },
	{ 58, 0, OUT_WAY2_block, 0, 59 },
	{ 59, TAKEOFF, RUNWAY_OUT2_block, 0, 60 }, // takeoff
	{ 60, 0, RUNWAY_OUT2_block, 0, 61 },
	{ 61, STARTTAKEOFF, NOTHING_block, 0, 62 },
	{ 62, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* runway 2 in support */
	{ 63, LANDING, RUNWAY_IN2_block, 0, 64 },
	{ 64, 0, RUNWAY_IN2_block, 0, 65 },
	{ 65, 0, RUNWAY_IN2_block, 0, 66 },
	{ 66, ENDLANDING, RUNWAY_IN2_block, 0, 0 }, { 66, 255, 0, 0, 1 }, { 66, 255, 0, 0, 0 }, { 66, 0, 0, 0, 67 },
	{ 67, 0, IN_WAY2_block, 0, 68 },
	{ 68, 255, IN_WAY2_block, 0, 0 }, { 68, 255, TERM_GROUP2_block, 0, 1 }, { 68, 255, TERM_GROUP1_block, 0, 0 }, { 68, HANGAR, HANGAR2_AREA_block, 0, 22 }, { 68, 0, 0, 0, 22 },
	{ 69, 255, RUNWAY_IN2_block, 0, 0 }, { 69, 0, RUNWAY_IN2_block, 0, 63 },
	{ 70, 255, TERM_GROUP2_EXIT1_block, 0, 0 }, { 70, HELIPAD1, HELIPAD1_block, 0, 12 }, { 70, HELITAKEOFF, HELIPAD1_block, 0, 12 }, { 70, 0, 0, 0, 71 },
	{ 71, 255, TERM_GROUP2_EXIT1_block, 0, 0 }, { 71, HELIPAD2, HELIPAD2_block, 0, 13 }, { 71, HELITAKEOFF, HELIPAD1_block, 0, 12 }, { 71, 0, 0, 0, 24 },
	{ 72, 0, HELIPAD1_block, 0, 53 },
	{ 73, 0, HELIPAD2_block, 0, 54 },
	{ 74, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 75, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 76, 255, RUNWAY_IN_block, 0, 0 }, { 76, 0, RUNWAY_IN_block, 0, 37 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

static const HangarTileTable _airport_depots_intercontinental2[] = { {{0, 1}, DIR_SE, 0}, {{11, 1}, DIR_SE, 1}  };
static const byte _airport_terminal_intercontinental2[] = {2, 1, 2, 1, 2, 2};
static const byte _airport_entries_intercontinental2[] = {55, 54, 56, 57};
static const AirportFTAbuildup _airport_fta_intercontinental2[] = {
  /* Hangars */
	{  0, HANGAR, NOTHING_block, 0, 2 }, { 0, 255, 0, 0, 0}, { 0, 255, 0, 0, 1}, { 0, 255, 0, 0, 2}, { 0, 255, 0, 0, 3}, { 0, 255, 0, 0, 4}, { 0, 0, 0, 0, 2},
  {  1, HANGAR, NOTHING_block, 0, 3 }, { 1, 255, TERM_GROUP1_block, 0, 4}, { 1, 255, TERM_GROUP1_block, 0, 3}, { 1, 255, TERM_GROUP1_block, 0, 2}, { 1, 255, TERM_GROUP1_block, 0, 1},  { 1, 255, TERM_GROUP1_block, 0, 0},  { 1, TAKEOFF, 0, 0, 3}, { 1, 0, TERM_GROUP1_block, 0, 3 },
  /* Taxi */
  {  2, 255,HANGAR1_AREA_block, 0, 0 }, { 2, HANGAR, 0, 0, 0 }, { 2, 0 ,0, 0, 12 },
  {  3, 255,HANGAR2_AREA_block, 0, 0 }, { 3, HANGAR, 0, 0, 1 }, { 3, 0, 0, 0, 20 },
  /* Terminals */
  {  4, TERM1, TERM1_block, 0, 12 },
	{  5, TERM2, TERM2_block, 0, 13 },
	{  6, TERM3, TERM3_block, 0, 14 },
  {  7, TERM4, TERM4_block, 0, 15 },
  {  8, TERM5, TERM5_block, 0, 16 },
  {  9, TERM6, TERM6_block, 0, 17 },
  { 10, TERM7, TERM7_block, 0, 18 },
  { 11, TERM8, TERM8_block, 0, 19 },
  /* Taxi */
  { 12, 255, NEW_block, 0, 0 }, { 12, TERM1, TERM1_block, 0, 4 }, { 12, 0,0, 0, 13 },
	{ 13, 255, NEW2_block, 0, 0 }, { 13, TERM2, TERM2_block, 0, 5 }, { 13, 0,0, 0, 14 },
	{ 14, 255, NEW3_block, 0, 0 }, { 14, TERM3, TERM3_block, 0, 6 }, { 14, 0, 0, 0, 15 },
  { 15, 255, NEW4_block, 0, 0 }, { 15, TERM4, TERM4_block, 0, 7 }, { 15, 0, 0, 0, 29 },
  { 16, 255, NEW5_block, 0, 0 }, { 16, TERM5, TERM5_block, 0, 8 }, { 16, 0, 0, 0, 17 },
  { 17, 255, NEW6_block, 0, 0 }, { 17, TERM6, TERM6_block, 0, 9 }, { 17, 0,0, 0, 18 },
  { 18, 255, NEW7_block, 0, 0 }, { 18, TERM7, TERM7_block, 0, 10 }, { 18, 0, 0, 0, 19 },
  { 19, 255, NEW8_block, 0, 0 }, { 19, TERM8, TERM8_block, 0, 11 }, { 19, 0, 0, 0, 3},
  { 20, 0, NEW9_block, 0, 21 },
  { 21, 255, TERM_GROUP2_ENTER2_block, 0, 0 }, { 21, TAKEOFF,0, 0, 31 }, { 21, 0,TERM_GROUP1_block , 0, 22 },
  { 22, 0, TERM_GROUP1_block , 0, 23 },
  { 23, 255, NEW11_block, 0, 0 }, { 23, TERM7, 0, 0, 18 }, { 23, TERM8, 0, 0, 18 }, { 23, 0, 0, 0, 24 },
  { 24, 255, NEW12_block, 0, 0 }, { 24, HANGAR,0, 0, 16 }, { 24, TERM5, 0, 0, 16 }, { 24, TERM6, 0, 0, 16 }, { 24, 0, 0, 0, 58 },
  { 25, 255, NEW13_block, 0, 0 }, { 25, HANGAR, 0, 0, 26 }, { 25, TERM4, 0, 0, 15 }, { 25, HELIPAD1, 0, 0, 15 }, { 25, HELIPAD2, 0, 0, 15 }, { 25, 0, 0, 0, 26 },
  { 26, 255, NEW14_block, 0, 0 }, { 26, HANGAR, 0, 0, 27 }, { 26, TERM2, 0, 0, 13 }, { 26, TERM3, 0, 0, 13 }, { 26, 0, 0, 0, 27 },
  { 27, 0,TAXIWAY_BUSY_block, 0, 28 },
  { 28, 0, TERM_GROUP2_ENTER1_block, 0, 2 },
  { 29, 255, TERM_GROUP2_EXIT1_block, 0, 0 }, { 29, HELIPAD1, HELIPAD1_block, 0, 46 },  { 29, 0, 0, 0, 30 },
  { 30, 255, TERM_GROUP2_EXIT2_block, 0, 0 }, { 30, HELIPAD2, HELIPAD2_block, 0, 47 },  { 30, 0, 0, 0, 16 },
	{ 31, 0, NEW15_block, 0, 32 },
	{ 32, 0, NEW16_block, 0, 33 },
  { 33, 255, NEW17_block, 0, 0 }, { 33, 0, 0, 0, 34 }, { 33, 0, 0, 0, 35 },
  { 34, 0, OUT_WAY_block, 0, 40 },
  { 35, 0, OUT_WAY2_block, 0, 43 },
  { 36, 0, IN_WAY_block, 0, 38 },
  { 37, 0, IN_WAY2_block, 0, 38 },
  { 38, 0, NEW18_block, 0, 39 },
  { 39, 0, NEW19_block, 0, 27 },
	/* takeoff */
	{ 40, TAKEOFF, RUNWAY_OUT_block, 0, 41 },
	{ 41, STARTTAKEOFF, NOTHING_block, 0, 42 },
	{ 42, ENDTAKEOFF, NOTHING_block, 0, 0 },
	/* takeoff 2 */
	{ 43, TAKEOFF, OUT_WAY_block2, 0, 44 },
	{ 44, STARTTAKEOFF, NOTHING_block, 0, 45 },
	{ 45, ENDTAKEOFF, NOTHING_block, 0, 0 },
  /* Helipads */
  { 46, HELIPAD1, HELIPAD1_block, 0, 46 }, { 46, HANGAR, 0, 0, 29 }, { 46, HELITAKEOFF, 0, 0, 60 },
	{ 47, HELIPAD2, HELIPAD2_block, 0, 47 }, { 47, HANGAR, 0, 0, 30 }, { 47, HELITAKEOFF, 0, 0, 61 },  
	/* landing */
	{ 48, FLYING, NOTHING_block, 0, 56 }, { 48, LANDING, 0, 0, 49 },  { 48, HELILANDING, 0, 0, 66 },
	{ 49, LANDING, RUNWAY_IN_block, 0, 50 },
	{ 50, ENDLANDING, RUNWAY_IN_block, 0, 0 }, { 50, 255, 0, 0, 0}, { 50, 255, 0, 0, 1}, { 50, 255, 0, 0, 2}, { 50, 255, 0, 0, 3}, { 50, 255, 0, 0, 4}, { 50, 0, 0, 0, 36},
	/* landing 2 */
	{ 51, FLYING, NOTHING_block, 0, 54 }, { 51, LANDING, 0, 0, 52 }, { 51, HELILANDING, 0, 0, 66 },
	{ 52, LANDING, RUNWAY_IN2_block, 0, 53 },
	{ 53, ENDLANDING, RUNWAY_IN2_block, 0, 0 }, { 53, 255, 0, 0, 0}, { 53, 255, 0, 0, 1}, { 53, 255, 0, 0, 2}, { 53, 255, 0, 0, 3}, { 53, 255, 0, 0, 4}, { 53, 0, 0, 0, 37},
	/* In air */
	{ 54, 0, NOTHING_block, 0, 55 },
	{ 55, 0, NOTHING_block, 0, 72 },
	{ 56, 0, NOTHING_block, 0, 57 },
	{ 57, 0, NOTHING_block, 0, 71 },
  /* Taxi */
  { 58, 0, NEW20_block, 0, 59 },
  { 59, 255, TERM_GROUP2_block, 0, 0 }, {  59, HELITAKEOFF, 0, 0, 70 }, {  59, 0, 0, 0, 25 },
  /* Helitakeoff */ 
  { 60, 0, HELIPAD1_block, 0, 62 },
  { 61, 0, HELIPAD2_block, 0, 63 },
  { 62, HELITAKEOFF, NOTHING_block, 0, 0 },
  { 63, HELITAKEOFF, NOTHING_block, 0, 0 },
  /* Landing */
	{ 64, 255, NOTHING_block, 0, 0 }, { 64, HELIPAD1, HELIPAD1_block, 0, 46 },
	{ 65, 255, NOTHING_block, 0, 0 }, { 65, HELIPAD2, HELIPAD2_block, 0, 47 },
	/* Helicopter -- stay in air in special place as a buffer to choose from helipads */
	{ 66, HELILANDING, PRE_HELIPAD_block, 0, 67 },
	{ 67, HELIENDLANDING, PRE_HELIPAD_block, 0, 67 }, { 67, HELIPAD1, 0, 0, 68 }, { 67, HELIPAD2, 0, 0, 69 }, { 67, HANGAR, 0, 0, 73 },
	{ 68, 0, NOTHING_block, 0, 64 }, // helipad1 approach
	{ 69, 0, NOTHING_block, 0, 65 },
  { 70, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 71, 0, NOTHING_block, 0, 51 },
	{ 72, 0, NOTHING_block, 0, 48 },
	{ 73, 0, HANGAR2_AREA_block, 0, 74 },
	{ 74, 0, HANGAR2_AREA_block, 0, 3 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

static const HangarTileTable _airport_depots_circle[] = {{ {6, 6}, DIR_SW, 0 }, {{6, 8}, DIR_NW, 1 }, {{8, 6}, DIR_SE, 2 }, {{8, 8}, DIR_NE, 3 } };
static const byte _airport_terminal_circle[] = {4, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1 };
static const byte _airport_entries_circle[] = {163, 162, 161, 160};
static const AirportFTAbuildup _airport_fta_circle[] = {
  /* Hangars */
  { 0, HANGAR, NOTHING_block, 0, 4 }, { 0, 255, HANGAR1_AREA_block | NEW12_block, 0, 4 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 5 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 6 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 7 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 8 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 9 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 10 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 11 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 0 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 1 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 2 }, { 0, 255, HANGAR1_AREA_block | NEW11_block | NEW12_block, NEW4_block, 3 }, { 0, TERM8, HANGAR1_AREA_block | NEW12_block, 0, 4 }, { 0, TERM9, HANGAR1_AREA_block | NEW12_block, 0, 4 }, { 0, TAKEOFF, HANGAR1_AREA_block | NEW12_block, CIRCLE_block, 4 }, { 0, 0, HANGAR1_AREA_block | NEW12_block, NEW4_block | CIRCLE_block, 4 }, 
  { 1, HANGAR, NOTHING_block, 0, 5 }, { 1, 255, HANGAR2_AREA_block | NEW5_block, 0, 1 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 2 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 3 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 4 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 5 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 6 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 7 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 8 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 9 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 10 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 11 }, { 1, 255, HANGAR2_AREA_block | NEW4_block | NEW5_block, NEW2_block, 0 }, { 1, TERM3, HANGAR2_AREA_block | NEW5_block, 0, 5 }, { 1, TERM4, HANGAR2_AREA_block | NEW5_block, 0, 5 }, { 1, TAKEOFF, HANGAR2_AREA_block | NEW5_block, CIRCLE_block, 5 }, { 1, 0, HANGAR2_AREA_block | NEW5_block, NEW2_block | CIRCLE_block, 5 },
  { 2, HANGAR, NOTHING_block, 0, 6 }, { 2, 255, NEW19_block, HANGAR1_AREA_block, 7 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 8 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 9 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 10 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 11 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 0 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 1 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 2 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 3 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 4 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 5 }, { 2, 255, NEW18_block | NEW19_block, HANGAR1_AREA_block | NEW6_block, 6 }, { 2, TERM13, NEW19_block, HANGAR1_AREA_block, 6 }, { 2, TERM14, NEW19_block, HANGAR1_AREA_block, 6 }, { 2, TAKEOFF, NEW19_block, HANGAR1_AREA_block | CIRCLE_block, 6 }, { 2, 0, NEW19_block, HANGAR1_AREA_block | NEW6_block | CIRCLE_block, 6 }, 
  { 3, HANGAR, NOTHING_block, 0, 7 }, { 3, 255, TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block, 10 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 11 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 0 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 1 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 2 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 3 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 4 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 5 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 6 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 7 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 8 }, { 3, 255, TERM_GROUP2_EXIT1_block | TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block, 9 }, { 3, TERM18, TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block, 7 }, { 3, TERM19, TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block, 7 }, { 3, TAKEOFF, TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | CIRCLE_block, 7 }, { 3, 0, TERM_GROUP2_EXIT2_block, HANGAR2_AREA_block | NEW8_block | CIRCLE_block, 7 }, 
  { 4, 255, HANGAR1_AREA_block, 0, 0 }, { 4, HANGAR, 0, 0, 0 }, { 4, 0, NEW12_block, 0, 39 },   
  { 5, 255, HANGAR2_AREA_block, 0, 0 }, { 5, HANGAR, 0, 0, 1 }, { 5, 0, NEW5_block, 0, 32 },   
  { 6, 255, 0, HANGAR1_AREA_block, 0 }, { 6, HANGAR, 0, 0, 2 }, { 6, 0, NEW19_block, 0, 46 },   
  { 7, 255, 0, HANGAR2_AREA_block, 0 }, { 7, HANGAR, 0, 0, 3 }, { 7, 0, TERM_GROUP2_EXIT2_block, 0, 53 },    
  /* Terminals */
  { 8, TERM1, TERM1_block, 0, 28 }, { 8, TAKEOFF, 0, 0, 28 }, { 8, 0, 0, 0, 29 },          
	{ 9, TERM2, TERM2_block, 0, 30 },          
	{ 10, TERM3, TERM3_block, 0, 31 }, { 10, HANGAR, 0, 0, 32 }, { 10, 0, 0, 0, 31 },          
  { 11, TERM4, TERM4_block, 0, 33 }, { 11, HANGAR, 0, 0, 32 }, { 11, 0, 0, 0, 33 },        
  { 12, TERM5, TERM5_block, 0, 34 },            
  { 13, TERM6, TERM6_block, 0, 36 }, { 13, TAKEOFF, 0, 0, 35 }, { 13, 0, 0, 0, 36 },          
  { 14, TERM7, TERM7_block, 0, 37 },          
  { 15, TERM8, TERM8_block, 0, 38 }, { 15, HANGAR, 0, 0, 39 }, { 15, 0, 0, 0, 38 },           
  { 16, TERM9, TERM9_block, 0, 40 }, { 16, HANGAR, 0, 0, 39 }, { 16, 0, 0, 0, 40 },            
	{ 17, TERM10, TERM10_block, 0, 41 },        
	{ 18, TERM11, TERM11_block, 0, 43 }, { 18, TAKEOFF, 0, 0, 42 }, { 18, 0, 0, 0, 43 },          
  { 19, TERM12, TERM12_block, 0, 44 },         
  { 20, TERM13, TERM13_block, 0, 45 }, { 20, HANGAR, 0, 0, 46 }, { 20, 0, 0, 0, 45 },          
  { 21, TERM14, TERM14_block, 0, 47 }, { 21, HANGAR, 0, 0, 46 }, { 21, 0, 0, 0, 47 },         
  { 22, TERM15, TERM15_block, 0, 48 },         
  { 23, TERM16, TERM16_block, 0, 50 }, { 23, TAKEOFF, 0, 0, 49 }, { 23, 0, 0, 0, 50 },          
  { 24, TERM17, TERM17_block, 0, 51 },          
	{ 25, TERM18, TERM18_block, 0, 52 }, { 25, HANGAR, 0, 0, 53 }, { 25, 0, 0, 0, 52 },    
	{ 26, TERM19, TERM19_block, 0, 54 }, { 26, HANGAR, 0, 0, 53 }, { 26, 0, 0, 0, 54 },        
  { 27, TERM20, TERM20_block, 0, 55 },          
  /* Terminals Taxi */
  { 28, 255, NEW_block, CIRCLE_block, 0 }, { 28, TERM1, TERM1_block, 0, 8 }, { 28, 0, 0, CIRCLE_block, 56 },
	{ 29, 255, NEW2_block, CIRCLE_block, 0 }, { 29, TERM1, TERM1_block, 0, 8 }, { 29, 0,0, CIRCLE_block, 30 },
	{ 30, 255, NEW3_block, CIRCLE_block, 0 }, { 30, TERM2, TERM2_block, 0, 9 }, { 30, 0, 0, CIRCLE_block, 31 },
  { 31, 255, NEW4_block, CIRCLE_block, 0 }, { 31, TERM3, TERM3_block, 0, 10 }, { 31, 0, 0, CIRCLE_block, 57 }, 
  { 32, 255, NEW5_block, 0, 0 }, { 32, TERM3, TERM3_block, 0, 10 }, { 32, TERM4, TERM4_block, 0, 11 }, { 32, HANGAR, 0, 0, 5 }, { 32, TAKEOFF, 0, CIRCLE_block, 57 }, { 32, 0, 0, NEW2_block | CIRCLE_block, 57 }, 
  { 33, 255, NEW6_block, CIRCLE_block, 0 }, { 33, TERM4, TERM4_block, 0, 11 }, { 33, 0, 0, CIRCLE_block, 34 }, 
  { 34, 255, NEW7_block, CIRCLE_block, 0 }, { 34, TERM5, TERM5_block, 0, 12 }, { 34, TAKEOFF, NEW7_block, 0, 70 }, { 34, TAKEOFF, 0, CIRCLE_block, 35 }, { 34, 0, 0, CIRCLE_block, 35 },  
  { 35, 255, NEW8_block, CIRCLE_block, 0 }, { 35, TERM6, TERM6_block, 0, 13 }, { 35, 0, 0, CIRCLE_block, 58},
	{ 36, 255, NEW9_block, CIRCLE_block, 0 }, { 36, TERM6, TERM6_block, 0, 13 }, { 36, 0, 0, CIRCLE_block, 37 },
	{ 37, 255, NEW10_block, CIRCLE_block, 0 }, { 37, TERM7, TERM7_block, 0, 14 }, { 37, 0, 0, CIRCLE_block, 38 },
  { 38, 255, NEW11_block, CIRCLE_block, 0 }, { 38, TERM8, TERM8_block, 0, 15 }, { 38, 0 , 0, CIRCLE_block, 59 },
  { 39, 255, NEW12_block, 0, 0 }, { 39, TERM8, TERM8_block, 0, 15 }, { 39, TERM9, TERM9_block, 0, 16 }, { 39, HANGAR, 0, 0, 4 }, { 39, TAKEOFF, 0, CIRCLE_block, 59 },  { 39, 0, 0, NEW4_block | CIRCLE_block, 59 }, 
  { 40, 255, NEW13_block, CIRCLE_block, 0 }, { 40, TERM9, TERM9_block, 0, 16 }, { 40, 0, 0, CIRCLE_block, 41 }, 
  { 41, 255, NEW14_block, CIRCLE_block, 0 }, { 41, TERM10, TERM10_block, 0, 17 }, { 41, TAKEOFF, NEW14_block, 0, 80 }, { 41, TAKEOFF, 0, CIRCLE_block, 42 }, { 41, 0, 0, CIRCLE_block, 42 },  
  { 42, 255, NEW15_block, CIRCLE_block, 0 }, { 42, TERM11, TERM11_block, 0, 18 }, { 42, 0, 0, CIRCLE_block, 60},
	{ 43, 255, NEW16_block, CIRCLE_block, 0 }, { 43, TERM11, TERM11_block, 0, 18 }, { 43, 0, 0, CIRCLE_block, 44 },
	{ 44, 255, NEW17_block, CIRCLE_block, 0 }, { 44, TERM12, TERM12_block, 0, 19 }, { 44, 0, 0, CIRCLE_block, 45 },
  { 45, 255, NEW18_block, CIRCLE_block, 0 }, { 45, TERM13, TERM13_block, 0, 20 }, { 45, 0, 0, CIRCLE_block, 61 }, 
  { 46, 255, NEW19_block, 0, 0 }, { 46, TERM13, TERM13_block, 0, 20 }, { 46, TERM14, TERM14_block, 0, 21 }, { 46, HANGAR, 0, 0, 6 }, { 46, TAKEOFF, 0, CIRCLE_block, 61 }, { 46, 0, 0, NEW6_block | CIRCLE_block, 61 }, 
  { 47, 255, NEW20_block, CIRCLE_block, 0 }, { 47, TERM14, TERM14_block, 0, 21 }, { 47, 0, 0, CIRCLE_block, 48 }, 
  { 48, 255, TERM_GROUP1_block, CIRCLE_block, 0 }, { 48, TERM15, TERM15_block, 0, 22 }, { 48, TAKEOFF, TERM_GROUP1_block, 0, 90 }, { 48, TAKEOFF, 0, CIRCLE_block, 49 }, { 48, 0, 0, CIRCLE_block, 49 },  
  { 49, 255, TERM_GROUP2_block, CIRCLE_block, 0 }, { 49, TERM16, TERM16_block, 0, 23 }, { 49, 0, 0, CIRCLE_block, 62}, 
	{ 50, 255, TERM_GROUP2_ENTER1_block, CIRCLE_block, 0 }, { 50, TERM16, TERM16_block, 0, 23 }, { 50, 0, 0, CIRCLE_block, 51 },
	{ 51, 255, TERM_GROUP2_ENTER2_block, CIRCLE_block, 0 }, { 51, TERM17, TERM17_block, 0, 24 }, { 51, 0, 0, CIRCLE_block, 52 },
  { 52, 255, TERM_GROUP2_EXIT1_block, CIRCLE_block, 0 }, { 52, TERM18, TERM18_block, 0, 25 }, { 52, 0, 0, CIRCLE_block, 63 }, 
  { 53, 255, TERM_GROUP2_EXIT2_block, 0, 0 }, { 53, TERM18, TERM18_block, 0, 25 }, { 53, TERM19, TERM19_block, 0, 26 }, { 53, HANGAR, 0, 0, 7 }, { 53, TAKEOFF, 0, CIRCLE_block, 63 }, { 53, 0, 0, NEW8_block | CIRCLE_block, 63 }, 
  { 54, 255, PRE_HELIPAD_block, CIRCLE_block, 0 }, { 54, TERM19, TERM19_block, 0, 26 }, { 54, 0, 0, CIRCLE_block, 55 }, 
  { 55, 255, HELIPAD_GROUP_block, CIRCLE_block, 0 }, { 55, TERM20, TERM20_block, 0, 27 }, { 55, TAKEOFF, HELIPAD_GROUP_block, 0, 100 }, { 55, TAKEOFF, 0, CIRCLE_block, 28 }, { 55, 0, 0, CIRCLE_block, 28 },  
  /* Taxi circle 1*/
  { 56, 255, 0, NEW_block | CIRCLE_block, 0 }, { 56, TAKEOFF, 0, NEW_block, 102 }, { 56, TAKEOFF, 0, CIRCLE_block, 29 },  { 56, HELITAKEOFF, 0, 0, 168 }, { 56, HELITAKEOFF, 0, CIRCLE_block, 29 }, { 56, 0, 0, CIRCLE_block, 29 }, 
	{ 57, 255, 0, NEW2_block | CIRCLE_block, 0 }, { 57, TAKEOFF, 0, NEW2_block, 67 }, { 57, TAKEOFF, 0, CIRCLE_block, 33 }, { 57, HANGAR, 0, 0, 32 }, { 57, HANGAR, 0, CIRCLE_block, 33 }, { 57, 0, 0, CIRCLE_block, 33 },
	{ 58, 255, 0, NEW3_block | CIRCLE_block, 0 }, { 58, TAKEOFF, 0, NEW3_block, 72 }, { 58, TAKEOFF, 0, CIRCLE_block, 36 }, { 58, HELITAKEOFF, 0, 0, 164 }, { 58, HELITAKEOFF, 0, CIRCLE_block, 36 }, { 58, 0, 0, CIRCLE_block, 36 },
  { 59, 255, 0, NEW4_block | CIRCLE_block, 0 }, { 59, TAKEOFF, 0, NEW4_block, 77 }, { 59, TAKEOFF, 0, CIRCLE_block, 40 }, { 59, HANGAR, 0, 0, 39 }, { 59, HANGAR, 0, CIRCLE_block, 40 }, { 59, 0, 0, CIRCLE_block, 40 },
  { 60, 255, 0, NEW5_block | CIRCLE_block, 0 }, { 60, TAKEOFF, 0, NEW5_block, 82 }, { 60, TAKEOFF, 0, CIRCLE_block, 43 }, { 60, HELITAKEOFF, 0, 0, 170 }, { 60, HELITAKEOFF, 0, CIRCLE_block, 43 }, { 60, 0, 0, CIRCLE_block, 43 }, 
	{ 61, 255, 0, NEW6_block | CIRCLE_block, 0 }, { 61, TAKEOFF, 0, NEW6_block, 87 }, { 61, TAKEOFF, 0, CIRCLE_block, 47 }, { 61, HANGAR, 0, 0, 46 }, { 61, HANGAR, 0, CIRCLE_block, 47 }, { 61, 0, 0, CIRCLE_block, 47 }, 
	{ 62, 255, 0, NEW7_block | CIRCLE_block, 0 }, { 62, TAKEOFF, 0, NEW7_block, 92 }, { 62, TAKEOFF, 0, CIRCLE_block, 50 }, { 62, HELITAKEOFF, 0, 0, 166 }, { 62, HELITAKEOFF, 0, CIRCLE_block, 50 }, { 62, 0, 0, CIRCLE_block, 50 },
  { 63, 255, 0, NEW8_block | CIRCLE_block, 0 }, { 63, TAKEOFF, 0, NEW8_block, 97 }, { 63, TAKEOFF, 0, CIRCLE_block, 54 }, { 63, HANGAR, 0, 0, 53 }, { 63, HANGAR, 0, CIRCLE_block, 54 }, { 63, 0, 0, CIRCLE_block, 54 },
  /* Taxi circle 2*/
  { 64, 255, 0, NEW9_block, 0 }, { 64, 0, 0, NEW9_block, 65 },
  { 65, 255, 0, NEW9_block | NEW_block | CIRCLE_block, 0 }, { 65, 0, 0, NEW_block | CIRCLE_block, 56 },
  { 66, 0, 0, NEW10_block, 30 },
  { 67, 255, 0, NEW2_block | NEW11_block, 0 }, { 67, 0, 0, NEW11_block, 68 },
  { 68, 255, 0, NEW11_block, 0 }, { 68, 0, 0, NEW11_block, 69 }, 
  { 69, 255, 0, TERM3_block | NEW11_block, 0 }, { 69, 0, 0, TERM3_block, 108 }, 
  { 70, 255, NEW7_block, NEW12_block, 0 }, { 70, 0, 0, NEW12_block, 71 },
  { 71, 0, 0, NEW12_block, 106 },  
  { 72, 255, 0, NEW3_block | NEW13_block, 0 }, { 72, 0, 0, NEW13_block, 73 },
  { 73, 0, 0, NEW13_block, 104 },   
  { 74, 255, 0, NEW14_block, 0 }, { 74, 0, 0, NEW14_block, 75 },
  { 75, 255, 0, NEW14_block | NEW3_block | CIRCLE_block, 0 }, { 75, 0, 0, NEW3_block | CIRCLE_block, 58 },
  { 76, 0, 0, NEW15_block, 37 },
  { 77, 255, 0, NEW4_block | NEW16_block, 0 }, { 77, 0, 0, NEW16_block, 78 },  
  { 78, 255, 0, NEW16_block, 0 }, { 78, 0, 0,NEW16_block, 79 },  
  { 79, 255, 0, NEW16_block | TERM7_block, 0 }, { 79, 0, 0, TERM7_block, 116 },
  { 80, 255, NEW14_block, NEW17_block, 0 }, { 80, 0, 0, NEW17_block, 81 },
  { 81, 0, 0, NEW17_block, 114 },  
  { 82, 255, 0, NEW5_block | NEW18_block, 0 }, { 82, 0, 0, NEW18_block, 83 },
  { 83, 0, 0, NEW18_block, 112 },   
  { 84, 255, 0, NEW19_block, 0 }, { 84, 0, 0, NEW19_block, 85 },
  { 85, 255, 0, NEW19_block | NEW5_block | CIRCLE_block, 0 }, { 85, 0, 0, NEW5_block | CIRCLE_block, 60 },
  { 86, 0, 0, NEW20_block, 44 },
  { 87, 255, 0, NEW6_block | TERM_GROUP1_block, 0 }, { 87, 0, 0, TERM_GROUP1_block, 88 },  
  { 88, 255, 0, TERM_GROUP1_block, 0 }, { 88, 0, 0, TERM_GROUP1_block, 89 },  
  { 89, 255, 0, TERM_GROUP1_block | TERM11_block, 0 }, { 89, 0, 0, TERM11_block, 124 },  
  { 90, 255, TERM_GROUP1_block, TERM_GROUP2_block, 0 }, { 90, 0, 0, TERM_GROUP2_block, 91 },
  { 91, 0, 0, TERM_GROUP2_block, 122 }, 
  { 92, 255, 0, NEW7_block | TERM_GROUP2_ENTER1_block, 0 }, { 92, 0, 0, TERM_GROUP2_ENTER1_block, 93 },
  { 93, 0, 0, TERM_GROUP2_ENTER1_block, 120 },  
  { 94, 255, 0, TERM_GROUP2_ENTER2_block, 0 }, { 94, 0, 0, TERM_GROUP2_ENTER2_block, 95 },
  { 95, 255, 0, TERM_GROUP2_ENTER2_block | NEW7_block | CIRCLE_block, 0 }, { 95, 0, 0, NEW7_block | CIRCLE_block, 62 },
  { 96, 0, 0, TERM_GROUP2_EXIT1_block, 51 },
  { 97, 255, 0, NEW8_block | TERM_GROUP2_EXIT2_block, 0 }, { 97, 0, 0, TERM_GROUP2_EXIT2_block, 98 },  
  { 98, 255, 0, TERM_GROUP2_EXIT2_block, 0 },  { 98, 0, 0, TERM_GROUP2_EXIT2_block, 99 },  
  { 99, 255, 0, TERM_GROUP2_EXIT2_block | TERM15_block, 0 }, { 99, 0, 0, TERM15_block, 132 },  
  {100, 255, HELIPAD_GROUP_block, PRE_HELIPAD_block, 0 }, { 100, 0, 0, PRE_HELIPAD_block, 101 },
  {101, 0, 0, PRE_HELIPAD_block, 130 },  
  {102, 255, 0, NEW_block | HELIPAD_GROUP_block, 0 }, {102, 0, 0, HELIPAD_GROUP_block, 103 },
  {103, 0, 0, HELIPAD_GROUP_block, 128 },   
  /* Taxi circle 3*/
  {104, 0, 0, TERM1_block, 105 },
  {105, 0, 0, TERM1_block, 106 },
  {106, 0, 0, TERM2_block, 107 },
  {107, 0, 0, TERM2_block, 108 },
  {108, 0, 0, TERM3_block, 136 },
  {109, 255, RUNWAY_IN_block, TERM4_block, 0 }, {109, TERM1, 0, TERM4_block, 111 }, {109, 0, 0, TERM4_block, 110 },
  {110, 0, 0, TERM4_block, 66 },
  {111, 0, 0, TERM4_block, 64 },
  {112, 0, 0, TERM5_block, 113 },
  {113, 0, 0, TERM5_block, 114 },
  {114, 0, 0, TERM6_block, 115 },
  {115, 0, 0, TERM6_block, 116 },
  {116, 0, 0, TERM7_block, 139 }, 
  {117, 255, RUNWAY_IN2_block, TERM8_block, 0 }, {117, TERM6, 0, TERM8_block, 119 }, {117, 0, 0, TERM8_block, 118 },
  {118, 0, 0, TERM8_block, 76 },
  {119, 0, 0, TERM8_block, 74 },
  {120, 0, 0, TERM9_block, 121 },
  {121, 0, 0, TERM9_block, 122 },
  {122, 0, 0, TERM10_block, 123 },
  {123, 0, 0, TERM10_block, 124 },
  {124, 0, 0, TERM11_block, 142 }, 
  {125, 255, IN_WAY_block, TERM12_block, 0 }, {125, TERM11, 0, TERM12_block, 127 }, {125, 0, 0, TERM12_block, 126 },
  {126, 0, 0, TERM12_block, 86 },
  {127, 0, 0, TERM12_block, 84 },
  {128, 0, 0, TERM13_block, 129 },
  {129, 0, 0, TERM13_block, 130 },
  {130, 0, 0, TERM14_block, 131 },
  {131, 0, 0, TERM14_block, 132 },
  {132, 0, 0, TERM15_block, 145 }, 
  {133, 255, IN_WAY2_block, TERM16_block, 0 }, {133, TERM16, 0, TERM16_block, 135 }, {133, 0, 0, TERM16_block, 134 },
  {134, 0, 0, TERM16_block, 96 },
  {135, 0, 0, TERM16_block, 94 },
  /* takeoff */
	{ 136, TAKEOFF, RUNWAY_OUT_block, 0, 137 },
	{ 137, STARTTAKEOFF, NOTHING_block, 0, 138 },
	{ 138, ENDTAKEOFF, NOTHING_block, 0, 0 },
	{ 139, TAKEOFF, OUT_WAY_block2, 0, 140 },
	{ 140, STARTTAKEOFF, NOTHING_block, 0, 141 },
	{ 141, ENDTAKEOFF, NOTHING_block, 0, 0 },
	{ 142, TAKEOFF, OUT_WAY_block, 0, 143 },
	{ 143, STARTTAKEOFF, NOTHING_block, 0, 144 },
	{ 144, ENDTAKEOFF, NOTHING_block, 0, 0 },
	{ 145, TAKEOFF, OUT_WAY2_block, 0, 146 },
	{ 146, STARTTAKEOFF, NOTHING_block, 0, 147 },
	{ 147, ENDTAKEOFF, NOTHING_block, 0, 0 },
  /* landing */
	{ 148, FLYING, NOTHING_block, 0, 161 },	{ 148, LANDING, 0, 0, 149 }, { 148, HELILANDING, 0, 0, 172 },
	{ 149, LANDING, RUNWAY_IN_block, 0, 150 },
	{ 150, ENDLANDING, RUNWAY_IN_block, 0, 0 }, { 150, 255, 0, 0, 0}, { 150, 255, 0, 0, 1}, { 150, 255, 0, 0, 2}, { 150, 255, 0, 0, 3}, { 150, 255, 0, 0, 4}, { 150, 255, 0, 0, 5}, { 150, 255, 0, 0, 6}, { 150, 255, 0, 0, 7}, { 150, 255, 0, 0, 8},{ 150, 255, 0, 0, 9}, { 150, 255, 0, 0, 10}, { 150, 255, 0, 0, 11}, { 150, 0, RUNWAY_IN_block, 0, 109 },
	{ 151, FLYING, NOTHING_block, 0, 162 },	{ 151, LANDING, 0, 0, 152 },
	{ 152, LANDING, RUNWAY_IN2_block, 0, 153 },
	{ 153, ENDLANDING, RUNWAY_IN2_block, 0, 0 }, { 153, 255, 0, 0, 3}, { 153, 255, 0, 0, 4}, { 153, 255, 0, 0, 5}, { 153, 255, 0, 0, 6}, { 153, 255, 0, 0, 7}, { 153, 255, 0, 0, 8}, { 153, 255, 0, 0, 9}, { 153, 255, 0, 0, 10}, { 153, 255, 0, 0, 11}, { 153, 255, 0, 0, 0}, { 153, 255, 0, 0, 1}, { 153, 255, 0, 0, 2}, { 153, 0, RUNWAY_IN2_block, 0, 117 },
	{ 154, FLYING, NOTHING_block, 0, 163 },	{ 154, LANDING, 0, 0, 155 }, { 154, HELILANDING, 0, 0, 174 },
	{ 155, LANDING, IN_WAY_block, 0, 156 },
	{ 156, ENDLANDING, IN_WAY_block, 0, 0 }, { 156, 255, 0, 0, 6},{ 156, 255, 0, 0, 7}, { 156, 255, 0, 0, 8}, { 156, 255, 0, 0, 9}, { 156, 255, 0, 0, 10}, { 156, 255, 0, 0, 11}, { 156, 255, 0, 0, 0}, { 156, 255, 0, 0, 1}, { 156, 255, 0, 0, 2}, { 156, 255, 0, 0, 3}, { 156, 255, 0, 0, 4}, { 156, 255, 0, 0, 5}, { 156, 0, IN_WAY_block, 0, 125 },
	{ 157, FLYING, NOTHING_block, 0, 160 },	{ 157, LANDING, 0, 0, 158 },
	{ 158, LANDING, IN_WAY2_block, 0, 159 },
	{ 159, ENDLANDING, IN_WAY2_block, 0, 0 }, { 159, 255, 0, 0, 9}, { 159, 255, 0, 0, 10},{ 159, 255, 0, 0, 11}, { 159, 255, 0, 0, 0}, { 159, 255, 0, 0, 1}, { 159, 255, 0, 0, 2}, { 159, 255, 0, 0, 3}, { 159, 255, 0, 0, 4}, { 159, 255, 0, 0, 5}, { 159, 255, 0, 0, 6}, { 159, 255, 0, 0, 7}, { 159, 255, 0, 0, 8}, { 159, 0, IN_WAY2_block, 0, 133 },
	/* In air */
 	{ 160, 0, NOTHING_block, 0, 148 },
	{ 161, 0, NOTHING_block, 0, 151 },
	{ 162, 0, NOTHING_block, 0, 154 },
	{ 163, 0, NOTHING_block, 0, 157 },
  /* Helitakeoff */
 	{ 164, 0, 0, TERM17_block, 165 },
	{ 165, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 166, 0, 0, TERM18_block, 167 },
	{ 167, HELITAKEOFF, NOTHING_block, 0, 0 },
 	{ 168, 0, 0, TERM19_block, 169 },
	{ 169, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 170, 0, 0, TERM20_block, 171 },
	{ 171, HELITAKEOFF, NOTHING_block, 0, 0 },
  /* Helilanding */
	{ 172, HELILANDING, 0, TERM19_block, 173 },
	{ 173, HELIENDLANDING, 0, TERM19_block, 56 },{ 173, 255, 0, 0, 0}, { 173, 255, 0, 0, 1}, { 173, 255, 0, 0, 2}, { 173, 255, 0, 0, 3}, { 173, 255, 0, 0, 4}, { 173, 255, 0, 0, 5}, { 173, 255, 0, 0, 6}, { 173, 255, 0, 0, 7}, { 173, 255, 0, 0, 8},{ 173, 255, 0, 0, 9}, { 173, 255, 0, 0, 10}, { 173, 255, 0, 0, 11}, { 173, 0, 0, 0, 56 },
	{ 174, HELILANDING, 0, TERM20_block, 175 },
	{ 175, HELIENDLANDING, 0, TERM20_block, 60 }, { 175, 255, 0, 0, 6},{ 175, 255, 0, 0, 7}, { 175, 255, 0, 0, 8}, { 175, 255, 0, 0, 9}, { 175, 255, 0, 0, 10}, { 175, 255, 0, 0, 11}, { 175, 255, 0, 0, 0}, { 175, 255, 0, 0, 1}, { 175, 255, 0, 0, 2}, { 175, 255, 0, 0, 3}, { 175, 255, 0, 0, 4}, { 175, 255, 0, 0, 5}, { 175, 0, 0, 0, 60 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
}; 




/* heliports, oilrigs don't have depots */
static const byte _airport_entries_heliport[] = { 7, 7, 7, 7 };
static const AirportFTAbuildup _airport_fta_heliport[] = {
	{ 0, HELIPAD1, HELIPAD1_block, 0, 1 },
	{ 1, HELITAKEOFF, NOTHING_block, 0, 0 }, // takeoff
	{ 2, 255, AIRPORT_BUSY_block, 0, 0 }, { 2, HELILANDING, 0, 0, 3 }, { 2, HELITAKEOFF, 0, 0, 1 },
	{ 3, HELILANDING, AIRPORT_BUSY_block, 0, 4 },
	{ 4, HELIENDLANDING, AIRPORT_BUSY_block, 0, 4 }, { 4, HELIPAD1, HELIPAD1_block, 0, 0 }, { 4, HELITAKEOFF, 0, 0, 2 },
	/* In Air */
	{ 5, 0, NOTHING_block, 0, 6 },
	{ 6, 0, NOTHING_block, 0, 7 },
	{ 7, 0, NOTHING_block, 0, 8 },
	{ 8, FLYING, NOTHING_block, 0, 5 }, { 8, HELILANDING, HELIPAD1_block, 0, 2 }, // landing
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};
#define _airport_entries_oilrig _airport_entries_heliport
#define _airport_fta_oilrig _airport_fta_heliport

/* helidepots */
static const HangarTileTable _airport_depots_helidepot[] = { {{1, 0}, DIR_SE, 0} };
static const byte _airport_entries_helidepot[] = { 4, 4, 4, 4 };
static const AirportFTAbuildup _airport_fta_helidepot[] = {
	{  0, HANGAR, NOTHING_block, 0, 1 },
	{  1, 255, HANGAR2_AREA_block, 0, 0 }, { 1, HANGAR, 0, 0, 0 }, { 1, HELIPAD1, HELIPAD1_block, 0, 14 }, { 1, HELITAKEOFF, 0, 0, 15 }, { 1, 0, 0, 0, 0 },
	{  2, FLYING, NOTHING_block, 0, 3 }, { 2, HELILANDING, PRE_HELIPAD_block, 0, 7 }, { 2, HANGAR, 0, 0, 12 }, { 2, HELITAKEOFF, NOTHING_block, 0, 16 },
	/* In Air */
	{  3, 0, NOTHING_block, 0, 4 },
	{  4, 0, NOTHING_block, 0, 5 },
	{  5, 0, NOTHING_block, 0, 6 },
	{  6, 0, NOTHING_block, 0, 2 },
	/* Helicopter -- stay in air in special place as a buffer to choose from helipads */
	{  7, HELILANDING, PRE_HELIPAD_block, 0, 8 },
	{  8, HELIENDLANDING, PRE_HELIPAD_block, 0, 8 }, { 8, HELIPAD1, 0, 0, 9 }, { 8, HANGAR, 0, 0, 12 }, { 8, 0, 0, 0, 2 },
	{  9, 0, NOTHING_block, 0, 10 },
	/* landing */
	{ 10, 255, NOTHING_block, 0, 10 }, { 10, HELIPAD1, HELIPAD1_block, 0, 14 }, { 10, HANGAR, 0, 0, 1 }, { 10, 0, 0, 0, 14 },
	/* Helicopter -- takeoff */
	{ 11, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 12, 0, HANGAR2_AREA_block, 0, 13 }, // need to go to hangar when waiting in air
	{ 13, 0, HANGAR2_AREA_block, 0, 1 },
	{ 14, HELIPAD1, HELIPAD1_block, 0, 14 }, { 14, HANGAR, 0, 0, 1 }, { 14, HELITAKEOFF, 0, 0, 17 },
	{ 15, HELITAKEOFF, NOTHING_block, 0, 0 }, // takeoff outside depot
	{ 16, HELITAKEOFF, 0, 0, 14 },
	{ 17, 0, NOTHING_block, 0, 11 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

/* helistation */
static const HangarTileTable _airport_depots_helistation[] = { {{0, 0}, DIR_SE, 0} };
static const byte _airport_entries_helistation[] = { 25, 25, 25, 25 };
static const AirportFTAbuildup _airport_fta_helistation[] = {
	{  0, HANGAR, NOTHING_block, 0, 8 },    { 0, HELIPAD1, 0, 0, 1 }, { 0, HELIPAD2, 0, 0, 1 }, { 0, HELIPAD3, 0, 0, 1 }, { 0, HELITAKEOFF, 0, 0, 1 }, { 0, 0, 0, 0, 0 },
	{  1, 255, HANGAR2_AREA_block, 0, 0 },  { 1, HANGAR, 0, 0, 0 }, { 1, HELITAKEOFF, 0, 0, 3 }, { 1, 0, 0, 0, 4 },
	/* landing */
	{  2, FLYING, NOTHING_block, 0, 28 },   { 2, HELILANDING, 0, 0, 15 }, { 2, 0, 0, 0, 28 },
	/* helicopter side */
	{  3, HELITAKEOFF, NOTHING_block, 0, 0 }, // helitakeoff outside hangar2
	{  4, 255, TAXIWAY_BUSY_block, 0, 0 },  { 4, HANGAR, HANGAR2_AREA_block, 0, 1 }, { 4, HELITAKEOFF, 0, 0, 1 }, { 4, 0, 0, 0, 5 },
	{  5, 255, TAXIWAY_BUSY_block, 0, 0 },  { 5, HELIPAD1, HELIPAD1_block, 0, 6 }, { 5, HELIPAD2, HELIPAD2_block, 0, 7 }, { 5, HELIPAD3, HELIPAD3_block, 0, 8 }, { 5, 0, 0, 0, 4 },
	{  6, HELIPAD1, HELIPAD1_block, 0, 5 }, { 6, HANGAR, HANGAR2_AREA_block, 0, 5 }, { 6, HELITAKEOFF, 0, 0, 9 }, { 6, 0, 0, 0, 6 },
	{  7, HELIPAD2, HELIPAD2_block, 0, 5 }, { 7, HANGAR, HANGAR2_AREA_block, 0, 5 }, { 7, HELITAKEOFF, 0, 0, 10 }, { 7, 0, 0, 0, 7 },
	{  8, HELIPAD3, HELIPAD3_block, 0, 5 }, { 8, HANGAR, HANGAR2_AREA_block, 0, 5 }, { 8, HELITAKEOFF, 0, 0, 11 }, { 8, 0, 0, 0, 8 },
	{  9, 0, HELIPAD1_block, 0, 12 },
	{ 10, 0, HELIPAD2_block, 0, 13 },
	{ 11, 0, HELIPAD3_block, 0, 14 },
	{ 12, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 13, HELITAKEOFF, NOTHING_block, 0, 0 },
	{ 14, HELITAKEOFF, NOTHING_block, 0, 0 },
	/* heli - in flight moves */
	{ 15, HELILANDING, PRE_HELIPAD_block, 0, 16 },
	{ 16, HELIENDLANDING, PRE_HELIPAD_block, 0, 16 }, { 16, HELIPAD1, 0, 0, 17 }, { 16, HELIPAD2, 0, 0, 18 }, { 16, HELIPAD3, 0, 0, 19 }, { 16, HANGAR, 0, 0, 23 },
	{ 17, 0, NOTHING_block, 0, 20 },
	{ 18, 0, NOTHING_block, 0, 21 },
	{ 19, 0, NOTHING_block, 0, 22 },
	/* heli landing */
	{ 20, 255, NOTHING_block, 0, 0 }, { 20, HELIPAD1, HELIPAD1_block, 0, 6 }, { 20, HANGAR, 0, 0, 23 }, { 20, 0, 0, 0, 6 },
	{ 21, 255, NOTHING_block, 0, 0 }, { 21, HELIPAD2, HELIPAD2_block, 0, 7 }, { 21, HANGAR, 0, 0, 23 }, { 21, 0, 0, 0, 7 },
	{ 22, 255, NOTHING_block, 0, 0 }, { 22, HELIPAD3, HELIPAD3_block, 0, 8 }, { 22, HANGAR, 0, 0, 23 }, { 22, 0, 0, 0, 8 },
	{ 23, 0, HANGAR2_AREA_block, 0, 24 }, // need to go to helihangar when waiting in air
	{ 24, 0, HANGAR2_AREA_block, 0, 1 },
	{ 25, 0, NOTHING_block, 0, 26 },
	{ 26, 0, NOTHING_block, 0, 27 },
	{ 27, 0, NOTHING_block, 0, 2 },
	{ 28, 0, NOTHING_block, 0, 29 },
	{ 29, 0, NOTHING_block, 0, 30 },
	{ 30, 0, NOTHING_block, 0, 31 },
	{ 31, 0, NOTHING_block, 0, 32 },
	{ 32, 0, NOTHING_block, 0, 25 },
	{ MAX_ELEMENTS, 0, 0, 0, 0 } // end marker. DO NOT REMOVE
};

#endif /* AIRPORT_MOVEMENT_H */
