#pragma once

#include "Aimbot\EnginePrediction.h"
#include "Visuals\ESP.h"
#include "Misc\Misc.h"
#include "Resolver\Resolver.h"
#include "AntiAim\AntiAim.h"
#include "Aimbot\Aimbot.h"
#include "Visuals/Nightmode.h"
#include "Legit/LegitAimbot.h"
#include "Visuals/GlowEsp.h"

// Remastered Stuff
#include "Visuals/RemasteredEsp.h"

// http://rgho.st/download/6jjQ6H5JT/a11c5d329f77659ecda6bb7c401a56cf68668b0a/a11c5d329f77659ecda6bb7c401a56cf68668b0a/i%20get%20out.zip

// there is a shit ton of usefull stuff we could paste in but most of the shit does some wierd stuuf i cant fix lol



// fake media

// spread cross hair

//bullet racers

// offscreen esp


//teaser range

//knife changer

// on player hitmarker

/*
void c_animfix::re_work( client_frame_stage_t stage ) {

    if ( !local_player || !local_player->get_anim_state( ) )
        return;

    if ( stage == client_frame_stage_t::frame_render_start )
        local_player->set_abs_angles( vec_t( 0.f, local_player->get_anim_state( )->goal_feet_yaw, 0.f ) );


    for ( int i = 1; i <= globals->max_clients; i++ ) {
        c_baseentity * entity = ( c_baseentity* ) entity_list->get_client_entity( i );

        if ( !entity->is_valid_player( ) )
            continue;


        static auto set_interpolation_flags = [ ] ( c_baseentity* e, int flag ) {
            const auto var_map = ( uintptr_t ) e + 36;
            const auto sz_var_map = *( int* ) ( var_map + 20 );

            for ( auto index = 0; index < sz_var_map; index++ )
                *( uintptr_t* ) ( ( *( uintptr_t* ) var_map ) + index * 12 ) = flag;
        };

        if ( stage == client_frame_stage_t::frame_net_update_postdataupdate_end )
            set_interpolation_flags( entity, 0 );


    }
}
void c_animfix::fix_local_player_animations( )
{
    if ( !local_player )
        return;

    static float sim_time;
    if ( sim_time != local_player->get_simulation_time( ) )
    {
        auto state = local_player->get_anim_state( ); if ( !state ) return;

        const float curtime = globals->curtime;
        const float frametime = globals->frametime;
        const float realtime = globals->real_time;
        const float absoluteframetime = globals->absolute_frametime;
        const float absoluteframestarttimestddev = globals->absolute_frame_start_time;
        const float interpolation_amount = globals->interpolation_amount;
        const float framecount = globals->frame_count;
        const float tickcount = globals->tickcount;

        static auto host_timescale = cvar->find_var( ( "host_timescale" ) );

        globals->curtime = local_player->get_simulation_time( );
        globals->real_time = local_player->get_simulation_time( );
        globals->frametime = globals->interval_per_tick * host_timescale->get_float( );
        globals->absolute_frametime = globals->interval_per_tick * host_timescale->get_float( );
        globals->absolute_frame_start_time = local_player->get_simulation_time( ) - globals->interval_per_tick * host_timescale->get_float( );
        globals->interpolation_amount = 0;
        globals->frame_count = time_to_ticks( local_player->get_simulation_time( ) );
        globals->tickcount = time_to_ticks( local_player->get_simulation_time( ) );

        int backup_flags = local_player->get_flags( );
        int backup_eflags = local_player->get_eflags( );

        animationlayer backup_layers [ 15 ];
        std::memcpy( backup_layers, local_player->get_anim_overlays( ), ( sizeof( animationlayer ) * 15 ) );

        if ( state->last_client_side_animation_update_framecount == globals->frame_count )
            state->last_client_side_animation_update_framecount = globals->frame_count - 1;

        local_player->get_clientside_animation( ) = true;
        local_player->update_clientside_animation( );
        local_player->get_clientside_animation( ) = false;


        float lby_delta = local_player->get_lby( ) - thirdperson->thirdperson_angle.y;
        lby_delta = std::remainderf( lby_delta, 360.f );
        lby_delta = std::clamp( lby_delta, -60.f, 60.f );

        float feet_yaw = std::remainderf( thirdperson->thirdperson_angle.y + lby_delta, 360.f );

        if ( feet_yaw < 0.f ) {
            feet_yaw += 360.f;
        }


        std::memcpy( local_player->get_anim_overlays( ), backup_layers, ( sizeof( animationlayer ) * 15 ) );

        c_config::get( ).dev.animstate [ local_player->get_index( ) ] = local_player->get_anim_state( );
        local_player->get_flags( ) = backup_flags;
        local_player->get_eflags( ) = backup_eflags;


        globals->curtime = curtime;
        globals->real_time = realtime;
        globals->frametime = frametime;
        globals->absolute_frametime = absoluteframetime;
        globals->absolute_frame_start_time = absoluteframestarttimestddev;
        globals->interpolation_amount = interpolation_amount;
        globals->frame_count = framecount;
        globals->tickcount = tickcount;
        sim_time = local_player->get_simulation_time( );
    }
    local_player->invalidate_bone_cache( );
    local_player->setup_bones( nullptr, -1, 0x7FF00, globals->curtime );
}

void c_animfix::update_animations( c_baseentity* entity )  thx to xsharcs
{
auto state = entity->get_anim_state(); if (!state) return;
auto index = entity->get_index();
static float sim_time[65];

if (sim_time[index] != entity->get_simulation_time())
{
	const float curtime = globals->curtime;
	const float frametime = globals->frametime;
	static auto host_timescale = cvar->find_var(("host_timescale"));

	globals->frametime = globals->interval_per_tick * host_timescale->get_float();
	globals->curtime = entity->get_simulation_time() + globals->interval_per_tick;

	vec_t backup_velocity = entity->get_velocity();

	int backup_flags = entity->get_flags();
	int backup_eflags = entity->get_eflags();

	animationlayer backup_layers[15];
	std::memcpy(backup_layers, entity->get_anim_overlays(), (sizeof(animationlayer) * 15));

	state->on_ground ? entity->get_flags() |= (1 << 0) : entity->get_flags() &= ~(1 << 0);

	entity->get_eflags() &= ~0x1000;

	entity->get_abs_velocity() = entity->get_velocity();
	entity->get_abs_velocity2() = entity->get_velocity();
	entity->unkpasted() = 0x1;

	if (state->last_client_side_animation_update_framecount == globals->frame_count)
		state->last_client_side_animation_update_framecount = globals->frame_count - 1;

	entity->update_clientside_animation();

	float lby_delta = entity->get_lby() - entity->get_eyeangles().y;
	lby_delta = std::remainderf(lby_delta, 360.f);
	lby_delta = std::clamp(lby_delta, -60.f, 60.f);

	float feet_yaw = std::remainderf(entity->get_eyeangles().y + lby_delta, 360.f);

	if (feet_yaw < 0.f) {
		feet_yaw += 360.f;
	}

	static float pitch, yaw = 0.f;

	entity->get_anim_state()->goal_feet_yaw = entity->get_anim_state()->current_feet_yaw = feet_yaw;

	entity->get_anim_state()->eye_angles_y = entity->get_anim_state()->body_yaw = resolver->data[entity->get_index()].final_angle;

	std::memcpy(entity->get_anim_overlays(), backup_layers, (sizeof(animationlayer) * 15));

	entity->get_velocity() = backup_velocity;
	entity->get_flags() = backup_flags;
	entity->get_eflags() = backup_eflags;

	globals->curtime = curtime;
	globals->frametime = frametime;
	sim_time[index] = entity->get_simulation_time();
}

entity->invalidate_bone_cache();
entity->setup_bones(nullptr, -1, 0x7FF00, globals->curtime);
}*/