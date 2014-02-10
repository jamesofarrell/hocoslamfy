/*
 * Hocoslamfy, background rendering code file
 * Copyright (C) 2014 Nebuleon Fumika <nebuleon@gcw-zero.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <math.h>

#include "SDL.h"

#include "main.h"
#include "init.h"
#include "game.h"
#include "bg.h"

// The X coordinates from which the various pieces of the background start to
// be rendered. (In meters.)
static       float    BG_X     [BG_PIECE_COUNT] = {
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f
};
// The speed at which the X coordinate moves, for each piece of the background.
// (In meters per second.)
static const float    BG_Speed [BG_PIECE_COUNT] = {
	BG_SPEED_4, BG_SPEED_3, BG_SPEED_2, BG_SPEED_1,
	BG_SPEED_2, BG_SPEED_3, BG_SPEED_4, BG_SPEED_5
};

// The Y coordinates at which the various pieces of the background start, and
// their heights. (In pixels of the background image.)
static const uint32_t BG_StartY[BG_PIECE_COUNT] = {
	  0,  28,  42,  54,
	192, 200, 210, 222
};
static const uint32_t BG_Height[BG_PIECE_COUNT] = {
	 28,  14,  12, 138,
	  8,  10,  12,  18
};

void AdvanceBackground(uint32_t Milliseconds)
{
	uint32_t i;
	for (i = 0; i < BG_PIECE_COUNT; i++)
	{
		BG_X[i] = fmodf(BG_X[i] + BG_Speed[i] * Milliseconds / 1000, FIELD_WIDTH * 0.5f);
	}
}

void DrawBackground(void)
{
	uint32_t i;
	for (i = 0; i < BG_PIECE_COUNT; i++)
	{
		SDL_Rect SourceRect = {
			.x = (int) (BG_X[i] * SCREEN_WIDTH / FIELD_WIDTH),
			.y = BG_StartY[i],
			.w = SCREEN_WIDTH,
			.h = BG_Height[i] };
		SDL_Rect DestRect = {
			.x = 0,
			.y = BG_StartY[i],
			.w = SCREEN_WIDTH,
			.h = BG_Height[i] };
		SDL_BlitSurface(BackgroundImage, &SourceRect, Screen, &DestRect);
	}
}
