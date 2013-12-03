/**
 * KIARA Transport Library Message
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */

#include "../../include/KT_Msg.hpp"

namespace KIARA {
namespace Transport {

//
// Constructors/Destructors
//  

KT_Msg::KT_Msg ( ) { 
    _payload = new std::vector < char >;
    //_metadata = new std::map < std::string, std::string >; 
}
KT_Msg::~KT_Msg ( ) { }

KT_Msg::KT_Msg ( std::vector< char > *payload) {
    _payload = payload;
}

//  
// Methods
//

/**
 * Add a key-value metadata pair to _metadata
 * @param key A std::string as key
 * @param value A std::string as value
 */
void KT_Msg::add_metadata ( std::string &key, std::string &value ) {
    std::pair < std::string, std::string > elem (key, value);
    _metadata.insert ( elem );
}

/**
 * Return a serialized variant of the _metadata
 * @param delim A delimiter, standard is ':'
 * @return A std::string with a serialized variant
 */
std::string KT_Msg::get_serialized_metadata ( const std::string delim = ":" ) {
    std::map < std::string, std::string >::iterator metadata_iter;
    std::string result;
    
    for ( metadata_iter = _metadata.begin();
            _metadata.end() != metadata_iter;
            metadata_iter++ )
    {
        result += metadata_iter->first + delim + metadata_iter->second + "\n";
    }
    return result;
}

} // end of Transport namespace
} // end of KIARA namespace
