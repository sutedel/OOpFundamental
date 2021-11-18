
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignment.

#include <string>
#include <algorithm>
#include <iostream>

#include "Utilities.h"

namespace sdds
{
    //assigning delimiter
    char Utilities::m_delimiter = ' ';

    //set field width
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    //return field width
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    //extracting a token based on the provided string, starting position and return the found token
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        std::string tempstr = "";
        //get starting position of the token
        size_t startpos = next_pos;

        //find the position of next delimiter
        next_pos = str.find(m_delimiter, startpos);

        //check if token was found and set the token in the tempstr accordingly
        if (next_pos == std::string::npos)
        {
            tempstr = str.substr(startpos);
            if (tempstr.size() > m_widthField)
            {
                m_widthField = tempstr.size();
            }
            more = false;
        }
        else if (next_pos > startpos)
        {
            tempstr = str.substr(startpos, (next_pos - startpos));
            if (tempstr.size() > m_widthField)
            {
                m_widthField = tempstr.size();
            }
            more = true;
        }
        else
        {
            more = false;
            throw "Invalid token!";
        }
        next_pos++;
        return tempstr;
    }

    //set new delimiter
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    //return the current delimiter
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}
