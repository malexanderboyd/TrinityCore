//
// Created by Alex Boyd on 2019-03-14.
//

#ifndef TRINITYCORE_BATTLE_ROYAL_H
#define TRINITYCORE_BATTLE_ROYAL_H

#include "ScriptMgr.h"
#include "Player.h"
#include "OutdoorPvP.h"
#include <map>
using namespace std;

typedef std::function<void(Player*, int)> playerHandlerCallback;
typedef std::function<void(int)> gameMasterCallback;



class BattleRoyale : public OutdoorPvP {
public:
    BattleRoyale();

    playerHandlerCallback playerHandlerCB;
    struct RelicSpawnPoint {
        float x;
        float y;
        float z;
        float o;
    } spawnPointNighthaven, spawnPointShrine, spawnPointDens;


    bool SetupOutdoorPvP() override;
    void HandlePlayerEnterZone(Player* player, uint32 zone) override;
    void HandlePlayerLeaveZone(Player* player, uint32 zone) override;
    bool Update(uint32 diff) override;
    void HandleKill(Player* player, Unit* killed) override;

private:
    void startRoyale();
    void resetRoyale();
    bool checkShouldStart();
    void RemovePlayerFromRoyal(Player* player);
    bool IsPlayerInQueue(Player* player);
    bool IsPlayerCurrentlyPlaying(Player* player);
    void RemovePlayerFromQueue(Player* player);
    void RemovePlayerFromCurrentPlayers(Player* player);
    void TurnPlayersAggressive();
    static Creature* SpawnCreature(uint32 entry, Position const& pos);
    Creature* game_master;
    bool gameStarted;
    deque<Player*> queue;
    std::vector<Player*> currentPlayers;
    std::vector<RelicSpawnPoint> relicSpawnPoints;
    map<string, int> queuePlrPos;
    bool aggressivePlayers;
    int totalPlayers;
    int remainingPlayers;
    int playerLimit = 40;
    uint32 startTimer = 60000;
    uint32 relicSwitchTimer;
    uint32 totalGameTimer;
    uint32 infectTimer;
};

#endif //TRINITYCORE_BATTLE_ROYAL_H
