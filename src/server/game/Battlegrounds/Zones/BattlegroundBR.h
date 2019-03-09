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
#ifndef __BATTLEGROUNDBR_H
#define __BATTLEGROUNDBR_H

#include "Arena.h"

enum BattlegroundBRObjectTypes
{
    BG_BR_OBJECT_DOOR_1         = 0,
    BG_BR_OBJECT_DOOR_2         = 1,
    BG_BR_OBJECT_BUFF_1         = 2,
    BG_BR_OBJECT_BUFF_2         = 3,
    BG_BR_OBJECT_MAX            = 4
};

enum BattlegroundBRGameObjects
{
    BG_BR_OBJECT_TYPE_DOOR_1    = 185918,
    BG_BR_OBJECT_TYPE_DOOR_2    = 185917,
    BG_BR_OBJECT_TYPE_BUFF_1    = 184663,
    BG_BR_OBJECT_TYPE_BUFF_2    = 184664
};

class BattlegroundBR : public Arena
{
    public:
        BattlegroundBR();

        /* inherited from BattlegroundClass */
        void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;
        void StartingEventCloseDoors() override;
        void StartingEventOpenDoors() override;

        void HandleAreaTrigger(Player* Source, uint32 Trigger) override;
        void CheckWinConditions() override;
        bool SetupBattleground() override;
        void EndBattleground(uint32 winner) override;
};
#endif
