//=============================================================================================================
/**
* @file     spectrumsettingsview.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     May, 2014
*
* @section  LICENSE
*
* Copyright (C) 2014, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Declaration of the SpectrumSettingsView Class.
*
*/

#ifndef SPECTRUMSETTINGSVIEW_H
#define SPECTRUMSETTINGSVIEW_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../disp_global.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QWidget>
#include <QPointer>


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class QSlider;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE DISPLIB
//=============================================================================================================

namespace DISPLIB
{


//*************************************************************************************************************
//=============================================================================================================
// DISPLIB FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* DECLARE CLASS SpectrumSettingsView
*
* @brief The SpectrumSettingsView class provides settings for the spectrum estimation
*/
class DISPSHARED_EXPORT SpectrumSettingsView : public QWidget
{
    Q_OBJECT

public:    
    typedef QSharedPointer<SpectrumSettingsView> SPtr;              /**< Shared pointer type for SpectrumSettingsView. */
    typedef QSharedPointer<const SpectrumSettingsView> ConstSPtr;   /**< Const shared pointer type for SpectrumSettingsView. */

    //=========================================================================================================
    /**
    * Constructs a SpectrumSettingsView which is a child of parent.
    *
    * @param [in] parent    parent of widget
    */
    SpectrumSettingsView(QWidget *parent,
                         Qt::WindowFlags f = Qt::Widget);

    //=========================================================================================================
    /**
    * Update slider value
    *
    * @param [in] value    slider value
    */
    void updateValue(qint32 value);

signals:
    //=========================================================================================================
    /**
    * Emitted whenever the settings changed and are ready to be retreived.
    */
    void settingsChanged();

public:
    QPointer<QSlider>   m_pSliderLowerBound;    /**< Lower bound frequency */
    QPointer<QSlider>   m_pSliderUpperBound;    /**< Upper bound frequency */
};

} // NAMESPACE

#endif // SPECTRUMSETTINGSVIEW_H
