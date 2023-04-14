/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file script_window.hpp Everything to handle window interaction. */

#ifndef SCRIPT_WINDOW_HPP
#define SCRIPT_WINDOW_HPP

#include "script_object.hpp"
#include "../../window_type.h"
#include "../../gfx_type.h"

#include "../../window_type.h"
#include "../../widgets/ai_widget.h"
#include "../../widgets/airport_widget.h"
#include "../../widgets/autoreplace_widget.h"
#include "../../widgets/bootstrap_widget.h"
#include "../../widgets/bridge_widget.h"
#include "../../widgets/build_vehicle_widget.h"
#include "../../widgets/cheat_widget.h"
#include "../../widgets/company_widget.h"
#include "../../widgets/console_widget.h"
#include "../../widgets/date_widget.h"
#include "../../widgets/departures_widget.h"
#include "../../widgets/depot_widget.h"
#include "../../widgets/dock_widget.h"
#include "../../widgets/dropdown_widget.h"
#include "../../widgets/engine_widget.h"
#include "../../widgets/error_widget.h"
#include "../../widgets/fios_widget.h"
#include "../../widgets/framerate_widget.h"
#include "../../widgets/game_widget.h"
#include "../../widgets/genworld_widget.h"
#include "../../widgets/goal_widget.h"
#include "../../widgets/graph_widget.h"
#include "../../widgets/group_widget.h"
#include "../../widgets/highscore_widget.h"
#include "../../widgets/industry_widget.h"
#include "../../widgets/intro_widget.h"
#include "../../widgets/league_widget.h"
#include "../../widgets/link_graph_legend_widget.h"
#include "../../widgets/main_widget.h"
#include "../../widgets/misc_widget.h"
#include "../../widgets/music_widget.h"
#include "../../widgets/network_chat_widget.h"
#include "../../widgets/network_content_widget.h"
#include "../../widgets/network_widget.h"
#include "../../widgets/newgrf_debug_widget.h"
#include "../../widgets/newgrf_widget.h"
#include "../../widgets/news_widget.h"
#include "../../widgets/object_widget.h"
#include "../../widgets/order_widget.h"
#include "../../widgets/osk_widget.h"
#include "../../widgets/plans_widget.h"
#include "../../widgets/rail_widget.h"
#include "../../widgets/road_widget.h"
#include "../../widgets/screenshot_widget.h"
#include "../../widgets/script_widget.h"
#include "../../widgets/settings_widget.h"
#include "../../widgets/sign_widget.h"
#include "../../widgets/smallmap_widget.h"
#include "../../widgets/station_widget.h"
#include "../../widgets/statusbar_widget.h"
#include "../../widgets/story_widget.h"
#include "../../widgets/subsidy_widget.h"
#include "../../widgets/terraform_widget.h"
#include "../../widgets/timetable_widget.h"
#include "../../widgets/toolbar_widget.h"
#include "../../widgets/town_widget.h"
#include "../../widgets/transparency_widget.h"
#include "../../widgets/tree_widget.h"
#include "../../widgets/vehicle_widget.h"
#include "../../widgets/viewport_widget.h"
#include "../../widgets/waypoint_widget.h"

/**
 * Class that handles window interaction. A Window in OpenTTD has two important
 *  values. The WindowClass, and a Window number. The first indicates roughly
 *  which window it is. WC_TOWN_VIEW for example, is the view of a town.
 * The Window number is a bit more complex, as it depends mostly on the
 *  WindowClass. For example for WC_TOWN_VIEW it is the TownID. In general a
 *  good rule of thumb is: either the number is always 0, or the ID of the
 *  object in question.
 * In the comment at the widget enum, it is mentioned how the number is used.
 *
 * Note, that the detailed window layout is very version specific.
 * Enum values might be added, changed or removed in future versions without notice
 * in the changelog, and there won't be any means of compatibility.
 *
 * @api game
 */
class ScriptWindow : public ScriptObject {
public:
	// @enum WindowNumberEnum ../../window_type.h
	/* automatically generated from ../../window_type.h */
	/** %Window numbers. */
	enum WindowNumberEnum {
		WN_GAME_OPTIONS_AI                           = ::WN_GAME_OPTIONS_AI,                           ///< AI settings.
		WN_GAME_OPTIONS_GS                           = ::WN_GAME_OPTIONS_GS,                           ///< GS settings.
		WN_GAME_OPTIONS_ABOUT                        = ::WN_GAME_OPTIONS_ABOUT,                        ///< About window.
		WN_GAME_OPTIONS_NEWGRF_STATE                 = ::WN_GAME_OPTIONS_NEWGRF_STATE,                 ///< NewGRF settings.
		WN_GAME_OPTIONS_GAME_OPTIONS                 = ::WN_GAME_OPTIONS_GAME_OPTIONS,                 ///< Game options.
		WN_GAME_OPTIONS_GAME_SETTINGS                = ::WN_GAME_OPTIONS_GAME_SETTINGS,                ///< Game settings.

		WN_QUERY_STRING                              = ::WN_QUERY_STRING,                              ///< Query string.
		WN_QUERY_STRING_SIGN                         = ::WN_QUERY_STRING_SIGN,                         ///< Query string for signs.

		WN_CONFIRM_POPUP_QUERY                       = ::WN_CONFIRM_POPUP_QUERY,                       ///< Query popup confirm.
		WN_CONFIRM_POPUP_QUERY_BOOTSTRAP             = ::WN_CONFIRM_POPUP_QUERY_BOOTSTRAP,             ///< Query popup confirm for bootstrap.

		WN_NETWORK_WINDOW_GAME                       = ::WN_NETWORK_WINDOW_GAME,                       ///< Network game window.
		WN_NETWORK_WINDOW_CONTENT_LIST               = ::WN_NETWORK_WINDOW_CONTENT_LIST,               ///< Network content list.
		WN_NETWORK_WINDOW_START                      = ::WN_NETWORK_WINDOW_START,                      ///< Network start server.

		WN_NETWORK_STATUS_WINDOW_JOIN                = ::WN_NETWORK_STATUS_WINDOW_JOIN,                ///< Network join status.
		WN_NETWORK_STATUS_WINDOW_CONTENT_DOWNLOAD    = ::WN_NETWORK_STATUS_WINDOW_CONTENT_DOWNLOAD,    ///< Network content download status.
	};

	// @endenum

	// @enum WindowClass ../../window_type.h
	/* automatically generated from ../../window_type.h */
	/** %Window classes. */
	enum WindowClass {
		WC_NONE                                      = ::WC_NONE,                                      ///< No window, redirects to WC_MAIN_WINDOW.

		/**
		 * Main window; %Window numbers:
		 *   - 0 = #MainWidgets
		 */
		WC_MAIN_WINDOW                               = ::WC_MAIN_WINDOW,

		/**
		 * Main toolbar (the long bar at the top); %Window numbers:
		 *   - 0 = #ToolbarNormalWidgets
		 *   - 0 = #ToolbarEditorWidgets
		 */
		WC_MAIN_TOOLBAR                              = ::WC_MAIN_TOOLBAR,

		/**
		 * Statusbar (at the bottom of your screen); %Window numbers:
		 *   - 0 = #StatusbarWidgets
		 */
		WC_STATUS_BAR                                = ::WC_STATUS_BAR,

		/**
		 * Build toolbar; %Window numbers:
		 *   - #TRANSPORT_RAIL = #RailToolbarWidgets
		 *   - #TRANSPORT_AIR = #AirportToolbarWidgets
		 *   - #TRANSPORT_WATER = #DockToolbarWidgets
		 *   - #TRANSPORT_ROAD = #RoadToolbarWidgets
		 */
		WC_BUILD_TOOLBAR                             = ::WC_BUILD_TOOLBAR,

		/**
		 * Scenario build toolbar; %Window numbers:
		 *   - #TRANSPORT_WATER = #DockToolbarWidgets
		 *   - #TRANSPORT_ROAD = #RoadToolbarWidgets
		 */
		WC_SCEN_BUILD_TOOLBAR                        = ::WC_SCEN_BUILD_TOOLBAR,

		/**
		 * Build trees toolbar; %Window numbers:
		 *   - 0 = #BuildTreesWidgets
		 */
		WC_BUILD_TREES                               = ::WC_BUILD_TREES,

		/**
		 * Transparency toolbar; %Window numbers:
		 *   - 0 = #TransparencyToolbarWidgets
		 */
		WC_TRANSPARENCY_TOOLBAR                      = ::WC_TRANSPARENCY_TOOLBAR,

		/**
		 * Build signal toolbar; %Window numbers:
		 *   - #TRANSPORT_RAIL = #BuildSignalWidgets
		 */
		WC_BUILD_SIGNAL                              = ::WC_BUILD_SIGNAL,

		/**
		 * Small map; %Window numbers:
		 *   - 0 = #SmallMapWidgets
		 */
		WC_SMALLMAP                                  = ::WC_SMALLMAP,

		/**
		 * Error message; %Window numbers:
		 *   - 0 = #ErrorMessageWidgets
		 */
		WC_ERRMSG                                    = ::WC_ERRMSG,

		/**
		 * Tooltip window; %Window numbers:
		 *   - 0 = #ToolTipsWidgets
		 */
		WC_TOOLTIPS                                  = ::WC_TOOLTIPS,

		/**
		* Station rating tooltip window; %Window numbers:
		*   - 0 = #ToolTipsWidgets
		*/
		WC_STATION_RATING_TOOLTIP                    = ::WC_STATION_RATING_TOOLTIP,

		/**
		 * Query string window; %Window numbers:
		 *   - #WN_QUERY_STRING = #QueryStringWidgets
		 *   - #WN_QUERY_STRING_SIGN = #QueryEditSignWidgets
		 */
		WC_QUERY_STRING                              = ::WC_QUERY_STRING,

		/**
		 * Popup with confirm question; %Window numbers:
		 *   - #WN_CONFIRM_POPUP_QUERY = #QueryWidgets
		 *   - #WN_CONFIRM_POPUP_QUERY_BOOTSTRAP = #BootstrapAskForDownloadWidgets
		 */
		WC_CONFIRM_POPUP_QUERY                       = ::WC_CONFIRM_POPUP_QUERY,

		/**
		 * Popup with a set of buttons, designed to ask the user a question
		 *  from a GameScript. %Window numbers:
		 *   - uniqueid = #GoalQuestionWidgets
		 */
		WC_GOAL_QUESTION                             = ::WC_GOAL_QUESTION,


		/**
		 * Saveload window; %Window numbers:
		 *   - 0 = #SaveLoadWidgets
		 */
		WC_SAVELOAD                                  = ::WC_SAVELOAD,

		/**
		 * Land info window; %Window numbers:
		 *   - 0 = #LandInfoWidgets
		 */
		WC_LAND_INFO                                 = ::WC_LAND_INFO,

		/**
		 * Drop down menu; %Window numbers:
		 *   - 0 = #DropdownMenuWidgets
		 */
		WC_DROPDOWN_MENU                             = ::WC_DROPDOWN_MENU,

		/**
		 * On Screen Keyboard; %Window numbers:
		 *   - 0 = #OnScreenKeyboardWidgets
		 */
		WC_OSK                                       = ::WC_OSK,

		/**
		 * Set date; %Window numbers:
		 *   - #VehicleID = #SetDateWidgets
		 */
		WC_SET_DATE                                  = ::WC_SET_DATE,


		/**
		 * Script settings; %Window numbers:
		 *   - 0 = #ScriptSettingsWidgets
		 */
		WC_SCRIPT_SETTINGS                           = ::WC_SCRIPT_SETTINGS,

		/**
		 * NewGRF parameters; %Window numbers:
		 *   - 0 = #NewGRFParametersWidgets
		 */
		WC_GRF_PARAMETERS                            = ::WC_GRF_PARAMETERS,

		/**
		 * textfile; %Window numbers:
		 *   - 0 = #TextfileWidgets
		 */
		WC_TEXTFILE                                  = ::WC_TEXTFILE,


		/**
		 * Town authority; %Window numbers:
		 *   - #TownID = #TownAuthorityWidgets
		 */
		WC_TOWN_AUTHORITY                            = ::WC_TOWN_AUTHORITY,

		/**
		 * Vehicle details; %Window numbers:
		 *   - #VehicleID = #VehicleDetailsWidgets
		 */
		WC_VEHICLE_DETAILS                           = ::WC_VEHICLE_DETAILS,

		/**
		 * Vehicle refit; %Window numbers:
		 *   - #VehicleID = #VehicleRefitWidgets
		 */
		WC_VEHICLE_REFIT                             = ::WC_VEHICLE_REFIT,

		/**
		 * Vehicle orders; %Window numbers:
		 *   - #VehicleID = #OrderWidgets
		 */
		WC_VEHICLE_ORDERS                            = ::WC_VEHICLE_ORDERS,

		/**
		 * Vehicle cargo type load orders; %Window numbers:
		 *   - #VehicleID = #CargoTypeOrdersWidgets
		 */
		WC_VEHICLE_CARGO_TYPE_LOAD_ORDERS            = ::WC_VEHICLE_CARGO_TYPE_LOAD_ORDERS,

		/**
		 * Vehicle cargo type unload orders; %Window numbers:
		 *   - #VehicleID = #CargoTypeOrdersWidgets
		 */
		WC_VEHICLE_CARGO_TYPE_UNLOAD_ORDERS          = ::WC_VEHICLE_CARGO_TYPE_UNLOAD_ORDERS,

		/**
		 * Replace vehicle window; %Window numbers:
		 *   - #VehicleType = #ReplaceVehicleWidgets
		 */
		WC_REPLACE_VEHICLE                           = ::WC_REPLACE_VEHICLE,

		/**
		 * Vehicle timetable; %Window numbers:
		 *   - #VehicleID = #VehicleTimetableWidgets
		 */
		WC_VEHICLE_TIMETABLE                         = ::WC_VEHICLE_TIMETABLE,

		/**
		 * Vehicle trip history; %Window numbers:
		 *   - #VehicleID = #VehicleTripHistoryWidgets
		 */
		WC_VEHICLE_TRIP_HISTORY                      = ::WC_VEHICLE_TRIP_HISTORY,
		
		/**
		 * Company colour selection; %Window numbers:
		 *   - #CompanyID = #SelectCompanyLiveryWidgets
		 */
		WC_COMPANY_COLOUR                            = ::WC_COMPANY_COLOUR,

		/**
		 * Alter company face window; %Window numbers:
		 *   - #CompanyID = #SelectCompanyManagerFaceWidgets
		 */
		WC_COMPANY_MANAGER_FACE                      = ::WC_COMPANY_MANAGER_FACE,

		/**
		 * Select station (when joining stations); %Window numbers:
		 *   - 0 = #JoinStationWidgets
		 */
		WC_SELECT_STATION                            = ::WC_SELECT_STATION,

		/**
		 * Select town (when placing a house); %Window numbers:
		 *   - 0 = #SelectTownWidgets
		 */
		WC_SELECT_TOWN                               = ::WC_SELECT_TOWN,

		/**
		 * News window; %Window numbers:
		 *   - 0 = #NewsWidgets
		 */
		WC_NEWS_WINDOW                               = ::WC_NEWS_WINDOW,

		/**
		 * Town directory; %Window numbers:
		 *   - 0 = #TownDirectoryWidgets
		 */
		WC_TOWN_DIRECTORY                            = ::WC_TOWN_DIRECTORY,

		/**
		 * Subsidies list; %Window numbers:
		 *   - 0 = #SubsidyListWidgets
		 */
		WC_SUBSIDIES_LIST                            = ::WC_SUBSIDIES_LIST,

		/**
		 * Industry directory; %Window numbers:
		 *   - 0 = #IndustryDirectoryWidgets
		 */
		WC_INDUSTRY_DIRECTORY                        = ::WC_INDUSTRY_DIRECTORY,

		/**
		 * News history list; %Window numbers:
		 *   - 0 = #MessageHistoryWidgets
		 */
		WC_MESSAGE_HISTORY                           = ::WC_MESSAGE_HISTORY,

		/**
		 * Sign list; %Window numbers:
		 *   - 0 = #SignListWidgets
		 */
		WC_SIGN_LIST                                 = ::WC_SIGN_LIST,

		/**
		 * Scripts list; %Window numbers:
		 *   - 0 = #ScriptListWidgets
		 */
		WC_SCRIPT_LIST                               = ::WC_SCRIPT_LIST,

		/**
		 * Goals list; %Window numbers:
		 *   - 0 ; #GoalListWidgets
		 */
		WC_GOALS_LIST                                = ::WC_GOALS_LIST,

		/**
		 * Story book; %Window numbers:
		 *   - CompanyID = #StoryBookWidgets
		 */
		WC_STORY_BOOK                                = ::WC_STORY_BOOK,

		/**
		 * Station list; %Window numbers:
		 *   - #CompanyID = #StationListWidgets
		 */
		WC_STATION_LIST                              = ::WC_STATION_LIST,

		/**
		 * Trains list; %Window numbers:
		 *   - Packed value = #GroupListWidgets / #VehicleListWidgets
		 */
		WC_TRAINS_LIST                               = ::WC_TRAINS_LIST,

		/**
		 * Road vehicle list; %Window numbers:
		 *   - Packed value = #GroupListWidgets / #VehicleListWidgets
		 */
		WC_ROADVEH_LIST                              = ::WC_ROADVEH_LIST,

		/**
		 * Ships list; %Window numbers:
		 *   - Packed value = #GroupListWidgets / #VehicleListWidgets
		 */
		WC_SHIPS_LIST                                = ::WC_SHIPS_LIST,

		/**
		 * Aircraft list; %Window numbers:
		 *   - Packed value = #GroupListWidgets / #VehicleListWidgets
		 */
		WC_AIRCRAFT_LIST                             = ::WC_AIRCRAFT_LIST,


		/**
		 * Town view; %Window numbers:
		 *   - #TownID = #TownViewWidgets
		 */
		WC_TOWN_VIEW                                 = ::WC_TOWN_VIEW,

		/**
		 * Vehicle view; %Window numbers:
		 *   - #VehicleID = #VehicleViewWidgets
		 */
		WC_VEHICLE_VIEW                              = ::WC_VEHICLE_VIEW,

		/**
		 * Station view; %Window numbers:
		 *   - #StationID = #StationViewWidgets
		 */
		WC_STATION_VIEW                              = ::WC_STATION_VIEW,

		/**
		 * Depot view; %Window numbers:
		 *   - #TileIndex = #DepotWidgets
		 */
		WC_VEHICLE_DEPOT                             = ::WC_VEHICLE_DEPOT,

		/**
		 * Waypoint view; %Window numbers:
		 *   - #WaypointID = #WaypointWidgets
		 */
		WC_WAYPOINT_VIEW                             = ::WC_WAYPOINT_VIEW,

		/**
		 * Industry view; %Window numbers:
		 *   - #IndustryID = #IndustryViewWidgets
		 */
		WC_INDUSTRY_VIEW                             = ::WC_INDUSTRY_VIEW,

		/**
		 * Company view; %Window numbers:
		 *   - #CompanyID = #CompanyWidgets
		 */
		WC_COMPANY                                   = ::WC_COMPANY,


		/**
		 * Build object; %Window numbers:
		 *   - 0 = #BuildObjectWidgets
		 */
		WC_BUILD_OBJECT                              = ::WC_BUILD_OBJECT,

		/**
		 * Build house; %Window numbers:
		 *  - 0 = #BuildHouseWidgets
		*/
		WC_BUILD_HOUSE                               = ::WC_BUILD_HOUSE,

		/**
		 * Build vehicle; %Window numbers:
		 *   - #VehicleType = #BuildVehicleWidgets
		 *   - #TileIndex = #BuildVehicleWidgets
		 */
		WC_BUILD_VEHICLE                             = ::WC_BUILD_VEHICLE,

		/**
		 * Build bridge; %Window numbers:
		 *   - #TransportType = #BuildBridgeSelectionWidgets
		 */
		WC_BUILD_BRIDGE                              = ::WC_BUILD_BRIDGE,

		/**
		 * Build station; %Window numbers:
		 *   - #TRANSPORT_AIR = #AirportPickerWidgets
		 *   - #TRANSPORT_WATER = #DockToolbarWidgets
		 *   - #TRANSPORT_RAIL = #BuildRailStationWidgets
		 */
		WC_BUILD_STATION                             = ::WC_BUILD_STATION,

		/**
		 * Build bus station; %Window numbers:
		 *   - #TRANSPORT_ROAD = #BuildRoadStationWidgets
		 */
		WC_BUS_STATION                               = ::WC_BUS_STATION,

		/**
		 * Build truck station; %Window numbers:
		 *   - #TRANSPORT_ROAD = #BuildRoadStationWidgets
		 */
		WC_TRUCK_STATION                             = ::WC_TRUCK_STATION,

		/**
		 * Build depot; %Window numbers:
		 *   - #TRANSPORT_WATER = #BuildDockDepotWidgets
		 *   - #TRANSPORT_RAIL = #BuildRailDepotWidgets
		 *   - #TRANSPORT_ROAD = #BuildRoadDepotWidgets
		 */
		WC_BUILD_DEPOT                               = ::WC_BUILD_DEPOT,

		/**
		 * Build waypoint; %Window numbers:
		 *   - #TRANSPORT_RAIL = #BuildRailWaypointWidgets
		 */
		WC_BUILD_WAYPOINT                            = ::WC_BUILD_WAYPOINT,

		/**
		 * Found a town; %Window numbers:
		 *   - 0 = #TownFoundingWidgets
		 */
		WC_FOUND_TOWN                                = ::WC_FOUND_TOWN,

		/**
		 * Build industry; %Window numbers:
		 *   - 0 = #DynamicPlaceIndustriesWidgets
		 */
		WC_BUILD_INDUSTRY                            = ::WC_BUILD_INDUSTRY,


		/**
		 * Select game window; %Window numbers:
		 *   - 0 = #SelectGameIntroWidgets
		 */
		WC_SELECT_GAME                               = ::WC_SELECT_GAME,

		/**
		 * Landscape generation (in Scenario Editor); %Window numbers:
		 *   - 0 = #TerraformToolbarWidgets
		 *   - 0 = #EditorTerraformToolbarWidgets
		 */
		WC_SCEN_LAND_GEN                             = ::WC_SCEN_LAND_GEN,

		/**
		 * Generate landscape (newgame); %Window numbers:
		 *   - GLWM_SCENARIO = #CreateScenarioWidgets
		 *   - #GenerateLandscapeWindowMode = #GenerateLandscapeWidgets
		 */
		WC_GENERATE_LANDSCAPE                        = ::WC_GENERATE_LANDSCAPE,

		/**
		 * Progress report of landscape generation; %Window numbers:
		 *   - 0 = #GenerationProgressWidgets
		 *   - 1 = #ScanProgressWidgets
		 */
		WC_MODAL_PROGRESS                            = ::WC_MODAL_PROGRESS,


		/**
		 * Network window; %Window numbers:
		 *   - #WN_NETWORK_WINDOW_GAME = #NetworkGameWidgets
		 *   - #WN_NETWORK_WINDOW_CONTENT_LIST = #NetworkContentListWidgets
		 *   - #WN_NETWORK_WINDOW_START = #NetworkStartServerWidgets
		 */
		WC_NETWORK_WINDOW                            = ::WC_NETWORK_WINDOW,

		/**
		 * Client list; %Window numbers:
		 *   - 0 = #ClientListWidgets
		 */
		WC_CLIENT_LIST                               = ::WC_CLIENT_LIST,

		/**
		 * Network status window; %Window numbers:
		 *   - #WN_NETWORK_STATUS_WINDOW_JOIN = #NetworkJoinStatusWidgets
		 *   - #WN_NETWORK_STATUS_WINDOW_CONTENT_DOWNLOAD = #NetworkContentDownloadStatusWidgets
		 */
		WC_NETWORK_STATUS_WINDOW                     = ::WC_NETWORK_STATUS_WINDOW,

		/**
		 * Network ask relay window; %Window numbers:
		 *   - 0 - #NetworkAskRelayWidgets
		 */
		WC_NETWORK_ASK_RELAY                         = ::WC_NETWORK_ASK_RELAY,

		/**
		 * Chatbox; %Window numbers:
		 *   - #DestType = #NetWorkChatWidgets
		 */
		WC_SEND_NETWORK_MSG                          = ::WC_SEND_NETWORK_MSG,

		/**
		 * Company password query; %Window numbers:
		 *   - 0 = #NetworkCompanyPasswordWidgets
		 */
		WC_COMPANY_PASSWORD_WINDOW                   = ::WC_COMPANY_PASSWORD_WINDOW,


		/**
		 * Industry cargoes chain; %Window numbers:
		 *   - 0 = #IndustryCargoesWidgets
		 */
		WC_INDUSTRY_CARGOES                          = ::WC_INDUSTRY_CARGOES,

		/**
		 * Legend for graphs; %Window numbers:
		 *   - 0 = #GraphLegendWidgets
		 */
		WC_GRAPH_LEGEND                              = ::WC_GRAPH_LEGEND,

		/**
		 * Finances of a company; %Window numbers:
		 *   - #CompanyID = #CompanyWidgets
		 */
		WC_FINANCES                                  = ::WC_FINANCES,

		/**
		 * Income graph; %Window numbers:
		 *   - 0 = #CompanyValueWidgets
		 */
		WC_INCOME_GRAPH                              = ::WC_INCOME_GRAPH,

		/**
		 * Operating profit graph; %Window numbers:
		 *   - 0 = #CompanyValueWidgets
		 */
		WC_OPERATING_PROFIT                          = ::WC_OPERATING_PROFIT,

		/**
		 * Delivered cargo graph; %Window numbers:
		 *   - 0 = #CompanyValueWidgets
		 */
		WC_DELIVERED_CARGO                           = ::WC_DELIVERED_CARGO,

		/**
		 * Performance history graph; %Window numbers:
		 *   - 0 = #PerformanceHistoryGraphWidgets
		 */
		WC_PERFORMANCE_HISTORY                       = ::WC_PERFORMANCE_HISTORY,

		/**
		 * Company value graph; %Window numbers:
		 *   - 0 = #CompanyValueWidgets
		 */
		WC_COMPANY_VALUE                             = ::WC_COMPANY_VALUE,

		/**
		 * Company league window; %Window numbers:
		 *   - 0 = #CompanyLeagueWidgets
		 */
		WC_COMPANY_LEAGUE                            = ::WC_COMPANY_LEAGUE,

		/**
		 * Payment rates graph; %Window numbers:
		 *   - 0 = #CargoPaymentRatesWidgets
		 */
		WC_PAYMENT_RATES                             = ::WC_PAYMENT_RATES,

		/**
		* Station cargo graph; %Window numbers:
		*   - #StationID = #StationCargoWidgets
		*/
		WC_STATION_CARGO                             = ::WC_STATION_CARGO,

		/**
		 * Performance detail window; %Window numbers:
		 *   - 0 = #PerformanceRatingDetailsWidgets
		 */
		WC_PERFORMANCE_DETAIL                        = ::WC_PERFORMANCE_DETAIL,

		/**
		 * Industry production history graph; %Window numbers:
		 *   - #IndustryID = #IndustryProductionGraphWidgets
		 */
		WC_INDUSTRY_PRODUCTION                       = ::WC_INDUSTRY_PRODUCTION,

		/**
		 * Company infrastructure overview; %Window numbers:
		 *   - #CompanyID = #CompanyInfrastructureWidgets
		 */
		WC_COMPANY_INFRASTRUCTURE                    = ::WC_COMPANY_INFRASTRUCTURE,


		/**
		 * Buyout company (merger); %Window numbers:
		 *   - #CompanyID = #BuyCompanyWidgets
		 */
		WC_BUY_COMPANY                               = ::WC_BUY_COMPANY,

		/**
		 * Engine preview window; %Window numbers:
		 *   - #EngineID = #EnginePreviewWidgets
		 */
		WC_ENGINE_PREVIEW                            = ::WC_ENGINE_PREVIEW,


		/**
		 * Music window; %Window numbers:
		 *   - 0 = #MusicWidgets
		 */
		WC_MUSIC_WINDOW                              = ::WC_MUSIC_WINDOW,

		/**
		 * Music track selection; %Window numbers:
		 *   - 0 = MusicTrackSelectionWidgets
		 */
		WC_MUSIC_TRACK_SELECTION                     = ::WC_MUSIC_TRACK_SELECTION,

		/**
		 * Game options window; %Window numbers:
		 *   - #WN_GAME_OPTIONS_AI = #AIConfigWidgets
		 *   - #WN_GAME_OPTIONS_GS = #GSConfigWidgets
		 *   - #WN_GAME_OPTIONS_ABOUT = #AboutWidgets
		 *   - #WN_GAME_OPTIONS_NEWGRF_STATE = #NewGRFStateWidgets
		 *   - #WN_GAME_OPTIONS_GAME_OPTIONS = #GameOptionsWidgets
		 *   - #WN_GAME_OPTIONS_GAME_SETTINGS = #GameSettingsWidgets
		 */
		WC_GAME_OPTIONS                              = ::WC_GAME_OPTIONS,

		/**
		 * Custom currency; %Window numbers:
		 *   - 0 = #CustomCurrencyWidgets
		 */
		WC_CUSTOM_CURRENCY                           = ::WC_CUSTOM_CURRENCY,

		/**
		 * Cheat window; %Window numbers:
		 *   - 0 = #CheatWidgets
		 */
		WC_CHEATS                                    = ::WC_CHEATS,

		/**
		 * Extra viewport; %Window numbers:
		 *   - Ascending value = #ExtraViewportWidgets
		 */
		WC_EXTRA_VIEWPORT                            = ::WC_EXTRA_VIEWPORT,


		/**
		 * Console; %Window numbers:
		 *   - 0 = #ConsoleWidgets
		 */
		WC_CONSOLE                                   = ::WC_CONSOLE,

		/**
		 * Bootstrap; %Window numbers:
		 *   - 0 = #BootstrapBackgroundWidgets
		 */
		WC_BOOTSTRAP                                 = ::WC_BOOTSTRAP,

		/**
		 * Highscore; %Window numbers:
		 *   - 0 = #HighscoreWidgets
		 */
		WC_HIGHSCORE                                 = ::WC_HIGHSCORE,

		/**
		 * Endscreen; %Window numbers:
		 *   - 0 = #HighscoreWidgets
		 */
		WC_ENDSCREEN                                 = ::WC_ENDSCREEN,


		/**
		 * Script debug window; %Window numbers:
		 *   - 0 = #ScriptDebugWidgets
		 */
		WC_SCRIPT_DEBUG                              = ::WC_SCRIPT_DEBUG,

		/**
		 * NewGRF inspect (debug); %Window numbers:
		 *   - Packed value = #NewGRFInspectWidgets
		 */
		WC_NEWGRF_INSPECT                            = ::WC_NEWGRF_INSPECT,

		/**
		 * Sprite aligner (debug); %Window numbers:
		 *   - 0 = #SpriteAlignerWidgets
		 */
		WC_SPRITE_ALIGNER                            = ::WC_SPRITE_ALIGNER,
		WC_ZONING_TOOLBAR                            = ::WC_ZONING_TOOLBAR,

		/**
		 * Linkgraph legend; %Window numbers:
		 *   - 0 = #LinkGraphWidgets
		 */
		WC_LINKGRAPH_LEGEND                          = ::WC_LINKGRAPH_LEGEND,

