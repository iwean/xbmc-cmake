#pragma once
/*
 *      Copyright (C) 2010-2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "addons/Addon.h"
#include "addons/AddonDll.h"
#include "addons/DllAudioDSP.h"
#include "threads/CriticalSection.h"
#include "utils/Observer.h"
#include "utils/StringUtils.h"

namespace ActiveAE
{
  class CActiveAEDSPDatabase;

  #define AE_DSP_MASTER_MODE_ID_PASSOVER          (0)  /* Used to ignore master processing */
  #define AE_DSP_MASTER_MODE_ID_INVALID           (-1)
  
  /*!
   * DSP Mode information class
   */
  //@{
  class CActiveAEDSPMode : public Observable
  {
    friend class CActiveAEDSPDatabase;

  public:
    /*! @brief Create a new mode */
    CActiveAEDSPMode();
    CActiveAEDSPMode(const AE_DSP_BASETYPE baseType);
    CActiveAEDSPMode(const AE_DSP_MASTER_MODES::AE_DSP_MASTER_MODE &mode, int iAddonId);
    CActiveAEDSPMode(const CActiveAEDSPMode &mode);

    bool operator ==(const CActiveAEDSPMode &right) const;
    bool operator !=(const CActiveAEDSPMode &right) const;
    CActiveAEDSPMode &operator=(const CActiveAEDSPMode &mode);

    bool Delete(void);
    int AddUpdate(void);
    bool UpdateFromAddon(const CActiveAEDSPMode &mode);
    bool IsNew(void) const;
    bool IsKnown(void);
    bool IsChanged(void) const;
    bool IsPrimary(void) const;
    int ModeID(void) const;
    bool IsHidden(void) const;
    bool SetHidden(bool bIsHidden);
    CStdString IconOwnModePath(void) const;
    bool SetIconOwnModePath(const CStdString &strIconPath);
    CStdString IconOverrideModePath(void) const;
    bool SetIconOverrideModePath(const CStdString &strIconPath);
    bool SetModeID(int iDatabaseId);
    AE_DSP_BASETYPE BaseType(void) const;
    bool SetBaseType(AE_DSP_BASETYPE baseType);
    static bool SupportStreamType(AE_DSP_STREAMTYPE streamType, unsigned int flags);
    bool SupportStreamType(AE_DSP_STREAMTYPE streamType);
    unsigned int StreamTypeFlags(void) const;
    bool SetStreamTypeFlags(unsigned int streamTypeFlags);
    int ModeName(void) const;
    bool SetModeName(int iModeName);
    int ModeSetupName(void) const;
    bool SetModeSetupName(int iModeSetupName);
    int ModeHelp(void) const;
    bool SetModeHelp(int iModeHelp);
    int ModeDescription(void) const;
    bool SetModeDescription(int iModeDescription);
    bool HasSettingsDialog(void) const;
    int AddonID(void) const;
    bool SetAddonID(int iAddonId);
    int AddonModeNumber(void) const;
    bool SetAddonModeNumber(int iAddonModeNumber);
    CStdString AddonModeName(void) const;
    bool SetAddonModeName(const CStdString &strAddonModeName);

  private:
    /*! @name XBMC related mode data
     */
    //@{
    int               m_iModeId;                 /*!< the identifier given to this mode by the DSP database */
    unsigned int      m_iStreamTypeFlags;        /*!< The stream content type flags */
    AE_DSP_BASETYPE   m_iBaseType;               /*!< The stream source coding format */
    bool              m_bIsHidden;               /*!< true if this mode is hidden, false if not */
    CStdString        m_strOwnIconPath;          /*!< the path to the icon for this mode */
    CStdString        m_strOverrideIconPath;     /*!< the path to the icon for this mode */
    int               m_iModeName;               /*!< the name id for this mode used by XBMC */
    int               m_iModeSetupName;          /*!< the name id for this mode inside settings used by XBMC */
    int               m_iModeDescription;        /*!< the description id for this mode used by XBMC */
    int               m_iModeHelp;               /*!< the help id for this mode used by XBMC */
    bool              m_bChanged;                /*!< true if anything in this entry was changed that needs to be persisted */
    bool              m_bHasSettingsDialog;      /*!< the mode have a own settings dialog */
    //@}

    /*! @name Audio dsp add-on related mode data
     */
    //@{
    int               m_iAddonId;                /*!< the identifier of the Addon that serves this mode */
    int               m_iAddonModeNumber;        /*!< the mode number on the Addon */
    CStdString        m_strAddonModeName;        /*!< the name of this mode on the Addon */
    bool              m_bIsPrimary;              /*!< if set to true this mode is the first used one (if nothing other becomes selected by hand) */
    //@}

    CCriticalSection m_critSection;
  };
  //@}
}
