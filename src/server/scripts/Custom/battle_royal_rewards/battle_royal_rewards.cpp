//
// Created by Alex Boyd on 2019-08-15.
//

#include "battle_royal_rewards.h"
#include "ScriptMgr.h"
#include "Item.h"
#include <ScriptPCH.h>
#include "GameObject.h"
#include "GameObjectAI.h"
#include "Player.h"
#include "Chat.h"
#include "Spell.h"
#include "DBCStores.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include <algorithm>

#include "MapManager.h"
#include "Creature.h"
#include "World.h"
#include "WorldSession.h"
#include "OutdoorPvP.h"
#include "UnitDefines.h"

class item_battle_royal_reward_title_vanquisher : public ItemScript {
public:
    item_battle_royal_reward_title_vanquisher() : ItemScript(
        "item_battle_royal_reward_title_vanquisher") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            VANQUISHER))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_battlemaster : public ItemScript {
public:
    item_battle_royal_reward_title_battlemaster() : ItemScript(
        "item_battle_royal_reward_title_battlemaster") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            BATTLEMASTER)) {
            player->SetTitle(titleEntry);
        } else {
            player->SetTitle(titleEntry);
        }
    }
};

class item_battle_royal_reward_title_commander : public ItemScript {
public:
    item_battle_royal_reward_title_commander() : ItemScript(
        "item_battle_royal_reward_title_commander") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            COMMANDER))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_grunt : public ItemScript {
public:
    item_battle_royal_reward_title_grunt() : ItemScript(
        "item_battle_royal_reward_title_grunt") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            GRUNT))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_brutual_gladiator : public ItemScript {
public:
    item_battle_royal_reward_title_brutual_gladiator() : ItemScript(
        "item_battle_royal_reward_title_brutual_gladiator") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            BRUTAL_GLADIATOR))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_knight_champion : public ItemScript {
public:
    item_battle_royal_reward_title_knight_champion() : ItemScript(
        "item_battle_royal_reward_title_knight_champion") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            KNIGHT_CHAMPION))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_flame_keeper : public ItemScript {
public:
    item_battle_royal_reward_title_flame_keeper() : ItemScript(
        "item_battle_royal_reward_title_flame_keeper") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            FLAME_KEEPER))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_deadly_gladiator : public ItemScript {
public:
    item_battle_royal_reward_title_deadly_gladiator() : ItemScript(
        "item_battle_royal_reward_title_deadly_gladiator") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            DEADLY_GLADIATOR))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_merrymaker : public ItemScript {
public:
    item_battle_royal_reward_title_merrymaker() : ItemScript(
        "item_battle_royal_reward_title_merrymaker") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            MERRYMAKER))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_blood_guard : public ItemScript {
public:
    item_battle_royal_reward_title_blood_guard() : ItemScript(
        "item_battle_royal_reward_title_blood_guard") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            BLOOD_GUARD))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_bane_of_fallen_king : public ItemScript {
public:
    item_battle_royal_reward_title_bane_of_fallen_king() : ItemScript(
        "item_battle_royal_reward_title_bane_of_fallen_king") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            BANE_OF_FALLEN_KING))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_champion : public ItemScript {
public:
    item_battle_royal_reward_title_champion() : ItemScript(
        "item_battle_royal_reward_title_champion") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            CHAMPION))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_blood_sail : public ItemScript {
public:
    item_battle_royal_reward_title_blood_sail() : ItemScript(
        "item_battle_royal_reward_title_blood_sail") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            BLOODSAIL))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_crusader : public ItemScript {
public:
    item_battle_royal_reward_title_crusader() : ItemScript(
        "item_battle_royal_reward_title_crusader") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            CRUSADER))
            player->SetTitle(titleEntry);
    }
};

class item_battle_royal_reward_title_celestial_defender : public ItemScript {
public:
    item_battle_royal_reward_title_celestial_defender() : ItemScript(
        "item_battle_royal_reward_title_celestial_defender") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (CharTitlesEntry const *titleEntry = sCharTitlesStore.LookupEntry(
            CELESTIAL_DEFENDER))
            player->SetTitle(titleEntry);
    }
};


