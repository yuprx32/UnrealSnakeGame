// SnakeGame project

#include "World/SG_SnakeLink.h"
#include "Components/StaticMeshComponent.h"
#include "SG_WorldUtils.h"

ASG_SnakeLink::ASG_SnakeLink()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);

    LinkMesh = CreateDefaultSubobject<UStaticMeshComponent>("LinkMesh");
    check(LinkMesh);
    LinkMesh->SetupAttachment(Origin);
}

void ASG_SnakeLink::UpdateColors(const FLinearColor& Color)
{
    if (auto* LinkMaterial = LinkMesh->CreateAndSetMaterialInstanceDynamic(0))
    {
        LinkMaterial->SetVectorParameterValue("Color", Color);
    }
}

void ASG_SnakeLink::UpdateScale(uint32 CellSize)
{
    check(LinkMesh->GetStaticMesh());
    SnakeGame::WorldUtils::ScaleMesh(LinkMesh, FVector(CellSize));
}