		/**
		 * Save preset; %Window numbers:
		 *   - 0 = #SavePresetWidgets
		 */
		WC_SAVE_PRESET                               = ::WC_SAVE_PRESET,

		/**
		 * Framerate display; %Window numbers:
		 *   - 0 = #FramerateDisplayWidgets
		 */
		WC_FRAMERATE_DISPLAY                         = ::WC_FRAMERATE_DISPLAY,

		/**
		 * Frame time graph; %Window numbers:
		 *   - 0 = #FrametimeGraphWindowWidgets
		 */
		WC_FRAMETIME_GRAPH                           = ::WC_FRAMETIME_GRAPH,
		/**
		 * Screenshot window; %Window numbers:
		 *   - 0 = #ScreenshotWidgets
		 */
		WC_SCREENSHOT                                = ::WC_SCREENSHOT,

		/**
		 * Trace restrict programme window; %Window numbers:
		 *   - #TileIndex << 3 | #Track = #TraceRestrictWindow
		 */
		WC_TRACE_RESTRICT                            = ::WC_TRACE_RESTRICT,

		/**
		 * Trace restrict slot window; %Window numbers:
		 *   - Packed value = #SlotListWidgets / #VehicleListWidgets
		 */
		WC_TRACE_RESTRICT_SLOTS                      = ::WC_TRACE_RESTRICT_SLOTS,

		/**
		 * Trace restrict counter window; %Window numbers:
		 *   - Packed value = #SlotListWidgets / #VehicleListWidgets
		 */
		WC_TRACE_RESTRICT_COUNTERS                   = ::WC_TRACE_RESTRICT_COUNTERS,

		/**
		 * Programmable pre-signals window
		 */
		WC_SIGNAL_PROGRAM                            = ::WC_SIGNAL_PROGRAM,

		/**
		 * Departure boards
		 */
		WC_DEPARTURES_BOARD                          = ::WC_DEPARTURES_BOARD,

		/**
		 * Vehicle scheduled dispatch - departure slots
		 */
		WC_SCHDISPATCH_SLOTS                         = ::WC_SCHDISPATCH_SLOTS,

		/**
		 * Plans window.
		 */
		WC_PLANS                                     = ::WC_PLANS,

		WC_TEMPLATEGUI_MAIN                          = ::WC_TEMPLATEGUI_MAIN,
		WC_TEMPLATEGUI_RPLALL                        = ::WC_TEMPLATEGUI_RPLALL,
		WC_BUILD_VIRTUAL_TRAIN                       = ::WC_BUILD_VIRTUAL_TRAIN,
		WC_CREATE_TEMPLATE                           = ::WC_CREATE_TEMPLATE,

		/**
		 * Modifier key toggle window.
		 */
		WC_MODIFIER_KEY_TOGGLE                       = ::WC_MODIFIER_KEY_TOGGLE,

		WC_INVALID                                   = ::WC_INVALID,                                   ///< Invalid window.
	};

	// @endenum

	/**
	 * The colours in the game which you can use for text and highlights.
	 */
	enum TextColour {
		/* Note: these values represent part of the in-game TextColour enum */
		TC_BLUE        = ::TC_BLUE,        ///< Blue colour.
		TC_SILVER      = ::TC_SILVER,      ///< Silver colour.
		TC_GOLD        = ::TC_GOLD,        ///< Gold colour.
		TC_RED         = ::TC_RED,         ///< Red colour.
		TC_PURPLE      = ::TC_PURPLE,      ///< Purple colour.
		TC_LIGHT_BROWN = ::TC_LIGHT_BROWN, ///< Light brown colour.
		TC_ORANGE      = ::TC_ORANGE,      ///< Orange colour.
		TC_GREEN       = ::TC_GREEN,       ///< Green colour.
		TC_YELLOW      = ::TC_YELLOW,      ///< Yellow colour.
		TC_DARK_GREEN  = ::TC_DARK_GREEN,  ///< Dark green colour.
		TC_CREAM       = ::TC_CREAM,       ///< Cream colour.
		TC_BROWN       = ::TC_BROWN,       ///< Brown colour.
		TC_WHITE       = ::TC_WHITE,       ///< White colour.
		TC_LIGHT_BLUE  = ::TC_LIGHT_BLUE,  ///< Light blue colour.
		TC_GREY        = ::TC_GREY,        ///< Grey colour.
		TC_DARK_BLUE   = ::TC_DARK_BLUE,   ///< Dark blue colour.
		TC_BLACK       = ::TC_BLACK,       ///< Black colour.
		TC_INVALID     = ::TC_INVALID,     ///< Invalid colour.
	};

	/**
	 * Special number values.
	 */
	enum NumberType {
		NUMBER_ALL = -1, ///< Value to select all windows of a class.
	};

	/**
	 * Special widget values.
	 */
	enum WidgetType {
		WIDGET_ALL = -1, ///< Value to select all widgets of a window.
	};

	/**
	 * Close a window.
	 * @param window The class of the window to close.
	 * @param number The number of the window to close, or NUMBER_ALL to close all of this class.
	 *               The value will be clamped to 0 .. MAX(int32) when value is not NUMBER_ALL.
	 * @pre !ScriptGame::IsMultiplayer().
	 */
	static void Close(WindowClass window, SQInteger number);

	/**
	 * Check if a window is open.
	 * @param window The class of the window to check for.
	 * @param number The number of the window to check for, or NUMBER_ALL to check for any in the class.
	 *               The value will be clamped to 0 .. MAX(int32) when value is not NUMBER_ALL.
	 * @pre !ScriptGame::IsMultiplayer().
	 * @return True if the window is open.
	 */
	static bool IsOpen(WindowClass window, SQInteger number);

	/**
	 * Highlight a widget in a window.
	 * @param window The class of the window to highlight a widget in.
	 * @param number The number of the window to highlight a widget in.
	 *               The value will be clamped to 0 .. MAX(int32) when value is not NUMBER_ALL.
	 * @param widget The widget in the window to highlight, or WIDGET_ALL (in combination with TC_INVALID) to disable all widget highlighting on this window.
	 *               The value will be clamped to 0 .. MAX(uint8) when value is not WIDGET_ALL.
	 * @param colour The colour of the highlight, or TC_INVALID for disabling.
	 * @pre !ScriptGame::IsMultiplayer().
	 * @pre number != NUMBER_ALL.
	 * @pre colour < TC_END || (widget == WIDGET_ALL && colour == TC_INVALID).
	 * @pre IsOpen(window, number).
	 */
	static void Highlight(WindowClass window, SQInteger number, SQInteger widget, TextColour colour);

	// @enum .*Widgets ../../widgets/*_widget.h
	/* automatically generated from ../../widgets/ai_widget.h */
	/** Widgets of the #AIConfigWindow class. */
	enum AIConfigWidgets {
		WID_AIC_BACKGROUND                           = ::WID_AIC_BACKGROUND,                           ///< Window background.
		WID_AIC_DECREASE                             = ::WID_AIC_DECREASE,                             ///< Decrease the number of AIs.
		WID_AIC_INCREASE                             = ::WID_AIC_INCREASE,                             ///< Increase the number of AIs.
		WID_AIC_NUMBER                               = ::WID_AIC_NUMBER,                               ///< Number of AIs.
		WID_AIC_LIST                                 = ::WID_AIC_LIST,                                 ///< List with currently selected AIs.
		WID_AIC_SCROLLBAR                            = ::WID_AIC_SCROLLBAR,                            ///< Scrollbar to scroll through the selected AIs.
		WID_AIC_MOVE_UP                              = ::WID_AIC_MOVE_UP,                              ///< Move up button.
		WID_AIC_MOVE_DOWN                            = ::WID_AIC_MOVE_DOWN,                            ///< Move down button.
		WID_AIC_CHANGE                               = ::WID_AIC_CHANGE,                               ///< Select another AI button.
		WID_AIC_CONFIGURE                            = ::WID_AIC_CONFIGURE,                            ///< Change AI settings button.
		WID_AIC_CLOSE                                = ::WID_AIC_CLOSE,                                ///< Close window button.
		WID_AIC_TEXTFILE                             = ::WID_AIC_TEXTFILE,                             ///< Open AI readme, changelog (+1) or license (+2).
		WID_AIC_CONTENT_DOWNLOAD                     = ::WID_AIC_CONTENT_DOWNLOAD,                     ///< Download content button.
	};

	/* automatically generated from ../../widgets/airport_widget.h */
	/** Widgets of the #BuildAirToolbarWindow class. */
	enum AirportToolbarWidgets {
		WID_AT_AIRPORT                               = ::WID_AT_AIRPORT,                               ///< Build airport button.
		WID_AT_DEMOLISH                              = ::WID_AT_DEMOLISH,                              ///< Demolish button.
	};

	/** Widgets of the #BuildAirportWindow class. */
	enum AirportPickerWidgets {
		WID_AP_CLASS_DROPDOWN                        = ::WID_AP_CLASS_DROPDOWN,                        ///< Dropdown of airport classes.
		WID_AP_AIRPORT_LIST                          = ::WID_AP_AIRPORT_LIST,                          ///< List of airports.
		WID_AP_SCROLLBAR                             = ::WID_AP_SCROLLBAR,                             ///< Scrollbar of the list.
		WID_AP_LAYOUT_NUM                            = ::WID_AP_LAYOUT_NUM,                            ///< Current number of the layout.
		WID_AP_LAYOUT_DECREASE                       = ::WID_AP_LAYOUT_DECREASE,                       ///< Decrease the layout number.
		WID_AP_LAYOUT_INCREASE                       = ::WID_AP_LAYOUT_INCREASE,                       ///< Increase the layout number.
		WID_AP_AIRPORT_SPRITE                        = ::WID_AP_AIRPORT_SPRITE,                        ///< A visual display of the airport currently selected.
		WID_AP_EXTRA_TEXT                            = ::WID_AP_EXTRA_TEXT,                            ///< Additional text about the airport.
		WID_AP_BOTTOMPANEL                           = ::WID_AP_BOTTOMPANEL,                           ///< Panel at the bottom.
		WID_AP_COVERAGE_LABEL                        = ::WID_AP_COVERAGE_LABEL,                        ///< Label if you want to see the coverage.
		WID_AP_BTN_DONTHILIGHT                       = ::WID_AP_BTN_DONTHILIGHT,                       ///< Don't show the coverage button.
		WID_AP_BTN_DOHILIGHT                         = ::WID_AP_BTN_DOHILIGHT,                         ///< Show the coverage button.
		WID_AP_ACCEPTANCE                            = ::WID_AP_ACCEPTANCE,                            ///< Acceptance info.
	};

	/* automatically generated from ../../widgets/autoreplace_widget.h */
	/** Widgets of the #ReplaceVehicleWindow class. */
	enum ReplaceVehicleWidgets {
		WID_RV_CAPTION                               = ::WID_RV_CAPTION,                               ///< Caption of the window.

		/* Sort dropdown at the right. */
		WID_RV_SORT_ASCENDING_DESCENDING             = ::WID_RV_SORT_ASCENDING_DESCENDING,             ///< Ascending/descending sort order button.
		WID_RV_SHOW_HIDDEN_ENGINES                   = ::WID_RV_SHOW_HIDDEN_ENGINES,                   ///< Toggle whether to display the hidden vehicles.
		WID_RV_SORT_DROPDOWN                         = ::WID_RV_SORT_DROPDOWN,                         ///< Dropdown for the sort criteria.

		/* Left and right matrix + details. */
		WID_RV_LEFT_MATRIX                           = ::WID_RV_LEFT_MATRIX,                           ///< The matrix on the left.
		WID_RV_LEFT_SCROLLBAR                        = ::WID_RV_LEFT_SCROLLBAR,                        ///< The scrollbar for the matrix on the left.
		WID_RV_RIGHT_MATRIX                          = ::WID_RV_RIGHT_MATRIX,                          ///< The matrix on the right.
		WID_RV_RIGHT_SCROLLBAR                       = ::WID_RV_RIGHT_SCROLLBAR,                       ///< The scrollbar for the matrix on the right.
		WID_RV_LEFT_DETAILS                          = ::WID_RV_LEFT_DETAILS,                          ///< Details of the entry on the left.
		WID_RV_RIGHT_DETAILS                         = ::WID_RV_RIGHT_DETAILS,                         ///< Details of the entry on the right.

		/* Button row. */
		WID_RV_START_REPLACE                         = ::WID_RV_START_REPLACE,                         ///< Start Replacing button.
		WID_RV_INFO_TAB                              = ::WID_RV_INFO_TAB,                              ///< Info tab.
		WID_RV_STOP_REPLACE                          = ::WID_RV_STOP_REPLACE,                          ///< Stop Replacing button.

		/* Train/road only widgets */
		WID_RV_RAIL_ROAD_TYPE_DROPDOWN               = ::WID_RV_RAIL_ROAD_TYPE_DROPDOWN,               ///< Dropdown menu about the rail/roadtype.

		/* Train only widgets. */
		WID_RV_TRAIN_ENGINEWAGON_DROPDOWN            = ::WID_RV_TRAIN_ENGINEWAGON_DROPDOWN,            ///< Dropdown to select engines and/or wagons.
		WID_RV_TRAIN_WAGONREMOVE_TOGGLE              = ::WID_RV_TRAIN_WAGONREMOVE_TOGGLE,              ///< Button to toggle removing wagons.
	};

	/* automatically generated from ../../widgets/bootstrap_widget.h */
	/** Widgets of the #BootstrapBackground class. */
	enum BootstrapBackgroundWidgets {
		WID_BB_BACKGROUND                            = ::WID_BB_BACKGROUND,                            ///< Background of the window.
	};

	/** Widgets of the #BootstrapErrmsgWindow class. */
	enum BootstrapErrorMessageWidgets {
		WID_BEM_CAPTION                              = ::WID_BEM_CAPTION,                              ///< Caption of the window.
		WID_BEM_MESSAGE                              = ::WID_BEM_MESSAGE,                              ///< Error message.
		WID_BEM_QUIT                                 = ::WID_BEM_QUIT,                                 ///< Quit button.
	};

	/** Widgets of the #BootstrapContentDownloadStatusWindow class. */
	enum BootstrapAskForDownloadWidgets {
		WID_BAFD_QUESTION                            = ::WID_BAFD_QUESTION,                            ///< The question whether to download.
		WID_BAFD_YES                                 = ::WID_BAFD_YES,                                 ///< An affirmative answer to the question.
		WID_BAFD_NO                                  = ::WID_BAFD_NO,                                  ///< An negative answer to the question.
	};

	/* automatically generated from ../../widgets/bridge_widget.h */
	/** Widgets of the #BuildBridgeWindow class. */
	enum BuildBridgeSelectionWidgets {
		WID_BBS_CAPTION                              = ::WID_BBS_CAPTION,                              ///< Caption of the window.
		WID_BBS_DROPDOWN_ORDER                       = ::WID_BBS_DROPDOWN_ORDER,                       ///< Direction of sort dropdown.
		WID_BBS_DROPDOWN_CRITERIA                    = ::WID_BBS_DROPDOWN_CRITERIA,                    ///< Criteria of sort dropdown.
		WID_BBS_BRIDGE_LIST                          = ::WID_BBS_BRIDGE_LIST,                          ///< List of bridges.
		WID_BBS_SCROLLBAR                            = ::WID_BBS_SCROLLBAR,                            ///< Scrollbar of the list.
	};

	/* automatically generated from ../../widgets/build_vehicle_widget.h */
	/** Widgets of the #BuildVehicleWindow class. */
	enum BuildVehicleWidgets {
		WID_BV_CAPTION                               = ::WID_BV_CAPTION,                               ///< Caption of window.
		WID_BV_SORT_ASCENDING_DESCENDING             = ::WID_BV_SORT_ASCENDING_DESCENDING,             ///< Sort direction.
		WID_BV_SORT_DROPDOWN                         = ::WID_BV_SORT_DROPDOWN,                         ///< Criteria of sorting dropdown.
		WID_BV_CARGO_FILTER_DROPDOWN                 = ::WID_BV_CARGO_FILTER_DROPDOWN,                 ///< Cargo filter dropdown.
		WID_BV_SHOW_HIDDEN_ENGINES                   = ::WID_BV_SHOW_HIDDEN_ENGINES,                   ///< Toggle whether to display the hidden vehicles.
		WID_BV_LIST                                  = ::WID_BV_LIST,                                  ///< List of vehicles.
		WID_BV_SCROLLBAR                             = ::WID_BV_SCROLLBAR,                             ///< Scrollbar of list.
		WID_BV_PANEL                                 = ::WID_BV_PANEL,                                 ///< Button panel.
		WID_BV_BUILD                                 = ::WID_BV_BUILD,                                 ///< Build panel.
		WID_BV_SHOW_HIDE                             = ::WID_BV_SHOW_HIDE,                             ///< Button to hide or show the selected engine.
		WID_BV_BUILD_SEL                             = ::WID_BV_BUILD_SEL,                             ///< Build button.
		WID_BV_RENAME                                = ::WID_BV_RENAME,                                ///< Rename button.

		WID_BV_CAPTION_LOCO                          = ::WID_BV_CAPTION_LOCO,                          ///< Caption of locomotive half of the window.
		WID_BV_SORT_ASCENDING_DESCENDING_LOCO        = ::WID_BV_SORT_ASCENDING_DESCENDING_LOCO,        ///< Sort direction.
		WID_BV_SORT_DROPDOWN_LOCO                    = ::WID_BV_SORT_DROPDOWN_LOCO,                    ///< Criteria of sorting dropdown.
		WID_BV_CARGO_FILTER_DROPDOWN_LOCO            = ::WID_BV_CARGO_FILTER_DROPDOWN_LOCO,            ///< Cargo filter dropdown.
		WID_BV_SHOW_HIDDEN_LOCOS                     = ::WID_BV_SHOW_HIDDEN_LOCOS,                     ///< Toggle whether to display the hidden locomotives.
		WID_BV_LIST_LOCO                             = ::WID_BV_LIST_LOCO,                             ///< List of vehicles.
		WID_BV_SCROLLBAR_LOCO                        = ::WID_BV_SCROLLBAR_LOCO,                        ///< Scrollbar of list.
		WID_BV_PANEL_LOCO                            = ::WID_BV_PANEL_LOCO,                            ///< Button panel.
		WID_BV_SHOW_HIDE_LOCO                        = ::WID_BV_SHOW_HIDE_LOCO,                        ///< Button to hide or show the selected locomotives.
		WID_BV_BUILD_LOCO                            = ::WID_BV_BUILD_LOCO,                            ///< Build panel.
		WID_BV_BUILD_SEL_LOCO                        = ::WID_BV_BUILD_SEL_LOCO,                        ///< Build button.
		WID_BV_RENAME_LOCO                           = ::WID_BV_RENAME_LOCO,                           ///< Rename button.

		WID_BV_CAPTION_WAGON                         = ::WID_BV_CAPTION_WAGON,                         ///< Caption of wagon half of the window.
		WID_BV_SORT_ASCENDING_DESCENDING_WAGON       = ::WID_BV_SORT_ASCENDING_DESCENDING_WAGON,       ///< Sort direction.
		WID_BV_SORT_DROPDOWN_WAGON                   = ::WID_BV_SORT_DROPDOWN_WAGON,                   ///< Criteria of sorting dropdown.
		WID_BV_CARGO_FILTER_DROPDOWN_WAGON           = ::WID_BV_CARGO_FILTER_DROPDOWN_WAGON,           ///< Cargo filter dropdown.
		WID_BV_SHOW_HIDDEN_WAGONS                    = ::WID_BV_SHOW_HIDDEN_WAGONS,                    ///< Toggle whether to display the hidden wagons.
		WID_BV_LIST_WAGON                            = ::WID_BV_LIST_WAGON,                            ///< List of vehicles.
		WID_BV_SCROLLBAR_WAGON                       = ::WID_BV_SCROLLBAR_WAGON,                       ///< Scrollbar of list.
		WID_BV_PANEL_WAGON                           = ::WID_BV_PANEL_WAGON,                           ///< Button panel.
		WID_BV_SHOW_HIDE_WAGON                       = ::WID_BV_SHOW_HIDE_WAGON,                       ///< Button to hide or show the selected wagons.
		WID_BV_BUILD_WAGON                           = ::WID_BV_BUILD_WAGON,                           ///< Build panel.
		WID_BV_BUILD_SEL_WAGON                       = ::WID_BV_BUILD_SEL_WAGON,                       ///< Build button.
		WID_BV_RENAME_WAGON                          = ::WID_BV_RENAME_WAGON,                          ///< Rename button.

		WID_BV_LOCO_BUTTONS_SEL                      = ::WID_BV_LOCO_BUTTONS_SEL,                      ///< Locomotive buttons selector.
		WID_BV_WAGON_BUTTONS_SEL                     = ::WID_BV_WAGON_BUTTONS_SEL,                     ///< Wagon buttons selector.

		WID_BV_COMB_BUTTONS_SEL                      = ::WID_BV_COMB_BUTTONS_SEL,                      ///< Combined buttons: section selector.
		WID_BV_COMB_BUILD_SEL                        = ::WID_BV_COMB_BUILD_SEL,                        ///< Combined buttons: build button selector.
		WID_BV_COMB_BUILD                            = ::WID_BV_COMB_BUILD,                            ///< Combined buttons: build button.
		WID_BV_COMB_SHOW_HIDE                        = ::WID_BV_COMB_SHOW_HIDE,                        ///< Combined buttons: show/hide button.
		WID_BV_COMB_RENAME                           = ::WID_BV_COMB_RENAME,                           ///< Combined buttons: rename button.
	};

	/* automatically generated from ../../widgets/cheat_widget.h */
	/** Widgets of the #CheatWindow class. */
	enum CheatWidgets {
		WID_C_NOTE                                   = ::WID_C_NOTE,                                   ///< Note on top of panel for use of cheat.
		WID_C_PANEL                                  = ::WID_C_PANEL,                                  ///< Panel where all cheats are shown in.
	};

	/* automatically generated from ../../widgets/company_widget.h */
	/** Widgets of the #CompanyWindow class. */
	enum CompanyWidgets {
		WID_C_CAPTION                                = ::WID_C_CAPTION,                                ///< Caption of the window.

		WID_C_FACE                                   = ::WID_C_FACE,                                   ///< View of the face.
		WID_C_FACE_TITLE                             = ::WID_C_FACE_TITLE,                             ///< Title for the face.

		WID_C_DESC_INAUGURATION                      = ::WID_C_DESC_INAUGURATION,                      ///< Inauguration.
		WID_C_DESC_COLOUR_SCHEME                     = ::WID_C_DESC_COLOUR_SCHEME,                     ///< Colour scheme.
		WID_C_DESC_COLOUR_SCHEME_EXAMPLE             = ::WID_C_DESC_COLOUR_SCHEME_EXAMPLE,             ///< Colour scheme example.
		WID_C_DESC_VEHICLE                           = ::WID_C_DESC_VEHICLE,                           ///< Vehicles.
		WID_C_DESC_VEHICLE_COUNTS                    = ::WID_C_DESC_VEHICLE_COUNTS,                    ///< Vehicle count.
		WID_C_DESC_COMPANY_VALUE                     = ::WID_C_DESC_COMPANY_VALUE,                     ///< Company value.
		WID_C_DESC_INFRASTRUCTURE                    = ::WID_C_DESC_INFRASTRUCTURE,                    ///< Infrastructure.
		WID_C_DESC_INFRASTRUCTURE_COUNTS             = ::WID_C_DESC_INFRASTRUCTURE_COUNTS,             ///< Infrastructure count.

		WID_C_SELECT_DESC_OWNERS                     = ::WID_C_SELECT_DESC_OWNERS,                     ///< Owners.
		WID_C_DESC_OWNERS                            = ::WID_C_DESC_OWNERS,                            ///< Owner in Owners.

		WID_C_SELECT_BUTTONS                         = ::WID_C_SELECT_BUTTONS,                         ///< Selection widget for the button bar.
		WID_C_NEW_FACE                               = ::WID_C_NEW_FACE,                               ///< Button to make new face.
		WID_C_COLOUR_SCHEME                          = ::WID_C_COLOUR_SCHEME,                          ///< Button to change colour scheme.
		WID_C_PRESIDENT_NAME                         = ::WID_C_PRESIDENT_NAME,                         ///< Button to change president name.
		WID_C_COMPANY_NAME                           = ::WID_C_COMPANY_NAME,                           ///< Button to change company name.
		WID_C_BUY_SHARE                              = ::WID_C_BUY_SHARE,                              ///< Button to buy a share.
		WID_C_SELL_SHARE                             = ::WID_C_SELL_SHARE,                             ///< Button to sell a share.

		WID_C_SELECT_VIEW_BUILD_HQ                   = ::WID_C_SELECT_VIEW_BUILD_HQ,                   ///< Panel about HQ.
		WID_C_VIEW_HQ                                = ::WID_C_VIEW_HQ,                                ///< Button to view the HQ.
		WID_C_BUILD_HQ                               = ::WID_C_BUILD_HQ,                               ///< Button to build the HQ.

		WID_C_SELECT_RELOCATE                        = ::WID_C_SELECT_RELOCATE,                        ///< Panel about 'Relocate HQ'.
		WID_C_RELOCATE_HQ                            = ::WID_C_RELOCATE_HQ,                            ///< Button to relocate the HQ.

		WID_C_VIEW_INFRASTRUCTURE                    = ::WID_C_VIEW_INFRASTRUCTURE,                    ///< Panel about infrastructure.

		WID_C_SELECT_GIVE_MONEY                      = ::WID_C_SELECT_GIVE_MONEY,                      ///< Selection widget for the give money button.
		WID_C_GIVE_MONEY                             = ::WID_C_GIVE_MONEY,                             ///< Button to give money.

		WID_C_HAS_PASSWORD                           = ::WID_C_HAS_PASSWORD,                           ///< Has company password lock.
		WID_C_SELECT_MULTIPLAYER                     = ::WID_C_SELECT_MULTIPLAYER,                     ///< Multiplayer selection panel.
		WID_C_COMPANY_PASSWORD                       = ::WID_C_COMPANY_PASSWORD,                       ///< Button to set company password.
		WID_C_COMPANY_JOIN                           = ::WID_C_COMPANY_JOIN,                           ///< Button to join company.
	};

	/** Widgets of the #CompanyFinancesWindow class. */
	enum CompanyFinancesWidgets {
		WID_CF_CAPTION                               = ::WID_CF_CAPTION,                               ///< Caption of the window.
		WID_CF_TOGGLE_SIZE                           = ::WID_CF_TOGGLE_SIZE,                           ///< Toggle windows size.
		WID_CF_SEL_PANEL                             = ::WID_CF_SEL_PANEL,                             ///< Select panel or nothing.
		WID_CF_EXPS_CATEGORY                         = ::WID_CF_EXPS_CATEGORY,                         ///< Column for expenses category strings.
		WID_CF_EXPS_PRICE1                           = ::WID_CF_EXPS_PRICE1,                           ///< Column for year Y-2 expenses.
		WID_CF_EXPS_PRICE2                           = ::WID_CF_EXPS_PRICE2,                           ///< Column for year Y-1 expenses.
		WID_CF_EXPS_PRICE3                           = ::WID_CF_EXPS_PRICE3,                           ///< Column for year Y expenses.
		WID_CF_TOTAL_PANEL                           = ::WID_CF_TOTAL_PANEL,                           ///< Panel for totals.
		WID_CF_SEL_MAXLOAN                           = ::WID_CF_SEL_MAXLOAN,                           ///< Selection of maxloan column.
		WID_CF_BALANCE_VALUE                         = ::WID_CF_BALANCE_VALUE,                         ///< Bank balance value.
		WID_CF_LOAN_VALUE                            = ::WID_CF_LOAN_VALUE,                            ///< Loan.
		WID_CF_BALANCE_LINE                          = ::WID_CF_BALANCE_LINE,                          ///< Available cash.
		WID_CF_OWN_VALUE                             = ::WID_CF_OWN_VALUE,                             ///< Own funds, not including loan.
		WID_CF_INTEREST_RATE                         = ::WID_CF_INTEREST_RATE,                         ///< Loan interest rate.
		WID_CF_MAXLOAN_VALUE                         = ::WID_CF_MAXLOAN_VALUE,                         ///< Max loan widget.
		WID_CF_SEL_BUTTONS                           = ::WID_CF_SEL_BUTTONS,                           ///< Selection of buttons.
		WID_CF_INCREASE_LOAN                         = ::WID_CF_INCREASE_LOAN,                         ///< Increase loan.
		WID_CF_REPAY_LOAN                            = ::WID_CF_REPAY_LOAN,                            ///< Decrease loan..
		WID_CF_INFRASTRUCTURE                        = ::WID_CF_INFRASTRUCTURE,                        ///< View company infrastructure.
	};

	/** Widgets of the #SelectCompanyLiveryWindow class. */
	enum SelectCompanyLiveryWidgets {
		WID_SCL_CAPTION                              = ::WID_SCL_CAPTION,                              ///< Caption of window.
		WID_SCL_CLASS_GENERAL                        = ::WID_SCL_CLASS_GENERAL,                        ///< Class general.
		WID_SCL_CLASS_RAIL                           = ::WID_SCL_CLASS_RAIL,                           ///< Class rail.
		WID_SCL_CLASS_ROAD                           = ::WID_SCL_CLASS_ROAD,                           ///< Class road.
		WID_SCL_CLASS_SHIP                           = ::WID_SCL_CLASS_SHIP,                           ///< Class ship.
		WID_SCL_CLASS_AIRCRAFT                       = ::WID_SCL_CLASS_AIRCRAFT,                       ///< Class aircraft.
		WID_SCL_GROUPS_RAIL                          = ::WID_SCL_GROUPS_RAIL,                          ///< Rail groups.
		WID_SCL_GROUPS_ROAD                          = ::WID_SCL_GROUPS_ROAD,                          ///< Road groups.
		WID_SCL_GROUPS_SHIP                          = ::WID_SCL_GROUPS_SHIP,                          ///< Ship groups.
		WID_SCL_GROUPS_AIRCRAFT                      = ::WID_SCL_GROUPS_AIRCRAFT,                      ///< Aircraft groups.
		WID_SCL_SPACER_DROPDOWN                      = ::WID_SCL_SPACER_DROPDOWN,                      ///< Spacer for dropdown.
		WID_SCL_PRI_COL_DROPDOWN                     = ::WID_SCL_PRI_COL_DROPDOWN,                     ///< Dropdown for primary colour.
		WID_SCL_SEC_COL_DROPDOWN                     = ::WID_SCL_SEC_COL_DROPDOWN,                     ///< Dropdown for secondary colour.
		WID_SCL_MATRIX                               = ::WID_SCL_MATRIX,                               ///< Matrix.
		WID_SCL_MATRIX_SCROLLBAR                     = ::WID_SCL_MATRIX_SCROLLBAR,                     ///< Matrix scrollbar.
	};

