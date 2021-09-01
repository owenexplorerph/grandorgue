/*
 * GrandOrgue - free pipe organ simulator
 *
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2019 GrandOrgue contributors (see AUTHORS)
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include <wx/app.h>
#include <wx/bookctrl.h>
#include <wx/button.h>
#include <wx/choicdlg.h> 
#include <wx/msgdlg.h>
#include <wx/sizer.h>

#include "SettingsDialog.h"

#include "GOrgueEvent.h"
#include "GOrgueSound.h"
#include "GrandOrgueID.h"
#include "SettingsArchives.h"
#include "SettingsAudioGroup.h"
#include "SettingsAudioOutput.h"
#include "SettingsDefaults.h"
#include "SettingsMidiDevices.h"
#include "SettingsMidiMessage.h"
#include "SettingsOption.h"
#include "SettingsOrgan.h"
#include "SettingsReverb.h"
#include "SettingsTemperaments.h"

BEGIN_EVENT_TABLE(SettingsDialog, wxPropertySheetDialog)
	EVT_BUTTON(wxID_APPLY, SettingsDialog::OnApply)
	EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
	EVT_BUTTON(wxID_HELP, SettingsDialog::OnHelp)
	EVT_BUTTON(ID_REASONS, SettingsDialog::OnReasons)
END_EVENT_TABLE()

SettingsDialog::SettingsDialog(
  wxWindow* win, GOrgueSound& sound, SettingsReasons *reasons
): wxPropertySheetDialog(
  win, wxID_ANY, _("Program Settings"), wxDefaultPosition, wxDefaultSize,
  wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxDIALOG_NO_PARENT
), m_Sound(sound), m_Reasons(reasons)
{
  wxBookCtrlBase* notebook = GetBookCtrl();

  m_MidiDevicePage = new SettingsMidiDevices(m_Sound, notebook);
  m_OptionsPage = new SettingsOption(m_Sound.GetSettings(), notebook);
  m_OrganPage = new SettingsOrgan(m_Sound.GetSettings(), m_Sound.GetMidi(), notebook);
  m_ArchivePage = new SettingsArchives(m_Sound.GetSettings(), *m_OrganPage, notebook);
  m_MidiMessagePage = new SettingsMidiMessage(m_Sound.GetSettings(), m_Sound.GetMidi(), notebook);
  m_GroupPage = new SettingsAudioGroup(m_Sound.GetSettings(), notebook);
  m_OutputPage = new SettingsAudioOutput(m_Sound, *m_GroupPage, notebook);
  m_ReverbPage = new SettingsReverb(m_Sound.GetSettings(), notebook);
  m_TemperamentsPage = new SettingsTemperaments(m_Sound.GetSettings(), notebook);
  m_DefaultsPage = new SettingsDefaults(m_Sound.GetSettings(), notebook);

  notebook->AddPage(m_OptionsPage,  _("Options"));
  notebook->AddPage(m_DefaultsPage,  _("Defaults and Initial Settings"));
  notebook->AddPage(m_OutputPage, _("Audio Output"));
  notebook->AddPage(m_ReverbPage, _("Reverb"));
  notebook->AddPage(m_GroupPage, _("Audio Groups"));
  notebook->AddPage(m_OrganPage, _("Organs"));
  notebook->AddPage(m_MidiDevicePage,  _("MIDI Devices"));
  notebook->AddPage(m_TemperamentsPage, _("Temperaments"));
  notebook->AddPage(m_MidiMessagePage, _("Initial MIDI Configuration"));
  notebook->AddPage(m_ArchivePage, _("Organ Packages"));
  
  bool hasReasons = reasons && reasons->size();
  
  notebook->SetSelection(hasReasons ? reasons->operator[](0).m_SettingsPageNum : 0);

  // add a custom button 'Reason into the space of the standard dialog button
  wxSizer * const pButtonSizer = CreateButtonSizer(wxOK | wxCANCEL | wxHELP);
  
  if (pButtonSizer)
  {
    wxButton * const pReasonBtn = new wxButton(this, ID_REASONS, _("Reason"));
    
    if (hasReasons)
    {
      wxCommandEvent event(wxEVT_BUTTON, ID_REASONS);

      GetEventHandler()->AddPendingEvent(event);
    } else
      pReasonBtn->Disable();
      
    pButtonSizer->Insert(3, pReasonBtn, wxSizerFlags().Border(wxLEFT | wxRIGHT, 20));
    GetInnerSizer()->Add(pButtonSizer, wxSizerFlags().Expand().Border(wxALL, 2));
    GetInnerSizer()->AddSpacer(2);
  }

  LayoutDialog();
}

SettingsDialog::~SettingsDialog()
{
  if (m_OptionsPage->NeedReload() &&  m_Sound.GetOrganFile() != NULL)
  {
	  if (wxMessageBox(_("Some changed settings effect unless the sample set is reloaded.\n\nWould you like to reload the sample set now?"), _("GrandOrgue"), wxYES_NO | wxICON_QUESTION, this) == wxYES)
	  {
		  wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, ID_FILE_RELOAD);
		  wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(event);
	  }
  }
}

void SettingsDialog::OnApply(wxCommandEvent& event)
{
	DoApply();
}

void SettingsDialog::OnHelp(wxCommandEvent& event)
{
	wxCommandEvent help(wxEVT_SHOWHELP, 0);
	help.SetString(GetBookCtrl()->GetPageText(GetBookCtrl()->GetSelection()));
	wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(help);
}

void SettingsDialog::OnOK(wxCommandEvent& event)
{
	if (DoApply())
		event.Skip();
}

bool SettingsDialog::DoApply()
{
	if (!(this->Validate()))
		return false;

	m_MidiDevicePage->Save();
	m_OptionsPage->Save();
	m_OrganPage->Save();
	m_ArchivePage->Save();
	m_GroupPage->Save();
	m_OutputPage->Save();
	m_ReverbPage->Save();
	m_TemperamentsPage->Save();
	m_DefaultsPage->Save();

	return true;
}

void SettingsDialog::OnReasons(wxCommandEvent& event)
{
  unsigned nReasons = m_Reasons ? (unsigned) m_Reasons->size() : 0;
  
  if (nReasons)
  {
    wxBookCtrlBase* const notebook = GetBookCtrl();
    const int currPageNum = notebook->GetSelection();
    wxArrayString reasonStrs;
    unsigned currReasonIndex = 0;
    
    for (unsigned i = 0; i < nReasons; i++)
    {
      const SettingsReason &reason(m_Reasons->operator[](i));
      
      reasonStrs.Add(reason.m_ReasonMessage);
      if ((int) reason.m_SettingsPageNum == currPageNum)
	currReasonIndex = i;
    }
    
    const int index = wxGetSingleChoiceIndex(wxEmptyString, _("Settings Reason"), reasonStrs, currReasonIndex, this);
    
    if (index >= 0)
      GetBookCtrl()->SetSelection(m_Reasons->operator[](index).m_SettingsPageNum);
  }
}
