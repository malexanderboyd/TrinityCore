//
// Created by Alex Boyd on 2019-03-10.
//

#include "battle_royal.h"

#include <utility>
#include <ScriptPCH.h>
#include "GameObject.h"
#include "GameObjectAI.h"
#include "Player.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "MapManager.h"
#include "Creature.h"
#include "World.h"
#include "WorldSession.h"
#include "OutdoorPvP.h"
#include "stdlib.h"
#include "UnitDefines.h"


uint32 const ITEM_KILL_TOKEN = 133701; // Bloodshed Token
uint32 const ITEM_WINNER_TOKEN = 133702; // Kings Badge
uint32 const SPELL_RELIC_BUFF = 72144;
uint32 const SPELL_VISUAL_AURA = 37800;


class BattleRoyalRelic : public GameObjectScript {
public:
    BattleRoyalRelic() : GameObjectScript("battle_royale_relic") {}

    struct BattleRoyalRelicAI : public GameObjectAI {
        explicit BattleRoyalRelicAI(GameObject *go) : GameObjectAI(go) {}

        bool GossipHello(Player* player) override {
            if(!player->HasAura(SPELL_RELIC_BUFF)) {
                player->SetAuraStack(SPELL_RELIC_BUFF, player, 1);
                player->RemoveAura(SPELL_VISUAL_AURA);
            } else {
                player->SetAuraStack(SPELL_VISUAL_AURA, player, 1);
                player->RemoveAura(SPELL_RELIC_BUFF);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject *go) const override {
        return new BattleRoyalRelicAI(go);
    }

};

class OutdoorPvP_moonglade_battle_royal : public OutdoorPvPScript {
public:
    OutdoorPvP_moonglade_battle_royal() : OutdoorPvPScript("outdoorpvp_mbr") {}

