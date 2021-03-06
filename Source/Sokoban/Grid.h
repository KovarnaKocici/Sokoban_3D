// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class SOKOBAN_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrid(const FObjectInitializer &ObjectInitializer);

	//SceneComponent as Root
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Initialize)
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialize)
		int Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialize)
		int Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialize)
		UStaticMesh* DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialize)
		UMaterialInterface* Material1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialize)
		UMaterialInterface* Material2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ConstructionScript
	virtual void OnConstruction(const FTransform & Transform) override;

	UFUNCTION()
	UMaterialInterface* SwitchCellMaterial(int row, int column);

};