#pragma once

#include <filesystem>

#include "ll/api/base/FixedString.h"
#include "ll/api/event/Event.h"
#include "ll/api/event/Listener.h"

namespace ll::event {
namespace detail {
class FileWatch;
class FileActionEmitter : public Emitter {
    std::unique_ptr<FileWatch> watcher;

public:
    LLAPI FileActionEmitter(std::string const& path);
    ~FileActionEmitter() override;
};
} // namespace detail


enum class FileActionType {
    Added = 1,
    Removed,
    Modified,
    RenamedOld,
    RenamedNew,
};

// usually for non native plugins
class DynamicFileActionEvent : public Event {
public:
    std::filesystem::path path;
    FileActionType        type;

    DynamicFileActionEvent(std::filesystem::path const& p, FileActionType e) : path(p), type(e) {}
};

template <FixedString WatchedPath>
class FileActionEvent : public DynamicFileActionEvent {
    static constexpr auto CustomIdOwn{
        FixedString<ll::reflection::type_name_v<FileActionEvent>.size()>{ll::reflection::type_name_v<FileActionEvent>}
        + FixedString{"|"} + WatchedPath
    };

public:
    static constexpr EventId CustomEventId{CustomIdOwn};
};

template <FixedString WatchedPath>
class Listener<FileActionEvent<WatchedPath>> : public ListenerBase {
public:
    using EventType = FileActionEvent<WatchedPath>;
    using Callback  = std::function<void(EventType&)>;

    explicit Listener(Callback const& fn, EventPriority priority = EventPriority::Normal)
    : ListenerBase(priority),
      callback(fn) {}

    ~Listener() override = default;

    void call(Event& event) override { callback(static_cast<EventType&>(event)); }

    std::unique_ptr<Emitter> getEmitter() override { return std::make_unique<detail::FileActionEmitter>(WatchedPath); }

    static std::shared_ptr<Listener> create(Callback const& fn, EventPriority priority = EventPriority::Normal) {
        return std::make_shared<Listener>(fn, priority);
    }

private:
    Callback callback;
};

template <>
class Listener<DynamicFileActionEvent> : public ListenerBase {
public:
    using EventType = DynamicFileActionEvent;
    using Callback  = std::function<void(EventType&)>;

    explicit Listener(std::string const& path, Callback const& fn, EventPriority priority = EventPriority::Normal)
    : ListenerBase(priority),
      callback(fn),
      path(path) {
        nativeId.assign(ll::reflection::type_name_v<FileActionEvent<"">>);
        nativeId += "|";
        nativeId += path;
    }

    EventId getEventId() const { return EventId{nativeId}; }

    ~Listener() override = default;

    void call(Event& event) override { callback(static_cast<EventType&>(event)); }

    std::unique_ptr<Emitter> getEmitter() override { return std::make_unique<detail::FileActionEmitter>(path); }

    static std::shared_ptr<Listener>
    create(std::string const& path, Callback const& fn, EventPriority priority = EventPriority::Normal) {
        return std::make_shared<Listener>(path, fn, priority);
    }

private:
    Callback    callback;
    std::string path;
    std::string nativeId;
};
} // namespace ll::event
