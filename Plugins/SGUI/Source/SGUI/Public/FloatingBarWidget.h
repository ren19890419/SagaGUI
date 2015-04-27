#pragma once

#include "Blueprint/UserWidget.h"
#include "FloatingBarWidget.generated.h"

/**
 *  Widget for floating bars. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UFloatingBarWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/* Hide the widget, when distane between follow target and the master controller is more than this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	float VisibleRadius = 1500.f;

	/* Speed of revealing\hiding the widget, controlled by visible radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	float VisibilityTransitionSpeed = 5.f;

	/** 
	 *	Creates the widget and adds it to the viewport.
	 *	@param masterController Controller of the player, that will own the widget.
	 *	@param followTarget An actor, which the widget will allign itsels with.
	 *	@param offset Offset to the follow target location in world space.
	 *	@param barColor Fill color of the bar.
	 *	@return Instance of the created widget.
	 */
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|FloatingBarWidget")
	static UFloatingBarWidget* Create(APlayerController* masterController, AActor* followTarget, FVector offset = FVector::ZeroVector, FLinearColor fillColor = FLinearColor::Red);

	/**
	 *	Sets the fill amount of the progress bar. 
	 *	@param value Fill value. Should be in 0.0 to 1.0 range.
	 */
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|FloatingBarWidget")
	void SetFillAmount(const float& value);
	
	/**
	*	Binds the fill amount of the progress bar.
	*	@param functor The lambda expression, which will be called on every tick to update fill value. 
	*	Should return float and take no parameters.
	*/
	template<typename FunctorType>
	void BindFillAmount(FunctorType&& functor) { onTick.BindLambda(Forward<FunctorType>(functor)); }

	/**
	*	Sets the fill color of the progress bar.
	*	@param fillColor The color.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|FloatingBarWidget")
	void SetFillColor(FLinearColor fillColor);

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float inDeltaTime) override;

private:
	UPROPERTY() UProgressBar* floatingBar;
	UPROPERTY() UTextBlock* hpLabel;
	UPROPERTY() AActor* followTarget;
	UPROPERTY() FVector offset;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;

	void SetOpacity(float opacity);
};
