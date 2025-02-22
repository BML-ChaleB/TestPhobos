#include "Body.h"

#include <Ext/CaptureManager/Body.h>
#include <Ext/WarheadType/Body.h>

void TechnoExt::TransferMindControlOnDeploy(TechnoClass* pTechnoFrom, TechnoClass* pTechnoTo)
{
	auto const pAnimType = pTechnoFrom->MindControlRingAnim ?
		pTechnoFrom->MindControlRingAnim->Type : TechnoExt::ExtMap.Find(pTechnoFrom)->MindControlRingAnimType;

	if (auto Controller = pTechnoFrom->MindControlledBy)
	{
		if (auto Manager = Controller->CaptureManager)
		{
			CaptureManagerExt::FreeUnit(Manager, pTechnoFrom, true);

			if (CaptureManagerExt::CaptureUnit(Manager, pTechnoTo, false, pAnimType, true))
			{
				if (auto pBld = abstract_cast<BuildingClass*>(pTechnoTo))
				{
					// Capturing the building after unlimbo before buildup has finished or even started appears to throw certain things off,
					// Hopefully this is enough to fix most of it like anims playing prematurely etc.
					pBld->ActuallyPlacedOnMap = false;
					pBld->DestroyNthAnim(BuildingAnimSlot::All);

					pBld->BeginMode(BStateType::Construction);
					pBld->QueueMission(Mission::Construction, false);
				}
			}
			else
			{
				int nSound = pTechnoTo->GetTechnoType()->MindClearedSound;
				if (nSound == -1)
					nSound = RulesClass::Instance->MindClearedSound;
				if (nSound != -1)
					VocClass::PlayIndexAtPos(nSound, pTechnoTo->Location);
			}

		}
	}
	else if (auto MCHouse = pTechnoFrom->MindControlledByHouse)
	{
		pTechnoTo->MindControlledByHouse = MCHouse;
		pTechnoFrom->MindControlledByHouse = nullptr;
	}
	else if (pTechnoFrom->MindControlledByAUnit) // Perma MC
	{
		pTechnoTo->MindControlledByAUnit = true;

		auto const pBuilding = abstract_cast<BuildingClass*>(pTechnoTo);
		CoordStruct location = pTechnoTo->GetCoords();

		if (pBuilding)
			location.Z += pBuilding->Type->Height * Unsorted::LevelHeight;
		else
			location.Z += pTechnoTo->GetTechnoType()->MindControlRingOffset;

		if (auto const pAnim = GameCreate<AnimClass>(pAnimType, location, 0, 1))
		{
			pTechnoTo->MindControlRingAnim = pAnim;

			if (pBuilding)
				pAnim->ZAdjust = -1024;

			pAnim->SetOwnerObject(pTechnoTo);
		}

	}
}

DEFINE_HOOK(0x739956, UnitClass_Deploy_Transfer, 0x6)
{
	GET(UnitClass*, pUnit, EBP);
	GET(BuildingClass*, pStructure, EBX);

	TechnoExt::TransferMindControlOnDeploy(pUnit, pStructure);
	ShieldClass::SyncShieldToAnother(pUnit, pStructure);
	TechnoExt::SyncIronCurtainStatus(pUnit, pStructure);

	return 0;
}

DEFINE_HOOK(0x44A03C, BuildingClass_Mi_Selling_Transfer, 0x6)
{
	GET(BuildingClass*, pStructure, EBP);
	GET(UnitClass*, pUnit, EBX);

	TechnoExt::TransferMindControlOnDeploy(pStructure, pUnit);
	ShieldClass::SyncShieldToAnother(pStructure, pUnit);
	TechnoExt::SyncIronCurtainStatus(pStructure, pUnit);

	pUnit->QueueMission(Mission::Hunt, true);
	//Why?
	return 0;
}

DEFINE_HOOK(0x449E2E, BuildingClass_Mi_Selling_CreateUnit, 0x6)
{
	GET(BuildingClass*, pStructure, EBP);
	R->ECX<HouseClass*>(pStructure->GetOriginalOwner());

	// Remember MC ring animation.
	if (pStructure->IsMindControlled())
	{
		auto const pTechnoExt = TechnoExt::ExtMap.Find(pStructure);
		pTechnoExt->UpdateMindControlAnim();
	}

	return 0x449E34;
}

DEFINE_HOOK(0x7396AD, UnitClass_Deploy_CreateBuilding, 0x6)
{
	GET(UnitClass*, pUnit, EBP);
	R->EDX<HouseClass*>(pUnit->GetOriginalOwner());

	return 0x7396B3;
}
