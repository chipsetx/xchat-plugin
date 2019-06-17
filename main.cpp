// ---------------------------------
// Copyright (c) 2016 Jens Kallup
// Alle Rechte Vorbehalten!
// ---------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "xchat-plugin.h"

#include <iostream>
using namespace std;

static xchat_plugin *ph;  // plugin handle

static const char* get_user(void)
{
    return xchat_get_info(ph,"nick");
}

static int get_help(char *word[], char **word_eol, void *userdata)
{
    std::string msg = "konnte ich helfen?'";

    if (!(strcmp(word[1],"hlp")))
    {
        if (strlen(word[2]) < 1)
        xchat_printf(ph,">\tAnwendung: /help <Frage>");
        else {
            if (!(strcmp(word[2],"garnicht")))
            {
                xchat_command(ph,"SAY das ist leider schade!");
            } else {
                std::string str = "SAY ";
                msg  = "Guten Tag: ";
                msg += get_user();
                msg += "\nWomit kann ich Ihnen helfen?\n\n";

                msg += "leider konnte ich keine passenden Informationen finden.\n"
                       "wie möchten Sie/Du angesprochen werden?";
                str += msg;
                xchat_command(ph,str.c_str());
            }
        }
    }
    return XCHAT_EAT_ALL;
}

extern "C" int xchat_plugin_init(xchat_plugin *plugin_handle,
                      char **plugin_name,
                      char **plugin_desc,
                      char **plugin_version,
                      char  *arg)
{
    ph = plugin_handle;
    *plugin_name = "dBase4Linux";
    *plugin_desc = "kleiner Versuch einer automatisierten Wissensdatenbank.";
    *plugin_version = "0.1";

    xchat_hook_command(
        ph,
        "hlp",
	XCHAT_PRI_NORM,
	get_help,"/pc hallo" ,
	0);

    //xchat_hook_timer(ph, 5000, timeout_cb, 0);

    return 1;
}
