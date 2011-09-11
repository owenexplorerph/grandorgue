/*
 * GrandOrgue - free pipe organ simulator based on MyOrgan
 *
 * MyOrgan 1.0.6 Codebase - Copyright 2006 Milan Digital Audio LLC
 * MyOrgan is a Trademark of Milan Digital Audio LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef GORGUEMIDIRECEIVER_H
#define GORGUEMIDIRECEIVER_H

#include <wx/wx.h>
#include <vector>
#include "GOrgueMidiEvent.h"

class GrandOrgueFile;
class IniFileConfig;
struct IniFileEnumEntry;

typedef enum {
	MIDI_RECV_DRAWSTOP,
	MIDI_RECV_BUTTON,
	MIDI_RECV_ENCLOSURE,
	MIDI_RECV_MANUAL,
} MIDI_RECEIVER_TYPE;

typedef enum {
	MIDI_MATCH_NONE,
	MIDI_MATCH_ON,
	MIDI_MATCH_OFF,
	MIDI_MATCH_CHANGE,
	MIDI_MATCH_RESET,
} MIDI_MATCH_TYPE;

typedef enum {
	MIDI_M_NONE = MIDI_NONE,
	MIDI_M_RESET = MIDI_RESET,
	MIDI_M_NOTE = MIDI_NOTE,
	MIDI_M_CTRL_CHANGE = MIDI_CTRL_CHANGE,
	MIDI_M_PGM_CHANGE = MIDI_PGM_CHANGE,
	MIDI_M_NOTE_ON,
	MIDI_M_NOTE_OFF,
	MIDI_M_CTRL_CHANGE_ON,
	MIDI_M_CTRL_CHANGE_OFF,
} midi_match_message_type;

typedef struct {
	wxString device;
	midi_match_message_type type;
	int channel;
	int key;
} MIDI_MATCH_EVENT;

class GOrgueMidiReceiver {
private:
	GrandOrgueFile* m_organfile;
	static const struct IniFileEnumEntry m_MidiTypes[];
	MIDI_RECEIVER_TYPE m_type;
	int m_Key;
	int m_Index;
	std::vector<MIDI_MATCH_EVENT> m_events;

public:
	GOrgueMidiReceiver(GrandOrgueFile* organfile, MIDI_RECEIVER_TYPE type);

	void Load(IniFileConfig& cfg, wxString group);
	void Save(IniFileConfig& cfg, bool prefix, wxString group);

	MIDI_RECEIVER_TYPE GetType() const;

	void SetIndex(int index);

	MIDI_MATCH_TYPE Match(const GOrgueMidiEvent& e);
 	MIDI_MATCH_TYPE Match(const GOrgueMidiEvent& e, int& value);

	unsigned GetEventCount() const;
	MIDI_MATCH_EVENT& GetEvent(unsigned index);
	unsigned AddNewEvent();
	void DeleteEvent(unsigned index);
};

#endif
