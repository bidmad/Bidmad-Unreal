// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EBidmadTrackingAuthorizationStatus : uint8
{
	BidmadAuthorizationStatusNotDetermined = 0   UMETA(DisplayName = "BidmadAuthorizationStatusNotDetermined"),
	BidmadAuthorizationStatusRestricted			UMETA(DisplayName = "BidmadAuthorizationStatusRestricted"),
	BidmadAuthorizationStatusDenied		UMETA(DisplayName = "BidmadAuthorizationStatusDenied"),
	BidmadAuthorizationStatusAuthorized		UMETA(DisplayName = "BidmadAuthorizationStatusAuthorized"),
	BidmadAuthorizationStatusLessThaniOS14		UMETA(DisplayName = "BidmadAuthorizationStatusLessThaniOS14")
};