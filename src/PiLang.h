#ifndef PI_LANGUAGE
    #define PI_LANGUAGE en
#endif

#define PiLang PiLanguages::PI_LANGUAGE

#ifdef PI_LANG_ONCE
    #define PL(a,b) const char* a = b
#else
    #define PL(a,b) extern const char* a
#endif

/* PL(hi_there,"Hi, there!");
 * 
 * can be picked up as a translated
 * string by using the following:
 * 
 * PiLang::hi_there
 */
namespace PiLanguages {
    namespace en {
        // General
        PL(SUGGESTED_RESPONSES,
                "Suggested responses:");
        PL(ITEM,
                "Item");
        PL(SHIP,
                "Ship");
        PL(PRICE,
                "Price");
        PL(BUY,
                "Buy");
        PL(SELL,
                "Sell");
        PL(STOCK,
                "Stock");
        PL(CARGO,
                "Cargo");
        PL(VID_LINK_DOWN,
                "Video link down");
        PL(VID_LINK_ESTABLISHED,
                "Video link established");
        PL(VID_CONNECTING,
                "Connecting...");
        PL(BOUGHT_1T_OF,
                "You have bought 1t of %s.");
        PL(SOLD_1T_OF,
                "You have sold 1t of %s.");
        PL(WELCOME_TO_MARKET,
                "Welcome to %s commodities market");
        PL(GO_BACK,
                "Go back");
        PL(FITTING,
                "Fitting ");  // Preserve trailing space
        PL(REMOVING,
                "Removing "); // Preserve trailing space
        PL(FIT_TO_WHICH_MOUNT,
                "Fit laser to which gun mount?");
        PL(REMOVE_FROM_WHICH_MOUNT,
                "Remove laser from which gun mount?");
        PL(YOU_NOT_ENOUGH_MONEY,
                "You do not have enough money");
        PL(TRADER_NOT_ENOUGH_MONEY,
                "Trader does not have enough money");
        PL(NO_SPACE_ON_SHIP,
                "There is no space on your ship");
        PL(SOMEWHERE_SERVICES,
                "%s services");
        PL(SOMEWHERE_SHIPYARD,
                "%s Shipyard");
        PL(PRICE_TO_FIT,
                "$ to fit");
        PL(PRICE_TO_REMOVE,
                "$ for removal");
        PL(WT,
                "Wt");
        PL(FIT,
                "Fit");
        PL(REMOVE,
                "Remove");
        PL(BUY_THIS_SHIP,
                "Buy this ship");
        PL(SHIP_TYPE,
                "Ship type");
        PL(REGISTRATION_ID,
                "Registration id");
        PL(WEIGHT_EMPTY,
                "Weight empty");
        PL(NUMBER_TONNES,
                "%dt");
        PL(WEIGHT_FULLY_LADEN,
                "Weight fully loaded");
        PL(CAPACITY,
                "Capacity");
        PL(FORWARD_ACCEL_EMPTY,
                "Forward accel (empty)");
        PL(NUMBER_G,
                "%.1f G");
        PL(FORWARD_ACCEL_LADEN,
                "Forward accel (laden)");
        PL(REVERSE_ACCEL_EMPTY,
                "Reverse accel (empty)");
        PL(REVERSE_ACCEL_LADEN,
                "Reverse accel (laden)");
        PL(HYPERDRIVE_FITTED,
                "Hyperdrive fitted:");
        PL(HYPERSPACE_RANGE_LADEN,
                "Hyperspace range (fully laden):");
        PL(CLASS_NUMBER,
                "Class %d");
        PL(NUMBER_LY,
                "%.2f ly");
        PL(SHIP_IS_ALREADY_FULLY_REPAIRED,
                "Your ship is in perfect working condition.");
        PL(REPAIR_1_PERCENT_HULL,
                "Repair 1.0% of hull damage");
        PL(REPAIR_ENTIRE_HULL,
                "Repair all hull damage (%.1f%%)");
        PL(REPAIR,
                "Repair");
        PL(PART_EX,
                "Part exchange");
        PL(VIEW,
                "View");
        PL(SHIP_EQUIPMENT,
                "Ship equipment");
        PL(REPAIRS_AND_SERVICING,
                "Repairs and servicing");
        PL(NEW_AND_RECONDITIONED_SHIPS,
                "New and reconditioned ships");
        PL(BULLETIN_BOARD,
                "Bulletin Board");
        PL(WELCOME_TO_SOMEWHERE,
                "Welcome to %s");
        PL(SPACESTATION_LONG_WELCOME_MESSAGE,
                "Hello, traveller.  Welcome to this space station.  We have reports of vandalism and graffiti on board.  If you see that any of our signage is misleading, mis-spelled or just missing, please inform a member of staff.\n\nOxygen is currently free of charge.");
        PL(REQUEST_LAUNCH,
                "Request Launch");
        PL(SHIPYARD,
                "Shipyard");
        PL(COMMODITIES_MARKET,
                "Commodities market");
        PL(CONTACT_LOCAL_POLICE,
                "Contact local police");
        PL(COMMS_LINK,
                "Comms link");
        PL(ZOOM_IN,
                "Zoom in");
        PL(ZOOM_OUT,
                "Zoom out");
        PL(NORMA_ARM,
                "Norma arm");
        PL(PERSEUS_ARM,
                "Perseus arm");
        PL(OUTER_ARM,
                "Outer arm");
        PL(SAGITTARIUS_ARM,
                "Sagittarius arm");
        PL(SCUTUM_CENTAURUS_ARM,
                "Scutum-Centaurus arm");
        PL(INT_LY,
                "%d ly");

