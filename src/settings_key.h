#ifndef SETTINGS_KEY_H
#define SETTINGS_KEY_H

/* ****************************************************************************
 * File:    settings_key.h
 * Author:  Chumakov Anton I.
 * Purpose: Keys of settings
 * Date:    July 21, 2024
 *************************************************************************** */

// #define SYSTEM__DICTIONARY_PATH "system/dictionary_path"
// The C++-style of constants is better than like-C defines
namespace ini_system {
    const char ini_file[] = "settings.ini";
    const char dictionary_path[] = "system/dictionary_path";
    const char sound_path[] = "system/sound_path";
    const char dictionary[] = "system/dictionary";
    const char count_to_done[] = "system/count_to_done";
    const char to_learn[] = "system/to_learn";
}

#endif // SETTINGS_KEY_H
