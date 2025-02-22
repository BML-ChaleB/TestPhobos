#pragma once
#include <WarheadTypeClass.h>
#include <SuperWeaponTypeClass.h>
#include <Helpers/Macro.h>
#include <Utilities/Container.h>
#include <Utilities/TemplateDef.h>
#include <New/Type/ShieldTypeClass.h>
#include <Ext/Bullet/Body.h>
#include <Misc/TypeConvertHelper.h>

class WarheadTypeExt
{
public:
	using base_type = WarheadTypeClass;

	static constexpr DWORD Canary = 0x22222222;
	static constexpr size_t ExtPointerOffset = 0x18;

	class ExtData final : public Extension<WarheadTypeClass>
	{
	public:

		Valueable<bool> SpySat;
		Valueable<bool> BigGap;
		Valueable<int> TransactMoney;
		Valueable<bool> TransactMoney_Display;
		Valueable<AffectedHouse> TransactMoney_Display_Houses;
		Valueable<bool> TransactMoney_Display_AtFirer;
		Valueable<Point2D> TransactMoney_Display_Offset;
		NullableVector<AnimTypeClass*> SplashList;
		Valueable<bool> SplashList_PickRandom;
		Valueable<bool> SplashList_CreateAll;
		Valueable<int> SplashList_CreationInterval;
		Valueable<bool> AnimList_PickRandom;
		Valueable<bool> AnimList_CreateAll;
		Valueable<int> AnimList_CreationInterval;
		Valueable<bool> CreateAnimsOnZeroDamage;
		Valueable<bool> Conventional_IgnoreUnits;
		Valueable<bool> RemoveDisguise;
		Valueable<bool> RemoveMindControl;
		Valueable<bool> DecloakDamagedTargets;
		Valueable<bool> ShakeIsLocal;

		Valueable<double> Crit_Chance;
		Valueable<bool> Crit_ApplyChancePerTarget;
		Valueable<int> Crit_ExtraDamage;
		Nullable<WarheadTypeClass*> Crit_Warhead;
		Valueable<AffectedTarget> Crit_Affects;
		Valueable<AffectedHouse> Crit_AffectsHouses;
		ValueableVector<AnimTypeClass*> Crit_AnimList;
		Nullable<bool> Crit_AnimList_PickRandom;
		Valueable<bool> Crit_AnimOnAffectedTargets;
		Valueable<double> Crit_AffectBelowPercent;
		Valueable<bool> Crit_SuppressWhenIntercepted;

		Nullable<AnimTypeClass*> MindControl_Anim;

		Valueable<bool> Shield_Penetrate;
		Valueable<bool> Shield_Break;
		Nullable<AnimTypeClass*> Shield_BreakAnim;
		Nullable<AnimTypeClass*> Shield_HitAnim;
		Nullable<WeaponTypeClass*> Shield_BreakWeapon;

		Nullable<double> Shield_AbsorbPercent;
		Nullable<double> Shield_PassPercent;
		Nullable<int> Shield_ReceivedDamage_Minimum;
		Nullable<int> Shield_ReceivedDamage_Maximum;

		Valueable<int> Shield_Respawn_Duration;
		Valueable<double> Shield_Respawn_Amount;
		Valueable<int> Shield_Respawn_Rate;
		Valueable<bool> Shield_Respawn_RestartTimer;
		Valueable<int> Shield_SelfHealing_Duration;
		Nullable<double> Shield_SelfHealing_Amount;
		Valueable<int> Shield_SelfHealing_Rate;
		Nullable<bool> Shield_SelfHealing_RestartInCombat;
		Valueable<int> Shield_SelfHealing_RestartInCombatDelay;
		Valueable<bool> Shield_SelfHealing_RestartTimer;

		ValueableVector<ShieldTypeClass*> Shield_AttachTypes;
		ValueableVector<ShieldTypeClass*> Shield_RemoveTypes;
		Valueable<bool> Shield_ReplaceOnly;
		Valueable<bool> Shield_ReplaceNonRespawning;
		Valueable<bool> Shield_InheritStateOnReplace;
		Valueable<int> Shield_MinimumReplaceDelay;
		ValueableVector<ShieldTypeClass*> Shield_AffectTypes;
		NullableVector<ShieldTypeClass*> Shield_Penetrate_Types;
		NullableVector<ShieldTypeClass*> Shield_Break_Types;
		NullableVector<ShieldTypeClass*> Shield_Respawn_Types;
		NullableVector<ShieldTypeClass*> Shield_SelfHealing_Types;

