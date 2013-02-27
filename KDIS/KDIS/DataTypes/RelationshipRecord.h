/*********************************************************************
Copyright 2013 KDIS
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

For Further Information Please Contact me at
Karljj1@yahoo.com
http://p.sf.net/kdis/UserGuide
*********************************************************************/

/********************************************************************
    class:      RelationshipRecord
    created:    26/06/2008
    author:     Karl Jones

    purpose:    Specifies the relationship of the part entity to its host entity.
    size:       32 bits / 4 octets
*********************************************************************/

#pragma once

#include "./DataTypeBase.h"

namespace KDIS {
namespace DATA_TYPE {

using KDIS::DATA_TYPE::ENUMS::RelationshipNature;
using KDIS::DATA_TYPE::ENUMS::RelationshipPosition;

class KDIS_EXPORT RelationshipRecord : public DataTypeBase
{
protected:

    KUINT16 m_ui16Nature;

    KUINT16 m_ui16Pos;

public:

    static const KUINT16 RELATIONSHIP_RECORD_SIZE = 4;

    RelationshipRecord();

    RelationshipRecord( KDataStream & stream )throw( KException );

    RelationshipRecord( RelationshipNature N, RelationshipPosition P );

    virtual ~RelationshipRecord();

    //************************************
    // FullName:    KDIS::DATA_TYPE::RelationshipRecord::SetNature
    //              KDIS::DATA_TYPE::RelationshipRecord::GetNature
    // Description: Nature or purpose for joining of the part entity to the host
    //              entity within a IsPartOf PDU.
    // Parameter:   RelationshipNature N, void
    //************************************
    void SetNature( RelationshipNature N );
    RelationshipNature GetNature() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::RelationshipRecord::SetPosition
    //              KDIS::DATA_TYPE::RelationshipRecord::GetPosition
    // Description: Specifies the position of the part entity with respect to the host
    //              entity within a IsPartOf PDU.
    // Parameter:   RelationshipPosition P, void
    //************************************
    void SetPosition( RelationshipPosition P );
    RelationshipPosition GetPosition() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::RelationshipRecord::GetAsString
    // Description: Returns a string representation
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::RelationshipRecord::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::DATA_TYPE::RelationshipRecord::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const RelationshipRecord & Value ) const;
    KBOOL operator != ( const RelationshipRecord & Value ) const;
};

} // END namespace DATA_TYPES
} // END namespace KDIS
