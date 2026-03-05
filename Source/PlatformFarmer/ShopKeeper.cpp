#include "ShopKeeper.h"

#include "PlayerCharacter.h"

AShopKeeper::AShopKeeper()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	
	ShopKeeperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ShopKeeperFlipbook"));
	ShopKeeperFlipbook->SetupAttachment(RootComponent);
	
	InteractKeySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("InteractKeySprite"));
	InteractKeySprite->SetupAttachment(RootComponent);
}

void AShopKeeper::BeginPlay()
{
	Super::BeginPlay();
	
	InteractKeySprite->SetVisibility(false);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AShopKeeper::OnComponentOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AShopKeeper::OnComponentOverlapEnd);
}

void AShopKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShopKeeper::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		InteractKeySprite->SetVisibility(true);
		PlayerOverlapping = true;
	}
}

void AShopKeeper::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractKeySprite->SetVisibility(false);
	PlayerOverlapping = false;
}