/* Mounts */

class item_battle_royal_reward_mount_magic_rooster : public ItemScript {
public:
    item_battle_royal_reward_mount_magic_rooster() : ItemScript(
        "item_battle_royal_reward_mount_magic_rooster") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (!player->HasSpell(MAGIC_ROOSTER))
            player->LearnSpell(MAGIC_ROOSTER, false);
    }
};

class item_battle_royal_reward_mount_brewfest_ram : public ItemScript {
public:
    item_battle_royal_reward_mount_brewfest_ram() : ItemScript(
        "item_battle_royal_reward_mount_brewfest_ram") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (!player->HasSpell(BREWFEST_RAM))
            player->LearnSpell(BREWFEST_RAM, false);
    }
};

class item_battle_royal_reward_mount_amani_warbear : public ItemScript {
public:
    item_battle_royal_reward_mount_amani_warbear() : ItemScript(
        "item_battle_royal_reward_mount_amani_warbear") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (!player->HasSpell(AMANI_WAR_BEAR))
            player->LearnSpell(AMANI_WAR_BEAR, false);
    }
};

class item_battle_royal_reward_mount_zulian_tiger : public ItemScript {
public:
    item_battle_royal_reward_mount_zulian_tiger() : ItemScript(
        "item_battle_royal_reward_mount_zulian_tiger") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (!player->HasSpell(ZULIAN_TIGER))
            player->LearnSpell(ZULIAN_TIGER, false);
    }
};

class item_battle_royal_reward_mount_fiery_warhorse : public ItemScript {
public:
    item_battle_royal_reward_mount_fiery_warhorse() : ItemScript(
        "item_battle_royal_reward_mount_fiery_warhorse") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {
        if (!player->HasSpell(FIERY_WARHORSE))
            player->LearnSpell(FIERY_WARHORSE, false);
    }
};

class item_battle_royal_reward_mount_war_stead : public ItemScript {
public:
    item_battle_royal_reward_mount_war_stead() : ItemScript(
        "item_battle_royal_reward_mount_war_stead") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        switch (player->GetTeam()) {
            case 0:
                if (!player->HasSpell(WAR_TIGER))
                    player->LearnSpell(WAR_TIGER, false);
                break;
            default:
                if (!player->HasSpell(WAR_WOLF))
                    player->LearnSpell(WAR_WOLF, false);
        }

    }
};

class item_battle_royal_reward_mount_dark_riding_talbuk : public ItemScript {
public:
    item_battle_royal_reward_mount_dark_riding_talbuk() : ItemScript(
        "item_battle_royal_reward_mount_dark_riding_talbuk") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(DARK_RIDING_TALBUK)) {
            player->LearnSpell(DARK_RIDING_TALBUK, false);
        }

    }
};

class item_battle_royal_reward_mount_spectral_tiger : public ItemScript {
public:
    item_battle_royal_reward_mount_spectral_tiger() : ItemScript(
        "item_battle_royal_reward_mount_spectral_tiger") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(SPECTRAL_TIGER)) {
            player->LearnSpell(SPECTRAL_TIGER, false);
        }

    }
};

class item_battle_royal_reward_mount_raven_lord : public ItemScript {
public:
    item_battle_royal_reward_mount_raven_lord() : ItemScript(
        "item_battle_royal_reward_mount_raven_lord") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(RAVEN_LORD)) {
            player->LearnSpell(RAVEN_LORD, false);
        }

    }
};

class item_battle_royal_reward_mount_invincible : public ItemScript {
public:
    item_battle_royal_reward_mount_invincible() : ItemScript(
        "item_battle_royal_reward_mount_invincible") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(INVINCIBLE)) {
            player->LearnSpell(INVINCIBLE, false);
        }

    }
};

class item_battle_royal_reward_mount_ashes_of_alar : public ItemScript {
public:
    item_battle_royal_reward_mount_ashes_of_alar() : ItemScript(
        "item_battle_royal_reward_mount_ashes_of_alar") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(ASHES_OF_ALAR)) {
            player->LearnSpell(ASHES_OF_ALAR, false);
        }

    }
};

