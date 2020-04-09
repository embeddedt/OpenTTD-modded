/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file airport.h Various declarations for airports */

#ifndef AIRPORT_H
#define AIRPORT_H

#include "direction_type.h"
#include "tile_type.h"

/** Some airport-related constants */
static const uint MAX_TERMINALS =  20;                       ///< maximum number of terminals per airport
static const uint MAX_HELIPADS  =   3;                       ///< maximum number of helipads per airport
static const uint MAX_ELEMENTS  = 767;                       ///< maximum number of aircraft positions at airport

static const uint NUM_AIRPORTTILES_PER_GRF = 255;            ///< Number of airport tiles per NewGRF; limited to 255 to allow extending Action3 with an extended byte later on.

static const uint NUM_AIRPORTTILES       = 256;              ///< Total number of airport tiles.
static const uint NEW_AIRPORTTILE_OFFSET = 74;               ///< offset of first newgrf airport tile
static const uint HUGE_AIRPORTTILE_OFFSET = 223;             ///< offset of first huge airport tile

static const uint INVALID_AIRPORTTILE    = NUM_AIRPORTTILES; ///< id for an invalid airport tile

/** Airport types */
enum AirportTypes {
	AT_SMALL              =   0, ///< Small airport.
	AT_LARGE              =   1, ///< Large airport.
	AT_HELIPORT           =   2, ///< Heli port.
	AT_METROPOLITAN       =   3, ///< Metropolitan airport.
	AT_INTERNATIONAL      =   4, ///< International airport.
	AT_COMMUTER           =   5, ///< Commuter airport.
	AT_HELIDEPOT          =   6, ///< Heli depot.
	AT_INTERCON           =   7, ///< Intercontinental airport.
	AT_HELISTATION        =   8, ///< Heli station airport.
	AT_OILRIG             =   9, ///< Oilrig airport.
	AT_INTERCONTINENTAL2  =  10, ///< Intercontinental airport 2.
    AT_CIRCLE             =  11, ///< Circle airport.
	NEW_AIRPORT_OFFSET    =  12, ///< Number of the first newgrf airport.  
	NUM_AIRPORTS          = 128, ///< Maximal number of airports.
	NUM_AIRPORTS_PER_GRF  = 128,
	AT_INVALID            = 254, ///< Invalid airport.
	AT_DUMMY              = 255, ///< Dummy airport.
};

/** Flags for airport movement data. */
enum AirportMovingDataFlags {
	AMED_NOSPDCLAMP = 1 << 0, ///< No speed restrictions.
	AMED_TAKEOFF    = 1 << 1, ///< Takeoff movement.
	AMED_SLOWTURN   = 1 << 2, ///< Turn slowly (mostly used in the air).
	AMED_LAND       = 1 << 3, ///< Landing onto landing strip.
	AMED_EXACTPOS   = 1 << 4, ///< Go exactly to the destination coordinates.
	AMED_BRAKE      = 1 << 5, ///< Taxiing at the airport.
	AMED_HELI_RAISE = 1 << 6, ///< Helicopter take-off.
	AMED_HELI_LOWER = 1 << 7, ///< Helicopter landing.
	AMED_HOLD       = 1 << 8, ///< Holding pattern movement (above the airport).
};

/** Movement States on Airports (headings target) */
enum AirportMovementStates {
	TO_ALL         =   0, ///< Go in this direction for every target.
	HANGAR         =   1, ///< Heading for hangar.
	TERM1          =   2, ///< Heading for terminal 1.
	TERM2          =   3, ///< Heading for terminal 2.
	TERM3          =   4, ///< Heading for terminal 3.
	TERM4          =   5, ///< Heading for terminal 4.
	TERM5          =   6, ///< Heading for terminal 5.
	TERM6          =   7, ///< Heading for terminal 6.
	HELIPAD1       =   8, ///< Heading for helipad 1.
	HELIPAD2       =   9, ///< Heading for helipad 2.
	TAKEOFF        =  10, ///< Airplane wants to leave the airport.
	STARTTAKEOFF   =  11, ///< Airplane has arrived at a runway for take-off.
	ENDTAKEOFF     =  12, ///< Airplane has reached end-point of the take-off runway.
	HELITAKEOFF    =  13, ///< Helicopter wants to leave the airport.
	FLYING         =  14, ///< %Vehicle is flying in the air.
	LANDING        =  15, ///< Airplane wants to land.
	ENDLANDING     =  16, ///< Airplane wants to finish landing.
	HELILANDING    =  17, ///< Helicopter wants to land.
	HELIENDLANDING =  18, ///< Helicopter wants to finish landing.
	TERM7          =  19, ///< Heading for terminal 7.
	TERM8          =  20, ///< Heading for terminal 8.
	HELIPAD3       =  21, ///< Heading for helipad 3.
	TERM9          = 22, ///< Heading for terminal 9.
	TERM10         = 23, ///< Heading for terminal 10.
	TERM11         = 24, ///< Heading for terminal 11.
	TERM12         = 25, ///< Heading for terminal 12.
	TERM13         = 26, ///< Heading for terminal 13.
	TERM14         = 27, ///< Heading for terminal 14.
	TERM15         = 28, ///< Heading for terminal 15.
	TERM16         = 29, ///< Heading for terminal 16.
	TERM17         = 30, ///< Heading for terminal 17.
	TERM18         = 31, ///< Heading for terminal 18.
	TERM19         = 32, ///< Heading for terminal 19.
	TERM20         = 33, ///< Heading for terminal 20.
	MAX_HEADINGS   = 33, ///< Last valid target to head for.
	TERMGROUP      = 255, ///< Aircraft is looking for a free terminal in a terminalgroup.
};