	/**
	 * Widgets of the #SelectCompanyManagerFaceWindow class.
	 * Do not change the order of the widgets from WID_SCMF_HAS_MOUSTACHE_EARRING to WID_SCMF_GLASSES_R,
	 * this order is needed for the WE_CLICK event of DrawFaceStringLabel().
	 */
	enum SelectCompanyManagerFaceWidgets {
		WID_SCMF_CAPTION                             = ::WID_SCMF_CAPTION,                             ///< Caption of window.
		WID_SCMF_TOGGLE_LARGE_SMALL                  = ::WID_SCMF_TOGGLE_LARGE_SMALL,                  ///< Toggle for large or small.
		WID_SCMF_SELECT_FACE                         = ::WID_SCMF_SELECT_FACE,                         ///< Select face.
		WID_SCMF_CANCEL                              = ::WID_SCMF_CANCEL,                              ///< Cancel.
		WID_SCMF_ACCEPT                              = ::WID_SCMF_ACCEPT,                              ///< Accept.
		WID_SCMF_MALE                                = ::WID_SCMF_MALE,                                ///< Male button in the simple view.
		WID_SCMF_FEMALE                              = ::WID_SCMF_FEMALE,                              ///< Female button in the simple view.
		WID_SCMF_MALE2                               = ::WID_SCMF_MALE2,                               ///< Male button in the advanced view.
		WID_SCMF_FEMALE2                             = ::WID_SCMF_FEMALE2,                             ///< Female button in the advanced view.
		WID_SCMF_SEL_LOADSAVE                        = ::WID_SCMF_SEL_LOADSAVE,                        ///< Selection to display the load/save/number buttons in the advanced view.
		WID_SCMF_SEL_MALEFEMALE                      = ::WID_SCMF_SEL_MALEFEMALE,                      ///< Selection to display the male/female buttons in the simple view.
		WID_SCMF_SEL_PARTS                           = ::WID_SCMF_SEL_PARTS,                           ///< Selection to display the buttons for setting each part of the face in the advanced view.
		WID_SCMF_RANDOM_NEW_FACE                     = ::WID_SCMF_RANDOM_NEW_FACE,                     ///< Create random new face.
		WID_SCMF_TOGGLE_LARGE_SMALL_BUTTON           = ::WID_SCMF_TOGGLE_LARGE_SMALL_BUTTON,           ///< Toggle for large or small.
		WID_SCMF_FACE                                = ::WID_SCMF_FACE,                                ///< Current face.
		WID_SCMF_LOAD                                = ::WID_SCMF_LOAD,                                ///< Load face.
		WID_SCMF_FACECODE                            = ::WID_SCMF_FACECODE,                            ///< Get the face code.
		WID_SCMF_SAVE                                = ::WID_SCMF_SAVE,                                ///< Save face.
		WID_SCMF_HAS_MOUSTACHE_EARRING_TEXT          = ::WID_SCMF_HAS_MOUSTACHE_EARRING_TEXT,          ///< Text about moustache and earring.
		WID_SCMF_TIE_EARRING_TEXT                    = ::WID_SCMF_TIE_EARRING_TEXT,                    ///< Text about tie and earring.
		WID_SCMF_LIPS_MOUSTACHE_TEXT                 = ::WID_SCMF_LIPS_MOUSTACHE_TEXT,                 ///< Text about lips and moustache.
		WID_SCMF_HAS_GLASSES_TEXT                    = ::WID_SCMF_HAS_GLASSES_TEXT,                    ///< Text about glasses.
		WID_SCMF_HAIR_TEXT                           = ::WID_SCMF_HAIR_TEXT,                           ///< Text about hair.
		WID_SCMF_EYEBROWS_TEXT                       = ::WID_SCMF_EYEBROWS_TEXT,                       ///< Text about eyebrows.
		WID_SCMF_EYECOLOUR_TEXT                      = ::WID_SCMF_EYECOLOUR_TEXT,                      ///< Text about eyecolour.
		WID_SCMF_GLASSES_TEXT                        = ::WID_SCMF_GLASSES_TEXT,                        ///< Text about glasses.
		WID_SCMF_NOSE_TEXT                           = ::WID_SCMF_NOSE_TEXT,                           ///< Text about nose.
		WID_SCMF_CHIN_TEXT                           = ::WID_SCMF_CHIN_TEXT,                           ///< Text about chin.
		WID_SCMF_JACKET_TEXT                         = ::WID_SCMF_JACKET_TEXT,                         ///< Text about jacket.
		WID_SCMF_COLLAR_TEXT                         = ::WID_SCMF_COLLAR_TEXT,                         ///< Text about collar.
		WID_SCMF_ETHNICITY_EUR                       = ::WID_SCMF_ETHNICITY_EUR,                       ///< Text about ethnicity european.
		WID_SCMF_ETHNICITY_AFR                       = ::WID_SCMF_ETHNICITY_AFR,                       ///< Text about ethnicity african.
		WID_SCMF_HAS_MOUSTACHE_EARRING               = ::WID_SCMF_HAS_MOUSTACHE_EARRING,               ///< Has moustache or earring.
		WID_SCMF_HAS_GLASSES                         = ::WID_SCMF_HAS_GLASSES,                         ///< Has glasses.
		WID_SCMF_EYECOLOUR_L                         = ::WID_SCMF_EYECOLOUR_L,                         ///< Eyecolour left.
		WID_SCMF_EYECOLOUR                           = ::WID_SCMF_EYECOLOUR,                           ///< Eyecolour.
		WID_SCMF_EYECOLOUR_R                         = ::WID_SCMF_EYECOLOUR_R,                         ///< Eyecolour right.
		WID_SCMF_CHIN_L                              = ::WID_SCMF_CHIN_L,                              ///< Chin left.
		WID_SCMF_CHIN                                = ::WID_SCMF_CHIN,                                ///< Chin.
		WID_SCMF_CHIN_R                              = ::WID_SCMF_CHIN_R,                              ///< Chin right.
		WID_SCMF_EYEBROWS_L                          = ::WID_SCMF_EYEBROWS_L,                          ///< Eyebrows left.
		WID_SCMF_EYEBROWS                            = ::WID_SCMF_EYEBROWS,                            ///< Eyebrows.
		WID_SCMF_EYEBROWS_R                          = ::WID_SCMF_EYEBROWS_R,                          ///< Eyebrows right.
		WID_SCMF_LIPS_MOUSTACHE_L                    = ::WID_SCMF_LIPS_MOUSTACHE_L,                    ///< Lips / Moustache left.
		WID_SCMF_LIPS_MOUSTACHE                      = ::WID_SCMF_LIPS_MOUSTACHE,                      ///< Lips / Moustache.
		WID_SCMF_LIPS_MOUSTACHE_R                    = ::WID_SCMF_LIPS_MOUSTACHE_R,                    ///< Lips / Moustache right.
		WID_SCMF_NOSE_L                              = ::WID_SCMF_NOSE_L,                              ///< Nose left.
		WID_SCMF_NOSE                                = ::WID_SCMF_NOSE,                                ///< Nose.
		WID_SCMF_NOSE_R                              = ::WID_SCMF_NOSE_R,                              ///< Nose right.
		WID_SCMF_HAIR_L                              = ::WID_SCMF_HAIR_L,                              ///< Hair left.
		WID_SCMF_HAIR                                = ::WID_SCMF_HAIR,                                ///< Hair.
		WID_SCMF_HAIR_R                              = ::WID_SCMF_HAIR_R,                              ///< Hair right.
		WID_SCMF_JACKET_L                            = ::WID_SCMF_JACKET_L,                            ///< Jacket left.
		WID_SCMF_JACKET                              = ::WID_SCMF_JACKET,                              ///< Jacket.
		WID_SCMF_JACKET_R                            = ::WID_SCMF_JACKET_R,                            ///< Jacket right.
		WID_SCMF_COLLAR_L                            = ::WID_SCMF_COLLAR_L,                            ///< Collar left.
		WID_SCMF_COLLAR                              = ::WID_SCMF_COLLAR,                              ///< Collar.
		WID_SCMF_COLLAR_R                            = ::WID_SCMF_COLLAR_R,                            ///< Collar right.
		WID_SCMF_TIE_EARRING_L                       = ::WID_SCMF_TIE_EARRING_L,                       ///< Tie / Earring left.
		WID_SCMF_TIE_EARRING                         = ::WID_SCMF_TIE_EARRING,                         ///< Tie / Earring.
		WID_SCMF_TIE_EARRING_R                       = ::WID_SCMF_TIE_EARRING_R,                       ///< Tie / Earring right.
		WID_SCMF_GLASSES_L                           = ::WID_SCMF_GLASSES_L,                           ///< Glasses left.
		WID_SCMF_GLASSES                             = ::WID_SCMF_GLASSES,                             ///< Glasses.
		WID_SCMF_GLASSES_R                           = ::WID_SCMF_GLASSES_R,                           ///< Glasses right.
	};

	/** Widgets of the #CompanyInfrastructureWindow class. */
	enum CompanyInfrastructureWidgets {
		WID_CI_CAPTION                               = ::WID_CI_CAPTION,                               ///< Caption of window.
		WID_CI_DESC                                  = ::WID_CI_DESC,                                  ///< Description.
		WID_CI_COUNT                                 = ::WID_CI_COUNT,                                 ///< Count.
		WID_CI_SCROLLBAR                             = ::WID_CI_SCROLLBAR,                             ///< Scrollbar.
	};

	/** Widgets of the #BuyCompanyWindow class. */
	enum BuyCompanyWidgets {
		WID_BC_CAPTION                               = ::WID_BC_CAPTION,                               ///< Caption of window.
		WID_BC_FACE                                  = ::WID_BC_FACE,                                  ///< Face button.
		WID_BC_QUESTION                              = ::WID_BC_QUESTION,                              ///< Question text.
		WID_BC_NO                                    = ::WID_BC_NO,                                    ///< No button.
		WID_BC_YES                                   = ::WID_BC_YES,                                   ///< Yes button.
	};

	/* automatically generated from ../../widgets/console_widget.h */
	/** Widgets of the #IConsoleWindow class. */
	enum ConsoleWidgets {
		WID_C_BACKGROUND                             = ::WID_C_BACKGROUND,                             ///< Background of the console.
	};

	/* automatically generated from ../../widgets/date_widget.h */
	/** Widgets of the #SetDateWindow class. */
	enum SetDateWidgets {
		WID_SD_DAY                                   = ::WID_SD_DAY,                                   ///< Dropdown for the day.
		WID_SD_MONTH                                 = ::WID_SD_MONTH,                                 ///< Dropdown for the month.
		WID_SD_YEAR                                  = ::WID_SD_YEAR,                                  ///< Dropdown for the year.
		WID_SD_SET_DATE                              = ::WID_SD_SET_DATE,                              ///< Actually set the date.
	};

	/* automatically generated from ../../widgets/departures_widget.h */
	/** Widgets of the WC_DEPARTURES_BOARD. */
	enum DeparturesWindowWidgets {
		WID_DB_CAPTION                               = ::WID_DB_CAPTION,                               ///< Window caption
		WID_DB_LIST                                  = ::WID_DB_LIST,                                  ///< List of departures
		WID_DB_SCROLLBAR                             = ::WID_DB_SCROLLBAR,                             ///< List scrollbar
		WID_DB_SHOW_PAX                              = ::WID_DB_SHOW_PAX,                              ///< Toggle passenger departures button
		WID_DB_SHOW_FREIGHT                          = ::WID_DB_SHOW_FREIGHT,                          ///< Toggle freight button
		WID_DB_SHOW_DEPS                             = ::WID_DB_SHOW_DEPS,                             ///< Toggle departures button
		WID_DB_SHOW_ARRS                             = ::WID_DB_SHOW_ARRS,                             ///< Toggle arrivals button
		WID_DB_SHOW_VIA                              = ::WID_DB_SHOW_VIA,                              ///< Toggle via button
		WID_DB_SHOW_TRAINS                           = ::WID_DB_SHOW_TRAINS,                           ///< Toggle trains button
		WID_DB_SHOW_ROADVEHS                         = ::WID_DB_SHOW_ROADVEHS,                         ///< Toggle road vehicles button
		WID_DB_SHOW_SHIPS                            = ::WID_DB_SHOW_SHIPS,                            ///< Toggle ships button
		WID_DB_SHOW_PLANES                           = ::WID_DB_SHOW_PLANES,                           ///< Toggle planes button
	};

	/* automatically generated from ../../widgets/depot_widget.h */
	/** Widgets of the #DepotWindow class. */
	enum DepotWidgets {
		WID_D_CAPTION                                = ::WID_D_CAPTION,                                ///< Caption of window.
		WID_D_SELL                                   = ::WID_D_SELL,                                   ///< Sell button.
		WID_D_SHOW_SELL_CHAIN                        = ::WID_D_SHOW_SELL_CHAIN,                        ///< Show sell chain panel.
		WID_D_SELL_CHAIN                             = ::WID_D_SELL_CHAIN,                             ///< Sell chain button.
		WID_D_SELL_ALL                               = ::WID_D_SELL_ALL,                               ///< Sell all button.
		WID_D_AUTOREPLACE                            = ::WID_D_AUTOREPLACE,                            ///< Autoreplace button.
		WID_D_MATRIX                                 = ::WID_D_MATRIX,                                 ///< Matrix of vehicles.
		WID_D_V_SCROLL                               = ::WID_D_V_SCROLL,                               ///< Vertical scrollbar.
		WID_D_SHOW_H_SCROLL                          = ::WID_D_SHOW_H_SCROLL,                          ///< Show horizontal scrollbar panel.
		WID_D_H_SCROLL                               = ::WID_D_H_SCROLL,                               ///< Horizontal scrollbar.
		WID_D_BUILD                                  = ::WID_D_BUILD,                                  ///< Build button.
		WID_D_CLONE                                  = ::WID_D_CLONE,                                  ///< Clone button.
		WID_D_LOCATION                               = ::WID_D_LOCATION,                               ///< Location button.
		WID_D_SHOW_RENAME                            = ::WID_D_SHOW_RENAME,                            ///< Show rename panel.
		WID_D_RENAME                                 = ::WID_D_RENAME,                                 ///< Rename button.
		WID_D_VEHICLE_LIST                           = ::WID_D_VEHICLE_LIST,                           ///< List of vehicles.
		WID_D_STOP_ALL                               = ::WID_D_STOP_ALL,                               ///< Stop all button.
		WID_D_START_ALL                              = ::WID_D_START_ALL,                              ///< Start all button.
	};

	/* automatically generated from ../../widgets/dock_widget.h */
	/** Widgets of the #BuildDocksDepotWindow class. */
	enum BuildDockDepotWidgets {
		WID_BDD_BACKGROUND                           = ::WID_BDD_BACKGROUND,                           ///< Background of the window.
		WID_BDD_X                                    = ::WID_BDD_X,                                    ///< X-direction button.
		WID_BDD_Y                                    = ::WID_BDD_Y,                                    ///< Y-direction button.
	};

	/** Widgets of the #BuildDocksToolbarWindow class. */
	enum DockToolbarWidgets {
		WID_DT_CANAL                                 = ::WID_DT_CANAL,                                 ///< Build canal button.
		WID_DT_LOCK                                  = ::WID_DT_LOCK,                                  ///< Build lock button.
		WID_DT_DEMOLISH                              = ::WID_DT_DEMOLISH,                              ///< Demolish aka dynamite button.
		WID_DT_DEPOT                                 = ::WID_DT_DEPOT,                                 ///< Build depot button.
		WID_DT_STATION                               = ::WID_DT_STATION,                               ///< Build station button.
		WID_DT_BUOY                                  = ::WID_DT_BUOY,                                  ///< Build buoy button.
		WID_DT_RIVER                                 = ::WID_DT_RIVER,                                 ///< Build river button (in scenario editor).
		WID_DT_BUILD_AQUEDUCT                        = ::WID_DT_BUILD_AQUEDUCT,                        ///< Build aqueduct button.
		WID_DT_RIVER_SEL                             = ::WID_DT_RIVER_SEL,                             ///< Build river button selector.

		WID_DT_INVALID                               = ::WID_DT_INVALID,                               ///< Used to initialize a variable.
	};

	/* automatically generated from ../../widgets/dropdown_widget.h */
	/** Widgets of the #DropdownWindow class. */
	enum DropdownMenuWidgets {
		WID_DM_ITEMS                                 = ::WID_DM_ITEMS,                                 ///< Panel showing the dropdown items.
		WID_DM_SHOW_SCROLL                           = ::WID_DM_SHOW_SCROLL,                           ///< Hide scrollbar if too few items.
		WID_DM_SCROLL                                = ::WID_DM_SCROLL,                                ///< Scrollbar.
	};

	/* automatically generated from ../../widgets/engine_widget.h */
	/** Widgets of the #EnginePreviewWindow class. */
	enum EnginePreviewWidgets {
		WID_EP_QUESTION                              = ::WID_EP_QUESTION,                              ///< The container for the question.
		WID_EP_NO                                    = ::WID_EP_NO,                                    ///< No button.
		WID_EP_YES                                   = ::WID_EP_YES,                                   ///< Yes button.
	};

	/* automatically generated from ../../widgets/error_widget.h */
	/** Widgets of the #ErrmsgWindow class. */
	enum ErrorMessageWidgets {
		WID_EM_CAPTION                               = ::WID_EM_CAPTION,                               ///< Caption of the window.
		WID_EM_FACE                                  = ::WID_EM_FACE,                                  ///< Error title.
		WID_EM_MESSAGE                               = ::WID_EM_MESSAGE,                               ///< Error message.
	};

	/* automatically generated from ../../widgets/fios_widget.h */
	/** Widgets of the #SaveLoadWindow class. */
	enum SaveLoadWidgets {
		WID_SL_CAPTION                               = ::WID_SL_CAPTION,                               ///< Caption of the window.
		WID_SL_SORT_BYNAME                           = ::WID_SL_SORT_BYNAME,                           ///< Sort by name button.
		WID_SL_SORT_BYDATE                           = ::WID_SL_SORT_BYDATE,                           ///< Sort by date button.
		WID_SL_FILTER                                = ::WID_SL_FILTER,                                ///< Filter list of files
		WID_SL_BACKGROUND                            = ::WID_SL_BACKGROUND,                            ///< Background of window.
		WID_SL_FILE_BACKGROUND                       = ::WID_SL_FILE_BACKGROUND,                       ///< Background of file selection.
		WID_SL_HOME_BUTTON                           = ::WID_SL_HOME_BUTTON,                           ///< Home button.
		WID_SL_DRIVES_DIRECTORIES_LIST               = ::WID_SL_DRIVES_DIRECTORIES_LIST,               ///< Drives list.
		WID_SL_SCROLLBAR                             = ::WID_SL_SCROLLBAR,                             ///< Scrollbar of the file list.
		WID_SL_CONTENT_DOWNLOAD                      = ::WID_SL_CONTENT_DOWNLOAD,                      ///< Content download button, only available for play scenario/heightmap.
		WID_SL_SAVE_OSK_TITLE                        = ::WID_SL_SAVE_OSK_TITLE,                        ///< Title textbox, only available for save operations.
		WID_SL_DELETE_SELECTION                      = ::WID_SL_DELETE_SELECTION,                      ///< Delete button, only available for save operations.
		WID_SL_SAVE_GAME                             = ::WID_SL_SAVE_GAME,                             ///< Save button, only available for save operations.
		WID_SL_CONTENT_DOWNLOAD_SEL                  = ::WID_SL_CONTENT_DOWNLOAD_SEL,                  ///< Selection 'stack' to 'hide' the content download.
		WID_SL_DETAILS                               = ::WID_SL_DETAILS,                               ///< Panel with game details.
		WID_SL_NEWGRF_INFO                           = ::WID_SL_NEWGRF_INFO,                           ///< Button to open NewGgrf configuration.
		WID_SL_LOAD_BUTTON                           = ::WID_SL_LOAD_BUTTON,                           ///< Button to load game/scenario.
		WID_SL_MISSING_NEWGRFS                       = ::WID_SL_MISSING_NEWGRFS,                       ///< Button to find missing NewGRFs online.
	};

	/* automatically generated from ../../widgets/framerate_widget.h */
	/** Widgets of the #FramerateWindow class. */
	enum FramerateWindowWidgets {
		WID_FRW_CAPTION                              = ::WID_FRW_CAPTION,
		WID_FRW_RATE_GAMELOOP                        = ::WID_FRW_RATE_GAMELOOP,
		WID_FRW_RATE_DRAWING                         = ::WID_FRW_RATE_DRAWING,
		WID_FRW_RATE_FACTOR                          = ::WID_FRW_RATE_FACTOR,
		WID_FRW_INFO_DATA_POINTS                     = ::WID_FRW_INFO_DATA_POINTS,
		WID_FRW_TIMES_NAMES                          = ::WID_FRW_TIMES_NAMES,
		WID_FRW_TIMES_CURRENT                        = ::WID_FRW_TIMES_CURRENT,
		WID_FRW_TIMES_AVERAGE                        = ::WID_FRW_TIMES_AVERAGE,
		WID_FRW_ALLOCSIZE                            = ::WID_FRW_ALLOCSIZE,
		WID_FRW_SEL_MEMORY                           = ::WID_FRW_SEL_MEMORY,
		WID_FRW_SCROLLBAR                            = ::WID_FRW_SCROLLBAR,
	};

	/** Widgets of the #FrametimeGraphWindow class. */
	enum FrametimeGraphWindowWidgets {
		WID_FGW_CAPTION                              = ::WID_FGW_CAPTION,
		WID_FGW_GRAPH                                = ::WID_FGW_GRAPH,
	};

	/* automatically generated from ../../widgets/game_widget.h */
	/** Widgets of the #GSConfigWindow class. */
	enum GSConfigWidgets {
		WID_GSC_BACKGROUND                           = ::WID_GSC_BACKGROUND,                           ///< Window background.
		WID_GSC_GSLIST                               = ::WID_GSC_GSLIST,                               ///< List with current selected Game Script.
		WID_GSC_SETTINGS                             = ::WID_GSC_SETTINGS,                             ///< Panel to draw the Game Script settings on
		WID_GSC_SCROLLBAR                            = ::WID_GSC_SCROLLBAR,                            ///< Scrollbar to scroll through the selected AIs.
		WID_GSC_CHANGE                               = ::WID_GSC_CHANGE,                               ///< Select another Game Script button.
		WID_GSC_TEXTFILE                             = ::WID_GSC_TEXTFILE,                             ///< Open GS readme, changelog (+1) or license (+2).
		WID_GSC_CONTENT_DOWNLOAD                     = ::WID_GSC_CONTENT_DOWNLOAD,                     ///< Download content button.
		WID_GSC_ACCEPT                               = ::WID_GSC_ACCEPT,                               ///< Accept ("Close") button
		WID_GSC_RESET                                = ::WID_GSC_RESET,                                ///< Reset button.
	};

	/* automatically generated from ../../widgets/genworld_widget.h */
	/** Widgets of the #GenerateLandscapeWindow class. */
	enum GenerateLandscapeWidgets {
		WID_GL_TEMPERATE                             = ::WID_GL_TEMPERATE,                             ///< Button with icon "Temperate".
		WID_GL_ARCTIC                                = ::WID_GL_ARCTIC,                                ///< Button with icon "Arctic".
		WID_GL_TROPICAL                              = ::WID_GL_TROPICAL,                              ///< Button with icon "Tropical".
		WID_GL_TOYLAND                               = ::WID_GL_TOYLAND,                               ///< Button with icon "Toyland".

		WID_GL_MAPSIZE_X_PULLDOWN                    = ::WID_GL_MAPSIZE_X_PULLDOWN,                    ///< Dropdown 'map X size'.
		WID_GL_MAPSIZE_Y_PULLDOWN                    = ::WID_GL_MAPSIZE_Y_PULLDOWN,                    ///< Dropdown 'map Y size'.

		WID_GL_TOWN_PULLDOWN                         = ::WID_GL_TOWN_PULLDOWN,                         ///< Dropdown 'No. of towns'.
		WID_GL_TOWNNAME_DROPDOWN                     = ::WID_GL_TOWNNAME_DROPDOWN,                     ///< Dropdown 'Townnames'.
		WID_GL_INDUSTRY_PULLDOWN                     = ::WID_GL_INDUSTRY_PULLDOWN,                     ///< Dropdown 'No. of industries'.

		WID_GL_GENERATE_BUTTON                       = ::WID_GL_GENERATE_BUTTON,                       ///< 'Generate' button.

		WID_GL_HEIGHTMAP_HEIGHT_DOWN                 = ::WID_GL_HEIGHTMAP_HEIGHT_DOWN,                 ///< Decrease heightmap highest mountain
		WID_GL_HEIGHTMAP_HEIGHT_TEXT                 = ::WID_GL_HEIGHTMAP_HEIGHT_TEXT,                 ///< Max. heightmap highest mountain
		WID_GL_HEIGHTMAP_HEIGHT_UP                   = ::WID_GL_HEIGHTMAP_HEIGHT_UP,                   ///< Increase max. heightmap highest mountain

		WID_GL_START_DATE_DOWN                       = ::WID_GL_START_DATE_DOWN,                       ///< Decrease start year.
		WID_GL_START_DATE_TEXT                       = ::WID_GL_START_DATE_TEXT,                       ///< Start year.
		WID_GL_START_DATE_UP                         = ::WID_GL_START_DATE_UP,                         ///< Increase start year.

		WID_GL_SNOW_COVERAGE_DOWN                    = ::WID_GL_SNOW_COVERAGE_DOWN,                    ///< Decrease snow coverage.
		WID_GL_SNOW_COVERAGE_TEXT                    = ::WID_GL_SNOW_COVERAGE_TEXT,                    ///< Snow coverage.
		WID_GL_SNOW_COVERAGE_UP                      = ::WID_GL_SNOW_COVERAGE_UP,                      ///< Increase snow coverage.

		WID_GL_DESERT_COVERAGE_DOWN                  = ::WID_GL_DESERT_COVERAGE_DOWN,                  ///< Decrease desert coverage.
		WID_GL_DESERT_COVERAGE_TEXT                  = ::WID_GL_DESERT_COVERAGE_TEXT,                  ///< Desert coverage.
		WID_GL_DESERT_COVERAGE_UP                    = ::WID_GL_DESERT_COVERAGE_UP,                    ///< Increase desert coverage.

		WID_GL_SNOW_LEVEL_DOWN                       = ::WID_GL_SNOW_LEVEL_DOWN,                       ///< Decrease snow level.
		WID_GL_SNOW_LEVEL_TEXT                       = ::WID_GL_SNOW_LEVEL_TEXT,                       ///< Snow level.
		WID_GL_SNOW_LEVEL_UP                         = ::WID_GL_SNOW_LEVEL_UP,                         ///< Increase snow level.

		WID_GL_RAINFOREST_LEVEL_DOWN                 = ::WID_GL_RAINFOREST_LEVEL_DOWN,                 ///< Decrease rainforest level.
		WID_GL_RAINFOREST_LEVEL_TEXT                 = ::WID_GL_RAINFOREST_LEVEL_TEXT,                 ///< Rainforest level.
		WID_GL_RAINFOREST_LEVEL_UP                   = ::WID_GL_RAINFOREST_LEVEL_UP,                   ///< Increase rainforest level.

		WID_GL_LANDSCAPE_PULLDOWN                    = ::WID_GL_LANDSCAPE_PULLDOWN,                    ///< Dropdown 'Land generator'.

		WID_GL_HEIGHTMAP_NAME_TEXT                   = ::WID_GL_HEIGHTMAP_NAME_TEXT,                   ///< Heightmap name.
		WID_GL_HEIGHTMAP_SIZE_TEXT                   = ::WID_GL_HEIGHTMAP_SIZE_TEXT,                   ///< Size of heightmap.
		WID_GL_HEIGHTMAP_ROTATION_PULLDOWN           = ::WID_GL_HEIGHTMAP_ROTATION_PULLDOWN,           ///< Dropdown 'Heightmap rotation'.

		WID_GL_TERRAIN_PULLDOWN                      = ::WID_GL_TERRAIN_PULLDOWN,                      ///< Dropdown 'Terrain type'.
		WID_GL_WATER_PULLDOWN                        = ::WID_GL_WATER_PULLDOWN,                        ///< Dropdown 'Sea level'.
		WID_GL_RIVER_PULLDOWN                        = ::WID_GL_RIVER_PULLDOWN,                        ///< Dropdown 'Rivers'.
		WID_GL_SMOOTHNESS_PULLDOWN                   = ::WID_GL_SMOOTHNESS_PULLDOWN,                   ///< Dropdown 'Smoothness'.
		WID_GL_VARIETY_PULLDOWN                      = ::WID_GL_VARIETY_PULLDOWN,                      ///< Dropdown 'Variety distribution'.

		WID_GL_BORDERS_RANDOM                        = ::WID_GL_BORDERS_RANDOM,                        ///< 'Random'/'Manual' borders.
		WID_GL_WATER_NW                              = ::WID_GL_WATER_NW,                              ///< NW 'Water'/'Freeform'.
		WID_GL_WATER_NE                              = ::WID_GL_WATER_NE,                              ///< NE 'Water'/'Freeform'.
		WID_GL_WATER_SE                              = ::WID_GL_WATER_SE,                              ///< SE 'Water'/'Freeform'.
		WID_GL_WATER_SW                              = ::WID_GL_WATER_SW,                              ///< SW 'Water'/'Freeform'.

		WID_GL_AI_BUTTON                             = ::WID_GL_AI_BUTTON,                             ///< 'AI Settings' button.
		WID_GL_GS_BUTTON                             = ::WID_GL_GS_BUTTON,                             ///< 'Game Script Settings' button.
		WID_GL_NEWGRF_BUTTON                         = ::WID_GL_NEWGRF_BUTTON,                         ///< 'NewGRF Settings' button.

		WID_GL_CLIMATE_SEL_LABEL                     = ::WID_GL_CLIMATE_SEL_LABEL,                     ///< NWID_SELECTION for snow or desert coverage label
		WID_GL_CLIMATE_SEL_SELECTOR                  = ::WID_GL_CLIMATE_SEL_SELECTOR,                  ///< NWID_SELECTION for snow or desert coverage selector
	};

	/** Widgets of the #CreateScenarioWindow class. */
	enum CreateScenarioWidgets {
		WID_CS_TEMPERATE                             = ::WID_CS_TEMPERATE,                             ///< Select temperate landscape style.
		WID_CS_ARCTIC                                = ::WID_CS_ARCTIC,                                ///< Select arctic landscape style.
		WID_CS_TROPICAL                              = ::WID_CS_TROPICAL,                              ///< Select tropical landscape style.
		WID_CS_TOYLAND                               = ::WID_CS_TOYLAND,                               ///< Select toy-land landscape style.
		WID_CS_EMPTY_WORLD                           = ::WID_CS_EMPTY_WORLD,                           ///< Generate an empty flat world.
		WID_CS_RANDOM_WORLD                          = ::WID_CS_RANDOM_WORLD,                          ///< Generate random land button
		WID_CS_MAPSIZE_X_PULLDOWN                    = ::WID_CS_MAPSIZE_X_PULLDOWN,                    ///< Pull-down arrow for x map size.
		WID_CS_MAPSIZE_Y_PULLDOWN                    = ::WID_CS_MAPSIZE_Y_PULLDOWN,                    ///< Pull-down arrow for y map size.
		WID_CS_START_DATE_DOWN                       = ::WID_CS_START_DATE_DOWN,                       ///< Decrease start year (start earlier).
		WID_CS_START_DATE_TEXT                       = ::WID_CS_START_DATE_TEXT,                       ///< Clickable start date value.
		WID_CS_START_DATE_UP                         = ::WID_CS_START_DATE_UP,                         ///< Increase start year (start later).
		WID_CS_FLAT_LAND_HEIGHT_DOWN                 = ::WID_CS_FLAT_LAND_HEIGHT_DOWN,                 ///< Decrease flat land height.
		WID_CS_FLAT_LAND_HEIGHT_TEXT                 = ::WID_CS_FLAT_LAND_HEIGHT_TEXT,                 ///< Clickable flat land height value.
		WID_CS_FLAT_LAND_HEIGHT_UP                   = ::WID_CS_FLAT_LAND_HEIGHT_UP,                   ///< Increase flat land height.
	};