class item_battle_royal_reward_mount_brewfest_kodo : public ItemScript {
public:
    item_battle_royal_reward_mount_brewfest_kodo() : ItemScript(
        "item_battle_royal_reward_mount_brewfest_kodo") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(BREWFEST_KODO)) {
            player->LearnSpell(BREWFEST_KODO, false);
        }

    }
};

class item_battle_royal_reward_mount_celestial_steed : public ItemScript {
public:
    item_battle_royal_reward_mount_celestial_steed() : ItemScript(
        "item_battle_royal_reward_mount_celestial_steed") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasSpell(CELESTIAL_STEED)) {
            player->LearnSpell(CELESTIAL_STEED, false);
        }

    }
};

class item_battle_royal_reward_season_1_shirt : public ItemScript {
public:
    item_battle_royal_reward_season_1_shirt() : ItemScript(
        "item_battle_royal_reward_season_1_shirt") {}

    bool OnUse(Player *player, Item *item,
               SpellCastTargets const & /*targets*/) override {

        if (!player->HasAura(SEASON_1_EFFECT)) {
            player->AddAura(SEASON_1_EFFECT, player);
        }
        return true;
    }

    bool OnExpire(Player* player, ItemTemplate const* /*proto*/) override {
        if (player->HasAura(SEASON_1_EFFECT)) {
            player->RemoveAura(SEASON_1_EFFECT);
        }
        return true;
    }

    // Called when the item is destroyed.
    bool OnRemove(Player* player, Item* /*item*/) override {
        if (player->HasAura(SEASON_1_EFFECT)) {
                player->RemoveAura(SEASON_1_EFFECT);
            }
        return true;
    }

};


class npc_battle_royal_reward_vendor : public CreatureScript {
public:
    npc_battle_royal_reward_vendor() : CreatureScript(
        "npc_battle_royal_reward_vendor") {
        _rewards = mapRewards();
    }

    static std::map<int, Reward> mapRewards() {

        std::map<int, Reward> r;
        for (auto &reward : rewards) {
            r[reward.id] = reward;
        }
        return r;
    }

    struct RewardVendorAI : public ScriptedAI {
    public:
        RewardVendorAI(Creature *creature) : ScriptedAI(creature) {}

        bool GossipHello(Player *player) override {
            return onGossipHello(player, me);
        }

