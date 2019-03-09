/*
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "BattlegroundBR.h"
#include "Log.h"
#include "Player.h"
#include "WorldPacket.h"
#include "WorldStatePackets.h"

BattlegroundBR::BattlegroundBR()
{
    BgObjects.resize(BG_BR_OBJECT_MAX);
}

void BattlegroundBR::StartingEventCloseDoors()
{
    for (uint32 i = BG_BR_OBJECT_DOOR_1; i <= BG_BR_OBJECT_DOOR_2; ++i)
        SpawnBGObject(i, RESPAWN_IMMEDIATELY);
}

void BattlegroundBR::StartingEventOpenDoors()
{
    for (uint32 i = BG_BR_OBJECT_DOOR_1; i <= BG_BR_OBJECT_DOOR_2; ++i)
        DoorOpen(i);

}

void BattlegroundBR::HandleAreaTrigger(Player* player, uint32 trigger)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    switch (trigger)
    {
        default:
            Battleground::HandleAreaTrigger(player, trigger);
            break;
    }
}

void BattlegroundBR::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(3002, 1); // BATTELGROUND_RUINS_OF_LORDAERNON_SHOW

    Arena::FillInitialWorldStates(packet);
}

bool BattlegroundBR::SetupBattleground()
{
    // gates
    if (!AddObject(BG_BR_OBJECT_DOOR_1, BG_BR_OBJECT_TYPE_DOOR_1, 1293.561f, 1601.938f, 31.60557f, -1.457349f, 0, 0, -0.6658813f, 0.7460576f, RESPAWN_IMMEDIATELY)
        || !AddObject(BG_BR_OBJECT_DOOR_2, BG_BR_OBJECT_TYPE_DOOR_2, 1278.648f, 1730.557f, 31.60557f, 1.684245f, 0, 0, 0.7460582f, 0.6658807f, RESPAWN_IMMEDIATELY))
    // TODO chests
//        || !AddObject(BG_BR_OBJECT_BUFF_1, BG_BR_OBJECT_TYPE_BUFF_1, 1328.719971f, 1632.719971f, 36.730400f, -1.448624f, 0, 0, 0.6626201f, -0.7489557f, 120)
//        || !AddObject(BG_BR_OBJECT_BUFF_2, BG_BR_OBJECT_TYPE_BUFF_2, 1243.300049f, 1699.170044f, 34.872601f, -0.06981307f, 0, 0, 0.03489945f, -0.9993908f, 120))
    {
        TC_LOG_ERROR("sql.sql", "BatteGroundBR: Failed to spawn some object!");
        return false;
    }

    return true;
}

void BattlegroundBR::CheckWinConditions()
{
    int allianceCount = GetAlivePlayersCountByTeam(ALLIANCE);
    int hordeCount = GetPlayersCountByTeam(HORDE);

    if(allianceCount + hordeCount == 1) {
        if(allianceCount == 1) {
           BattlegroundBR::EndBattleground(ALLIANCE);
        } else {
            BattlegroundBR::EndBattleground(HORDE);
        }
    }
}

void BattlegroundBR::EndBattleground(uint32 winner) {
    Battleground::EndBattleground(winner);
}