    OutdoorPvP *GetOutdoorPvP() const override {
        return new BattleRoyale();
    }
};

//https://community.trinitycore.org/topic/14891-share-callback-between-two-custom-scripts-question/
BattleRoyale::BattleRoyale() {
    m_TypeId = OUTDOOR_PVP_BR;

    gameStarted = false;
    aggressivePlayers = false;
    totalPlayers = 0;
    remainingPlayers = 0;

    spawnPointNighthaven = {7830.34f, -2433.79f, 488.01f, 4.74f};
    spawnPointShrine = {7842.36f, -2225.37f, 468.40, 4.05f};
    spawnPointDens = {7563.89f, -2951.61f, 466.69f, 1.51f};
    relicSpawnPoints.push_back(spawnPointDens);
    relicSpawnPoints.push_back(spawnPointShrine);
    relicSpawnPoints.push_back(spawnPointDens);

}

void BattleRoyale::HandleKill(Player *player, Unit *killed) {

    if (killed->GetTypeId() == TYPEID_PLAYER) {
         player->AddItem(ITEM_KILL_TOKEN, 1);
         remainingPlayers -= 1;

         Player* victim = static_cast<Player*>(killed);
         RemovePlayerFromRoyal(victim);
        char msg[250];
        snprintf(msg, 250,
                 "%s killed %s! Better luck next time!",
                 player->GetName().c_str(), victim->GetName().c_str());
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
    }
}

bool BattleRoyale::SetupOutdoorPvP() {
    // Moonglade
    SetMapFromZone(493);
    RegisterZone(493);
    return true;
}

void BattleRoyale::HandlePlayerEnterZone(Player *player, uint32 zone) {
    OutdoorPvP::HandlePlayerEnterZone(player, zone);
    if (!gameStarted) {
        player->CastSpell(player, 33795, true);
        this->totalPlayers += 1;
        queue.push_back(player);
        queuePlrPos[player->GetName().c_str()] = totalPlayers;
        player->GetSession()->SendAreaTriggerMessage(
            "You've joined the queue for the battle royale. (Total in queue: %d)",
            totalPlayers);
    } else {
        player->GetSession()->SendAreaTriggerMessage(
            "The royale is already in progress. You'll have to wait for the next one. Players Remaining: (%i)",
            remainingPlayers);
        RemovePlayerFromRoyal(player);
    }
}

void BattleRoyale::HandlePlayerLeaveZone(Player *player, uint32 zone) {
    OutdoorPvP::HandlePlayerLeaveZone(player, zone);
    // teleporting in first time, game started teleporting out
    // game started, was in zone and left prematurely,
    // game not started, exiting queue - done

    player->pvpInfo.IsInFFAPvPArea = false;
    player->UpdatePvPState(false);
    player->RemoveAurasDueToSpell(33795);
    if (!gameStarted) {
        RemovePlayerFromRoyal(player);
    } else {
        if (!player->IsBeingTeleported() and IsPlayerInQueue(player)) {
            this->totalPlayers -= 1;
            this->remainingPlayers -= 1;
            RemovePlayerFromRoyal(player);
        } else {
            RemovePlayerFromRoyal(player);
        }
    }
}

void BattleRoyale::resetRoyale() {
    gameStarted = false;
    aggressivePlayers = false;
    startTimer = 60000;
    currentPlayers.clear();
    remainingPlayers = 0;
}

bool BattleRoyale::Update(uint32 diff) {
    if (!gameStarted && checkShouldStart()) {
        startRoyale();
    }

    if (startTimer <= diff && gameStarted && !aggressivePlayers) {
            this->game_master->Yell("The battle royal has begun!",
                                    LANG_UNIVERSAL);
            TurnPlayersAggressive();
            return true;
        }

    startTimer -= diff;

    if(gameStarted) {

        if(remainingPlayers == 1 && aggressivePlayers) {
            if (!currentPlayers.empty()) {
                Player* winner = currentPlayers.front();
                char msg[250];
                snprintf(msg, 250,
                         "%s has won the Battle Royale! What a legend!",
                         winner->GetName().c_str());
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
                resetRoyale();
                winner->AddItem(ITEM_WINNER_TOKEN, 1);
                RemovePlayerFromRoyal(winner);
            }
        }


        if (relicSwitchTimer <= diff) { // switch Relic to new location

        }

        if(totalGameTimer <= diff) { // Speeds up other timers, restricts games from stalling

        }

        if(infectTimer <= diff) { // Damage players without relic buffs

        }

    }



    return true;
}

bool BattleRoyale::checkShouldStart() {
    return !gameStarted && totalPlayers >= 2;
}

void BattleRoyale::TurnPlayersAggressive() {
    while(!queue.empty() && remainingPlayers <= 20) {
        Player* plr = queue.front();

        plr->pvpInfo.IsInFFAPvPArea = true;
        plr->UpdatePvPState(true);

        currentPlayers.push_back(plr);
        remainingPlayers += 1;
        queue.pop_front();
    }
    aggressivePlayers = true;
}

void BattleRoyale::startRoyale() {
    gameStarted = true;
    char msg[250];
    snprintf(msg, 250,
             "The Battle Royale is about to begin! (Players: [%i])",
             totalPlayers);
    sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
    this->game_master = SpawnCreature(133701,
                                      Position(7396.81, -2186.72, 527, 0.6));
    this->startTimer = 60000;
}

bool BattleRoyale::IsPlayerCurrentlyPlaying(Player* player) {
    for(uint32 i = 0; i < currentPlayers.size(); i++) {
        Player* plr = currentPlayers.at(i);
        if(player->GetName().c_str() == plr->GetName().c_str()) {
            return true;
        }
    }
    return false;
}

void BattleRoyale::RemovePlayerFromCurrentPlayers(Player* player) {
    if(!IsPlayerCurrentlyPlaying(player)) {
        return;
    }

    int target = -1;
    for(uint32 i = 0; i < currentPlayers.size(); i++) {
        Player* plr = currentPlayers.at(i);
        if(player->GetName().c_str() == plr->GetName().c_str()) {
            target = i;
            break;
        }
    }
    if(target != -1) {
        currentPlayers.erase(currentPlayers.begin()+target);
    }
}

void BattleRoyale::RemovePlayerFromRoyal(Player* player) {
    RemovePlayerFromQueue(player);
    RemovePlayerFromCurrentPlayers(player);
    player->ResurrectPlayer(50.0f);
    player->TeleportTo(player->m_homebindMapId, player->m_homebindX,
                       player->m_homebindY, player->m_homebindZ, 0.0f);
}

void BattleRoyale::RemovePlayerFromQueue(Player *player) {
    if(IsPlayerInQueue(player)) {
        queue.erase(queue.begin() + queuePlrPos[player->GetName().c_str()]);
        queuePlrPos.erase(queuePlrPos.find(player->GetName().c_str()));
    }
}

bool BattleRoyale::IsPlayerInQueue(Player *player) {
    return queuePlrPos.count(player->GetName().c_str()) > 0;
}

Creature *BattleRoyale::SpawnCreature(uint32 entry, Position const &pos) {
    //Get map object
    Map *map = sMapMgr->CreateBaseMap(1);
    if (!map) {
        return nullptr;
    }

    auto creature = new Creature();
    if (!creature->Create(map->GenerateLowGuid<HighGuid::Unit>(), map,
                          PHASEMASK_NORMAL, entry, pos)) {
        delete creature;
        return nullptr;
    }

    creature->SetHomePosition(pos);

    // Set creature in world
    map->AddToMap(creature);
    creature->setActive(true);
    creature->SetFarVisible(true);

    return creature;
}


void AddSC_battle_royal() {
    new OutdoorPvP_moonglade_battle_royal();
    new BattleRoyalRelic();
}
