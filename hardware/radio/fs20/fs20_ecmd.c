/*
 *
 * Copyright (c) by Alexander Neumann <alexander@bumpern.de>
 * Copyright (c) 2007 by Stefan Siegl <stesie@brokenpipe.de>
 * Copyright (c) 2007 by Christian Dietrich <stettberger@dokucode.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (either version 2 or
 * version 3) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <string.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "core/bit-macros.h"
#include "core/debug.h"
#include "hardware/radio/fs20/fs20.h"

#include "protocols/ecmd/ecmd-base.h"


#ifdef FS20_SEND_SUPPORT
int16_t parse_cmd_fs20_send(char *cmd, char *output, uint16_t len)
{
#ifdef DEBUG_ECMD_FS20
    debug_printf("called with string %s\n", cmd);
#endif

    uint16_t hc, addr, c;

    int ret = sscanf_P(cmd,
            PSTR("%x %x %x"),
            &hc, &addr, &c);

    if (ret == 3) {
#ifdef DEBUG_ECMD_FS20
        debug_printf("fs20_send(0x%x,0x%x,0x%x)\n", hc, LO8(addr), LO8(c));
#endif

        fs20_send(hc, LO8(addr), LO8(c));
        return ECMD_FINAL_OK;
    }

    return ECMD_ERR_PARSE_ERROR;

}
#endif /* FS20_SEND_SUPPORT */


#ifdef FS20_RECEIVE_SUPPORT
int16_t parse_cmd_fs20_receive(char *cmd, char *output, uint16_t len)
{
    char *s = output;
    uint8_t l = 0;
    uint8_t outlen = 0;

#ifdef DEBUG_ECMD_FS20
    debug_printf("%u positions in queue\n", fs20_global.fs20.len);
#endif

    while (l < fs20_global.fs20.len &&
            (uint8_t)(outlen+11) < len) {
#ifdef DEBUG_ECMD_FS20
        debug_printf("generating for pos %u: %02x%02x%02x%02x%02x", l,
                fs20_global.fs20.queue[l].hc1,
                fs20_global.fs20.queue[l].hc2,
                fs20_global.fs20.queue[l].addr,
                fs20_global.fs20.queue[l].cmd,
				fs20_global.fs20.queue[l].ext);
#endif

        sprintf_P(s, PSTR("%02x%02x%02x%02x%02x\n"),
                fs20_global.fs20.queue[l].hc1,
                fs20_global.fs20.queue[l].hc2,
                fs20_global.fs20.queue[l].addr,
                fs20_global.fs20.queue[l].cmd,
				fs20_global.fs20.queue[l].ext);

        s += 11;
        outlen += 11;
        l++;

#ifdef DEBUG_ECMD_FS20
        *s = '\0';
        debug_printf("output is \"%s\"\n", output);
#endif
    }

    /* clear queue */
    fs20_global.fs20.len = 0;

    return ECMD_FINAL(outlen);
}

#ifdef FS20_RECEIVE_WS300_SUPPORT
int16_t parse_cmd_fs20_ws300(char *cmd, char *output, uint16_t len)
{

    return ECMD_FINAL(snprintf_P(output, len,
	
            PSTR("%u.%u deg, %u%% hygro, %u.%u km/h wind, rain: %u count %u"),
            fs20_global.ws300.temp,
            fs20_global.ws300.temp_frac,
            fs20_global.ws300.hygro,
            fs20_global.ws300.wind,
            fs20_global.ws300.wind_frac,
            fs20_global.ws300.rain,
            fs20_global.ws300.rain_value));

}
#endif /* FS20_RECEIVE_WS300_SUPPORT */
#endif /* FS20_RECEIVE_SUPPORT */
