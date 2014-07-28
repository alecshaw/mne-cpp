//=============================================================================================================
/**
* @file     realtimecov.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     February, 2013
*
* @section  LICENSE
*
* Copyright (C) 2013, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the declaration of the RealTimeCov class.
*
*/

#ifndef REALTIMECOV_H
#define REALTIMECOV_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "xmeas_global.h"
#include "newmeasurement.h"
#include "realtimesamplearraychinfo.h"

#include <fiff/fiff_cov.h>


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QSharedPointer>
#include <QVector>
#include <QList>
#include <QColor>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE XMEASLIB
//=============================================================================================================

namespace XMEASLIB
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace FIFFLIB;


//=========================================================================================================
/**
* DECLARE CLASS RealTimeCov -> ToDo check feasibilty of QAbstractTableModel
*
* @brief The RealTimeMultiSampleArrayNew class is the base class of every RealTimeMultiSampleArrayNew Measurement.
*/
class XMEASSHARED_EXPORT RealTimeCov : public NewMeasurement
{
    Q_OBJECT
public:
    typedef QSharedPointer<RealTimeCov> SPtr;               /**< Shared pointer type for RealTimeCov. */
    typedef QSharedPointer<const RealTimeCov> ConstSPtr;    /**< Const shared pointer type for RealTimeCov. */

    //=========================================================================================================
    /**
    * Constructs a RealTimeMultiSampleArrayNew.
    */
    explicit RealTimeCov(QObject *parent = 0);

    //=========================================================================================================
    /**
    * Destroys the RealTimeMultiSampleArrayNew.
    */
    virtual ~RealTimeCov();

    //=========================================================================================================
    /**
    * New covariance to distribute
    *
    * @param [in] v     the covariance which should be distributed.
    */
    virtual void setValue(FiffCov& v);

    //=========================================================================================================
    /**
    * Returns the current value set.
    * This method is inherited by Measurement.
    *
    * @return the last attached value.
    */
    virtual FiffCov::SPtr& getValue();

    //=========================================================================================================
    /**
    * Returns whether RealTimeCov contains values
    *
    * @return whether RealTimeCov contains values.
    */
    inline bool isInitialized() const;

private:
    FiffCov::SPtr               m_pFiffCov;     /**< Covariance data set */

    bool                        m_bInitialized;     /**< If values are stored.*/
};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

inline bool RealTimeCov::isInitialized() const
{
    return m_bInitialized;
}

} // NAMESPACE

Q_DECLARE_METATYPE(XMEASLIB::RealTimeCov::SPtr)

#endif // REALTIMECOV_H
