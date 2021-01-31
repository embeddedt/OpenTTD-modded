/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/* THIS FILE IS AUTO-GENERATED; PLEASE DO NOT ALTER MANUALLY */

#include "game_accounting.hpp.sq"
#include "game_admin.hpp.sq"
#include "game_airport.hpp.sq"
#include "game_base.hpp.sq"
#include "game_basestation.hpp.sq"
#include "game_bridge.hpp.sq"
#include "game_bridgelist.hpp.sq"
#include "game_cargo.hpp.sq"
#include "game_cargolist.hpp.sq"
#include "game_cargomonitor.hpp.sq"
#include "game_client.hpp.sq"
#include "game_clientlist.hpp.sq"
#include "game_company.hpp.sq"
#include "game_companymode.hpp.sq"
#include "game_controller.hpp.sq"
#include "game_date.hpp.sq"
#include "game_depotlist.hpp.sq"
#include "game_engine.hpp.sq"
#include "game_enginelist.hpp.sq"
#include "game_error.hpp.sq"
#include "game_event.hpp.sq"
#include "game_event_types.hpp.sq"
#include "game_execmode.hpp.sq"
#include "game_game.hpp.sq"
#include "game_gamesettings.hpp.sq"
#include "game_goal.hpp.sq"
#include "game_industry.hpp.sq"
#include "game_industrylist.hpp.sq"
#include "game_industrytype.hpp.sq"
#include "game_industrytypelist.hpp.sq"
#include "game_infrastructure.hpp.sq"
#include "game_list.hpp.sq"
#include "game_log.hpp.sq"
#include "game_map.hpp.sq"
#include "game_marine.hpp.sq"
#include "game_news.hpp.sq"
#include "game_order.hpp.sq"
#include "game_priorityqueue.hpp.sq"
#include "game_rail.hpp.sq"
#include "game_railtypelist.hpp.sq"
#include "game_road.hpp.sq"
#include "game_roadtypelist.hpp.sq"
#include "game_sign.hpp.sq"
#include "game_signlist.hpp.sq"
#include "game_station.hpp.sq"
#include "game_stationlist.hpp.sq"
#include "game_story_page.hpp.sq"
#include "game_storypageelementlist.hpp.sq"
#include "game_storypagelist.hpp.sq"
#include "game_subsidy.hpp.sq"
#include "game_subsidylist.hpp.sq"
#include "game_testmode.hpp.sq"
#include "game_text.hpp.sq"
#include "game_tile.hpp.sq"
#include "game_tilelist.hpp.sq"
#include "game_town.hpp.sq"
#include "game_townlist.hpp.sq"
#include "game_tunnel.hpp.sq"
#include "game_vehicle.hpp.sq"
#include "game_vehiclelist.hpp.sq"
#include "game_viewport.hpp.sq"
#include "game_waypoint.hpp.sq"
#include "game_waypointlist.hpp.sq"
#include "game_window.hpp.sq"