	/** Widgets of the #GenerateProgressWindow class. */
	enum GenerationProgressWidgets {
		WID_GP_PROGRESS_BAR                          = ::WID_GP_PROGRESS_BAR,                          ///< Progress bar.
		WID_GP_PROGRESS_TEXT                         = ::WID_GP_PROGRESS_TEXT,                         ///< Text with the progress bar.
		WID_GP_ABORT                                 = ::WID_GP_ABORT,                                 ///< Abort button.
	};

	/* automatically generated from ../../widgets/goal_widget.h */
	/** Widgets of the #GoalListWindow class. */
	enum GoalListWidgets {
		WID_GOAL_CAPTION                             = ::WID_GOAL_CAPTION,                             ///< Caption of the window.
		WID_GOAL_SELECT_BUTTONS                      = ::WID_GOAL_SELECT_BUTTONS,                      ///< Selection widget for the title bar button.
		WID_GOAL_GLOBAL_BUTTON                       = ::WID_GOAL_GLOBAL_BUTTON,                       ///< Button to show global goals.
		WID_GOAL_COMPANY_BUTTON                      = ::WID_GOAL_COMPANY_BUTTON,                      ///< Button to show company goals.
		WID_GOAL_LIST                                = ::WID_GOAL_LIST,                                ///< Goal list.
		WID_GOAL_SCROLLBAR                           = ::WID_GOAL_SCROLLBAR,                           ///< Scrollbar of the goal list.
	};

	/** Widgets of the #GoalQuestionWindow class. */
	enum GoalQuestionWidgets {
		WID_GQ_CAPTION                               = ::WID_GQ_CAPTION,                               ///< Caption of the window.
		WID_GQ_QUESTION                              = ::WID_GQ_QUESTION,                              ///< Question text.
		WID_GQ_BUTTONS                               = ::WID_GQ_BUTTONS,                               ///< Buttons selection (between 1, 2 or 3).
		WID_GQ_BUTTON_1                              = ::WID_GQ_BUTTON_1,                              ///< First button.
		WID_GQ_BUTTON_2                              = ::WID_GQ_BUTTON_2,                              ///< Second button.
		WID_GQ_BUTTON_3                              = ::WID_GQ_BUTTON_3,                              ///< Third button.
		WID_GQ_BUTTON_SPACER                         = ::WID_GQ_BUTTON_SPACER,                         ///< Selection to hide extra padding if there are no buttons
	};

	/* automatically generated from ../../widgets/graph_widget.h */
	/** Widgets of the #GraphLegendWindow class. */
	enum GraphLegendWidgets {
		WID_GL_BACKGROUND                            = ::WID_GL_BACKGROUND,                            ///< Background of the window.

		WID_GL_FIRST_COMPANY                         = ::WID_GL_FIRST_COMPANY,                         ///< First company in the legend.
		WID_GL_LAST_COMPANY                          = ::WID_GL_LAST_COMPANY,                          ///< Last company in the legend.
	};

	/** Widgets of the #OperatingProfitGraphWindow class, #IncomeGraphWindow class, #DeliveredCargoGraphWindow class, and #CompanyValueGraphWindow class. */
	enum CompanyValueWidgets {
		WID_CV_KEY_BUTTON                            = ::WID_CV_KEY_BUTTON,                            ///< Key button.
		WID_CV_BACKGROUND                            = ::WID_CV_BACKGROUND,                            ///< Background of the window.
		WID_CV_GRAPH                                 = ::WID_CV_GRAPH,                                 ///< Graph itself.
		WID_CV_RESIZE                                = ::WID_CV_RESIZE,                                ///< Resize button.
	};

	/** Widget of the #PerformanceHistoryGraphWindow class. */
	enum PerformanceHistoryGraphWidgets {
		WID_PHG_KEY                                  = ::WID_PHG_KEY,                                  ///< Key button.
		WID_PHG_DETAILED_PERFORMANCE                 = ::WID_PHG_DETAILED_PERFORMANCE,                 ///< Detailed performance.
		WID_PHG_BACKGROUND                           = ::WID_PHG_BACKGROUND,                           ///< Background of the window.
		WID_PHG_GRAPH                                = ::WID_PHG_GRAPH,                                ///< Graph itself.
		WID_PHG_RESIZE                               = ::WID_PHG_RESIZE,                               ///< Resize button.
	};

	/** Widget of the #PaymentRatesGraphWindow class. */
	enum CargoPaymentRatesWidgets {
		WID_CPR_BACKGROUND                           = ::WID_CPR_BACKGROUND,                           ///< Background of the window.
		WID_CPR_HEADER                               = ::WID_CPR_HEADER,                               ///< Header.
		WID_CPR_GRAPH                                = ::WID_CPR_GRAPH,                                ///< Graph itself.
		WID_CPR_RESIZE                               = ::WID_CPR_RESIZE,                               ///< Resize button.
		WID_CPR_FOOTER                               = ::WID_CPR_FOOTER,                               ///< Footer.
		WID_CPR_ENABLE_CARGOES                       = ::WID_CPR_ENABLE_CARGOES,                       ///< Enable cargoes button.
		WID_CPR_DISABLE_CARGOES                      = ::WID_CPR_DISABLE_CARGOES,                      ///< Disable cargoes button.
		WID_CPR_MATRIX                               = ::WID_CPR_MATRIX,                               ///< Cargo list.
		WID_CPR_MATRIX_SCROLLBAR                     = ::WID_CPR_MATRIX_SCROLLBAR,                     ///< Cargo list scrollbar.
		WID_CPR_DAYS                                 = ::WID_CPR_DAYS,                                 ///< Days in transit mode.
		WID_CPR_SPEED                                = ::WID_CPR_SPEED,                                ///< Speed mode.
	};

	/** Widget of the #StationCargoGraphWindow class. */
	enum StationCargoWidgets {
		WID_SCG_CAPTION                              = ::WID_SCG_CAPTION,                              ///< Window title
		WID_SCG_BACKGROUND                           = ::WID_SCG_BACKGROUND,                           ///< Background of the window.
		WID_SCG_HEADER                               = ::WID_SCG_HEADER,                               ///< Header.
		WID_SCG_GRAPH                                = ::WID_SCG_GRAPH,                                ///< Graph itself.
		WID_SCG_RESIZE                               = ::WID_SCG_RESIZE,                               ///< Resize button.
		WID_SCG_FOOTER                               = ::WID_SCG_FOOTER,                               ///< Footer.
		WID_SCG_ENABLE_CARGOES                       = ::WID_SCG_ENABLE_CARGOES,                       ///< Enable cargoes button.
		WID_SCG_DISABLE_CARGOES                      = ::WID_SCG_DISABLE_CARGOES,                      ///< Disable cargoes button.
		WID_SCG_MATRIX                               = ::WID_SCG_MATRIX,                               ///< Cargo list.
		WID_SCG_MATRIX_SCROLLBAR                     = ::WID_SCG_MATRIX_SCROLLBAR,                     ///< Cargo list scrollbar.
	};

	/** Widget of the #PerformanceRatingDetailWindow class. */
	enum PerformanceRatingDetailsWidgets {
		WID_PRD_SCORE_FIRST                          = ::WID_PRD_SCORE_FIRST,                          ///< First entry in the score list.
		WID_PRD_SCORE_LAST                           = ::WID_PRD_SCORE_LAST,                           ///< Last entry in the score list.

		WID_PRD_COMPANY_FIRST                        = ::WID_PRD_COMPANY_FIRST,                        ///< First company.
		WID_PRD_COMPANY_LAST                         = ::WID_PRD_COMPANY_LAST,                         ///< Last company.
	};

	/** Widget of the #IndustryProductionGraphWindow class. */
	enum IndustryProductionGraphWidgets {
		WID_IP_BACKGROUND                            = ::WID_IP_BACKGROUND,                            ///< Background of the window.
		WID_IP_GRAPH                                 = ::WID_IP_GRAPH,                                 ///< Graph itself.
		WID_IP_RESIZE                                = ::WID_IP_RESIZE,                                ///< Resize button.
		WID_IP_CAPTION                               = ::WID_IP_CAPTION,                               ///< Caption.
		WID_IP_ENABLE_CARGOES                        = ::WID_IP_ENABLE_CARGOES,                        ///< Enable cargoes button.
		WID_IP_DISABLE_CARGOES                       = ::WID_IP_DISABLE_CARGOES,                       ///< Disable cargoes button.
		WID_IP_MATRIX                                = ::WID_IP_MATRIX,                                ///< Cargo list.
		WID_IP_MATRIX_SCROLLBAR                      = ::WID_IP_MATRIX_SCROLLBAR,                      ///< Cargo list scrollbar.
	};

	/* automatically generated from ../../widgets/group_widget.h */
	/** Widgets of the #VehicleGroupWindow class. */
	enum GroupListWidgets {
		WID_GL_LIST_VEHICLE                          = ::WID_GL_LIST_VEHICLE,                          ///< List of the vehicles, this must be first, see: DirtyVehicleListWindowForVehicle
		WID_GL_CAPTION                               = ::WID_GL_CAPTION,                               ///< Caption of the window.
		WID_GL_GROUP_BY_ORDER                        = ::WID_GL_GROUP_BY_ORDER,                        ///< Group order.
		WID_GL_GROUP_BY_DROPDOWN                     = ::WID_GL_GROUP_BY_DROPDOWN,                     ///< Group by dropdown list.
		WID_GL_SORT_BY_ORDER                         = ::WID_GL_SORT_BY_ORDER,                         ///< Sort order.
		WID_GL_SORT_BY_DROPDOWN                      = ::WID_GL_SORT_BY_DROPDOWN,                      ///< Sort by dropdown list.
		WID_GL_FILTER_BY_CARGO                       = ::WID_GL_FILTER_BY_CARGO,                       ///< Filter vehicle by cargo type.
		WID_GL_FILTER_BY_CARGO_SEL                   = ::WID_GL_FILTER_BY_CARGO_SEL,                   ///< Filter vehicle by cargo type panel selector.
		WID_GL_LIST_VEHICLE_SCROLLBAR                = ::WID_GL_LIST_VEHICLE_SCROLLBAR,                ///< Scrollbar for the list.
		WID_GL_AVAILABLE_VEHICLES                    = ::WID_GL_AVAILABLE_VEHICLES,                    ///< Available vehicles.
		WID_GL_MANAGE_VEHICLES_DROPDOWN              = ::WID_GL_MANAGE_VEHICLES_DROPDOWN,              ///< Manage vehicles dropdown list.
		WID_GL_STOP_ALL                              = ::WID_GL_STOP_ALL,                              ///< Stop all button.
		WID_GL_START_ALL                             = ::WID_GL_START_ALL,                             ///< Start all button.

		WID_GL_ALL_VEHICLES                          = ::WID_GL_ALL_VEHICLES,                          ///< All vehicles entry.
		WID_GL_DEFAULT_VEHICLES                      = ::WID_GL_DEFAULT_VEHICLES,                      ///< Default vehicles entry.
		WID_GL_LIST_GROUP                            = ::WID_GL_LIST_GROUP,                            ///< List of the groups.
		WID_GL_LIST_GROUP_SCROLLBAR                  = ::WID_GL_LIST_GROUP_SCROLLBAR,                  ///< Scrollbar for the list.
		WID_GL_CREATE_GROUP                          = ::WID_GL_CREATE_GROUP,                          ///< Create group button.
		WID_GL_DELETE_GROUP                          = ::WID_GL_DELETE_GROUP,                          ///< Delete group button.
		WID_GL_RENAME_GROUP                          = ::WID_GL_RENAME_GROUP,                          ///< Rename group button.
		WID_GL_LIVERY_GROUP                          = ::WID_GL_LIVERY_GROUP,                          ///< Group livery button.
		WID_GL_COLLAPSE_ALL_GROUPS                   = ::WID_GL_COLLAPSE_ALL_GROUPS,                   ///< Collapse all groups button.
		WID_GL_EXPAND_ALL_GROUPS                     = ::WID_GL_EXPAND_ALL_GROUPS,                     ///< Expand all groups button.
		WID_GL_REPLACE_PROTECTION                    = ::WID_GL_REPLACE_PROTECTION,                    ///< Replace protection button.
		WID_GL_INFO                                  = ::WID_GL_INFO,                                  ///< Group info.
	};

	/* automatically generated from ../../widgets/highscore_widget.h */
	/** Widgets of the #EndGameHighScoreBaseWindow class and #HighScoreWindow class. */
	enum HighscoreWidgets {
		WID_H_BACKGROUND                             = ::WID_H_BACKGROUND,                             ///< Background of the window.
	};

	/* automatically generated from ../../widgets/industry_widget.h */
	/** Widgets of the #BuildIndustryWindow class. */
	enum DynamicPlaceIndustriesWidgets {
		WID_DPI_SCENARIO_EDITOR_PANE                 = ::WID_DPI_SCENARIO_EDITOR_PANE,                 ///< Pane containing SE-only widgets.
		WID_DPI_REMOVE_ALL_INDUSTRIES_WIDGET         = ::WID_DPI_REMOVE_ALL_INDUSTRIES_WIDGET,         ///< Remove all industries button.
		WID_DPI_CREATE_RANDOM_INDUSTRIES_WIDGET      = ::WID_DPI_CREATE_RANDOM_INDUSTRIES_WIDGET,      ///< Create random industries button.
		WID_DPI_MATRIX_WIDGET                        = ::WID_DPI_MATRIX_WIDGET,                        ///< Matrix of the industries.
		WID_DPI_SCROLLBAR                            = ::WID_DPI_SCROLLBAR,                            ///< Scrollbar of the matrix.
		WID_DPI_INFOPANEL                            = ::WID_DPI_INFOPANEL,                            ///< Info panel about the industry.
		WID_DPI_DISPLAY_WIDGET                       = ::WID_DPI_DISPLAY_WIDGET,                       ///< Display chain button.
		WID_DPI_FUND_WIDGET                          = ::WID_DPI_FUND_WIDGET,                          ///< Fund button.
	};

	/** Widgets of the #IndustryViewWindow class. */
	enum IndustryViewWidgets {
		WID_IV_CAPTION                               = ::WID_IV_CAPTION,                               ///< Caption of the window.
		WID_IV_VIEWPORT                              = ::WID_IV_VIEWPORT,                              ///< Viewport of the industry.
		WID_IV_INFO                                  = ::WID_IV_INFO,                                  ///< Info of the industry.
		WID_IV_GOTO                                  = ::WID_IV_GOTO,                                  ///< Goto button.
		WID_IV_DISPLAY                               = ::WID_IV_DISPLAY,                               ///< Display chain button.
		WID_IV_GRAPH                                 = ::WID_IV_GRAPH,                                 ///< Production history button.
	};

	/** Widgets of the #IndustryDirectoryWindow class. */
	enum IndustryDirectoryWidgets {
		WID_ID_DROPDOWN_ORDER                        = ::WID_ID_DROPDOWN_ORDER,                        ///< Dropdown for the order of the sort.
		WID_ID_DROPDOWN_CRITERIA                     = ::WID_ID_DROPDOWN_CRITERIA,                     ///< Dropdown for the criteria of the sort.
		WID_ID_FILTER_BY_ACC_CARGO                   = ::WID_ID_FILTER_BY_ACC_CARGO,                   ///< Accepted cargo filter dropdown list.
		WID_ID_FILTER_BY_PROD_CARGO                  = ::WID_ID_FILTER_BY_PROD_CARGO,                  ///< Produced cargo filter dropdown list.
		WID_ID_FILTER                                = ::WID_ID_FILTER,                                ///< Textbox to filter industry name.
		WID_ID_INDUSTRY_LIST                         = ::WID_ID_INDUSTRY_LIST,                         ///< Industry list.
		WID_ID_SCROLLBAR                             = ::WID_ID_SCROLLBAR,                             ///< Scrollbar of the list.
	};

	/** Widgets of the #IndustryCargoesWindow class */
	enum IndustryCargoesWidgets {
		WID_IC_CAPTION                               = ::WID_IC_CAPTION,                               ///< Caption of the window.
		WID_IC_NOTIFY                                = ::WID_IC_NOTIFY,                                ///< Row of buttons at the bottom.
		WID_IC_PANEL                                 = ::WID_IC_PANEL,                                 ///< Panel that shows the chain.
		WID_IC_SCROLLBAR                             = ::WID_IC_SCROLLBAR,                             ///< Scrollbar of the panel.
		WID_IC_CARGO_DROPDOWN                        = ::WID_IC_CARGO_DROPDOWN,                        ///< Select cargo dropdown.
		WID_IC_IND_DROPDOWN                          = ::WID_IC_IND_DROPDOWN,                          ///< Select industry dropdown.
	};

	/* automatically generated from ../../widgets/intro_widget.h */
	/** Widgets of the #SelectGameWindow class. */
	enum SelectGameIntroWidgets {
		WID_SGI_GENERATE_GAME                        = ::WID_SGI_GENERATE_GAME,                        ///< Generate game button.
		WID_SGI_LOAD_GAME                            = ::WID_SGI_LOAD_GAME,                            ///< Load game button.
		WID_SGI_PLAY_SCENARIO                        = ::WID_SGI_PLAY_SCENARIO,                        ///< Play scenario button.
		WID_SGI_PLAY_HEIGHTMAP                       = ::WID_SGI_PLAY_HEIGHTMAP,                       ///< Play heightmap button.
		WID_SGI_EDIT_SCENARIO                        = ::WID_SGI_EDIT_SCENARIO,                        ///< Edit scenario button.
		WID_SGI_PLAY_NETWORK                         = ::WID_SGI_PLAY_NETWORK,                         ///< Play network button.
		WID_SGI_TEMPERATE_LANDSCAPE                  = ::WID_SGI_TEMPERATE_LANDSCAPE,                  ///< Select temperate landscape button.
		WID_SGI_ARCTIC_LANDSCAPE                     = ::WID_SGI_ARCTIC_LANDSCAPE,                     ///< Select arctic landscape button.
		WID_SGI_TROPIC_LANDSCAPE                     = ::WID_SGI_TROPIC_LANDSCAPE,                     ///< Select tropic landscape button.
		WID_SGI_TOYLAND_LANDSCAPE                    = ::WID_SGI_TOYLAND_LANDSCAPE,                    ///< Select toyland landscape button.
		WID_SGI_BASESET_SELECTION                    = ::WID_SGI_BASESET_SELECTION,                    ///< Baseset selection.
		WID_SGI_BASESET                              = ::WID_SGI_BASESET,                              ///< Baseset errors.
		WID_SGI_TRANSLATION_SELECTION                = ::WID_SGI_TRANSLATION_SELECTION,                ///< Translation selection.
		WID_SGI_TRANSLATION                          = ::WID_SGI_TRANSLATION,                          ///< Translation errors.
		WID_SGI_OPTIONS                              = ::WID_SGI_OPTIONS,                              ///< Options button.
		WID_SGI_HIGHSCORE                            = ::WID_SGI_HIGHSCORE,                            ///< Highscore button.
		WID_SGI_SETTINGS_OPTIONS                     = ::WID_SGI_SETTINGS_OPTIONS,                     ///< Settings button.
		WID_SGI_GRF_SETTINGS                         = ::WID_SGI_GRF_SETTINGS,                         ///< NewGRF button.
		WID_SGI_CONTENT_DOWNLOAD                     = ::WID_SGI_CONTENT_DOWNLOAD,                     ///< Content Download button.
		WID_SGI_AI_SETTINGS                          = ::WID_SGI_AI_SETTINGS,                          ///< AI button.
		WID_SGI_GS_SETTINGS                          = ::WID_SGI_GS_SETTINGS,                          ///< Game Script button.
		WID_SGI_EXIT                                 = ::WID_SGI_EXIT,                                 ///< Exit button.
	};

	/* automatically generated from ../../widgets/league_widget.h */
	/** Widget of the #PerformanceLeagueWindow class. */
	enum PerformanceLeagueWidgets {
		WID_PLT_BACKGROUND                           = ::WID_PLT_BACKGROUND,                           ///< Background of the window.
	};

	/** Widget of the #ScriptLeagueWindow class. */
	enum ScriptLeagueWidgets {
		WID_SLT_CAPTION                              = ::WID_SLT_CAPTION,                              ///< Caption of the window.
		WID_SLT_BACKGROUND                           = ::WID_SLT_BACKGROUND,                           ///< Background of the window.
	};

	/* automatically generated from ../../widgets/link_graph_legend_widget.h */
	/** Widgets of the WC_LINKGRAPH_LEGEND. */
	enum LinkGraphLegendWidgets {
		WID_LGL_CAPTION                              = ::WID_LGL_CAPTION,                              ///< Caption widget.
		WID_LGL_SATURATION                           = ::WID_LGL_SATURATION,                           ///< Saturation legend.
		WID_LGL_SATURATION_FIRST                     = ::WID_LGL_SATURATION_FIRST,
		WID_LGL_SATURATION_LAST                      = ::WID_LGL_SATURATION_LAST,
		WID_LGL_COMPANIES                            = ::WID_LGL_COMPANIES,                            ///< Company selection widget.
		WID_LGL_COMPANY_FIRST                        = ::WID_LGL_COMPANY_FIRST,
		WID_LGL_COMPANY_LAST                         = ::WID_LGL_COMPANY_LAST,
		WID_LGL_COMPANIES_ALL                        = ::WID_LGL_COMPANIES_ALL,
		WID_LGL_COMPANIES_NONE                       = ::WID_LGL_COMPANIES_NONE,
		WID_LGL_CARGOES                              = ::WID_LGL_CARGOES,                              ///< Cargo selection widget.
		WID_LGL_CARGO_FIRST                          = ::WID_LGL_CARGO_FIRST,
		WID_LGL_CARGO_LAST                           = ::WID_LGL_CARGO_LAST,
		WID_LGL_CARGOES_ALL                          = ::WID_LGL_CARGOES_ALL,
		WID_LGL_CARGOES_NONE                         = ::WID_LGL_CARGOES_NONE,
	};

	/* automatically generated from ../../widgets/main_widget.h */
	/** Widgets of the #MainWindow class. */
	enum MainWidgets {
		WID_M_VIEWPORT                               = ::WID_M_VIEWPORT,                               ///< Main window viewport.
	};

	/* automatically generated from ../../widgets/misc_widget.h */
	/** Widgets of the #LandInfoWindow class. */
	enum LandInfoWidgets {
		WID_LI_LOCATION                              = ::WID_LI_LOCATION,                              ///< Scroll to location.
		WID_LI_BACKGROUND                            = ::WID_LI_BACKGROUND,                            ///< Background of the window.
	};

	/** Widgets of the #TooltipsWindow class. */
	enum ToolTipsWidgets {
		WID_TT_BACKGROUND                            = ::WID_TT_BACKGROUND,                            ///< Background of the window.
	};

	/** Widgets of the #AboutWindow class. */
	enum AboutWidgets {
		WID_A_SCROLLING_TEXT                         = ::WID_A_SCROLLING_TEXT,                         ///< The actually scrolling text.
		WID_A_WEBSITE                                = ::WID_A_WEBSITE,                                ///< URL of OpenTTD website.
		WID_A_WEBSITE1                               = ::WID_A_WEBSITE1,                               ///< URL of JGR's patchpack thread.
		WID_A_WEBSITE2                               = ::WID_A_WEBSITE2,                               ///< URL of JGR's patchpack github.
		WID_A_WEBSITE3                               = ::WID_A_WEBSITE3,                               ///< URL of embeddedt's patchpack github.
		WID_A_COPYRIGHT                              = ::WID_A_COPYRIGHT,                              ///< Copyright string
	};

	/** Widgets of the #QueryStringWindow class. */
	enum QueryStringWidgets {
		WID_QS_CAPTION                               = ::WID_QS_CAPTION,                               ///< Caption of the window.
		WID_QS_TEXT                                  = ::WID_QS_TEXT,                                  ///< Text of the query.
		WID_QS_WARNING                               = ::WID_QS_WARNING,                               ///< Warning label about password security
		WID_QS_DEFAULT                               = ::WID_QS_DEFAULT,                               ///< Default button.
		WID_QS_CANCEL                                = ::WID_QS_CANCEL,                                ///< Cancel button.
		WID_QS_OK                                    = ::WID_QS_OK,                                    ///< OK button.
	};

	/** Widgets of the #QueryWindow class. */
	enum QueryWidgets {
		WID_Q_CAPTION                                = ::WID_Q_CAPTION,                                ///< Caption of the window.
		WID_Q_TEXT                                   = ::WID_Q_TEXT,                                   ///< Text of the query.
		WID_Q_NO                                     = ::WID_Q_NO,                                     ///< Yes button.
		WID_Q_YES                                    = ::WID_Q_YES,                                    ///< No button.
	};

	/** Widgets of the #TextfileWindow class. */
	enum TextfileWidgets {
		WID_TF_CAPTION                               = ::WID_TF_CAPTION,                               ///< The caption of the window.
		WID_TF_WRAPTEXT                              = ::WID_TF_WRAPTEXT,                              ///< Whether or not to wrap the text.
		WID_TF_BACKGROUND                            = ::WID_TF_BACKGROUND,                            ///< Panel to draw the textfile on.
		WID_TF_VSCROLLBAR                            = ::WID_TF_VSCROLLBAR,                            ///< Vertical scrollbar to scroll through the textfile up-and-down.
		WID_TF_HSCROLLBAR                            = ::WID_TF_HSCROLLBAR,                            ///< Horizontal scrollbar to scroll through the textfile left-to-right.
	};

	/** Widgets of the #TextfileWindow class. */
	enum ModifierKeyToggleWidgets {
		WID_MKT_SHIFT                                = ::WID_MKT_SHIFT,
		WID_MKT_CTRL                                 = ::WID_MKT_CTRL,
	};

	/* automatically generated from ../../widgets/music_widget.h */
	/** Widgets of the #MusicTrackSelectionWindow class. */
	enum MusicTrackSelectionWidgets {
		WID_MTS_CAPTION                              = ::WID_MTS_CAPTION,                              ///< Window caption.
		WID_MTS_LIST_LEFT                            = ::WID_MTS_LIST_LEFT,                            ///< Left button.
		WID_MTS_PLAYLIST                             = ::WID_MTS_PLAYLIST,                             ///< Playlist.
		WID_MTS_LIST_RIGHT                           = ::WID_MTS_LIST_RIGHT,                           ///< Right button.
		WID_MTS_MUSICSET                             = ::WID_MTS_MUSICSET,                             ///< Music set selection.
		WID_MTS_ALL                                  = ::WID_MTS_ALL,                                  ///< All button.
		WID_MTS_OLD                                  = ::WID_MTS_OLD,                                  ///< Old button.
		WID_MTS_NEW                                  = ::WID_MTS_NEW,                                  ///< New button.
		WID_MTS_EZY                                  = ::WID_MTS_EZY,                                  ///< Ezy button.
		WID_MTS_CUSTOM1                              = ::WID_MTS_CUSTOM1,                              ///< Custom1 button.
		WID_MTS_CUSTOM2                              = ::WID_MTS_CUSTOM2,                              ///< Custom2 button.
		WID_MTS_CLEAR                                = ::WID_MTS_CLEAR,                                ///< Clear button.
	};

	/** Widgets of the #MusicWindow class. */
	enum MusicWidgets {
		WID_M_PREV                                   = ::WID_M_PREV,                                   ///< Previous button.
		WID_M_NEXT                                   = ::WID_M_NEXT,                                   ///< Next button.
		WID_M_STOP                                   = ::WID_M_STOP,                                   ///< Stop button.
		WID_M_PLAY                                   = ::WID_M_PLAY,                                   ///< Play button.
		WID_M_SLIDERS                                = ::WID_M_SLIDERS,                                ///< Sliders.
		WID_M_MUSIC_VOL                              = ::WID_M_MUSIC_VOL,                              ///< Music volume.
		WID_M_EFFECT_VOL                             = ::WID_M_EFFECT_VOL,                             ///< Effect volume.
		WID_M_BACKGROUND                             = ::WID_M_BACKGROUND,                             ///< Background of the window.
		WID_M_TRACK                                  = ::WID_M_TRACK,                                  ///< Track playing.
		WID_M_TRACK_NR                               = ::WID_M_TRACK_NR,                               ///< Track number.
		WID_M_TRACK_TITLE                            = ::WID_M_TRACK_TITLE,                            ///< Track title.
		WID_M_TRACK_NAME                             = ::WID_M_TRACK_NAME,                             ///< Track name.
		WID_M_SHUFFLE                                = ::WID_M_SHUFFLE,                                ///< Shuffle button.
		WID_M_PROGRAMME                              = ::WID_M_PROGRAMME,                              ///< Program button.
		WID_M_ALL                                    = ::WID_M_ALL,                                    ///< All button.
		WID_M_OLD                                    = ::WID_M_OLD,                                    ///< Old button.
		WID_M_NEW                                    = ::WID_M_NEW,                                    ///< New button.
		WID_M_EZY                                    = ::WID_M_EZY,                                    ///< Ezy button.
		WID_M_CUSTOM1                                = ::WID_M_CUSTOM1,                                ///< Custom1 button.
		WID_M_CUSTOM2                                = ::WID_M_CUSTOM2,                                ///< Custom2 button.
	};

	/* automatically generated from ../../widgets/network_chat_widget.h */
	/** Widgets of the #NetworkChatWindow class. */
	enum NetWorkChatWidgets {
		WID_NC_CLOSE                                 = ::WID_NC_CLOSE,                                 ///< Close button.
		WID_NC_BACKGROUND                            = ::WID_NC_BACKGROUND,                            ///< Background of the window.
		WID_NC_DESTINATION                           = ::WID_NC_DESTINATION,                           ///< Destination.
		WID_NC_TEXTBOX                               = ::WID_NC_TEXTBOX,                               ///< Textbox.
		WID_NC_SENDBUTTON                            = ::WID_NC_SENDBUTTON,                            ///< Send button.
	};

	/* automatically generated from ../../widgets/network_content_widget.h */
	/** Widgets of the #NetworkContentDownloadStatusWindow class. */
	enum NetworkContentDownloadStatusWidgets {
		WID_NCDS_PROGRESS_BAR                        = ::WID_NCDS_PROGRESS_BAR,                        ///< Simple progress bar.
		WID_NCDS_PROGRESS_TEXT                       = ::WID_NCDS_PROGRESS_TEXT,                       ///< Text explaining what is happening.
		WID_NCDS_CANCELOK                            = ::WID_NCDS_CANCELOK,                            ///< (Optional) Cancel/OK button.
	};

	/** Widgets of the #NetworkContentListWindow class. */
	enum NetworkContentListWidgets {
		WID_NCL_BACKGROUND                           = ::WID_NCL_BACKGROUND,                           ///< Resize button.

		WID_NCL_FILTER_CAPT                          = ::WID_NCL_FILTER_CAPT,                          ///< Caption for the filter editbox.
		WID_NCL_FILTER                               = ::WID_NCL_FILTER,                               ///< Filter editbox.

