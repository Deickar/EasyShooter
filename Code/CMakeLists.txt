cmake_minimum_required (VERSION 3.6.0)
project (Game VERSION 1.0 LANGUAGES CXX)

if (${CMAKE_GENERATOR} MATCHES "^Visual Studio")
	ADD_DEFINITIONS("/ZI")
	# Set startup project to launch Game.exe with this project
	configure_file ("Game.vcxproj.user.in" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

find_package (CryCommon REQUIRED)
find_package (CryAction REQUIRED)

option(OPTION_PCH "Enable Precompiled headers" ON)

# Main
set (SourceGroup_PluginMain
	"StdAfx.cpp"
	"StdAfx.h"
	"GamePlugin.cpp"
	"GamePlugin.h"
	"PluginENV.h"
)
source_group("Main" FILES ${SourceGroup_PluginMain})

# Game
set (SourceGroup_Game
	"Game/GameRules.cpp"
	"Game/GameRules.h"
)
source_group("Game" FILES ${SourceGroup_Game})

# Weapon entities
set (SourceGroup_WeaponEntities
	"Entities/Gameplay/Weapons/Bullet.cpp"
	"Entities/Gameplay/Weapons/Bullet.h"
	"Entities/Gameplay/Weapons/ISimpleWeapon.h"
	"Entities/Gameplay/Weapons/Rifle.cpp"
	"Entities/Gameplay/Weapons/Rifle.h"
)
source_group("Entities\\Gameplay\\Weapons" FILES ${SourceGroup_WeaponEntities})

# Gameplay entities
set (SourceGroup_GameplayEntities
	"Entities/Gameplay/SpawnPoint.cpp"
	"Entities/Gameplay/SpawnPoint.h"
	"Entities/Gameplay/Lift.cpp"
	"Entities/Gameplay/Lift.h"
)
source_group("Entities\\Gameplay" FILES ${SourceGroup_GameplayEntities})

# Entity helpers
set (SourceGroup_EntityHelpers
	"Entities/Helpers/ISimpleExtension.h"
)
source_group("Entities\\Helpers" FILES ${SourceGroup_EntityHelpers})

# Player
set (SourceGroup_Player
	"Player/Player.cpp"
	"Player/Player.h"
	"Player/ISimpleActor.h"
)
source_group("Player" FILES ${SourceGroup_Player})

# Player animation
set (SourceGroup_PlayerAnimations
	"Player/Animations/PlayerAnimations.cpp"
	"Player/Animations/PlayerAnimations.h"
)
source_group("Player\\Animations" FILES ${SourceGroup_PlayerAnimations})

# Player input
set (SourceGroup_PlayerInput
	"Player/Input/PlayerInput.cpp"
	"Player/Input/PlayerInput.h"
)
source_group("Player\\Input" FILES ${SourceGroup_PlayerInput})

# Player movement
set (SourceGroup_PlayerMovement
	"Player/Movement/PlayerMovement.cpp"
	"Player/Movement/PlayerMovement.h"
)
source_group("Player\\Movement" FILES ${SourceGroup_PlayerMovement})

# Player view
set (SourceGroup_PlayerView
	"Player/View/PlayerView.cpp"
	"Player/View/PlayerView.h"
)
source_group("Player\\View" FILES ${SourceGroup_PlayerView})

# FlowNodes
set (SourceGroup_FlowNodes
	"FlowNodes/FlowNodesGame.cpp"
)
source_group("FlowNodes" FILES ${SourceGroup_FlowNodes})

# UI
set (SourceGroup_UI
	"UI/UIManager.cpp"
	"UI/UIManager.h"
	"UI/IUIPage.h"
)
source_group("UI" FILES ${SourceGroup_UI})

# Menu
set (SourceGroup_UI_Menu
	"UI/Menu/PageAuthorization.cpp"
	"UI/Menu/PageAuthorization.h"
	"UI/Menu/PageInGame.cpp"
	"UI/Menu/PageInGame.h"
	"UI/Menu/PageLoading.cpp"
	"UI/Menu/PageLoading.h"
	"UI/Menu/PageLoadout.cpp"
	"UI/Menu/PageLoadout.h"
	"UI/Menu/PageMain.cpp"
	"UI/Menu/PageMain.h"
	"UI/Menu/PageProfile.cpp"
	"UI/Menu/PageProfile.h"
	"UI/Menu/PageServerSearch.cpp"
	"UI/Menu/PageServerSearch.h"
	"UI/Menu/PageSettings.cpp"
	"UI/Menu/PageSettings.h"
	"UI/Menu/PageShop.cpp"
	"UI/Menu/PageShop.h"
	"UI/Menu/PageError.cpp"
	"UI/Menu/PageError.h"
)
source_group("UI\\Menu" FILES ${SourceGroup_UI_Menu})

# HUD
set (SourceGroup_UI_HUD
	"UI/HUD/PageHUD.cpp"
	"UI/HUD/PageHUD.h"
)
source_group("UI\\HUD" FILES ${SourceGroup_UI_HUD})

set (SOURCE
	${SourceGroup_PluginMain}
	${SourceGroup_Game}
	${SourceGroup_WeaponEntities}
	${SourceGroup_GameplayEntities}
	${SourceGroup_EntityHelpers}
	${SourceGroup_Player}
	${SourceGroup_PlayerAnimations}
	${SourceGroup_PlayerInput}
	${SourceGroup_PlayerMovement}
	${SourceGroup_PlayerView}
	${SourceGroup_FlowNodes}
	${SourceGroup_UI}
	${SourceGroup_UI_Menu}
	${SourceGroup_UI_HUD}
)

if(OPTION_PCH AND MSVC)	
	set (PRECOMPILED_SOURCE ${SOURCE})
	list(REMOVE_ITEM PRECOMPILED_SOURCE "StdAfx.cpp")
	set (PRECOMPILED_BINARY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pch)
	set_source_files_properties (${PRECOMPILED_SOURCE} PROPERTIES COMPILE_FLAGS "/Yu\"StdAfx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_DEPENDS "${PRECOMPILED_BINARY}")
	set_source_files_properties (StdAfx.cpp PROPERTIES COMPILE_FLAGS "/Yc\"StdAfx.h\" /Fp\"${PRECOMPILED_BINARY}\"" OBJECT_OUTPUTS "${PRECOMPILED_BINARY}")
endif (OPTION_PCH AND MSVC)

add_library(${PROJECT_NAME} MODULE ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# FireNet includes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/FireNet)
target_link_libraries(${PROJECT_NAME} PRIVATE CryCommon CryAction)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE Ntdll)
endif(WIN32)