/** Movement Blocks on Airports blocks (eg_airport_flags). */
static const uint64
	TERM1_block              = 1ULL <<  0, ///< Block belonging to terminal 1.
	TERM2_block              = 1ULL <<  1, ///< Block belonging to terminal 2.
	TERM3_block              = 1ULL <<  2, ///< Block belonging to terminal 3.
	TERM4_block              = 1ULL <<  3, ///< Block belonging to terminal 4.
	TERM5_block              = 1ULL <<  4, ///< Block belonging to terminal 5.
	TERM6_block              = 1ULL <<  5, ///< Block belonging to terminal 6.
	HELIPAD1_block           = 1ULL <<  6, ///< Block belonging to helipad 1.
	HELIPAD2_block           = 1ULL <<  7, ///< Block belonging to helipad 2.
	RUNWAY_IN_OUT_block      = 1ULL <<  8,
	RUNWAY_IN_block          = 1ULL <<  8,
	AIRPORT_BUSY_block       = 1ULL <<  8,
	RUNWAY_OUT_block         = 1ULL <<  9,
	TAXIWAY_BUSY_block       = 1ULL << 10,
	OUT_WAY_block            = 1ULL << 11,
	IN_WAY_block             = 1ULL << 12,
	AIRPORT_ENTRANCE_block   = 1ULL << 13,
	TERM_GROUP1_block        = 1ULL << 14,
	TERM_GROUP2_block        = 1ULL << 15,
	HANGAR2_AREA_block       = 1ULL << 16,
	TERM_GROUP2_ENTER1_block = 1ULL << 17,
	TERM_GROUP2_ENTER2_block = 1ULL << 18,
	TERM_GROUP2_EXIT1_block  = 1ULL << 19,
	TERM_GROUP2_EXIT2_block  = 1ULL << 20,
	PRE_HELIPAD_block        = 1ULL << 21,

	/* blocks for new airports */
	TERM7_block              = 1ULL << 22, ///< Block belonging to terminal 7.
	TERM8_block              = 1ULL << 23, ///< Block belonging to terminal 8.
	HELIPAD3_block           = 1ULL << 24, ///< Block belonging to helipad 3.
	HANGAR1_AREA_block       = 1ULL << 26,
	OUT_WAY2_block           = 1ULL << 27,
	IN_WAY2_block            = 1ULL << 28,
	RUNWAY_IN2_block         = 1ULL << 29,
	RUNWAY_OUT2_block        = 1ULL << 10, ///< @note re-uses #TAXIWAY_BUSY_block
	HELIPAD_GROUP_block      = 1ULL << 13, ///< @note re-uses #AIRPORT_ENTRANCE_block
	OUT_WAY_block2           = 1ULL << 31,
	NEW_block                = 1ULL << 32,
	NEW2_block               = 1ULL << 33,
	NEW3_block               = 1ULL << 34,
	NEW4_block               = 1ULL << 35,
	NEW5_block               = 1ULL << 36,
	NEW6_block               = 1ULL << 37,
	NEW7_block               = 1ULL << 38,
	NEW8_block               = 1ULL << 39,
	NEW9_block               = 1ULL << 40,
	NEW10_block              = 1ULL << 41,
	NEW11_block              = 1ULL << 42,
	NEW12_block              = 1ULL << 43,
	NEW13_block              = 1ULL << 44,
	NEW14_block              = 1ULL << 45,
	NEW15_block              = 1ULL << 46,
	NEW16_block              = 1ULL << 47,
	NEW17_block              = 1ULL << 48,
	NEW18_block              = 1ULL << 49,
	NEW19_block              = 1ULL << 50,
	NEW20_block              = 1ULL << 51,
	TERM9_block              = 1ULL << 52,
	TERM10_block             = 1ULL << 53,
	TERM11_block             = 1ULL << 54,
	TERM12_block             = 1ULL << 55,
	TERM13_block             = 1ULL << 56,
	TERM14_block             = 1ULL << 57,
	TERM15_block             = 1ULL << 58,
	TERM16_block             = 1ULL << 59,
	TERM17_block             = 1ULL << 60,
	TERM18_block             = 1ULL << 61,
	TERM19_block             = 1ULL << 62,
	TERM20_block             = 1ULL << 63,
	/* end of new blocks */

	NOTHING_block            = 1ULL << 30,
	CIRCLE_block             = 1ULL << 30, ///< @note re-uses #NOTHING_block. Uses in block2 on circle airport(s) as condition of counter st->num_circle
	AIRPORT_CLOSED_block     = 1ULL << 63; ///< Dummy block for indicating a closed airport.

