//
// Created by Alex Boyd on 2019-03-10.
//

#include "BattleRoyal.h"
#include "ScriptMgr.h"

//void AddSC_magisters_terrace()
//{
//    new npc_kalecgos();
//}


class go_queue_portal : public GameObjectScript {
public:
    go_queue_portal() : GameObjectScript("go_queue_portal") {}

    struct go_queue_portalAI : public GameObjectAI {
        go_queue_portalAI(GameObject *go) : GameObjectAI(go) {}

        bool GossipHello(Player *player) override {


//            me->UseDoorOrButton();
//            if (player->GetQuestStatus(QUEST_HYPERCAPACITOR_GIZMO) == QUEST_STATUS_INCOMPLETE)
//            {
//                if (Creature* panther = me->FindNearestCreature(ENRAGED_PANTHER, 5, true))
//                {
//                    panther->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
//                    panther->SetReactState(REACT_AGGRESSIVE);
//                    panther->AI()->AttackStart(player);
//                }
//            }

            return true;
        }
    };

    GameObjectAI *GetAI(GameObject *go) const override {
        return new go_queue_portal(go);
    }
};


class PlayerHandler : public PlayerScript {
public:
    PlayerHandler() : PlayerScript("BRPlayerScript") {}

    void OnMapChanged(Player *player) {
        if (player->GetZoneId() == 493) {
            char msg[250];
            snprintf(msg, 250,
                     "|CFF7BBEF7[BR]|r:|cffff0000 %s |r has entered the royale (K: |CFFFF2502[%d]|r W: |CFFB900B5[%d]|r)",
                     player->GetName(), player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS), 0);
            sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        }
    }
};


void AddBattleRoyalScripts() {
    new PlayerHandler();
}