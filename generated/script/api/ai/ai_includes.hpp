/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/* THIS FILE IS AUTO-GENERATED; PLEASE DO NOT ALTER MANUALLY */

#include "ai_accounting.hpp.sq"
#include "ai_airport.hpp.sq"
#include "ai_base.hpp.sq"
#include "ai_basestation.hpp.sq"
#include "ai_bridge.hpp.sq"
#include "ai_bridgelist.hpp.sq"
#include "ai_cargo.hpp.sq"
#include "ai_cargolist.hpp.sq"
#include "ai_company.hpp.sq"
#include "ai_controller.hpp.sq"
#include "ai_date.hpp.sq"
#include "ai_depotlist.hpp.sq"
#include "ai_engine.hpp.sq"
#include "ai_enginelist.hpp.sq"
#include "ai_error.hpp.sq"
#include "ai_event.hpp.sq"
#include "ai_event_types.hpp.sq"
#include "ai_execmode.hpp.sq"
#include "ai_gamesettings.hpp.sq"
#include "ai_group.hpp.sq"
#include "ai_grouplist.hpp.sq"
#include "ai_industry.hpp.sq"
#include "ai_industrylist.hpp.sq"
#include "ai_industrytype.hpp.sq"
#include "ai_industrytypelist.hpp.sq"
#include "ai_infrastructure.hpp.sq"
#include "ai_list.hpp.sq"
#include "ai_log.hpp.sq"
#include "ai_map.hpp.sq"
#include "ai_marine.hpp.sq"
#include "ai_order.hpp.sq"
#include "ai_priorityqueue.hpp.sq"
#include "ai_rail.hpp.sq"
#include "ai_railtypelist.hpp.sq"
#include "ai_road.hpp.sq"
#include "ai_roadtypelist.hpp.sq"
#include "ai_sign.hpp.sq"
#include "ai_signlist.hpp.sq"
#include "ai_station.hpp.sq"
#include "ai_stationlist.hpp.sq"
#include "ai_subsidy.hpp.sq"
#include "ai_subsidylist.hpp.sq"
#include "ai_testmode.hpp.sq"
#include "ai_tile.hpp.sq"
#include "ai_tilelist.hpp.sq"
#include "ai_town.hpp.sq"
#include "ai_townlist.hpp.sq"
#include "ai_tunnel.hpp.sq"
#include "ai_vehicle.hpp.sq"
#include "ai_vehiclelist.hpp.sq"
#include "ai_waypoint.hpp.sq"
#include "ai_waypointlist.hpp.sq"

