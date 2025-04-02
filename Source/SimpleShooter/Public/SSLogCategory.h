#pragma once

#define SS_LOG(LogCategory, LogVerbosity, Format, ...) \
	UE_LOG(LogCategory, LogVerbosity, TEXT("[%s] " Format), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)

static void LogOnScreen(const UObject* WorldContext, const FString& Msg, const FColor Color = FColor::White, const float Duration = 5.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	const UWorld* World = WorldContext->GetWorld();
	if (!ensure(World))
	{
		return;
	}

	const FString NetPrefix = World->IsNetMode(NM_Client) ? "[CLIENT]" : "[SERVER]";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPrefix + Msg);
	}
}

DECLARE_LOG_CATEGORY_EXTERN(LogSSAction, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(LogSSBaseProjectile, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(LogSSHUD, Log, All);
