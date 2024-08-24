#ifndef SETTINGS_KEY_H
#define SETTINGS_KEY_H

/* ****************************************************************************
 * File:    settings_key.h
 * Author:  Chumakov Anton I.
 * Purpose: Keys of settings
 * Date:    July 21, 2024
 *************************************************************************** */

// Keys of the INI
namespace ini_system {
    const char ini_file[]       = "settings.ini";
    const char dictionary_path[]= "system/dictionary_path";
    const char sound_path[]     = "system/sound_path";
    const char dictionary[]     = "system/dictionary";
    const char count_to_done[]  = "system/count_to_done";
    const char to_learn[]       = "system/to_learn";
}

// XML-tags of a dictionary
namespace XML_DICT {
    const char TAG_DICTIONARY[] = "dictionary";
    const char TAG_ID[]         = "id";
    const char TAG_SOUND[]      = "sound";
    const char TAG_TEXT[]       = "text";
    const char TAG_FORM1[]      = "form1";
    const char TAG_FORM2[]      = "form2";
    const char TAG_FORM3[]      = "form3";
    const char TAG_TRANSLATION[]= "translation";
    const char TAG_EXAMPLE[]    = "example";
    const char TAG_STATISTICS[] = "statistics";
    const char TAG_STATUS[]     = "status";
}

#endif // SETTINGS_KEY_H