void SQAI_RegisterAll(Squirrel *engine)
{
	SQAIList_Register(engine);
	SQAIAccounting_Register(engine);
	SQAIAirport_Register(engine);
	SQAIBase_Register(engine);
	SQAIBaseStation_Register(engine);
	SQAIBridge_Register(engine);
	SQAIBridgeList_Register(engine);
	SQAIBridgeList_Length_Register(engine);
	SQAICargo_Register(engine);
	SQAICargoList_Register(engine);
	SQAICargoList_IndustryAccepting_Register(engine);
	SQAICargoList_IndustryProducing_Register(engine);
	SQAICargoList_StationAccepting_Register(engine);
	SQAICompany_Register(engine);
	SQAIDate_Register(engine);
	SQAIDepotList_Register(engine);
	SQAIEngine_Register(engine);
	SQAIEngineList_Register(engine);
	SQAIError_Register(engine);
	SQAIEvent_Register(engine);
	SQAIEventAircraftDestTooFar_Register(engine);
	SQAIEventCompanyAskMerger_Register(engine);
	SQAIEventCompanyBankrupt_Register(engine);
	SQAIEventCompanyInTrouble_Register(engine);
	SQAIEventCompanyMerger_Register(engine);
	SQAIEventCompanyNew_Register(engine);
	SQAIEventCompanyTown_Register(engine);
	SQAIEventController_Register(engine);
	SQAIEventDisasterZeppelinerCleared_Register(engine);
	SQAIEventDisasterZeppelinerCrashed_Register(engine);
	SQAIEventEngineAvailable_Register(engine);
	SQAIEventEnginePreview_Register(engine);
	SQAIEventExclusiveTransportRights_Register(engine);
	SQAIEventIndustryClose_Register(engine);
	SQAIEventIndustryOpen_Register(engine);
	SQAIEventRoadReconstruction_Register(engine);
	SQAIEventStationFirstVehicle_Register(engine);
	SQAIEventSubsidyAwarded_Register(engine);
	SQAIEventSubsidyExpired_Register(engine);
	SQAIEventSubsidyOffer_Register(engine);
	SQAIEventSubsidyOfferExpired_Register(engine);
	SQAIEventTownFounded_Register(engine);
	SQAIEventVehicleAutoReplaced_Register(engine);
	SQAIEventVehicleCrashed_Register(engine);
	SQAIEventVehicleLost_Register(engine);
	SQAIEventVehicleUnprofitable_Register(engine);
	SQAIEventVehicleWaitingInDepot_Register(engine);
	SQAIExecMode_Register(engine);
	SQAIGameSettings_Register(engine);
	SQAIGroup_Register(engine);
	SQAIGroupList_Register(engine);
	SQAIIndustry_Register(engine);
	SQAIIndustryList_Register(engine);
	SQAIIndustryList_CargoAccepting_Register(engine);
	SQAIIndustryList_CargoProducing_Register(engine);
	SQAIIndustryType_Register(engine);
	SQAIIndustryTypeList_Register(engine);
	SQAIInfrastructure_Register(engine);
	SQAILog_Register(engine);
	SQAIMap_Register(engine);
	SQAIMarine_Register(engine);
	SQAIOrder_Register(engine);
	SQAIPriorityQueue_Register(engine);
	SQAIRail_Register(engine);
	SQAIRailTypeList_Register(engine);
	SQAIRoad_Register(engine);
	SQAIRoadTypeList_Register(engine);
	SQAISign_Register(engine);
	SQAISignList_Register(engine);
	SQAIStation_Register(engine);
	SQAIStationList_Register(engine);
	SQAIStationList_Cargo_Register(engine);
	SQAIStationList_CargoPlanned_Register(engine);
	SQAIStationList_CargoPlannedByFrom_Register(engine);
	SQAIStationList_CargoPlannedByVia_Register(engine);
	SQAIStationList_CargoPlannedFromByVia_Register(engine);
	SQAIStationList_CargoPlannedViaByFrom_Register(engine);
	SQAIStationList_CargoWaiting_Register(engine);
	SQAIStationList_CargoWaitingByFrom_Register(engine);
	SQAIStationList_CargoWaitingByVia_Register(engine);
	SQAIStationList_CargoWaitingFromByVia_Register(engine);
	SQAIStationList_CargoWaitingViaByFrom_Register(engine);
	SQAIStationList_Vehicle_Register(engine);
	SQAISubsidy_Register(engine);
	SQAISubsidyList_Register(engine);
	SQAITestMode_Register(engine);
	SQAITile_Register(engine);
	SQAITileList_Register(engine);
	SQAITileList_IndustryAccepting_Register(engine);
	SQAITileList_IndustryProducing_Register(engine);
	SQAITileList_StationType_Register(engine);
	SQAITown_Register(engine);
	SQAITownEffectList_Register(engine);
	SQAITownList_Register(engine);
	SQAITunnel_Register(engine);
	SQAIVehicle_Register(engine);
	SQAIVehicleList_Register(engine);
	SQAIVehicleList_DefaultGroup_Register(engine);
	SQAIVehicleList_Depot_Register(engine);
	SQAIVehicleList_Group_Register(engine);
	SQAIVehicleList_SharedOrders_Register(engine);
	SQAIVehicleList_Station_Register(engine);
	SQAIWaypoint_Register(engine);
	SQAIWaypointList_Register(engine);
	SQAIWaypointList_Vehicle_Register(engine);
}