		WID_NCL_CHECKBOX                             = ::WID_NCL_CHECKBOX,                             ///< Button above checkboxes.
		WID_NCL_TYPE                                 = ::WID_NCL_TYPE,                                 ///< 'Type' button.
		WID_NCL_NAME                                 = ::WID_NCL_NAME,                                 ///< 'Name' button.

		WID_NCL_MATRIX                               = ::WID_NCL_MATRIX,                               ///< Panel with list of content.
		WID_NCL_SCROLLBAR                            = ::WID_NCL_SCROLLBAR,                            ///< Scrollbar of matrix.

		WID_NCL_DETAILS                              = ::WID_NCL_DETAILS,                              ///< Panel with content details.
		WID_NCL_TEXTFILE                             = ::WID_NCL_TEXTFILE,                             ///< Open readme, changelog (+1) or license (+2) of a file in the content window.

		WID_NCL_SELECT_ALL                           = ::WID_NCL_SELECT_ALL,                           ///< 'Select all' button.
		WID_NCL_SELECT_UPDATE                        = ::WID_NCL_SELECT_UPDATE,                        ///< 'Select updates' button.
		WID_NCL_UNSELECT                             = ::WID_NCL_UNSELECT,                             ///< 'Unselect all' button.
		WID_NCL_OPEN_URL                             = ::WID_NCL_OPEN_URL,                             ///< 'Open url' button.
		WID_NCL_CANCEL                               = ::WID_NCL_CANCEL,                               ///< 'Cancel' button.
		WID_NCL_DOWNLOAD                             = ::WID_NCL_DOWNLOAD,                             ///< 'Download' button.

		WID_NCL_SEL_ALL_UPDATE                       = ::WID_NCL_SEL_ALL_UPDATE,                       ///< #NWID_SELECTION widget for select all/update buttons..
		WID_NCL_SEARCH_EXTERNAL                      = ::WID_NCL_SEARCH_EXTERNAL,                      ///< Search external sites for missing NewGRF.
	};

	/* automatically generated from ../../widgets/network_widget.h */
	/** Widgets of the #NetworkGameWindow class. */
	enum NetworkGameWidgets {
		WID_NG_MAIN                                  = ::WID_NG_MAIN,                                  ///< Main panel.

		WID_NG_CLIENT_LABEL                          = ::WID_NG_CLIENT_LABEL,                          ///< Label in front of client name edit box.
		WID_NG_CLIENT                                = ::WID_NG_CLIENT,                                ///< Panel with editbox to set client name.
		WID_NG_FILTER_LABEL                          = ::WID_NG_FILTER_LABEL,                          ///< Label in front of the filter/search edit box.
		WID_NG_FILTER                                = ::WID_NG_FILTER,                                ///< Panel with the edit box to enter the search text.

		WID_NG_HEADER                                = ::WID_NG_HEADER,                                ///< Header container of the matrix.
		WID_NG_NAME                                  = ::WID_NG_NAME,                                  ///< 'Name' button.
		WID_NG_CLIENTS                               = ::WID_NG_CLIENTS,                               ///< 'Clients' button.
		WID_NG_MAPSIZE                               = ::WID_NG_MAPSIZE,                               ///< 'Map size' button.
		WID_NG_DATE                                  = ::WID_NG_DATE,                                  ///< 'Date' button.
		WID_NG_YEARS                                 = ::WID_NG_YEARS,                                 ///< 'Years' button.
		WID_NG_INFO                                  = ::WID_NG_INFO,                                  ///< Third button in the game list panel.

		WID_NG_MATRIX                                = ::WID_NG_MATRIX,                                ///< Panel with list of games.
		WID_NG_SCROLLBAR                             = ::WID_NG_SCROLLBAR,                             ///< Scrollbar of matrix.

		WID_NG_LASTJOINED_LABEL                      = ::WID_NG_LASTJOINED_LABEL,                      ///< Label "Last joined server:".
		WID_NG_LASTJOINED                            = ::WID_NG_LASTJOINED,                            ///< Info about the last joined server.
		WID_NG_LASTJOINED_SPACER                     = ::WID_NG_LASTJOINED_SPACER,                     ///< Spacer after last joined server panel.

		WID_NG_DETAILS                               = ::WID_NG_DETAILS,                               ///< Panel with game details.
		WID_NG_DETAILS_SPACER                        = ::WID_NG_DETAILS_SPACER,                        ///< Spacer for game actual details.
		WID_NG_JOIN                                  = ::WID_NG_JOIN,                                  ///< 'Join game' button.
		WID_NG_REFRESH                               = ::WID_NG_REFRESH,                               ///< 'Refresh server' button.
		WID_NG_NEWGRF                                = ::WID_NG_NEWGRF,                                ///< 'NewGRF Settings' button.
		WID_NG_NEWGRF_SEL                            = ::WID_NG_NEWGRF_SEL,                            ///< Selection 'widget' to hide the NewGRF settings.
		WID_NG_NEWGRF_MISSING                        = ::WID_NG_NEWGRF_MISSING,                        ///< 'Find missing NewGRF online' button.
		WID_NG_NEWGRF_MISSING_SEL                    = ::WID_NG_NEWGRF_MISSING_SEL,                    ///< Selection widget for the above button.

		WID_NG_SEARCH_INTERNET                       = ::WID_NG_SEARCH_INTERNET,                       ///< 'Search internet server' button.
		WID_NG_SEARCH_LAN                            = ::WID_NG_SEARCH_LAN,                            ///< 'Search LAN server' button.
		WID_NG_ADD                                   = ::WID_NG_ADD,                                   ///< 'Add server' button.
		WID_NG_START                                 = ::WID_NG_START,                                 ///< 'Start server' button.
		WID_NG_CANCEL                                = ::WID_NG_CANCEL,                                ///< 'Cancel' button.
	};

	/** Widgets of the #NetworkStartServerWindow class. */
	enum NetworkStartServerWidgets {
		WID_NSS_BACKGROUND                           = ::WID_NSS_BACKGROUND,                           ///< Background of the window.
		WID_NSS_GAMENAME_LABEL                       = ::WID_NSS_GAMENAME_LABEL,                       ///< Label for the game name.
		WID_NSS_GAMENAME                             = ::WID_NSS_GAMENAME,                             ///< Background for editbox to set game name.
		WID_NSS_SETPWD                               = ::WID_NSS_SETPWD,                               ///< 'Set password' button.
		WID_NSS_CONNTYPE_LABEL                       = ::WID_NSS_CONNTYPE_LABEL,                       ///< Label for 'connection type'.
		WID_NSS_CONNTYPE_BTN                         = ::WID_NSS_CONNTYPE_BTN,                         ///< 'Connection type' droplist button.
		WID_NSS_CLIENTS_LABEL                        = ::WID_NSS_CLIENTS_LABEL,                        ///< Label for 'max clients'.
		WID_NSS_CLIENTS_BTND                         = ::WID_NSS_CLIENTS_BTND,                         ///< 'Max clients' downarrow.
		WID_NSS_CLIENTS_TXT                          = ::WID_NSS_CLIENTS_TXT,                          ///< 'Max clients' text.
		WID_NSS_CLIENTS_BTNU                         = ::WID_NSS_CLIENTS_BTNU,                         ///< 'Max clients' uparrow.
		WID_NSS_COMPANIES_LABEL                      = ::WID_NSS_COMPANIES_LABEL,                      ///< Label for 'max companies'.
		WID_NSS_COMPANIES_BTND                       = ::WID_NSS_COMPANIES_BTND,                       ///< 'Max companies' downarrow.
		WID_NSS_COMPANIES_TXT                        = ::WID_NSS_COMPANIES_TXT,                        ///< 'Max companies' text.
		WID_NSS_COMPANIES_BTNU                       = ::WID_NSS_COMPANIES_BTNU,                       ///< 'Max companies' uparrow.

		WID_NSS_GENERATE_GAME                        = ::WID_NSS_GENERATE_GAME,                        ///< New game button.
		WID_NSS_LOAD_GAME                            = ::WID_NSS_LOAD_GAME,                            ///< Load game button.
		WID_NSS_PLAY_SCENARIO                        = ::WID_NSS_PLAY_SCENARIO,                        ///< Play scenario button.
		WID_NSS_PLAY_HEIGHTMAP                       = ::WID_NSS_PLAY_HEIGHTMAP,                       ///< Play heightmap button.

		WID_NSS_CANCEL                               = ::WID_NSS_CANCEL,                               ///< 'Cancel' button.
	};

	/** Widgets of the #NetworkClientListWindow class. */
	enum ClientListWidgets {
		WID_CL_PANEL                                 = ::WID_CL_PANEL,                                 ///< Panel of the window.
		WID_CL_SERVER_SELECTOR                       = ::WID_CL_SERVER_SELECTOR,                       ///< Selector to hide the server frame.
		WID_CL_SERVER_NAME                           = ::WID_CL_SERVER_NAME,                           ///< Server name.
		WID_CL_SERVER_NAME_EDIT                      = ::WID_CL_SERVER_NAME_EDIT,                      ///< Edit button for server name.
		WID_CL_SERVER_VISIBILITY                     = ::WID_CL_SERVER_VISIBILITY,                     ///< Server visibility.
		WID_CL_SERVER_INVITE_CODE                    = ::WID_CL_SERVER_INVITE_CODE,                    ///< Invite code for this server.
		WID_CL_SERVER_CONNECTION_TYPE                = ::WID_CL_SERVER_CONNECTION_TYPE,                ///< The type of connection the Game Coordinator detected for this server.
		WID_CL_CLIENT_NAME                           = ::WID_CL_CLIENT_NAME,                           ///< Client name.
		WID_CL_CLIENT_NAME_EDIT                      = ::WID_CL_CLIENT_NAME_EDIT,                      ///< Edit button for client name.
		WID_CL_MATRIX                                = ::WID_CL_MATRIX,                                ///< Company/client list.
		WID_CL_SCROLLBAR                             = ::WID_CL_SCROLLBAR,                             ///< Scrollbar for company/client list.
		WID_CL_COMPANY_JOIN                          = ::WID_CL_COMPANY_JOIN,                          ///< Used for QueryWindow when a company has a password.
		WID_CL_CLIENT_COMPANY_COUNT                  = ::WID_CL_CLIENT_COMPANY_COUNT,                  ///< Count of clients and companies.
	};

	/** Widgets of the #NetworkJoinStatusWindow class. */
	enum NetworkJoinStatusWidgets {
		WID_NJS_PROGRESS_BAR                         = ::WID_NJS_PROGRESS_BAR,                         ///< Simple progress bar.
		WID_NJS_PROGRESS_TEXT                        = ::WID_NJS_PROGRESS_TEXT,                        ///< Text explaining what is happening.
		WID_NJS_CANCELOK                             = ::WID_NJS_CANCELOK,                             ///< Cancel / OK button.
	};

	/** Widgets of the #NetworkCompanyPasswordWindow class. */
	enum NetworkCompanyPasswordWidgets {
		WID_NCP_BACKGROUND                           = ::WID_NCP_BACKGROUND,                           ///< Background of the window.
		WID_NCP_LABEL                                = ::WID_NCP_LABEL,                                ///< Label in front of the password field.
		WID_NCP_PASSWORD                             = ::WID_NCP_PASSWORD,                             ///< Input field for the password.
		WID_NCP_SAVE_AS_DEFAULT_PASSWORD             = ::WID_NCP_SAVE_AS_DEFAULT_PASSWORD,             ///< Toggle 'button' for saving the current password as default password.
		WID_NCP_WARNING                              = ::WID_NCP_WARNING,                              ///< Warning text about password security
		WID_NCP_CANCEL                               = ::WID_NCP_CANCEL,                               ///< Close the window without changing anything.
		WID_NCP_OK                                   = ::WID_NCP_OK,                                   ///< Safe the password etc.
	};

	/** Widgets of the #NetworkAskRelayWindow class. */
	enum NetworkAskRelayWidgets {
		WID_NAR_CAPTION                              = ::WID_NAR_CAPTION,                              ///< Caption of the window.
		WID_NAR_TEXT                                 = ::WID_NAR_TEXT,                                 ///< Text in the window.
		WID_NAR_NO                                   = ::WID_NAR_NO,                                   ///< "No" button.
		WID_NAR_YES_ONCE                             = ::WID_NAR_YES_ONCE,                             ///< "Yes, once" button.
		WID_NAR_YES_ALWAYS                           = ::WID_NAR_YES_ALWAYS,                           ///< "Yes, always" button.
	};

	/* automatically generated from ../../widgets/newgrf_debug_widget.h */
	/** Widgets of the #NewGRFInspectWindow class. */
	enum NewGRFInspectWidgets {
		WID_NGRFI_CAPTION                            = ::WID_NGRFI_CAPTION,                            ///< The caption bar of course.
		WID_NGRFI_PARENT                             = ::WID_NGRFI_PARENT,                             ///< Inspect the parent.
		WID_NGRFI_VEH_PREV                           = ::WID_NGRFI_VEH_PREV,                           ///< Go to previous vehicle in chain.
		WID_NGRFI_VEH_NEXT                           = ::WID_NGRFI_VEH_NEXT,                           ///< Go to next vehicle in chain.
		WID_NGRFI_VEH_CHAIN                          = ::WID_NGRFI_VEH_CHAIN,                          ///< Display for vehicle chain.
		WID_NGRFI_MAINPANEL                          = ::WID_NGRFI_MAINPANEL,                          ///< Panel widget containing the actual data.
		WID_NGRFI_SCROLLBAR                          = ::WID_NGRFI_SCROLLBAR,                          ///< Scrollbar.
		WID_NGRFI_REFRESH                            = ::WID_NGRFI_REFRESH,                            ///< Refresh toggle.
		WID_NGRFI_LOG_CONSOLE                        = ::WID_NGRFI_LOG_CONSOLE,                        ///< Log to console
		WID_NGRFI_DUPLICATE                          = ::WID_NGRFI_DUPLICATE,                          ///< Duplicate window
		WID_NGRFI_SPRITE_DUMP                        = ::WID_NGRFI_SPRITE_DUMP,                        ///< Dump current sprite group
		WID_NGRFI_SPRITE_DUMP_SEL                    = ::WID_NGRFI_SPRITE_DUMP_SEL,                    ///< Selection widget for WID_NGRFI_SPRITE_DUMP
		WID_NGRFI_SPRITE_DUMP_UNOPT                  = ::WID_NGRFI_SPRITE_DUMP_UNOPT,                  ///< Dump unoptimised sprite group
		WID_NGRFI_SPRITE_DUMP_UNOPT_SEL              = ::WID_NGRFI_SPRITE_DUMP_UNOPT_SEL,              ///< Selection widget for WID_NGRFI_SPRITE_DUMP_UNOPT
		WID_NGRFI_SPRITE_DUMP_GOTO                   = ::WID_NGRFI_SPRITE_DUMP_GOTO,                   ///< Goto sprite
		WID_NGRFI_SPRITE_DUMP_GOTO_SEL               = ::WID_NGRFI_SPRITE_DUMP_GOTO_SEL,               ///< Selection widget for WID_NGRFI_SPRITE_DUMP_GOTO
	};

	/** Widgets of the #SpriteAlignerWindow class. */
	enum SpriteAlignerWidgets {
		WID_SA_CAPTION                               = ::WID_SA_CAPTION,                               ///< Caption of the window.
		WID_SA_PREVIOUS                              = ::WID_SA_PREVIOUS,                              ///< Skip to the previous sprite.
		WID_SA_GOTO                                  = ::WID_SA_GOTO,                                  ///< Go to a given sprite.
		WID_SA_NEXT                                  = ::WID_SA_NEXT,                                  ///< Skip to the next sprite.
		WID_SA_UP                                    = ::WID_SA_UP,                                    ///< Move the sprite up.
		WID_SA_LEFT                                  = ::WID_SA_LEFT,                                  ///< Move the sprite to the left.
		WID_SA_RIGHT                                 = ::WID_SA_RIGHT,                                 ///< Move the sprite to the right.
		WID_SA_DOWN                                  = ::WID_SA_DOWN,                                  ///< Move the sprite down.
		WID_SA_SPRITE                                = ::WID_SA_SPRITE,                                ///< The actual sprite.
		WID_SA_OFFSETS_ABS                           = ::WID_SA_OFFSETS_ABS,                           ///< The sprite offsets (absolute).
		WID_SA_OFFSETS_REL                           = ::WID_SA_OFFSETS_REL,                           ///< The sprite offsets (relative).
		WID_SA_PICKER                                = ::WID_SA_PICKER,                                ///< Sprite picker.
		WID_SA_LIST                                  = ::WID_SA_LIST,                                  ///< Queried sprite list.
		WID_SA_SCROLLBAR                             = ::WID_SA_SCROLLBAR,                             ///< Scrollbar for sprite list.
		WID_SA_RESET_REL                             = ::WID_SA_RESET_REL,                             ///< Reset relative sprite offset
		WID_SA_CENTRE                                = ::WID_SA_CENTRE,                                ///< Toggle centre sprite.
		WID_SA_CROSSHAIR                             = ::WID_SA_CROSSHAIR,                             ///< Toggle crosshair.
	};

	/* automatically generated from ../../widgets/newgrf_widget.h */
	/** Widgets of the #NewGRFParametersWindow class. */
	enum NewGRFParametersWidgets {
		WID_NP_SHOW_NUMPAR                           = ::WID_NP_SHOW_NUMPAR,                           ///< #NWID_SELECTION to optionally display #WID_NP_NUMPAR.
		WID_NP_NUMPAR_DEC                            = ::WID_NP_NUMPAR_DEC,                            ///< Button to decrease number of parameters.
		WID_NP_NUMPAR_INC                            = ::WID_NP_NUMPAR_INC,                            ///< Button to increase number of parameters.
		WID_NP_NUMPAR                                = ::WID_NP_NUMPAR,                                ///< Optional number of parameters.
		WID_NP_NUMPAR_TEXT                           = ::WID_NP_NUMPAR_TEXT,                           ///< Text description.
		WID_NP_BACKGROUND                            = ::WID_NP_BACKGROUND,                            ///< Panel to draw the settings on.
		WID_NP_SCROLLBAR                             = ::WID_NP_SCROLLBAR,                             ///< Scrollbar to scroll through all settings.
		WID_NP_ACCEPT                                = ::WID_NP_ACCEPT,                                ///< Accept button.
		WID_NP_RESET                                 = ::WID_NP_RESET,                                 ///< Reset button.
		WID_NP_SHOW_DESCRIPTION                      = ::WID_NP_SHOW_DESCRIPTION,                      ///< #NWID_SELECTION to optionally display parameter descriptions.
		WID_NP_DESCRIPTION                           = ::WID_NP_DESCRIPTION,                           ///< Multi-line description of a parameter.
	};

	/** Widgets of the #NewGRFWindow class. */
	enum NewGRFStateWidgets {
		WID_NS_PRESET_LIST                           = ::WID_NS_PRESET_LIST,                           ///< Active NewGRF preset.
		WID_NS_PRESET_SAVE                           = ::WID_NS_PRESET_SAVE,                           ///< Save list of active NewGRFs as presets.
		WID_NS_PRESET_DELETE                         = ::WID_NS_PRESET_DELETE,                         ///< Delete active preset.
		WID_NS_ADD                                   = ::WID_NS_ADD,                                   ///< Add NewGRF to active list.
		WID_NS_REMOVE                                = ::WID_NS_REMOVE,                                ///< Remove NewGRF from active list.
		WID_NS_MOVE_UP                               = ::WID_NS_MOVE_UP,                               ///< Move NewGRF up in active list.
		WID_NS_MOVE_DOWN                             = ::WID_NS_MOVE_DOWN,                             ///< Move NewGRF down in active list.
		WID_NS_UPGRADE                               = ::WID_NS_UPGRADE,                               ///< Upgrade NewGRFs that have a newer version available.
		WID_NS_FILTER                                = ::WID_NS_FILTER,                                ///< Filter list of available NewGRFs.
		WID_NS_FILE_LIST                             = ::WID_NS_FILE_LIST,                             ///< List window of active NewGRFs.
		WID_NS_SCROLLBAR                             = ::WID_NS_SCROLLBAR,                             ///< Scrollbar for active NewGRF list.
		WID_NS_AVAIL_LIST                            = ::WID_NS_AVAIL_LIST,                            ///< List window of available NewGRFs.
		WID_NS_SCROLL2BAR                            = ::WID_NS_SCROLL2BAR,                            ///< Scrollbar for available NewGRF list.
		WID_NS_NEWGRF_INFO_TITLE                     = ::WID_NS_NEWGRF_INFO_TITLE,                     ///< Title for Info on selected NewGRF.
		WID_NS_NEWGRF_INFO                           = ::WID_NS_NEWGRF_INFO,                           ///< Panel for Info on selected NewGRF.
		WID_NS_OPEN_URL                              = ::WID_NS_OPEN_URL,                              ///< Open URL of NewGRF.
		WID_NS_NEWGRF_TEXTFILE                       = ::WID_NS_NEWGRF_TEXTFILE,                       ///< Open NewGRF readme, changelog (+1) or license (+2).
		WID_NS_SET_PARAMETERS                        = ::WID_NS_SET_PARAMETERS,                        ///< Open Parameters Window for selected NewGRF for editing parameters.
		WID_NS_VIEW_PARAMETERS                       = ::WID_NS_VIEW_PARAMETERS,                       ///< Open Parameters Window for selected NewGRF for viewing parameters.
		WID_NS_TOGGLE_PALETTE                        = ::WID_NS_TOGGLE_PALETTE,                        ///< Toggle Palette of selected, active NewGRF.
		WID_NS_APPLY_CHANGES                         = ::WID_NS_APPLY_CHANGES,                         ///< Apply changes to NewGRF config.
		WID_NS_RESCAN_FILES                          = ::WID_NS_RESCAN_FILES,                          ///< Rescan files (available NewGRFs).
		WID_NS_RESCAN_FILES2                         = ::WID_NS_RESCAN_FILES2,                         ///< Rescan files (active NewGRFs).
		WID_NS_CONTENT_DOWNLOAD                      = ::WID_NS_CONTENT_DOWNLOAD,                      ///< Open content download (available NewGRFs).
		WID_NS_CONTENT_DOWNLOAD2                     = ::WID_NS_CONTENT_DOWNLOAD2,                     ///< Open content download (active NewGRFs).
		WID_NS_SHOW_REMOVE                           = ::WID_NS_SHOW_REMOVE,                           ///< Select active list buttons (0, 1 = simple layout).
		WID_NS_SHOW_APPLY                            = ::WID_NS_SHOW_APPLY,                            ///< Select display of the buttons below the 'details'.
	};

	/** Widgets of the #SavePresetWindow class. */
	enum SavePresetWidgets {
		WID_SVP_PRESET_LIST                          = ::WID_SVP_PRESET_LIST,                          ///< List with available preset names.
		WID_SVP_SCROLLBAR                            = ::WID_SVP_SCROLLBAR,                            ///< Scrollbar for the list available preset names.
		WID_SVP_EDITBOX                              = ::WID_SVP_EDITBOX,                              ///< Edit box for changing the preset name.
		WID_SVP_CANCEL                               = ::WID_SVP_CANCEL,                               ///< Button to cancel saving the preset.
		WID_SVP_SAVE                                 = ::WID_SVP_SAVE,                                 ///< Button to save the preset.
	};

	/** Widgets of the #ScanProgressWindow class. */
	enum ScanProgressWidgets {
		WID_SP_PROGRESS_BAR                          = ::WID_SP_PROGRESS_BAR,                          ///< Simple progress bar.
		WID_SP_PROGRESS_TEXT                         = ::WID_SP_PROGRESS_TEXT,                         ///< Text explaining what is happening.
	};

	/* automatically generated from ../../widgets/news_widget.h */
	/** Widgets of the #NewsWindow class. */
	enum NewsWidgets {
		WID_N_PANEL                                  = ::WID_N_PANEL,                                  ///< Panel of the window.
		WID_N_TITLE                                  = ::WID_N_TITLE,                                  ///< Title of the company news.
		WID_N_HEADLINE                               = ::WID_N_HEADLINE,                               ///< The news headline.
		WID_N_CLOSEBOX                               = ::WID_N_CLOSEBOX,                               ///< Close the window.
		WID_N_DATE                                   = ::WID_N_DATE,                                   ///< Date of the news item.
		WID_N_CAPTION                                = ::WID_N_CAPTION,                                ///< Title bar of the window. Only used in small news items.
		WID_N_INSET                                  = ::WID_N_INSET,                                  ///< Inset around the viewport in the window. Only used in small news items.
		WID_N_VIEWPORT                               = ::WID_N_VIEWPORT,                               ///< Viewport in the window.
		WID_N_COMPANY_MSG                            = ::WID_N_COMPANY_MSG,                            ///< Message in company news items.
		WID_N_MESSAGE                                = ::WID_N_MESSAGE,                                ///< Space for displaying the message. Only used in small news items.
		WID_N_MGR_FACE                               = ::WID_N_MGR_FACE,                               ///< Face of the manager.
		WID_N_MGR_NAME                               = ::WID_N_MGR_NAME,                               ///< Name of the manager.
		WID_N_VEH_TITLE                              = ::WID_N_VEH_TITLE,                              ///< Vehicle new title.
		WID_N_VEH_BKGND                              = ::WID_N_VEH_BKGND,                              ///< Dark background of new vehicle news.
		WID_N_VEH_NAME                               = ::WID_N_VEH_NAME,                               ///< Name of the new vehicle.
		WID_N_VEH_SPR                                = ::WID_N_VEH_SPR,                                ///< Graphical display of the new vehicle.
		WID_N_VEH_INFO                               = ::WID_N_VEH_INFO,                               ///< Some technical data of the new vehicle.
		WID_N_SHOW_GROUP                             = ::WID_N_SHOW_GROUP,                             ///< Show vehicle's group
	};

	/** Widgets of the #MessageHistoryWindow class. */
	enum MessageHistoryWidgets {
		WID_MH_STICKYBOX                             = ::WID_MH_STICKYBOX,                             ///< Stickybox.
		WID_MH_BACKGROUND                            = ::WID_MH_BACKGROUND,                            ///< Background of the window.
		WID_MH_SCROLLBAR                             = ::WID_MH_SCROLLBAR,                             ///< Scrollbar for the list.
	};

	/* automatically generated from ../../widgets/object_widget.h */
	/** Widgets of the #BuildObjectWindow class. */
	enum BuildObjectWidgets {
		WID_BO_FILTER                                = ::WID_BO_FILTER,                                ///< The filter text box for the object list.
		WID_BO_CLASS_LIST                            = ::WID_BO_CLASS_LIST,                            ///< The list with classes.
		WID_BO_SCROLLBAR                             = ::WID_BO_SCROLLBAR,                             ///< The scrollbar associated with the list.
		WID_BO_OBJECT_MATRIX                         = ::WID_BO_OBJECT_MATRIX,                         ///< The matrix with preview sprites.
		WID_BO_OBJECT_SPRITE                         = ::WID_BO_OBJECT_SPRITE,                         ///< A preview sprite of the object.
		WID_BO_OBJECT_NAME                           = ::WID_BO_OBJECT_NAME,                           ///< The name of the selected object.
		WID_BO_OBJECT_SIZE                           = ::WID_BO_OBJECT_SIZE,                           ///< The size of the selected object.
		WID_BO_INFO                                  = ::WID_BO_INFO,                                  ///< Other information about the object (from the NewGRF).

		WID_BO_SELECT_MATRIX                         = ::WID_BO_SELECT_MATRIX,                         ///< Selection preview matrix of objects of a given class.
		WID_BO_SELECT_IMAGE                          = ::WID_BO_SELECT_IMAGE,                          ///< Preview image in the #WID_BO_SELECT_MATRIX.
		WID_BO_SELECT_SCROLL                         = ::WID_BO_SELECT_SCROLL,                         ///< Scrollbar next to the #WID_BO_SELECT_MATRIX.
	};