        // icons -  https://wotlk.evowow.com/?icon=240
        static bool onGossipHello(Player *player, Creature *vendor) {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                             "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tTitles",
                             GOSSIP_SENDER_MAIN, TITLE_REWARDS);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                             "|TInterface/ICONS/Ability_mount_dreadsteed:30:30:-18:0|tMounts",
                             GOSSIP_SENDER_MAIN, MOUNT_REWARDS);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                             "|TInterface/ICONS/achievement_arena_3v3_7:30:30:-18:0|tItems",
                             GOSSIP_SENDER_MAIN, ITEM_REWARDS);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                             "|TInterface/ICONS/INV_Misc_coin_16:30:30:-18:0|tExchange 1 Kings Badge for 40 Bloodshed Tokens",
                             GOSSIP_SENDER_MAIN, EXCHANGE_REWARDS);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE,
                              vendor->GetGUID());
            return true;
        }

        static void ExchangeTokens(Player *player) {
            if (player->HasItemCount(KINGS_BADGE, 1)) {
                player->DestroyItemCount(KINGS_BADGE, 1, true);
                player->AddItem(BLOODSHED_TOKEN, 40);
            } else {
                player->GetSession()->SendAreaTriggerMessage(
                    "Sorry, you don't have enough tokens to buy that.");
            }
        }

        static void AddRewardGossipMenu(Player *player, REWARD_TYPE rewardType) {
            std::vector<Reward> menuRewards;
            for (const Reward &itr : rewards) {
                if (itr.type == rewardType) {
                    menuRewards.push_back(itr);
                }
            }

            std::sort(menuRewards.begin(), menuRewards.end(), compareByName);


            for (Reward &itr : menuRewards) {

                std::string badgeString;
                switch (itr.currency) {
                    case KINGS_BADGE:
                        badgeString = "King's Badge";
                        break;
                    case BLOODSHED_TOKEN:
                        badgeString = "Bloodshed Token";
                        break;
                }

                std::string cost =
                    itr.name + " (" + std::to_string(itr.cost) + ") " +
                    badgeString;
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, cost,
                                 GOSSIP_SENDER_MAIN, itr.id);
            }

        }

        static void selectReward(Player *player, int selectedReward) {
            auto rewarditr = _rewards.find(selectedReward);

            if (rewarditr == _rewards.end()) {
                player->GetSession()->SendAreaTriggerMessage(
                    "Item not found!");
            } else {
                Reward reward = rewarditr->second;
                if (player->HasItemCount(reward.currency, reward.cost)) {
                    player->DestroyItemCount(reward.currency, reward.cost,
                                             true);
                    player->AddItem(reward.id, 1);
                } else {
                    player->GetSession()->SendAreaTriggerMessage(
                        "Sorry, you don't have enough tokens to buy that.");
                }
            }
        }

        bool GossipSelect(Player *player, uint32 /*menuId*/,
                          uint32 gossipListId) override {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(
                gossipListId);
            ClearGossipMenuFor(player);
            switch (action) {
                case TITLE_REWARDS:
                    player->PlayerTalkClass->SendCloseGossip();
                    AddRewardGossipMenu(player, REWARD_TYPE_TITLE);
                    SendGossipMenuFor(player, 696900, me->GetGUID());
                    break;
                case MOUNT_REWARDS:
                    player->PlayerTalkClass->SendCloseGossip();
                    AddRewardGossipMenu(player, REWARD_TYPE_MOUNT);
                    SendGossipMenuFor(player, 696900, me->GetGUID());
                    break;
                case ITEM_REWARDS:
                    player->PlayerTalkClass->SendCloseGossip();
                    AddRewardGossipMenu(player, REWARD_TYPE_ITEM);
                    SendGossipMenuFor(player, 696900, me->GetGUID());
                    break;
                case EXCHANGE_REWARDS:
                    ExchangeTokens(player);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                default:
                    selectReward(player, (int) action);
                    CloseGossipMenuFor(player);
                    break;
            }
            return false;
        };
    };

    CreatureAI *GetAI(Creature *creature) const override {
        return new RewardVendorAI(creature);
    }

};


void AddSC_battle_royal_rewards() {
    // Kills Title Rewards
    new item_battle_royal_reward_title_battlemaster();
    new item_battle_royal_reward_title_blood_guard();
    new item_battle_royal_reward_title_blood_sail();
    new item_battle_royal_reward_title_brutual_gladiator();
    new item_battle_royal_reward_title_commander();
    new item_battle_royal_reward_title_deadly_gladiator();
    new item_battle_royal_reward_title_flame_keeper();
    new item_battle_royal_reward_title_grunt();
    new item_battle_royal_reward_title_knight_champion();
    new item_battle_royal_reward_title_merrymaker();
    new item_battle_royal_reward_title_vanquisher();

    // Win Title Rewards
    new item_battle_royal_reward_title_bane_of_fallen_king();
    new item_battle_royal_reward_title_crusader();
    new item_battle_royal_reward_title_champion();
    new item_battle_royal_reward_title_celestial_defender();

    /* Mounts */
    new item_battle_royal_reward_mount_amani_warbear();
    new item_battle_royal_reward_mount_ashes_of_alar();
    new item_battle_royal_reward_mount_brewfest_ram();
    new item_battle_royal_reward_mount_dark_riding_talbuk();
    new item_battle_royal_reward_mount_fiery_warhorse();
    new item_battle_royal_reward_mount_invincible();
    new item_battle_royal_reward_mount_magic_rooster();
    new item_battle_royal_reward_mount_raven_lord();
    new item_battle_royal_reward_mount_spectral_tiger();
    new item_battle_royal_reward_mount_zulian_tiger();
    new item_battle_royal_reward_mount_war_stead();
    new item_battle_royal_reward_mount_brewfest_kodo();
    new item_battle_royal_reward_mount_celestial_steed();


    // Rewards Vendor
    new npc_battle_royal_reward_vendor();
    new item_battle_royal_reward_season_1_shirt();
}