        // Config / game control
        PL(PRESS_BUTTON_WANTED_FOR,
                "Press the button you want for "); // Preserve trailing space
        PL(MOVE_AXIS_WANTED_FOR,
                "Move the joystick axis you want for "); // Preserve trailing space
        PL(SAVE,
                "Save");
        PL(LOAD,
                "Load");
        PL(CANCEL,
                "Cancel");
        PL(SELECT_FILENAME_TO_SAVE,
                "Select a file to save to or enter a new filename");
        PL(GAME_SAVED_TO,
                "Game saved to "); // Preserve trailing space
        PL(SELECT_FILENAME_TO_LOAD,
                "Select a file to load");
        PL(COULD_NOT_OPEN_FILENAME,
                "Could not open %s");
        PL(GAME_LOAD_CORRUPT,
                "This saved game cannot be loaded because it contains errors.");
        PL(GAME_LOAD_CANNOT_OPEN,
                "This saved game file could not be opened due to permissions or something...");
        PL(LOW,
                "Low");
        PL(MEDIUM,
                "Medium");
        PL(HIGH,
                "High");
        PL(VERY_HIGH,
                "Very high");
        PL(VERY_VERY_HIGH,
                "Very very high");
        PL(SIGHTS_SOUNDS_SAVES,
                "Sights, sounds & saving games");
        PL(PIONEER,
                "PIONEER");
        PL(SAVE_THE_GAME,
                "[S] Save the game");
        PL(LOAD_A_GAME,
                "[L] Load a game");
        PL(EXIT_THIS_GAME,
                "Exit this game");
        PL(WINDOW_OR_FULLSCREEN,
                "Windowed or fullscreen (restart to apply)");
        PL(FULL_SCREEN,
                "Full screen");
        PL(OTHER_GRAPHICS_SETTINGS,
                "Other graphics settings");
        PL(USE_SHADERS,
                "Use shaders");
        PL(USE_HDR,
                "Use HDR Lighting (looks cool)");
        PL(SOUND_SETTINGS,
                "Sound settings");
        PL(VOL_MASTER,
                "Master:");
        PL(VOL_EFFECTS,
                "Effects:");
        PL(VOL_MUSIC,
                "Music:");
        PL(VIDEO_RESOLUTION,
                "Video resolution (restart game to apply)");
        PL(X_BY_X,
                "%dx%d");
        PL(PLANET_DETAIL_LEVEL,
                "Planet detail level:");
        PL(CITY_DETAIL_LEVEL,
                "City detail level:");
        PL(CONTROLS,
                "Controls");
        PL(ENABLE_JOYSTICK,
                "Enable joystick control");
        PL(MOUSE_INPUT,
                "Mouse Input");
        PL(INVERT_MOUSE_Y,
                "Invert MouseY");
 
        // Wares
        PL(NONE,
                "None");
        PL(HYDROGEN,
                "Hydrogen");
        PL(HYDROGEN_DESCRIPTION,
                "Hydrogen is primarily used as a fusion fuel");
        PL(LIQUID_OXYGEN,
                "Liquid Oxygen");
        PL(LIQUID_OXYGEN_DESCRIPTION,
                "Oxygen is required for life support systems and some industrial processes");
        PL(METAL_ORE,
                "Metal ore");
        PL(CARBON_ORE,
                "Carbon ore");
        PL(CARBON_ORE_DESCRIPTION,
                "Carbon ores (coal and oil) are required for the synthesis of many useful chemicals, including plastics, synthetic foodstuffs, medicines and textiles");
        PL(METAL_ALLOYS,
                "Metal alloys");
        PL(PLASTICS,
                "Plastics");
        PL(FRUIT_AND_VEG,
                "Fruit and Veg");
        PL(ANIMAL_MEAT,
                "Animal Meat");
        PL(LIVE_ANIMALS,
                "Live Animals");
        PL(LIQUOR,
                "Liquor");
        PL(GRAIN,
                "Grain");
        PL(TEXTILES,
                "Textiles");
        PL(FERTILIZER,
                "Fertilizer");
        PL(WATER,
                "Water");
        PL(MEDICINES,
                "Medicines");
        PL(CONSUMER_GOODS,
                "Consumer goods");
        PL(COMPUTERS,
                "Computers");
        PL(ROBOTS,
                "Robots");
        PL(PRECIOUS_METALS,
                "Precious metals");
        PL(INDUSTRIAL_MACHINERY,
                "Industrial machinery");
        PL(FARM_MACHINERY,
                "Farm machinery");
        PL(MINING_MACHINERY,
                "Mining machinery");
        PL(AIR_PROCESSORS,
                "Air processors");
        PL(SLAVES,
                "Slaves");
        PL(HAND_WEAPONS,
                "Hand weapons");
        PL(BATTLE_WEAPONS,
                "Battle weapons");
        PL(NERVE_GAS,
                "Nerve Gas");
        PL(NARCOTICS,
                "Narcotics");
        PL(MILITARY_FUEL,
                "Military fuel");
        PL(RUBBISH,
                "Rubbish");
        PL(RADIOACTIVES,
                "Radioactive waste");
 
