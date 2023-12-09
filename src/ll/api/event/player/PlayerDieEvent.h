#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/player/PlayerEvent.h"

#include "mc/world/actor/ActorDamageSource.h"

namespace ll::event::inline player {

class PlayerDieEvent : public PlayerEvent {
    ActorDamageSource const& mSource;

public:
    constexpr explicit PlayerDieEvent(Player& player, ActorDamageSource const& source)
    : PlayerEvent(player),
      mSource(source) {}

    LLNDAPI ActorDamageSource const& source() const;
};
} // namespace ll::event::inline player
