/*
 *
 *          fs20 sender/receiver implementation
 *
 * (c) by Alexander Neumann <alexander@bumpern.de>
 *        2009, Torsten Schumacher <tosch@schopl.de>
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


#ifndef _FS20_H
#define _FS20_H

#include "config.h"

#ifdef FS20_SUPPORT

#if !defined(F_CPU)
#error "F_CPU undefined!"
#endif

/*
	FS20 and FHT on the air protokoll is described here
	http://fhz4linux.info/tiki-index.php?page=FS20+Protocol
	http://fhz4linux.info/tiki-index.php?page=FHT+protocol
	
	In short
	A logical "0" is a pulse 400us on, 400 us off
	A logical "1" is a pulse 600us on, 600 us off
	All bytes are secured by an even parity bit
	A datagram consists of a starting sequence of 12 * "0" followed by a "1"
	Then follows
		houscode high byte
		housecode low byte
		address byte
		command byte
		optional extension byte (if bit 5 of command byte is set)
		checksum byte
	The checksum is 8bit sum of all bytes plus
		0x06 for FS20
		0x0c for FHT

*/

/* ws300 datagram description:
 *
 * See also
 * http://www.dc3yc.homepage.t-online.de/protocol.htm
 *
 * Signal:
 *
 *    +-------+   +---+       +----
 *    |       |   |   |       |
 *  --+       +---+   +-------+
 *    |  "0" wave |  "1" wave |   
 *
 * 
 * long pulse: 90 <= t <= 180
 *
 * Experiments have shown, that the encoding for a logical "0" is a long high
 * pulse, followed by a short low pulse and a logical "1" is a short high
 * pulse, followed by a long low pulse.
 *
 * wave period is 1220 ms
 * logic 0 is 7:3 logic 1 is 3:7 wave
 *
 * The datagram is started by sending 8-10 zeroes, followed by a "1".  After
 * that, 16 nibbles (= 4 bit, BCD) of data (LSB first) are sent, divided by
 * exactly one "1".
 *
 * As far as we were able to figure it out for the WS300-2, the meaning is:
 *
 * nibble | meaning
 * ================
 *      1 | constant 1110 (bin, LSB first) == 7 (dec), perhaps sensor type?
 *      2 | 1W0T (bin, LSB first),
 *        | W is set if water is detected, (bit 1)
 *        | T is temperature sign bit (set if temperature is negative (bit 3)
 *      3 | temperature fraction part
 *      4 | temperature decimal place 1
 *      5 | temperature decimal place 10
 *      6 | hygrometer decimal place 1
 *      7 | hygrometer decimal place 10
 *      8 | wind strength fraction part
 *      9 | wind strength decimal place 1
 *     10 | wind strength decimal place 10
 *     11 | rain counter decimal place 1
 *     12 | rain counter decimal place 10
 *     13 | rain counter decimal place 100
 *     14 | unknown, seems to be some sort of checksum?
 *     15 | XOR checksum (XOR every nibble up to and including nibble 15,
 *        | if correct, | the result is zero)
 *     16 | checksum, this is: (sum of nibbles 1 to 15) & 0x0F + 5
 *        | (the lower 4 bit of the sum of the value of all nibbles 1 to 15, plus 5)
 *
 *
 * The datagram is terminated by an additional "1", but this is not always received.
 * A datagram consists of 80 bit, including the last "1".
 *
 *
 */


/* FS20 send definitions */

#define FS20_DELAY_ZERO (4 * (F_CPU / 10000) / 4) /* 400uS, for delay_loop_2 */
#define FS20_DELAY_ONE  (6 * (F_CPU / 10000) / 4) /* 600uS, for delay_loop_2 */
#define FS20_DELAY_CMD  ( F_CPU / 100 / 4) /* 10ms, for delay_loop_2 */

/* FS20 read definitions */

/* FS20 read routines use timer 0 with prescaler 256 */

#define FS20_PRESCALER 256

#define FS20_US2T(x) (int)(F_CPU/1000000*(x)/FS20_PRESCALER)
#define FS20_BETWEEN(x, a, b) ((x >= FS20_US2T(a)) && (x <= FS20_US2T(b)))
#define FS20_SYMM(x, y, r) ( (x-y) <= FS20_US2T(r) && (y-x) <= FS20_US2T(r) )

/* zero is 400uS: accept everything between 300us and 500us */
#define FS20_PULSE_ZERO(x) FS20_BETWEEN((x), 300, 500)
/* one is 600uS: accept any pulse between 500us and 700us */
#define FS20_PULSE_ONE(x) FS20_BETWEEN((x), 500, 700)
/* maximum allowed difference between two pulses is 100 uS */
#define FS20_PULSE_DIFFERENCE(x,y) FS20_SYMM(x, y, 100)


/* ws300 timing: */

