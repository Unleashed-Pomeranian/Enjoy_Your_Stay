
#pragma once

#include "EYS_InteractInterface.generated.h"

class AEYS_MyCharacter;

  UINTERFACE(MinimalAPI,Blueprintable)
      class UEYS_InteractInterface : public UInterface
  {

      GENERATED_BODY()



  };

  class IEYS_InteractInterface
  {
      GENERATED_BODY()

  public:
     
      UFUNCTION(BlueprintNativeEvent, Category = Interact)
      void eInteract(AEYS_MyCharacter* myPlayer);

      UFUNCTION()
      virtual void Interact(AEYS_MyCharacter* myPlayer)=0;

      UFUNCTION(BlueprintNativeEvent, Category = Interact)
      void aInteract(AEYS_MyCharacter* myPlayer, int32 Value);

      UFUNCTION(BlueprintNativeEvent, Category = Interact)
      void InteractUI(AEYS_MyCharacter* myPlayer);

  public:
     
  };