		Valueable<int> NotHuman_DeathSequence;
		ValueableIdxVector<SuperWeaponTypeClass> LaunchSW;
		Valueable<bool> LaunchSW_RealLaunch;
		Valueable<bool> LaunchSW_IgnoreInhibitors;
		Valueable<bool> LaunchSW_IgnoreDesignators;
		Valueable<bool> LaunchSW_DisplayMoney;
		Valueable<AffectedHouse> LaunchSW_DisplayMoney_Houses;
		Valueable<Point2D> LaunchSW_DisplayMoney_Offset;

		Valueable<bool> AllowDamageOnSelf;
		NullableVector<AnimTypeClass*> DebrisAnims;
		Valueable<bool> Debris_Conventional;

		Valueable<bool> DetonateOnAllMapObjects;
		Valueable<bool> DetonateOnAllMapObjects_RequireVerses;
		Valueable<AffectedTarget> DetonateOnAllMapObjects_AffectTargets;
		Valueable<AffectedHouse> DetonateOnAllMapObjects_AffectHouses;
		ValueableVector<TechnoTypeClass*> DetonateOnAllMapObjects_AffectTypes;
		ValueableVector<TechnoTypeClass*> DetonateOnAllMapObjects_IgnoreTypes;

		std::vector<TypeConvertGroup> Convert_Pairs;

		Valueable<bool> InflictLocomotor;
		Valueable<bool> RemoveInflictedLocomotor;

		// Ares tags
		// http://ares-developers.github.io/Ares-docs/new/warheads/general.html
		Valueable<bool> AffectsEnemies;
		Nullable<bool> AffectsOwner;

		double Crit_RandomBuffer;
		bool HasCrit;
		bool WasDetonatedOnAllMapObjects;
		bool Splashed;
		int RemainingAnimCreationInterval;
		bool PossibleCellSpreadDetonate;

	private:
		Valueable<double> Shield_Respawn_Rate_InMinutes;
		Valueable<double> Shield_SelfHealing_Rate_InMinutes;

	public:
		ExtData(WarheadTypeClass* OwnerObject) : Extension<WarheadTypeClass>(OwnerObject)
			, SpySat { false }
			, BigGap { false }
			, TransactMoney { 0 }
			, TransactMoney_Display { false }
			, TransactMoney_Display_Houses { AffectedHouse::All }
			, TransactMoney_Display_AtFirer { false }
			, TransactMoney_Display_Offset { { 0, 0 } }
			, SplashList {}
			, SplashList_PickRandom { false }
			, SplashList_CreateAll { false }
			, SplashList_CreationInterval { 0 }
			, AnimList_PickRandom { false }
			, AnimList_CreateAll { false }
			, AnimList_CreationInterval { 0 }
			, CreateAnimsOnZeroDamage { false }
			, Conventional_IgnoreUnits { false }
			, RemoveDisguise { false }
			, RemoveMindControl { false }
			, DecloakDamagedTargets { true }
			, ShakeIsLocal { false }

			, Crit_Chance { 0.0 }
			, Crit_ApplyChancePerTarget { false }
			, Crit_ExtraDamage { 0 }
			, Crit_Warhead {}
			, Crit_Affects { AffectedTarget::All }
			, Crit_AffectsHouses { AffectedHouse::All }
			, Crit_AnimList {}
			, Crit_AnimList_PickRandom {}
			, Crit_AnimOnAffectedTargets { false }
			, Crit_AffectBelowPercent { 1.0 }
			, Crit_SuppressWhenIntercepted { false }

			, MindControl_Anim {}

			, Shield_Penetrate { false }
			, Shield_Break { false }
			, Shield_BreakAnim {}
			, Shield_HitAnim {}
			, Shield_BreakWeapon {}
			, Shield_AbsorbPercent {}
			, Shield_PassPercent {}
			, Shield_ReceivedDamage_Minimum {}
			, Shield_ReceivedDamage_Maximum {}