	/* automatically generated from ../../widgets/order_widget.h */
	/** Widgets of the #OrdersWindow class. */
	enum OrderWidgets {
		WID_O_CAPTION                                = ::WID_O_CAPTION,                                ///< Caption of the window.
		WID_O_TIMETABLE_VIEW                         = ::WID_O_TIMETABLE_VIEW,                         ///< Toggle timetable view.
		WID_O_ORDER_LIST                             = ::WID_O_ORDER_LIST,                             ///< Order list panel.
		WID_O_SCROLLBAR                              = ::WID_O_SCROLLBAR,                              ///< Order list scrollbar.
		WID_O_SKIP                                   = ::WID_O_SKIP,                                   ///< Skip current order.
		WID_O_MANAGE_LIST                            = ::WID_O_MANAGE_LIST,                            ///< Manage order list.
		WID_O_MGMT_BTN                               = ::WID_O_MGMT_BTN,                               ///< Management button.
		WID_O_MGMT_LIST_BTN                          = ::WID_O_MGMT_LIST_BTN,                          ///< Management list button.
		WID_O_DELETE                                 = ::WID_O_DELETE,                                 ///< Delete selected order.
		WID_O_STOP_SHARING                           = ::WID_O_STOP_SHARING,                           ///< Stop sharing orders.
		WID_O_NON_STOP                               = ::WID_O_NON_STOP,                               ///< Goto non-stop to destination.
		WID_O_GOTO                                   = ::WID_O_GOTO,                                   ///< Goto destination.
		WID_O_FULL_LOAD                              = ::WID_O_FULL_LOAD,                              ///< Select full load.
		WID_O_UNLOAD                                 = ::WID_O_UNLOAD,                                 ///< Select unload.
		WID_O_REFIT                                  = ::WID_O_REFIT,                                  ///< Select refit.
		WID_O_SERVICE                                = ::WID_O_SERVICE,                                ///< Select service (at depot).
		WID_O_EMPTY                                  = ::WID_O_EMPTY,                                  ///< Placeholder for refit dropdown when not owner.
		WID_O_REFIT_DROPDOWN                         = ::WID_O_REFIT_DROPDOWN,                         ///< Open refit options.
		WID_O_REVERSE                                = ::WID_O_REVERSE,                                ///< Select waypoint reverse type
		WID_O_COND_VARIABLE                          = ::WID_O_COND_VARIABLE,                          ///< Choose condition variable.
		WID_O_COND_COMPARATOR                        = ::WID_O_COND_COMPARATOR,                        ///< Choose condition type.
		WID_O_COND_VALUE                             = ::WID_O_COND_VALUE,                             ///< Choose condition value.
		WID_O_COND_CARGO                             = ::WID_O_COND_CARGO,                             ///< Choose condition cargo.
		WID_O_COND_AUX_CARGO                         = ::WID_O_COND_AUX_CARGO,                         ///< Choose condition cargo.
		WID_O_COND_SLOT                              = ::WID_O_COND_SLOT,                              ///< Choose condition slot.
		WID_O_COND_COUNTER                           = ::WID_O_COND_COUNTER,                           ///< Choose condition counter.
		WID_O_COND_TIME_DATE                         = ::WID_O_COND_TIME_DATE,                         ///< Choose time/date value.
		WID_O_COND_TIMETABLE                         = ::WID_O_COND_TIMETABLE,                         ///< Choose timetable value.
		WID_O_COND_SCHED_SELECT                      = ::WID_O_COND_SCHED_SELECT,                      ///< Choose scheduled dispatch schedule.
		WID_O_COND_AUX_VIA                           = ::WID_O_COND_AUX_VIA,                           ///< Condition via button.
		WID_O_COND_SCHED_TEST                        = ::WID_O_COND_SCHED_TEST,                        ///< Choose scheduled dispatch test.
		WID_O_RELEASE_SLOT                           = ::WID_O_RELEASE_SLOT,                           ///< Choose slot to release.
		WID_O_COUNTER_OP                             = ::WID_O_COUNTER_OP,                             ///< Choose counter operation.
		WID_O_CHANGE_COUNTER                         = ::WID_O_CHANGE_COUNTER,                         ///< Choose counter to change.
		WID_O_COUNTER_VALUE                          = ::WID_O_COUNTER_VALUE,                          ///< Choose counter value.
		WID_O_TEXT_LABEL                             = ::WID_O_TEXT_LABEL,                             ///< Choose text label.
		WID_O_SEL_COND_VALUE                         = ::WID_O_SEL_COND_VALUE,                         ///< Widget for conditional value or conditional cargo type.
		WID_O_SEL_COND_AUX                           = ::WID_O_SEL_COND_AUX,                           ///< Widget for auxiliary conditional cargo type.
		WID_O_SEL_COND_AUX2                          = ::WID_O_SEL_COND_AUX2,                          ///< Widget for auxiliary conditional via button.
		WID_O_SEL_MGMT                               = ::WID_O_SEL_MGMT,                               ///< Widget for management buttons.
		WID_O_SEL_TOP_LEFT                           = ::WID_O_SEL_TOP_LEFT,                           ///< #NWID_SELECTION widget for left part of the top row of the 'your train' order window.
		WID_O_SEL_TOP_MIDDLE                         = ::WID_O_SEL_TOP_MIDDLE,                         ///< #NWID_SELECTION widget for middle part of the top row of the 'your train' order window.
		WID_O_SEL_TOP_RIGHT                          = ::WID_O_SEL_TOP_RIGHT,                          ///< #NWID_SELECTION widget for right part of the top row of the 'your train' order window.
		WID_O_SEL_TOP_ROW_GROUNDVEHICLE              = ::WID_O_SEL_TOP_ROW_GROUNDVEHICLE,              ///< #NWID_SELECTION widget for the top row of the 'your train' order window.
		WID_O_SEL_TOP_ROW                            = ::WID_O_SEL_TOP_ROW,                            ///< #NWID_SELECTION widget for the top row of the 'your non-trains' order window.
		WID_O_SEL_BOTTOM_LEFT                        = ::WID_O_SEL_BOTTOM_LEFT,                        ///< #NWID_SELECTION widget for the left part of the bottom row of the 'your train' order window.
		WID_O_SEL_BOTTOM_MIDDLE                      = ::WID_O_SEL_BOTTOM_MIDDLE,                      ///< #NWID_SELECTION widget for the middle part of the bottom row of the 'your train' order window.
		WID_O_SEL_SHARED                             = ::WID_O_SEL_SHARED,                             ///< #NWID_SELECTION widget for WID_O_SHARED_ORDER_LIST and WID_O_ADD_VEH_GROUP
		WID_O_SHARED_ORDER_LIST                      = ::WID_O_SHARED_ORDER_LIST,                      ///< Open list of shared vehicles.
		WID_O_ADD_VEH_GROUP                          = ::WID_O_ADD_VEH_GROUP,                          ///< Add single vehicle to new group button.
		WID_O_SEL_OCCUPANCY                          = ::WID_O_SEL_OCCUPANCY,                          ///< #NWID_SELECTION widget for the occupancy list panel.
		WID_O_OCCUPANCY_LIST                         = ::WID_O_OCCUPANCY_LIST,                         ///< Occupancy list panel.
		WID_O_OCCUPANCY_TOGGLE                       = ::WID_O_OCCUPANCY_TOGGLE,                       ///< Toggle display of occupancy measures.
		WID_O_TOGGLE_SIZE                            = ::WID_O_TOGGLE_SIZE,                            ///< Toggle show order management button.
	};

	/** Widgets of the #CargoTypeOrdersWindow class. */
	enum CargoTypeOrdersWidgets {
		WID_CTO_CAPTION                              = ::WID_CTO_CAPTION,                              ///< Caption of the window.
		WID_CTO_HEADER                               = ::WID_CTO_HEADER,                               ///< Window header.
		WID_CTO_CLOSEBTN                             = ::WID_CTO_CLOSEBTN,                             ///< Close button.
		WID_CTO_SET_TO_ALL_LABEL                     = ::WID_CTO_SET_TO_ALL_LABEL,                     ///< 'Set to all' dropdown label
		WID_CTO_SET_TO_ALL_DROPDOWN                  = ::WID_CTO_SET_TO_ALL_DROPDOWN,                  ///< 'Set to all' dropdown
		WID_CTO_CARGO_ROW_FIRST                      = ::WID_CTO_CARGO_ROW_FIRST,                      ///< First cargo type order row.
		WID_CTO_CARGO_ROW_LAST                       = ::WID_CTO_CARGO_ROW_LAST,                       ///< Last cargo type order row.
		WID_CTO_CARGO_LABEL_FIRST                    = ::WID_CTO_CARGO_LABEL_FIRST,                    ///< First cargo label.
		WID_CTO_CARGO_LABEL_LAST                     = ::WID_CTO_CARGO_LABEL_LAST,                     ///< Last cargo label.
		WID_CTO_CARGO_DROPDOWN_FIRST                 = ::WID_CTO_CARGO_DROPDOWN_FIRST,                 ///< First order dropdown.
		WID_CTO_CARGO_DROPDOWN_LAST                  = ::WID_CTO_CARGO_DROPDOWN_LAST,                  ///< Last order dropdown.
		WID_CTO_SELECT                               = ::WID_CTO_SELECT,                               ///< Right column select panel
	};

	/* automatically generated from ../../widgets/osk_widget.h */
	/** Widgets of the #OskWindow class. */
	enum OnScreenKeyboardWidgets {
		WID_OSK_CAPTION                              = ::WID_OSK_CAPTION,                              ///< Caption of window.
		WID_OSK_TEXT                                 = ::WID_OSK_TEXT,                                 ///< Edit box.
		WID_OSK_CANCEL                               = ::WID_OSK_CANCEL,                               ///< Cancel key.
		WID_OSK_OK                                   = ::WID_OSK_OK,                                   ///< Ok key.
		WID_OSK_BACKSPACE                            = ::WID_OSK_BACKSPACE,                            ///< Backspace key.
		WID_OSK_SPECIAL                              = ::WID_OSK_SPECIAL,                              ///< Special key (at keyboards often used for tab key).
		WID_OSK_CAPS                                 = ::WID_OSK_CAPS,                                 ///< Capslock key.
		WID_OSK_SHIFT                                = ::WID_OSK_SHIFT,                                ///< Shift(lock) key.
		WID_OSK_SPACE                                = ::WID_OSK_SPACE,                                ///< Space bar.
		WID_OSK_LEFT                                 = ::WID_OSK_LEFT,                                 ///< Cursor left key.
		WID_OSK_RIGHT                                = ::WID_OSK_RIGHT,                                ///< Cursor right key.
		WID_OSK_LETTERS                              = ::WID_OSK_LETTERS,                              ///< First widget of the 'normal' keys.

		WID_OSK_NUMBERS_FIRST                        = ::WID_OSK_NUMBERS_FIRST,                        ///< First widget of the numbers row.
		WID_OSK_NUMBERS_LAST                         = ::WID_OSK_NUMBERS_LAST,                         ///< Last widget of the numbers row.

		WID_OSK_QWERTY_FIRST                         = ::WID_OSK_QWERTY_FIRST,                         ///< First widget of the qwerty row.
		WID_OSK_QWERTY_LAST                          = ::WID_OSK_QWERTY_LAST,                          ///< Last widget of the qwerty row.

		WID_OSK_ASDFG_FIRST                          = ::WID_OSK_ASDFG_FIRST,                          ///< First widget of the asdfg row.
		WID_OSK_ASDFG_LAST                           = ::WID_OSK_ASDFG_LAST,                           ///< Last widget of the asdfg row.

		WID_OSK_ZXCVB_FIRST                          = ::WID_OSK_ZXCVB_FIRST,                          ///< First widget of the zxcvb row.
		WID_OSK_ZXCVB_LAST                           = ::WID_OSK_ZXCVB_LAST,                           ///< Last widget of the zxcvb row.
	};

	/* automatically generated from ../../widgets/plans_widget.h */
	/** Widgets of the #PlansWindow class. */
	enum PlansWidgets {
		WID_PLN_CAPTION                              = ::WID_PLN_CAPTION,                              ///< Caption of the window.
		WID_PLN_LIST                                 = ::WID_PLN_LIST,
		WID_PLN_SCROLLBAR                            = ::WID_PLN_SCROLLBAR,
		WID_PLN_NEW                                  = ::WID_PLN_NEW,
		WID_PLN_ADD_LINES                            = ::WID_PLN_ADD_LINES,
		WID_PLN_VISIBILITY                           = ::WID_PLN_VISIBILITY,
		WID_PLN_COLOUR                               = ::WID_PLN_COLOUR,
		WID_PLN_HIDE_ALL                             = ::WID_PLN_HIDE_ALL,
		WID_PLN_SHOW_ALL                             = ::WID_PLN_SHOW_ALL,
		WID_PLN_DELETE                               = ::WID_PLN_DELETE,
		WID_PLN_HIDE_ALL_SEL                         = ::WID_PLN_HIDE_ALL_SEL,
		WID_PLN_RENAME                               = ::WID_PLN_RENAME,
	};

	/* automatically generated from ../../widgets/rail_widget.h */
	/** Widgets of the #BuildRailToolbarWindow class. */
	enum RailToolbarWidgets {
		/* Name starts with RA instead of R, because of collision with RoadToolbarWidgets */
		WID_RAT_CAPTION                              = ::WID_RAT_CAPTION,                              ///< Caption of the window.
		WID_RAT_BUILD_NS                             = ::WID_RAT_BUILD_NS,                             ///< Build rail along the game view Y axis.
		WID_RAT_BUILD_X                              = ::WID_RAT_BUILD_X,                              ///< Build rail along the game grid X axis.
		WID_RAT_BUILD_EW                             = ::WID_RAT_BUILD_EW,                             ///< Build rail along the game view X axis.
		WID_RAT_BUILD_Y                              = ::WID_RAT_BUILD_Y,                              ///< Build rail along the game grid Y axis.
		WID_RAT_AUTORAIL                             = ::WID_RAT_AUTORAIL,                             ///< Autorail tool.
		WID_RAT_POLYRAIL                             = ::WID_RAT_POLYRAIL,                             ///< Polyline rail tool.
		WID_RAT_DEMOLISH                             = ::WID_RAT_DEMOLISH,                             ///< Destroy something with dynamite!
		WID_RAT_BUILD_DEPOT                          = ::WID_RAT_BUILD_DEPOT,                          ///< Build a depot.
		WID_RAT_BUILD_WAYPOINT                       = ::WID_RAT_BUILD_WAYPOINT,                       ///< Build a waypoint.
		WID_RAT_BUILD_STATION                        = ::WID_RAT_BUILD_STATION,                        ///< Build a station.
		WID_RAT_BUILD_SIGNALS                        = ::WID_RAT_BUILD_SIGNALS,                        ///< Build signals.
		WID_RAT_BUILD_BRIDGE                         = ::WID_RAT_BUILD_BRIDGE,                         ///< Build a bridge.
		WID_RAT_BUILD_TUNNEL                         = ::WID_RAT_BUILD_TUNNEL,                         ///< Build a tunnel.
		WID_RAT_REMOVE                               = ::WID_RAT_REMOVE,                               ///< Bulldozer to remove rail.
		WID_RAT_CONVERT_RAIL                         = ::WID_RAT_CONVERT_RAIL,                         ///< Convert other rail to this type.
	};

	/** Widgets of the #BuildRailStationWindow class. */
	enum BuildRailStationWidgets {
		/* Name starts with BRA instead of BR, because of collision with BuildRoadStationWidgets */
		WID_BRAS_PLATFORM_DIR_X                      = ::WID_BRAS_PLATFORM_DIR_X,                      ///< Button to select '/' view.
		WID_BRAS_PLATFORM_DIR_Y                      = ::WID_BRAS_PLATFORM_DIR_Y,                      ///< Button to select '\' view.

		WID_BRAS_PLATFORM_NUM_1                      = ::WID_BRAS_PLATFORM_NUM_1,                      ///< Button to select stations with a single platform.
		WID_BRAS_PLATFORM_NUM_2                      = ::WID_BRAS_PLATFORM_NUM_2,                      ///< Button to select stations with 2 platforms.
		WID_BRAS_PLATFORM_NUM_3                      = ::WID_BRAS_PLATFORM_NUM_3,                      ///< Button to select stations with 3 platforms.
		WID_BRAS_PLATFORM_NUM_4                      = ::WID_BRAS_PLATFORM_NUM_4,                      ///< Button to select stations with 4 platforms.
		WID_BRAS_PLATFORM_NUM_5                      = ::WID_BRAS_PLATFORM_NUM_5,                      ///< Button to select stations with 5 platforms.
		WID_BRAS_PLATFORM_NUM_6                      = ::WID_BRAS_PLATFORM_NUM_6,                      ///< Button to select stations with 6 platforms.
		WID_BRAS_PLATFORM_NUM_7                      = ::WID_BRAS_PLATFORM_NUM_7,                      ///< Button to select stations with 7 platforms.

		WID_BRAS_PLATFORM_LEN_1                      = ::WID_BRAS_PLATFORM_LEN_1,                      ///< Button to select single tile length station platforms.
		WID_BRAS_PLATFORM_LEN_2                      = ::WID_BRAS_PLATFORM_LEN_2,                      ///< Button to select 2 tiles length station platforms.
		WID_BRAS_PLATFORM_LEN_3                      = ::WID_BRAS_PLATFORM_LEN_3,                      ///< Button to select 3 tiles length station platforms.
		WID_BRAS_PLATFORM_LEN_4                      = ::WID_BRAS_PLATFORM_LEN_4,                      ///< Button to select 4 tiles length station platforms.
		WID_BRAS_PLATFORM_LEN_5                      = ::WID_BRAS_PLATFORM_LEN_5,                      ///< Button to select 5 tiles length station platforms.
		WID_BRAS_PLATFORM_LEN_6                      = ::WID_BRAS_PLATFORM_LEN_6,                      ///< Button to select 6 tiles length station platforms.
		WID_BRAS_PLATFORM_LEN_7                      = ::WID_BRAS_PLATFORM_LEN_7,                      ///< Button to select 7 tiles length station platforms.

		WID_BRAS_PLATFORM_DRAG_N_DROP                = ::WID_BRAS_PLATFORM_DRAG_N_DROP,                ///< Button to enable drag and drop type station placement.

		WID_BRAS_HIGHLIGHT_OFF                       = ::WID_BRAS_HIGHLIGHT_OFF,                       ///< Button for turning coverage highlighting off.
		WID_BRAS_HIGHLIGHT_ON                        = ::WID_BRAS_HIGHLIGHT_ON,                        ///< Button for turning coverage highlighting on.
		WID_BRAS_COVERAGE_TEXTS                      = ::WID_BRAS_COVERAGE_TEXTS,                      ///< Empty space for the coverage texts.

		WID_BRAS_MATRIX                              = ::WID_BRAS_MATRIX,                              ///< Matrix widget displaying the available stations.
		WID_BRAS_IMAGE                               = ::WID_BRAS_IMAGE,                               ///< Panel used at each cell of the matrix.
		WID_BRAS_MATRIX_SCROLL                       = ::WID_BRAS_MATRIX_SCROLL,                       ///< Scrollbar of the matrix widget.

		WID_BRAS_FILTER_CONTAINER                    = ::WID_BRAS_FILTER_CONTAINER,                    ///< Container for the filter text box for the station class list.
		WID_BRAS_FILTER_EDITBOX                      = ::WID_BRAS_FILTER_EDITBOX,                      ///< Filter text box for the station class list.
		WID_BRAS_SHOW_NEWST_DEFSIZE                  = ::WID_BRAS_SHOW_NEWST_DEFSIZE,                  ///< Selection for default-size button for newstation.
		WID_BRAS_SHOW_NEWST_ADDITIONS                = ::WID_BRAS_SHOW_NEWST_ADDITIONS,                ///< Selection for newstation class selection list.
		WID_BRAS_SHOW_NEWST_MATRIX                   = ::WID_BRAS_SHOW_NEWST_MATRIX,                   ///< Selection for newstation image matrix.
		WID_BRAS_SHOW_NEWST_RESIZE                   = ::WID_BRAS_SHOW_NEWST_RESIZE,                   ///< Selection for panel and resize at bottom right for newstation.
		WID_BRAS_SHOW_NEWST_TYPE                     = ::WID_BRAS_SHOW_NEWST_TYPE,                     ///< Display of selected station type.
		WID_BRAS_NEWST_LIST                          = ::WID_BRAS_NEWST_LIST,                          ///< List with available newstation classes.
		WID_BRAS_NEWST_SCROLL                        = ::WID_BRAS_NEWST_SCROLL,                        ///< Scrollbar of the #WID_BRAS_NEWST_LIST.

		WID_BRAS_PLATFORM_NUM_BEGIN                  = ::WID_BRAS_PLATFORM_NUM_BEGIN,                  ///< Helper for determining the chosen platform width.
		WID_BRAS_PLATFORM_LEN_BEGIN                  = ::WID_BRAS_PLATFORM_LEN_BEGIN,                  ///< Helper for determining the chosen platform length.
	};

	/** Widgets of the #BuildSignalWindow class. */
	enum BuildSignalWidgets {
		WID_BS_CAPTION                               = ::WID_BS_CAPTION,                               ///< Caption for the Signal Selection window.
		WID_BS_TOGGLE_SIZE                           = ::WID_BS_TOGGLE_SIZE,                           ///< Toggle showing advanced signal types.
		WID_BS_SEMAPHORE_NORM                        = ::WID_BS_SEMAPHORE_NORM,                        ///< Build a semaphore normal block signal
		WID_BS_SEMAPHORE_ENTRY                       = ::WID_BS_SEMAPHORE_ENTRY,                       ///< Build a semaphore entry block signal
		WID_BS_SEMAPHORE_EXIT                        = ::WID_BS_SEMAPHORE_EXIT,                        ///< Build a semaphore exit block signal
		WID_BS_SEMAPHORE_COMBO                       = ::WID_BS_SEMAPHORE_COMBO,                       ///< Build a semaphore combo block signal
		WID_BS_SEMAPHORE_PROG                        = ::WID_BS_SEMAPHORE_PROG,                        ///< Build a semahore programmable pre-signal
		WID_BS_SEMAPHORE_PBS                         = ::WID_BS_SEMAPHORE_PBS,                         ///< Build a semaphore path signal.
		WID_BS_SEMAPHORE_PBS_OWAY                    = ::WID_BS_SEMAPHORE_PBS_OWAY,                    ///< Build a semaphore one way path signal.
		WID_BS_SEMAPHORE_NO_ENTRY                    = ::WID_BS_SEMAPHORE_NO_ENTRY,                    ///< Build a semaphore no-entry signal.
		WID_BS_ELECTRIC_NORM                         = ::WID_BS_ELECTRIC_NORM,                         ///< Build an electric normal block signal
		WID_BS_ELECTRIC_ENTRY                        = ::WID_BS_ELECTRIC_ENTRY,                        ///< Build an electric entry block signal
		WID_BS_ELECTRIC_EXIT                         = ::WID_BS_ELECTRIC_EXIT,                         ///< Build an electric exit block signal
		WID_BS_ELECTRIC_COMBO                        = ::WID_BS_ELECTRIC_COMBO,                        ///< Build an electric combo block signal
		WID_BS_ELECTRIC_PROG                         = ::WID_BS_ELECTRIC_PROG,                         ///< Build an electric programmable pre-signal
		WID_BS_ELECTRIC_PBS                          = ::WID_BS_ELECTRIC_PBS,                          ///< Build an electric path signal.
		WID_BS_ELECTRIC_PBS_OWAY                     = ::WID_BS_ELECTRIC_PBS_OWAY,                     ///< Build an electric one way path signal.
		WID_BS_ELECTRIC_NO_ENTRY                     = ::WID_BS_ELECTRIC_NO_ENTRY,                     ///< Build an electric no-entry signal.
		WID_BS_CONVERT                               = ::WID_BS_CONVERT,                               ///< Convert the signal.
		WID_BS_TRACE_RESTRICT                        = ::WID_BS_TRACE_RESTRICT,                        ///< Open trace restrict window.
		WID_BS_PROGRAM                               = ::WID_BS_PROGRAM,                               ///< Enter program to prog signal
		WID_BS_DRAG_SIGNALS_DENSITY_LABEL            = ::WID_BS_DRAG_SIGNALS_DENSITY_LABEL,            ///< The current signal density.
		WID_BS_DRAG_SIGNALS_DENSITY_DECREASE         = ::WID_BS_DRAG_SIGNALS_DENSITY_DECREASE,         ///< Decrease the signal density.
		WID_BS_DRAG_SIGNALS_DENSITY_INCREASE         = ::WID_BS_DRAG_SIGNALS_DENSITY_INCREASE,         ///< Increase the signal density.
		WID_BS_TOGGLE_SIZE_SEL                       = ::WID_BS_TOGGLE_SIZE_SEL,                       ///< NWID_SELECTION for WID_BS_TOGGLE_SIZE
		WID_BS_SEMAPHORE_NORM_SEL                    = ::WID_BS_SEMAPHORE_NORM_SEL,                    ///< NWID_SELECTION for WID_BS_SEMAPHORE_NORM
		WID_BS_ELECTRIC_NORM_SEL                     = ::WID_BS_ELECTRIC_NORM_SEL,                     ///< NWID_SELECTION for WID_BS_ELECTRIC_NORM
		WID_BS_SEMAPHORE_ENTRY_SEL                   = ::WID_BS_SEMAPHORE_ENTRY_SEL,                   ///< NWID_SELECTION for WID_BS_SEMAPHORE_ENTRY
		WID_BS_ELECTRIC_ENTRY_SEL                    = ::WID_BS_ELECTRIC_ENTRY_SEL,                    ///< NWID_SELECTION for WID_BS_ELECTRIC_ENTRY
		WID_BS_SEMAPHORE_EXIT_SEL                    = ::WID_BS_SEMAPHORE_EXIT_SEL,                    ///< NWID_SELECTION for WID_BS_SEMAPHORE_EXIT
		WID_BS_ELECTRIC_EXIT_SEL                     = ::WID_BS_ELECTRIC_EXIT_SEL,                     ///< NWID_SELECTION for WID_BS_ELECTRIC_EXIT
		WID_BS_SEMAPHORE_COMBO_SEL                   = ::WID_BS_SEMAPHORE_COMBO_SEL,                   ///< NWID_SELECTION for WID_BS_SEMAPHORE_COMBO
		WID_BS_ELECTRIC_COMBO_SEL                    = ::WID_BS_ELECTRIC_COMBO_SEL,                    ///< NWID_SELECTION for WID_BS_ELECTRIC_COMBO
		WID_BS_SEMAPHORE_PROG_SEL                    = ::WID_BS_SEMAPHORE_PROG_SEL,                    ///< NWID_SELECTION for WID_BS_SEMAPHORE_PROG
		WID_BS_ELECTRIC_PROG_SEL                     = ::WID_BS_ELECTRIC_PROG_SEL,                     ///< NWID_SELECTION for WID_BS_ELECTRIC_PROG
		WID_BS_SEMAPHORE_NOEN_SEL                    = ::WID_BS_SEMAPHORE_NOEN_SEL,                    ///< NWID_SELECTION for WID_BS_SEMAPHORE_NO_ENTRY
		WID_BS_ELECTRIC_NOEN_SEL                     = ::WID_BS_ELECTRIC_NOEN_SEL,                     ///< NWID_SELECTION for WID_BS_ELECTRIC_NO_ENTRY
		WID_BS_PROGRAM_SEL                           = ::WID_BS_PROGRAM_SEL,                           ///< NWID_SELECTION for WID_BS_PROGRAM
		WID_BS_STYLE                                 = ::WID_BS_STYLE,                                 ///< Style selection dropdown
		WID_BS_STYLE_SEL                             = ::WID_BS_STYLE_SEL,                             ///< NWID_SELECTION for WID_BS_STYLE
	};

	/** Widgets of the #BuildRailDepotWindow class. */
	enum BuildRailDepotWidgets {
		/* Name starts with BRA instead of BR, because of collision with BuildRoadDepotWidgets */
		WID_BRAD_DEPOT_NE                            = ::WID_BRAD_DEPOT_NE,                            ///< Build a depot with the entrance in the north east.
		WID_BRAD_DEPOT_SE                            = ::WID_BRAD_DEPOT_SE,                            ///< Build a depot with the entrance in the south east.
		WID_BRAD_DEPOT_SW                            = ::WID_BRAD_DEPOT_SW,                            ///< Build a depot with the entrance in the south west.
		WID_BRAD_DEPOT_NW                            = ::WID_BRAD_DEPOT_NW,                            ///< Build a depot with the entrance in the north west.
	};

	/** Widgets of the #BuildRailWaypointWindow class. */
	enum BuildRailWaypointWidgets {
		WID_BRW_WAYPOINT_MATRIX                      = ::WID_BRW_WAYPOINT_MATRIX,                      ///< Matrix with waypoints.
		WID_BRW_WAYPOINT                             = ::WID_BRW_WAYPOINT,                             ///< A single waypoint.
		WID_BRW_SCROLL                               = ::WID_BRW_SCROLL,                               ///< Scrollbar for the matrix.
	};

	/* automatically generated from ../../widgets/road_widget.h */
	/** Widgets of the #BuildRoadToolbarWindow class. */
	enum RoadToolbarWidgets {
		/* Name starts with RO instead of R, because of collision with RailToolbarWidgets */
		WID_ROT_CAPTION                              = ::WID_ROT_CAPTION,                              ///< Caption of the window
		WID_ROT_ROAD_X                               = ::WID_ROT_ROAD_X,                               ///< Build road in x-direction.
		WID_ROT_ROAD_Y                               = ::WID_ROT_ROAD_Y,                               ///< Build road in y-direction.
		WID_ROT_AUTOROAD                             = ::WID_ROT_AUTOROAD,                             ///< Autorail.
		WID_ROT_DEMOLISH                             = ::WID_ROT_DEMOLISH,                             ///< Demolish.
		WID_ROT_DEPOT                                = ::WID_ROT_DEPOT,                                ///< Build depot.
		WID_ROT_BUILD_WAYPOINT                       = ::WID_ROT_BUILD_WAYPOINT,                       ///< Build waypoint.
		WID_ROT_BUS_STATION                          = ::WID_ROT_BUS_STATION,                          ///< Build bus station.
		WID_ROT_TRUCK_STATION                        = ::WID_ROT_TRUCK_STATION,                        ///< Build truck station.
		WID_ROT_ONE_WAY                              = ::WID_ROT_ONE_WAY,                              ///< Build one-way road.
		WID_ROT_BUILD_BRIDGE                         = ::WID_ROT_BUILD_BRIDGE,                         ///< Build bridge.
		WID_ROT_BUILD_TUNNEL                         = ::WID_ROT_BUILD_TUNNEL,                         ///< Build tunnel.
		WID_ROT_REMOVE                               = ::WID_ROT_REMOVE,                               ///< Remove road.
		WID_ROT_CONVERT_ROAD                         = ::WID_ROT_CONVERT_ROAD,                         ///< Convert road.
	};

	/** Widgets of the #BuildRoadDepotWindow class. */
	enum BuildRoadDepotWidgets {
		/* Name starts with BRO instead of BR, because of collision with BuildRailDepotWidgets */
		WID_BROD_CAPTION                             = ::WID_BROD_CAPTION,                             ///< Caption of the window.
		WID_BROD_DEPOT_NE                            = ::WID_BROD_DEPOT_NE,                            ///< Depot with NE entry.
		WID_BROD_DEPOT_SE                            = ::WID_BROD_DEPOT_SE,                            ///< Depot with SE entry.
		WID_BROD_DEPOT_SW                            = ::WID_BROD_DEPOT_SW,                            ///< Depot with SW entry.
		WID_BROD_DEPOT_NW                            = ::WID_BROD_DEPOT_NW,                            ///< Depot with NW entry.
	};

	/** Widgets of the #BuildRoadStationWindow class. */
	enum BuildRoadStationWidgets {
		/* Name starts with BRO instead of BR, because of collision with BuildRailStationWidgets */
		WID_BROS_CAPTION                             = ::WID_BROS_CAPTION,                             ///< Caption of the window.
		WID_BROS_BACKGROUND                          = ::WID_BROS_BACKGROUND,                          ///< Background of the window.
		WID_BROS_STATION_NE                          = ::WID_BROS_STATION_NE,                          ///< Terminal station with NE entry.
		WID_BROS_STATION_SE                          = ::WID_BROS_STATION_SE,                          ///< Terminal station with SE entry.
		WID_BROS_STATION_SW                          = ::WID_BROS_STATION_SW,                          ///< Terminal station with SW entry.
		WID_BROS_STATION_NW                          = ::WID_BROS_STATION_NW,                          ///< Terminal station with NW entry.
		WID_BROS_STATION_X                           = ::WID_BROS_STATION_X,                           ///< Drive-through station in x-direction.
		WID_BROS_STATION_Y                           = ::WID_BROS_STATION_Y,                           ///< Drive-through station in y-direction.
		WID_BROS_LT_OFF                              = ::WID_BROS_LT_OFF,                              ///< Turn off area highlight.
		WID_BROS_LT_ON                               = ::WID_BROS_LT_ON,                               ///< Turn on area highlight.
		WID_BROS_INFO                                = ::WID_BROS_INFO,                                ///< Station acceptance info.

		WID_BROS_MATRIX                              = ::WID_BROS_MATRIX,                              ///< Matrix widget displaying all available road stops.
		WID_BROS_IMAGE                               = ::WID_BROS_IMAGE,                               ///< Panel used for each image of the matrix.
		WID_BROS_MATRIX_SCROLL                       = ::WID_BROS_MATRIX_SCROLL,                       ///< Scrollbar of the #WID_BROS_SHOW_NEWST_ADDITIONS.

		WID_BROS_FILTER_CONTAINER                    = ::WID_BROS_FILTER_CONTAINER,                    ///< Container for the filter text box for the road stop class list.
		WID_BROS_FILTER_EDITBOX                      = ::WID_BROS_FILTER_EDITBOX,                      ///< Filter text box for the road stop class list.
		WID_BROS_SHOW_NEWST_DEFSIZE                  = ::WID_BROS_SHOW_NEWST_DEFSIZE,                  ///< Selection for default-size button for new road stops.
		WID_BROS_SHOW_NEWST_ADDITIONS                = ::WID_BROS_SHOW_NEWST_ADDITIONS,                ///< Selection for new class selection list.
		WID_BROS_SHOW_NEWST_MATRIX                   = ::WID_BROS_SHOW_NEWST_MATRIX,                   ///< Selection for new stop image matrix.
		WID_BROS_SHOW_NEWST_RESIZE                   = ::WID_BROS_SHOW_NEWST_RESIZE,                   ///< Selection for panel and resize at bottom right for new stops.
		WID_BROS_SHOW_NEWST_ORIENTATION              = ::WID_BROS_SHOW_NEWST_ORIENTATION,              ///< Selection for the orientation string for new stops.
		WID_BROS_SHOW_NEWST_TYPE_SEL                 = ::WID_BROS_SHOW_NEWST_TYPE_SEL,                 ///< Selection for the type name.
		WID_BROS_SHOW_NEWST_TYPE                     = ::WID_BROS_SHOW_NEWST_TYPE,                     ///< Display of selected stop type.
		WID_BROS_NEWST_LIST                          = ::WID_BROS_NEWST_LIST,                          ///< List with new road stops.
		WID_BROS_NEWST_SCROLL                        = ::WID_BROS_NEWST_SCROLL,                        ///< Scrollbar of the #WID_BROS_NEWST_LIST.
	};

