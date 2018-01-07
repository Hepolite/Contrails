
#include "Initializer.h"

#include "core/setup/SetupAssets.h"
#include "core/setup/SetupScene.h"
#include "core/setup/SetupScripts.h"
#include "core/setup/SetupUbos.h"

void core::setup::initialize(Engine & engine)
{
	setupUbos(engine);
	setupAssets(engine);
	setupScripts(engine);
	setupScene(engine);
}