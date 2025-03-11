// Copyright 2024 alex-anisimov (@alex-anisimov)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
#define SOFT_SERIAL_PIN D3
#define SELECT_SOFT_SERIAL_SPEED 2
#define MASTER_RIGHT
#ifndef BOOTMAGIC_LITE_ROW
#    define BOOTMAGIC_LITE_ROW 0
#endif
#ifndef BOOTMAGIC_LITE_COLUMN
#    define BOOTMAGIC_LITE_COLUMN 1
#endif

#ifndef BOOTMAGIC_LITE_ROW_RIGHT
#    define BOOTMAGIC_LITE_ROW_RIGHT 4
#endif
#ifndef BOOTMAGIC_LITE_COLUMN_RIGHT
#    define BOOTMAGIC_LITE_COLUMN_RIGHT 1
#endif
// #define ENCODERS_PAD_A { F4 }
// #define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTIONS { 4 }
#define ENCODER_MAP_KEY_DELAY 10
#define TAPPING_TERM 150
/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