/** A single location on an airport where aircraft can move to. */
struct AirportMovingData {
	int16 x;             ///< x-coordinate of the destination.
	int16 y;             ///< y-coordinate of the destination.
	uint16 flag;         ///< special flags when moving towards the destination.
	Direction direction; ///< Direction to turn the aircraft after reaching the destination.
};

/**
 * Combination of aircraft state for going to a certain terminal and the
 * airport flag for that terminal block.
 */
struct AirportMovementTerminalMapping {
	AirportMovementStates state; ///< Aircraft movement state when going to this terminal.
	uint64 airport_flag;         ///< Bitmask in the airport flags that need to be free for this terminal.
};


#define AIRPORT_TERMINAL_MAPPING_LENGTH 23
extern const AirportMovementTerminalMapping _airport_terminal_mapping[];

AirportMovingData RotateAirportMovingData(const AirportMovingData *orig, Direction rotation, uint num_tiles_x, uint num_tiles_y);

struct AirportFTAbuildup;

/** Finite sTate mAchine (FTA) of an airport. */
struct AirportFTAClass {
public:
	/** Bitmask of airport flags. */
	enum Flags {
		AIRPLANES   = 0x1,                     ///< Can planes land on this airport type?
		HELICOPTERS = 0x2,                     ///< Can helicopters land on this airport type?
		ALL         = AIRPLANES | HELICOPTERS, ///< Mask to check for both planes and helicopters.
		SHORT_STRIP = 0x4,                     ///< This airport has a short landing strip, dangerous for fast aircraft.
	};

	AirportFTAClass(
		const AirportMovingData *moving_data,
		const byte *terminals,
		const byte num_helipads,
		const byte *entry_points,
		Flags flags,
		const AirportFTAbuildup *apFA,
		byte delta_z
	);

	~AirportFTAClass();

	/**
	 * Get movement data at a position.
	 * @param position Element number to get movement data about.
	 * @return Pointer to the movement data.
	 */
	const AirportMovingData *MovingData(byte position) const
	{
		assert(position < nofelements);
		return &moving_data[position];
	}

	const AirportMovingData *moving_data; ///< Movement data.
	struct AirportFTA *layout;            ///< state machine for airport
	const byte *terminals;                ///< %Array with the number of terminal groups, followed by the number of terminals in each group.
	const byte num_helipads;              ///< Number of helipads on this airport. When 0 helicopters will go to normal terminals.
	Flags flags;                          ///< Flags for this airport type.
	byte nofelements;                     ///< number of positions the airport consists of
	const byte *entry_points;             ///< when an airplane arrives at this airport, enter it at position entry_point, index depends on direction
	byte delta_z;                         ///< Z adjustment for helicopter pads
};

DECLARE_ENUM_AS_BIT_SET(AirportFTAClass::Flags)


/** Internal structure used in openttd - Finite sTate mAchine --> FTA */
struct AirportFTA {
	AirportFTA *next;        ///< possible extra movement choices from this position
	uint64 block;            ///< 64 bit blocks (st->airport.flags), should be enough for the most complex airports
	uint64 block2;           ///< additional 64 bit blocks for everytile-block airports 8*8 up to 11*11 every-tile
	byte position;           ///< the position that an airplane is at
	byte next_position;      ///< next position from this position
	byte heading;            ///< heading (current orders), guiding an airplane to its target on an airport
};

const AirportFTAClass *GetAirport(const byte airport_type);
byte GetVehiclePosOnBuild(TileIndex hangar_tile);

#endif /* AIRPORT_H */
