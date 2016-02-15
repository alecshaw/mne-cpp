//=============================================================================================================
/**
* @file     gusbamp.cpp
* @author   Viktor Klüber <viktor.klueber@tu-ilmenau.de>;
*           Lorenz Esch <lorenz.esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>;
* @version  1.0
* @date     November, 2015
*
* @section  LICENSE
*
* Copyright (C) 2015, Viktor Klüber, Lorenz Esch and Matti Hamalainen. All rights reserved.
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
* @brief    Contains the implementation of the GUSBAmp class.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "gusbamp.h"
#include "gusbampproducer.h"
#include "gtec_gusbamp.h"       /**< heder-file from gTec for gubamp amplifier*/


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QtCore/QtPlugin>
#include <QDebug>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace GUSBAmpPlugin;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

GUSBAmp::GUSBAmp()
: m_pRMTSA_GUSBAmp(0)
, m_qStringResourcePath(qApp->applicationDirPath()+"/mne_x_plugins/resources/gusbamp/")
, m_pRawMatrixBuffer_In(0)
, m_pGUSBAmpProducer(new GUSBAmpProducer(this))
{
}


//*************************************************************************************************************

GUSBAmp::~GUSBAmp()
{
    //std::cout << "GUSBAmp::~GUSBAmp() " << std::endl;

    //If the program is closed while the sampling is in process
    if(this->isRunning())
        this->stop();
}


//*************************************************************************************************************


//void GUSBAmp::setUpFiffInfo()
//{
//    // Only works for ANT Neuro Waveguard Duke caps
//    //
//    //Clear old fiff info data
//    //
//    m_pFiffInfo->clear();

//    //
//    //Set number of channels, sampling frequency and high/-lowpass
//    //
//    m_pFiffInfo->nchan = m_iNumberOfChannels;
//    m_pFiffInfo->sfreq = m_iSamplingFreq;
//    m_pFiffInfo->highpass = (float)0.001;
//    m_pFiffInfo->lowpass = m_iSamplingFreq/2;

//    //
//    //Set up the channel info
//    //
//    QStringList QSLChNames;
//    m_pFiffInfo->chs.clear();

//    for(int i=0; i<m_iNumberOfChannels; i++)
//    {
//        //Create information for each channel
//        QString sChType;
//        FiffChInfo fChInfo;

//        //EEG Channels
//        if(i<=numberEEGCh-1)
//        {
//            //Set channel name
//            //fChInfo.ch_name = elcChannelNames.at(i);
//            sChType = QString("EEG ");
//            if(i<10)
//                sChType.append("00");

//            if(i>=10 && i<100)
//                sChType.append("0");

//            fChInfo.ch_name = sChType.append(sChType.number(i));

//            //Set channel type
//            fChInfo.kind = FIFFV_EEG_CH;

//            //Set coil type
//            fChInfo.coil_type = FIFFV_COIL_EEG;

//            //Set logno
//            fChInfo.logno = i;

//            //Set coord frame
//            fChInfo.coord_frame = FIFFV_COORD_HEAD;

//            //Set unit
//            fChInfo.unit = FIFF_UNIT_V;
//            fChInfo.unit_mul = 0;

//            //cout<<i<<endl<<fChInfo.eeg_loc<<endl;
//        }

//        QSLChNames << sChType;

//        m_pFiffInfo->chs.append(fChInfo);
//    }

//    //Set channel names in fiff_info_base
//    m_pFiffInfo->ch_names = QSLChNames;

//    //
//    //Set head projection
//    //
//    m_pFiffInfo->dev_head_t.from = FIFFV_COORD_DEVICE;
//    m_pFiffInfo->dev_head_t.to = FIFFV_COORD_HEAD;
//    m_pFiffInfo->ctf_head_t.from = FIFFV_COORD_DEVICE;
//    m_pFiffInfo->ctf_head_t.to = FIFFV_COORD_HEAD;
//}

//*************************************************************************************************************


QSharedPointer<IPlugin> GUSBAmp::clone() const
{
    QSharedPointer<GUSBAmp> pGUSBAmpClone(new GUSBAmp());
    return pGUSBAmpClone;
}


//*************************************************************************************************************

void GUSBAmp::init()
{
    m_pRMTSA_GUSBAmp = PluginOutputData<NewRealTimeMultiSampleArray>::create(this, "GUSBAmp", "EEG output data");

    //m_outputConnectors.append(m_pRMTSA_GUSBAmp);

    m_bIsRunning = false;
}


//*************************************************************************************************************

void GUSBAmp::unload()
{

}


//*************************************************************************************************************

bool GUSBAmp::start()
{
    //Check if the thread is already or still running. This can happen if the start button is pressed immediately after the stop button was pressed. In this case the stopping process is not finished yet but the start process is initiated.
    if(this->isRunning())
        QThread::wait();

//    //Setup fiff info
//    setUpFiffInfo();

//    //Set the channel size of the RMTSA - this needs to be done here and NOT in the init() function because the user can change the number of channels during runtime
//    m_pRMTSA_TMSI->data()->initFromFiffInfo(m_pFiffInfo);
//    m_pRMTSA_TMSI->data()->setMultiArraySize(m_iSamplesPerBlock);
//    m_pRMTSA_TMSI->data()->setSamplingRate(m_iSamplingFreq);

    //Buffer
    m_pRawMatrixBuffer_In = QSharedPointer<RawMatrixBuffer>(new RawMatrixBuffer(8, 16, 1024));

    m_pGUSBAmpProducer->start();

    if(m_pGUSBAmpProducer->isRunning())
    {
        m_bIsRunning = true;
        QThread::start();
        return true;
    }
    else
    {
        qWarning() << "Plugin GUSBAmp - ERROR - GUSBAmpProducer thread could not be started - Either the device is turned off (check your OS device manager) or the driver DLL (GUSBAmpSDK.dll / GUSBAmpSDK32bit.dll) is not installed in the system32 / SysWOW64 directory" << endl;
        return false;
    }


}


//*************************************************************************************************************

bool GUSBAmp::stop()
{
    //Stop the producer thread first
    m_pGUSBAmpProducer->stop();

    //Wait until this thread (GUSBAmp) is stopped
    m_bIsRunning = false;

    //In case the semaphore blocks the thread -> Release the QSemaphore and let it exit from the pop function (acquire statement)
    m_pRawMatrixBuffer_In->releaseFromPop();

    m_pRawMatrixBuffer_In->clear();

    m_pRMTSA_GUSBAmp->data()->clear();

    return true;
}


//*************************************************************************************************************

IPlugin::PluginType GUSBAmp::getType() const
{
    return _ISensor;
}


//*************************************************************************************************************

QString GUSBAmp::getName() const
{
    return "GUSBAmp EEG";
}


//*************************************************************************************************************

QWidget* GUSBAmp::setupWidget()
{
    GUSBAmpSetupWidget* widget = new GUSBAmpSetupWidget(this);//widget is later destroyed by CentralWidget - so it has to be created everytime new

    //init properties dialog
    widget->initGui();

    return widget;
}


//*************************************************************************************************************

void GUSBAmp::run()
{
    while(m_bIsRunning)
    {
        //pop matrix only if the producer thread is running
        if(m_pGUSBAmpProducer->isRunning())
        {
            //qDebug()<<"GUSBAmp is running";
            MatrixXf matValue = m_pRawMatrixBuffer_In->pop();

            //emit values to real time multi sample array
            m_pRMTSA_GUSBAmp->data()->setValue(matValue.cast<double>());
        }
    }
}


