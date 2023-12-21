CPortFolio
==========
#### 3인칭 액션,생존게임(맵 내의 좀비를 모두 처치하여 클리어)

개발 환경
---------
 * Unreal Engine 4.27
 * Visual Studio 2019 (C++)

제작 기간
---------
 * 2023년 11월 6일 ~ 

포트폴리오 설명
---------------
![image](https://github.com/HyukJun46/CPortFolio/assets/126559827/4fde759e-3eb7-4ab1-8120-a1a72d77e807)

맵 내의 모든 좀비들을 처치하여 생존하는 게임입니다.    
플레이어는 다양한 종류의 전투 모션을 이용하여 좀비들을 물리치고    
적을 처치하여 얻는 보상으로 체력회복이나 아이템 강화 및 구매하여 플레이할 수 있습니다.   
맵의 숨겨진 위치를 발견하여 좀비의 공격을 피해 안전한 곳으로 이동하여 전략적인 전투를 할 수 있으며   
기본적인 기능들을 이용해 게임을 제작하였습니다.    

사용된 기능
-----------
## 사용자 정의 컴포넌트

1. OptionComponent - 플레이어의 시점(카메라) 확대 및 축소, 마우스 감도 등 플레이 환경을 관리하는 컴포넌트

2. StatusComponent - 캐릭터의 이동 상태나 체력 등을 나타내는 컴포넌트

3. StateComponent - 캐릭터의 행동을 나타내며 현재 어떠한 상태인지 알 수 있게 해주는 컴포넌트
<pre>
<code>
UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Roll, Equip, Action, Hitted, Dead, Max
};
</code>
</pre>
 + Idle : 캐릭터가 아무행동도 하지 않는 상태
 + Roll : 캐릭터가 구르는 상태 
 + Equip : 캐릭터가 무기를 장착하고 있는 상태
 + Action : 캐릭터가 공격하는 상태
 + Hitted : 캐릭터가 공격을 당하고 있는 상태
 + Dead : 캐릭터가 사망한 상태

4. MontageComponent - 캐릭터의 몽타주를 데이터 테이블로 만든 후 컴포넌트로 장착하여 실행하는 컴포넌트
<pre>
<code>
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase 
{
	GENERATED_BODY()

public:
	static void Log(const FString& InValue);

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove;
};
</code>
</pre>

5. ActionComponent - 캐릭터의 무기와 교체를 담당하는 컴포넌트
<pre>
<code>
UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, Sword, Gun, Grenade, Max
};
</code>
</pre>
 + Unarmed : 캐릭터가 무기를 착용하지 않은 상태
 + Fist : 주먹을 이용한 캐릭터의 근접 공격
 + Sword : 칼을 이용한 캐릭터의 근접 공격
 + Gun : 총을 이용한 캐릭터의 원거리 공격
 + Grenade : 수류탄을 이용한 원거리 공격

6. BehaviorComponent - AIController를 이용하여 적의 행동 상태를 나타내는 컴포넌트
<pre>
<code>
UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted
};
</code>
</pre>

7. PatrolComponent - AI의 적들의 순찰경로를 지정한다.

노티파이
--------

1. RolledNotify
 + 플레이어가 구른 후 UnarmedMode로 돌아갈 수 있도록 알려준다.
   
3. BeginNotify
 + 콤보 공격 시 콤보 카운트를 증가하여 다음 공격 모션이 나가야 함을 알려준다.

4. EndNotify
 + 공격이 종료되었음을 알려준다.
 + 콤보카운트를 다시 0으로 만들고 다시 UnarmedMode로 돌아가게 알려준다.

5. HittedNotify
 + 캐릭터가 공격 당했을 때 맞는 모션 후 다시 UnarmedMode로 돌아가게 알려준다.

6. EquipNotify
 + 캐릭터가 무기를 장착했음을 알려주는 노티파이

7. ComboNotify(State)
 + 공격 모션 중 콤보 노티파이 스테이트 구간 안에서 다시 공격할 경우 다음 콤보 공격 모션이 재생된다.

7. CollisionNotify(State)
 + 애니메이션에 맞게 공격 모션 지정 시 충돌체를 지정하는 노티파이 스테이트
 + Collision의 노티파이 스테이트 구간 안에 충돌체가 있을 경우 데미지를 준다.

데이터 에셋
-----------
### 구조체를 사용하여 하나의 데이터 에셋에 다양한 데이터들을 사용할 수 있게 하였다.

1. EquipData - 몽타주, 몽타주 재생시간, 이동공격 여부 등을 장착 모션들을 Blueprint에서 손쉽게 관리할 수 잇다.
<pre>
<code>
USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};
</code>
</pre>

2. DoActionData - 데미지, 이펙트 등 공격에 관련된 설정들을 Blueprint에서 손쉽게 관리할 수 있다.
<pre>
<code>
USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 1.f;

	UPROPERTY(EditAnywhere)
		float HitStop;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACBullet> ProjectileClass;
};
</code>
</pre>

BehaviorTree
------------
### 비헤이비어 트리를 사용하여 적들의 행동을 관리한다.

1. PatrolNode - 적이 플레이어를 발견하기 전 까지 순찰경로를 따라 움직인다.
![image](https://github.com/HyukJun46/CPortFolio/assets/126559827/855f084b-26cb-487a-90e9-5a2734550255)

2. MoveSpeedNode - 적이 플레이어를 발견 할 경우 플레이어를 쫓아온다.
![image](https://github.com/HyukJun46/CPortFolio/assets/126559827/410ed7c9-86db-4cbc-80a1-409d6af724f7)

3. ActionNode - 적이 플레이어를 발견 할 경우 플레이어를 공격한다.
![image](https://github.com/HyukJun46/CPortFolio/assets/126559827/7d7765a2-1559-4b36-93fe-d27380951ad7)

+ 플레이어가 일정 거리 이상 멀어진다면 Spline으로 되돌아가 다시 순찰을 시작한다.