	/** Widgets of the #BuildRoadWaypointWindow class. */
	enum BuildRoadWaypointWidgets {
		WID_BROW_WAYPOINT_MATRIX                     = ::WID_BROW_WAYPOINT_MATRIX,                     ///< Matrix with waypoints.
		WID_BROW_WAYPOINT                            = ::WID_BROW_WAYPOINT,                            ///< A single waypoint.
		WID_BROW_SCROLL                              = ::WID_BROW_SCROLL,                              ///< Scrollbar for the matrix.
	};

	/* automatically generated from ../../widgets/screenshot_widget.h */
	/** Widgets of the #ScreenshotWindow class. */
	enum ScreenshotWindowWidgets {
		WID_SC_TAKE                                  = ::WID_SC_TAKE,                                  ///< Button for taking a normal screenshot
		WID_SC_TAKE_ZOOMIN                           = ::WID_SC_TAKE_ZOOMIN,                           ///< Button for taking a zoomed in screenshot
		WID_SC_TAKE_DEFAULTZOOM                      = ::WID_SC_TAKE_DEFAULTZOOM,                      ///< Button for taking a screenshot at normal zoom
		WID_SC_TAKE_WORLD                            = ::WID_SC_TAKE_WORLD,                            ///< Button for taking a screenshot of the whole world
		WID_SC_TAKE_WORLD_ZOOM                       = ::WID_SC_TAKE_WORLD_ZOOM,                       ///< Button for taking a screenshot of the whole world at the current zoom level
		WID_SC_TAKE_HEIGHTMAP                        = ::WID_SC_TAKE_HEIGHTMAP,                        ///< Button for taking a heightmap "screenshot"
		WID_SC_TAKE_MINIMAP                          = ::WID_SC_TAKE_MINIMAP,                          ///< Button for taking a minimap screenshot
		WID_SC_TAKE_TOPOGRAPHY                       = ::WID_SC_TAKE_TOPOGRAPHY,                       ///< Button for taking a topography screenshot
		WID_SC_TAKE_INDUSTRY                         = ::WID_SC_TAKE_INDUSTRY,                         ///< Button for taking a industry screenshot
	};

	/* automatically generated from ../../widgets/script_widget.h */
	/** Widgets of the #ScriptListWindow class. */
	enum ScriptListWidgets {
		WID_SCRL_CAPTION                             = ::WID_SCRL_CAPTION,                             ///< Caption of the window.
		WID_SCRL_LIST                                = ::WID_SCRL_LIST,                                ///< The matrix with all available Scripts.
		WID_SCRL_SCROLLBAR                           = ::WID_SCRL_SCROLLBAR,                           ///< Scrollbar next to the Script list.
		WID_SCRL_INFO_BG                             = ::WID_SCRL_INFO_BG,                             ///< Panel to draw some Script information on.
		WID_SCRL_ACCEPT                              = ::WID_SCRL_ACCEPT,                              ///< Accept button.
		WID_SCRL_CANCEL                              = ::WID_SCRL_CANCEL,                              ///< Cancel button.
	};

	/** Widgets of the #ScriptSettingsWindow class. */
	enum ScriptSettingsWidgets {
		WID_SCRS_CAPTION                             = ::WID_SCRS_CAPTION,                             ///< Caption of the window.
		WID_SCRS_BACKGROUND                          = ::WID_SCRS_BACKGROUND,                          ///< Panel to draw the settings on.
		WID_SCRS_SCROLLBAR                           = ::WID_SCRS_SCROLLBAR,                           ///< Scrollbar to scroll through all settings.
		WID_SCRS_ACCEPT                              = ::WID_SCRS_ACCEPT,                              ///< Accept button.
		WID_SCRS_RESET                               = ::WID_SCRS_RESET,                               ///< Reset button.
	};

	/** Widgets of the #ScriptDebugWindow class. */
	enum ScriptDebugWidgets {
		WID_SCRD_VIEW                                = ::WID_SCRD_VIEW,                                ///< The row of company buttons.
		WID_SCRD_NAME_TEXT                           = ::WID_SCRD_NAME_TEXT,                           ///< Name of the current selected.
		WID_SCRD_SETTINGS                            = ::WID_SCRD_SETTINGS,                            ///< Settings button.
		WID_SCRD_SCRIPT_GAME                         = ::WID_SCRD_SCRIPT_GAME,                         ///< Game Script button.
		WID_SCRD_RELOAD_TOGGLE                       = ::WID_SCRD_RELOAD_TOGGLE,                       ///< Reload button.
		WID_SCRD_LOG_PANEL                           = ::WID_SCRD_LOG_PANEL,                           ///< Panel where the log is in.
		WID_SCRD_SCROLLBAR                           = ::WID_SCRD_SCROLLBAR,                           ///< Scrollbar of the log panel.
		WID_SCRD_COMPANY_BUTTON_START                = ::WID_SCRD_COMPANY_BUTTON_START,                ///< Buttons in the VIEW.
		WID_SCRD_COMPANY_BUTTON_END                  = ::WID_SCRD_COMPANY_BUTTON_END,                  ///< Last possible button in the VIEW.
		WID_SCRD_BREAK_STRING_WIDGETS                = ::WID_SCRD_BREAK_STRING_WIDGETS,                ///< The panel to handle the breaking on string.
		WID_SCRD_BREAK_STR_ON_OFF_BTN                = ::WID_SCRD_BREAK_STR_ON_OFF_BTN,                ///< Enable breaking on string.
		WID_SCRD_BREAK_STR_EDIT_BOX                  = ::WID_SCRD_BREAK_STR_EDIT_BOX,                  ///< Edit box for the string to break on.
		WID_SCRD_MATCH_CASE_BTN                      = ::WID_SCRD_MATCH_CASE_BTN,                      ///< Checkbox to use match caching or not.
		WID_SCRD_CONTINUE_BTN                        = ::WID_SCRD_CONTINUE_BTN,                        ///< Continue button.
	};

	/* automatically generated from ../../widgets/settings_widget.h */
	/** Widgets of the #GameOptionsWindow class. */
	enum GameOptionsWidgets {
		WID_GO_BACKGROUND                            = ::WID_GO_BACKGROUND,                            ///< Background of the window.
		WID_GO_CURRENCY_DROPDOWN                     = ::WID_GO_CURRENCY_DROPDOWN,                     ///< Currency dropdown.
		WID_GO_DISTANCE_DROPDOWN                     = ::WID_GO_DISTANCE_DROPDOWN,                     ///< Measuring unit dropdown.
		WID_GO_AUTOSAVE_DROPDOWN                     = ::WID_GO_AUTOSAVE_DROPDOWN,                     ///< Dropdown to say how often to autosave.
		WID_GO_LANG_DROPDOWN                         = ::WID_GO_LANG_DROPDOWN,                         ///< Language dropdown.
		WID_GO_RESOLUTION_DROPDOWN                   = ::WID_GO_RESOLUTION_DROPDOWN,                   ///< Dropdown for the resolution.
		WID_GO_FULLSCREEN_BUTTON                     = ::WID_GO_FULLSCREEN_BUTTON,                     ///< Toggle fullscreen.
		WID_GO_GUI_SCALE                             = ::WID_GO_GUI_SCALE,                             ///< GUI Scale slider.
		WID_GO_GUI_SCALE_AUTO                        = ::WID_GO_GUI_SCALE_AUTO,                        ///< Autodetect GUI scale button.
		WID_GO_GUI_SCALE_BEVEL_BUTTON                = ::WID_GO_GUI_SCALE_BEVEL_BUTTON,                ///< Toggle for chunky bevels.
		WID_GO_BASE_GRF_DROPDOWN                     = ::WID_GO_BASE_GRF_DROPDOWN,                     ///< Use to select a base GRF.
		WID_GO_BASE_GRF_STATUS                       = ::WID_GO_BASE_GRF_STATUS,                       ///< Info about missing files etc.
		WID_GO_BASE_GRF_TEXTFILE                     = ::WID_GO_BASE_GRF_TEXTFILE,                     ///< Open base GRF readme, changelog (+1) or license (+2).
		WID_GO_BASE_GRF_DESCRIPTION                  = ::WID_GO_BASE_GRF_DESCRIPTION,                  ///< Description of selected base GRF.
		WID_GO_BASE_SFX_DROPDOWN                     = ::WID_GO_BASE_SFX_DROPDOWN,                     ///< Use to select a base SFX.
		WID_GO_BASE_SFX_VOLUME                       = ::WID_GO_BASE_SFX_VOLUME,                       ///< Change sound effects volume.
		WID_GO_BASE_SFX_TEXTFILE                     = ::WID_GO_BASE_SFX_TEXTFILE,                     ///< Open base SFX readme, changelog (+1) or license (+2).
		WID_GO_BASE_SFX_DESCRIPTION                  = ::WID_GO_BASE_SFX_DESCRIPTION,                  ///< Description of selected base SFX.
		WID_GO_BASE_MUSIC_DROPDOWN                   = ::WID_GO_BASE_MUSIC_DROPDOWN,                   ///< Use to select a base music set.
		WID_GO_BASE_MUSIC_VOLUME                     = ::WID_GO_BASE_MUSIC_VOLUME,                     ///< Change music volume.
		WID_GO_BASE_MUSIC_JUKEBOX                    = ::WID_GO_BASE_MUSIC_JUKEBOX,                    ///< Open the jukebox.
		WID_GO_BASE_MUSIC_STATUS                     = ::WID_GO_BASE_MUSIC_STATUS,                     ///< Info about corrupted files etc.
		WID_GO_BASE_MUSIC_TEXTFILE                   = ::WID_GO_BASE_MUSIC_TEXTFILE,                   ///< Open base music readme, changelog (+1) or license (+2).
		WID_GO_BASE_MUSIC_DESCRIPTION                = ::WID_GO_BASE_MUSIC_DESCRIPTION,                ///< Description of selected base music set.
		WID_GO_VIDEO_ACCEL_BUTTON                    = ::WID_GO_VIDEO_ACCEL_BUTTON,                    ///< Toggle for video acceleration.
		WID_GO_VIDEO_VSYNC_BUTTON                    = ::WID_GO_VIDEO_VSYNC_BUTTON,                    ///< Toggle for video vsync.
		WID_GO_REFRESH_RATE_DROPDOWN                 = ::WID_GO_REFRESH_RATE_DROPDOWN,                 ///< Dropdown for all available refresh rates.
		WID_GO_VIDEO_DRIVER_INFO                     = ::WID_GO_VIDEO_DRIVER_INFO,                     ///< Label showing details about the current video driver.
	};

	/** Widgets of the #GameSettingsWindow class. */
	enum GameSettingsWidgets {
		WID_GS_FILTER                                = ::WID_GS_FILTER,                                ///< Text filter.
		WID_GS_OPTIONSPANEL                          = ::WID_GS_OPTIONSPANEL,                          ///< Panel widget containing the option lists.
		WID_GS_SCROLLBAR                             = ::WID_GS_SCROLLBAR,                             ///< Scrollbar.
		WID_GS_HELP_TEXT                             = ::WID_GS_HELP_TEXT,                             ///< Information area to display help text of the selected option.
		WID_GS_EXPAND_ALL                            = ::WID_GS_EXPAND_ALL,                            ///< Expand all button.
		WID_GS_COLLAPSE_ALL                          = ::WID_GS_COLLAPSE_ALL,                          ///< Collapse all button.
		WID_GS_RESET_ALL                             = ::WID_GS_RESET_ALL,                             ///< Reset all button.
		WID_GS_RESTRICT_CATEGORY                     = ::WID_GS_RESTRICT_CATEGORY,                     ///< Label upfront to the category drop-down box to restrict the list of settings to show
		WID_GS_RESTRICT_TYPE                         = ::WID_GS_RESTRICT_TYPE,                         ///< Label upfront to the type drop-down box to restrict the list of settings to show
		WID_GS_RESTRICT_DROPDOWN                     = ::WID_GS_RESTRICT_DROPDOWN,                     ///< The drop down box to restrict the list of settings
		WID_GS_TYPE_DROPDOWN                         = ::WID_GS_TYPE_DROPDOWN,                         ///< The drop down box to choose client/game/company/all settings
	};

	/** Widgets of the #CustomCurrencyWindow class. */
	enum CustomCurrencyWidgets {
		WID_CC_RATE_DOWN                             = ::WID_CC_RATE_DOWN,                             ///< Down button.
		WID_CC_RATE_UP                               = ::WID_CC_RATE_UP,                               ///< Up button.
		WID_CC_RATE                                  = ::WID_CC_RATE,                                  ///< Rate of currency.
		WID_CC_SEPARATOR_EDIT                        = ::WID_CC_SEPARATOR_EDIT,                        ///< Separator edit button.
		WID_CC_SEPARATOR                             = ::WID_CC_SEPARATOR,                             ///< Current separator.
		WID_CC_PREFIX_EDIT                           = ::WID_CC_PREFIX_EDIT,                           ///< Prefix edit button.
		WID_CC_PREFIX                                = ::WID_CC_PREFIX,                                ///< Current prefix.
		WID_CC_SUFFIX_EDIT                           = ::WID_CC_SUFFIX_EDIT,                           ///< Suffix edit button.
		WID_CC_SUFFIX                                = ::WID_CC_SUFFIX,                                ///< Current suffix.
		WID_CC_YEAR_DOWN                             = ::WID_CC_YEAR_DOWN,                             ///< Down button.
		WID_CC_YEAR_UP                               = ::WID_CC_YEAR_UP,                               ///< Up button.
		WID_CC_YEAR                                  = ::WID_CC_YEAR,                                  ///< Year of introduction.
		WID_CC_PREVIEW                               = ::WID_CC_PREVIEW,                               ///< Preview.
	};

	/* automatically generated from ../../widgets/sign_widget.h */
	/** Widgets of the #SignListWindow class. */
	enum SignListWidgets {
		/* Name starts with SI instead of S, because of collision with SaveLoadWidgets */
		WID_SIL_CAPTION                              = ::WID_SIL_CAPTION,                              ///< Caption of the window.
		WID_SIL_LIST                                 = ::WID_SIL_LIST,                                 ///< List of signs.
		WID_SIL_SCROLLBAR                            = ::WID_SIL_SCROLLBAR,                            ///< Scrollbar of list.
		WID_SIL_FILTER_TEXT                          = ::WID_SIL_FILTER_TEXT,                          ///< Text box for typing a filter string.
		WID_SIL_FILTER_MATCH_CASE_BTN                = ::WID_SIL_FILTER_MATCH_CASE_BTN,                ///< Button to toggle if case sensitive filtering should be used.
		WID_SIL_FILTER_ENTER_BTN                     = ::WID_SIL_FILTER_ENTER_BTN,                     ///< Scroll to first sign.
	};

	/** Widgets of the #SignWindow class. */
	enum QueryEditSignWidgets {
		WID_QES_CAPTION                              = ::WID_QES_CAPTION,                              ///< Caption of the window.
		WID_QES_LOCATION                             = ::WID_QES_LOCATION,                             ///< Scroll to sign location.
		WID_QES_TEXT                                 = ::WID_QES_TEXT,                                 ///< Text of the query.
		WID_QES_OK                                   = ::WID_QES_OK,                                   ///< OK button.
		WID_QES_CANCEL                               = ::WID_QES_CANCEL,                               ///< Cancel button.
		WID_QES_DELETE                               = ::WID_QES_DELETE,                               ///< Delete button.
		WID_QES_PREVIOUS                             = ::WID_QES_PREVIOUS,                             ///< Previous button.
		WID_QES_NEXT                                 = ::WID_QES_NEXT,                                 ///< Next button.
	};

	/* automatically generated from ../../widgets/smallmap_widget.h */
	/** Widgets of the #SmallMapWindow class. */
	enum SmallMapWidgets {
		WID_SM_CAPTION                               = ::WID_SM_CAPTION,                               ///< Caption of the window.
		WID_SM_MAP_BORDER                            = ::WID_SM_MAP_BORDER,                            ///< Border around the smallmap.
		WID_SM_MAP                                   = ::WID_SM_MAP,                                   ///< Panel containing the smallmap.
		WID_SM_LEGEND                                = ::WID_SM_LEGEND,                                ///< Bottom panel to display smallmap legends.
		WID_SM_BLANK                                 = ::WID_SM_BLANK,                                 ///< Empty button as placeholder.
		WID_SM_ZOOM_IN                               = ::WID_SM_ZOOM_IN,                               ///< Button to zoom in one step.
		WID_SM_ZOOM_OUT                              = ::WID_SM_ZOOM_OUT,                              ///< Button to zoom out one step.
		WID_SM_CONTOUR                               = ::WID_SM_CONTOUR,                               ///< Button to select the contour view (height map).
		WID_SM_VEHICLES                              = ::WID_SM_VEHICLES,                              ///< Button to select the vehicles view.
		WID_SM_INDUSTRIES                            = ::WID_SM_INDUSTRIES,                            ///< Button to select the industries view.
		WID_SM_LINKSTATS                             = ::WID_SM_LINKSTATS,                             ///< Button to select the link stats view.
		WID_SM_ROUTES                                = ::WID_SM_ROUTES,                                ///< Button to select the routes view.
		WID_SM_VEGETATION                            = ::WID_SM_VEGETATION,                            ///< Button to select the vegetation view.
		WID_SM_OWNERS                                = ::WID_SM_OWNERS,                                ///< Button to select the owners view.
		WID_SM_CENTERMAP                             = ::WID_SM_CENTERMAP,                             ///< Button to move smallmap center to main window center.
		WID_SM_TOGGLETOWNNAME                        = ::WID_SM_TOGGLETOWNNAME,                        ///< Toggle button to display town names.
		WID_SM_SELECT_BUTTONS                        = ::WID_SM_SELECT_BUTTONS,                        ///< Selection widget for the buttons present in some smallmap modes.
		WID_SM_ENABLE_ALL                            = ::WID_SM_ENABLE_ALL,                            ///< Button to enable display of all legend entries.
		WID_SM_DISABLE_ALL                           = ::WID_SM_DISABLE_ALL,                           ///< Button to disable display of all legend entries.
		WID_SM_SHOW_HEIGHT                           = ::WID_SM_SHOW_HEIGHT,                           ///< Show heightmap toggle button.
		WID_SM_SCREENSHOT                            = ::WID_SM_SCREENSHOT,                            ///< Button to take smallmap screenshots
	};

	/* automatically generated from ../../widgets/station_widget.h */
	/** Widgets of the #StationViewWindow class. */
	enum StationViewWidgets {
		WID_SV_CAPTION                               = ::WID_SV_CAPTION,                               ///< Caption of the window.
		WID_SV_GROUP                                 = ::WID_SV_GROUP,                                 ///< label for "group by"
		WID_SV_GROUP_BY                              = ::WID_SV_GROUP_BY,                              ///< 'Group by' button
		WID_SV_SORT_ORDER                            = ::WID_SV_SORT_ORDER,                            ///< 'Sort order' button
		WID_SV_SORT_BY                               = ::WID_SV_SORT_BY,                               ///< 'Sort by' button
		WID_SV_WAITING                               = ::WID_SV_WAITING,                               ///< List of waiting cargo.
		WID_SV_SCROLLBAR                             = ::WID_SV_SCROLLBAR,                             ///< Scrollbar.
		WID_SV_ACCEPT_RATING_LIST                    = ::WID_SV_ACCEPT_RATING_LIST,                    ///< List of accepted cargoes / rating of cargoes.
		WID_SV_LOCATION                              = ::WID_SV_LOCATION,                              ///< 'Location' button.
		WID_SV_ACCEPTS_RATINGS                       = ::WID_SV_ACCEPTS_RATINGS,                       ///< 'Accepts' / 'Ratings' button.
		WID_SV_RENAME                                = ::WID_SV_RENAME,                                ///< 'Rename' button.
		WID_SV_CLOSE_AIRPORT                         = ::WID_SV_CLOSE_AIRPORT,                         ///< 'Close airport' button.
		WID_SV_TRAINS                                = ::WID_SV_TRAINS,                                ///< List of scheduled trains button.
		WID_SV_ROADVEHS                              = ::WID_SV_ROADVEHS,                              ///< List of scheduled road vehs button.
		WID_SV_SHIPS                                 = ::WID_SV_SHIPS,                                 ///< List of scheduled ships button.
		WID_SV_PLANES                                = ::WID_SV_PLANES,                                ///< List of scheduled planes button.
		WID_SV_CATCHMENT                             = ::WID_SV_CATCHMENT,                             ///< Toggle catchment area highlight.
		WID_SV_DEPARTURES                            = ::WID_SV_DEPARTURES,                            ///< Departures button.
		WID_SV_HISTORY                               = ::WID_SV_HISTORY,                               ///< Cargo history button.
	};

	/** Widgets of the #CompanyStationsWindow class. */
	enum StationListWidgets {
		/* Name starts with ST instead of S, because of collision with SaveLoadWidgets */
		WID_STL_CAPTION                              = ::WID_STL_CAPTION,                              ///< Caption of the window.
		WID_STL_LIST                                 = ::WID_STL_LIST,                                 ///< The main panel, list of stations.
		WID_STL_SCROLLBAR                            = ::WID_STL_SCROLLBAR,                            ///< Scrollbar next to the main panel.

		/* Vehicletypes need to be in order of StationFacility due to bit magic */
		WID_STL_TRAIN                                = ::WID_STL_TRAIN,                                ///< 'TRAIN' button - list only facilities where is a railroad station.
		WID_STL_TRUCK                                = ::WID_STL_TRUCK,                                ///< 'TRUCK' button - list only facilities where is a truck stop.
		WID_STL_BUS                                  = ::WID_STL_BUS,                                  ///< 'BUS' button - list only facilities where is a bus stop.
		WID_STL_AIRPLANE                             = ::WID_STL_AIRPLANE,                             ///< 'AIRPLANE' button - list only facilities where is an airport.
		WID_STL_SHIP                                 = ::WID_STL_SHIP,                                 ///< 'SHIP' button - list only facilities where is a dock.
		WID_STL_FACILALL                             = ::WID_STL_FACILALL,                             ///< 'ALL' button - list all facilities.

		WID_STL_NOCARGOWAITING                       = ::WID_STL_NOCARGOWAITING,                       ///< 'NO' button - list stations where no cargo is waiting.
		WID_STL_CARGOALL                             = ::WID_STL_CARGOALL,                             ///< 'ALL' button - list all stations.

		WID_STL_SORTBY                               = ::WID_STL_SORTBY,                               ///< 'Sort by' button - reverse sort direction.
		WID_STL_SORTDROPBTN                          = ::WID_STL_SORTDROPBTN,                          ///< Dropdown button.

		WID_STL_CARGOSTART                           = ::WID_STL_CARGOSTART,                           ///< Widget numbers used for list of cargo types (not present in _company_stations_widgets).
	};

	/** Widgets of the #SelectStationWindow class. */
	enum JoinStationWidgets {
		WID_JS_CAPTION                               = ::WID_JS_CAPTION,                               // Caption of the window.
		WID_JS_PANEL                                 = ::WID_JS_PANEL,                                 // Main panel.
		WID_JS_SCROLLBAR                             = ::WID_JS_SCROLLBAR,                             // Scrollbar of the panel.
	};

	/* automatically generated from ../../widgets/statusbar_widget.h */
	/** Widgets of the #StatusBarWindow class. */
	enum StatusbarWidgets {
		WID_S_LEFT                                   = ::WID_S_LEFT,                                   ///< Left part of the statusbar; date is shown there.
		WID_S_MIDDLE                                 = ::WID_S_MIDDLE,                                 ///< Middle part; current news or company name or *** SAVING *** or *** PAUSED ***.
		WID_S_RIGHT                                  = ::WID_S_RIGHT,                                  ///< Right part; bank balance.
	};

	/* automatically generated from ../../widgets/story_widget.h */
	/** Widgets of the #GoalListWindow class. */
	enum StoryBookWidgets {
		WID_SB_CAPTION                               = ::WID_SB_CAPTION,                               ///< Caption of the window.
		WID_SB_SEL_PAGE                              = ::WID_SB_SEL_PAGE,                              ///< Page selector.
		WID_SB_PAGE_PANEL                            = ::WID_SB_PAGE_PANEL,                            ///< Page body.
		WID_SB_SCROLLBAR                             = ::WID_SB_SCROLLBAR,                             ///< Scrollbar of the goal list.
		WID_SB_PREV_PAGE                             = ::WID_SB_PREV_PAGE,                             ///< Prev button.
		WID_SB_NEXT_PAGE                             = ::WID_SB_NEXT_PAGE,                             ///< Next button.
	};

	/* automatically generated from ../../widgets/subsidy_widget.h */
	/** Widgets of the #SubsidyListWindow class. */
	enum SubsidyListWidgets {
		/* Name starts with SU instead of S, because of collision with SaveLoadWidgets. */
		WID_SUL_PANEL                                = ::WID_SUL_PANEL,                                ///< Main panel of window.
		WID_SUL_SCROLLBAR                            = ::WID_SUL_SCROLLBAR,                            ///< Scrollbar of panel.
	};

	/* automatically generated from ../../widgets/terraform_widget.h */
	/** Widgets of the #TerraformToolbarWindow class. */
	enum TerraformToolbarWidgets {
		WID_TT_SHOW_PLACE_OBJECT                     = ::WID_TT_SHOW_PLACE_OBJECT,                     ///< Should the place object button be shown?
		WID_TT_BUTTONS_START                         = ::WID_TT_BUTTONS_START,                         ///< Start of pushable buttons.
		WID_TT_LOWER_LAND                            = ::WID_TT_LOWER_LAND,                            ///< Lower land button.
		WID_TT_RAISE_LAND                            = ::WID_TT_RAISE_LAND,                            ///< Raise land button.
		WID_TT_LEVEL_LAND                            = ::WID_TT_LEVEL_LAND,                            ///< Level land button.
		WID_TT_DEMOLISH                              = ::WID_TT_DEMOLISH,                              ///< Demolish aka dynamite button.
		WID_TT_BUY_LAND                              = ::WID_TT_BUY_LAND,                              ///< Buy land button.
		WID_TT_PLANT_TREES                           = ::WID_TT_PLANT_TREES,                           ///< Plant trees button (note: opens separate window, no place-push-button).
		WID_TT_MEASUREMENT_TOOL                      = ::WID_TT_MEASUREMENT_TOOL,                      ///< Ruler tool button
		WID_TT_PLACE_SIGN                            = ::WID_TT_PLACE_SIGN,                            ///< Place sign button.
		WID_TT_PLACE_OBJECT                          = ::WID_TT_PLACE_OBJECT,                          ///< Place object button.
	};

	/** Widgets of the #ScenarioEditorLandscapeGenerationWindow class. */
	enum EditorTerraformToolbarWidgets {
		WID_ETT_SHOW_PLACE_DESERT                    = ::WID_ETT_SHOW_PLACE_DESERT,                    ///< Should the place desert button be shown?
		WID_ETT_SHOW_PUBLIC_ROADS                    = ::WID_ETT_SHOW_PUBLIC_ROADS,                    ///< Should the public roads button be shown?
		WID_ETT_START                                = ::WID_ETT_START,                                ///< Used for iterations.
		WID_ETT_DOTS                                 = ::WID_ETT_DOTS,                                 ///< Invisible widget for rendering the terraform size on.
		WID_ETT_BUTTONS_START                        = ::WID_ETT_BUTTONS_START,                        ///< Start of pushable buttons.
		WID_ETT_DEMOLISH                             = ::WID_ETT_DEMOLISH,                             ///< Demolish aka dynamite button.
		WID_ETT_LOWER_LAND                           = ::WID_ETT_LOWER_LAND,                           ///< Lower land button.
		WID_ETT_RAISE_LAND                           = ::WID_ETT_RAISE_LAND,                           ///< Raise land button.
		WID_ETT_LEVEL_LAND                           = ::WID_ETT_LEVEL_LAND,                           ///< Level land button.
		WID_ETT_PLACE_ROCKS                          = ::WID_ETT_PLACE_ROCKS,                          ///< Place rocks button.
		WID_ETT_PLACE_DESERT                         = ::WID_ETT_PLACE_DESERT,                         ///< Place desert button (in tropical climate).
		WID_ETT_PLACE_OBJECT                         = ::WID_ETT_PLACE_OBJECT,                         ///< Place transmitter button.
		WID_ETT_PLACE_HOUSE                          = ::WID_ETT_PLACE_HOUSE,                          ///< Place house button.
		WID_ETT_BUTTONS_END                          = ::WID_ETT_BUTTONS_END,                          ///< End of pushable buttons.
		WID_ETT_INCREASE_SIZE                        = ::WID_ETT_INCREASE_SIZE,                        ///< Upwards arrow button to increase terraforming size.
		WID_ETT_DECREASE_SIZE                        = ::WID_ETT_DECREASE_SIZE,                        ///< Downwards arrow button to decrease terraforming size.
		WID_ETT_NEW_SCENARIO                         = ::WID_ETT_NEW_SCENARIO,                         ///< Button for generating a new scenario.
		WID_ETT_RESET_LANDSCAPE                      = ::WID_ETT_RESET_LANDSCAPE,                      ///< Button for removing all company-owned property.
		WID_ETT_PUBLIC_ROADS                         = ::WID_ETT_PUBLIC_ROADS,                         ///< Button for creating public roads.
	};

