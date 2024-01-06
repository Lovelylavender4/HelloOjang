#pragma once

#include "mc/_HeaderOutputPredefine.h"

class ScoreboardEventCoordinator {
public:
    // prevent constructor by default
    ScoreboardEventCoordinator& operator=(ScoreboardEventCoordinator const&);
    ScoreboardEventCoordinator(ScoreboardEventCoordinator const&);
    ScoreboardEventCoordinator();

public:
    // NOLINTBEGIN
    // vIndex: 0, symbol: ??1ScoreboardEventCoordinator@@UEAA@XZ
    virtual ~ScoreboardEventCoordinator();

    // symbol:
    // ?sendOnObjectiveAdded@ScoreboardEventCoordinator@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    MCAPI void sendOnObjectiveAdded(std::string const& objective);

    // symbol:
    // ?sendOnObjectiveRemoved@ScoreboardEventCoordinator@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    MCAPI void sendOnObjectiveRemoved(std::string const& objective);

    // symbol:
    // ?sendOnScoreChanged@ScoreboardEventCoordinator@@QEAAXAEBUScoreboardId@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    MCAPI void sendOnScoreChanged(struct ScoreboardId const& id, std::string const& objective, int score);

    // symbol: ?sendOnScoreboardIdentityRemoved@ScoreboardEventCoordinator@@QEAAXAEBUScoreboardId@@@Z
    MCAPI void sendOnScoreboardIdentityRemoved(struct ScoreboardId const& id);

    // NOLINTEND
};
