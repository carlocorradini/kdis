/*********************************************************************
For Further Information on KDIS:
http://p.sf.net/kdis/UserGuide


Example created by request: https://sourceforge.net/p/kdis/discussion/879756/thread/89a6e27d/

*********************************************************************/

#include <iostream>
#include "KDIS/Extras/PDU_Factory.h"
#include "KDIS/DataTypes/VariableDatum.h"
#include "KDIS/DataTypes/EntityIdentifier.h"
#include "KDIS/DataTypes/WorldCoordinates.h"
#include "KDIS/PDU/Simulation_Management/Set_Data_PDU.h"

using namespace std;
using namespace KDIS;
using namespace DATA_TYPE;
using namespace PDU;
using namespace UTILS;

// An example custom Variable Datum that contains a Entity ID and World Coordinates Record
class TargetPosition : public VariableDatum
{
private:

	// Entity ID
	EntityIdentifier m_EntID;

	// Our target position 
	WorldCoordinates m_worldCoords;

	KUINT16 m_ui16padding;

public:

	// Ctor
	TargetPosition( EntityIdentifier id, WorldCoordinates wc ) :
	  m_EntID( id ),
	  m_worldCoords( wc ),
	  m_ui16padding( 0 )
	{
		m_ui32DatumID = 12345; // Our DatumID. Pick something to use that is not already in the DatumID enum.
		
		// Add the length of our fields on
		m_ui32DatumLength = EntityIdentifier::ENTITY_IDENTIFER_SIZE * 8; // The Datum length is the size in BITS of our custom data
		m_ui32DatumLength += WorldCoordinates::WORLD_COORDINATES_SIZE * 8; 
	}

	// Ctor
	TargetPosition( KDataStream & stream )
	{
		Decode( stream );
	}

	virtual ~TargetPosition()
	{
	}
	
    virtual KString GetAsString() const
	{
		KStringStream ss;

		ss << "This is our custom VariableDatum!!!!\n"
			<< m_EntID.GetAsString()
			<< m_worldCoords.GetAsString();
		
		return ss.str();
	}

	// Our custom decode function.
    virtual void Decode( KDataStream & stream ) throw( KException )
	{
		// Deocode the standard variable datum fields
		stream >> m_ui32DatumID
               >> m_ui32DatumLength;

		// Now decode our 'extra' fields.
		stream >> KDIS_STREAM m_EntID
			   >> KDIS_STREAM m_worldCoords
			   >> m_ui16padding; // The variable datum needs to be padded to a 64 bit boundry, with our 2 new fields the total size is 38 bytes, we need 2 more bytes to be on a 64 bit boundry(40).
	}

    virtual void Encode( KDataStream & stream ) const
	{
		// Encode the standard variable datum fields
		stream << m_ui32DatumID
               << m_ui32DatumLength;

		// Now encode our 'extra' fields.
		stream << KDIS_STREAM m_EntID
			   << KDIS_STREAM m_worldCoords
			   << m_ui16padding; // The variable datum needs to be padded to a 64 bit boundry, with our 2 new fields the total size is 38 bytes, we need 2 more bytes to be on a 64 bit boundry(40).
	}
};

// 
// Our decoder class. This tells KDIS how to decode a specific DatumID. So when the DatumID is 12345 we want to create a TargetPositionRecord
//
class TargetPositionDecoderClass : public FactoryDecoder<VariableDatum>
{
public:

	TargetPositionDecoderClass(){};

	~TargetPositionDecoderClass(){};

	// This is our factory decode function, we do the decoding for KDIS in here.
	virtual VariableDatum * FactoryDecode( KINT32 EnumVal, KDataStream & stream )
	{
		// This should allways return a new data type, however you can return NULL.
		if( EnumVal == 12345 )
		{
			return new TargetPosition( stream );
		}
		else return 0;
	}
};

int main()
{
	try
	{
		// 1
		// Register our factory decode function, KDIS will use this deocoder when it encounters a VariableDatum record that has this DatumID
		VariableDatum::RegisterFactoryDecoder( 12345, new TargetPositionDecoderClass );

		// 2
		// Create an instance of our data type.		
		TargetPosition * pTargetPos = new TargetPosition( EntityIdentifier( 1, 2, 3 ), WorldCoordinates( 3, 2, 1 ) );
		
		// 3
		// Now create a PDU that uses this data type and add it like normal.
		Set_Data_PDU ourPDU;
		ourPDU.AddVariableDatum( pTargetPos );

		// 4 
		// Encode the PDU.		
		KDataStream stream = ourPDU.Encode();
		
		// 5
		// Lets skip actually sending this data over the network in order to keep things simple..
		//

		// 6
		// Now decode the PDU as if we have just received it from the network.		
		PDU_Factory pduFact;
		auto_ptr<Header> pdu = pduFact.Decode( stream );
		
		if( pdu.get() )
		{
			// Here we should see that our variable datum has been correctly decoded.
			cout << pdu->GetAsString() << endl;

			// Lets get the decoded class
			Set_Data_PDU * ourRecPDU = ( Set_Data_PDU * )pdu.get();
			
			// Get the first and only item.
			VarDtmPtr pVd = ourRecPDU->GetVariableDatum()[0];

			// Now upcast so we get our data type.
			TargetPosition * pMyRecvTargetPos = dynamic_cast<TargetPosition*>( pVd.GetPtr() );
			
			if( pMyRecvTargetPos )
			{
				cout << "Ta da!, we got the custom data class back out!" << endl;				
			}
		}
		else
		{
			cout << "Something went horribly wrong!" << endl;
		}
	}
	catch( exception & e )
	{
		cout  << e.what() << endl;
	}

	// 7
	// Now we should clean up memory. Our decoder will not be deleted unless we call ClearFactoryDecoders.
	VariableDatum::ClearFactoryDecoders();

    return 0;
}