	/* automatically generated from ../../widgets/timetable_widget.h */
	/** Widgets of the #TimetableWindow class. */
	enum VehicleTimetableWidgets {
		WID_VT_CAPTION                               = ::WID_VT_CAPTION,                               ///< Caption of the window.
		WID_VT_ORDER_VIEW                            = ::WID_VT_ORDER_VIEW,                            ///< Order view.
		WID_VT_TIMETABLE_PANEL                       = ::WID_VT_TIMETABLE_PANEL,                       ///< Timetable panel.
		WID_VT_ARRIVAL_DEPARTURE_PANEL               = ::WID_VT_ARRIVAL_DEPARTURE_PANEL,               ///< Panel with the expected/scheduled arrivals.
		WID_VT_SCROLLBAR                             = ::WID_VT_SCROLLBAR,                             ///< Scrollbar for the panel.
		WID_VT_SUMMARY_PANEL                         = ::WID_VT_SUMMARY_PANEL,                         ///< Summary panel.
		WID_VT_START_DATE                            = ::WID_VT_START_DATE,                            ///< Start date button.
		WID_VT_CHANGE_TIME                           = ::WID_VT_CHANGE_TIME,                           ///< Change time button.
		WID_VT_CLEAR_TIME                            = ::WID_VT_CLEAR_TIME,                            ///< Clear time button.
		WID_VT_RESET_LATENESS                        = ::WID_VT_RESET_LATENESS,                        ///< Reset lateness button.
		WID_VT_AUTOFILL                              = ::WID_VT_AUTOFILL,                              ///< Autofill button.
		WID_VT_AUTOMATE                              = ::WID_VT_AUTOMATE,                              ///< Automate button.
		WID_VT_AUTO_SEPARATION                       = ::WID_VT_AUTO_SEPARATION,                       ///< Auto separation button.
		WID_VT_EXPECTED                              = ::WID_VT_EXPECTED,                              ///< Toggle between expected and scheduled arrivals.
		WID_VT_SEL_SHARED                            = ::WID_VT_SEL_SHARED,                            ///< #NWID_SELECTION widget for WID_VT_SHARED_ORDER_LIST and WID_VT_ADD_VEH_GROUP
		WID_VT_SHARED_ORDER_LIST                     = ::WID_VT_SHARED_ORDER_LIST,                     ///< Show the shared order list.
		WID_VT_ADD_VEH_GROUP                         = ::WID_VT_ADD_VEH_GROUP,                         ///< Create new group from single vehicle
		WID_VT_ARRIVAL_DEPARTURE_SELECTION           = ::WID_VT_ARRIVAL_DEPARTURE_SELECTION,           ///< Disable/hide the arrival departure panel.
		WID_VT_AUTO_SELECTION                        = ::WID_VT_AUTO_SELECTION,                        ///< Disable/hide the automate button.
		WID_VT_EXPECTED_SELECTION                    = ::WID_VT_EXPECTED_SELECTION,                    ///< Disable/hide the expected selection button.
		WID_VT_CHANGE_SPEED                          = ::WID_VT_CHANGE_SPEED,                          ///< Change speed limit button.
		WID_VT_CLEAR_SPEED                           = ::WID_VT_CLEAR_SPEED,                           ///< Clear speed limit button.
		WID_VT_SCHEDULED_DISPATCH                    = ::WID_VT_SCHEDULED_DISPATCH,                    ///< Scheduled Dispatch button.
		WID_VT_LOCK_ORDER_TIME                       = ::WID_VT_LOCK_ORDER_TIME,                       ///< Lock order time button.
		WID_VT_EXTRA                                 = ::WID_VT_EXTRA,                                 ///< Extra drop down menu.
		WID_VT_ASSIGN_SCHEDULE                       = ::WID_VT_ASSIGN_SCHEDULE,                       ///< Assign scheduled dispatch schedule.
		WID_VT_START_DATE_SELECTION                  = ::WID_VT_START_DATE_SELECTION,                  ///< #NWID_SELECTION widget for WID_VT_START_DATE and WID_VT_ASSIGN_SCHEDULE.
	};

	/* automatically generated from ../../widgets/toolbar_widget.h */
	/** Widgets of the #MainToolbarWindow class. */
	enum ToolbarNormalWidgets {
		WID_TN_PAUSE                                 = ::WID_TN_PAUSE,                                 ///< Pause the game.
		WID_TN_FAST_FORWARD                          = ::WID_TN_FAST_FORWARD,                          ///< Fast forward the game.
		WID_TN_SETTINGS                              = ::WID_TN_SETTINGS,                              ///< Settings menu.
		WID_TN_SAVE                                  = ::WID_TN_SAVE,                                  ///< Save menu.
		WID_TN_SMALL_MAP                             = ::WID_TN_SMALL_MAP,                             ///< Small map menu.
		WID_TN_TOWNS                                 = ::WID_TN_TOWNS,                                 ///< Town menu.
		WID_TN_SUBSIDIES                             = ::WID_TN_SUBSIDIES,                             ///< Subsidy menu.
		WID_TN_STATIONS                              = ::WID_TN_STATIONS,                              ///< Station menu.
		WID_TN_FINANCES                              = ::WID_TN_FINANCES,                              ///< Finance menu.
		WID_TN_COMPANIES                             = ::WID_TN_COMPANIES,                             ///< Company menu.
		WID_TN_STORY                                 = ::WID_TN_STORY,                                 ///< Story menu.
		WID_TN_GOAL                                  = ::WID_TN_GOAL,                                  ///< Goal menu.
		WID_TN_GRAPHS                                = ::WID_TN_GRAPHS,                                ///< Graph menu.
		WID_TN_LEAGUE                                = ::WID_TN_LEAGUE,                                ///< Company league menu.
		WID_TN_INDUSTRIES                            = ::WID_TN_INDUSTRIES,                            ///< Industry menu.
		WID_TN_VEHICLE_START                         = ::WID_TN_VEHICLE_START,                         ///< Helper for the offset of the vehicle menus.
		WID_TN_TRAINS                                = ::WID_TN_TRAINS,                                ///< Train menu.
		WID_TN_ROADVEHS                              = ::WID_TN_ROADVEHS,                              ///< Road vehicle menu.
		WID_TN_SHIPS                                 = ::WID_TN_SHIPS,                                 ///< Ship menu.
		WID_TN_AIRCRAFT                              = ::WID_TN_AIRCRAFT,                              ///< Aircraft menu.
		WID_TN_ZOOM_IN                               = ::WID_TN_ZOOM_IN,                               ///< Zoom in the main viewport.
		WID_TN_ZOOM_OUT                              = ::WID_TN_ZOOM_OUT,                              ///< Zoom out the main viewport.
		WID_TN_BUILDING_TOOLS_START                  = ::WID_TN_BUILDING_TOOLS_START,                  ///< Helper for the offset of the building tools
		WID_TN_RAILS                                 = ::WID_TN_RAILS,                                 ///< Rail building menu.
		WID_TN_ROADS                                 = ::WID_TN_ROADS,                                 ///< Road building menu.
		WID_TN_TRAMS                                 = ::WID_TN_TRAMS,                                 ///< Tram building menu.
		WID_TN_WATER                                 = ::WID_TN_WATER,                                 ///< Water building toolbar.
		WID_TN_AIR                                   = ::WID_TN_AIR,                                   ///< Airport building toolbar.
		WID_TN_LANDSCAPE                             = ::WID_TN_LANDSCAPE,                             ///< Landscaping toolbar.
		WID_TN_MUSIC_SOUND                           = ::WID_TN_MUSIC_SOUND,                           ///< Music/sound configuration menu.
		WID_TN_MESSAGES                              = ::WID_TN_MESSAGES,                              ///< Messages menu.
		WID_TN_HELP                                  = ::WID_TN_HELP,                                  ///< Help menu.
		WID_TN_SWITCH_BAR                            = ::WID_TN_SWITCH_BAR,                            ///< Only available when toolbar has been split to switch between different subsets.
		WID_TN_END                                   = ::WID_TN_END,                                   ///< Helper for knowing the amount of widgets.
	};

	/** Widgets of the #ScenarioEditorToolbarWindow class. */
	enum ToolbarEditorWidgets {
		WID_TE_PAUSE                                 = ::WID_TE_PAUSE,                                 ///< Pause the game.
		WID_TE_FAST_FORWARD                          = ::WID_TE_FAST_FORWARD,                          ///< Fast forward the game.
		WID_TE_SETTINGS                              = ::WID_TE_SETTINGS,                              ///< Settings menu.
		WID_TE_SAVE                                  = ::WID_TE_SAVE,                                  ///< Save menu.
		WID_TE_SPACER                                = ::WID_TE_SPACER,                                ///< Spacer with "scenario editor" text.
		WID_TE_DATE                                  = ::WID_TE_DATE,                                  ///< The date of the scenario.
		WID_TE_DATE_BACKWARD                         = ::WID_TE_DATE_BACKWARD,                         ///< Reduce the date of the scenario.
		WID_TE_DATE_FORWARD                          = ::WID_TE_DATE_FORWARD,                          ///< Increase the date of the scenario.
		WID_TE_SMALL_MAP                             = ::WID_TE_SMALL_MAP,                             ///< Small map menu.
		WID_TE_ZOOM_IN                               = ::WID_TE_ZOOM_IN,                               ///< Zoom in the main viewport.
		WID_TE_ZOOM_OUT                              = ::WID_TE_ZOOM_OUT,                              ///< Zoom out the main viewport.
		WID_TE_LAND_GENERATE                         = ::WID_TE_LAND_GENERATE,                         ///< Land generation.
		WID_TE_TOWN_GENERATE                         = ::WID_TE_TOWN_GENERATE,                         ///< Town building window.
		WID_TE_INDUSTRY                              = ::WID_TE_INDUSTRY,                              ///< Industry building window.
		WID_TE_ROADS                                 = ::WID_TE_ROADS,                                 ///< Road building menu.
		WID_TE_TRAMS                                 = ::WID_TE_TRAMS,                                 ///< Tram building menu.
		WID_TE_WATER                                 = ::WID_TE_WATER,                                 ///< Water building toolbar.
		WID_TE_TREES                                 = ::WID_TE_TREES,                                 ///< Tree building toolbar.
		WID_TE_SIGNS                                 = ::WID_TE_SIGNS,                                 ///< Sign building.
		WID_TE_DATE_PANEL                            = ::WID_TE_DATE_PANEL,                            ///< Container for the date widgets.
		WID_TE_MUSIC_SOUND                           = ::WID_TE_MUSIC_SOUND,                           ///< Music/sound configuration menu.
		WID_TE_HELP                                  = ::WID_TE_HELP,                                  ///< Help menu.
		WID_TE_SWITCH_BAR                            = ::WID_TE_SWITCH_BAR,                            ///< Only available when toolbar has been split to switch between different subsets.
	};

	/* automatically generated from ../../widgets/town_widget.h */
	/** Widgets of the #TownDirectoryWindow class. */
	enum TownDirectoryWidgets {
		WID_TD_SORT_ORDER                            = ::WID_TD_SORT_ORDER,                            ///< Direction of sort dropdown.
		WID_TD_SORT_CRITERIA                         = ::WID_TD_SORT_CRITERIA,                         ///< Criteria of sort dropdown.
		WID_TD_FILTER                                = ::WID_TD_FILTER,                                ///< Filter of name.
		WID_TD_LIST                                  = ::WID_TD_LIST,                                  ///< List of towns.
		WID_TD_SCROLLBAR                             = ::WID_TD_SCROLLBAR,                             ///< Scrollbar for the town list.
		WID_TD_WORLD_POPULATION                      = ::WID_TD_WORLD_POPULATION,                      ///< The world's population.
	};

	/** Widgets of the #TownAuthorityWindow class. */
	enum TownAuthorityWidgets {
		WID_TA_CAPTION                               = ::WID_TA_CAPTION,                               ///< Caption of window.
		WID_TA_ZONE_BUTTON                           = ::WID_TA_ZONE_BUTTON,                           ///< Turn on/off showing local authority zone.
		WID_TA_RATING_INFO                           = ::WID_TA_RATING_INFO,                           ///< Overview with ratings for each company.
		WID_TA_COMMAND_LIST                          = ::WID_TA_COMMAND_LIST,                          ///< List of commands for the player.
		WID_TA_SCROLLBAR                             = ::WID_TA_SCROLLBAR,                             ///< Scrollbar of the list of commands.
		WID_TA_ACTION_INFO                           = ::WID_TA_ACTION_INFO,                           ///< Additional information about the action.
		WID_TA_EXECUTE                               = ::WID_TA_EXECUTE,                               ///< Do-it button.
		WID_TA_SETTING                               = ::WID_TA_SETTING,                               ///< Setting drop-down.
		WID_TA_BTN_SEL                               = ::WID_TA_BTN_SEL,                               ///< Button selector.
	};

	/** Widgets of the #TownViewWindow class. */
	enum TownViewWidgets {
		WID_TV_CAPTION                               = ::WID_TV_CAPTION,                               ///< Caption of window.
		WID_TV_VIEWPORT                              = ::WID_TV_VIEWPORT,                              ///< View of the center of the town.
		WID_TV_INFO                                  = ::WID_TV_INFO,                                  ///< General information about the town.
		WID_TV_CENTER_VIEW                           = ::WID_TV_CENTER_VIEW,                           ///< Center the main view on this town.
		WID_TV_SHOW_AUTHORITY                        = ::WID_TV_SHOW_AUTHORITY,                        ///< Show the town authority window.
		WID_TV_CHANGE_NAME                           = ::WID_TV_CHANGE_NAME,                           ///< Change the name of this town.
		WID_TV_CATCHMENT                             = ::WID_TV_CATCHMENT,                             ///< Toggle catchment area highlight.
		WID_TV_EXPAND                                = ::WID_TV_EXPAND,                                ///< Expand this town (scenario editor only).
		WID_TV_DELETE                                = ::WID_TV_DELETE,                                ///< Delete this town (scenario editor only).
	};

	/** Widgets of the #FoundTownWindow class. */
	enum TownFoundingWidgets {
		WID_TF_NEW_TOWN                              = ::WID_TF_NEW_TOWN,                              ///< Create a new town.
		WID_TF_RANDOM_TOWN                           = ::WID_TF_RANDOM_TOWN,                           ///< Randomly place a town.
		WID_TF_MANY_RANDOM_TOWNS                     = ::WID_TF_MANY_RANDOM_TOWNS,                     ///< Randomly place many towns.
		WID_TF_EXPAND_ALL_TOWNS                      = ::WID_TF_EXPAND_ALL_TOWNS,                      ///< Make all towns grow slightly.
		WID_TF_TOWN_NAME_EDITBOX                     = ::WID_TF_TOWN_NAME_EDITBOX,                     ///< Editor for the town name.
		WID_TF_TOWN_NAME_RANDOM                      = ::WID_TF_TOWN_NAME_RANDOM,                      ///< Generate a random town name.
		WID_TF_SIZE_SMALL                            = ::WID_TF_SIZE_SMALL,                            ///< Selection for a small town.
		WID_TF_SIZE_MEDIUM                           = ::WID_TF_SIZE_MEDIUM,                           ///< Selection for a medium town.
		WID_TF_SIZE_LARGE                            = ::WID_TF_SIZE_LARGE,                            ///< Selection for a large town.
		WID_TF_SIZE_RANDOM                           = ::WID_TF_SIZE_RANDOM,                           ///< Selection for a randomly sized town.
		WID_TF_CITY                                  = ::WID_TF_CITY,                                  ///< Selection for the town's city state.
		WID_TF_LAYOUT_ORIGINAL                       = ::WID_TF_LAYOUT_ORIGINAL,                       ///< Selection for the original town layout.
		WID_TF_LAYOUT_BETTER                         = ::WID_TF_LAYOUT_BETTER,                         ///< Selection for the better town layout.
		WID_TF_LAYOUT_GRID2                          = ::WID_TF_LAYOUT_GRID2,                          ///< Selection for the 2x2 grid town layout.
		WID_TF_LAYOUT_GRID3                          = ::WID_TF_LAYOUT_GRID3,                          ///< Selection for the 3x3 grid town layout.
		WID_TF_LAYOUT_RANDOM                         = ::WID_TF_LAYOUT_RANDOM,                         ///< Selection for a randomly chosen town layout.
	};

	/** Widgets of the #HousePickerWindow class. */
	enum HousePickerWidgets {
		WID_HP_CAPTION                               = ::WID_HP_CAPTION,
		WID_HP_MAIN_PANEL_SEL                        = ::WID_HP_MAIN_PANEL_SEL,                        ///< Selection widget to show/hide the main panel.
		WID_HP_HOUSE_SETS_SEL                        = ::WID_HP_HOUSE_SETS_SEL,                        ///< Selection widget to show/hide the list of house sets.
		WID_HP_HOUSE_SETS                            = ::WID_HP_HOUSE_SETS,                            ///< List of available house sets.
		WID_HP_HOUSE_SELECT_MATRIX                   = ::WID_HP_HOUSE_SELECT_MATRIX,                   ///< Matrix with houses to select.
		WID_HP_HOUSE_SELECT_SCROLL                   = ::WID_HP_HOUSE_SELECT_SCROLL,                   ///< Scrollbar associated with the house matrix.
		WID_HP_HOUSE_SELECT                          = ::WID_HP_HOUSE_SELECT,                          ///< Panels with house images in the house matrix.
		WID_HP_HOUSE_PREVIEW                         = ::WID_HP_HOUSE_PREVIEW,                         ///< House preview panel.
		WID_HP_HOUSE_NAME                            = ::WID_HP_HOUSE_NAME,                            ///< House name display.
		WID_HP_HISTORICAL_BUILDING                   = ::WID_HP_HISTORICAL_BUILDING,                   ///< "Historical building" label.
		WID_HP_HOUSE_POPULATION                      = ::WID_HP_HOUSE_POPULATION,                      ///< House population display.
		WID_HP_HOUSE_ZONES                           = ::WID_HP_HOUSE_ZONES,                           ///< House zones display.
		WID_HP_HOUSE_LANDSCAPE                       = ::WID_HP_HOUSE_LANDSCAPE,                       ///< Information about house availability against the landscape.
		WID_HP_HOUSE_LANDSCAPE_SEL                   = ::WID_HP_HOUSE_LANDSCAPE_SEL,                   ///< Selection widget to show/hide the landscape info.
		WID_HP_HOUSE_YEARS                           = ::WID_HP_HOUSE_YEARS,                           ///< Years display.
		WID_HP_HOUSE_ACCEPTANCE                      = ::WID_HP_HOUSE_ACCEPTANCE,                      ///< Cargo accepted.
		WID_HP_HOUSE_SUPPLY                          = ::WID_HP_HOUSE_SUPPLY,                          ///< Cargo supplied.
	};

	/** Widgets of the #SelectTownWindow class. */
	enum SelectTownWidgets {
		WID_ST_CAPTION                               = ::WID_ST_CAPTION,                               ///< Caption of the window.
		WID_ST_PANEL                                 = ::WID_ST_PANEL,                                 ///< Main panel.
		WID_ST_SCROLLBAR                             = ::WID_ST_SCROLLBAR,                             ///< Scrollbar of the panel.
	};

	/* automatically generated from ../../widgets/transparency_widget.h */
	/** Widgets of the #TransparenciesWindow class. */
	enum TransparencyToolbarWidgets {
		/* Button row. */
		WID_TT_BEGIN                                 = ::WID_TT_BEGIN,                                 ///< First toggle button.
		WID_TT_SIGNS                                 = ::WID_TT_SIGNS,                                 ///< Signs background transparency toggle button.
		WID_TT_TREES                                 = ::WID_TT_TREES,                                 ///< Trees transparency toggle button.
		WID_TT_HOUSES                                = ::WID_TT_HOUSES,                                ///< Houses transparency toggle button.
		WID_TT_INDUSTRIES                            = ::WID_TT_INDUSTRIES,                            ///< industries transparency toggle button.
		WID_TT_BUILDINGS                             = ::WID_TT_BUILDINGS,                             ///< Company buildings and structures transparency toggle button.
		WID_TT_BRIDGES                               = ::WID_TT_BRIDGES,                               ///< Bridges transparency toggle button.
		WID_TT_STRUCTURES                            = ::WID_TT_STRUCTURES,                            ///< Object structure transparency toggle button.
		WID_TT_CATENARY                              = ::WID_TT_CATENARY,                              ///< Catenary transparency toggle button.
		WID_TT_LOADING                               = ::WID_TT_LOADING,                               ///< Loading indicators transparency toggle button.
		WIT_TT_TUNNELS                               = ::WIT_TT_TUNNELS,                               ///< Vehicles in tunnels toggle button.
		WID_TT_END                                   = ::WID_TT_END,                                   ///< End of toggle buttons.

		/* Panel with buttons for invisibility */
		WID_TT_BUTTONS                               = ::WID_TT_BUTTONS,                               ///< Panel with 'invisibility' buttons.
	};

	/* automatically generated from ../../widgets/tree_widget.h */
	/** Widgets of the #BuildTreesWindow class. */
	enum BuildTreesWidgets {
		WID_BT_TYPE_RANDOM                           = ::WID_BT_TYPE_RANDOM,                           ///< Button to build random type of tree.
		WID_BT_SE_PANE                               = ::WID_BT_SE_PANE,                               ///< Selection pane to show/hide scenario editor tools.
		WID_BT_MODE_NORMAL                           = ::WID_BT_MODE_NORMAL,                           ///< Select normal/rectangle planting mode.
		WID_BT_MODE_FOREST_SM                        = ::WID_BT_MODE_FOREST_SM,                        ///< Select small forest planting mode.
		WID_BT_MODE_FOREST_LG                        = ::WID_BT_MODE_FOREST_LG,                        ///< Select large forest planting mode.
		WID_BT_MANY_RANDOM                           = ::WID_BT_MANY_RANDOM,                           ///< Button to build many random trees.
		WID_BT_REMOVE_ALL                            = ::WID_BT_REMOVE_ALL,                            ///< Button to remove all trees.
		WID_BT_TYPE_BUTTON_FIRST                     = ::WID_BT_TYPE_BUTTON_FIRST,                     ///< First tree type selection button. (This must be last in the enum.)
	};

	/* automatically generated from ../../widgets/vehicle_widget.h */
	/** Widgets of the #VehicleViewWindow class. */
	enum VehicleViewWidgets {
		WID_VV_CAPTION                               = ::WID_VV_CAPTION,                               ///< Caption of window.
		WID_VV_VIEWPORT                              = ::WID_VV_VIEWPORT,                              ///< Viewport widget.
		WID_VV_START_STOP                            = ::WID_VV_START_STOP,                            ///< Start or stop this vehicle, and show information about the current state.
		WID_VV_RENAME                                = ::WID_VV_RENAME,                                ///< Rename vehicle
		WID_VV_LOCATION                              = ::WID_VV_LOCATION,                              ///< Center the main view on this vehicle.
		WID_VV_ORDER_LOCATION                        = ::WID_VV_ORDER_LOCATION,                        ///< Center the main view on the order's target location.
		WID_VV_GOTO_DEPOT                            = ::WID_VV_GOTO_DEPOT,                            ///< Order this vehicle to go to the depot.
		WID_VV_REFIT                                 = ::WID_VV_REFIT,                                 ///< Open the refit window.
		WID_VV_SHOW_ORDERS                           = ::WID_VV_SHOW_ORDERS,                           ///< Show the orders of this vehicle.
		WID_VV_SHOW_DETAILS                          = ::WID_VV_SHOW_DETAILS,                          ///< Show details of this vehicle.
		WID_VV_CLONE                                 = ::WID_VV_CLONE,                                 ///< Clone this vehicle.
		WID_VV_SELECT_DEPOT_CLONE                    = ::WID_VV_SELECT_DEPOT_CLONE,                    ///< Selection widget between 'goto depot', and 'clone vehicle' buttons.
		WID_VV_SELECT_REFIT_TURN                     = ::WID_VV_SELECT_REFIT_TURN,                     ///< Selection widget between 'refit' and 'turn around' buttons.
		WID_VV_TURN_AROUND                           = ::WID_VV_TURN_AROUND,                           ///< Turn this vehicle around.
		WID_VV_FORCE_PROCEED                         = ::WID_VV_FORCE_PROCEED,                         ///< Force this vehicle to pass a signal at danger.
		WID_VV_HONK_HORN                             = ::WID_VV_HONK_HORN,                             ///< Honk the vehicles horn (not drawn on UI, only used for hotkey).
	};

	/** Widgets of the #RefitWindow class. */
	enum VehicleRefitWidgets {
		WID_VR_CAPTION                               = ::WID_VR_CAPTION,                               ///< Caption of window.
		WID_VR_VEHICLE_PANEL_DISPLAY                 = ::WID_VR_VEHICLE_PANEL_DISPLAY,                 ///< Display with a representation of the vehicle to refit.
		WID_VR_SHOW_HSCROLLBAR                       = ::WID_VR_SHOW_HSCROLLBAR,                       ///< Selection widget for the horizontal scrollbar.
		WID_VR_HSCROLLBAR                            = ::WID_VR_HSCROLLBAR,                            ///< Horizontal scrollbar or the vehicle display.
		WID_VR_VEHICLE_DROPDOWN                      = ::WID_VR_VEHICLE_DROPDOWN,                      ///< Dropdown for the vehicle display.
		WID_VR_SELECT_HEADER                         = ::WID_VR_SELECT_HEADER,                         ///< Header with question about the cargo to carry.
		WID_VR_MATRIX                                = ::WID_VR_MATRIX,                                ///< Options to refit to.
		WID_VR_SCROLLBAR                             = ::WID_VR_SCROLLBAR,                             ///< Scrollbar for the refit options.
		WID_VR_INFO                                  = ::WID_VR_INFO,                                  ///< Information about the currently selected refit option.
		WID_VR_REFIT                                 = ::WID_VR_REFIT,                                 ///< Perform the refit.
	};

	/** Widgets of the #VehicleDetailsWindow class. */
	enum VehicleDetailsWidgets {
		WID_VD_CAPTION                               = ::WID_VD_CAPTION,                               ///< Caption of window.
		WID_VD_TRIP_HISTORY                          = ::WID_VD_TRIP_HISTORY,                          ///< Show the trip history of vehicle.
		WID_VD_TOP_DETAILS                           = ::WID_VD_TOP_DETAILS,                           ///< Panel with generic details.
		WID_VD_INCREASE_SERVICING_INTERVAL           = ::WID_VD_INCREASE_SERVICING_INTERVAL,           ///< Increase the servicing interval.
		WID_VD_DECREASE_SERVICING_INTERVAL           = ::WID_VD_DECREASE_SERVICING_INTERVAL,           ///< Decrease the servicing interval.
		WID_VD_SERVICE_INTERVAL_DROPDOWN             = ::WID_VD_SERVICE_INTERVAL_DROPDOWN,             ///< Dropdown to select default/days/percent service interval.
		WID_VD_SERVICING_INTERVAL                    = ::WID_VD_SERVICING_INTERVAL,                    ///< Information about the servicing interval.
		WID_VD_MIDDLE_DETAILS                        = ::WID_VD_MIDDLE_DETAILS,                        ///< Details for non-trains.
		WID_VD_MATRIX                                = ::WID_VD_MATRIX,                                ///< List of details for trains.
		WID_VD_SCROLLBAR                             = ::WID_VD_SCROLLBAR,                             ///< Scrollbar for train details.
		WID_VD_DETAILS_CARGO_CARRIED                 = ::WID_VD_DETAILS_CARGO_CARRIED,                 ///< Show carried cargo per part of the train.
		WID_VD_DETAILS_TRAIN_VEHICLES                = ::WID_VD_DETAILS_TRAIN_VEHICLES,                ///< Show all parts of the train with their description.
		WID_VD_DETAILS_CAPACITY_OF_EACH              = ::WID_VD_DETAILS_CAPACITY_OF_EACH,              ///< Show the capacity of all train parts.
		WID_VD_DETAILS_TOTAL_CARGO                   = ::WID_VD_DETAILS_TOTAL_CARGO,                   ///< Show the capacity and carried cargo amounts aggregated per cargo of the train.
	};

	/** Widgets of the #VehicleListWindow class. */
	enum VehicleListWidgets {
		WID_VL_LIST                                  = ::WID_VL_LIST,                                  ///< List of the vehicles, this must be first, see: DirtyVehicleListWindowForVehicle
		WID_VL_CAPTION                               = ::WID_VL_CAPTION,                               ///< Caption of window (for non shared orders windows).
		WID_VL_CAPTION_SHARED_ORDERS                 = ::WID_VL_CAPTION_SHARED_ORDERS,                 ///< Caption of window (for shared orders windows).
		WID_VL_CAPTION_SELECTION                     = ::WID_VL_CAPTION_SELECTION,                     ///< Selection for caption.
		WID_VL_ORDER_VIEW                            = ::WID_VL_ORDER_VIEW,                            ///< Button to open order window (for shared orders windows).
		WID_VL_GROUP_ORDER                           = ::WID_VL_GROUP_ORDER,                           ///< Group order.
		WID_VL_GROUP_BY_PULLDOWN                     = ::WID_VL_GROUP_BY_PULLDOWN,                     ///< Group by dropdown list.
		WID_VL_SORT_ORDER                            = ::WID_VL_SORT_ORDER,                            ///< Sort order.
		WID_VL_SORT_BY_PULLDOWN                      = ::WID_VL_SORT_BY_PULLDOWN,                      ///< Sort by dropdown list.
		WID_VL_FILTER_BY_CARGO                       = ::WID_VL_FILTER_BY_CARGO,                       ///< Cargo filter dropdown list
		WID_VL_FILTER_BY_CARGO_SEL                   = ::WID_VL_FILTER_BY_CARGO_SEL,                   ///< Cargo filter dropdown list panel selector
		WID_VL_SCROLLBAR                             = ::WID_VL_SCROLLBAR,                             ///< Scrollbar for the list.
		WID_VL_HIDE_BUTTONS                          = ::WID_VL_HIDE_BUTTONS,                          ///< Selection to hide the buttons.
		WID_VL_AVAILABLE_VEHICLES                    = ::WID_VL_AVAILABLE_VEHICLES,                    ///< Available vehicles.
		WID_VL_MANAGE_VEHICLES_DROPDOWN              = ::WID_VL_MANAGE_VEHICLES_DROPDOWN,              ///< Manage vehicles dropdown list.
		WID_VL_STOP_ALL                              = ::WID_VL_STOP_ALL,                              ///< Stop all button.
		WID_VL_START_ALL                             = ::WID_VL_START_ALL,                             ///< Start all button.
	};

	/* automatically generated from ../../widgets/viewport_widget.h */
	/** Widgets of the #ExtraViewportWindow class. */
	enum ExtraViewportWidgets {
		WID_EV_CAPTION                               = ::WID_EV_CAPTION,                               ///< Caption of window.
		WID_EV_VIEWPORT                              = ::WID_EV_VIEWPORT,                              ///< The viewport.
		WID_EV_ZOOM_IN                               = ::WID_EV_ZOOM_IN,                               ///< Zoom in.
		WID_EV_ZOOM_OUT                              = ::WID_EV_ZOOM_OUT,                              ///< Zoom out.
		WID_EV_MAIN_TO_VIEW                          = ::WID_EV_MAIN_TO_VIEW,                          ///< Center the view of this viewport on the main view.
		WID_EV_VIEW_TO_MAIN                          = ::WID_EV_VIEW_TO_MAIN,                          ///< Center the main view on the view of this viewport.
	};

	/* automatically generated from ../../widgets/waypoint_widget.h */
	/** Widgets of the #WaypointWindow class. */
	enum WaypointWidgets {
		WID_W_CAPTION                                = ::WID_W_CAPTION,                                ///< Caption of window.
		WID_W_VIEWPORT                               = ::WID_W_VIEWPORT,                               ///< The viewport on this waypoint.
		WID_W_CENTER_VIEW                            = ::WID_W_CENTER_VIEW,                            ///< Center the main view on this waypoint.
		WID_W_RENAME                                 = ::WID_W_RENAME,                                 ///< Rename this waypoint.
		WID_W_SHOW_VEHICLES                          = ::WID_W_SHOW_VEHICLES,                          ///< Show the vehicles visiting this waypoint.
		WID_W_DEPARTURES                             = ::WID_W_DEPARTURES,                             ///< Departures button.
		WID_W_TOGGLE_HIDDEN                          = ::WID_W_TOGGLE_HIDDEN,                          ///< Toggle label hidden.
		WID_W_TOGGLE_HIDDEN_SEL                      = ::WID_W_TOGGLE_HIDDEN_SEL,                      ///< Toggle label hidden selector.
	};

	// @endenum
};

#endif /* SCRIPT_WINDOW_HPP */