void SQGS_RegisterAll(Squirrel *engine)
{
	SQGSList_Register(engine);
	SQGSAccounting_Register(engine);
	SQGSAdmin_Register(engine);
	SQGSAirport_Register(engine);
	SQGSBase_Register(engine);
	SQGSBaseStation_Register(engine);
	SQGSBridge_Register(engine);
	SQGSBridgeList_Register(engine);
	SQGSBridgeList_Length_Register(engine);
	SQGSCargo_Register(engine);
	SQGSCargoList_Register(engine);
	SQGSCargoList_IndustryAccepting_Register(engine);
	SQGSCargoList_IndustryProducing_Register(engine);
	SQGSCargoList_StationAccepting_Register(engine);
	SQGSCargoMonitor_Register(engine);
	SQGSClient_Register(engine);
	SQGSClientList_Register(engine);
	SQGSClientList_Company_Register(engine);
	SQGSCompany_Register(engine);
	SQGSCompanyMode_Register(engine);
	SQGSDate_Register(engine);
	SQGSDepotList_Register(engine);
	SQGSEngine_Register(engine);
	SQGSEngineList_Register(engine);
	SQGSError_Register(engine);
	SQGSEvent_Register(engine);
	SQGSEventAdminPort_Register(engine);
	SQGSEventCompanyBankrupt_Register(engine);
	SQGSEventCompanyInTrouble_Register(engine);
	SQGSEventCompanyMerger_Register(engine);
	SQGSEventCompanyNew_Register(engine);
	SQGSEventCompanyTown_Register(engine);
	SQGSEventController_Register(engine);
	SQGSEventExclusiveTransportRights_Register(engine);
	SQGSEventGoalQuestionAnswer_Register(engine);
	SQGSEventIndustryClose_Register(engine);
	SQGSEventIndustryOpen_Register(engine);
	SQGSEventRoadReconstruction_Register(engine);
	SQGSEventStationFirstVehicle_Register(engine);
	SQGSEventStoryPageButtonClick_Register(engine);
	SQGSEventStoryPageTileSelect_Register(engine);
	SQGSEventStoryPageVehicleSelect_Register(engine);
	SQGSEventSubsidyAwarded_Register(engine);
	SQGSEventSubsidyExpired_Register(engine);
	SQGSEventSubsidyOffer_Register(engine);
	SQGSEventSubsidyOfferExpired_Register(engine);
	SQGSEventTownFounded_Register(engine);
	SQGSEventVehicleCrashed_Register(engine);
	SQGSEventWindowWidgetClick_Register(engine);
	SQGSExecMode_Register(engine);
	SQGSGame_Register(engine);
	SQGSGameSettings_Register(engine);
	SQGSGoal_Register(engine);
	SQGSIndustry_Register(engine);
	SQGSIndustryList_Register(engine);
	SQGSIndustryList_CargoAccepting_Register(engine);
	SQGSIndustryList_CargoProducing_Register(engine);
	SQGSIndustryType_Register(engine);
	SQGSIndustryTypeList_Register(engine);
	SQGSInfrastructure_Register(engine);
	SQGSLog_Register(engine);
	SQGSMap_Register(engine);
	SQGSMarine_Register(engine);
	SQGSNews_Register(engine);
	SQGSOrder_Register(engine);
	SQGSPriorityQueue_Register(engine);
	SQGSRail_Register(engine);
	SQGSRailTypeList_Register(engine);
	SQGSRoad_Register(engine);
	SQGSRoadTypeList_Register(engine);
	SQGSSign_Register(engine);
	SQGSSignList_Register(engine);
	SQGSStation_Register(engine);
	SQGSStationList_Register(engine);
	SQGSStationList_Cargo_Register(engine);
	SQGSStationList_CargoPlanned_Register(engine);
	SQGSStationList_CargoPlannedByFrom_Register(engine);
	SQGSStationList_CargoPlannedByVia_Register(engine);
	SQGSStationList_CargoPlannedFromByVia_Register(engine);
	SQGSStationList_CargoPlannedViaByFrom_Register(engine);
	SQGSStationList_CargoWaiting_Register(engine);
	SQGSStationList_CargoWaitingByFrom_Register(engine);
	SQGSStationList_CargoWaitingByVia_Register(engine);
	SQGSStationList_CargoWaitingFromByVia_Register(engine);
	SQGSStationList_CargoWaitingViaByFrom_Register(engine);
	SQGSStationList_Vehicle_Register(engine);
	SQGSStoryPage_Register(engine);
	SQGSStoryPageElementList_Register(engine);
	SQGSStoryPageList_Register(engine);
	SQGSSubsidy_Register(engine);
	SQGSSubsidyList_Register(engine);
	SQGSTestMode_Register(engine);
	SQGSText_Register(engine);
	SQGSTile_Register(engine);
	SQGSTileList_Register(engine);
	SQGSTileList_IndustryAccepting_Register(engine);
	SQGSTileList_IndustryProducing_Register(engine);
	SQGSTileList_StationType_Register(engine);
	SQGSTown_Register(engine);
	SQGSTownEffectList_Register(engine);
	SQGSTownList_Register(engine);
	SQGSTunnel_Register(engine);
	SQGSVehicle_Register(engine);
	SQGSVehicleList_Register(engine);
	SQGSVehicleList_Depot_Register(engine);
	SQGSVehicleList_SharedOrders_Register(engine);
	SQGSVehicleList_Station_Register(engine);
	SQGSViewport_Register(engine);
	SQGSWaypoint_Register(engine);
	SQGSWaypointList_Register(engine);
	SQGSWaypointList_Vehicle_Register(engine);
	SQGSWindow_Register(engine);
}
