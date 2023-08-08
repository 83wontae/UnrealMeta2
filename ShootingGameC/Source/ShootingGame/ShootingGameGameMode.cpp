// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingGameGameMode.h"
#include "ShootingGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootingGameGameMode::AShootingGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AShootingGameGameMode::CreateOnlineSession()
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

        if (SessionInterface.IsValid())
        {
            FOnlineSessionSettings SessionSettings;
            SessionSettings.NumPublicConnections = 4; // Maximum number of players in the session.
            SessionSettings.bShouldAdvertise = true; // Allow the session to be advertised.
            SessionSettings.bAllowJoinInProgress = true; // Allow players to join a game in progress.
            SessionSettings.bIsLANMatch = false; // Set to true for LAN games, false for online.

            TSharedPtr<const FUniqueNetId> UserId = OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0);
            SessionInterface->CreateSession(*UserId, GameSessionName, SessionSettings);
        }
    }
}

void AShootingGameGameMode::FindOnlineSessions()
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

        if (SessionInterface.IsValid())
        {
            TSharedPtr<class FOnlineSessionSearch> SessionSearch;
            SessionSearch = MakeShareable(new FOnlineSessionSearch());

            SessionSearch->bIsLanQuery = true;
            SessionSearch->MaxSearchResults = 20;
            SessionSearch->PingBucketSize = 50;

            TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

            // Start the search for sessions.
            TSharedPtr<const FUniqueNetId> UserId = OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0);
            SessionInterface->FindSessions(*UserId, SearchSettingsRef);
        }
    }
}
