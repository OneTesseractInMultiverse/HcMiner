//
// Created by pedro on 7/5/17.
//

#include "XmlUtil.h"

// =======================================================================
// FUNCTION CREATE XML
// =======================================================================
/**
 * Creates a valid Xml document from a vector of data captures and sets
 * the indicator that they represent.
 * @param indicator the name of the indicator that the data represent
 * @param captures a pointer to the std::vector where the data captures are
 *        located.
 * @return a std::string with the corresponding xml representation of the
 *         mined data.
 */
std::string XmlUtil::createXml(std::string indicator, std::vector<double> * captures) {
    std::ostringstream os;
    if(!captures->empty()){
        os << "<?xml version=\"1.0\" ?>" << std::endl;
        os << "<perf-block>" << std::endl;
        os << "\t<perf-indicator>" << indicator << "</perf-indicator>" << std::endl;
        os << "\t<data>" << std::endl;
        for(auto i = captures->begin(); i != captures->end(); ++i){
            os << "\t\t<item>" << *i << "</item>" << std::endl;
        } // FOR ENDS
        os << "\t</data>" << std::endl;
        os << "</perf-block>" << std::endl;
    } // IF ENDS
    return os.str();
} // METHOD CREATE XML ENDS
