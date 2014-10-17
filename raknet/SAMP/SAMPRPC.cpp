#include "main.h"

int RPC_ServerJoin = 137;
int RPC_ServerQuit = 138;
int RPC_InitGame = 139;
int RPC_ClientJoin = 25;
int RPC_NPCJoin = 54;
int RPC_Death = 53;
int RPC_RequestClass = 128;
int RPC_RequestSpawn = 129;
int RPC_SetInteriorId = 118;
int RPC_Spawn = 52;
int RPC_Chat = 101;
int RPC_EnterVehicle = 26;
int RPC_ExitVehicle = 154;
int RPC_DamageVehicle = 106;
int RPC_MenuSelect = 132;
int RPC_MenuQuit = 140;
int RPC_ScmEvent = 96;
int RPC_AdminMapTeleport = 255;
int RPC_WorldPlayerAdd = 32;
int RPC_WorldPlayerDeath = 166;
int RPC_WorldPlayerRemove = 163;
int RPC_WorldVehicleAdd = 164;
int RPC_WorldVehicleRemove = 165;
int RPC_SetCheckpoint = 107;
int RPC_DisableCheckpoint = 37;
int RPC_SetRaceCheckpoint = 38;
int RPC_DisableRaceCheckpoint = 39;
int RPC_UpdateScoresPingsIPs = 155;
int RPC_SvrStats = 102;
int RPC_GameModeRestart = 40;
int RPC_ConnectionRejected = 130;
int RPC_ClientMessage = 93;
int RPC_WorldTime = 94;
int RPC_Pickup = 255;
int RPC_DestroyPickup = 255;
int RPC_DestroyWeaponPickup = 255;
int RPC_Weather = 152;
int RPC_SetTimeEx = 255;
int RPC_ToggleClock = 255;
int RPC_ServerCommand = 50;
int RPC_PickedUpPickup = 131;
int RPC_PickedUpWeapon = 255;
int RPC_VehicleDestroyed = 136;
int RPC_DialogResponse = 62;
int RPC_PlayAudioStream = 41;
int RPC_ClickPlayer = 23;
int RPC_PlayerUpdate = 255;
int RPC_ClickTextDraw = 83;
int RPC_MapMarker = 119;
int RPC_PlayerGiveTakeDamage = 115; //bool Give/Take, playerid, amount, weaponid
int RPC_EnterEditObject = 27;
int RPC_EditObject = 117;

int RPC_ScrSetSpawnInfo = 255;
int RPC_ScrSetPlayerTeam = 255;
int RPC_ScrSetPlayerSkin = 255;
int RPC_ScrSetPlayerName = 255;
int RPC_ScrSetPlayerPos = 255;
int RPC_ScrSetPlayerPosFindZ = 255;
int RPC_ScrSetPlayerHealth = 255;
int RPC_ScrPutPlayerInVehicle = 255;
int RPC_ScrRemovePlayerFromVehicle = 255;
int RPC_ScrSetPlayerColor = 255;
int RPC_ScrDisplayGameText = 73;
int RPC_ScrSetInterior = 255;
int RPC_ScrSetCameraPos = 255;
int RPC_ScrSetCameraLookAt = 255;
int RPC_ScrSetVehiclePos = 255;
int RPC_ScrSetVehicleZAngle = 255;
int RPC_ScrVehicleParams = 255;
int RPC_ScrSetCameraBehindPlayer = 255;
int RPC_ScrTogglePlayerControllable = 255;
int RPC_ScrPlaySound = 255;
int RPC_ScrSetWorldBounds = 255;
int RPC_ScrHaveSomeMoney = 255;
int RPC_ScrSetPlayerFacingAngle = 255;
int RPC_ScrResetMoney = 255;
int RPC_ScrResetPlayerWeapons = 255;
int RPC_ScrGivePlayerWeapon = 255;
int RPC_ScrRespawnVehicle = 255;
int RPC_ScrLinkVehicle = 255;
int RPC_ScrSetPlayerArmour = 255;
int RPC_ScrDeathMessage = 255;
int RPC_ScrSetMapIcon = 255;
int RPC_ScrDisableMapIcon = 255;
int RPC_ScrSetWeaponAmmo = 255;
int RPC_ScrSetGravity = 255;
int RPC_ScrSetVehicleHealth = 255;
int RPC_ScrAttachTrailerToVehicle = 255;
int RPC_ScrDetachTrailerFromVehicle = 255;
int RPC_ScrCreateObject = 255;
int RPC_ScrSetObjectPos = 255;
int RPC_ScrSetObjectRotation = 255;
int RPC_ScrDestroyObject = 255;
int RPC_ScrCreateExplosion = 255;
int RPC_ScrShowNameTag = 255;
int RPC_ScrMoveObject = 255;
int RPC_ScrStopObject = 255;
int RPC_ScrNumberPlate = 255;
int RPC_ScrTogglePlayerSpectating = 255;
int RPC_ScrSetPlayerSpectating = 255;
int RPC_ScrPlayerSpectatePlayer = 255;
int RPC_ScrPlayerSpectateVehicle = 255;
int RPC_ScrRemoveComponent = 255;
int RPC_ScrForceSpawnSelection = 255;
int RPC_ScrAttachObjectToPlayer = 255;
int RPC_ScrInitMenu = 76;
int RPC_ScrShowMenu = 77;
int RPC_ScrHideMenu = 78;
int RPC_ScrSetPlayerWantedLevel = 255;
int RPC_ScrShowTextDraw = 134;
int RPC_ScrHideTextDraw = 255;
int RPC_ScrEditTextDraw = 255;
int RPC_ScrAddGangZone = 255;
int RPC_ScrRemoveGangZone = 255;
int RPC_ScrFlashGangZone = 255;
int RPC_ScrStopFlashGangZone = 255;
int RPC_ScrApplyAnimation = 255;
int RPC_ScrClearAnimations = 255;
int RPC_ScrSetSpecialAction = 255;
int RPC_ScrEnableStuntBonus = 255;
int RPC_ScrSetFightingStyle = 255;
int RPC_ScrSetPlayerVelocity = 255;
int RPC_ScrSetVehicleVelocity = 255;
int RPC_ScrToggleWidescreen = 255;
int RPC_ScrSetVehicleTireStatus = 255;
int RPC_ScrSetPlayerDrunkVisuals = 255;
int RPC_ScrSetPlayerDrunkHandling = 255;
int RPC_ScrDialogBox = 61;

//TODO: Give/Take damage func, ClickPlayer, ClickTextdraw, Menu