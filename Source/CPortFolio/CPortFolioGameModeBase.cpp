#include "CPortFolioGameModeBase.h"
#include "GameFramework/HUD.h"

ACPortFolioGameModeBase::ACPortFolioGameModeBase()
{

	ConstructorHelpers::FClassFinder<AHUD> asset(L"Blueprint'/Game/BP_CHUD.BP_CHUD_C'");
	verifyf(asset.Succeeded(), L"Class Not Found");
	HUDClass = asset.Class;

}