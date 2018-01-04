
#include "Initializer.h"

#include "core/setup/SetupAssets.h"
#include "core/setup/SetupScripts.h"
#include "core/setup/SetupUbos.h"

#include "logic/event/EventBus.h"
#include "logic/event/Events.h"

void core::setup::initialize(Engine & engine)
{
	setupUbos(engine);
	setupAssets(engine);
	setupScripts(engine);

	detail::setupEvents(engine);
}

void core::setup::detail::setupEvents(Engine & engine)
{
	auto & bus = engine.getEventBus();

	bus.add<logic::event::DisplayClose>([&engine](auto &) { engine.stop(); });
}