        // Hardware
        PL(MISSILE_UNGUIDED,
                "R40 Unguided Rocket");
        PL(MISSILE_GUIDED,
                "Guided Missile");                                                     
        PL(MISSILE_SMART,
                "Smart Missile");                                                   
        PL(MISSILE_NAVAL,
                "Naval Missile");
        PL(ATMOSPHERIC_SHIELDING,
                "Atmospheric Shielding");
        PL(ATMOSPHERIC_SHIELDING_DESCRIPTION,
                "Shields your spaceship from the heat of atmospheric re-entry.");
        PL(ECM_BASIC,
                "ECM system");
        PL(ECM_BASIC_DESCRIPTION,
                "An electronic countermeasure missile defence system, capable of destroying some homing missiles.");
        PL(SCANNER,
                "Scanner");
        PL(SCANNER_DESCRIPTION,
                "Provides a 3D map of nearby ships.");
        PL(ECM_ADVANCED,
                "Advanced ECM system");
        PL(ECM_ADVANCED_DESCRIPTION,
                "An electronic countermeasure missile defence system, capable of destroying more advanced types of homing missiles.");
        PL(SHIELD_GENERATOR,
                "Shield Generator");
        PL(SHIELD_GENERATOR_DESCRIPTION,
                "Provides additional hull defences with each unit fitted.");
        PL(LASER_COOLING_BOOSTER,
                "Laser Cooling Booster");
        PL(LASER_COOLING_BOOSTER_DESCRIPTION,
                "An improved cooling system for your weapons.");
        PL(CARGO_LIFE_SUPPORT,
                "Cargo Bay Life Support");
        PL(CARGO_LIFE_SUPPORT_DESCRIPTION,
                "Allows the transport of live cargo.");
        PL(AUTOPILOT,
                "Autopilot");
        PL(AUTOPILOT_DESCRIPTION,
                "An on-board flight computer.");
        PL(RADAR_MAPPER,
                "Radar Mapper");
        PL(RADAR_MAPPER_DESCRIPTION,
                "Used to remotely inspect the equipment, cargo and state of other ships.");
        PL(FUEL_SCOOP,
                "Fuel Scoop");
        PL(FUEL_SCOOP_DESCRIPTION,
                "Permits scooping hydrogen fuel from gas giant planets.");
        PL(HYPERCLOUD_ANALYZER,
                "Hypercloud Analyzer");
        PL(HYPERCLOUD_ANALYZER_DESCRIPTION,
                "Analyze hyperspace clouds to determine destination and time of arrival or departure.");
        PL(HULL_AUTOREPAIR,
                "Hull Auto-Repair System");
        PL(HULL_AUTOREPAIR_DESCRIPTION,
                "Automatically repairs the ship's hull in the event of damage.");
        PL(SHIELD_ENERGY_BOOSTER,
                "Shield Energy Booster");
        PL(SHIELD_ENERGY_BOOSTER_DESCRIPTION,
                "Increases the rate at which shields recharge.");
        PL(DRIVE_CLASS1,
                "Class 1 Hyperdrive");
        PL(DRIVE_CLASS2,
                "Class 2 Hyperdrive");
        PL(DRIVE_CLASS3,
                "Class 3 Hyperdrive");
        PL(DRIVE_CLASS4,
                "Class 4 Hyperdrive");
        PL(DRIVE_CLASS5,
                "Class 5 Hyperdrive");
        PL(DRIVE_CLASS6,
                "Class 6 Hyperdrive");
        PL(DRIVE_CLASS7,
                "Class 7 Hyperdrive");
        PL(DRIVE_CLASS8,
                "Class 8 Hyperdrive");
        PL(DRIVE_CLASS9,
                "Class 9 Hyperdrive");
        PL(DRIVE_MIL1,
                "Class 1 Military drive");
        PL(DRIVE_MIL2,
                "Class 2 Military drive");
        PL(DRIVE_MIL3,
                "Class 3 Military drive");
        PL(DRIVE_MIL4,
                "Class 4 Military drive");
        PL(PULSECANNON_1MW,
                "1MW pulse cannon");
        PL(PULSECANNON_DUAL_1MW,
                "1MW dual-fire pulse cannon");
        PL(PULSECANNON_2MW,
                "2MW pulse cannon");
        PL(PULSECANNON_RAPID_2MW,
                "2MW rapid-fire pulse cannon");
        PL(PULSECANNON_4MW,
                "4MW pulse cannon");
        PL(PULSECANNON_10MW,
                "10MW pulse cannon");
        PL(PULSECANNON_20MW,
                "20MW pulse cannon");
        PL(MININGCANNON_17MW,
                "17MW blast-mining cannon");
        PL(MININGCANNON_17MW_DESCRIPTION,
                "Used to blast-mine mineral rich asteroids.");
        PL(SMALL_PLASMA_ACCEL,
                "Small plasma accelerator");
        PL(LARGE_PLASMA_ACCEL,
                "Large plasma accelerator");
        PL(CLEAN,
                "Clean");
        PL(HYPERSPACE_ARRIVAL_CLOUD,
                "Hyperspace arrival cloud");
        PL(HYPERSPACE_DEPARTURE_CLOUD,
                "Hyperspace departure cloud");
        PL(TYPE,
                "Type");
        PL(CLIENT,
                "Client");
        PL(LOCATION,
                "Location");
        PL(DUE,
                "Due");
        PL(REWARD,
                "Reward");
        PL(STATUS,
                "Status");
        PL(CARGO_INVENTORY,
                "Cargo Inventory:");
        PL(JETTISON,
                "Jettison");
        PL(JETTISONED,
                "Jettisoned 1 tonne of "); // preserve trailing space
        PL(COMBAT_RATING,
                "COMBAT RATING:");
        PL(CRIMINAL_RECORD,
                "CRIMINAL RECORD:");
        PL(SHIP_INFORMATION_HEADER,
                "SHIP INFORMATION:  "); // preserve trailing space
        PL(HYPERDRIVE,
                "Hyperdrive");
        PL(FREE,
                "Free");
        PL(USED,
                "Used");
        PL(TOTAL_WEIGHT,
                "All-up weight");
        PL(FRONT_WEAPON,
                "Front weapon");
        PL(REAR_WEAPON,
                "Rear weapon");
        PL(HYPERSPACE_RANGE,
                "Hyperspace range");
        PL(NO_MOUNTING,
                "no mounting");
        PL(SHIP_INFORMATION,
                "Ship information");
        PL(REPUTATION,
                "Reputation");
        PL(MISSIONS,
                "Missions");
        PL(SHIFT,
                "shift "); // preserve trailing space
        PL(CTRL,
                "ctrl "); // preserve trailing space
        PL(ALT,
                "alt "); // preserve trailing space
        PL(META,
                "meta "); // preserve trailing space
        PL(JOY,
                "Joy");
        PL(BUTTON,
                " Button "); // preserve leading and trailing space
        PL(HAT,
                " Hat"); // preserve leading space
        PL(DIRECTION,
                " Dir "); // preserve leading and trailing space
        PL(X,
                "X");
        PL(Y,
                "Y");
        PL(Z,
                "Z");
        PL(AXIS,
                " Axis"); // preserve leading space
        PL(WEAPONS,
                "Weapons");
        PL(TARGET_OBJECT_IN_SIGHTS,
                "Target object in cross-hairs");
        PL(FIRE_LASER,
                "Fire laser");
        PL(SHIP_ORIENTATION,
                "Ship orientation");
        PL(FAST_ROTATION_CONTROL,
                "Fast rotational control");
        PL(PITCH_UP,
                "Pitch up");
        PL(PITCH_DOWN,
                "Pitch down");
        PL(YAW_LEFT,
                "Yaw left");
        PL(YAW_RIGHT,
                "Yaw right");
        PL(ROLL_LEFT,
                "Roll left");
        PL(ROLL_RIGHT,
                "Roll right");
        PL(MANUAL_CONTROL_MODE,
                "Manual control mode");
        PL(THRUSTER_MAIN,
                "Thrust forward");
        PL(THRUSTER_RETRO,
                "Thrust backwards");
        PL(THRUSTER_VENTRAL,
                "Thrust up");
        PL(THRUSTER_DORSAL,
                "Thrust down");
        PL(THRUSTER_PORT,
                "Thrust left");
        PL(THRUSTER_STARBOARD,
                "Thrust right");
        PL(SPEED_CONTROL_MODE,
                "Speed control mode");
        PL(INCREASE_SET_SPEED,
                "Increase set speed");
        PL(DECREASE_SET_SPEED,
                "Decrease set speed");
        PL(JOYSTICK_INPUT,
                "Joystick input");
        PL(PITCH,
                "Pitch");
        PL(ROLL,
                "Roll");
        PL(YAW,
                "Yaw");
        PL(MISSILE,
                "missile");
        PL(HARMLESS,
                "Harmless");
        PL(MOSTLY_HARMLESS,
                "Mostly harmless");
        PL(POOR,
                "Poor");
        PL(AVERAGE,
                "Average");
        PL(ABOVE_AVERAGE ,
                "Above Average");
        PL(COMPETENT,
                "Competent");
        PL(DANGEROUS,
                "Dangerous");
        PL(DEADLY,
                "Deadly");
        PL(ELITE,
                "ELITE");
        PL(SIMULATING_UNIVERSE_EVOLUTION_N_BYEARS,
                "Simulating evolution of the universe: %.1f billion years ;-)");
        PL(TOMBSTONE_EPITAPH,
                "RIP OLD BEAN");
        PL(MM_START_NEW_GAME_EARTH,
                "New game starting on Earth");
        PL(MM_START_NEW_GAME_E_ERIDANI,
                "New game starting on Epsilon Eridani");
        PL(MM_START_NEW_GAME_DEBUG,
                "New game starting on debug point");
        PL(MM_LOAD_SAVED_GAME,
                "Load a saved game");
        PL(MM_QUIT,
                "Quit");
        PL(SCREENSHOT_FILENAME_TEMPLATE,
                "screenshot%08d.png");
        PL(PIONEERING_PILOTS_GUILD,
                "Pioneering Pilot's Guild");
        PL(RIGHT_ON_COMMANDER,
                "Well done commander! Your combat rating has improved!");
        PL(ALERT_CANCELLED,
                "Alert cancelled.");
        PL(SHIP_DETECTED_NEARBY,
                "Ship detected nearby.");
        PL(DOWNGRADING_ALERT_STATUS,
                "No fire detected for 60 seconds, downgrading alert status.");
        PL(LASER_FIRE_DETECTED,
                "Laser fire detected.");
        PL(SOMEWHERE_POLICE,
                "%s Police");
        PL(WE_HAVE_NO_BUSINESS_WITH_YOU,
                "We have no business with you at the moment.");
        PL(YOU_MUST_PAY_FINE_OF_N_CREDITS,
                "We do not tolerate crime. You must pay a fine of %s.");
        PL(PAY_THE_FINE_NOW,
                "Pay the fine now.");
        PL(HANG_UP,
                "Hang up.");
        PL(TRADING_ILLEGAL_GOODS,
                "Trading illegal goods");
        PL(UNLAWFUL_WEAPONS_DISCHARGE,
                "Unlawful weapons discharge");
        PL(PIRACY,
                "Piracy");
        PL(MURDER,
                "Murder");
        PL(INDEPENDENT,
                "Independent");
        PL(EARTH_FEDERATION,
                "Earth Federation");
        PL(INDEPENDENT_CONFEDERATION,
                "Confederation of Independent Systems");
        PL(EMPIRE,
                "The Empire");
        PL(NO_ESTABLISHED_ORDER,
                "No established order");
        PL(HARD_CAPITALIST,
                "Entirely Capitalist - no government welfare provision");
        PL(CAPITALIST,
                "Capitalist");
        PL(MIXED_ECONOMY,
                "Mixed economy");
        PL(PLANNED_ECONOMY,
                "Centrally planned economy");
        PL(NO_CENTRAL_GOVERNANCE,
                "No central governance");
        PL(EARTH_FEDERATION_COLONIAL_RULE,
                "Earth Federation Colonial Rule");
        PL(EARTH_FEDERATION_DEMOCRACY,
                "Earth Federation Democracy");
        PL(IMPERIAL_RULE,
                "Imperial Rule");
        PL(LIBERAL_DEMOCRACY,
                "Liberal democracy");
        PL(SOCIAL_DEMOCRACY,
                "Social democracy");
        PL(CORPORATE_SYSTEM,
                "Corporate system");
        PL(MILITARY_DICTATORSHIP,
                "Military dictatorship");
        PL(COMMUNIST,
                "Communist");
        PL(PLUTOCRATIC_DICTATORSHIP,
                "Plutocratic dictatorship");
        PL(VIOLENT_ANARCHY,
                "Disorder - Overall governance contested by armed factions");
        PL(X_CANNOT_BE_TOLERATED_HERE,
                "%s cannot be tolerated here.");
        PL(SECTOR_X_Y,
                "Sector: %d,%d");
        PL(DISTANCE_FUEL_TIME,
                "Dist. %.2f light years (fuel required: %dt | time loss: %.1fhrs)");
        PL(CURRENT_SYSTEM,
                "Current system");
        PL(DISTANCE_FUEL_REQUIRED,
                "Dist. %.2f light years (insufficient fuel, required: %dt)");
        PL(DISTANCE_OUT_OF_RANGE,
                "Dist. %.2f light years (out of range)");
        PL(CANNOT_HYPERJUMP_WITHOUT_WORKING_DRIVE,
                "You cannot perform a hyperjump because you do not have a functioning hyperdrive");
        PL(QUADRUPLE_SYSTEM,
                "Quadruple system. "); // preserve trailing space
        PL(TRIPLE_SYSTEM,
                "Triple system. "); // preserve trailing space
        PL(BINARY_SYSTEM,
                "Binary system. "); // preserve trailing space
        PL(FUEL_SCOOP_ACTIVE_N_TONNES_H_COLLECTED,
                "Fuel scoop active. You now have %d tonnes of hydrogen.");
        PL(CARGO_BAY_LIFE_SUPPORT_LOST,
                "Sensors report critical cargo bay life-support conditions.");
        PL(NO_FREE_SPACE_FOR_ITEM,
                "You have no free space for this item.");
        PL(SHIP_IS_FULLY_LADEN,
                "Your ship is fully laden.");
        PL(YOU_DO_NOT_HAVE_ANY_X,
                "You do not have any %s.");
        PL(REAR_VIEW,
                "Rear view");
        PL(EXTERNAL_VIEW,
                "External view");
        PL(NAVIGATION_STAR_MAPS,
                "Navigation and star maps");
        PL(COMMS,
                "Comms");
        PL(GALAXY_SECTOR_VIEW,
                "Galaxy sector view");
        PL(SYSTEM_ORBIT_VIEW,
                "System orbit view");
        PL(STAR_SYSTEM_INFORMATION,
                "Star system information");
        PL(GALACTIC_VIEW,
                "Galactic view");
        PL(NO_ALERT,
                "No alert");
        PL(SHIP_NEARBY,
                "Ship nearby");
        PL(FIRE_DETECTED,
                "Fire detected");
        PL(DOCKING_CLEARANCE_EXPIRED,
                "Docking clearance expired. If you wish to dock you must repeat your request.");
        PL(MESSAGE_FROM_X,
                "Message from %s:");
        PL(SELECT_A_TARGET,
                "Select a target");
        PL(FRONT,
                "Front");
        PL(REAR,
                "Rear");
        PL(POLICE_SHIP_REGISTRATION,
                "POLICE");
        PL(CLEARANCE_ALREADY_GRANTED_BAY_N,
                "Clearance already granted. Proceed to docking bay %d.");
        PL(CLEARANCE_GRANTED_BAY_N,
                "Clearance granted. Proceed to docking bay %d.");
        PL(CLEARANCE_DENIED_NO_BAYS,
                "Clearance denied. There are no free docking bays.");
        PL(ITEM_IS_OUT_OF_STOCK,
                "This item is out of stock.");
        PL(BROWN_DWARF,
                "Brown dwarf sub-stellar object");
        PL(WHITE_DWARF,
                "White dwarf stellar remnant");
        PL(STAR_M,
                "Type 'M' red star");
        PL(STAR_K,
                "Type 'K' orange star");
        PL(STAR_G,
                "Type 'G' yellow star");
        PL(STAR_F,
                "Type 'F' white star");
        PL(STAR_A,
                "Type 'A' hot white star");
        PL(STAR_B,
                "Bright type 'B' blue star");
        PL(STAR_O,
                "Hot, massive type 'O' star");
        PL(STAR_M_GIANT,
                "Red giant star");
        PL(STAR_K_GIANT,
                "Orange giant star - Unstable");
        PL(STAR_G_GIANT,
                "Yellow giant star - Unstable");
        PL(STAR_AF_GIANT,
                "White giant star");
        PL(STAR_B_GIANT,
                "Blue giant star");
        PL(STAR_O_GIANT,
                "Hot Blue giant star");
        PL(STAR_M_SUPER_GIANT,
                "Red super giant star");
        PL(STAR_K_SUPER_GIANT,
                "Orange super giant star");
        PL(STAR_G_SUPER_GIANT,
                "Yellow super giant star");
        PL(STAR_AF_SUPER_GIANT,
                "White super giant star");
        PL(STAR_B_SUPER_GIANT,
                "Blue super giant star");
        PL(STAR_O_SUPER_GIANT,
                "Hot Blue super giant star");
        PL(STAR_M_HYPER_GIANT,
                "Red hyper giant star");
        PL(STAR_K_HYPER_GIANT,
                "Orange hyper giant star - Unstable");
        PL(STAR_G_HYPER_GIANT,
                "Yellow hyper giant star - Unstable");
        PL(STAR_AF_HYPER_GIANT,
                "White hyper giant star");
        PL(STAR_B_HYPER_GIANT,
                "Blue hyper giant star");
        PL(STAR_O_HYPER_GIANT,
                "Hot Blue hyper giant star");
        PL(STAR_M_WF,
                "Wolf-Rayet star - Unstable");
        PL(STAR_B_WF,
                "Wolf-Rayet star - Risk of collapse");
        PL(STAR_O_WF,
                "Wolf-Rayet star - Imminent collapse");
        PL(STAR_S_BH,
                "A stellar black hole");
        PL(STAR_IM_BH,
                "An intermediate-mass black hole");
        PL(STAR_SM_BH,
                "Our galactic anchor");
        PL(VERY_LARGE_GAS_GIANT,
                "Very large gas giant");
        PL(LARGE_GAS_GIANT,
                "Large gas giant");
        PL(MEDIUM_GAS_GIANT,
                "Medium gas giant");
        PL(SMALL_GAS_GIANT,
                "Small gas giant");
        PL(ASTEROID,
                "Asteroid");
        PL(MASSIVE,
                "Massive");
        PL(LARGE,
                "Large");
        PL(TINY,
                "Tiny");
        PL(SMALL,
                "Small");
        PL(COMMA_HIGHLY_VOLCANIC,
                ", highly volcanic");
        PL(HIGHLY_VOLCANIC,
                "Highly volcanic");
        PL(ICE_WORLD,
                " ice world"); // preserve leading space
        PL(ROCKY_PLANET,
                " rocky planet"); // preserve leading space
        PL(OCEANICWORLD,
                " oceanic world"); // preserve leading space
        PL(PLANET_CONTAINING_LIQUID_WATER,
                " planet containing liquid water"); // preserve leading space
        PL(PLANET_WITH_SOME_ICE,
                " planet with some ice"); // preserve leading space
        PL(ROCKY_PLANET_CONTAINING_COME_LIQUIDS,
                " rocky planet containing some liquids,"); // preserve leading space
        PL(WITH_NO_SIGNIFICANT_ATMOSPHERE,
                " with no significant atmosphere"); // preserve leading space
        PL(TENUOUS,
                "tenuous");
        PL(THIN,
                "thin");
        PL(THICK,
                "thick");
        PL(VERY_DENSE,
                "very dense");
        PL(WITH_A,
                " with a "); // preserve leading and trailing space
        PL(O2_ATMOSPHERE,
                " Oxygen atmosphere"); // preserve leading space
        PL(CO2_ATMOSPHERE,
                " Carbon Dioxide atmosphere"); // preserve leading space
        PL(CO_ATMOSPHERE,
                " Carbon Monoxide atmosphere"); // preserve leading space
        PL(CH4_ATMOSPHERE,
                " Methane atmosphere"); // preserve leading space
        PL(H_ATMOSPHERE,
                " Hydrogen atmosphere"); // preserve leading space
        PL(HE_ATMOSPHERE,
                " Helium atmosphere"); // preserve leading space
        PL(AR_ATMOSPHERE,
                " Argon atmosphere"); // preserve leading space
        PL(S_ATMOSPHERE,
                " Sulfuric atmosphere"); // preserve leading space
        PL(N_ATMOSPHERE,
                " Nitrogen atmosphere"); // preserve leading space
        PL(AND_HIGHLY_COMPLEX_ECOSYSTEM,
                " and a highly complex ecosystem."); // preserve leading space
        PL(AND_INDIGENOUS_PLANT_LIFE,
                " and indigenous plant life."); // preserve leading space
        PL(AND_INDIGENOUS_MICROBIAL_LIFE,
                " and indigenous microbial life."); // preserve leading space
        PL(ORBITAL_STARPORT,
                "Orbital starport");
        PL(STARPORT,
                "Starport");
        PL(UNKNOWN,
                "<unknown>");
        PL(UNEXPLORED_SYSTEM_NO_DATA,
                "Unexplored system. No more data available.");
        PL(SMALL_SCALE_PROSPECTING_NO_SETTLEMENTS,
                "Small-scale prospecting. No registered settlements.");
        PL(SMALL_INDUSTRIAL_OUTPOST,
                "Small industrial outpost.");
        PL(SOME_ESTABLISHED_MINING,
                "Some established mining.");
        PL(YOUNG_FARMING_COLONY,
                "Young farming colony.");
        PL(INDUSTRIAL_COLONY,
                "Industrial colony.");
        PL(MINING_COLONY,
                "Mining colony.");
        PL(OUTDOOR_AGRICULTURAL_WORLD,
                "Outdoor agricultural world.");
        PL(HEAVY_INDUSTRY,
                "Heavy industry.");
        PL(EXTENSIVE_MINING,
                "Extensive mining operations.");
        PL(THRIVING_OUTDOOR_WORLD,
                "Thriving outdoor world.");
        PL(INDUSTRIAL_HUB_SYSTEM,
                "Industrial hub system.");
        PL(VAST_STRIP_MINE,
                "Vast strip-mining colony.");
        PL(HIGH_POPULATION_OUTDOOR_WORLD,
                "High population outdoor world.");
        PL(SOMEWHERE_SPACEPORT,
                " Spaceport"); // preserve leading space
        PL(SOMEWHERE_STARPORT,
                " Starport"); // preserve leading space
        PL(MASS,
                "Mass");
        PL(N_WHATEVER_MASSES,
                "%.3f %s masses");
        PL(SOLAR,
                "Solar");
        PL(EARTH,
                "Earth");
        PL(SURFACE_TEMPERATURE,
                "Surface temperature");
        PL(N_CELSIUS,
                "%d C");
        PL(N_YEARS,
                "%.1f years");
        PL(N_DAYS,
                "%.1f days");
        PL(ORBITAL_PERIOD,
                "Orbital period");
        PL(PERIAPSIS_DISTANCE,
                "Periapsis distance");
        PL(APOAPSIS_DISTANCE,
                "Apoapsis distance");
        PL(ECCENTRICITY,
                "Eccentricity");
        PL(AXIAL_TILE,
                "Axial tilt");
        PL(N_DEGREES,
                "%.1f degrees");
        PL(DAY_LENGTH,
                "Day length");
        PL(N_EARTH_DAYS,
                "%.1f earth days");
        PL(STARPORTS,
                "Starports");
        PL(MAJOR_IMPORTS,
                "Major Imports:");
        PL(MINOR_IMPORTS,
                "Minor Imports:");
        PL(MAJOR_EXPORTS,
                "Major Exports:");
        PL(MINOR_EXPORTS,
                "Minor Exports:");
        PL(ILLEGAL_GOODS,
                "Illegal Goods:");
        PL(UNEXPLORED_SYSTEM_STAR_INFO_ONLY,
                "Unexplored System. Star information has been gathered by remote telescope, but no planetary information is available.");
        PL(PLANETARY_INFO,
                "Planetary info");
        PL(ECONOMIC_INFO,
                "Economic info");
        PL(DEMOGRAPHICS,
                "Demographics");
        PL(STABLE_SYSTEM_WITH_N_MAJOR_MINOR_STARPORTS,
                "Stable system with %d major %s and %d starport%s.\n\n%s");
        PL(BODY,
                "body");
        PL(BODIES,
                "bodies");
        PL(PLURAL_SUFFIX,
                "s");
        PL(SYSTEM_TYPE,
                "System type:");
        PL(GOVERNMENT_TYPE,
                "Government type:");
        PL(ECONOMY_TYPE,
                "Economy type:");
        PL(ALLEGIANCE,
                "Allegiance:");
        PL(POPULATION,
                "Population:");
        PL(OVER_N_BILLION,
                "Over %d billion");
        PL(OVER_N_MILLION,
                "Over %d million");
        PL(A_FEW_THOUSAND,
                "Only a few thousand");
        PL(NO_REGISTERED_INHABITANTS,
                "No registered inhabitants");
        PL(SECTOR_COORDINATES,
                "Sector coordinates:");
        PL(SYSTEM_NUMBER,
                "System number:");
        PL(NAME,
                "Name");
        PL(ROTATIONAL_PERIOD,
                " (rotational period)"); // preserve leading space
        PL(RADIUS,
                "Radius");
        PL(SEMI_MAJOR_AXIS,
                "Semi-major axis");
        PL(TIME_POINT,
                "Time point: ");
        PL(UNEXPLORED_SYSTEM_NO_SYSTEM_VIEW,
                "Unexplored system. System view unavailable.");
        PL(WHEELS_ARE_UP,
                "Wheels are up");
        PL(WHEELS_ARE_DOWN,
                "Wheels are down");
        PL(OBJECT_LABELS_ARE_ON,
                "Object labels are on");
        PL(OBJECT_LABELS_ARE_OFF,
                "Object labels are off");
        PL(HYPERSPACE_JUMP,
                "Hyperspace Jump");
        PL(TAKEOFF,
                "Takeoff");
        PL(MANUAL_CONTROL,
                "Manual control");
        PL(COMPUTER_SPEED_CONTROL,
                "Computer speed control");
        PL(AUTOPILOT_ON,
                "Autopilot on");
        PL(SHIP_VELOCITY_BY_REFERENCE_OBJECT,
                "Ship velocity by reference object");
        PL(DISTANCE_FROM_SHIP_TO_NAV_TARGET,
                "Distance from ship to navigation target");
        PL(SHIP_ALTITUDE_ABOVE_TERRAIN,
                "Ship altitude above terrain");
        PL(EXTERNAL_ATMOSPHERIC_PRESSURE,
                "External atmospheric pressure");
        PL(HULL_TEMP,
                "Hull temp");
        PL(WEAPON_TEMP,
                "Weapon temp");
        PL(HULL_INTEGRITY,
                "Hull integrity");
        PL(SHIELD_INTEGRITY,
                "Shield integrity");
        PL(LAUNCH_PERMISSION_DENIED_BUSY,
                "Permission to launch denied: docking bay busy.");
        PL(HYPERSPACE_JUMP_ABORTED,
                "Hyperspace jump aborted.");
        PL(CAMERA,
                "camera");
        PL(LANDED,
                "Landed");
        PL(DOCKING,
                "Docking");
        PL(DOCKED,
                "Docked");
        PL(HYPERSPACE,
                "Hyperspace");
        PL(SET_SPEED_KM_S,
                "Set speed: %.2f km/s");
        PL(SET_SPEED_M_S,
                "Set speed: %.0f m/s");
        PL(KM_S_RELATIVE_TO,
                "%.2f km/s rel-to %s");
        PL(M_S_RELATIVE_TO,
                "%.0f m/s rel-to %s");
        PL(N_DISTANCE_TO_TARGET,
                "%s to target");
        PL(ALT_IN_METRES,
                "Alt: %.0fm");
        PL(PRESSURE_N_BAR,
                "P: %.2f bar");
        PL(NO_HYPERDRIVE,
                "No hyperdrive");
        PL(MASS_N_TONNES,
                "Mass: %dt");
        PL(SHIELD_STRENGTH_N,
                "Shield strength: %.2f");
        PL(CARGO_N,
                "Cargo: %dt");
        PL(HYPERSPACE_ARRIVAL_CLOUD_REMNANT,
                "Hyperspace arrival cloud remnant");
        PL(HYPERSPACE_X_CLOUD,
                "Hyperspace %s cloud");
        PL(SHIP_MASS_N_TONNES,
                "Ship mass: %dt");
        PL(DATE_DUE_N,
                "Date due: %s");
        PL(ARRIVAL,
                "arrival");
        PL(DEPARTURE,
                "departure");
        PL(SOURCE,
                "Source");
        PL(DESTINATION,
                "Destination");
        PL(HYPERSPACING_IN_N_SECONDS,
                "Hyperspacing in %.0f seconds");
        PL(NAVIGATION_TARGETS_IN_THIS_SYSTEM,
                "Navigation targets in this system");
        PL(YOU_NO_MONEY,
                "You do not have any money.");
        PL(FINE_PAID_N_BUT_N_REMAINING,
                "You have paid %s but still have an outstanding fine of %s.");
        PL(FINE_PAID_N,
                "You have paid the fine of %s.");
        PL(SET_HYPERSPACE_DESTINATION_TO,
                "Set hyperspace destination to "); // preserve trailing space
        PL(NO_TARGET_SELECTED,
                "Ship Computer: No target selected");
        PL(REQUEST_DOCKING_CLEARANCE,
                "Request docking clearance");
        PL(AUTOPILOT_DOCK_WITH_STATION,
                "Autopilot: Dock with space station");
        PL(PAY_FINE_REMOTELY,
                "Pay fine by remote transfer (%s)");
        PL(AUTOPILOT_FLY_TO_VICINITY_OF,
                "Autopilot: Fly to vicinity of "); // preserve trailing space
        PL(AUTOPILOT_ENTER_LOW_ORBIT_AROUND,
                "Autopilot: Enter low orbit around "); // preserve trailing space
        PL(AUTOPILOT_ENTER_MEDIUM_ORBIT_AROUND,
                "Autopilot: Enter medium orbit around "); // preserve trailing space
        PL(AUTOPILOT_ENTER_HIGH_ORBIT_AROUND,
                "Autopilot: Enter high orbit around "); // preserve trailing space
        PL(SET_HYPERSPACE_TARGET_TO_FOLLOW_THIS_DEPARTURE,
                "Hyperspace cloud analyzer: Set hyperspace target to follow this departure");
        PL(SET_HYPERSPACE_TARGET_TO,
                "Set hyperspace target to "); // preserve trailing space
    }
    namespace test {
        // An example additional language.  It inherits all strings from
        // the English namespace, and then overloads them.  This way,
        // untranslated strings fall back to English.
        using namespace en;
        PL(SUGGESTED_RESPONSES,
                "Tested responses:");
    }
}