/* one is a short pulse, followed by a long pulse */
#define WS300_PULSE_ONE(x,y)  (FS20_BETWEEN((x), 244, 488) && FS20_BETWEEN((y), 732, 976))
/* zero is a long pulse, followed by a short pulse */
#define WS300_PULSE_ZERO(x,y) (FS20_BETWEEN((x), 732, 976) && FS20_BETWEEN((y), 244, 488))

/* test if the received value might be a valid ws300 timing */
#define WS300_VALID_VALUE(x) FS20_BETWEEN((x), 244, 976)
/* test if two adjacent timings might be a valid ws300 timing */
#define WS300_VALID_VALUES(x, y) FS20_BETWEEN((x)+(y), 976, 1464)


/* a fs20 datagram consists of 45 or 54 bits */
#define FS20_DATAGRAM_LENGTH 54

/* a ws300 datagram consists of 79 = 16*4+15 bits */
#define FS20_WS300_DATAGRAM_LENGTH 79


#define FS20_WS300_CONSTANT 7

#define FS20_WS300_FLAG_WATER 1
#define FS20_WS300_FLAG_TEMP 3


/* queue length */
#define FS20_QUEUE_LENGTH 4

/* structures */
struct fs20_datagram_t {
    uint8_t p6:1;
    uint8_t checksum:8;
	uint8_t p5:1;
	uint8_t ext:8;
    uint8_t p4:1;
    uint8_t cmd:8;
    uint8_t p3:1;
    uint8_t addr:8;
    uint8_t p2:1;
    uint8_t hc2:8;
    uint8_t p1:1;
    uint8_t hc1:8;
};

struct fs20_command_t {
	char	type;
	uint8_t	hc1;
	uint8_t hc2;
	uint8_t	addr;
	uint8_t	cmd;
	uint8_t ext;
};

struct ws300_datagram_t {
    uint8_t constant:4;
    uint8_t p1:1;
    uint8_t flags:4;
    uint8_t p2:1;
    uint8_t temp1:4;
    uint8_t p3:1;
    uint8_t temp2:4;
    uint8_t p4:1;
    uint8_t temp3:4;
    uint8_t p5:1;
    uint8_t hygro1:4;
    uint8_t p6:1;
    uint8_t hygro2:4;
    uint8_t p7:1;
    uint8_t wind1:4;
    uint8_t p8:1;
    uint8_t wind2:4;
    uint8_t p9:1;
    uint8_t wind3:4;
    uint8_t p10:1;
    uint8_t raincounter1:4;
    uint8_t p11:1;
    uint8_t raincounter2:4;
    uint8_t p12:1;
    uint8_t raincounter3:4;
    uint8_t p13:1;
    uint8_t unknown:4;
    uint8_t p14:1;
    uint8_t checksum1:4;
    uint8_t p15:1;
    uint8_t checksum2:4;
    uint8_t p16:1;
};

struct fs20_global_t {
    uint8_t enable;
    #ifdef FS20_RECEIVE_SUPPORT
        struct {
            union {
                struct fs20_datagram_t datagram;
                uint64_t raw;
                uint16_t words[4];
            };
            uint8_t sync:1;   /* sync preamble n*"0" + "1" received */
			uint8_t start:1;  /* expecting first rising edge */
            uint8_t null:6;   /* number of preamble "0"s received */
            uint8_t rec;      /* number of datagram bits received */
            uint8_t err;      /* number of too long/short pulses received */
            uint8_t timeout;  /* counter for death period after successfull reception */
			/* the FS20 receive queue */
            struct fs20_command_t queue[FS20_QUEUE_LENGTH];
            uint8_t len;      
        } fs20;
		#ifdef FS20_RECEIVE_WS300_SUPPORT
			/* same structure for ws300 reception */
			struct {
				union {
					struct ws300_datagram_t datagram;
					uint8_t bytes[10];
				};
				uint8_t sync:1;
				uint8_t start:1;
				uint8_t null:6;
				uint8_t rec;
				uint8_t err;

				/* the received WS300 decoded data */
				int8_t temp;
				uint8_t temp_frac:4;

				uint8_t rain:1;
				uint16_t rain_value;

				uint8_t hygro;

				uint8_t wind;
				uint8_t wind_frac:4;

				uint16_t last_update; /* seconds since ... */
			} ws300;
		#endif
    #endif
    #ifdef FS20_RECV_PROFILE
        uint16_t int_counter;
        uint16_t ovf_counter;
    #endif
};

/* global variables */
extern volatile struct fs20_global_t fs20_global;

/* public prototypes */
void fs20_init(void);

#ifdef FS20_SEND_SUPPORT
void fs20_send(uint16_t housecode, uint8_t address, uint8_t command);
#endif

#ifdef FS20_RECEIVE_SUPPORT
void fs20_process(void);
void fs20_process_timeout(void);
#else
#define fs20_process()
#define fs20_process_timeout()
#endif

#endif /* FS20_SUPPORT */

#endif /* _FS20_H */
