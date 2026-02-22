#include "Tree.h"

ATree::ATree()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	TreeSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TreeSprite"));
	TreeSprite->SetupAttachment(RootComponent);

	StumpSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("StumpSprite"));
	StumpSprite->SetupAttachment(RootComponent);
}

void ATree::BeginPlay()
{
	Super::BeginPlay();
	
	StumpSprite->SetVisibility(false);
}

void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