			, Shield_Respawn_Duration { 0 }
			, Shield_Respawn_Amount { 0.0 }
			, Shield_Respawn_Rate { -1 }
			, Shield_Respawn_Rate_InMinutes { -1.0 }
			, Shield_Respawn_RestartTimer { false }
			, Shield_SelfHealing_Duration { 0 }
			, Shield_SelfHealing_Amount { }
			, Shield_SelfHealing_Rate { -1 }
			, Shield_SelfHealing_Rate_InMinutes { -1.0 }
			, Shield_SelfHealing_RestartInCombat {}
			, Shield_SelfHealing_RestartInCombatDelay { -1 }
			, Shield_SelfHealing_RestartTimer { false }
			, Shield_AttachTypes {}
			, Shield_RemoveTypes {}
			, Shield_ReplaceOnly { false }
			, Shield_ReplaceNonRespawning { false }
			, Shield_InheritStateOnReplace { false }
			, Shield_MinimumReplaceDelay { 0 }
			, Shield_AffectTypes {}
			, Shield_Penetrate_Types {}
			, Shield_Break_Types {}
			, Shield_Respawn_Types {}
			, Shield_SelfHealing_Types {}

			, NotHuman_DeathSequence { -1 }
			, LaunchSW {}
			, LaunchSW_RealLaunch { true }
			, LaunchSW_IgnoreInhibitors { false }
			, LaunchSW_IgnoreDesignators { true }
			, LaunchSW_DisplayMoney { false }
			, LaunchSW_DisplayMoney_Houses { AffectedHouse::All }
			, LaunchSW_DisplayMoney_Offset { { 0, 0 } }

			, AllowDamageOnSelf { false }
			, DebrisAnims {}
			, Debris_Conventional { false }

			, DetonateOnAllMapObjects { false }
			, DetonateOnAllMapObjects_RequireVerses { false }
			, DetonateOnAllMapObjects_AffectTargets { AffectedTarget::None }
			, DetonateOnAllMapObjects_AffectHouses { AffectedHouse::None }
			, DetonateOnAllMapObjects_AffectTypes {}
			, DetonateOnAllMapObjects_IgnoreTypes {}

			, Convert_Pairs {}

			, InflictLocomotor { false }
			, RemoveInflictedLocomotor { false }

			, AffectsEnemies { true }
			, AffectsOwner {}

			, Crit_RandomBuffer { 0.0 }
			, HasCrit { false }
			, WasDetonatedOnAllMapObjects { false }
			, Splashed { false }
			, RemainingAnimCreationInterval { 0 }
			, PossibleCellSpreadDetonate {false}
		{ }

	private:
		void DetonateOnOneUnit(HouseClass* pHouse, TechnoClass* pTarget, TechnoClass* pOwner = nullptr, bool bulletWasIntercepted = false);

		void ApplyRemoveDisguiseToInf(HouseClass* pHouse, TechnoClass* pTarget);
		void ApplyRemoveMindControl(HouseClass* pHouse, TechnoClass* pTarget);
		void ApplyCrit(HouseClass* pHouse, TechnoClass* pTarget, TechnoClass* Owner);
		void ApplyShieldModifiers(TechnoClass* pTarget);
		void ApplyConvert(HouseClass* pHouse, TechnoClass* pTarget);
		void ApplyLocomotorInfliction(TechnoClass* pTarget);
		void ApplyLocomotorInflictionReset(TechnoClass* pTarget);

	public:
		void Detonate(TechnoClass* pOwner, HouseClass* pHouse, BulletExt::ExtData* pBullet, CoordStruct coords);
		bool CanTargetHouse(HouseClass* pHouse, TechnoClass* pTechno);
		void InterceptBullets(TechnoClass* pOwner, WeaponTypeClass* pWeapon, CoordStruct coords);
		bool EligibleForFullMapDetonation(TechnoClass* pTechno, HouseClass* pOwner);

		virtual ~ExtData() = default;
		virtual void LoadFromINIFile(CCINIClass* pINI) override;
		virtual void InvalidatePointer(void* ptr, bool bRemoved) override { }
		virtual void LoadFromStream(PhobosStreamReader& Stm) override;
		virtual void SaveToStream(PhobosStreamWriter& Stm) override;

	private:
		template <typename T>
		void Serialize(T& Stm);
	};

	class ExtContainer final : public Container<WarheadTypeExt>
	{
	public:
		ExtContainer();
		~ExtContainer();
	};

	static ExtContainer ExtMap;
	static bool LoadGlobals(PhobosStreamReader& Stm);
	static bool SaveGlobals(PhobosStreamWriter& Stm);

	static void DetonateAt(WarheadTypeClass* pThis, AbstractClass* pTarget, TechnoClass* pOwner, int damage, HouseClass* pFiringHouse = nullptr);
	static void DetonateAt(WarheadTypeClass* pThis, const CoordStruct& coords, TechnoClass* pOwner, int damage, HouseClass* pFiringHouse = nullptr);
};
